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

#ifndef _SIM2EDITOR_GBA_APPEARANCE_EDITOR_HPP
#define _SIM2EDITOR_GBA_APPEARANCE_EDITOR_HPP

#include "GBASlot.hpp"
#include "Pointer.hpp"
#include "screen.hpp"
#include <string>
#include <vector>

class GBAAppearanceEditor : public Screen {
public:
	GBAAppearanceEditor(std::shared_ptr<S2Core::GBASlot> &Slot);
	void Draw(void) const override;
	void Logic(u32 hDown, u32 hHeld, touchPosition touch) override;
private:
	enum class Tabs : uint8_t { Head, Shirt, Pants };

	std::shared_ptr<S2Core::GBASlot> Slot = nullptr;
	Tabs Tab = Tabs::Head;

	/* Shared. */
	void HeadTab() { this->Tab = Tabs::Head; }
	void ShirtTab() { this->Tab = Tabs::Shirt; }
	void PantsTab() { this->Tab = Tabs::Pants; }
	void Back();

	void SelectShoeHatColor();
	void SelectHair();
	void SelectHaircolor();
	void SelectShirt();
	void SelectShirtcolor1();
	void SelectShirtcolor2();
	void SelectShirtcolor3();
	void SelectPants();
	void SelectPantsColor();

	const std::vector<PointerStr> HeadPosition = {
		{ 1, 0, 106, 20, [this]() { this->HeadTab(); } },
		{ 107, 0, 106, 20, [this]() { this->ShirtTab(); } },
		{ 213, 0, 106, 20, [this]() { this->PantsTab(); } },

		{ 263, 39, 24, 24, [this]() { this->SelectHair(); } },
		{ 263, 79, 24, 24, [this]() { this->SelectShoeHatColor(); } },
		{ 263, 119, 24, 24, [this]() { this->SelectHaircolor(); } },

		{ 0, 223, 17, 17, [this]() { this->Back(); } }
	};

	const std::vector<PointerStr> ShirtPosition = {
		{ 1, 0, 106, 20, [this]() { this->HeadTab(); } },
		{ 107, 0, 106, 20, [this]() { this->ShirtTab(); } },
		{ 213, 0, 106, 20, [this]() { this->PantsTab(); } },

		{ 263, 39, 24, 24, [this]() { this->SelectShirt(); } },
		{ 263, 79, 24, 24, [this]() { this->SelectShirtcolor1(); } },
		{ 263, 119, 24, 24, [this]() { this->SelectShirtcolor2(); } },
		{ 263, 159, 24, 24, [this]() { this->SelectShirtcolor3(); } },

		{ 0, 223, 17, 17, [this]() { this->Back(); } }
	};

	const std::vector<PointerStr> PantsPosition = {
		{ 1, 0, 106, 20, [this]() { this->HeadTab(); } },
		{ 107, 0, 106, 20, [this]() { this->ShirtTab(); } },
		{ 213, 0, 106, 20, [this]() { this->PantsTab(); } },

		{ 263, 39, 24, 24, [this]() { this->SelectPants(); } },
		{ 263, 79, 24, 24, [this]() { this->SelectPantsColor(); } },

		{ 0, 223, 17, 17, [this]() { this->Back(); } }
	};
};

#endif