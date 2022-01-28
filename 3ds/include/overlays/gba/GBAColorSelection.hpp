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

#ifndef _SIM2EDITOR_GBA_COLOR_SELECTION_HPP
#define _SIM2EDITOR_GBA_COLOR_SELECTION_HPP

#include "Pointer.hpp"
#include <citro2d.h>
#include <string>
#include <vector>

class GBAColorSelection {
public:
	GBAColorSelection(const std::string &Text, const bool Mode = false, const uint8_t Selection = 0);
	int8_t Action() const;

	/* The 16 Color selection, used for Shoe, Hat and Hair color. */
	static constexpr uint32_t _16Color[16] = {
		C2D_Color32(204, 196, 144, 255), C2D_Color32(172, 132, 92, 255), C2D_Color32(140, 92, 72, 255),
		C2D_Color32(184, 104, 80, 255), C2D_Color32(104, 68, 56, 255), C2D_Color32(104, 52, 52, 255),
		C2D_Color32(60, 48, 44, 255), C2D_Color32(48, 48, 44, 255), C2D_Color32(216, 228, 228, 255),
		C2D_Color32(184, 80, 80, 255), C2D_Color32(180, 92, 128, 255), C2D_Color32(160, 128, 192, 255),
		C2D_Color32(60, 132, 196, 255), C2D_Color32(80, 152, 172, 255), C2D_Color32(84, 136, 88, 255),
		C2D_Color32(152, 192, 116, 255)
	};

	/* The 32 Color selection, used for Shirt, Pants color. */
	static constexpr uint32_t _32Color[32] = {
		C2D_Color32(116, 56, 56, 255), C2D_Color32(112, 60, 60, 255), C2D_Color32(104, 60, 56, 255),
		C2D_Color32(124, 76, 64, 255), C2D_Color32(128, 76, 64, 255), C2D_Color32(112, 92, 68, 255),
		C2D_Color32(116, 112, 76, 255), C2D_Color32(100, 120, 80, 255), C2D_Color32(76, 116, 80, 255),
		C2D_Color32(60, 84, 64, 255), C2D_Color32(76, 128, 116, 255), C2D_Color32(80, 132, 140, 255),
		C2D_Color32(96, 140, 144, 255), C2D_Color32(64, 104, 128, 255), C2D_Color32(48, 76, 104, 255),
		C2D_Color32(72, 84, 96, 255), C2D_Color32(60, 64, 80, 255), C2D_Color32(92, 92, 124, 255),
		C2D_Color32(100, 104, 160, 255), C2D_Color32(96, 84, 128, 255), C2D_Color32(104, 84, 124, 255),
		C2D_Color32(124, 76, 104, 255), C2D_Color32(168, 176, 176, 255), C2D_Color32(192, 104, 96, 255),
		C2D_Color32(180, 172, 116, 255), C2D_Color32(216, 212, 168, 255), C2D_Color32(180, 188, 188, 255),
		C2D_Color32(136, 116, 92, 255), C2D_Color32(80, 60, 52, 255), C2D_Color32(132, 136, 136, 255),
		C2D_Color32(68, 68, 68, 255), C2D_Color32(44, 48, 48, 255)
	};
private:
	mutable std::string Text = "";
	mutable bool Done = false, Mode = false;
	mutable uint8_t Selected = 0;

	void PrevColor() const;
	void NextColor() const;
	void Select() const;
	void Cancel() const;

	const std::vector<PointerStr> Positions = {
		{ 0, 25, 25, 215, [this]() { this->PrevColor(); } },
		{ 375, 25, 25, 215, [this]() { this->NextColor(); } },
		{ 100, 200, 200, 20, [this]() { this->Select(); } }
	};

	/* Same as above, but on the bottom for touch compatibility! */
	const std::vector<PointerStr> BottomPos = {
		{ 70, 75, 25, 90, [this]() { this->PrevColor(); } },
		{ 123, 109, 74, 22, [this]() { this->Select(); } },
		{ 225, 75, 25, 90, [this]() { this->NextColor(); } },
		{ 0, 223, 17, 17, [this]() { this->Cancel(); } }
	};
};

#endif