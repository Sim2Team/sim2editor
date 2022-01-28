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

#include "Common.hpp"
#include "GFX.hpp"
#include "Pointer.hpp"

#define PTR_X_SIZE 16
#define PTR_Y_SIZE 24
#define PTR_DL 5
#define PTR_FRAMES 15

#define X_DIST 7
#define Y_DIST 19
#define PTR_SPEED 4

int16_t Pointer::X = 0, Pointer::Y = 0; // Declare.
uint8_t Pointer::FrameDL = PTR_DL, Pointer::Frame = 0;
bool Pointer::OnTop = false;


/*
	Pointer Callback to a PointerStr Pos.

	const Pointer Pos: The Button position which to check a callback.
	const bool CallFunc: If function should be called or not.

	Returns true, if touches a button.
*/
bool Pointer::Callback(const PointerStr Pos, const bool CallFunc) {
	if (((Pointer::X + X_DIST) >= Pos.X && (Pointer::X + X_DIST) <= Pos.X + Pos.W)
		&& ((Pointer::Y + Y_DIST) >= Pos.Y && (Pointer::Y + Y_DIST) <= Pos.Y + Pos.H)) {
			if (CallFunc) Pos.Func();
			return true;
	}

	return false;
}


/*
	Handle the Frame Delay of the Pointer.
*/
void Pointer::FrameHandle() {
	if (Pointer::FrameDL > 0) {
		Pointer::FrameDL--;

		if (Pointer::FrameDL == 0) {
			if (Pointer::Frame < (PTR_FRAMES - 1)) Pointer::Frame++;
			else Pointer::Frame = 0;

			Pointer::FrameDL = PTR_DL;
		}
	}
}


/*
	Handle Scrolling of the Pointer.

	const uint32_t hHeld: The hidKeysHeld() variable.
*/
void Pointer::ScrollHandle(const uint32_t hHeld) {
	if (hHeld & KEY_LEFT) {
		if (Pointer::X >= 0) {
			Pointer::X -= CFG->PointerSpeed();
			if (Pointer::X < 0) Pointer::X = 0; // Make it not go below the limit.
		}
	}

	if (hHeld & KEY_RIGHT) {
		if (Pointer::X <= ((Pointer::OnTop ? 400 : 320) - PTR_X_SIZE)) {
			Pointer::X += CFG->PointerSpeed();
			if (Pointer::X > (Pointer::OnTop ? 400 : 320) - PTR_X_SIZE) Pointer::X = (Pointer::OnTop ? 400 : 320) - PTR_X_SIZE; // Make it not go over the limit.
		}
	}

	if (hHeld & KEY_UP) {
		if (Pointer::Y >= -20) {
			Pointer::Y -= CFG->PointerSpeed();
			if (Pointer::Y < -20) Pointer::Y = -20; // Make it not go below the limit.
		}
	}

	if (hHeld & KEY_DOWN) {
		if (Pointer::Y <= (240 - PTR_Y_SIZE)) {
			Pointer::Y += CFG->PointerSpeed();
			if (Pointer::Y > (240 - PTR_Y_SIZE)) Pointer::Y = (240 - PTR_Y_SIZE); // Make it not go over the limit.
		}
	}
}


/*
	Draw the Pointer, also with Position.

	const float Scale: Optional Pointer Scale.
*/
void Pointer::Draw(const float Scale) {
	Gui::DrawSprite(GFX::Sprites, Pointer::Frame, Pointer::X, Pointer::Y, ((Scale == 1) ? 1 : Scale), ((Scale == 1) ? 1 : Scale));
}


/*
	Set Pointer Position from two int16_t's, or the Pointer Struct.
*/
void Pointer::SetPos(const PointerStr Pos) { Pointer::X = Pos.X; Pointer::Y = Pos.Y; }
void Pointer::SetPos(const int16_t X, const int16_t Y) { Pointer::X = X; Pointer::Y = Y; }


/*
	Touch Callback.

	const Structs::ButtonPos pos: The Button Position.
	touchPosition touch: The touchPosition variable.
	const bool CallFunc: If function should be called or not.
*/
bool Touching(const PointerStr Pos, touchPosition touch, const bool CallFunc) {
	if (touch.px >= Pos.X && touch.px <= (Pos.X + Pos.W) && touch.py >= Pos.Y && touch.py <= (Pos.Y + Pos.H)) {
		if (CallFunc) Pos.Func();
		return true;
	}

	return false;
}