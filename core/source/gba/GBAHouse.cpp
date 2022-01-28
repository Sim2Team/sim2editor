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

#include "GBAHouse.hpp"
#include "../shared/SavUtils.hpp"


namespace S2Core {
	/*
		Get and Set the Room Design.
		Only 0 - 3 SHOULD be used at all, the others aren't actual room designs and instead may cause issues.
	*/
	uint8_t GBAHouse::Roomdesign() const { return SavUtils::ReadBits(this->Offs + 0x2E, true); };
	void GBAHouse::Roomdesign(const uint8_t V) { SavUtils::WriteBits(this->Offs + 0x2E, true, V); };

	/* Get the Items of your House / Room. */
	std::unique_ptr<GBAHouseItem> GBAHouse::Items() const { return std::make_unique<GBAHouseItem>(this->Offs + 0xD6); };
};