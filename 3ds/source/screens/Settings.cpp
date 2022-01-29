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
#include "FileSelection.hpp"
#include "Numpad.hpp"
#include "Settings.hpp"


void Settings::Draw(void) const {
	this->DrawCredits();
	this->DrawPages();
}


/* Tab switches. */
void Settings::ConfigTab() { this->Tab = SettingsTab::Configuration; }
void Settings::AppinfoTab() { this->Tab = SettingsTab::AppInfo; }


/* Toggle Backup Creation. */
void Settings::ToggleBackups() {
	if (this->Tab == SettingsTab::Configuration) CFG->CreateBackups(!CFG->CreateBackups());
}


/* Set Default Save Path. */
void Settings::SetDefaultPath() {
	if (this->Tab == SettingsTab::Configuration) {
		std::unique_ptr<FileSelection> Overlay = std::make_unique<FileSelection>(CFG->SAVPath(), std::vector<std::string>({ "/" }), "Select a Default Save Path.", true, true);

		std::string Path = Overlay->Action();
		if (Path != "!") {
			if (Path[Path.size() - 1] != '/') Path += "/";

			CFG->SAVPath(Path);
		}
	}
}


/* Set Pointer Speed. */
void Settings::SetPointerSpeed() {
	if (this->Tab == SettingsTab::Configuration) {
		std::unique_ptr<Numpad> Overlay = std::make_unique<Numpad>(3, CFG->PointerSpeed(), 255, "Enter the Pointer Movement speed.");
		CFG->PointerSpeed(Overlay->Action());
	}
}


/* Go back to MainMenu. */
void Settings::Back() {
	Gui::screenBack();
	return;
}


void Settings::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	Pointer::FrameHandle();
	Pointer::ScrollHandle(hHeld); // Pointer Handling.

	if (hDown & KEY_B) this->Back();
	if (hDown & KEY_L) this->ConfigTab();
	if (hDown & KEY_R) this->AppinfoTab();
	if (hDown & KEY_SELECT) CFG->PointerSpeed(4); // Reset in case someone made it too fast so it can't be controlled anymore. ;P
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


void Settings::DrawCredits() const {
	GFX::DrawTop();
	Gui::DrawStringCentered(0, 3, 0.6f, TEXT_COLOR, "Sim2Editor");
	Gui::DrawString(340, 3, 0.6f, TEXT_COLOR, V_STRING);
	Gui::DrawSprite(GFX::Sprites, sprites_StackZ_idx, 10, 62);

	Gui::DrawString(150, 40, 0.4f, TEXT_COLOR, "Developed by: Universal-Team / now Sim2Team.");
	Gui::DrawString(150, 50, 0.4f, TEXT_COLOR, "Main Developer: SuperSaiyajinStackZ.");

	Gui::DrawString(225, 80, 0.5f, TEXT_COLOR, "Others");
	Gui::DrawString(125, 100, 0.4f, TEXT_COLOR, "DevkitPro: devkitARM, libctru, citro2d, citro3d.");
	Gui::DrawString(125, 110, 0.4f, TEXT_COLOR, "SuperSaiyajinStackZ: App Developement + Researches.");
	Gui::DrawString(125, 120, 0.4f, TEXT_COLOR, "Universal-Team: Universal-Core.");

	Gui::DrawStringCentered(0, 200, 0.4f, TEXT_COLOR, "For Researches, see 'https://sim2team.github.io/wiki/research'.");
}


void Settings::DrawSettingStripe() const {
	for (uint8_t Idx = 0; Idx < 3; Idx++) Gui::Draw_Rect(220, 35 + (Idx * 40), 10, 30, BAR_COLOR);
}


void Settings::DrawPages() const {
	GFX::DrawBottom();
	Gui::Draw_Rect(0, 0, 160, 20, (this->Tab == SettingsTab::Configuration ? KBD_KEYPRESSED : KD_KEYUNPRESSED));
	Gui::Draw_Rect(160, 0, 160, 20, (this->Tab == SettingsTab::AppInfo ? KBD_KEYPRESSED : KD_KEYUNPRESSED));

	for (uint8_t Idx = 0; Idx < 2; Idx++) { // Draw Tabs.
		Gui::DrawStringCentered((Idx ? + 80 : - 80), 3, 0.45f, TEXT_COLOR, this->TabNames[Idx]);
	}

	switch(this->Tab) {
		case SettingsTab::Configuration:
			this->DrawSettingStripe();
			Gui::DrawString(30, this->Positions[2].Y + 5, 0.4f, TEXT_COLOR, "Create Backups on Save Load");
			GFX::DrawCheckbox(this->Positions[2].X, this->Positions[2].Y, CFG->CreateBackups());

			Gui::DrawString(30, this->Positions[3].Y + 5, 0.4f, TEXT_COLOR, "Default Save Path");
			Gui::DrawSprite(GFX::Sprites, sprites_stripe_idx, this->Positions[3].X, this->Positions[3].Y);

			Gui::DrawString(30, this->Positions[4].Y + 5, 0.4f, TEXT_COLOR, "Pointer Speed");
			Gui::DrawSprite(GFX::Sprites, sprites_stripe_idx, this->Positions[4].X, this->Positions[4].Y);
			break;

		case SettingsTab::AppInfo:
			Gui::DrawString(10, 50, 0.5f, TEXT_COLOR, "Build Version: " + std::string(V_STRING));
			Gui::DrawString(10, 80, 0.5f, TEXT_COLOR, "Commit hash: " + std::string(V_SHA));
			Gui::DrawStringCentered(0, 110, 0.6f, TEXT_COLOR, "Latest Changes");

			/* Change this, after changes to the 3DS version. */
			Gui::DrawStringCentered(0, 130, 0.4f, TEXT_COLOR,
				"* [CORE]: GBA Identifier is 8 in size, not 7.\n" \
				"* [CORE]: Fixed the Backup Checks.\n" \
				"* [APP]: Don't allow empty String Label Inputs.",
			310);
			break;
	}

	/* Back Icon. */
	Gui::Draw_Rect(this->Positions[7].X, this->Positions[7].Y, this->Positions[7].W, this->Positions[7].H, KBD_KEYPRESSED);
	Gui::DrawSprite(GFX::Sprites, sprites_back_btn_idx, this->Positions[7].X, this->Positions[7].Y);

	Pointer::Draw();
}