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
#include "NDSGeneralEditor.hpp"
#include "Strings.hpp"


/* Initialize the NDSSlot + the Labels. */
NDSGeneralEditor::NDSGeneralEditor(std::shared_ptr<S2Core::NDSSlot> &Slot) : Slot(Slot) {
	/* Init Name Label. */
	this->NameLabel = std::make_unique<StringInputLabel>(140, 40, 8, this->Slot->Name(), "Enter a Sim Name.");
	/* Init Simoleon Label. */
	this->SimoleonLabel = std::make_unique<NumInputLabel<uint32_t>>(140, 80, this->Slot->Simoleons(), 0, 999999, "Enter the Simoleon Amount.");

	/* Init Collectables. - Nuclear Fuelrods. */
	this->CollectableLabels.push_back(std::make_unique<NumInputLabel<uint8_t>>(190, 45, this->Slot->Fuelrods(), 0, 250, "Enter the Nuclear Fuelrods Amount."));

	/* Init Collectables. - License Plates. */
	this->CollectableLabels.push_back(std::make_unique<NumInputLabel<uint8_t>>(190, 95, this->Slot->Plates(), 0, 250, "Enter the License Plates Amount."));

	/* Init Collectables. - Strange Gourduns. */
	this->CollectableLabels.push_back(std::make_unique<NumInputLabel<uint8_t>>(190, 145, this->Slot->Gourds(), 0, 250, "Enter the Strange Gourds Amount."));

	/* Init Collectables. - Alien Spaceship Parts. */
	this->CollectableLabels.push_back(std::make_unique<NumInputLabel<uint8_t>>(190, 195, this->Slot->Spaceship(), 0, 250, "Enter the Alien Spaceship Parts Amount."));

	/* Init Skill point Labels. */
	this->SkillLabels.push_back(std::make_unique<NumInputLabel<uint8_t>>(190, 40, this->Slot->Creativity(), 0, 10, "Enter the Creativity Skill Points."));
	this->SkillLabels.push_back(std::make_unique<NumInputLabel<uint8_t>>(190, 70, this->Slot->Business(), 0, 10, "Enter the Business Skill Points."));
	this->SkillLabels.push_back(std::make_unique<NumInputLabel<uint8_t>>(190, 100, this->Slot->Body(), 0, 10, "Enter the Body Skill Points."));
	this->SkillLabels.push_back(std::make_unique<NumInputLabel<uint8_t>>(190, 130, this->Slot->Charisma(), 0, 10, "Enter the Charisma Skill Points."));
	this->SkillLabels.push_back(std::make_unique<NumInputLabel<uint8_t>>(190, 160, this->Slot->Mechanical(), 0, 10, "Enter the Mechanical Skill Points."));
}


/* Goes back to the Slot Editor. */
void NDSGeneralEditor::Back() {
	this->Exit = true;
	Gui::screenBack();
	return;
}


void NDSGeneralEditor::Draw(void) const {
	GFX::DrawTop();
	Gui::DrawStringCentered(0, 3, 0.6f, TEXT_COLOR, "NDS General Editor");

	GFX::DrawBottom();

	/* Draw Tabs. */
	Gui::Draw_Rect(1, 0, 106, 20, (this->Tab == Tabs::Main ? KBD_KEYPRESSED : KD_KEYUNPRESSED));
	Gui::Draw_Rect(107, 0, 106, 20, (this->Tab == Tabs::Collectables ? KBD_KEYPRESSED : KD_KEYUNPRESSED));
	Gui::Draw_Rect(213, 0, 106, 20, (this->Tab == Tabs::SkillPoints ? KBD_KEYPRESSED : KD_KEYUNPRESSED));
	Gui::DrawString(1 + 40, 3, 0.45f, TEXT_COLOR, "Main");
	Gui::DrawString(107 + 19, 3, 0.45f, TEXT_COLOR, "Collectables");
	Gui::DrawString(213 + 23, 3, 0.45f, TEXT_COLOR, "Skill Points");

	switch(this->Tab) {
		case Tabs::Main:
			Gui::DrawString(120, 39, 0.5f, TEXT_COLOR, "Sim Name: ", 110, 0, nullptr, C2D_AlignRight);
			this->NameLabel->Draw();

			Gui::DrawString(120, 83, 0.5f, TEXT_COLOR, "Simoleons: ", 110, 0, nullptr, C2D_AlignRight);
			this->SimoleonLabel->Draw();
			break;

		case Tabs::Collectables:
			Gui::DrawString(40, 47, 0.5f, TEXT_COLOR, "Nuclear Fuelrods: ");
			Gui::DrawString(40, 97, 0.5f, TEXT_COLOR, "License Plates: ");
			Gui::DrawString(40, 147, 0.5f, TEXT_COLOR, "Strange Gourds: ");
			Gui::DrawString(40, 197, 0.5f, TEXT_COLOR, "Alien Spaceship Parts: ");
			for (auto &Label : this->CollectableLabels) Label->Draw(); // Draw Collectable Labels.
			break;

		case Tabs::SkillPoints:
			for (uint8_t Idx = 0; Idx < 5; Idx++) {
				Gui::DrawString(50, 44 + (Idx * 30), 0.5f, TEXT_COLOR, S2Core::Strings::NDSSkillPointNames_EN[Idx]);
				this->SkillLabels[Idx]->Draw();
			}
			break;
	}

	Gui::Draw_Rect(this->Positions[3].X, this->Positions[3].Y, this->Positions[3].W, this->Positions[3].H, KBD_KEYPRESSED); // Back Icn.
	Gui::DrawSprite(GFX::Sprites, sprites_back_btn_idx, this->Positions[3].X, this->Positions[3].Y);

	Pointer::Draw();
}


/*
	Just a way to not have a whole mess on the KEY_A whatever operations.
	This basically sets the proper things into the Slot.

	const uint8_t Idx: The Index of the Collectable.
*/
void NDSGeneralEditor::CollectableUpdater(const uint8_t Idx) {
	switch(Idx) {
		case 0:
			this->Slot->Fuelrods(this->CollectableLabels[0]->GetVal());
			break;

		case 1:
			this->Slot->Plates(this->CollectableLabels[1]->GetVal());
			break;

		case 2:
			this->Slot->Gourds(this->CollectableLabels[2]->GetVal());
			break;

		case 3:
			this->Slot->Spaceship(this->CollectableLabels[3]->GetVal());
			break;
	}
}


/*
	Just a way to not have a whole mess on the KEY_A whatever operations.
	This basically sets the proper things into the Slot.

	const uint8_t Idx: The Index of the Skillpoint.
*/
void NDSGeneralEditor::SkillUpdater(const uint8_t Idx) {
	switch(Idx) {
		case 0:
			this->Slot->Creativity(this->SkillLabels[0]->GetVal());
			break;

		case 1:
			this->Slot->Business(this->SkillLabels[1]->GetVal());
			break;

		case 2:
			this->Slot->Body(this->SkillLabels[2]->GetVal());
			break;

		case 3:
			this->Slot->Charisma(this->SkillLabels[3]->GetVal());
			break;

		case 4:
			this->Slot->Mechanical(this->SkillLabels[4]->GetVal());
			break;
	}
}


void NDSGeneralEditor::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	Pointer::FrameHandle();
	Pointer::ScrollHandle(hHeld);
	uint32_t hRepeat = hidKeysDownRepeat();

	/* MAIN Tab Logic. */
	if (this->Tab == Tabs::Main) {
		if (hDown & KEY_A) {
			bool Pressed = false;

			for (auto &Pos : this->Positions) {
				if (Pointer::Callback(Pos, true)) {
					Pressed = true;
					break;
				}
			}

			/* Name. */
			if (!Pressed) {
				if (this->NameLabel->CallbackA()) {
					this->Slot->Name(this->NameLabel->GetVal());
					Pressed = true;
				}
			}

			/* Simoleons. */
			if (!Pressed) {
				if (this->SimoleonLabel->CallbackA()) {
					this->Slot->Simoleons(this->SimoleonLabel->GetVal());
					Pressed = true;
				}
			}
		}

		/* NUM Input Labels Only. */
		if (hRepeat & KEY_A) {
			if (this->Exit) return;

			/* Simoleons. */
			if (this->SimoleonLabel->CallbackAmountA()) {
				this->Slot->Simoleons(this->SimoleonLabel->GetVal());
			}
		}

		/* Same for Touch as well now. */
		if (hDown & KEY_TOUCH) {
			bool Pressed = false;

			for (auto &Pos : this->Positions) {
				if (Touching(Pos, touch, true)) {
					Pressed = true;
					break;
				}
			}

			/* Name. */
			if (!Pressed) {
				if (this->NameLabel->CallbackTouch(touch)) {
					this->Slot->Name(this->NameLabel->GetVal());
					Pressed = true;
				}
			}

			/* Simoleons. */
			if (!Pressed) {
				if (this->SimoleonLabel->CallbackTouch(touch)) {
					this->Slot->Simoleons(this->SimoleonLabel->GetVal());
					Pressed = true;
				}
			}
		}

		/* Same for the Minus and Plus buttons as well. */
		if (hRepeat & KEY_TOUCH) {
			if (this->Exit) return;

			/* Simoleons. */
			if (this->SimoleonLabel->CallbackAmountTouch(touch)) this->Slot->Simoleons(this->SimoleonLabel->GetVal());
		}

	/* Collectables Tab. */
	} else if (this->Tab == Tabs::Collectables) {
		if (hDown & KEY_A) {
			bool Pressed = false;

			for (auto &Pos : this->Positions) {
				if (Pointer::Callback(Pos, true)) {
					Pressed = true;
					break;
				}
			}

			if (!Pressed) {
				for (uint8_t Idx = 0; Idx < 4; Idx++) {
					if (this->CollectableLabels[Idx]->CallbackA()) {
						this->CollectableUpdater(Idx);
						break;
					}
				}
			}
		}

		if (hRepeat & KEY_A) {
			if (this->Exit) return;

			for (uint8_t Idx = 0; Idx < 4; Idx++) {
				if (this->CollectableLabels[Idx]->CallbackAmountA()) {
					this->CollectableUpdater(Idx);
					break;
				}
			}
		}

		if (hDown & KEY_TOUCH) {
			bool Pressed = false;

			for (auto &Pos : this->Positions) {
				if (Touching(Pos, touch, true)) {
					Pressed = true;
					break;
				}
			}

			if (!Pressed) {
				for (uint8_t Idx = 0; Idx < 4; Idx++) {
					if (this->CollectableLabels[Idx]->CallbackTouch(touch)) {
						this->CollectableUpdater(Idx);
						break;
					}
				}
			}
		}

		if (hRepeat & KEY_TOUCH) {
			if (this->Exit) return;

			for (uint8_t Idx = 0; Idx < 4; Idx++) {
				if (this->CollectableLabels[Idx]->CallbackAmountTouch(touch)) {
					this->CollectableUpdater(Idx);
					break;
				}
			}
		}

	} else if (this->Tab == Tabs::SkillPoints) {
		if (hDown & KEY_A) {
			bool Pressed = false;

			for (auto &Pos : this->Positions) {
				if (Pointer::Callback(Pos, true)) {
					Pressed = true;
					break;
				}
			}

			if (!Pressed) {
				for (uint8_t Idx = 0; Idx < 5; Idx++) {
					if (SkillLabels[Idx]->CallbackA()) {
						this->SkillUpdater(Idx);
						break;
					}
				}
			}
		}

		/* NUM Input Labels Only. */
		if (hRepeat & KEY_A) {
			if (this->Exit) return;

			for (uint8_t Idx = 0; Idx < 5; Idx++) {
				if (SkillLabels[Idx]->CallbackAmountA()) {
					this->SkillUpdater(Idx);
					break;
				}
			}
		}

		/* Same for Touch as well now. */
		if (hDown & KEY_TOUCH) {
			bool Pressed = false;

			for (auto &Pos : this->Positions) {
				if (Touching(Pos, touch, true)) {
					Pressed = true;
					break;
				}
			}

			if (!Pressed) {
				for (uint8_t Idx = 0; Idx < 5; Idx++) {
					if (SkillLabels[Idx]->CallbackTouch(touch)) {
						this->SkillUpdater(Idx);
						break;
					}
				}
			}
		}

		/* Same for the Minus and Plus buttons as well. */
		if (hRepeat & KEY_TOUCH) {
			if (this->Exit) return;

			for (uint8_t Idx = 0; Idx < 5; Idx++) {
				if (SkillLabels[Idx]->CallbackAmountTouch(touch)) {
					this->SkillUpdater(Idx);
					break;
				}
			}
		}
	}

	if (hDown & KEY_B) this->Back();
	if (hDown & KEY_L) {
		switch(this->Tab) {
			case Tabs::SkillPoints:
				this->CollectableTab();
				break;

			case Tabs::Collectables:
				this->MainTab();
				break;

			case Tabs::Main:
				break;
		}
	}

	if (hDown & KEY_R) {
		switch(this->Tab) {
			case Tabs::Main:
				this->CollectableTab();
				break;

			case Tabs::Collectables:
				this->SkillPointsTab();
				break;

			case Tabs::SkillPoints:
				break;
		}
	}
}