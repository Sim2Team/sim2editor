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

#ifndef _SIM2EDITOR_NUMPAD_HPP
#define _SIM2EDITOR_NUMPAD_HPP

#include "Pointer.hpp"
#include <string>
#include <vector>

class Numpad {
public:
	Numpad(const int MaxLength, const int OldNum, const int MaxVal, const std::string &Text)
			: MaxLength(MaxLength), OldNum(OldNum), MaxVal(MaxVal), Text(Text) { this->Res = std::to_string(this->OldNum); }
	int Action() const;
private:
	mutable int MaxLength = 0, OldNum = 0, MaxVal = 0, FinalRes = 0;
	mutable bool Done = false;
	mutable std::string Text = "", Res = "";

	void Draw() const;
	void InputNum(const uint8_t Idx) const;
	void RemoveNum() const;
	void Confirm() const;
	void SetPos() const;

	/*
		Numpad Structure.

		1   2   3
		4   5   6
		7   8   9
			0
	*/

	const std::vector<std::string> Nums = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "<-", "->" };
	const std::vector<PointerStr> Pad = {
		{  80, 15, 40, 40, [this]() { this->InputNum(0); } }, { 140, 15, 40, 40, [this]() { this->InputNum(1); } },  { 200, 15, 40, 40, [this]() { this->InputNum(2); } },
		{ 80, 75, 40, 40, [this]() { this->InputNum(3); } },  { 140, 75, 40, 40, [this]() { this->InputNum(4); } },  { 200, 75, 40, 40, [this]() { this->InputNum(5); } },
		{ 80, 135, 40, 40, [this]() { this->InputNum(6); } }, { 140, 135, 40, 40, [this]() { this->InputNum(7); } }, { 200, 135, 40, 40, [this]() { this->InputNum(8); } },
															  { 140, 195, 40, 40, [this]() { this->InputNum(9); } },
		{ 5, 205, 30, 30, [this]() { this->RemoveNum(); } }, 														 { 285, 205, 30, 30, [this]() { this->Confirm(); } } // Back and Next.
	};
};

#endif