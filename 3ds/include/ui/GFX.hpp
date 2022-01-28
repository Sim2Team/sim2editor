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

#ifndef _SIM2EDITOR_GFX_HPP
#define _SIM2EDITOR_GFX_HPP

#include "screenCommon.hpp"
#include "sprites.h"
#include <vector>

#define BAR_COLOR C2D_Color32(44, 48, 64, 255)
#define BG_COLOR C2D_Color32(52, 56, 64, 255)
#define TEXT_COLOR C2D_Color32(216, 228, 228, 255)
#define BUTTON_COLOR C2D_Color32(80, 112, 128, 255)
#define KBD_KEYPRESSED C2D_Color32(60, 63, 113, 255)
#define KD_KEYUNPRESSED C2D_Color32(42, 46, 54, 255)
#define CORNER_COLOR C2D_Color32(52, 60, 76, 255)

namespace GFX {
	extern C2D_SpriteSheet Appearance, Casts, Moves, Sprites;

	void LoadSheets();
	void UnloadSheets();

	void DrawTop();
	void DrawBottom();

	void DrawCornerEdge(const bool LeftSide, const int XPos, const int YPos, const int YSize, const bool DrawArrow = true);
	void DrawMsgBox(const int PosX, const int PosY, const int XSize, const int YSize);
	void DrawCheckbox(const int PosX, const int PosY, const bool Checked);
};

#endif