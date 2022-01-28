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

#ifndef _SIM2EDITOR_NUM_INPUT_LABEL_HPP
#define _SIM2EDITOR_NUM_INPUT_LABEL_HPP

#include "Pointer.hpp"
#include <string>
#include <vector>

template <typename T>
class NumInputLabel {
public:
	NumInputLabel(const int LabelX, const int LabelY, const T CurrentVal, const T MinVal, const T MaxVal, const std::string &InputText);

	void Draw(void) const;
	bool CallbackA();
	bool CallbackAmountA();
	bool CallbackTouch(touchPosition Touch);
	bool CallbackAmountTouch(touchPosition Touch);
	T GetVal() { return this->CurrentVal; }
private:
	int X, Y;
	T CurrentVal, MinVal, MaxVal;
	std::string InputText = "";
	std::vector<PointerStr> Positions = { };

	void MinusCallback() {
		if (this->CurrentVal > this->MinVal) this->CurrentVal--;
	}

	void PlusCallback() {
		if (this->CurrentVal < this->MaxVal) this->CurrentVal++;
	}

	void InputCallback();
};

#endif