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
#include "GBAPantsSelection.hpp"


/* Go to the previous Pants. */
void GBAPantsSelection::PrevPants() const {
	this->Res = !this->Res;
}

/* Go to the next Hair. */
void GBAPantsSelection::NextPants() const {
	this->Res = !this->Res;
}

/* Set the Select State. */
void GBAPantsSelection::Select() const {
	this->Done = true;
}


void GBAPantsSelection::Cancel() const {
	this->Res = -1;
	this->Done = true;
}


int8_t GBAPantsSelection::Action() const {
	Pointer::SetPos(this->Positions[1]);
	Pointer::OnTop = true;

	while(!this->Done) {
		Gui::clearTextBufs();
		C2D_TargetClear(Top, C2D_Color32(0, 0, 0, 0));
		C2D_TargetClear(Bottom, C2D_Color32(0, 0, 0, 0));
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

		GFX::DrawTop();
		Gui::DrawStringCentered(0, 3, 0.6f, TEXT_COLOR, "Select the Pants you want.");

		/* Draw Edge boxes. */
		GFX::DrawCornerEdge(true, this->Positions[0].X, this->Positions[0].Y, this->Positions[0].H, true);
		GFX::DrawCornerEdge(false, this->Positions[1].X, this->Positions[1].Y, this->Positions[1].H, true);

		/* Draw the Pants. */
		Gui::DrawSprite(GFX::Appearance, 8, 100, 50);
		Gui::DrawSprite(GFX::Appearance, (this->IsFemale ? 10 : 9), 235, 50);
		Gui::DrawSprite(GFX::Sprites, sprites_frame1_idx, (this->Res ? 280 : 145), 40); // Draw first frame of the Pointer above the current Pants.

		Gui::Draw_Rect(this->Positions[2].X, this->Positions[2].Y, this->Positions[2].W, this->Positions[2].H, BUTTON_COLOR);
		Pointer::Draw();

		GFX::DrawBottom();
		Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(0, 0, 0, 190));

		GFX::DrawCornerEdge(true, this->BottomPos[0].X, this->BottomPos[0].Y, this->BottomPos[0].H, true);
		GFX::DrawCornerEdge(false, this->BottomPos[2].X, this->BottomPos[2].Y, this->BottomPos[2].H, true);

		Gui::Draw_Rect(95, 105, 130, 30, KD_KEYUNPRESSED);
		Gui::Draw_Rect(this->BottomPos[1].X, this->BottomPos[1].Y, this->BottomPos[1].W, this->BottomPos[1].H, CORNER_COLOR);
		Gui::DrawStringCentered(0, this->BottomPos[1].Y + 3, 0.5f, TEXT_COLOR, "Select");

		Gui::Draw_Rect(this->BottomPos[3].X, this->BottomPos[3].Y, this->BottomPos[3].W, this->BottomPos[3].H, KBD_KEYPRESSED); // Back.
		Gui::DrawSprite(GFX::Sprites, sprites_back_btn_idx, this->BottomPos[3].X, this->BottomPos[3].Y);
		C3D_FrameEnd(0);

		Pointer::FrameHandle();
		hidScanInput();
		touchPosition T;
		hidTouchRead(&T);
		uint32_t hDown = hidKeysDown();
		uint32_t hHeld = hidKeysHeld();
		Pointer::ScrollHandle(hHeld);

		if (hDown & KEY_L) this->PrevPants();
		if (hDown & KEY_R) this->NextPants();
		if (hDown & KEY_B) this->Cancel();

		if (hDown & KEY_A) {
			for (auto &Position : this->Positions) {
				if (Pointer::Callback(Position, true)) break;
			}
		}

		if (hDown & KEY_TOUCH) {
			for (auto &Position : this->BottomPos) {
				if (Touching(Position, T, true)) break;
			}
		}

		if (hDown & KEY_START) this->Select();
	}

	Pointer::OnTop = false;
	Pointer::SetPos(0, 0);
	return this->Res;
}