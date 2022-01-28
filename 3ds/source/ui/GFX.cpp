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

#include "GFX.hpp"
#include "screenCommon.hpp"

C2D_SpriteSheet GFX::Appearance = nullptr, GFX::Casts = nullptr, GFX::Moves = nullptr, GFX::Sprites = nullptr; // All used Spritesheets.


/* Load all Spritesheets. */
void GFX::LoadSheets() {
	Gui::loadSheet("romfs:/gfx/appearance.t3x", GFX::Appearance);
	Gui::loadSheet("romfs:/gfx/cast.t3x", GFX::Casts);
	Gui::loadSheet("romfs:/gfx/social_move.t3x", GFX::Moves);
	Gui::loadSheet("romfs:/gfx/sprites.t3x", GFX::Sprites);
}


/* Unload all Spritesheets. */
void GFX::UnloadSheets() {
	Gui::unloadSheet(GFX::Appearance);
	Gui::unloadSheet(GFX::Casts);
	Gui::unloadSheet(GFX::Moves);
	Gui::unloadSheet(GFX::Sprites);
}


/* Draws the Top Screen base. */
void GFX::DrawTop() {
	Gui::ScreenDraw(Top);
	Gui::Draw_Rect(0, 0, 400, 25, BAR_COLOR);
	Gui::Draw_Rect(0, 25, 400, 215, BG_COLOR);
}


/* Draws the Bottom Screen base. */
void GFX::DrawBottom() {
	Gui::ScreenDraw(Bottom);
	Gui::Draw_Rect(0, 0, 320, 240, BG_COLOR);
}


/*
	Draw the Corner Edges, being used for the Overlays like File Selection.

	const bool LeftSide: If that Corner should be drawn on the Left (true) or Right (false) side.
	const int XPos: The X Start Position where to draw.
	const int YPos: The Y Start Position where to draw (usually 25 with the bar, or 0 without).
	const int YSize: The Y Size of the Corners.
	const bool DrawArrow: If the Arrow should be drawn or not.
*/
void GFX::DrawCornerEdge(const bool LeftSide, const int XPos, const int YPos, const int YSize, const bool DrawArrow) {
	if (LeftSide) {
		Gui::DrawSprite(GFX::Sprites, sprites_corner_idx, XPos, YPos);
		Gui::Draw_Rect(XPos, YPos + 25, 25, YSize - 50, CORNER_COLOR);
		Gui::DrawSprite(GFX::Sprites, sprites_corner_idx, XPos, YPos + YSize - 25, 1.0f, -1.0f);
		if (DrawArrow) Gui::DrawSprite(GFX::Sprites, sprites_arrow_idx, XPos + 5, YPos + ((YSize / 2) - (39 / 2)));

	} else {
		Gui::DrawSprite(GFX::Sprites, sprites_corner_idx, XPos, YPos, -1.0f, 1.0f);
		Gui::Draw_Rect(XPos, YPos + 25, 25, YSize - 50, CORNER_COLOR);
		Gui::DrawSprite(GFX::Sprites, sprites_corner_idx, XPos, YPos + YSize - 25, -1.0f, -1.0f);
		if (DrawArrow)  Gui::DrawSprite(GFX::Sprites, sprites_arrow_idx, XPos, YPos + ((YSize / 2) - (39 / 2)), -1.0f, 1.0f);
	}
}


/*
	Draw the new styled Message Box.

	const int PosX: The X Start Position where to draw the message box.
	const int PosY: The Y Start Position where to draw the message box.
	const int XSize: The X-Size of the Message box (Including the Corners).
	const int YSize: The Y-Size of the Message box (Including the Corners).
*/
void GFX::DrawMsgBox(const int PosX, const int PosY, const int XSize, const int YSize) {
	/* Left Side. */
	Gui::DrawSprite(GFX::Sprites, sprites_corner_idx, PosX, PosY);
	Gui::Draw_Rect(PosX, PosY + 25, 25, YSize - 50, CORNER_COLOR);
	Gui::DrawSprite(GFX::Sprites, sprites_corner_idx, PosX, PosY + YSize - 25, 1.0f, -1.0f);

	/* Right Side. */
	Gui::DrawSprite(GFX::Sprites, sprites_corner_idx, PosX + XSize - 25, PosY, -1.0f, 1.0f);
	Gui::Draw_Rect(PosX + XSize - 25, PosY + 25, 25, YSize - 50, CORNER_COLOR);
	Gui::DrawSprite(GFX::Sprites, sprites_corner_idx, PosX + XSize - 25, PosY + YSize - 25, -1.0f, -1.0f);

	/* Middle. */
	Gui::Draw_Rect(PosX + 25, PosY, XSize - 50, YSize, KD_KEYUNPRESSED);
}


/*
	Draws a Checkbox.

	const int PosX: The X Start Position where to draw the checkbox.
	const int PosY: The Y Start Position where to draw the checkbox.
	const bool Checked: If it's checked or not.
*/
void GFX::DrawCheckbox(const int PosX, const int PosY, const bool Checked) {
	Gui::DrawSprite(GFX::Sprites, sprites_checkbox_idx, PosX, PosY);
	if (Checked) Gui::DrawSprite(GFX::Sprites, sprites_mark_idx, PosX + 4, PosY + 4);
}