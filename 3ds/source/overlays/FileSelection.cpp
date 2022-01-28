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

#define ENTRIES_PER_SCREEN 5


FileSelection::FileSelection(const std::string &StartPath, const std::vector<std::string> &Ext, const std::string &Text, const bool ReturnPath, const bool DirSelect) : Text(Text), ReturnPath(ReturnPath), DirSelect(DirSelect) {
	if (this->DirSelect) this->Browse = std::make_unique<Browser>(StartPath, std::vector<std::string>({ "/" }));
	else 				 this->Browse = std::make_unique<Browser>(StartPath, Ext);

	this->Files = this->Browse->GetList();
}


/* Pages. */
void FileSelection::PrevPage() const { this->Browse->Left(ENTRIES_PER_SCREEN); }
void FileSelection::NextPage() const { this->Browse->Right(ENTRIES_PER_SCREEN); }


/*
	List Call: Check if Index is valid and if it's a file, return it.

	const int Idx: The Index.
*/
void FileSelection::ListCall(const int Idx) const {
	if (Idx >= (int)this->Files.size()) return;
	if (!this->Browse->SetSelection(this->ScreenPos + Idx)) return;

	if (!this->Browse->OpenHandle()) {
		if (this->Browse->GetSelectedName() != "..") {
			if (!this->DirSelect) {
				this->Res = (this->ReturnPath ? this->Browse->GetSelectedPath() : this->Browse->GetSelectedName());
				this->Done = true;
			}

		} else {
			this->Browse->GoDirBack();
			this->Files = this->Browse->GetList();
		}

	} else {
		this->Browse->GoDirUp();
		this->Files = this->Browse->GetList();
	}
}


/*
	Same as above.. but with Directories.

	const int Idx: The Index.
*/
void FileSelection::DirCall(const int Idx) const {
	if (this->DirSelect) {
		if (Idx >= (int)this->Files.size()) return;

		this->Browse->SetSelection(this->ScreenPos + Idx);

		if (this->Browse->OpenHandle()) {
			this->Res = (this->ReturnPath ? this->Browse->GetSelectedPath() : this->Browse->GetSelectedName());
			this->Done = true;
		}
	}
}


/*
	This is basically a wrapper for the above both functions.
	If the DCall (Directory Call) is true, it checks for Directory, else File, this is needed for the Pointer Callback.

	const int Idx: The Index.
*/
void FileSelection::GetCall(const int Idx) const {
	(this->DCall ? this->DirCall(Idx) : this->ListCall(Idx));
}


/* BCall: The B Button Press call for going Directories back or exit. */
void FileSelection::BCall() const {
	if (this->Browse->CanDirBack()) {
		this->Browse->GoDirBack();
		this->Files = this->Browse->GetList();

	} else {
		this->Res = "!";
		this->Done = true;
	}
}


/* Directory Call Toggle. */
void FileSelection::ToggleDCall() const {
	if (this->DirSelect) this->DCall = !this->DCall;
}


std::string FileSelection::Action() const {
	Pointer::OnTop = true;
	Pointer::SetPos(this->Positions[0]);

	while(!this->Done) {
		Gui::clearTextBufs();
		C2D_TargetClear(Top, C2D_Color32(0, 0, 0, 0));
		C2D_TargetClear(Bottom, C2D_Color32(0, 0, 0, 0));
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		GFX::DrawTop();

		/* Side Edge boxes. */
		GFX::DrawCornerEdge(true, this->Positions[0].X, this->Positions[0].Y, this->Positions[0].H, true);
		GFX::DrawCornerEdge(false, this->Positions[6].X, this->Positions[6].Y, this->Positions[6].H, true);

		/* Display Text + current Path. */
		Gui::DrawStringCentered(0, 3, 0.6f, TEXT_COLOR, this->Text);
		Gui::Draw_Rect(0, 215, 400, 25, BAR_COLOR); // Bottom bar for Path.
		Gui::DrawStringCentered(0, 218, 0.6f, TEXT_COLOR, this->Browse->GetPath());

		if (this->Files.size() > 0) {
			for(int Idx = 0; Idx < ENTRIES_PER_SCREEN && Idx < (int)this->Files.size(); Idx++) {
				Gui::Draw_Rect(this->Positions[1 + Idx].X, this->Positions[1 + Idx].Y, this->Positions[1 + Idx].W, this->Positions[1 + Idx].H, (Idx % 2 == 0 ? KBD_KEYPRESSED : KD_KEYUNPRESSED));
				Gui::DrawStringCentered(0, this->Positions[1 + Idx].Y + 8, 0.5f, TEXT_COLOR, this->Files[this->ScreenPos + Idx], 290);
			}
		}

		Pointer::Draw();
		GFX::DrawBottom();
		/* Side Edge boxes. */
		GFX::DrawCornerEdge(true, this->BottomPos[0].X, this->BottomPos[0].Y, this->BottomPos[0].H, true);
		GFX::DrawCornerEdge(false, this->BottomPos[7].X, 25, this->BottomPos[7].H, true);

		if (this->Files.size() > 0) {
			for(int Idx = 0; Idx < ENTRIES_PER_SCREEN && Idx < (int)this->Files.size(); Idx++) {
				Gui::Draw_Rect(this->BottomPos[1 + Idx].X, this->BottomPos[1 + Idx].Y, this->BottomPos[1 + Idx].W, this->BottomPos[1 + Idx].H, (Idx % 2 == 0 ? KBD_KEYPRESSED : KD_KEYUNPRESSED));
			}
		}

		/* BACK. */
		Gui::Draw_Rect(this->BottomPos[8].X, this->BottomPos[8].Y, this->BottomPos[8].W, this->BottomPos[8].H, KBD_KEYPRESSED); // Back Icn.
		Gui::DrawSprite(GFX::Sprites, sprites_back_btn_idx, this->BottomPos[8].X, this->BottomPos[8].Y);

		if (this->DirSelect) {
			Gui::DrawString(this->BottomPos[6].X - 10, this->BottomPos[6].Y + 3, 0.5f, TEXT_COLOR, "Touch: Directory", 0, 0, nullptr, C2D_AlignRight);
			GFX::DrawCheckbox(this->BottomPos[6].X, this->BottomPos[6].Y, this->DCall);
		}

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
			this->DCall = false;

			for (auto &Position : this->Positions) {
				if (Pointer::Callback(Position, true)) break;
			}
		}

		if (hDown & KEY_TOUCH) {
			for (auto &Position : this->BottomPos) {
				if (Touching(Position, T, true)) break;
			}
		}

		if (hDown & KEY_X || hDown & KEY_START) { // X / START -> Directory Select or so.
			this->DCall = true;

			for (uint8_t Idx = 1; Idx < 6; Idx++) {
				if (Pointer::Callback(this->Positions[Idx], true)) break;
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