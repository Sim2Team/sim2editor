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
#include "GBAItemEditor.hpp"
#include "ListSelection.hpp"
#include "Strings.hpp"


/* Go back. */
void GBAItemEditor::Back() {
	Gui::screenBack();
	return;
}


void GBAItemEditor::Draw(void) const {
	GFX::DrawTop();
	Gui::DrawStringCentered(0, 3, 0.6f, TEXT_COLOR, "GBA Item Editor");

	GFX::DrawBottom();

	/* Draw Tabs. */
	Gui::Draw_Rect(0, 0, 64, 20, (this->Tab == Tabs::Pawnshop ? KBD_KEYPRESSED : KD_KEYUNPRESSED));
	Gui::Draw_Rect(64, 0, 64, 20, (this->Tab == Tabs::Saloon ? KBD_KEYPRESSED : KD_KEYUNPRESSED));
	Gui::Draw_Rect(128, 0, 64, 20, (this->Tab == Tabs::Skills ? KBD_KEYPRESSED : KD_KEYUNPRESSED));
	Gui::Draw_Rect(192, 0, 64, 20, (this->Tab == Tabs::Mailbox ? KBD_KEYPRESSED : KD_KEYUNPRESSED));
	Gui::Draw_Rect(256, 0, 64, 20, (this->Tab == Tabs::Inventory ? KBD_KEYPRESSED : KD_KEYUNPRESSED));

	Gui::DrawString(0 + 1, 3, 0.45f, TEXT_COLOR, "Pawn Shop");
	Gui::DrawString(64 + 13, 3, 0.45f, TEXT_COLOR, "Saloon");
	Gui::DrawString(128 + 18, 3, 0.45f, TEXT_COLOR, "Skills");
	Gui::DrawString(192 + 10, 3, 0.45f, TEXT_COLOR, "Mailbox");
	Gui::DrawString(256 + 6, 3, 0.45f, TEXT_COLOR, "Inventory");

	for (uint8_t Idx = 0; Idx < 6; Idx++) {
		Gui::DrawSprite(GFX::Sprites, sprites_stripe_idx, 250, this->Positions[5 + Idx].Y); // Draw Option Stripes.
		Gui::DrawString(30, 34 + (Idx * 36), 0.5f, TEXT_COLOR, S2Core::Strings::GBAItemNames_EN[this->ActiveItemGroup->ID(Idx)], 200);
	}

	Gui::Draw_Rect(this->Positions[11].X, this->Positions[11].Y, this->Positions[11].W, this->Positions[11].H, KBD_KEYPRESSED); // Back Icn.
	Gui::DrawSprite(GFX::Sprites, sprites_back_btn_idx, this->Positions[11].X, this->Positions[11].Y);
	Pointer::Draw();
}


/*
	Select an Item from the List and set it, if changed.

	const uint8_t Slot: The Item Slot to edit.
*/
void GBAItemEditor::SelectItem(const uint8_t Slot) {
	std::unique_ptr<ListSelection> Ovl = std::make_unique<ListSelection>(S2Core::Strings::GBAItemNames_EN, "Select an Item.", this->ActiveItemGroup->ID(Slot));
	const uint8_t ID = Ovl->Action();

	if (ID != this->ActiveItemGroup->ID(Slot)) this->ActiveItemGroup->ID(Slot, ID);
}


/*
	Switch Tabs and initialize it to the ActiveItemGroup.

	const Tabs T: The Tab which to switch to.
*/
void GBAItemEditor::SwitchTab(const Tabs T) {
	this->Tab = T;

	switch(this->Tab) {
		case Tabs::Pawnshop:
			this->ActiveItemGroup = this->Slot->PawnShop();
			break;

		case Tabs::Saloon:
			this->ActiveItemGroup = this->Slot->Saloon();
			break;

		case Tabs::Skills:
			this->ActiveItemGroup = this->Slot->Skills();
			break;

		case Tabs::Mailbox:
			this->ActiveItemGroup = this->Slot->Mailbox();
			break;

		case Tabs::Inventory:
			this->ActiveItemGroup = this->Slot->Inventory();
			break;
	}
}


void GBAItemEditor::Logic(uint32_t hDown, uint32_t hHeld, touchPosition touch) {
	Pointer::FrameHandle();
	Pointer::ScrollHandle(hHeld);
	uint32_t hRepeat = hidKeysDownRepeat();

	if (hDown & KEY_A) {
		for (auto &Pos : this->Positions) {
			if (Pointer::Callback(Pos, true)) {
				break;
			}
		}
	}

	if (hDown & KEY_TOUCH) {
		for (auto &Pos : this->Positions) {
			if (Touching(Pos, touch, true)) {
				break;
			}
		}
	}

	if (hDown & KEY_B) this->Back();

	if (hRepeat & KEY_L) {
		if (this->Tab != Tabs::Pawnshop) this->SwitchTab((Tabs)((uint8_t)this->Tab - 0x1));
	}

	if (hRepeat & KEY_R) {
		if (this->Tab != Tabs::Inventory) this->SwitchTab((Tabs)((uint8_t)this->Tab + 0x1));
	}
}