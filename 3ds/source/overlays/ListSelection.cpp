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
#include "ListSelection.hpp"

#define ENTRIES_PER_SCREEN 5


ListSelection::ListSelection(const std::vector<std::string> &List, const std::string &Text, const int OldSelection)
	: Text(Text), OldSelection(OldSelection) {
	this->Browse = std::make_unique<Browser>(List);
	this->List = this->Browse->GetList();
	this->Browse->SetSelection(this->OldSelection);
};


/* Pages. */
void ListSelection::PrevPage() const { this->Browse->Left(ENTRIES_PER_SCREEN); }
void ListSelection::NextPage() const { this->Browse->Right(ENTRIES_PER_SCREEN); }


/*
	List call: Check if the pressed Index is good, and return it.

	const int Idx: The clicked Index.
*/
void ListSelection::ListCall(const int Idx) const {
	if (Idx >= (int)this->List.size()) return;

	if (this->Browse->SetSelection(this->ScreenPos + Idx)) {
		this->Res = this->Browse->GetSelectedIndex();
		this->Done = true;
	}
}


/* B Button Call: Set the result to the old Selection and set status to done. */
void ListSelection::BCall() const {
	this->Res = this->OldSelection;
	this->Done = true;
}


int ListSelection::Action() const {
	Pointer::OnTop = true;
	Pointer::SetPos(this->Positions[0]);

	while(!this->Done) {
		Gui::clearTextBufs();
		C2D_TargetClear(Top, C2D_Color32(0, 0, 0, 0));
		C2D_TargetClear(Bottom, C2D_Color32(0, 0, 0, 0));
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		GFX::DrawTop();

		GFX::DrawCornerEdge(true, this->Positions[0].X, this->Positions[0].Y, this->Positions[0].H, true);
		GFX::DrawCornerEdge(false, this->Positions[6].X, this->Positions[6].Y, this->Positions[6].H, true);

		Gui::DrawStringCentered(0, 3, 0.6f, TEXT_COLOR, this->Text);
		Gui::Draw_Rect(0, 215, 400, 25, BAR_COLOR);
		Gui::DrawStringCentered(0, 218, 0.6f, TEXT_COLOR, this->List[this->OldSelection]);

		if (this->List.size() > 0) {
			for(int Idx = 0; Idx < ENTRIES_PER_SCREEN && Idx < (int)this->List.size(); Idx++) {
				Gui::Draw_Rect(this->Positions[1 + Idx].X, this->Positions[1 + Idx].Y, this->Positions[1 + Idx].W, this->Positions[1 + Idx].H, (Idx % 2 == 0 ? KBD_KEYPRESSED : KD_KEYUNPRESSED));
				Gui::DrawStringCentered(0, this->Positions[1 + Idx].Y + 8, 0.5f, TEXT_COLOR, this->List[this->ScreenPos + Idx], 290);
			}
		}

		Pointer::Draw();
		GFX::DrawBottom();
		/* Side Edge boxes. */
		GFX::DrawCornerEdge(true, this->BottomPos[0].X, this->BottomPos[0].Y, this->BottomPos[0].H, true);
		GFX::DrawCornerEdge(false, this->BottomPos[6].X, 25, this->BottomPos[6].H, true);

		if (this->List.size() > 0) {
			for(int Idx = 0; Idx < ENTRIES_PER_SCREEN && Idx < (int)this->List.size(); Idx++) {
				Gui::Draw_Rect(this->BottomPos[1 + Idx].X, this->BottomPos[1 + Idx].Y, this->BottomPos[1 + Idx].W, this->BottomPos[1 + Idx].H, (Idx % 2 == 0 ? KBD_KEYPRESSED : KD_KEYUNPRESSED));
			}
		}

		/* BACK. */
		Gui::Draw_Rect(this->BottomPos[7].X, this->BottomPos[7].Y, this->BottomPos[7].W, this->BottomPos[7].H, KBD_KEYPRESSED); // Back Icn.
		Gui::DrawSprite(GFX::Sprites, sprites_back_btn_idx, this->BottomPos[7].X, this->BottomPos[7].Y);
		C3D_FrameEnd(0);

		Pointer::FrameHandle();
		hidScanInput();
		touchPosition T;
		hidTouchRead(&T);
		uint32_t hDown = hidKeysDown();
		uint32_t hHeld = hidKeysHeld();
		uint32_t hRepeat = hidKeysDownRepeat();
		Pointer::ScrollHandle(hHeld);

		if (hRepeat & KEY_R) this->NextPage();
		if (hRepeat & KEY_L) this->PrevPage();
		if (hDown & KEY_B) this->BCall();

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

		/* ScreenPos handle. */
		if (this->Browse->GetSelectedIndex() < this->ScreenPos) this->ScreenPos = this->Browse->GetSelectedIndex();
		else if (this->Browse->GetSelectedIndex() > this->ScreenPos + ENTRIES_PER_SCREEN - 1) this->ScreenPos = this->Browse->GetSelectedIndex() - ENTRIES_PER_SCREEN + 1;
	}

	Pointer::OnTop = false;
	Pointer::SetPos(0, 0);
	return this->Res;
}