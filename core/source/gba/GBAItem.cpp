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

#include "GBAItem.hpp"
#include "../shared/SavUtils.hpp"


namespace S2Core {
	/* Get and Set the Item Count. */
	uint8_t GBAItem::Count() const { return SavUtils::Read<uint8_t>(this->Offs); };
	void GBAItem::Count(const uint8_t V) { SavUtils::Write<uint8_t>(this->Offs, V); };

	/* Get and Set the Item's ID. */
	uint8_t GBAItem::ID(const uint8_t Index) const { return SavUtils::Read<uint8_t>(this->Offs + 0x1 + (std::min<uint8_t>(5, Index) * 0x3)); };
	void GBAItem::ID(const uint8_t Index, const uint8_t V) {
		SavUtils::Write<uint8_t>(this->Offs + 0x1 + (std::min<uint8_t>(5, Index) * 0x3), V);

		/* Update Item Count. */
		uint8_t Amount = 0;
		for (uint8_t Idx = 0; Idx < 6; Idx++) {
			if (this->ID(Idx) != 0xE6) Amount++; // If not 0xE6 (Empty Item), increase count.
		}

		if (this->Count() != Amount) this->Count(Amount);
	};

	/* Get and Set the Item's Flags. */
	uint8_t GBAItem::Flag(const uint8_t Idx) const { return SavUtils::Read<uint8_t>(this->Offs + 0x2 + (std::min<uint8_t>(5, Idx) * 0x3)); };
	void GBAItem::Flag(const uint8_t Idx, const uint8_t V) { SavUtils::Write<uint8_t>(this->Offs + 0x2 + (std::min<uint8_t>(5, Idx) * 0x3), V); };

	/* Get and Set the Item's Use Count. */
	uint8_t GBAItem::UseCount(const uint8_t Idx) const { return SavUtils::Read<uint8_t>(this->Offs + 0x3 + (std::min<uint8_t>(5, Idx) * 0x3)); };
	void GBAItem::UseCount(const uint8_t Idx, const uint8_t V) { SavUtils::Write<uint8_t>(this->Offs + 0x3 + (std::min<uint8_t>(5, Idx) * 0x3), V); };
};