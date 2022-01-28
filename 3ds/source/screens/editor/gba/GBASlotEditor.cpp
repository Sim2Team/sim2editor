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
#include "GBAAppearanceEditor.hpp"
#include "GBACastEditor.hpp"
#include "GBAEpisodeEditor.hpp"
#include "GBAGeneralEditor.hpp"
#include "GBAHouseEditor.hpp"
#include "GBAItemEditor.hpp"
#include "GBAMinigameEditor.hpp"
#include "GBASlotEditor.hpp"
#include "GBASocialMoveEditor.hpp"
#include "SimUtils.hpp"


/* Go to Cast Editor. */
void GBASlotEditor::GotoCastEditor() { Gui::setScreen(std::make_unique<GBACastEditor>(this->Slot), false, true); }

/* Go to Episode Editor. */
void GBASlotEditor::GotoEpisodeEditor() { Gui::setScreen(std::make_unique<GBAEpisodeEditor>(this->Slot), false, true); }

/* Go to Social Move Editor. */
void GBASlotEditor::GotoMoveEditor() { Gui::setScreen(std::make_unique<GBASocialMoveEditor>(this->Slot), false, true); }

/* Go to General Editor. */
void GBASlotEditor::GotoGeneralEditor() { Gui::setScreen(std::make_unique<GBAGeneralEditor>(this->Slot), false, true); }

/* Go to Item Editor. */
void GBASlotEditor::GotoItemEditor() { Gui::setScreen(std::make_unique<GBAItemEditor>(this->Slot), false, true); }

/* Go to House Editor. */
void GBASlotEditor::GotoHouseEditor() { Gui::setScreen(std::make_unique<GBAHouseEditor>(this->Slot), false, true); }

/* Go to Appearance Editor. */
void GBASlotEditor::GotoAppearanceEditor() { Gui::setScreen(std::make_unique<GBAAppearanceEditor>(this->Slot), false, true); }

/* Go to Minigame Editor. */
void GBASlotEditor::GotoMinigameEditor() { Gui::setScreen(std::make_unique<GBAMinigameEditor>(this->Slot), false, true); }

/* Go back to Editor. */
void GBASlotEditor::Back() {
	Gui::screenBack();
	return;
}


void GBASlotEditor::Draw(void) const {
	GFX::DrawTop();
	Gui::DrawStringCentered(0, 3, 0.6f, TEXT_COLOR, "GBA Slot Editor");

	/* Display Info. */
	Gui::DrawStringCentered(0, 50, 0.5f, TEXT_COLOR, "Sim Name: " + this->Slot->Name());
	Gui::DrawStringCentered(0, 80, 0.5f, TEXT_COLOR, "Simoleons: " + S2Core::SimUtils::SimoleonsString(this->Slot->Simoleons()));
	Gui::DrawStringCentered(0, 110, 0.5f, TEXT_COLOR, "Ratings: " + S2Core::SimUtils::RatingString(this->Slot->Ratings()));
	Gui::DrawStringCentered(0, 140, 0.5f, TEXT_COLOR, "Time: " + S2Core::SimUtils::TimeString(this->Slot->Time(), false));
	GFX::DrawBottom();

	Gui::Draw_Rect(this->Positions[0].X, this->Positions[0].Y, this->Positions[0].W, this->Positions[0].H, KBD_KEYPRESSED); // Cast Icn.
	Gui::DrawSprite(GFX::Sprites, sprites_cast_btn_idx, this->Positions[0].X, this->Positions[0].Y);

	Gui::Draw_Rect(this->Positions[1].X, this->Positions[1].Y, this->Positions[1].W, this->Positions[1].H, KBD_KEYPRESSED); // Episode Icn.
	Gui::DrawSprite(GFX::Sprites, sprites_episode_btn_idx, this->Positions[1].X, this->Positions[1].Y);

	Gui::Draw_Rect(this->Positions[2].X, this->Positions[2].Y, this->Positions[2].W, this->Positions[2].H, KBD_KEYPRESSED); // Social Move Icn.
	Gui::DrawSprite(GFX::Sprites, sprites_moves_btn_idx, this->Positions[2].X, this->Positions[2].Y);

	Gui::Draw_Rect(this->Positions[3].X, this->Positions[3].Y, this->Positions[3].W, this->Positions[3].H, KBD_KEYPRESSED); // Appearance Icn.
	Gui::DrawSprite(GFX::Sprites, sprites_appearance_btn_idx, this->Positions[3].X, this->Positions[3].Y);

	Gui::Draw_Rect(this->Positions[4].X, this->Positions[4].Y, this->Positions[4].W, this->Positions[4].H, KBD_KEYPRESSED); // General Icn.
	Gui::DrawSprite(GFX::Sprites, sprites_collectables_btn_idx, this->Positions[4].X, this->Positions[4].Y);

	Gui::Draw_Rect(this->Positions[5].X, this->Positions[5].Y, this->Positions[5].W, this->Positions[5].H, KBD_KEYPRESSED); // Item Icn.
	Gui::DrawSprite(GFX::Sprites, sprites_item_btn_idx, this->Positions[5].X, this->Positions[5].Y + 5);

	Gui::Draw_Rect(this->Positions[6].X, this->Positions[6].Y, this->Positions[6].W, this->Positions[6].H, KBD_KEYPRESSED); // House Icn.
	Gui::DrawSprite(GFX::Sprites, sprites_house_btn_idx, this->Positions[6].X, this->Positions[6].Y + 2);

	Gui::Draw_Rect(this->Positions[7].X, this->Positions[7].Y, this->Positions[7].W, this->Positions[7].H, KBD_KEYPRESSED); // Minigame Icn.
	Gui::DrawSprite(GFX::Sprites, sprites_minigame_btn_idx, this->Positions[7].X, this->Positions[7].Y);

	Gui::Draw_Rect(this->Positions[8].X, this->Positions[8].Y, this->Positions[8].W, this->Positions[8].H, KBD_KEYPRESSED); // Back Icn.
	Gui::DrawSprite(GFX::Sprites, sprites_back_btn_idx, this->Positions[8].X, this->Positions[8].Y);

	Pointer::Draw();
}


void GBASlotEditor::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
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