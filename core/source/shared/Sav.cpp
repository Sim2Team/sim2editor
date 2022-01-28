/*
*   This file is part of Sim2Editor-CPPCore
*   Copyright (C) 2020-2022 Sim2Team
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*   Additional Terms 7.b and 7.c of GPLv3 apply to this file:
*       * Requiring preservation of specified reasonable legal notices or
*         author attributions in that material or in the Appropriate Legal
*         Notices displayed by works containing it.
*       * Prohibiting misrepresentation of the origin of that material,
*         or requiring that modified versions of such material be marked in
*         reasonable ways as different from the original version.
*/

#include "Checksum.hpp"
#include "DataHelper.hpp"
#include "Sav.hpp"


namespace S2Core {
	/*
		Initialize the Sav.

		const std::string &SavFile: The SavFile path.
	*/
	SAV::SAV(const std::string &SavFile) : SavPath(SavFile) {
		FILE *SFile = fopen(this->SavPath.c_str(), "r");

		if (SFile) {
			fseek(SFile, 0, SEEK_END);
			this->SavSize = ftell(SFile);
			fseek(SFile, 0, SEEK_SET);

			/*
				0x10000 & 0x20000: GBA Savefile sizes.
				0x40000 & 0x80000: NDS Savefile sizes.
			*/
			if (this->SavSize == 0x10000 || this->SavSize == 0x20000 || this->SavSize == 0x40000 || this->SavSize == 0x80000) {
				this->SavData = std::make_unique<uint8_t[]>(this->GetSize());
				fread(this->SavData.get(), 1, this->GetSize(), SFile);

				this->ValidationCheck();
			}

			fclose(SFile);
		}
	};


	/*
		A second way for the Initializer.

		std::unique_ptr<uint8_t[]> &Data: The raw Save Buffer.
		const uint32_t Size: The size of the Save Buffer.
	*/
	SAV::SAV(std::unique_ptr<uint8_t[]> &Data, const uint32_t Size) {
		/*
			0x10000 & 0x20000: GBA Savefile sizes.
			0x40000 & 0x80000: NDS Savefile sizes.
		*/
		if (this->SavSize == 0x10000 || this->SavSize == 0x20000 || this->SavSize == 0x40000 || this->SavSize == 0x80000) {
			this->SavData = std::move(Data);
			this->SavSize = Size;

			this->ValidationCheck();
		}
	};


	/* Some Save Validation checks. */
	void SAV::ValidationCheck() {
		if (!this->GetData()) return;

		switch(this->SavSize) {
			/* Game Boy Advance. */
			case 0x10000:
			case 0x20000: {
				bool Res = true;

				for (uint8_t Idx = 0; Idx < 7; Idx++) {
					if (this->GetData()[Idx] != this->GBAIdent[Idx]) {
						Res = false;
						break;
					}
				}

				this->SavValid = Res;
				if (this->GetValid()) this->SType = SavType::_GBA;
				break;
			}

			/* Nintendo DS. */
			case 0x40000:
			case 0x80000: {
				uint8_t Count = 0, Reg = 0;

				for (uint8_t Slot = 0; Slot < 5; Slot++) { // Check for all 5 possible Slots.
					Count = 0; // Reset Count here.

					for (uint8_t ID = 0; ID < 8; ID++) {
						if (ID == 0x4) {
							for (Reg = 0; Reg < 3; Reg++) {
								if (this->GetData()[(Slot * 0x1000) + ID] == this->NDSIdent[ID] + Reg) {
									Count++;
									break;
								}
							}

						} else {
							if (this->GetData()[(Slot * 0x1000) + ID] == this->NDSIdent[ID]) Count++;
						}
					}

					if (Count == 8) {
						this->SavValid = true;
						this->Region = (Reg == 2 ? NDSSavRegion::Jpn : NDSSavRegion::Int);
						this->SType = SavType::_NDS;
						break;
					}
				}

				/* Fetch all 3 Active Slot Indexes. */
				if (this->GetValid()) {
					for (uint8_t Idx = 0; Idx < 3; Idx++) this->NDSSlots[Idx] = this->InitNDSSlotIdxs(Idx, Reg); // Fetch NDS Slot Locations / Indexes.
				}

				break;
			}

			/* Invalid. */
			default:
				this->SavValid = false;
				this->SType = SavType::_NONE;
				break;
		}
	};


	/*
		This one is called at the SAV's class constructor 3 times (only if the SavType is a NDS one), to get the proper NDS SavSlot offsets / indexes.

		This function has been ported of the LSSD Tool, SuperSaiyajinStackZ created.
	*/
	int8_t SAV::InitNDSSlotIdxs(const uint8_t SavSlot, const uint8_t Reg) {
		if (!this->GetData()) return -1;

		int8_t LastSavedSlot = -1, IDCount = 0;
		uint32_t SavCount[5] = { 0x0 };
		bool SavSlotExist[5] = { false };

		/* Looping through all possible Locations. */
		for (uint8_t Slot = 0; Slot < 5; Slot++) {
			IDCount = 0; // First reset here to 0.

			/* Check for Identifier. */
			for (uint8_t ID = 0; ID < 8; ID++) {
				if (this->GetData()[(Slot * 0x1000) + ID] == this->NDSIdent[ID] + (ID == 0x4 ? Reg : 0x0)) IDCount++;
			}

			/* If 8, then it properly passed the slot existence check. */
			if (IDCount == 8) {
				/* Check, if current slot is also the actual SavSlot. It seems 0xC and 0xD added is the Slot, however 0xD seems never be touched from the game and hence like all the time 0x0? */
				if ((this->GetData()[(Slot * 0x1000) + 0xC] + this->GetData()[(Slot * 0x1000) + 0xD]) == SavSlot) {
					/* Now get the SavCount. */
					SavCount[Slot] = DataHelper::Read<uint32_t>(this->GetData(), (Slot * 0x1000) + 0x8);
					SavSlotExist[Slot] = true;
				}
			}
		}

		/* Here we check and return the proper last Saved Slot. */
		uint32_t HighestCount = 0;

		for (uint8_t Slot = 0; Slot < 5; Slot++) {
			if (SavSlotExist[Slot]) { // Ensure the Slot existed before.
				if (SavCount[Slot] > HighestCount) { // Ensure count is higher.
					HighestCount = SavCount[Slot];
					LastSavedSlot = Slot;
				}
			}
		}

		return LastSavedSlot;
	};


	/*
		Return, wheter a Slot is valid / exist.

		const uint8_t Slot: The Slot to check.
	*/
	bool SAV::SlotExist(const uint8_t Slot) const {
		switch(this->SType) {
			case SavType::_GBA:
				if (Slot < 1 || Slot > 4 || !this->GetValid()) return false;

				for (uint8_t Idx = 0; Idx < 10; Idx++) {
					if (this->GetData()[(Slot * 0x1000) + Idx] != 0) return true;
				}

				return false;

			case SavType::_NDS:
				if (Slot > 2 || !this->GetValid()) return false;

				return this->NDSSlots[Slot] != -1;
				
			case SavType::_NONE:
				return false;
		}

		return false;
	};


	/*
		Return a GBASlot class pointer.

		const uint8_t Slot: The GBASav Slot ( 1 - 4 ).
	*/
	std::unique_ptr<GBASlot> SAV::_GBASlot(const uint8_t Slot) const {
		if (this->SType != SavType::_GBA || !this->SlotExist(Slot)) return nullptr;

		return std::make_unique<GBASlot>(Slot);
	};


	/* Return a GBASettings class pointer. */
	std::unique_ptr<GBASettings> SAV::_GBASettings() const {
		if (this->SType != SavType::_GBA) return nullptr;

		return std::make_unique<GBASettings>();
	};


	/*
		Return a NDSSlot class pointer.

		const uint8_t Slot: The NDSSav Slot ( 0 - 2 ).
	*/
	std::unique_ptr<NDSSlot> SAV::_NDSSlot(const uint8_t Slot) const {
		if (this->SType != SavType::_NDS || !this->SlotExist(Slot)) return nullptr;

		return std::make_unique<NDSSlot>(this->NDSSlots[Slot]);
	};


	/*
		Return a NDSPainting class pointer.

		const uint8_t Idx: The Painting Index ( 0 - 19 ).
	*/
	std::unique_ptr<NDSPainting> SAV::_NDSPainting(const uint8_t Idx) const {
		if (this->SType != SavType::_NDS || Idx >= 20) return nullptr;

		return std::make_unique<NDSPainting>(Idx);
	};


	/*
		Finish call before writting to file.

		Fixes the Checksums on needed things.
	*/
	void SAV::Finish() {
		if (!this->GetValid()) return;

		switch(this->SType) {
			case SavType::_GBA:
				/* Update the Checksum of the Sav Slots. */
				for (uint8_t Slot = 1; Slot < 5; Slot++) {
					if (this->SlotExist(Slot)) this->_GBASlot(Slot)->FixChecksum();
				}

				/* Do the same with the Settings. */
				this->_GBASettings()->UpdateChecksum();
				break;

			case SavType::_NDS:
				/* Update the Checksum of the Sav Slots. */
				for (uint8_t Slot = 0; Slot < 3; Slot++) {
					if (this->SlotExist(Slot)) this->_NDSSlot(Slot)->FixChecksum();
				}

				/* Update the Checksum of the Paintings. */
				for (uint8_t Idx = 0; Idx < 20; Idx++) {
					std::unique_ptr<NDSPainting> PTG = this->_NDSPainting(Idx);

					if (PTG->Valid()) PTG->UpdateChecksum();
				}
				break;

			case SavType::_NONE:
				break;
		}
	};
};