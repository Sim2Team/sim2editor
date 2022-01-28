/*
*   This file is part of Sim2Editor
*   Copyright (C) 2020-2022 Universal-Team, Sim2Team
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

#ifndef _SIM2EDITOR_GBA_SLOT_SELECTION_HPP
#define _SIM2EDITOR_GBA_SLOT_SELECTION_HPP

#include "Pointer.hpp"
#include <string>
#include <vector>

class GBASlotSelection {
public:
	GBASlotSelection() { }
	int8_t Action() const;
private:
	struct GBASlotInformation {
		uint8_t Slot = 1;
		bool Gender = true;
		std::string SimoleonString = "0$";
		std::string RatingString = "0";
		std::string SimName = "";
		std::string Episode = "It All Began";
		std::string TimeString = "00:00";
	};

	mutable int8_t Res = 1;
	mutable bool Done = false;
	mutable GBASlotInformation Info;

	void PrevSlot() const;
	void NextSlot() const;
	void OK() const;
	void FetchSlot() const;
	void Cancel() const;

	const std::vector<PointerStr> Positions = {
		{ 40, 60, 25, 145, [this]() { this->PrevSlot(); } }, // Prev.
		{ 166, 172, 73, 21, [this]() { this->OK(); } }, // OK.
		{ 335, 60, 25, 145, [this]() { this->NextSlot(); } }, // Next.
		{ 97, 37, 206, 17 } // Top Box, also NO action there.
	};

	/* Same as above, but on the bottom for touch compatibility! */
	const std::vector<PointerStr> BottomPos = {
		{ 70, 75, 25, 90, [this]() { this->PrevSlot(); } },
		{ 123, 109, 74, 22, [this]() { this->OK(); } },
		{ 225, 75, 25, 90, [this]() { this->NextSlot(); } },
		{ 0, 223, 17, 17, [this]() { this->Cancel(); } }
	};
};

#endif