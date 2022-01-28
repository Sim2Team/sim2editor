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

#ifndef _SIM2EDITOR_GBA_ITEM_EDITOR_HPP
#define _SIM2EDITOR_GBA_ITEM_EDITOR_HPP

#include "GBAItem.hpp"
#include "GBASlot.hpp"
#include "Pointer.hpp"
#include "screen.hpp"
#include <vector>

class GBAItemEditor : public Screen {
public:
	GBAItemEditor(std::shared_ptr<S2Core::GBASlot> &Slot) : Slot(Slot) { this->SwitchTab(Tabs::Pawnshop); }
	void Draw(void) const override;
	void Logic(u32 hDown, u32 hHeld, touchPosition touch) override;
private:
	enum class Tabs : uint8_t { Pawnshop, Saloon, Skills, Mailbox, Inventory };

	Tabs Tab = Tabs::Pawnshop;
	std::shared_ptr<S2Core::GBASlot> Slot = nullptr;
	std::unique_ptr<S2Core::GBAItem> ActiveItemGroup = nullptr;

	void Back();
	void SelectItem(const uint8_t Slot);
	void SwitchTab(const Tabs T);

	const std::vector<PointerStr> Positions = {
		{ 0, 0, 64, 20, [this]() { this->SwitchTab(Tabs::Pawnshop); } },
		{ 64, 0, 64, 20, [this]() { this->SwitchTab(Tabs::Saloon); } },
		{ 128, 0, 64, 20, [this]() { this->SwitchTab(Tabs::Skills); } },
		{ 192, 0, 64, 20, [this]() { this->SwitchTab(Tabs::Mailbox); } },
		{ 256, 0, 64, 20, [this]() { this->SwitchTab(Tabs::Inventory); } },

		{ 250, 30, 24, 24, [this]() { this->SelectItem(0); } },
		{ 250, 66, 24, 24, [this]() { this->SelectItem(1); } },
		{ 250, 102, 24, 24, [this]() { this->SelectItem(2); } },
		{ 250, 138, 24, 24, [this]() { this->SelectItem(3); } },
		{ 250, 174, 24, 24, [this]() { this->SelectItem(4); } },
		{ 250, 210, 24, 24, [this]() { this->SelectItem(5); } },


		{ 0, 223, 17, 17, [this]() { this->Back(); } }
	};
};

#endif