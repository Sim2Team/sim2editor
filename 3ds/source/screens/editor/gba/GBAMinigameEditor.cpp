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
#include "GBAMinigameEditor.hpp"
#include "ListSelection.hpp"
#include "Strings.hpp"


/* MAIN Tab. */
void GBAMinigameEditor::TogglePlayed() { this->ActiveMinigame->Played(!this->ActiveMinigame->Played()); } // Toggle the Played state.


/* Miscellaneous Tab. */
void GBAMinigameEditor::ResetLevels() { // Reset Minigame Levels.
	for (uint8_t Idx = 0; Idx < 7; Idx++) {
		std::unique_ptr<S2Core::GBAMinigame> Game = this->Slot->Minigame(Idx);

		Game->Level(0, true);
	}

	this->LevelLabel = std::make_unique<NumInputLabel<uint8_t>>(140, 80, this->ActiveMinigame->Level(), 0, 5, "Enter the Minigame Level.");
}

void GBAMinigameEditor::MaxLevels() { // Max out Minigame Levels.
	for (uint8_t Idx = 0; Idx < 7; Idx++) {
		std::unique_ptr<S2Core::GBAMinigame> Game = this->Slot->Minigame(Idx);

		Game->Level(5, true);
	}

	this->LevelLabel = std::make_unique<NumInputLabel<uint8_t>>(140, 80, this->ActiveMinigame->Level(), 0, 5, "Enter the Minigame Level.");
}

void GBAMinigameEditor::AllPlayed() { // Set all Minigames to played.
	for (uint8_t Idx = 0; Idx < 7; Idx++) {
		std::unique_ptr<S2Core::GBAMinigame> Game = this->Slot->Minigame(Idx);

		Game->Played(true);
	}
}

void GBAMinigameEditor::AllUnplayed() { // Set all Minigames to unplayed.
	for (uint8_t Idx = 0; Idx < 7; Idx++) {
		std::unique_ptr<S2Core::GBAMinigame> Game = this->Slot->Minigame(Idx);

		Game->Played(false);
	}
}


/* Goes screen back. */
void GBAMinigameEditor::Back() {
	this->Exit = true;
	Gui::screenBack();
	return;
}


/* Init a minigame. */
void GBAMinigameEditor::InitGame(const uint8_t Game) {
	this->ActiveMinigame = this->Slot->Minigame(Game);

	/* Init Label. */
	this->LevelLabel = std::make_unique<NumInputLabel<uint8_t>>(140, 80, this->ActiveMinigame->Level(), 0, 5, "Enter the Minigame Level.");
}


/* Select a Minigame from the list. */
void GBAMinigameEditor::SelectMinigame() {
	std::unique_ptr<ListSelection> Ovl = std::make_unique<ListSelection>(S2Core::Strings::GBAMinigameNames_EN, "Select a minigame you like to edit.", this->ActiveMinigame->Index());
	const uint8_t Game = Ovl->Action();

	/* Init new selected game. */
	if (Game != this->ActiveMinigame->Index()) this->InitGame(Game);
}


/* Main Draw. */
void GBAMinigameEditor::Draw(void) const {
	GFX::DrawTop();
	Gui::DrawStringCentered(0, 3, 0.6f, TEXT_COLOR, "GBA Minigame Editor");
	Gui::Draw_Rect(100, 200, 200, 20, BUTTON_COLOR);
	Gui::DrawStringCentered(0, 202, 0.5f, TEXT_COLOR, S2Core::Strings::GBAMinigameNames_EN[this->ActiveMinigame->Index()]);

	GFX::DrawBottom();

	/* Draw Tabs. */
	Gui::Draw_Rect(0, 0, 160, 20, (this->Tab == Tabs::Main ? KBD_KEYPRESSED : KD_KEYUNPRESSED));
	Gui::Draw_Rect(160, 0, 160, 20, (this->Tab == Tabs::Misc ? KBD_KEYPRESSED : KD_KEYUNPRESSED));
	Gui::DrawStringCentered(-80, 3, 0.45f, TEXT_COLOR, "Main");
	Gui::DrawStringCentered(80, 3, 0.45f, TEXT_COLOR, "Miscellaneous");

	switch(this->Tab) {
		case Tabs::Main:
			/* Draw Level. */
			Gui::DrawString(120, 83, 0.5f, TEXT_COLOR, "Level: ", 110, 0, nullptr, C2D_AlignRight);
			this->LevelLabel->Draw();

			/* Draw Minigame Played. */
			Gui::DrawString(120, 123, 0.5f, TEXT_COLOR, "Played Today: ", 110, 0, nullptr, C2D_AlignRight);
			GFX::DrawCheckbox(this->Positions[2].X, this->Positions[2].Y, this->ActiveMinigame->Played());
			break;

		case Tabs::Misc:
			/* Display Misc Buttons. */
			for (uint8_t Idx = 0; Idx < 4; Idx++) {
				Gui::Draw_Rect(this->MassPos[Idx + 2].X, this->MassPos[Idx + 2].Y, this->MassPos[Idx + 2].W, this->MassPos[Idx + 2].H, KBD_KEYPRESSED);

				Gui::DrawStringCentered(0, this->MassPos[Idx + 2].Y + 8, 0.5f, TEXT_COLOR, this->MiscNames[Idx], 150);
			}
			break;
	}

	Gui::Draw_Rect(this->Positions[3].X, this->Positions[3].Y, this->Positions[3].W, this->Positions[3].H, KBD_KEYPRESSED); // Minigame icn.
	Gui::DrawSprite(GFX::Sprites, sprites_minigame_btn_idx, this->Positions[3].X, this->Positions[3].Y);
	Gui::Draw_Rect(this->Positions[4].X, this->Positions[4].Y, this->Positions[4].W, this->Positions[4].H, KBD_KEYPRESSED); // Back.
	Gui::DrawSprite(GFX::Sprites, sprites_back_btn_idx, this->Positions[4].X, this->Positions[4].Y);
	Pointer::Draw();
}


/* Main Logic. */
void GBAMinigameEditor::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	Pointer::FrameHandle();
	Pointer::ScrollHandle(hHeld);
	uint32_t hRepeat = hidKeysDownRepeat();

	if (hDown & KEY_A) {
		bool Pressed = false;

		for (auto &Position : (this->Tab == Tabs::Main ? this->Positions : this->MassPos)) {
			if (Pointer::Callback(Position, true)) {
				Pressed = true;
				break;
			}
		}

		/* Level. */
		if (!Pressed && this->Tab == Tabs::Main) {
			if (this->LevelLabel->CallbackA()) this->ActiveMinigame->Level(this->LevelLabel->GetVal());
		}
	}

	/* NUM Input Labels Only. */
	if (hRepeat & KEY_A && this->Tab == Tabs::Main) {
		if (this->Exit) return;

		/* Level. */
		if (this->LevelLabel->CallbackAmountA()) this->ActiveMinigame->Level(this->LevelLabel->GetVal());
	}

	if (hDown & KEY_TOUCH) {
		bool Pressed = false;

		for (auto &Position : (this->Tab == Tabs::Main ? this->Positions : this->MassPos)) {
			if (Touching(Position, touch, true)) {
				Pressed = true;
				break;
			}
		}

		/* Level. */
		if (!Pressed && this->Tab == Tabs::Main) {
			if (this->LevelLabel->CallbackTouch(touch)) this->ActiveMinigame->Level(this->LevelLabel->GetVal());
		}
	}

	/* Same for the Minus and Plus buttons as well. */
	if (hRepeat & KEY_TOUCH) {
		if (this->Exit) return;

		/* Level. */
		if (this->LevelLabel->CallbackAmountTouch(touch)) this->ActiveMinigame->Level(this->LevelLabel->GetVal());
	}

	if (hDown & KEY_L) this->MainTab();
	if (hDown & KEY_R) this->MiscTab();
	if (hDown & KEY_B) this->Back();
}