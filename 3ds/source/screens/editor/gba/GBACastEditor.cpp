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
#include "GBACastEditor.hpp"
#include "ListSelection.hpp"
#include "Strings.hpp"


/* Cast Selector. */
void GBACastEditor::NextCast() { // Goes one cast to the right.
	if (this->SelectedCast < 25) this->SelectedCast++;
}

void GBACastEditor::PrevCast() { // Goes one cast to the left.
	if (this->SelectedCast > 0) this->SelectedCast--;
}

void GBACastEditor::Select() { // Select the current Cast.
	this->ActiveCast = this->Slot->Cast(this->SelectedCast);
	Pointer::OnTop = false;
	this->CastSelection = false;
	Pointer::SetPos(0, 0);
}

void GBACastEditor::CancelSelection() {
	Pointer::OnTop = false;
	this->CastSelection = false;
	Pointer::SetPos(0, 0);
}


/* Cast Selector Draw. */
void GBACastEditor::DrawCastSelector(void) const {
	GFX::DrawTop();
	Gui::DrawStringCentered(0, 3, 0.6f, TEXT_COLOR, "Select the Cast you like to edit.");

	/* Draw Edge boxes. */
	GFX::DrawCornerEdge(true, this->CastSelector[0].X, this->CastSelector[0].Y, this->CastSelector[0].H, true);
	GFX::DrawCornerEdge(false, this->CastSelector[1].X, this->CastSelector[1].Y, this->CastSelector[1].H, true);

	Gui::DrawSprite(GFX::Sprites, sprites_frame1_idx, 195, 45); // Draw first frame of the Pointer above the current Cast.

	/* Draw Cast Images. */
	if (this->SelectedCast == 0) { // First Cast, only draw first 2.
		Gui::DrawSprite(GFX::Casts, this->SelectedCast, 150, 82);
		Gui::DrawSprite(GFX::Casts, this->SelectedCast + 1, 265, 82);

	} else if (this->SelectedCast > 0 && this->SelectedCast < 25) { // 1 until 24, draw all 3.
		Gui::DrawSprite(GFX::Casts, this->SelectedCast - 1, 35, 82);
		Gui::DrawSprite(GFX::Casts, this->SelectedCast, 150, 82);
		Gui::DrawSprite(GFX::Casts, this->SelectedCast + 1, 265, 82);

	} else { // 25 -> Draw last 2.
		Gui::DrawSprite(GFX::Casts, this->SelectedCast - 1, 35, 82);
		Gui::DrawSprite(GFX::Casts, this->SelectedCast, 150, 82);
	}

	Gui::Draw_Rect(this->CastSelector[2].X, this->CastSelector[2].Y, this->CastSelector[2].W, this->CastSelector[2].H, BUTTON_COLOR);
	Gui::DrawStringCentered(0, 202, 0.5f, TEXT_COLOR, S2Core::Strings::GBACastNames_EN[this->SelectedCast]);
	Pointer::Draw();
}


/* Cast Selector Logic. */
void GBACastEditor::CastSelectorLogic(u32 hDown, u32 hHeld, touchPosition touch) {
	Pointer::FrameHandle();
	Pointer::ScrollHandle(hHeld);
	uint32_t hRepeat = hidKeysDownRepeat();

	if (hDown & KEY_A) {
		for (auto &Position : this->CastSelector) {
			if (Pointer::Callback(Position, true)) break;
		}
	}

	if (hDown & KEY_TOUCH) {
		const int Pos[0x2] = { 1, 3 };

		for (uint8_t Idx = 0; Idx < 2; Idx++) {
			if (Touching(this->CastSelectorBot[Pos[Idx]], touch, true)) break;
		}
	}

	if (hRepeat & KEY_TOUCH) {
		const int Pos[0x2] = { 0, 2 };

		for (uint8_t Idx = 0; Idx < 2; Idx++) {
			if (Touching(this->CastSelectorBot[Pos[Idx]], touch, true)) break;
		}
	}

	if (hRepeat & KEY_L) this->PrevCast();
	if (hRepeat & KEY_R) this->NextCast();
	if (hDown & KEY_START) this->Select();
	if (hDown & KEY_B) this->CancelSelection();
}


/* MAIN Tab. */
void GBACastEditor::ChangeFriendly() { // Changes the Friendly Conversation Level.
	if (this->ActiveCast->Friendly() < 3) this->ActiveCast->Friendly(this->ActiveCast->Friendly() + 1);
	else this->ActiveCast->Friendly(0);
}

void GBACastEditor::ChangeRomance() { // Changes the Romance Conversation Level.
	if (this->ActiveCast->Romance() < 3) this->ActiveCast->Romance(this->ActiveCast->Romance() + 1);
	else this->ActiveCast->Romance(0);
}

void GBACastEditor::ChangeIntimidate() { // Changes the Intimidate Conversation Level.
	if (this->ActiveCast->Intimidate() < 3) this->ActiveCast->Intimidate(this->ActiveCast->Intimidate() + 1);
	else this->ActiveCast->Intimidate(0);
}


/* Set the Feeling. */
void GBACastEditor::SetFeeling() {
	std::unique_ptr<ListSelection> Ovl = std::make_unique<ListSelection>(this->Feelings, "Select the feeling of the Cast Member.", (uint8_t)this->ActiveCast->Feeling());
	const S2Core::GBACastFeeling Feeling = (S2Core::GBACastFeeling)Ovl->Action();

	if (Feeling != this->ActiveCast->Feeling()) this->ActiveCast->Feeling(Feeling);
}

/* Toggle Secret. */
void GBACastEditor::ToggleSecret() { this->ActiveCast->Secret(!this->ActiveCast->Secret()); };


/* Miscellaneous Tab. */
void GBACastEditor::MinConversation() { // Clear Conversations.
	for (uint8_t Idx = 0; Idx < 26; Idx++) {
		std::unique_ptr<S2Core::GBACast> Cst = this->Slot->Cast(Idx);

		Cst->Friendly(0); Cst->Romance(0); Cst->Intimidate(0);
	}
}

void GBACastEditor::MaxConversation() { // Max out Conversations.
	for (uint8_t Idx = 0; Idx < 26; Idx++) {
		std::unique_ptr<S2Core::GBACast> Cst = this->Slot->Cast(Idx);

		Cst->Friendly(3); Cst->Romance(3); Cst->Intimidate(3);
	}
}

void GBACastEditor::SecretUnlocks() { // Unlock all Secrets.
	for (uint8_t Idx = 0; Idx < 26; Idx++) {
		std::unique_ptr<S2Core::GBACast> Cst = this->Slot->Cast(Idx);

		Cst->Secret(true);
	}
}

void GBACastEditor::MassFeelingChange() { // Set the feeling for all casts.
	std::unique_ptr<ListSelection> Ovl = std::make_unique<ListSelection>(this->Feelings, "Select the feeling of the Cast Member.", (uint8_t)this->ActiveCast->Feeling());
	const S2Core::GBACastFeeling Feeling = (S2Core::GBACastFeeling)Ovl->Action();

	for (uint8_t Idx = 0; Idx < 26; Idx++) {
		std::unique_ptr<S2Core::GBACast> Cst = this->Slot->Cast(Idx);

		Cst->Feeling(Feeling);
	}
}


/* Sets the Cast Selector. */
void GBACastEditor::SelectCast() {
	Pointer::OnTop = true;
	this->CastSelection = true;
	Pointer::SetPos(0, 0);
}


/* Goes screen back. */
void GBACastEditor::Back() {
	Gui::screenBack();
	return;
}


/* Main Draw. */
void GBACastEditor::Draw(void) const {
	if (this->CastSelection) this->DrawCastSelector();
	else {
		GFX::DrawTop();
		Gui::DrawStringCentered(0, 3, 0.6f, TEXT_COLOR, "GBA Cast Editor");
		Gui::DrawSprite(GFX::Casts, this->ActiveCast->Index(), 150, 25 + 57);
		Gui::Draw_Rect(100, 200, 200, 20, BUTTON_COLOR);
		Gui::DrawStringCentered(0, 202, 0.5f, TEXT_COLOR, S2Core::Strings::GBACastNames_EN[this->ActiveCast->Index()]);
	}

	GFX::DrawBottom();

	/* Draw Tabs. */
	Gui::Draw_Rect(0, 0, 160, 20, (this->Tab == Tabs::Main ? KBD_KEYPRESSED : KD_KEYUNPRESSED));
	Gui::Draw_Rect(160, 0, 160, 20, (this->Tab == Tabs::Misc ? KBD_KEYPRESSED : KD_KEYUNPRESSED));
	Gui::DrawStringCentered(-80, 3, 0.45f, TEXT_COLOR, "Main");
	Gui::DrawStringCentered(80, 3, 0.45f, TEXT_COLOR, "Miscellaneous");

	switch(this->Tab) {
		case Tabs::Main:
			/* Draw Conversations. */
			Gui::DrawString(39, 30, 0.5f, TEXT_COLOR, "Friendly");
			Gui::DrawSprite(GFX::Sprites, sprites_conversation_0_idx + (this->ActiveCast->Friendly()), this->Positions[2].X, this->Positions[2].Y);
			Gui::DrawString(133, 30, 0.5f, TEXT_COLOR, "Romance");
			Gui::DrawSprite(GFX::Sprites, sprites_conversation_0_idx + (this->ActiveCast->Romance()), this->Positions[3].X, this->Positions[3].Y);
			Gui::DrawString(230, 30, 0.5f, TEXT_COLOR, "Intimidate");
			Gui::DrawSprite(GFX::Sprites, sprites_conversation_0_idx + (this->ActiveCast->Intimidate()), this->Positions[4].X, this->Positions[4].Y);

			/* Draw Feeling + Secret box. */
			Gui::DrawString(10, this->Positions[5].Y + 5, 0.4f, TEXT_COLOR, "Feeling: " + this->Feelings[(uint8_t)this->ActiveCast->Feeling()]);
			Gui::DrawSprite(GFX::Sprites, sprites_stripe_idx, this->Positions[5].X, this->Positions[5].Y);
			Gui::DrawString(10, this->Positions[6].Y + 5, 0.4f, TEXT_COLOR, "Secret Unlocked: ");
			GFX::DrawCheckbox(this->Positions[6].X, this->Positions[6].Y, this->ActiveCast->Secret());
			break;

		case Tabs::Misc:
			/* Display Misc Buttons. */
			for (uint8_t Idx = 0; Idx < 4; Idx++) {
				Gui::Draw_Rect(this->MassPos[Idx + 2].X, this->MassPos[Idx + 2].Y, this->MassPos[Idx + 2].W, this->MassPos[Idx + 2].H, KBD_KEYPRESSED);

				Gui::DrawStringCentered(0, this->MassPos[Idx + 2].Y + 8, 0.5f, TEXT_COLOR, this->MiscNames[Idx], 150);
			}
			break;
	}

	Gui::Draw_Rect(this->Positions[7].X, this->Positions[7].Y, this->Positions[7].W, this->Positions[7].H, KBD_KEYPRESSED); // Cast Select.
	Gui::DrawSprite(GFX::Sprites, sprites_cast_btn_idx, this->Positions[7].X, this->Positions[7].Y);
	Gui::Draw_Rect(this->Positions[8].X, this->Positions[8].Y, this->Positions[8].W, this->Positions[8].H, KBD_KEYPRESSED); // Back.
	Gui::DrawSprite(GFX::Sprites, sprites_back_btn_idx, this->Positions[8].X, this->Positions[8].Y);

	if (!this->CastSelection) Pointer::Draw(); // Only draw Pointer if not Selector.

	/* Cast Selection for the bottom screen. */
	if (this->CastSelection) {
		Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(0, 0, 0, 190)); // Dim screen if Selector.

		GFX::DrawCornerEdge(true, this->CastSelectorBot[0].X, this->CastSelectorBot[0].Y, this->CastSelectorBot[0].H, true);
		GFX::DrawCornerEdge(false, this->CastSelectorBot[2].X, this->CastSelectorBot[2].Y, this->CastSelectorBot[2].H, true);

		Gui::Draw_Rect(95, 105, 130, 30, KD_KEYUNPRESSED);
		Gui::Draw_Rect(this->CastSelectorBot[1].X, this->CastSelectorBot[1].Y, this->CastSelectorBot[1].W, this->CastSelectorBot[1].H, CORNER_COLOR);
		Gui::DrawStringCentered(0, this->CastSelectorBot[1].Y + 3, 0.5f, TEXT_COLOR, "Select");

		Gui::Draw_Rect(this->CastSelectorBot[3].X, this->CastSelectorBot[3].Y, this->CastSelectorBot[3].W, this->CastSelectorBot[3].H, KBD_KEYPRESSED); // Back.
		Gui::DrawSprite(GFX::Sprites, sprites_back_btn_idx, this->CastSelectorBot[3].X, this->CastSelectorBot[3].Y);
	}
}


/* Main Logic. */
void GBACastEditor::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (this->CastSelection) this->CastSelectorLogic(hDown, hHeld, touch);
	else {
		Pointer::FrameHandle();
		Pointer::ScrollHandle(hHeld);

		if (hDown & KEY_A) {
			for (auto &Position : (this->Tab == Tabs::Main ? this->Positions : this->MassPos)) {
				if (Pointer::Callback(Position, true)) break;
			}
		}

		if (hDown & KEY_TOUCH) {
			for (auto &Position : (this->Tab == Tabs::Main ? this->Positions : this->MassPos)) {
				if (Touching(Position, touch, true)) break;
			}
		}

		if (hDown & KEY_L) this->MainTab();
		if (hDown & KEY_R) this->MiscTab();
		if (hDown & KEY_B) this->Back();
	}
}