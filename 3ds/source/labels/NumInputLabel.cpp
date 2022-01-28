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
#include "NumInputLabel.hpp"
#include "Numpad.hpp"


/* We are only using uint8_t, uint16_t OR uint32_t. */
template class NumInputLabel<uint8_t>;
template class NumInputLabel<uint16_t>;
template class NumInputLabel<uint32_t>;


/* Construct the Num Input Label Positions there for the Callback etc. */
template <typename T>
NumInputLabel<T>::NumInputLabel(const int LabelX, const int LabelY, const T CurrentVal, const T MinVal, const T MaxVal, const std::string &InputText)
	: X(LabelX), Y(LabelY), CurrentVal(CurrentVal), MinVal(MinVal), MaxVal(MaxVal), InputText(InputText) {
	/* Create our Pointer Struct. */
	this->Positions.push_back({ this->X, this->Y, 24, 24, [this]() { this->MinusCallback(); } });
	this->Positions.push_back({ this->X + 24 + 4, this->Y + 4, (int)Gui::GetStringWidth(0.45f, std::to_string(this->MaxVal), nullptr) + 12, 16, [this]() { this->InputCallback(); } });
	this->Positions.push_back({ this->X + 24 + 4 + this->Positions[1].W + 4, this->Y, 24, 24, [this]() { this->PlusCallback(); } });
}


/* Draw the Num Input Label. */
template <typename T>
void NumInputLabel<T>::Draw(void) const {
	/* Draw Minus. */
	Gui::DrawSprite(GFX::Sprites, sprites_checkbox_idx, this->X, this->Y);
	Gui::Draw_Rect(this->X + 6, this->Y + 11, 12, 2, BUTTON_COLOR);

	/* Draw Input. */
	Gui::Draw_Rect(this->Positions[1].X, this->Positions[1].Y, this->Positions[1].W, this->Positions[1].H, BUTTON_COLOR);
	Gui::DrawString(this->Positions[1].X + 6, this->Positions[1].Y + 1, 0.45f, TEXT_COLOR, std::to_string(this->CurrentVal), this->Positions[1].W);

	/* Draw Plus. */
	Gui::DrawSprite(GFX::Sprites, sprites_checkbox_idx, this->Positions[2].X, this->Positions[2].Y);
	Gui::Draw_Rect(this->Positions[2].X + 6, this->Positions[2].Y + 11, 12, 2, BUTTON_COLOR); // Plus Part 1.
	Gui::Draw_Rect(this->Positions[2].X + 11, this->Positions[2].Y + 6, 2, 12, BUTTON_COLOR); // Plus Part 2.
}


/* Open the Numpad to enter a value. */
template <typename T>
void NumInputLabel<T>::InputCallback() {
	const int Size = std::to_string(this->MaxVal).size(); // Get Max Input Length.
	std::unique_ptr<Numpad> Overlay = std::make_unique<Numpad>(Size, this->CurrentVal, this->MaxVal, this->InputText);
	this->CurrentVal = Overlay->Action();
}


/* The A Button Callback. */
template <typename T>
bool NumInputLabel<T>::CallbackA() {
	if (1 < this->Positions.size()) return (Pointer::Callback(this->Positions[1], true));

	return false;
}


/* The A Button Amount change for the hidKeysDownRepeat() method. */
template <typename T>
bool NumInputLabel<T>::CallbackAmountA() {
	const uint8_t Callbacks[2] = { 0, 2 };

	for (uint8_t Idx = 0; Idx < 2; Idx++) {
		if (Callbacks[Idx] < this->Positions.size()) {
			if (Pointer::Callback(this->Positions[Callbacks[Idx]], true)) return true;
		}
	}

	return false;
}


/* The Touch Tap Callback. */
template <typename T>
bool NumInputLabel<T>::CallbackTouch(touchPosition Touch) {
	if (1 < this->Positions.size()) return (Touching(this->Positions[1], Touch, true));

	return false;
}


/* The Touch Tap Amount change for the hidKeysDownRepeat() method. */
template <typename T>
bool NumInputLabel<T>::CallbackAmountTouch(touchPosition Touch) {
	static const uint8_t Callbacks[2] = { 0, 2 };

	for (uint8_t Idx = 0; Idx < 2; Idx++) {
		if (Callbacks[Idx] < this->Positions.size()) {
			if (Touching(this->Positions[Callbacks[Idx]], Touch, true)) return true;
		}
	}

	return false;
}