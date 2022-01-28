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
#include "GBAHouseEditor.hpp"
#include "ListSelection.hpp"
#include "PromptMessage.hpp"
#include "Strings.hpp"


/* Go back. */
void GBAHouseEditor::Back() {
	this->Exit = true;
	Gui::screenBack();
	return;
}


/*
	Init an Item for the Input Labels.

	const bool AddItem: If it's on add mode or not.
*/
void GBAHouseEditor::InitItem(const bool AddMode) {
	this->InputLabels.clear(); // Clear first.

	/* Flags. */
	this->InputLabels.push_back(std::make_unique<NumInputLabel<uint8_t>>(190, 60, (AddMode ? this->AddFlag : this->Items->Flag(this->Selection)), 0, 255, "Enter the Flags of the Item in Decimal."));
	/* Use Count. */
	this->InputLabels.push_back(std::make_unique<NumInputLabel<uint8_t>>(190, 90, (AddMode ? this->AddUseCount : this->Items->UseCount(this->Selection)), 0, 255, "Enter the Use Count of the Item."));
	/* X-Position. */
	this->InputLabels.push_back(std::make_unique<NumInputLabel<uint8_t>>(190, 120, (AddMode ? this->AddX : this->Items->XPos(this->Selection)), 0, 255, "Enter the X-Position of the Item."));
	/* Y-Position. */
	this->InputLabels.push_back(std::make_unique<NumInputLabel<uint8_t>>(190, 150, (AddMode ? this->AddY : this->Items->YPos(this->Selection)), 0, 255, "Enter the Y-Position of the Item."));
}


/* Go to the Editing Tab. Also Init the Selected Item. */
void GBAHouseEditor::EditingTab() {
	this->Tab = Tabs::Editing;
	this->InitItem(false);
}

/* Go to the Adding Tab. Also Init the Adding Item. */
void GBAHouseEditor::AddTab() {
	this->Tab = Tabs::Add;
	this->InitItem(true);
}

/* Remove the Selected Item, if on Editing Tab. */
void GBAHouseEditor::RemoveTab() {
	if ((this->Tab == Tabs::Editing) && (this->Items->Count() > 0)) {
		std::unique_ptr<PromptMessage> Ovl = std::make_unique<PromptMessage>("Would you like to remove the current Item?");
		const bool Answer = Ovl->Action();

		if (Answer) {
			this->Items->RemoveItem(this->Selection);
			if (this->Selection > 0) this->Selection--;
			this->InitItem(true);
		}
	}
}


/*
	Select an Item from a List.

	const bool AddItem: If it's on add mode or not.
*/
void GBAHouseEditor::SelectItemID(const bool AddMode) {
	std::unique_ptr<ListSelection> Ovl = std::make_unique<ListSelection>(S2Core::Strings::GBAItemNames_EN, "Select an Item.", (AddMode ? this-> AddID : this->Items->ID(this->Selection)));
	const uint8_t ID = Ovl->Action();

	if (ID != (AddMode ? this->AddID : this->Items->ID(this->Selection))) {
		if (AddMode) this->AddID = ID;
		else this->Items->ID(this->Selection, ID);
	}
}


/*
	Select a Direction for the Item.

	const bool AddItem: If it's on add mode or not.
*/
void GBAHouseEditor::SelectItemDirection(const bool AddMode) {
	const std::vector<std::string> Tmp = { "Right", "Down", "Left", "Up", "Invalid" };

	std::unique_ptr<ListSelection> Ovl = std::make_unique<ListSelection>(Tmp, "Select a Direction.", this->DirectionInt((AddMode ? this->AddDirection : this->Items->Direction(this->Selection))));
	const uint8_t Direction = Ovl->Action();

	if (Direction != (AddMode ? this-> AddID : this->Items->ID(this->Selection))) {
		S2Core::GBAHouseItemDirection Dir = S2Core::GBAHouseItemDirection::Invalid;

		switch(Direction) {
			case 0:
				Dir = S2Core::GBAHouseItemDirection::Right;
				break;

			case 1:
				Dir = S2Core::GBAHouseItemDirection::Down;
				break;

			case 2:
				Dir = S2Core::GBAHouseItemDirection::Left;
				break;

			case 3:
				Dir = S2Core::GBAHouseItemDirection::Up;
				break;

			case 4:
				Dir = S2Core::GBAHouseItemDirection::Invalid;
				break;
		}


		if (AddMode) this->AddDirection = Dir;
		else this->Items->Direction(this->Selection, Dir);
	}
}


/* Select an Item from the Room List. */
void GBAHouseEditor::SelectItem() {
	std::vector<std::string> ITMs;
	std::vector<bool> ITMsExist;

	for (uint8_t Idx = 0; Idx < 12; Idx++) {
		if (Idx < this->Items->Count()) {
			ITMs.push_back(S2Core::Strings::GBAItemNames_EN[this->Items->ID(Idx)]);
			ITMsExist.push_back(true);

		} else {
			ITMs.push_back("Don't Exist");
			ITMsExist.push_back(false);
		}
	}

	std::unique_ptr<ListSelection> Ovl = std::make_unique<ListSelection>(ITMs, "Select an Item you like to edit.", this->Selection);
	const uint8_t ITM = Ovl->Action();

	if (ITMsExist[ITM]) {
		this->Selection = ITM;
		this->InitItem(false);
	}
}


/* Add the Added Item to the Room. */
void GBAHouseEditor::AddItem() {
	if (this->Items->Count() < 12) {
		std::unique_ptr<PromptMessage> Ovl = std::make_unique<PromptMessage>("Would you like to add this item?");
		if (Ovl->Action()) this->Items->AddItem(this->AddID, this->AddFlag, this->AddUseCount, this->AddX, this->AddY, this->AddDirection);
	}
}


/*
	Returns the Direction as an Integer.

	const S2Core::GBAHouseItemDirection V: The Direction.
*/
uint8_t GBAHouseEditor::DirectionInt(const S2Core::GBAHouseItemDirection V) const {
	switch(V) {
		case S2Core::GBAHouseItemDirection::Right:
			return 0;

		case S2Core::GBAHouseItemDirection::Down:
			return 1;

		case S2Core::GBAHouseItemDirection::Left:
			return 2;

		case S2Core::GBAHouseItemDirection::Up:
			return 3;

		case S2Core::GBAHouseItemDirection::Invalid:
			return 4;
	}

	return 4;
}


/*
	Returns the Direction as a String.

	const S2Core::GBAHouseItemDirection V: The Direction.
*/
std::string GBAHouseEditor::Direction(const S2Core::GBAHouseItemDirection V) const {
	switch(V) {
		case S2Core::GBAHouseItemDirection::Right:
			return "Right";

		case S2Core::GBAHouseItemDirection::Down:
			return "Down";

		case S2Core::GBAHouseItemDirection::Left:
			return "Left";

		case S2Core::GBAHouseItemDirection::Up:
			return "Up";

		case S2Core::GBAHouseItemDirection::Invalid:
			return "Invalid";
	}

	return "Invalid";
}


/*
	Updates the Labels to the core.

	const uint8_t C: The Category.
*/
void GBAHouseEditor::ValueUpdate(const uint8_t C) {
	if (this->Tab == Tabs::Editing) { // Editing Mode.
		switch(C) {
			case 0:
				this->Items->Flag(this->Selection, this->InputLabels[0]->GetVal());
				break;

			case 1:
				this->Items->UseCount(this->Selection, this->InputLabels[1]->GetVal());
				break;

			case 2:
				this->Items->XPos(this->Selection, this->InputLabels[2]->GetVal());
				break;

			case 3:
				this->Items->YPos(this->Selection, this->InputLabels[3]->GetVal());
				break;
		}

	} else if (this->Tab == Tabs::Add) { // Adding Mode.
		switch(C) {
			case 0:
				this->AddFlag = this->InputLabels[0]->GetVal();
				break;

			case 1:
				this->AddUseCount = this->InputLabels[1]->GetVal();
				break;

			case 2:
				this->AddX = this->InputLabels[2]->GetVal();
				break;

			case 3:
				this->AddY = this->InputLabels[3]->GetVal();
				break;
		}
	}
}


/* Main Draw. */
void GBAHouseEditor::Draw(void) const {
	GFX::DrawTop();
	Gui::DrawStringCentered(0, 3, 0.6f, TEXT_COLOR, "GBA House Editor");
	GFX::DrawBottom();

	/* Draw Tabs. */
	Gui::Draw_Rect(1, 0, 106, 20, (this->Tab == Tabs::Editing ? KBD_KEYPRESSED : KD_KEYUNPRESSED));
	Gui::Draw_Rect(107, 0, 106, 20, (this->Tab == Tabs::Add ? KBD_KEYPRESSED : KD_KEYUNPRESSED));
	Gui::Draw_Rect(213, 0, 106, 20, (this->Tab == Tabs::Remove ? KBD_KEYPRESSED : KD_KEYUNPRESSED));
	Gui::DrawString(1 + 34, 3, 0.45f, TEXT_COLOR, "Editing");
	Gui::DrawString(107 + 28, 3, 0.45f, TEXT_COLOR, "Add Item");
	Gui::DrawString(213 + 17, 3, 0.45f, TEXT_COLOR, "Remove Item");

	switch(this->Tab) {
		case Tabs::Editing:
			Gui::DrawString(30, 34 + (0 * 30), 0.5f, TEXT_COLOR, S2Core::Strings::GBAItemNames_EN[this->Items->ID(this->Selection)], 150);
			Gui::DrawSprite(GFX::Sprites, sprites_stripe_idx, this->EditPositions[3].X, this->EditPositions[3].Y);

			Gui::DrawString(30, 34 + (1 * 30), 0.5f, TEXT_COLOR, "Item Flags ", 150);
			Gui::DrawString(30, 34 + (2 * 30), 0.5f, TEXT_COLOR, "Item Use Count ", 150);
			Gui::DrawString(30, 34 + (3 * 30), 0.5f, TEXT_COLOR, "Item X Position ", 150);
			Gui::DrawString(30, 34 + (4 * 30), 0.5f, TEXT_COLOR, "Item Y Position ", 150);
			Gui::DrawString(30, 34 + (5 * 30), 0.5f, TEXT_COLOR, "Item Direction: " + this->Direction(this->Items->Direction(this->Selection)), 150);
			Gui::DrawSprite(GFX::Sprites, sprites_stripe_idx, this->EditPositions[4].X, this->EditPositions[4].Y);
			for (auto &Label : this->InputLabels) Label->Draw();

			Gui::Draw_Rect(this->EditPositions[5].X, this->EditPositions[5].Y, this->EditPositions[5].W, this->EditPositions[5].H, KBD_KEYPRESSED); // Item Icn.
			Gui::DrawSprite(GFX::Sprites, sprites_item_btn_idx, this->EditPositions[5].X, this->EditPositions[5].Y + 4);
			break;

		case Tabs::Add:
			Gui::DrawString(30, 34 + (0 * 30), 0.5f, TEXT_COLOR, S2Core::Strings::GBAItemNames_EN[this->AddID], 150);
			Gui::DrawSprite(GFX::Sprites, sprites_stripe_idx, this->EditPositions[3].X, this->EditPositions[3].Y);

			Gui::DrawString(30, 34 + (1 * 30), 0.5f, TEXT_COLOR, "Item Flags ", 150);
			Gui::DrawString(30, 34 + (2 * 30), 0.5f, TEXT_COLOR, "Item Use Count ", 150);
			Gui::DrawString(30, 34 + (3 * 30), 0.5f, TEXT_COLOR, "Item X Position ", 150);
			Gui::DrawString(30, 34 + (4 * 30), 0.5f, TEXT_COLOR, "Item Y Position ", 150);
			Gui::DrawString(30, 34 + (5 * 30), 0.5f, TEXT_COLOR, "Item Direction: " + this->Direction(this->AddDirection), 150);
			Gui::DrawSprite(GFX::Sprites, sprites_stripe_idx, this->EditPositions[4].X, this->EditPositions[4].Y);
			for (auto &Label : this->InputLabels) Label->Draw();

			Gui::Draw_Rect(this->AddPositions[5].X, this->AddPositions[5].Y, this->AddPositions[5].W, this->AddPositions[5].H, KBD_KEYPRESSED);
			Gui::DrawStringCentered(0, this->AddPositions[5].Y + 4, 0.5f, TEXT_COLOR, "Add Item to Room", 150);
			break;

		case Tabs::Remove:
			break;
	}

	Gui::Draw_Rect(this->EditPositions[6].X, this->EditPositions[6].Y, this->EditPositions[6].W, this->EditPositions[6].H, KBD_KEYPRESSED); // Back Icn.
	Gui::DrawSprite(GFX::Sprites, sprites_back_btn_idx, this->EditPositions[6].X, this->EditPositions[6].Y);
	Pointer::Draw();
}


/* The Editing Logic. */
void GBAHouseEditor::EditLogic(uint32_t hDown, uint32_t hHeld, touchPosition touch) {
	uint32_t hRepeat = hidKeysDownRepeat();

	if (hDown & KEY_A) {
		bool Pressed = false;

		for (auto &Pos : this->EditPositions) {
			if (Pointer::Callback(Pos, true)) {
				Pressed = true;
				break;
			}
		}

		if (!Pressed) {
			for (uint8_t Idx = 0; Idx < 4; Idx++) {
				if (this->InputLabels[Idx]->CallbackA()) {
					this->ValueUpdate(Idx);
					break;
				}
			}
		}
	}

	if (hRepeat & KEY_A) {
		if (this->Exit) return;

		for (uint8_t Idx = 0; Idx < 4; Idx++) {
			if (this->InputLabels[Idx]->CallbackAmountA()) {
				this->ValueUpdate(Idx);
				break;
			}
		}
	}

	if (hDown & KEY_TOUCH) {
		bool Pressed = false;

		for (auto &Pos : this->EditPositions) {
			if (Touching(Pos, touch, true)) {
				Pressed = true;
				break;
			}
		}

		if (!Pressed) {
			for (uint8_t Idx = 0; Idx < 4; Idx++) {
				if (this->InputLabels[Idx]->CallbackTouch(touch)) {
					this->ValueUpdate(Idx);
					break;
				}
			}
		}
	}

	if (hRepeat & KEY_TOUCH) {
		if (this->Exit) return;

		for (uint8_t Idx = 0; Idx < 4; Idx++) {
			if (this->InputLabels[Idx]->CallbackAmountTouch(touch)) {
				this->ValueUpdate(Idx);
				break;
			}
		}
	}
}


/* Adding Logic. */
void GBAHouseEditor::AddLogic(uint32_t hDown, uint32_t hHeld, touchPosition touch) {
	uint32_t hRepeat = hidKeysDownRepeat();

	if (hDown & KEY_A) {
		bool Pressed = false;

		for (auto &Pos : this->AddPositions) {
			if (Pointer::Callback(Pos, true)) {
				Pressed = true;
				break;
			}
		}

		if (!Pressed) {
			for (uint8_t Idx = 0; Idx < 4; Idx++) {
				if (this->InputLabels[Idx]->CallbackA()) {
					this->ValueUpdate(Idx);
					break;
				}
			}
		}
	}

	if (hRepeat & KEY_A) {
		if (this->Exit) return;

		for (uint8_t Idx = 0; Idx < 4; Idx++) {
			if (this->InputLabels[Idx]->CallbackAmountA()) {
				this->ValueUpdate(Idx);
				break;
			}
		}
	}

	if (hDown & KEY_TOUCH) {
		bool Pressed = false;

		for (auto &Pos : this->AddPositions) {
			if (Touching(Pos, touch, true)) {
				Pressed = true;
				break;
			}
		}

		if (!Pressed) {
			for (uint8_t Idx = 0; Idx < 4; Idx++) {
				if (this->InputLabels[Idx]->CallbackTouch(touch)) {
					this->ValueUpdate(Idx);
					break;
				}
			}
		}
	}

	if (hRepeat & KEY_TOUCH) {
		if (this->Exit) return;

		for (uint8_t Idx = 0; Idx < 4; Idx++) {
			if (this->InputLabels[Idx]->CallbackAmountTouch(touch)) {
				this->ValueUpdate(Idx);
				break;
			}
		}
	}
}


/* Main Logic. */
void GBAHouseEditor::Logic(uint32_t hDown, uint32_t hHeld, touchPosition touch) {
	Pointer::FrameHandle();
	Pointer::ScrollHandle(hHeld);

	switch(this->Tab) {
		case Tabs::Editing:
			this->EditLogic(hDown, hHeld, touch);
			break;

		case Tabs::Add:
			this->AddLogic(hDown, hHeld, touch);
			break;

		case Tabs::Remove: // DO nothing.
			break;
	}

	if (hDown & KEY_B) this->Back();
}