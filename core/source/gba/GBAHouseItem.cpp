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

#include "GBAHouseItem.hpp"
#include "../shared/SavUtils.hpp"


namespace S2Core {
	/* Get and Set the Item Count. */
	uint8_t GBAHouseItem::Count() const { return SavUtils::Read<uint8_t>(this->Offs); };
	void GBAHouseItem::Count(const uint8_t V) { SavUtils::Write<uint8_t>(this->Offs, V); };

	/* Get and Set the Item ID. */
	uint8_t GBAHouseItem::ID(const uint8_t Index) const {
		if (this->Count() == 0) return 0xE6;

		return SavUtils::Read<uint8_t>(this->Offs + 0x1 + (std::min<uint8_t>(this->Count() - 1, Index) * 0x6));
	};
	void GBAHouseItem::ID(const uint8_t Index, const uint8_t V) {
		if (this->Count() == 0) return;

		SavUtils::Write<uint8_t>(this->Offs + 0x1 + (std::min<uint8_t>(this->Count() - 1, Index) * 0x6), V);
	};

	/* Get and Set the Item Flag. */
	uint8_t GBAHouseItem::Flag(const uint8_t Index) const {
		if (this->Count() == 0) return 0x0;

		return SavUtils::Read<uint8_t>(this->Offs + 0x2 + (std::min<uint8_t>(this->Count() - 1, Index) * 0x6));
	};
	void GBAHouseItem::Flag(const uint8_t Index, const uint8_t V) {
		if (this->Count() == 0) return;

		SavUtils::Write<uint8_t>(this->Offs + 0x2 + (std::min<uint8_t>(this->Count() - 1, Index) * 0x6), V);
	};

	/* Get and Set the Use Count(?). */
	uint8_t GBAHouseItem::UseCount(const uint8_t Index) const {
		if (this->Count() == 0) return 0x0;

		return SavUtils::Read<uint8_t>(this->Offs + 0x3 + (std::min<uint8_t>(this->Count() - 1, Index) * 0x6));
	};
	void GBAHouseItem::UseCount(const uint8_t Index, const uint8_t V) {
		if (this->Count() == 0) return;

		SavUtils::Write<uint8_t>(this->Offs + 0x3 + (std::min<uint8_t>(this->Count() - 1, Index) * 0x6), V);
	};

	/* Get and Set the X Position of the Item. */
	uint8_t GBAHouseItem::XPos(const uint8_t Index) const {
		if (this->Count() == 0) return 0x0;

		return SavUtils::Read<uint8_t>(this->Offs + 0x4 + (std::min<uint8_t>(this->Count() - 1, Index) * 0x6));
	};
	void GBAHouseItem::XPos(const uint8_t Index, const uint8_t V) {
		if (this->Count() == 0) return;

		SavUtils::Write<uint8_t>(this->Offs + 0x4 + (std::min<uint8_t>(this->Count() - 1, Index) * 0x6), V);
	};

	/* Get and Set the Y Position of the Item. */
	uint8_t GBAHouseItem::YPos(const uint8_t Index) const {
		if (this->Count() == 0) return 0x0;

		return SavUtils::Read<uint8_t>(this->Offs + 0x5 + (std::min<uint8_t>(this->Count() - 1, Index) * 0x6));
	};
	void GBAHouseItem::YPos(const uint8_t Index, const uint8_t V) {
		if (this->Count() == 0) return;

		SavUtils::Write<uint8_t>(this->Offs + 0x5 + (std::min<uint8_t>(this->Count() - 1, Index) * 0x6), V);
	};

	/* Get and Set the Item Direction. */
	GBAHouseItemDirection GBAHouseItem::Direction(const uint8_t Index) const {
		if (this->Count() == 0) return GBAHouseItemDirection::Invalid;

		const uint8_t D = SavUtils::Read<uint8_t>(this->Offs + 0x6 + (std::min<uint8_t>(this->Count() - 1, Index)) * 0x6);

		switch(D) {
			case 0x1:
				return GBAHouseItemDirection::Right;

			case 0x3:
				return GBAHouseItemDirection::Down;

			case 0x5:
				return GBAHouseItemDirection::Left;

			case 0x7:
				return GBAHouseItemDirection::Up;
		}

		return GBAHouseItemDirection::Invalid;
	};
	void GBAHouseItem::Direction(const uint8_t Index, const GBAHouseItemDirection V) {
		if (this->Count() == 0) return;

		switch(V) {
			case GBAHouseItemDirection::Right:
				SavUtils::Write<uint8_t>(this->Offs + 0x6 + (std::min<uint8_t>(this->Count() - 1, Index)) * 0x6, 0x1);
				break;

			case GBAHouseItemDirection::Down:
				SavUtils::Write<uint8_t>(this->Offs + 0x6 + (std::min<uint8_t>(this->Count() - 1, Index)) * 0x6, 0x3);
				break;

			case GBAHouseItemDirection::Left:
				SavUtils::Write<uint8_t>(this->Offs + 0x6 + (std::min<uint8_t>(this->Count() - 1, Index)) * 0x6, 0x5);
				break;

			case GBAHouseItemDirection::Up:
				SavUtils::Write<uint8_t>(this->Offs + 0x6 + (std::min<uint8_t>(this->Count() - 1, Index)) * 0x6, 0x7);
				break;

			case GBAHouseItemDirection::Invalid:
				break;
		}
	};

	/*
		Add an Item to the House.
		This needs to be handled like this, because things move 0x6 bytes up when an Item is being added.

		NOTE:
			The game seems to handle it the other way than this;
			by doing an insert or something at the 0xD7'th byte, but this way works too.

	*/
	bool GBAHouseItem::AddItem(const uint8_t ID, const uint8_t Flag, const uint8_t UseCount, const uint8_t XPos, const uint8_t YPos, const GBAHouseItemDirection Direction) {
		if (this->Count() == 0xC) return false; // Not allowed to add more than 0xC / 12 Items.

		const uint8_t CT = this->Count();
		this->Count(CT + 0x1);

		std::unique_ptr<uint8_t[]> TMP = std::make_unique<uint8_t[]>(0xF26 - (this->Count() * 6));
		memcpy( // Copy first to a TMP pointer.
			TMP.get(),
			SavUtils::Sav->GetData() + (this->Offs + 0x1) + (CT * 0x6),
			0xF26 - (this->Count() * 6)
		);

		memcpy( // Then copy to the actual location from the TMP pointer.
			SavUtils::Sav->GetData() + (this->Offs + 0x1) + (this->Count() * 0x6),
			TMP.get(),
			0xF26 - (this->Count() * 6)
		);

		/* Set Item Data. */
		this->ID(CT, ID);
		this->Flag(CT, Flag);
		this->UseCount(CT, UseCount);
		this->XPos(CT, XPos);
		this->YPos(CT, YPos);
		this->Direction(CT, Direction);

		return true;
	};

	/*
		Remove an Item from the House.
		This needs to be handled like this, because things move 0x6 bytes down when an Item is being removed.
	*/
	bool GBAHouseItem::RemoveItem(const uint8_t Index) {
		if ((this->Count() == 0) || (this->Count() - 1 < Index)) return false; // Nanana, Index and or Count is not good.

		this->Count(this->Count() - 0x1);

		std::unique_ptr<uint8_t[]> TMP = std::make_unique<uint8_t[]>(0xF26 - (this->Count() * 6));
		memcpy( // Copy first to a TMP pointer.
			TMP.get(),
			SavUtils::Sav->GetData() + (this->Offs + 0x1) + ((Index + 0x1) * 0x6),
			0xF26 - (this->Count() * 6)
		);

		memcpy( // Then copy to the actual location from the TMP pointer.
			SavUtils::Sav->GetData() + (this->Offs + 0x1) + (Index * 0x6),
			TMP.get(),
			0xF26 - (this->Count() * 6)
		);

		return true;
	};
};