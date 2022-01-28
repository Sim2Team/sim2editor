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
#include "Editor.hpp"
#include "MainMenu.hpp"
#include "Settings.hpp"

extern bool exiting;


void MainMenu::Draw(void) const {
	GFX::DrawTop();
	Gui::DrawStringCentered(0, 3, 0.6f, TEXT_COLOR, "Sim2Editor");
	GFX::DrawBottom();

	for (uint8_t i = 0; i < (int)this->Positions.size(); i++) {
		Gui::Draw_Rect(this->Positions[i].X, this->Positions[i].Y, this->Positions[i].W, this->Positions[i].H, KBD_KEYPRESSED);

		Gui::DrawStringCentered(0, this->Positions[i].Y + 8, 0.6f, TEXT_COLOR, this->ButtonNames[i], 130);
	}

	Pointer::Draw();
}


void MainMenu::GotoEditor() { Gui::setScreen(std::make_unique<Editor>(), false, true); }
void MainMenu::GotoSettings() { Gui::setScreen(std::make_unique<Settings>(), false, true); }


void MainMenu::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	Pointer::FrameHandle();
	Pointer::ScrollHandle(hHeld); // Pointer Handling.

	if (hDown & KEY_A) {
		for (auto &Position : this->Positions) {
			if (Pointer::Callback(Position, true)) break;
		}
	}

	if (hDown & KEY_TOUCH) {
		for (auto &Position : this->Positions) {
			if (Touching(Position, touch, true)) break;
		}
	}

	if (hDown & KEY_START) exiting = true;
}