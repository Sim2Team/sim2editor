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
#include "GBASocialMoveEditor.hpp"
#include "ListSelection.hpp"
#include "Strings.hpp"


/* Go to previous Move. */
void GBASocialMoveEditor::PrevMove() {
	if (this->SelectedMove > 0) this->SelectedMove--;
}

/* Go to next Move. */
void GBASocialMoveEditor::NextMove() {
	if (this->SelectedMove < 14) this->SelectedMove++;
}

/* Select the Move. */
void GBASocialMoveEditor::Select() {
	this->ActiveMove = this->Slot->SocialMove(this->SelectedMove);
	Pointer::OnTop = false;
	this->MoveSelection = false;
	Pointer::SetPos(0, 0);
}

void GBASocialMoveEditor::CancelSelection() {
	Pointer::OnTop = false;
	this->MoveSelection = false;
	Pointer::SetPos(0, 0);
}


/* Draw the Move Selector. */
void GBASocialMoveEditor::DrawMoveSelector(void) const {
	GFX::DrawTop();
	Gui::DrawStringCentered(0, 3, 0.6f, TEXT_COLOR, "Select the Social Move you like to edit.");

	/* Draw Edge boxes. */
	GFX::DrawCornerEdge(true, this->MoveSelector[0].X, this->MoveSelector[0].Y, this->MoveSelector[0].H, true);
	GFX::DrawCornerEdge(false, this->MoveSelector[1].X, this->MoveSelector[1].Y, this->MoveSelector[1].H, true);

	Gui::DrawSprite(GFX::Sprites, sprites_frame1_idx, 195, 45); // Draw first frame of the Pointer above the current Move.

	/* Draw Social Move Images. */
	if (this->SelectedMove == 0) { // First Move, only draw first 2.
		Gui::DrawSprite(GFX::Moves, this->SelectedMove, 150, 82);
		Gui::DrawSprite(GFX::Moves, this->SelectedMove + 1, 265, 82);

	} else if (this->SelectedMove > 0 && this->SelectedMove < 14) { // 1 until 13, draw all 3.
		Gui::DrawSprite(GFX::Moves, this->SelectedMove - 1, 35, 82);
		Gui::DrawSprite(GFX::Moves, this->SelectedMove, 150, 82);
		Gui::DrawSprite(GFX::Moves, this->SelectedMove + 1, 265, 82);

	} else { // 14 -> Draw last 2.
		Gui::DrawSprite(GFX::Moves, this->SelectedMove - 1, 35, 82);
		Gui::DrawSprite(GFX::Moves, this->SelectedMove, 150, 82);
	}

	Gui::Draw_Rect(this->MoveSelector[2].X, this->MoveSelector[2].Y, this->MoveSelector[2].W, this->MoveSelector[2].H, BUTTON_COLOR);
	Gui::DrawStringCentered(0, 202, 0.5f, TEXT_COLOR, S2Core::Strings::GBASocialMoveNames_EN[this->SelectedMove]);
	Pointer::Draw();
}


/* Move Selector Logic. */
void GBASocialMoveEditor::MoveSelectorLogic(u32 hDown, u32 hHeld, touchPosition touch) {
	Pointer::FrameHandle();
	Pointer::ScrollHandle(hHeld);
	uint32_t hRepeat = hidKeysDownRepeat();

	if (hDown & KEY_A) {
		for (auto &Position : this->MoveSelector) {
			if (Pointer::Callback(Position, true)) break;
		}
	}

	if (hDown & KEY_TOUCH) {
		const int Pos[0x2] = { 1, 3 };

		for (uint8_t Idx = 0; Idx < 2; Idx++) {
			if (Touching(this->MoveSelectorBot[Pos[Idx]], touch, true)) break;
		}
	}

	if (hRepeat & KEY_TOUCH) {
		const int Pos[0x2] = { 0, 2 };

		for (uint8_t Idx = 0; Idx < 2; Idx++) {
			if (Touching(this->MoveSelectorBot[Pos[Idx]], touch, true)) break;
		}
	}

	if (hRepeat & KEY_L) this->PrevMove();
	if (hRepeat & KEY_R) this->NextMove();
	if (hDown & KEY_START) this->Select();
	if (hDown & KEY_B) this->CancelSelection();
}


/* Set state to Move Selection. */
void GBASocialMoveEditor::SelectMove() {
	Pointer::OnTop = true;
	this->MoveSelection = true;
	Pointer::SetPos(0, 0);
}


/* Go back to the Slot Editor. */
void GBASocialMoveEditor::Back() {
	Gui::screenBack();
	return;
}


/* Change the Flag of the current Move. */
void GBASocialMoveEditor::ChangeFlag() {
	std::unique_ptr<ListSelection> Overlay = std::make_unique<ListSelection>(this->Flags, "Select a Social Move State.", (uint8_t)this->ActiveMove->Flag());
	this->ActiveMove->Flag((S2Core::SocialMoveFlag)Overlay->Action());
}

/* Change the Flags of all Moves. */
void GBASocialMoveEditor::ChangeMassFlag() {
	std::unique_ptr<ListSelection> Overlay = std::make_unique<ListSelection>(this->Flags, "Select a Social Move State.", (uint8_t)this->ActiveMove->Flag());
	const uint8_t Flag = Overlay->Action();

	for (uint8_t Idx = 0; Idx < 15; Idx++) {
		std::unique_ptr<S2Core::GBASocialMove> Move = this->Slot->SocialMove(Idx);
		Move->Flag((S2Core::SocialMoveFlag)Flag);
	}
}


/* Change the Level of the current Move. */
void GBASocialMoveEditor::ChangeLevel() {
	std::unique_ptr<ListSelection> Overlay = std::make_unique<ListSelection>(this->Levels, "Select a Social Move Level.", this->ActiveMove->Level());
	this->ActiveMove->Level(Overlay->Action());
}

/* Change the Level of all Moves. */
void GBASocialMoveEditor::ChangeMassLevel() {
	std::unique_ptr<ListSelection> Overlay = std::make_unique<ListSelection>(this->Levels, "Select a Social Move Level.", this->ActiveMove->Level());
	const uint8_t Level = Overlay->Action();

	for (uint8_t Idx = 0; Idx < 15; Idx++) {
		std::unique_ptr<S2Core::GBASocialMove> Move = this->Slot->SocialMove(Idx);
		Move->Level(Level);
	}
}


/* Draw Stripes, like on the Settings Screen to make it not look that Empty. */
void GBASocialMoveEditor::DrawStripes() const {
	for (uint8_t Idx = 0; Idx < 4; Idx++) Gui::Draw_Rect(220, 25 + (Idx * 40), 10, 30, BAR_COLOR);
}


/* Main Draw. */
void GBASocialMoveEditor::Draw(void) const {
	if (this->MoveSelection) this->DrawMoveSelector();
	else {
		GFX::DrawTop();
		Gui::DrawStringCentered(0, 3, 0.6f, TEXT_COLOR, "GBA Social Move Editor");
		Gui::DrawSprite(GFX::Moves, this->ActiveMove->Index(), 150, 25 + 57);
		Gui::Draw_Rect(100, 200, 200, 20, BUTTON_COLOR);
		Gui::DrawStringCentered(0, 202, 0.5f, TEXT_COLOR, S2Core::Strings::GBASocialMoveNames_EN[this->ActiveMove->Index()]);
	}

	GFX::DrawBottom();
	this->DrawStripes();

	Gui::DrawString(15, this->Positions[0].Y + 5, 0.4f, TEXT_COLOR, "Social Move Flag: " + this->Flags[std::min<uint8_t>(2, (uint8_t)this->ActiveMove->Flag())]);
	Gui::DrawSprite(GFX::Sprites, sprites_stripe_idx, this->Positions[0].X, this->Positions[0].Y);

	Gui::DrawString(15, this->Positions[1].Y + 5, 0.4f, TEXT_COLOR, "Change Social Move Flag of all Moves");
	Gui::DrawSprite(GFX::Sprites, sprites_stripe_idx, this->Positions[1].X, this->Positions[1].Y);

	Gui::DrawString(15, this->Positions[2].Y + 5, 0.4f, TEXT_COLOR, "Social Move Level: " + this->Levels[std::min<uint8_t>(3, (uint8_t)this->ActiveMove->Level())]);
	Gui::DrawSprite(GFX::Sprites, sprites_stripe_idx, this->Positions[2].X, this->Positions[2].Y);

	Gui::DrawString(15, this->Positions[3].Y + 5, 0.4f, TEXT_COLOR, "Change Social Move Level of all Moves");
	Gui::DrawSprite(GFX::Sprites, sprites_stripe_idx, this->Positions[3].X, this->Positions[3].Y);

	Gui::Draw_Rect(this->Positions[4].X, this->Positions[4].Y, this->Positions[4].W, this->Positions[4].H, KBD_KEYPRESSED); // Cast Select.
	Gui::DrawSprite(GFX::Sprites, sprites_moves_btn_idx, this->Positions[4].X, this->Positions[4].Y);
	Gui::Draw_Rect(this->Positions[5].X, this->Positions[5].Y, this->Positions[5].W, this->Positions[5].H, KBD_KEYPRESSED); // Back.
	Gui::DrawSprite(GFX::Sprites, sprites_back_btn_idx, this->Positions[5].X, this->Positions[5].Y);

	if (!this->MoveSelection) Pointer::Draw(); // Only draw Pointer if not Selector.

	/* Cast Selection for the bottom screen. */
	if (this->MoveSelection) {
		Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(0, 0, 0, 190)); // Dim screen if Selector.

		GFX::DrawCornerEdge(true, this->MoveSelectorBot[0].X, this->MoveSelectorBot[0].Y, this->MoveSelectorBot[0].H, true);
		GFX::DrawCornerEdge(false, this->MoveSelectorBot[2].X, this->MoveSelectorBot[2].Y, this->MoveSelectorBot[2].H, true);

		Gui::Draw_Rect(95, 105, 130, 30, KD_KEYUNPRESSED);
		Gui::Draw_Rect(this->MoveSelectorBot[1].X, this->MoveSelectorBot[1].Y, this->MoveSelectorBot[1].W, this->MoveSelectorBot[1].H, CORNER_COLOR);
		Gui::DrawStringCentered(0, this->MoveSelectorBot[1].Y + 3, 0.5f, TEXT_COLOR, "Select");

		Gui::Draw_Rect(this->MoveSelectorBot[3].X, this->MoveSelectorBot[3].Y, this->MoveSelectorBot[3].W, this->MoveSelectorBot[3].H, KBD_KEYPRESSED); // Back.
		Gui::DrawSprite(GFX::Sprites, sprites_back_btn_idx, this->MoveSelectorBot[3].X, this->MoveSelectorBot[3].Y);
	}
}


/* Main Logic. */
void GBASocialMoveEditor::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (this->MoveSelection) this->MoveSelectorLogic(hDown, hHeld, touch);
	else {
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
}