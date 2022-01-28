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
#include "FileSelection.hpp"
#include "GBASlotEditor.hpp"
#include "GBASlotSelection.hpp"
#include "NDSSlotSelection.hpp"
#include "NDSSlotEditor.hpp"
#include "PromptMessage.hpp"
#include "SavUtils.hpp"
#include "WaitMessage.hpp"


/* Goes back to MainMenu. */
void Editor::Back() {
	/* Warning if changes made and you try to exit. */
	if (this->Mode == Modes::Menu) {
		if (S2Core::SavUtils::ChangesMade()) {
			std::unique_ptr<PromptMessage> Overlay = std::make_unique<PromptMessage>("Changes have been made to the Savefile.\n\nWould you still like to exit without Saving?");
			if (!Overlay->Action()) return;
		}
	}

	Gui::screenBack();
	return;
}


/* Loading a SAV Operation. */
void Editor::LoadSAV() {
	const std::vector<std::string> EXTs = { "sav", "sav1", "sav2", "sav3", "sav4", "sav5", "sav6", "sav7", "sav8", "sav9" };
	std::unique_ptr<FileSelection> Overlay = std::make_unique<FileSelection>(CFG->SAVPath(), EXTs, "Select a Savefile for the Editor.", true, false);

	const std::string Path = Overlay->Action();
	if (Path != "!") { // '!' means canceled.
		const S2Core::SavType ST = S2Core::SavUtils::LoadSav(Path);

		switch(ST) {
			case S2Core::SavType::_GBA:
			case S2Core::SavType::_NDS: {
				if (CFG->CreateBackups()) {
					if (S2Core::SavUtils::CreateBackup("sdmc:/3ds/Sim2Editor")) {
						std::unique_ptr<WaitMessage> Ovl = std::make_unique<WaitMessage>("Backup Created!\nHave fun with the Editor now.");
						Ovl->Action();

					} else {
						std::unique_ptr<WaitMessage> Ovl = std::make_unique<WaitMessage>("Backup Creation Failed!\nIssue might be related to your SD Card or so.");
						Ovl->Action();
					}
				}

				this->Mode = Modes::Menu;
			}
			break;

			case S2Core::SavType::_NONE: {
					std::unique_ptr<PromptMessage> Ovl = std::make_unique<PromptMessage>("This is not a The Sims 2 GBA or NDS Savefile.\nWould you like to load another Savefile?");
					if (!Ovl->Action()) this->Back();
				}
				break;
		}

	} else {
		this->Back();
	}
}


/* Loading a SAVSlot. */
void Editor::LoadSlot() {
	if (this->Mode == Modes::Menu) {
		if (S2Core::SavUtils::Sav->GetType() == S2Core::SavType::_GBA) {
			std::unique_ptr<GBASlotSelection> Overlay = std::make_unique<GBASlotSelection>();
			const int8_t Slot = Overlay->Action();

			if (Slot != -1) Gui::setScreen(std::make_unique<GBASlotEditor>(S2Core::SavUtils::Sav->_GBASlot(Slot)), false, true);

		} else if (S2Core::SavUtils::Sav->GetType() == S2Core::SavType::_NDS) {
			std::unique_ptr<NDSSlotSelection> Overlay = std::make_unique<NDSSlotSelection>();
			const int8_t Slot = Overlay->Action();

			if (Slot != -1) Gui::setScreen(std::make_unique<NDSSlotEditor>(S2Core::SavUtils::Sav->_NDSSlot(Slot)), false, true);
		}
	}
}


/* SAV changes to file. */
void Editor::SAV() {
	if (this->Mode == Modes::Menu) {
		this->Mode = Modes::SAVLoad; // First set to SAVLoad.
		S2Core::SavUtils::Finish(); // Finish, Write to File, Reset variables such as the pointer to the SAV.

		std::unique_ptr<PromptMessage> Overlay = std::make_unique<PromptMessage>("Changes have been saved.\nWould you like to load another Savefile?");
		const bool Res = Overlay->Action();

		if (!Res) this->Back();
	}
}


void Editor::Draw(void) const {
	if (this->Mode == Modes::Menu) {
		GFX::DrawTop();
		Gui::DrawStringCentered(0, 3, 0.6f, TEXT_COLOR, "Editor Main Screen");

		switch(S2Core::SavUtils::Sav->GetType()) {
			case S2Core::SavType::_GBA:
				Gui::DrawStringCentered(0, 60, 0.5f, TEXT_COLOR, "Detected SAVType: GBA.");
				break;

			case S2Core::SavType::_NDS:
				Gui::DrawStringCentered(0, 60, 0.5f, TEXT_COLOR, "Detected SAVType: NDS.");
				break;

			case S2Core::SavType::_NONE:
				break;
		}

		GFX::DrawBottom();

		Gui::Draw_Rect(this->Positions[0].X, this->Positions[0].Y, this->Positions[0].W, this->Positions[0].H, KBD_KEYPRESSED); // Slot Icn.
		Gui::DrawSprite(GFX::Sprites, sprites_slot_btn_idx, this->Positions[0].X, this->Positions[0].Y);
		Gui::Draw_Rect(this->Positions[1].X, this->Positions[1].Y, this->Positions[1].W, this->Positions[1].H, KBD_KEYPRESSED); // SAV Icn.
		Gui::DrawSprite(GFX::Sprites, sprites_sav_btn_idx, this->Positions[1].X, this->Positions[1].Y);
		Gui::Draw_Rect(this->Positions[2].X, this->Positions[2].Y, this->Positions[2].W, this->Positions[2].H, KBD_KEYPRESSED); // Back Icn.
		Gui::DrawSprite(GFX::Sprites, sprites_back_btn_idx, this->Positions[2].X, this->Positions[2].Y);

		Pointer::Draw();
	}
}


void Editor::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (this->Mode == Modes::SAVLoad) {
		this->LoadSAV();
		return;
	}

	Pointer::FrameHandle();
	Pointer::ScrollHandle(hHeld);

	if (hDown & KEY_B) this->Back();
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
}