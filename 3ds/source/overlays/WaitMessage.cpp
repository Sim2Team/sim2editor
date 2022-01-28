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
#include "WaitMessage.hpp"


WaitMessage::WaitMessage(const std::string &Msg) { this->Msgs.push_back(Msg); }

void WaitMessage::OK() { this->Done = true; } // Set OK.

void WaitMessage::PrevMsg() { // Go to previous Message.
	if (!this->MMessages) return;

	if (this->MsgPage > 0) this->MsgPage--;
}

void WaitMessage::NextMsg() { // Go to next Message.
	if (!this->MMessages) return;

	if (this->MsgPage < (int)this->Msgs.size() - 1) this->MsgPage++;
}


void WaitMessage::Action() {
	Pointer::OnTop = true;
	Pointer::SetPos(this->Positions[1]);

	while(!this->Done) {
		Gui::clearTextBufs();
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(Top, C2D_Color32(0, 0, 0, 0));
		C2D_TargetClear(Bottom, C2D_Color32(0, 0, 0, 0));
		GFX::DrawTop();

		if (this->MMessages) Gui::DrawStringCentered(0, 3, 0.6f, TEXT_COLOR, "Message " + std::to_string(this->MsgPage + 1) + " / " + std::to_string(this->Msgs.size()));

		/* Message Box with message + OK. */
		GFX::DrawMsgBox(10, 37, 380, 191);
		Gui::DrawStringCentered(0, 57, 0.48f, TEXT_COLOR, this->Msgs[this->MsgPage], 330, 110, nullptr, C2D_WordWrap);
		Gui::Draw_Rect(this->Positions[1].X, this->Positions[1].Y, this->Positions[1].W, this->Positions[1].H, CORNER_COLOR);
		Gui::DrawString(this->Positions[1].X + 41, this->Positions[1].Y + 2, 0.5f, TEXT_COLOR, "OK");

		/* Arrows for the sides. */
		if (this->MMessages) {
			Gui::DrawSprite(GFX::Sprites, sprites_arrow_idx, this->Positions[0].X + 5, this->Positions[0].Y + ((this->Positions[0].H / 2) - (39 / 2)));
			Gui::DrawSprite(GFX::Sprites, sprites_arrow_idx, this->Positions[2].X, this->Positions[2].Y + ((this->Positions[2].H / 2) - (39 / 2)), -1.0f, 1.0f);
		}

		Pointer::Draw();
		GFX::DrawBottom();

		GFX::DrawCornerEdge(true, this->BottomPos[0].X, this->BottomPos[0].Y, this->BottomPos[0].H, this->MMessages);
		GFX::DrawCornerEdge(false, this->BottomPos[2].X, this->BottomPos[2].Y, this->BottomPos[2].H, this->MMessages);

		Gui::Draw_Rect(95, 105, 130, 30, KD_KEYUNPRESSED);
		Gui::Draw_Rect(this->BottomPos[1].X, this->BottomPos[1].Y, this->BottomPos[1].W, this->BottomPos[1].H, CORNER_COLOR);
		Gui::DrawStringCentered(0, this->BottomPos[1].Y + 3, 0.5f, TEXT_COLOR, "OK"); // OK.


		C3D_FrameEnd(0);
		Pointer::FrameHandle();

		hidScanInput();
		touchPosition T;
		hidTouchRead(&T);
		uint32_t hDown = hidKeysDown();
		uint32_t hHeld = hidKeysHeld();
		Pointer::ScrollHandle(hHeld);

		if (this->MMessages) {
			if (hDown & KEY_L) this->PrevMsg();
			if (hDown & KEY_R) this->NextMsg();
		}

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
	}

	Pointer::OnTop = false;
	Pointer::SetPos(0, 0);
}