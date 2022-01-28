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
#include "StringInputLabel.hpp"


/* Construct the Label. */
StringInputLabel::StringInputLabel(const int LabelX, const int LabelY, const int MaxLength, const std::string &CurrentVal, const std::string &InputText)
	: X(LabelX), Y(LabelY), MaxLength(MaxLength), CurrentVal(CurrentVal), InputText(InputText) {
	std::string Tmp = "";
	for (int Idx = 0; Idx < this->MaxLength; Idx++) Tmp += "S"; // We get the Max String Length there.

	this->Position = { this->X, this->Y, (int)Gui::GetStringWidth(0.45f, Tmp, nullptr) + 12, 16, [this]() { this->Input(); } };
}


/* Draw the String Input Label. */
void StringInputLabel::Draw(void) const {
	Gui::Draw_Rect(this->X, this->Y, this->Position.W, this->Position.H, BUTTON_COLOR);
	Gui::DrawString(this->X + 6, this->Y + 1, 0.45f, TEXT_COLOR, this->CurrentVal, this->Position.W);
}


/* Input Logic. */
void StringInputLabel::Input() {
	std::unique_ptr<KBD> Overlay = std::make_unique<KBD>(this->MaxLength, this->CurrentVal, this->InputText);
	this->CurrentVal = Overlay->Action();
}


/* Callbacks. */
bool StringInputLabel::CallbackA() { return Pointer::Callback(this->Position, true); }
bool StringInputLabel::CallbackTouch(touchPosition Touch) { return Touching(this->Position, Touch, true); }