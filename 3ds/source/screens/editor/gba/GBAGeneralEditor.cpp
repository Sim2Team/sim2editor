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
#include "GBAGeneralEditor.hpp"
#include "Strings.hpp"


/* Initialize the GBASlot + the Labels. */
GBAGeneralEditor::GBAGeneralEditor(std::shared_ptr<S2Core::GBASlot> &Slot) : Slot(Slot) {
	/* Init Name Label. */
	this->NameLabel = std::make_unique<StringInputLabel>(140, 40, 16, this->Slot->Name(), "Enter a Sim Name.");
	/* Init Simoleon Label. */
	this->SimoleonLabel = std::make_unique<NumInputLabel<uint32_t>>(140, 80, this->Slot->Simoleons(), 0, 999999, "Enter the Simoleon Amount.");
	/* Init Rating Label. */
	this->RatingLabel = std::make_unique<NumInputLabel<uint16_t>>(140, 120, this->Slot->Ratings(), 0, 9999, "Enter the Ratings Amount.");
	/* Init Time Labels. */
	this->TimeLabels.push_back(std::make_unique<NumInputLabel<uint8_t>>(140, 160, (uint8_t)this->Slot->Time(), 0, 23, "Enter the Hour."));
	this->TimeLabels.push_back(std::make_unique<NumInputLabel<uint8_t>>(140, 200, (this->Slot->Time() >> 8), 0, 59, "Enter the Minute."));

	/* Init Collectables. - Empty Chug-Chug Cola Cans. */
	this->CollectableLabels.push_back(std::make_unique<NumInputLabel<uint8_t>>(5, 45, this->Slot->Cans(), 0, 250, "Enter the Empty Chug-Chug Cola Can Amount."));
	this->CollectableLabels.push_back(std::make_unique<NumInputLabel<uint8_t>>(225, 45, this->Slot->CansPrice(), 0, 255, "Enter the Empty Chug-Chug Cola Can Price."));

	/* Init Collectables. - Cowbells. */
	this->CollectableLabels.push_back(std::make_unique<NumInputLabel<uint8_t>>(5, 95, this->Slot->Cowbells(), 0, 250, "Enter the Cowbells Amount."));
	this->CollectableLabels.push_back(std::make_unique<NumInputLabel<uint8_t>>(225, 95, this->Slot->CowbellsPrice(), 0, 255, "Enter the Cowbells Price."));

	/* Init Collectables. - Alien Spaceship Parts. */
	this->CollectableLabels.push_back(std::make_unique<NumInputLabel<uint8_t>>(5, 145, this->Slot->Spaceship(), 0, 250, "Enter the Alien Spaceship Parts Amount."));
	this->CollectableLabels.push_back(std::make_unique<NumInputLabel<uint8_t>>(225, 145, this->Slot->SpaceshipPrice(), 0, 255, "Enter the Alien Spaceship Parts Price."));

	/* Init Collectables. - Nuclear Fuelrods. */
	this->CollectableLabels.push_back(std::make_unique<NumInputLabel<uint8_t>>(5, 195, this->Slot->Fuelrods(), 0, 250, "Enter the Nuclear Fuelrods Amount."));
	this->CollectableLabels.push_back(std::make_unique<NumInputLabel<uint8_t>>(225, 195, this->Slot->FuelrodsPrice(), 0, 255, "Enter the Nuclear Fuelrods Price."));

	/* Init Skill point Labels. */
	this->SkillLabels.push_back(std::make_unique<NumInputLabel<uint8_t>>(190, 40, this->Slot->Confidence(), 0, 5, "Enter the Confidence Skill Points."));
	this->SkillLabels.push_back(std::make_unique<NumInputLabel<uint8_t>>(190, 70, this->Slot->Mechanical(), 0, 5, "Enter the Mechanical Skill Points."));
	this->SkillLabels.push_back(std::make_unique<NumInputLabel<uint8_t>>(190, 100, this->Slot->Strength(), 0, 5, "Enter the Strength Skill Points."));
	this->SkillLabels.push_back(std::make_unique<NumInputLabel<uint8_t>>(190, 130, this->Slot->Personality(), 0, 5, "Enter the Personality Skill Points."));
	this->SkillLabels.push_back(std::make_unique<NumInputLabel<uint8_t>>(190, 160, this->Slot->Hotness(), 0, 5, "Enter the Hotness Skill Points."));
	this->SkillLabels.push_back(std::make_unique<NumInputLabel<uint8_t>>(190, 190, this->Slot->Intellect(), 0, 5, "Enter the Intellect Skill Points."));
}


/* Goes back to the Slot Editor. */
void GBAGeneralEditor::Back() {
	this->Exit = true;
	Gui::screenBack();
	return;
}


void GBAGeneralEditor::Draw(void) const {
	GFX::DrawTop();
	Gui::DrawStringCentered(0, 3, 0.6f, TEXT_COLOR, "GBA General Editor");

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

			Gui::DrawString(120, 123, 0.5f, TEXT_COLOR, "Ratings: ", 110, 0, nullptr, C2D_AlignRight);
			this->RatingLabel->Draw();

			Gui::DrawString(120, 163, 0.5f, TEXT_COLOR, "Hour: ", 110, 0, nullptr, C2D_AlignRight);
			Gui::DrawString(120, 203, 0.5f, TEXT_COLOR, "Minute: ", 110, 0, nullptr, C2D_AlignRight);
			for (auto &Time : this->TimeLabels) Time->Draw();
			break;

		case Tabs::Collectables:
			Gui::DrawString(5, 25, 0.45f, TEXT_COLOR, "Collectable Amount", 0, 0, nullptr, C2D_AlignLeft);
			Gui::DrawString(315, 25, 0.45f, TEXT_COLOR, "Collectable Price", 0, 0, nullptr, C2D_AlignRight);
			for (auto &Label : this->CollectableLabels) Label->Draw(); // Draw Collectable Labels.

			/* Draw Collectable Icons in the Middle. */
			Gui::DrawSprite(GFX::Sprites, sprites_cola_idx, 122, 40);
			Gui::DrawSprite(GFX::Sprites, sprites_bell_idx, 122, 90);
			Gui::DrawSprite(GFX::Sprites, sprites_spaceship_idx, 122, 140);
			Gui::DrawSprite(GFX::Sprites, sprites_fuelrod_idx, 122, 190);
			break;

		case Tabs::SkillPoints:
			for (uint8_t Idx = 0; Idx < 6; Idx++) {
				Gui::DrawString(50, 44 + (Idx * 30), 0.5f, TEXT_COLOR, S2Core::Strings::GBASkillPointNames_EN[Idx]);
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
void GBAGeneralEditor::CollectableUpdater(const uint8_t Idx) {
	switch(Idx) {
		case 0:
			this->Slot->Cans(this->CollectableLabels[0]->GetVal());
			break;

		case 1:
			this->Slot->CansPrice(this->CollectableLabels[1]->GetVal());
			break;

		case 2:
			this->Slot->Cowbells(this->CollectableLabels[2]->GetVal());
			break;

		case 3:
			this->Slot->CowbellsPrice(this->CollectableLabels[3]->GetVal());
			break;

		case 4:
			this->Slot->Spaceship(this->CollectableLabels[4]->GetVal());
			break;

		case 5:
			this->Slot->SpaceshipPrice(this->CollectableLabels[5]->GetVal());
			break;

		case 6:
			this->Slot->Fuelrods(this->CollectableLabels[6]->GetVal());
			break;

		case 7:
			this->Slot->FuelrodsPrice(this->CollectableLabels[7]->GetVal());
			break;
	}
}


/*
	Just a way to not have a whole mess on the KEY_A whatever operations.
	This basically sets the proper things into the Slot.

	const uint8_t Idx: The Index of the Skillpoint.
*/
void GBAGeneralEditor::SkillUpdater(const uint8_t Idx) {
	switch(Idx) {
		case 0:
			this->Slot->Confidence(this->SkillLabels[0]->GetVal());
			break;

		case 1:
			this->Slot->Mechanical(this->SkillLabels[1]->GetVal());
			break;

		case 2:
			this->Slot->Strength(this->SkillLabels[2]->GetVal());
			break;

		case 3:
			this->Slot->Personality(this->SkillLabels[3]->GetVal());
			break;

		case 4:
			this->Slot->Hotness(this->SkillLabels[4]->GetVal());
			break;

		case 5:
			this->Slot->Intellect(this->SkillLabels[5]->GetVal());
			break;
	}
}


void GBAGeneralEditor::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
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

			if (!Pressed) {
				if (this->RatingLabel->CallbackA()) {
					this->Slot->Ratings(this->RatingLabel->GetVal());
					Pressed = true;
				}
			}

			if (!Pressed) {
				for (auto &Time : this->TimeLabels) {
					if (Time->CallbackA()) {
						const uint16_t T =  (256 * this->TimeLabels[1]->GetVal()) + this->TimeLabels[0]->GetVal();
						this->Slot->Time(T);
						Pressed = true;
						break;
					}
				}
			}
		}

		/* NUM Input Labels Only. */
		if (hRepeat & KEY_A) {
			if (this->Exit) return;

			bool Pressed = false;

			/* Simoleons. */
			if (this->SimoleonLabel->CallbackAmountA()) {
				this->Slot->Simoleons(this->SimoleonLabel->GetVal());
				Pressed = true;
			}

			/* Ratings. */
			if (!Pressed) {
				if (this->RatingLabel->CallbackAmountA()) {
					this->Slot->Ratings(this->RatingLabel->GetVal());
					Pressed = true;
				}
			}

			/* Time. */
			if (!Pressed) {
				for (auto &Time : this->TimeLabels) {
					if (Time->CallbackAmountA()) {
						const uint16_t T =  (256 * this->TimeLabels[1]->GetVal()) + this->TimeLabels[0]->GetVal();
						this->Slot->Time(T);
						Pressed = true;
						break;
					}
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

			/* Ratings. */
			if (!Pressed) {
				if (this->RatingLabel->CallbackTouch(touch)) {
					this->Slot->Ratings(this->RatingLabel->GetVal());
					Pressed = true;
				}
			}

			/* Time. */
			if (!Pressed) {
				for (auto &Time : this->TimeLabels) {
					if (Time->CallbackTouch(touch)) {
						const uint16_t T =  (256 * this->TimeLabels[1]->GetVal()) + this->TimeLabels[0]->GetVal();
						this->Slot->Time(T);
						Pressed = true;
						break;
					}
				}
			}
		}

		/* Same for the Minus and Plus buttons as well. */
		if (hRepeat & KEY_TOUCH) {
			if (this->Exit) return;

			bool Pressed = false;

			/* Simoleons. */
			if (this->SimoleonLabel->CallbackAmountTouch(touch)) {
				this->Slot->Simoleons(this->SimoleonLabel->GetVal());
				Pressed = true;
			}

			if (!Pressed) {
				if (this->RatingLabel->CallbackAmountTouch(touch)) {
					this->Slot->Ratings(this->RatingLabel->GetVal());
					Pressed = true;
				}
			}

			if (!Pressed) {
				for (auto &Time : this->TimeLabels) {
					if (Time->CallbackAmountTouch(touch)) {
						const uint16_t T =  (256 * this->TimeLabels[1]->GetVal()) + this->TimeLabels[0]->GetVal();
						this->Slot->Time(T);
						Pressed = true;
						break;
					}
				}
			}
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
				for (uint8_t Idx = 0; Idx < 8; Idx++) {
					if (this->CollectableLabels[Idx]->CallbackA()) {
						this->CollectableUpdater(Idx);
						break;
					}
				}
			}
		}

		if (hRepeat & KEY_A) {
			if (this->Exit) return;

			for (uint8_t Idx = 0; Idx < 8; Idx++) {
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
				for (uint8_t Idx = 0; Idx < 8; Idx++) {
					if (this->CollectableLabels[Idx]->CallbackTouch(touch)) {
						this->CollectableUpdater(Idx);
						break;
					}
				}
			}
		}

		if (hRepeat & KEY_TOUCH) {
			if (this->Exit) return;

			for (uint8_t Idx = 0; Idx < 8; Idx++) {
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
				for (uint8_t Idx = 0; Idx < 6; Idx++) {
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

			for (uint8_t Idx = 0; Idx < 6; Idx++) {
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
				for (uint8_t Idx = 0; Idx < 6; Idx++) {
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

			for (uint8_t Idx = 0; Idx < 6; Idx++) {
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