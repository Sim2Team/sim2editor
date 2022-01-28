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
#include "KBD.hpp"


/* Draw the Keyboard. */
void KBD::Draw() const {
	/* Draw Upper + Lower. */
	for (uint8_t Idx = 0; Idx < 2; Idx++) {
		Gui::Draw_Rect(this->SpecialKeysFunc[Idx].X, this->SpecialKeysFunc[Idx].Y, this->SpecialKeysFunc[Idx].W, this->SpecialKeysFunc[Idx].H, (!this->Upper == Idx ? KBD_KEYPRESSED : KD_KEYUNPRESSED));
		Gui::DrawString(this->SpecialKeysFunc[Idx].X + 35, this->SpecialKeysFunc[Idx].Y + 3, 0.7f, TEXT_COLOR, this->SpecialKeys[Idx]);
	}

	/* Draw Keys. */
	for (uint8_t Idx = 0; Idx < this->Layout.size(); Idx++) {
		Gui::Draw_Rect(this->Layout[Idx].X, this->Layout[Idx].Y, this->Layout[Idx].W, this->Layout[Idx].H, KD_KEYUNPRESSED);
		Gui::DrawString(this->Layout[Idx].X + 15, this->Layout[Idx].Y + 5, 0.6f, TEXT_COLOR, (this->Upper ? this->ABCKeys[Idx] : this->abcKeys[Idx]));
	}

	/* Draw Back and Confirm. */
	for (uint8_t Idx = 0; Idx < 2; Idx++) {
		Gui::Draw_Rect(this->SpecialKeysFunc[2 + Idx].X, this->SpecialKeysFunc[2 + Idx].Y, this->SpecialKeysFunc[2 + Idx].W, this->SpecialKeysFunc[2].H, KD_KEYUNPRESSED);
		Gui::DrawString(this->SpecialKeysFunc[2 + Idx].X + 5, this->SpecialKeysFunc[2 + Idx].Y + 5, 0.6f, TEXT_COLOR, this->SpecialKeys[2 + Idx]);
	}
}


/*
	Insert a Character.

	const int Idx: The Index of the character.
*/
void KBD::InputChar(const int Idx) const {
	if ((int)this->Res.size() < this->MaxLength) this->Res += (this->Upper ? this->ABCKeys[Idx] : this->abcKeys[Idx]);
}


/* Upper and Lower Tab. */
void KBD::UpperTab() const { this->Upper = true; }
void KBD::LowerTab() const { this->Upper = false; }


/* Removes the last character if not empty. */
void KBD::RemoveChar() const {
	if (!this->Res.empty()) this->Res.pop_back();
}


/* Set status to done. */
void KBD::Confirm() const { this->Done = true; }


std::string KBD::Action() const {
	Pointer::OnTop = false;
	Pointer::SetPos(this->Layout[0]);

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

		Pointer::FrameHandle();
		touchPosition t;
		hidScanInput();
		uint32_t hDown = hidKeysDown();
		uint32_t hHeld = hidKeysHeld();
		hidTouchRead(&t);
		Pointer::ScrollHandle(hHeld);

		if (hDown & KEY_A) {
			bool pressed = false;

			for (auto &Position : this->Layout) {
				if (Pointer::Callback(Position, true)) {
					pressed = true;
					break;
				}
			}

			if (!pressed) {
				for (auto &Position : this->SpecialKeysFunc) {
					if (Pointer::Callback(Position, true)) break;
				}
			}
		}

		if (hDown & KEY_TOUCH) {
			bool pressed = false;

			for (auto &Position : this->Layout) {
				if (Touching(Position, t, true)) {
					pressed = true;
					break;
				}
			}

			if (!pressed) {
				for (auto &Position : this->SpecialKeysFunc) {
					if (Touching(Position, t, true)) break;
				}
			}
		}
	}

	Pointer::SetPos(0, 0);
	return this->Res;
}