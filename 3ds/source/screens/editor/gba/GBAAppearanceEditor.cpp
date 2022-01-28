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
#include "GBAColorSelection.hpp"
#include "GBAAppearanceEditor.hpp"
#include "GBAHairSelection.hpp"
#include "GBAPantsSelection.hpp"
#include "GBAShirtSelection.hpp"


GBAAppearanceEditor::GBAAppearanceEditor(std::shared_ptr<S2Core::GBASlot> &Slot) : Slot(Slot) { }


/* Goes back to the Slot Editor. */
void GBAAppearanceEditor::Back() {
	Gui::screenBack();
	return;
}


/* Select Shoe / Hat Color. */
void GBAAppearanceEditor::SelectShoeHatColor() {
	std::unique_ptr<GBAColorSelection> Ovl = std::make_unique<GBAColorSelection>("Select a Shoe / Hat color.", false);
	const int8_t Res = Ovl->Action();
	if (Res != -1) this->Slot->Hatcolor(Res);
}


/* Select Hairstyle. */
void GBAAppearanceEditor::SelectHair()  {
	std::unique_ptr<GBAHairSelection> Ovl = std::make_unique<GBAHairSelection>(this->Slot->Hairstyle());
	const int8_t Res = Ovl->Action();
	if (Res != -1) this->Slot->Hairstyle(Res);
}


/* Select Haircolor. */
void GBAAppearanceEditor::SelectHaircolor() {
	std::unique_ptr<GBAColorSelection> Ovl = std::make_unique<GBAColorSelection>("Select a Haircolor.", false, this->Slot->Haircolor());
	const int8_t Res = Ovl->Action();
	if (Res != -1) this->Slot->Haircolor(Res);
}


/* Select Shirttype. */
void GBAAppearanceEditor::SelectShirt() {
	std::unique_ptr<GBAShirtSelection> Ovl = std::make_unique<GBAShirtSelection>(this->Slot->Shirt());
	const int8_t Res = Ovl->Action();
	if (Res != -1) this->Slot->Shirt(Res);
}


/* Select Shirt Body color. */
void GBAAppearanceEditor::SelectShirtcolor1() {
	std::unique_ptr<GBAColorSelection> Ovl = std::make_unique<GBAColorSelection>("Select the first Shirt Color.", true, this->Slot->Shirtcolor1());
	const int8_t Res = Ovl->Action();
	if (Res != -1) this->Slot->Shirtcolor1(Res);
}


/* Select Shirt short sleeve color. */
void GBAAppearanceEditor::SelectShirtcolor2() {
	std::unique_ptr<GBAColorSelection> Ovl = std::make_unique<GBAColorSelection>("Select the second Shirt Color.", true, this->Slot->Shirtcolor2());
	const int8_t Res = Ovl->Action();
	if (Res != -1) this->Slot->Shirtcolor2(Res);
}


/* Select Shirt long sleeve color. */
void GBAAppearanceEditor::SelectShirtcolor3() {
	std::unique_ptr<GBAColorSelection> Ovl = std::make_unique<GBAColorSelection>("Select the third Shirt Color.", true, this->Slot->Shirtcolor3());
	const int8_t Res = Ovl->Action();
	if (Res != -1) this->Slot->Shirtcolor3(Res);
}


/* Select Pantstype. */
void GBAAppearanceEditor::SelectPants() {
	std::unique_ptr<GBAPantsSelection> Ovl = std::make_unique<GBAPantsSelection>(this->Slot->Pants(), this->Slot->Hairstyle() > 3);
	const int8_t Res = Ovl->Action();
	if (Res != -1) this->Slot->Pants(Res);
}


/* Select Pantscolor. */
void GBAAppearanceEditor::SelectPantsColor() {
	std::unique_ptr<GBAColorSelection> Ovl = std::make_unique<GBAColorSelection>("Select the Pants color.", true, this->Slot->Pantscolor());
	const int8_t Res = Ovl->Action();
	if (Res != -1) this->Slot->Pantscolor(Res);
}


void GBAAppearanceEditor::Draw(void) const {
	GFX::DrawTop();
	Gui::DrawStringCentered(0, 3, 0.6f, TEXT_COLOR, "GBA Appearance Editor");

	/* Draw some bit on the top screen, to not make it look empty. */
	Gui::DrawString(10, 45, 0.5f, TEXT_COLOR, "Hairstyle: ");
	Gui::DrawSprite(GFX::Appearance, this->Slot->Hairstyle(), 70, 30, 0.5f, 0.5f); // Hairstyle.

	Gui::DrawString(10, 100, 0.5f, TEXT_COLOR, "Hatcolor: ");
	Gui::Draw_Rect(90, 100, 20, 20, GBAColorSelection::_16Color[this->Slot->Hatcolor()]); // Hatcolor.

	Gui::DrawString(10, 140, 0.5f, TEXT_COLOR, "Haircolor: ");
	Gui::Draw_Rect(90, 140, 20, 20, GBAColorSelection::_16Color[this->Slot->Haircolor()]); // Haircolor.


	Gui::DrawString(140, 45, 0.5f, TEXT_COLOR, "Shirt: ");
	Gui::DrawSprite(GFX::Appearance, 11 + this->Slot->Shirt(), 200, 30, 0.5f, 0.5f); // Shirtstyle.

	Gui::DrawString(140, 100, 0.5f, TEXT_COLOR, "Shirtcolor 1: ");
	Gui::Draw_Rect(220, 100, 20, 20, GBAColorSelection::_32Color[this->Slot->Shirtcolor1()]); // Shirt color 1 (Body).

	Gui::DrawString(140, 140, 0.5f, TEXT_COLOR, "Shirtcolor 2: ");
	Gui::Draw_Rect(220, 140, 20, 20, GBAColorSelection::_32Color[this->Slot->Shirtcolor2()]); // Shirt color 2 (Short sleeve).

	Gui::DrawString(140, 180, 0.5f, TEXT_COLOR, "Shirtcolor 3: ");
	Gui::Draw_Rect(220, 180, 20, 20, GBAColorSelection::_32Color[this->Slot->Shirtcolor3()]); // Shirt color 3 (Long sleeve).


	Gui::DrawString(280, 45, 0.5f, TEXT_COLOR, "Pants: ");
	/* Exception for the Pants Images (Female / Male). */
	if (this->Slot->Hairstyle() > 3) { // Female.
		Gui::DrawSprite(GFX::Appearance, 8 + (this->Slot->Pants() ? 2 : 0), 340, 30, 0.6f, 0.6f); // Pants.

	} else { // Male.
		Gui::DrawSprite(GFX::Appearance, 8 + (this->Slot->Pants() ? 1 : 0), 340, 30, 0.6f, 0.6f); // Pants.
	}

	Gui::DrawString(280, 140, 0.5f, TEXT_COLOR, "Pantscolor: ");
	Gui::Draw_Rect(360, 140, 20, 20, GBAColorSelection::_32Color[this->Slot->Pantscolor()]); // Pants color.

	GFX::DrawBottom();

	/* Draw Tabs. */
	Gui::Draw_Rect(1, 0, 106, 20, (this->Tab == Tabs::Head ? KBD_KEYPRESSED : KD_KEYUNPRESSED));
	Gui::Draw_Rect(107, 0, 106, 20, (this->Tab == Tabs::Shirt ? KBD_KEYPRESSED : KD_KEYUNPRESSED));
	Gui::Draw_Rect(213, 0, 106, 20, (this->Tab == Tabs::Pants ? KBD_KEYPRESSED : KD_KEYUNPRESSED));
	Gui::DrawString(1 + 40, 3, 0.45f, TEXT_COLOR, "Head");
	Gui::DrawString(107 + 40, 3, 0.45f, TEXT_COLOR, "Shirt");
	Gui::DrawString(213 + 33, 3, 0.45f, TEXT_COLOR, "Pants");

	switch(this->Tab) {
		case Tabs::Head:
				Gui::DrawString(30, this->HeadPosition[3].Y + 5, 0.4f, TEXT_COLOR, "Hairstyle");
				Gui::DrawString(30, this->HeadPosition[4].Y + 5, 0.4f, TEXT_COLOR, "Hat / Shoe Color");
				Gui::DrawString(30, this->HeadPosition[5].Y + 5, 0.4f, TEXT_COLOR, "Haircolor");

				for (uint8_t Idx = 0; Idx < 3; Idx++) {
					Gui::DrawSprite(GFX::Sprites, sprites_stripe_idx, this->HeadPosition[3 + Idx].X, this->HeadPosition[3 + Idx].Y);
				}
			break;

		case Tabs::Shirt:
				Gui::DrawString(30, this->ShirtPosition[3].Y + 5, 0.4f, TEXT_COLOR, "Shirt style");
				Gui::DrawString(30, this->ShirtPosition[4].Y + 5, 0.4f, TEXT_COLOR, "Shirt Body color");
				Gui::DrawString(30, this->ShirtPosition[5].Y + 5, 0.4f, TEXT_COLOR, "Shirt short sleeve color");
				Gui::DrawString(30, this->ShirtPosition[6].Y + 5, 0.4f, TEXT_COLOR, "Shirt long sleeve color");

				for (uint8_t Idx = 0; Idx < 4; Idx++) {
					Gui::DrawSprite(GFX::Sprites, sprites_stripe_idx, this->ShirtPosition[3 + Idx].X, this->ShirtPosition[3 + Idx].Y);
				}
			break;

		case Tabs::Pants:
				Gui::DrawString(30, this->PantsPosition[3].Y + 5, 0.4f, TEXT_COLOR, "Pants");
				Gui::DrawString(30, this->PantsPosition[4].Y + 5, 0.4f, TEXT_COLOR, "Pantscolor");

				for (uint8_t Idx = 0; Idx < 2; Idx++) {
					Gui::DrawSprite(GFX::Sprites, sprites_stripe_idx, this->PantsPosition[3 + Idx].X, this->PantsPosition[3 + Idx].Y);
				}
			break;
	}

	Gui::Draw_Rect(this->HeadPosition[6].X, this->HeadPosition[6].Y, this->HeadPosition[6].W, this->HeadPosition[6].H, KBD_KEYPRESSED); // Back.
	Gui::DrawSprite(GFX::Sprites, sprites_back_btn_idx, this->HeadPosition[6].X, this->HeadPosition[6].Y);
	Pointer::Draw();
}


void GBAAppearanceEditor::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	Pointer::FrameHandle();
	Pointer::ScrollHandle(hHeld);

	if (hDown & KEY_B) this->Back();

	if (hDown & KEY_A) {
		switch(this->Tab) {
			case Tabs::Head:
				for (auto &Pos : this->HeadPosition) {
					if (Pointer::Callback(Pos, true)) break;
				}
				break;

			case Tabs::Shirt:
				for (auto &Pos : this->ShirtPosition) {
					if (Pointer::Callback(Pos, true)) break;
				}
				break;

			case Tabs::Pants:
				for (auto &Pos : this->PantsPosition) {
					if (Pointer::Callback(Pos, true)) break;
				}
				break;
		}
	}

	if (hDown & KEY_TOUCH) {
		switch(this->Tab) {
			case Tabs::Head:
				for (auto &Pos : this->HeadPosition) {
					if (Touching(Pos, touch, true)) break;
				}
				break;

			case Tabs::Shirt:
				for (auto &Pos : this->ShirtPosition) {
					if (Touching(Pos, touch, true)) break;
				}
				break;

			case Tabs::Pants:
				for (auto &Pos : this->PantsPosition) {
					if (Touching(Pos, touch, true)) break;
				}
				break;
		}
	}
}