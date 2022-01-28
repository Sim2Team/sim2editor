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

#ifndef _SIM2EDITOR_POINTER_HPP
#define _SIM2EDITOR_POINTER_HPP

/* Pointer and Touching Callback Structure. */
struct PointerStr {
	int X;
	int Y;
	int W;
	int H;
	std::function<void()> Func = []() { }; // Optional.
};

namespace Pointer {
	extern int16_t X, Y; // X, Y Positions.
	extern bool OnTop;
	extern uint8_t FrameDL, Frame;

	bool Callback(const PointerStr pos, const bool CallFunc = true);
	void FrameHandle();
	void ScrollHandle(const uint32_t hHeld);
	void Draw(const float Scale = 1);
	void SetPos(const PointerStr pos);
	void SetPos(const int16_t X, const int16_t Y);
}

/* Outside of that, also have the pointer Callback. */
bool Touching(const PointerStr pos, touchPosition touch, const bool CallFunc = true);

#endif