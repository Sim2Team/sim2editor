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
#include "MainMenu.hpp"
#include "WaitMessage.hpp"
#include <3ds.h>
#include <dirent.h>

bool exiting = false;
uint32_t hDown = 0, hHeld = 0;
touchPosition touch;
std::unique_ptr<Config> CFG = nullptr;


int main() {
	gfxInitDefault();
	romfsInit();
	Gui::init();

	/* Create necessary directories. */
	mkdir("sdmc:/3ds", 0777);
	mkdir("sdmc:/3ds/Sim2Editor", 0777);
	mkdir("sdmc:/3ds/Sim2Editor/Backups", 0777);
	mkdir("sdmc:/3ds/Sim2Editor/Backups/GBA", 0777);
	mkdir("sdmc:/3ds/Sim2Editor/Backups/NDS", 0777);

	CFG = std::make_unique<Config>();
	GFX::LoadSheets();
	hidSetRepeatParameters(14, 6); // Set hidKeysDownRepeat() delay.

	if (CFG->FirstStart()) {
		std::unique_ptr<WaitMessage> Overlay = std::make_unique<WaitMessage>(std::vector<std::string>({
			"Welcome to Sim2Editor, a The Sims 2 GBA and NDS Save Editor for Nintendo 3DS and for your web browser.\n\nFor more Information, please use the next page arrow button.",
			"Currently the GBA Version has the most progress, however work on the NDS version has already started as well.",
			"Always create a backup of your Savefile though, in case bad things may happen, because this is still an early work in progress Save Editor.",
			"If you need to know more, checkout the wiki from Sim2Editor. And now have fun with Sim2Editor! ~SuperSaiyajinStackZ"
		}));

		Overlay->Action();
		CFG->FirstStart(false);
	}


	Gui::setScreen(std::make_unique<MainMenu>(), false, true);

	while(aptMainLoop() && !exiting) {
		Gui::clearTextBufs();
		C2D_TargetClear(Top, C2D_Color32(0, 0, 0, 0));
		C2D_TargetClear(Bottom, C2D_Color32(0, 0, 0, 0));
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		Gui::DrawScreen(true);
		Gui::ScreenLogic(hDown, hHeld, touch, false, true);
		C3D_FrameEnd(0);

		hidScanInput();
		hDown = hidKeysDown();
		hHeld = hidKeysHeld();
		hidTouchRead(&touch);
	}

	CFG->Sav();
	GFX::UnloadSheets();
	Gui::exit();
	romfsExit();
	gfxExit();

	return 0;
}