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
#include "Numpad.hpp"


/* Draw the Numpad. */
void Numpad::Draw(void) const {
	/* Draw Numbers. */
	for (uint8_t Idx = 0; Idx < 10; Idx++) {
		Gui::Draw_Rect(this->Pad[Idx].X, this->Pad[Idx].Y, this->Pad[Idx].W, this->Pad[Idx].H, KD_KEYUNPRESSED);
		Gui::DrawString(this->Pad[Idx].X + 14, this->Pad[Idx].Y + 7, 0.75f, TEXT_COLOR, this->Nums[Idx]);
	}

	/* Draw Back and Next Buttons. */
	for (uint8_t Idx = 0; Idx < 2; Idx++) {
		Gui::Draw_Rect(this->Pad[10 + Idx].X, this->Pad[10 + Idx].Y, this->Pad[10 + Idx].W, this->Pad[10 + Idx].H, KD_KEYUNPRESSED);
		Gui::DrawString(this->Pad[10 + Idx].X + 5, this->Pad[10 + Idx].Y + 5, 0.6f, TEXT_COLOR, this->Nums[10 + Idx]);
	}
}


/*
	Insert a Number digit.

	const uint8_t Idx: The index of the Nums vector.
*/
void Numpad::InputNum(const uint8_t Idx) const {
	if ((int)this->Res.size() < this->MaxLength) this->Res += this->Nums[Idx];
}


/* Remove the last digit. */
void Numpad::RemoveNum() const {
	if (!this->Res.empty()) this->Res.pop_back();
}


void Numpad::Confirm() const { this->Done = true; } // Confirm.


int Numpad::Action() const {
	Pointer::OnTop = false;
	Pointer::SetPos(this->Pad[0]);

	while(!this->Done) {
		/* Drawing part. */
		C2D_TargetClear(Top, C2D_Color32(0, 0, 0, 0));
		C2D_TargetClear(Bottom, C2D_Color32(0, 0, 0, 0));
		Gui::clearTextBufs();
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		GFX::DrawTop();

		Gui::DrawStringCentered(0, 3, 0.6f, TEXT_COLOR, this->Text);
		Gui::Draw_Rect(0, 215, 400, 25, BAR_COLOR);
		Gui::DrawStringCentered(0, 218, 0.6f, TEXT_COLOR, this->Res);

		GFX::DrawBottom();
		this->Draw();
		Pointer::Draw();
		C3D_FrameEnd(0);

		Pointer::FrameHandle(); // Handle Pointer anim.
		touchPosition t;
		hidScanInput();
		uint32_t hDown = hidKeysDown();
		uint32_t hHeld = hidKeysHeld();
		hidTouchRead(&t);

		/* Navigation. */
		Pointer::ScrollHandle(hHeld);

		if (hDown & KEY_A) {
			for (auto &Position : this->Pad) {
				if (Pointer::Callback(Position, true)) break;
			}
		}

		if (hDown & KEY_TOUCH) {
			for (auto &Position : this->Pad) {
				if (Touching(Position, t, true)) break;
			}
		}
	}

	Pointer::SetPos(0, 0);
	this->FinalRes = std::atoi(this->Res.c_str()); // Convert that string into an Int.
	if (this->FinalRes > this->MaxVal) return this->OldNum;
	else return this->FinalRes;
}