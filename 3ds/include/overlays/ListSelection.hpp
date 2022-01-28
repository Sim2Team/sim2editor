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

#ifndef _SIM2EDITOR_LIST_SELECTION_HPP
#define _SIM2EDITOR_LIST_SELECTION_HPP

#include "Browser.hpp"
#include "Pointer.hpp"
#include <string>
#include <vector>

class ListSelection {
public:
	ListSelection(const std::vector<std::string> &List = { }, const std::string &Text = "Select a File.", const int OldSelection = 0);
	int Action() const;
private:
	mutable std::unique_ptr<Browser> Browse = nullptr;
	mutable std::string Text = "";
	mutable int OldSelection = 0, ScreenPos = 0, Res = 0;
	mutable bool Done = false;
	mutable std::vector<std::string> List;

	void PrevPage() const;
	void NextPage() const;
	void ListCall(const int Idx) const;
	void BCall() const;

	const std::vector<PointerStr> Positions = {
		{ 0, 25, 25, 190, [this]() { this->PrevPage(); } },

		/* Entries. */
		{ 50, 30, 300, 32, [this]() { this->ListCall(0); } },
		{ 50, 67, 300, 32, [this]() { this->ListCall(1); } },
		{ 50, 104, 300, 32, [this]() { this->ListCall(2); } },
		{ 50, 141, 300, 32, [this]() { this->ListCall(3); } },
		{ 50, 178, 300, 32, [this]() { this->ListCall(4); } },

		{ 375, 25, 25, 190, [this]() { this->NextPage(); } }
	};

	/* Same as above, but on the bottom for touch compatibility! */
	const std::vector<PointerStr> BottomPos = {
		{ 70, 25, 25, 190, [this]() { this->PrevPage(); } },

		/* Entries. */
		{ 95, 30, 130, 32, [this]() { this->ListCall(0); } },
		{ 95, 67, 130, 32, [this]() { this->ListCall(1); } },
		{ 95, 104, 130, 32, [this]() { this->ListCall(2); } },
		{ 95, 141, 130, 32, [this]() { this->ListCall(3); } },
		{ 95, 178, 130, 32, [this]() { this->ListCall(4); } },

		{ 225, 25, 25, 190, [this]() { this->NextPage(); } },
		{ 0, 223, 17, 17, [this]() { this->BCall(); } }
	};
};

#endif