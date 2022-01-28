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
#include "GBAEpisodeEditor.hpp"
#include "Numpad.hpp"
#include "Strings.hpp"


GBAEpisodeEditor::GBAEpisodeEditor(std::shared_ptr<S2Core::GBASlot> &Slot) : Slot(Slot) {
	this->ActiveEpisode = this->Slot->Episode(0);

	/* Push initial Boxes. */
	this->SetInputBoxes();
}


/* Set the NumInputLabel Boxes. */
void GBAEpisodeEditor::SetInputBoxes() {
	this->Boxes.clear(); // Clear first.

	this->Boxes.push_back(std::make_unique<NumInputLabel<uint8_t>>(220, 36, this->ActiveEpisode->Rating(0), 0, 25, "Enter the Episode Rating."));
	this->Boxes.push_back(std::make_unique<NumInputLabel<uint8_t>>(220, 76, this->ActiveEpisode->Rating(1), 0, 25, "Enter the Episode Rating."));
	this->Boxes.push_back(std::make_unique<NumInputLabel<uint8_t>>(220, 116, this->ActiveEpisode->Rating(2), 0, 25, "Enter the Episode Rating."));
	this->Boxes.push_back(std::make_unique<NumInputLabel<uint8_t>>(220, 156, this->ActiveEpisode->Rating(3), 0, 25, "Enter the Episode Rating."));
}


/* Go to last Season. */
void GBAEpisodeEditor::PrevSeason() {
	if (this->Season > 1) this->Season--;
}

/* Go to next Season. */
void GBAEpisodeEditor::NextSeason() {
	if (this->Season < 3) this->Season++;
}

/* The Episode Selection Action. */
void GBAEpisodeEditor::Select(const int Idx) {
	if (this->Season == 1 && Idx == 3) return; // Season 1 only has 3.

	switch(this->Season) {
		case 1:
			this->SelectedEpisode = Idx;
			break;

		case 2:
			this->SelectedEpisode = 3 + Idx;
			break;

		case 3:
			this->SelectedEpisode = 7 + Idx;
			break;
	}

	this->ActiveEpisode = this->Slot->Episode(this->SelectedEpisode);
	this->SetInputBoxes(); // Fetch again.

	Pointer::OnTop = false;
	Pointer::SetPos(this->MainPositions[3]);
	this->EpisodeSelect = false;
}


void GBAEpisodeEditor::CancelSelection() {
	Pointer::OnTop = false;
	Pointer::SetPos(this->MainPositions[3]);
	this->EpisodeSelect = false;
}


/* Draws the Episode Selector. */
void GBAEpisodeEditor::DrawEpisodeSelection(void) const {
	GFX::DrawTop();
	Gui::DrawString(40, 3, 0.6f, TEXT_COLOR, "Select a Episode you like to edit.");
	Gui::DrawString(390, 3, 0.6f, TEXT_COLOR, "Season: " + std::to_string(this->Season), 0, 0, nullptr, C2D_AlignRight);

	GFX::DrawCornerEdge(true, this->EPSelect[0].X, this->EPSelect[0].Y, this->EPSelect[0].H, true);
	GFX::DrawCornerEdge(false, this->EPSelect[5].X, this->EPSelect[5].Y, this->EPSelect[5].H, true);

	switch(this->Season) {
		case 1: // Season 1, 3 Episodes.
			for (uint8_t Idx = 0; Idx < 3; Idx++) {
				Gui::Draw_Rect(this->EPSelect[1 + Idx].X, this->EPSelect[1 + Idx].Y, this->EPSelect[1 + Idx].W, this->EPSelect[1 + Idx].H, (Idx % 2 == 0 ? KBD_KEYPRESSED : KD_KEYUNPRESSED));
				Gui::DrawStringCentered(0, this->EPSelect[1 + Idx].Y + 8, 0.5f, TEXT_COLOR, S2Core::Strings::GBAEpisodeNames_EN[1 + Idx]);
			}
			break;

		case 2: // Season 2, 4 Episodes.
			for (uint8_t Idx = 0; Idx < 4; Idx++) {
				Gui::Draw_Rect(this->EPSelect[1 + Idx].X, this->EPSelect[1 + Idx].Y, this->EPSelect[1 + Idx].W, this->EPSelect[1 + Idx].H, (Idx % 2 == 0 ? KBD_KEYPRESSED : KD_KEYUNPRESSED));
				Gui::DrawStringCentered(0, this->EPSelect[1 + Idx].Y + 8, 0.5f, TEXT_COLOR, S2Core::Strings::GBAEpisodeNames_EN[4 + Idx]);
			}
			break;

		case 3: // Season 3: 4 Episodes.
			for (uint8_t Idx = 0; Idx < 4; Idx++) {
				Gui::Draw_Rect(this->EPSelect[1 + Idx].X, this->EPSelect[1 + Idx].Y, this->EPSelect[1 + Idx].W, this->EPSelect[1 + Idx].H, (Idx % 2 == 0 ? KBD_KEYPRESSED : KD_KEYUNPRESSED));
				Gui::DrawStringCentered(0, this->EPSelect[1 + Idx].Y + 8, 0.5f, TEXT_COLOR, S2Core::Strings::GBAEpisodeNames_EN[8 + Idx]);
			}
			break;
	}

	Pointer::Draw();
}


/* Episode Selector Logic. */
void GBAEpisodeEditor::EpisodeSelectLogic(u32 hDown, u32 hHeld, touchPosition touch) {
	Pointer::FrameHandle();
	Pointer::ScrollHandle(hHeld);

	if (hDown & KEY_L) this->PrevSeason();
	if (hDown & KEY_R) this->NextSeason();

	if (hDown & KEY_A) {
		for (auto &Position : this->EPSelect) {
			if (Pointer::Callback(Position, true)) break;
		}
	}

	if (hDown & KEY_TOUCH) {
		for (auto &Position : this->EPSelectBot) {
			if (Touching(Position, touch, true)) break;
		}
	}

	if (hDown & KEY_B) this->CancelSelection();
}


/* Screen go back. */
void GBAEpisodeEditor::Back() {
	this->Exit = true;
	Gui::screenBack();
	return;
}


/* Select an Episode. */
void GBAEpisodeEditor::SelectEpisode() {
	Pointer::OnTop = true;
	Pointer::SetPos(this->EPSelect[0]);
	this->EpisodeSelect = true;
}


/* Toggle the Episode Unlock state. */
void GBAEpisodeEditor::ToggleEpisode() { this->ActiveEpisode->Unlocked(!this->ActiveEpisode->Unlocked()); }


/* Lock all Episodes cause why not LoL. */
void GBAEpisodeEditor::Lockall() {
	for (uint8_t Idx = 0; Idx < 11; Idx++) {
		std::unique_ptr<S2Core::GBAEpisode> EP = this->Slot->Episode(Idx);
		EP->Unlocked(false);
	}
}

/* Unlock all Episodes. */
void GBAEpisodeEditor::Unlockall() {
	for (uint8_t Idx = 0; Idx < 11; Idx++) {
		std::unique_ptr<S2Core::GBAEpisode> EP = this->Slot->Episode(Idx);
		EP->Unlocked(true);
	}
}

/* Clear the Rating of all Episodes. */
void GBAEpisodeEditor::ClearRatings() {
	for (uint8_t Idx = 0; Idx < 11; Idx++) {
		std::unique_ptr<S2Core::GBAEpisode> EP = this->Slot->Episode(Idx);

		for (uint8_t Idx2 = 0; Idx2 < 4; Idx2++) EP->Rating(Idx2, 0);
	}

	this->SetInputBoxes(); // Refresh.
}

/* Max out the Rating of all Episodes. */
void GBAEpisodeEditor::MaxRatings() {
	for (uint8_t Idx = 0; Idx < 11; Idx++) {
		std::unique_ptr<S2Core::GBAEpisode> EP = this->Slot->Episode(Idx);

		for (uint8_t Idx2 = 0; Idx2 < 4; Idx2++) EP->Rating(Idx2, 25);
	}

	this->SetInputBoxes(); // Refresh.
}


/* Draw Stripes cause cool. */
void GBAEpisodeEditor::DrawStripes(void) const {
	for (uint8_t Idx = 0; Idx < 5; Idx++) Gui::Draw_Rect(180, 31 + (Idx * 40), 10, 30, KBD_KEYPRESSED);
}


/* Main Draw. */
void GBAEpisodeEditor::Draw(void) const {
	if (this->EpisodeSelect) this->DrawEpisodeSelection();
	else {
		GFX::DrawTop();
		Gui::DrawStringCentered(0, 3, 0.6f, TEXT_COLOR, "GBA Episode Editor");
		Gui::Draw_Rect(100, 200, 200, 20, BUTTON_COLOR);
		Gui::DrawStringCentered(0, 202, 0.5f, TEXT_COLOR, S2Core::Strings::GBAEpisodeNames_EN[this->ActiveEpisode->Index() + 1]); // +1 cause 'It all Began' isn't a real Episode.
	}

	GFX::DrawBottom();

	/* Draw Tabs. */
	Gui::Draw_Rect(0, 0, 160, 20, (this->Tab == Tabs::Main ? KBD_KEYPRESSED : KD_KEYUNPRESSED));
	Gui::Draw_Rect(160, 0, 160, 20, (this->Tab == Tabs::Misc ? KBD_KEYPRESSED : KD_KEYUNPRESSED));
	Gui::DrawStringCentered(-80, 3, 0.45f, TEXT_COLOR, "Main");
	Gui::DrawStringCentered(80, 3, 0.45f, TEXT_COLOR, "Miscellaneous");

	switch(this->Tab) {
		case Tabs::Main:
			Gui::DrawString(10, 40, 0.5f, TEXT_COLOR, "Plot Points Completed: ");
			Gui::DrawString(10, 80, 0.5f, TEXT_COLOR, "Aspiration Conversations: ");
			Gui::DrawString(10, 120, 0.5f, TEXT_COLOR, "Hidden Want Completed: ");
			Gui::DrawString(10, 160, 0.5f, TEXT_COLOR, "Errand Completed: ");
			for (auto &Box : this->Boxes) Box->Draw(); // Draw Input Boxes.

			Gui::DrawString(10, 200, 0.5f, TEXT_COLOR, "Episode Unlocked: ");
			GFX::DrawCheckbox(this->MainPositions[2].X, this->MainPositions[2].Y, this->ActiveEpisode->Unlocked());
			this->DrawStripes();
			break;

		case Tabs::Misc:
			/* Display Misc Buttons. */
			for (uint8_t Idx = 0; Idx < 4; Idx++) {
				Gui::Draw_Rect(this->MassPos[Idx + 2].X, this->MassPos[Idx + 2].Y, this->MassPos[Idx + 2].W, this->MassPos[Idx + 2].H, KBD_KEYPRESSED);

				Gui::DrawStringCentered(0, this->MassPos[Idx + 2].Y + 8, 0.5f, TEXT_COLOR, this->MiscNames[Idx], 150);
			}
			break;
	}

	Gui::Draw_Rect(this->MainPositions[3].X, this->MainPositions[3].Y, this->MainPositions[3].W, this->MainPositions[3].H, KBD_KEYPRESSED); // Cast Select.
	Gui::DrawSprite(GFX::Sprites, sprites_episode_btn_idx, this->MainPositions[3].X, this->MainPositions[3].Y);
	Gui::Draw_Rect(this->MainPositions[4].X, this->MainPositions[4].Y, this->MainPositions[4].W, this->MainPositions[4].H, KBD_KEYPRESSED); // Back.
	Gui::DrawSprite(GFX::Sprites, sprites_back_btn_idx, this->MainPositions[4].X, this->MainPositions[4].Y);
	if (!this->EpisodeSelect) Pointer::Draw();

	if (this->EpisodeSelect) {
		Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(0, 0, 0, 210)); // DIM.

		/* Side Edge boxes. */
		GFX::DrawCornerEdge(true, this->EPSelectBot[0].X, this->EPSelectBot[0].Y, this->EPSelectBot[0].H, true);
		GFX::DrawCornerEdge(false, this->EPSelectBot[5].X, 25, this->EPSelectBot[5].H, true);

		for(uint8_t Idx = 0; Idx < (this->Season == 1 ? 3 : 4); Idx++) {
			Gui::Draw_Rect(this->EPSelectBot[1 + Idx].X, this->EPSelectBot[1 + Idx].Y, this->EPSelectBot[1 + Idx].W, this->EPSelectBot[1 + Idx].H, (Idx % 2 == 0 ? KBD_KEYPRESSED : KD_KEYUNPRESSED));
		}

		Gui::Draw_Rect(this->EPSelectBot[6].X, this->EPSelectBot[6].Y, this->EPSelectBot[6].W, this->EPSelectBot[6].H, KBD_KEYPRESSED); // Back.
		Gui::DrawSprite(GFX::Sprites, sprites_back_btn_idx, this->EPSelectBot[6].X, this->EPSelectBot[6].Y);
	}
}


/* Main Logic. */
void GBAEpisodeEditor::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (this->EpisodeSelect) {
		this->EpisodeSelectLogic(hDown, hHeld, touch);
		return;
	}

	const uint32_t hRepeat = hidKeysDownRepeat();
	Pointer::FrameHandle();
	Pointer::ScrollHandle(hHeld);

	if (hDown & KEY_B) this->Back();
	if (hDown & KEY_A) {
		bool Pressed = false;

		for (auto &Position : (this->Tab == Tabs::Main ? this->MainPositions : this->MassPos)) {
			if (Pointer::Callback(Position, true)) {
				Pressed = true;
				break;
			}
		}

		if (!Pressed && this->Tab == Tabs::Main) {
			for (uint8_t Idx = 0; Idx < 4; Idx++) {
				if (this->Boxes[Idx]->CallbackA()) {
					this->ActiveEpisode->Rating(Idx, this->Boxes[Idx]->GetVal());
					break;
				}
			}
		}
	}

	if (hRepeat & KEY_A) {
		if (this->Exit) return;

		if (this->Tab == Tabs::Main) {
			for (uint8_t Idx = 0; Idx < 4; Idx++) {
				if (this->Boxes[Idx]->CallbackAmountA()) {
					this->ActiveEpisode->Rating(Idx, this->Boxes[Idx]->GetVal());
					break;
				}
			}
		}
	}

	if (hDown & KEY_TOUCH) {
		bool Pressed = false;

		for (auto &Position : (this->Tab == Tabs::Main ? this->MainPositions : this->MassPos)) {
			if (Touching(Position, touch, true)) {
				Pressed = true;
				break;
			}
		}

		if (!Pressed && this->Tab == Tabs::Main) {
			for (uint8_t Idx = 0; Idx < 4; Idx++) {
				if (this->Boxes[Idx]->CallbackTouch(touch)) {
					this->ActiveEpisode->Rating(Idx, this->Boxes[Idx]->GetVal());
					break;
				}
			}
		}
	}

	if (hRepeat & KEY_TOUCH) {
		if (this->Exit) return;

		if (this->Tab == Tabs::Main) {
			for (uint8_t Idx = 0; Idx < 4; Idx++) {
				if (this->Boxes[Idx]->CallbackAmountTouch(touch)) {
					this->ActiveEpisode->Rating(Idx, this->Boxes[Idx]->GetVal());
					break;
				}
			}
		}
	}
}