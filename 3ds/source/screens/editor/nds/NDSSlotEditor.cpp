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
#include "NDSGeneralEditor.hpp"
#include "NDSSlotEditor.hpp"
#include "SimUtils.hpp"


/* Go to General Editor. */
void NDSSlotEditor::GotoGeneralEditor() { Gui::setScreen(std::make_unique<NDSGeneralEditor>(this->Slot), false, true); }

/* Go back to Editor. */
void NDSSlotEditor::Back() {
	Gui::screenBack();
	return;
}


void NDSSlotEditor::Draw(void) const {
	GFX::DrawTop();
	Gui::DrawStringCentered(0, 3, 0.6f, TEXT_COLOR, "NDS Slot Editor");

	/* Display Info. */
	Gui::DrawStringCentered(0, 50, 0.5f, TEXT_COLOR, "Sim Name: " + this->Slot->Name());
	Gui::DrawStringCentered(0, 80, 0.5f, TEXT_COLOR, "Simoleons: " + S2Core::SimUtils::SimoleonsString(this->Slot->Simoleons()));
	//Gui::DrawStringCentered(0, 110, 0.5f, TEXT_COLOR, "Time: " + S2Core::SimUtils::TimeString(this->Slot->Time(), false));
	GFX::DrawBottom();

	Gui::Draw_Rect(this->Positions[0].X, this->Positions[0].Y, this->Positions[0].W, this->Positions[0].H, KBD_KEYPRESSED); // Cast Icn.
	Gui::DrawSprite(GFX::Sprites, sprites_collectables_btn_idx, this->Positions[0].X, this->Positions[0].Y);

	Gui::Draw_Rect(this->Positions[1].X, this->Positions[1].Y, this->Positions[1].W, this->Positions[1].H, KBD_KEYPRESSED); // Back Icn.
	Gui::DrawSprite(GFX::Sprites, sprites_back_btn_idx, this->Positions[1].X, this->Positions[1].Y);

	Pointer::Draw();
}


void NDSSlotEditor::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	Pointer::FrameHandle();
	Pointer::ScrollHandle(hHeld);

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

	if (hDown & KEY_B) this->Back();
}