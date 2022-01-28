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
#include "NDSSlotSelection.hpp"
#include "SAVUtils.hpp"
#include "SimUtils.hpp"
#include "Strings.hpp"


/* Go to the last Slot and fetch the information. */
void NDSSlotSelection::PrevSlot() const {
	if (this->Res > 0) this->Res--;
	else this->Res = 2;

	this->FetchSlot();
}

/* Go to the next Slot and fetch the information. */
void NDSSlotSelection::NextSlot() const {
	if (this->Res < 2) this->Res++;
	else this->Res = 0;

	this->FetchSlot();
}

/* Check if Slot exist and set to done. */
void NDSSlotSelection::OK() const {
	if (S2Core::SavUtils::Sav->SlotExist(this->Res)) this->Done = true;
}


/*
	Fetches Information about the Slot.
	Current Fetches:

	- Slot Index.
	- Simoleon Amount.
	- Sim Name.
*/
void NDSSlotSelection::FetchSlot() const {
	this->Info.Slot = this->Res;

	if (S2Core::SavUtils::Sav->SlotExist(this->Res)) {
		std::unique_ptr<S2Core::NDSSlot> Slt = S2Core::SavUtils::Sav->_NDSSlot(this->Res);
		this->Info.SimoleonString = S2Core::SimUtils::SimoleonsString(Slt->Simoleons());
		this->Info.SimName = Slt->Name();

	} else {
		this->Info.SimoleonString = "0$";
		this->Info.SimName = "";
	}
}


/* Cancel NDSSlot Selection. */
void NDSSlotSelection::Cancel() const {
	this->Res = -1;
	this->Done = true;
}


int8_t NDSSlotSelection::Action() const {
	Pointer::SetPos(this->Positions[1]);
	Pointer::OnTop = true;
	this->FetchSlot();

	while(!this->Done) {
		Gui::clearTextBufs();
		C2D_TargetClear(Top, C2D_Color32(0, 0, 0, 0));
		C2D_TargetClear(Bottom, C2D_Color32(0, 0, 0, 0));
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

		GFX::DrawTop();
		Gui::Draw_Rect(0, 215, 400, 25, BAR_COLOR);
		Gui::DrawStringCentered(0, 3, 0.6f, TEXT_COLOR, "Select the NDSSlot you like to edit.");

		/* Display Box + Top Field. */
		GFX::DrawMsgBox(this->Positions[0].X, this->Positions[0].Y, this->Positions[2].X - 15, this->Positions[0].H);
		Gui::Draw_Rect(this->Positions[1].X, this->Positions[1].Y, this->Positions[1].W, this->Positions[1].H, CORNER_COLOR);
		Gui::Draw_Rect(this->Positions[3].X, this->Positions[3].Y, this->Positions[3].W, this->Positions[3].H, CORNER_COLOR);

		/* Arrows for the sides. */
		Gui::DrawSprite(GFX::Sprites, sprites_arrow_idx, this->Positions[0].X + 5, this->Positions[0].Y + ((this->Positions[0].H / 2) - (39 / 2)));
		Gui::DrawSprite(GFX::Sprites, sprites_arrow_idx, this->Positions[2].X, this->Positions[2].Y + ((this->Positions[2].H / 2) - (39 / 2)), -1.0f, 1.0f);

		/* Info. */
		Gui::DrawStringCentered(0, 36, 0.6f, TEXT_COLOR, "Selected Slot: " + std::to_string(this->Info.Slot + 1));
		Gui::DrawStringCentered(0, 65, 0.5f, TEXT_COLOR, "Name: " + this->Info.SimName, 260);
		Gui::DrawStringCentered(0, 85, 0.5f, TEXT_COLOR, "Simoleons: " + this->Info.SimoleonString, 260);

		Gui::DrawStringCentered(2, this->Positions[1].Y + 2, 0.5f, TEXT_COLOR, "OK"); // OK.

		Pointer::Draw();
		GFX::DrawBottom();

		GFX::DrawCornerEdge(true, this->BottomPos[0].X, this->BottomPos[0].Y, this->BottomPos[0].H, true);
		GFX::DrawCornerEdge(false, this->BottomPos[2].X, this->BottomPos[2].Y, this->BottomPos[2].H, true);

		Gui::Draw_Rect(95, 105, 130, 30, KD_KEYUNPRESSED);
		Gui::Draw_Rect(this->BottomPos[1].X, this->BottomPos[1].Y, this->BottomPos[1].W, this->BottomPos[1].H, CORNER_COLOR);
		Gui::DrawStringCentered(0, this->BottomPos[1].Y + 3, 0.5f, TEXT_COLOR, "OK"); // OK.

		/* BACK. */
		Gui::Draw_Rect(this->BottomPos[3].X, this->BottomPos[3].Y, this->BottomPos[3].W, this->BottomPos[3].H, KBD_KEYPRESSED); // Back Icn.
		Gui::DrawSprite(GFX::Sprites, sprites_back_btn_idx, this->BottomPos[3].X, this->BottomPos[3].Y);

		C3D_FrameEnd(0);

		Pointer::FrameHandle();
		hidScanInput();
		touchPosition T;
		hidTouchRead(&T);
		uint32_t hDown = hidKeysDown();
		uint32_t hHeld = hidKeysHeld();
		Pointer::ScrollHandle(hHeld);

		if (hDown & KEY_L) this->PrevSlot();
		if (hDown & KEY_R) this->NextSlot();
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

		if (hDown & KEY_START) this->OK();
	}

	Pointer::OnTop = false;
	Pointer::SetPos(0, 0);
	return this->Res;
}