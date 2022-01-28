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

#include "NDSSlot.hpp"
#include "../shared/Checksum.hpp"
#include "../shared/SavUtils.hpp"


namespace S2Core {
	/* Get and Set Simoleons. */
	uint32_t NDSSlot::Simoleons() const { return SavUtils::Read<uint32_t>(this->Offs + 0x2C); };
	void NDSSlot::Simoleons(uint32_t V) { SavUtils::Write<uint32_t>(this->Offs + 0x2C, (std::min<uint32_t>(999999, V))); };

	/* Get and Set Name. */
	std::string NDSSlot::Name() const { return SavUtils::ReadString(this->Offs + 0x30, 7); };
	void NDSSlot::Name(const std::string &V) { SavUtils::WriteString(this->Offs + 0x30, 7, V); };

	/* Get and Set Nuclear Fuelrods. */
	uint8_t NDSSlot::Fuelrods() const { return SavUtils::Read<uint8_t>(this->Offs + 0xBC); };
	void NDSSlot::Fuelrods(const uint8_t V) { SavUtils::Write<uint8_t>(this->Offs + 0xBC, (std::min<uint8_t>(250, V))); };

	/* Get and Set License Plates. */
	uint8_t NDSSlot::Plates() const { return SavUtils::Read<uint8_t>(this->Offs + 0xBD); };
	void NDSSlot::Plates(const uint8_t V) { SavUtils::Write<uint8_t>(this->Offs + 0xBD, (std::min<uint8_t>(250, V))); };

	/* Get and Set Strange Gourds. */
	uint8_t NDSSlot::Gourds() const { return SavUtils::Read<uint8_t>(this->Offs + 0xBE); };
	void NDSSlot::Gourds(const uint8_t V) { SavUtils::Write<uint8_t>(this->Offs + 0xBE, (std::min<uint8_t>(250, V))); };

	/* Get and Set Alien Spaceship Parts. */
	uint8_t NDSSlot::Spaceship() const { return SavUtils::Read<uint8_t>(this->Offs + 0xBF); };
	void NDSSlot::Spaceship(const uint8_t V) { SavUtils::Write<uint8_t>(this->Offs + 0xBF, (std::min<uint8_t>(250, V))); };

	/* Get and Set Creativity Skill Points. */
	uint8_t NDSSlot::Creativity() const { return SavUtils::Read<uint8_t>(this->Offs + 0xDF); };
	void NDSSlot::Creativity(const uint8_t V) { SavUtils::Write<uint8_t>(this->Offs + 0xDF, (std::min<uint8_t>(10, V))); };

	/* Get and Set Business Skill Points. */
	uint8_t NDSSlot::Business() const { return SavUtils::Read<uint8_t>(this->Offs + 0xE0); };
	void NDSSlot::Business(const uint8_t V) { SavUtils::Write<uint8_t>(this->Offs + 0xE0, (std::min<uint8_t>(10, V))); };

	/* Get and Set Body Skill Points. */
	uint8_t NDSSlot::Body() const { return SavUtils::Read<uint8_t>(this->Offs + 0xE1); };
	void NDSSlot::Body(const uint8_t V) { SavUtils::Write<uint8_t>(this->Offs + 0xE1, (std::min<uint8_t>(10, V))); };

	/* Get and Set Charisma Skill Points. */
	uint8_t NDSSlot::Charisma() const { return SavUtils::Read<uint8_t>(this->Offs + 0xE2); };
	void NDSSlot::Charisma(const uint8_t V) { SavUtils::Write<uint8_t>(this->Offs + 0xE2, (std::min<uint8_t>(10, V))); };

	/* Get and Set Mechanical Skill Points. */
	uint8_t NDSSlot::Mechanical() const { return SavUtils::Read<uint8_t>(this->Offs + 0xE3); };
	void NDSSlot::Mechanical(const uint8_t V) { SavUtils::Write<uint8_t>(this->Offs + 0xE3, (std::min<uint8_t>(10, V))); };

	/* Get and Set the Pocket Item Count. */
	uint8_t NDSSlot::PocketCount() const { return SavUtils::Read<uint8_t>(this->Offs + 0xCF); };
	void NDSSlot::PocketCount(const uint8_t V) { SavUtils::Write<uint8_t>(this->Offs + 0xCF, std::min<uint8_t>(6, V)); };

	/* Get and Set the Pocket Item IDs. */
	uint16_t NDSSlot::PocketID(const uint8_t Index) const { return SavUtils::Read<uint16_t>(this->Offs + 0xC3 + (std::min<uint8_t>(6, Index) * 2)); };
	void NDSSlot::PocketID(const uint8_t Index, const uint16_t V) {
		SavUtils::Write<uint8_t>(this->Offs + 0xC3 + (std::min<uint8_t>(6, Index) * 2), V);

		uint8_t Count = 0;
		for (uint8_t Idx = 0; Idx < 6; Idx++) {
			if (this->PocketID(Idx) != 0x0) Count++; // Is that the proper way? TODO: More research for actual empty IDs.
		}

		this->PocketCount(Count);
	};

	/*
		Fix the Checksum of the current Slot, if invalid.

		Returns false if already valid, true if got fixed.
	*/
	bool NDSSlot::FixChecksum() {
		const uint16_t CurCHKS = SavUtils::Read<uint16_t>(this->Offs + 0x28);
		const std::vector<uint32_t> Offs = { (this->Offs + 0x12) / 2, (this->Offs + 0x28) / 2 };
		const uint16_t Calced = Checksum::Calc(SavUtils::Sav->GetData(), (this->Offs + 0x10) / 2, (this->Offs + 0x1000) / 2, Offs);

		/* If the calced result is NOT the current checksum. */
		if (Calced != CurCHKS) {
			SavUtils::Write<uint16_t>(this->Offs + 0x28, Calced);
			return true;
		}

		return false;
	};
};