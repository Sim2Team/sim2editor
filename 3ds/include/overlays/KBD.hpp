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

#ifndef _SIM2EDITOR_KBD_HPP
#define _SIM2EDITOR_KBD_HPP

#include "Pointer.hpp"
#include <string>
#include <vector>

class KBD {
public:
	KBD(const int MaxLength, const std::string &OldString, const std::string &Text)
			: MaxLength(MaxLength), Res(OldString), Text(Text) { }
	std::string Action() const;
private:
	mutable int MaxLength = 0;
	mutable bool Upper = true, Done = false;
	mutable std::string Res = "", Text = "";

	void Draw() const;
	void InputChar(const int Idx) const;
	void UpperTab() const;
	void LowerTab() const;
	void RemoveChar() const;
	void Confirm() const;
	void SetPos() const;

	/*
		Keyboard Structure.

		A B C D E F G
		 H I J K L M
		 N O P Q R S
		T U V W X Y Z
		  0 1 2 3 4
		  5 6 7 8 9

		a b c d e f g
		 h i j k l m
		 n o p q r s
		t u v w x y z
		  ! + # $ %
		  & _ * ( )
	*/

	const std::vector<std::string> ABCKeys = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
	const std::vector<std::string> abcKeys = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "!", "+", "#", "$", "%", "&", "_", "*", "(", ")" };
	const std::vector<std::string> SpecialKeys = { "ABC / 012", "abc / !+#", "<-", "->" };

	const std::vector<PointerStr> Layout = {
		{ 5, 34, 40, 30, [this]() { this->InputChar(0); } }, { 50, 34, 40, 30, [this]() { this->InputChar(1); } }, { 95, 34, 40, 30, [this]() { this->InputChar(2); } }, { 140, 34, 40, 30, [this]() { this->InputChar(3); } }, { 185, 34, 40, 30, [this]() { this->InputChar(4); } }, { 230, 34, 40, 30, [this]() { this->InputChar(5); } }, { 275, 34, 40, 30, [this]() { this->InputChar(6); } },
			{ 27, 68, 40, 30, [this]() { this->InputChar(7); } }, { 72, 68, 40, 30, [this]() { this->InputChar(8); } }, { 117, 68, 40, 30, [this]() { this->InputChar(9); } }, { 162, 68, 40, 30, [this]() { this->InputChar(10); } }, { 207, 68, 40, 30, [this]() { this->InputChar(11); } }, { 252, 68, 40, 30, [this]() { this->InputChar(12); } },
			{ 27, 102, 40, 30, [this]() { this->InputChar(13); } }, { 72, 102, 40, 30, [this]() { this->InputChar(14); } }, { 117, 102, 40, 30, [this]() { this->InputChar(15); } }, { 162, 102, 40, 30, [this]() { this->InputChar(16); } }, { 207, 102, 40, 30, [this]() { this->InputChar(17); } }, { 252, 102, 40, 30, [this]() { this->InputChar(18); } },
		{ 5, 136, 40, 30, [this]() { this->InputChar(19); } }, { 50, 136, 40, 30, [this]() { this->InputChar(20); } }, { 95, 136, 40, 30, [this]() { this->InputChar(21); } }, { 140, 136, 40, 30, [this]() { this->InputChar(22); } }, { 185, 136, 40, 30, [this]() { this->InputChar(23); } }, { 230, 136, 40, 30, [this]() { this->InputChar(24); } }, { 275, 136, 40, 30, [this]() { this->InputChar(25); } },

				{ 50, 170, 40, 30, [this]() { this->InputChar(26); } }, { 95, 170, 40, 30, [this]() { this->InputChar(27); } }, { 140, 170, 40, 30, [this]() { this->InputChar(28); } }, { 185, 170, 40, 30, [this]() { this->InputChar(29); } }, { 230, 170, 40, 30, [this]() { this->InputChar(30); } },
				{ 50, 204, 40, 30, [this]() { this->InputChar(31); } }, { 95, 204, 40, 30, [this]() { this->InputChar(32); } }, { 140, 204, 40, 30, [this]() { this->InputChar(33); } }, { 185, 204, 40, 30, [this]() { this->InputChar(34); } }, { 230, 204, 40, 30, [this]() { this->InputChar(35); } }
	};

	const std::vector<PointerStr> SpecialKeysFunc = {
		{ 0, 0, 160, 25, [this]() { this->UpperTab(); } }, { 160, 0, 160, 25, [this]() { this->LowerTab(); } },
		{ 5, 205, 30, 30, [this]() { this->RemoveChar(); } }, { 285, 205, 30, 30, [this]() { this->Confirm(); } }
	};
};

#endif