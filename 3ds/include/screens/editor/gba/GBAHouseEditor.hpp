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

#ifndef _SIM2EDITOR_GBA_HOUSE_EDITOR_HPP
#define _SIM2EDITOR_GBA_HOUSE_EDITOR_HPP

#include "GBAHouseItem.hpp"
#include "GBASlot.hpp"
#include "NumInputLabel.hpp"
#include "Pointer.hpp"
#include "screen.hpp"
#include <vector>

class GBAHouseEditor : public Screen {
public:
	GBAHouseEditor(std::shared_ptr<S2Core::GBASlot> &Slot) : Slot(Slot) {
		this->House = this->Slot->House(); // Not used right now, it will later for the room design.
		this->Items = this->House->Items();
		this->InitItem(false);
	}
	void Draw(void) const override;
	void Logic(u32 hDown, u32 hHeld, touchPosition touch) override;
private:
	enum class Tabs : uint8_t { Editing, Add, Remove };

	uint8_t Selection = 0;
	std::shared_ptr<S2Core::GBASlot> Slot = nullptr;
	std::unique_ptr<S2Core::GBAHouse> House = nullptr;
	std::unique_ptr<S2Core::GBAHouseItem> Items = nullptr;

	std::vector<std::unique_ptr<NumInputLabel<uint8_t>>> InputLabels = { };
	Tabs Tab = Tabs::Editing;
	bool Exit = false;

	/* Item Add Vars. */
	uint8_t AddID = 0, AddFlag = 0, AddUseCount = 0, AddX = 0, AddY = 0;
	S2Core::GBAHouseItemDirection AddDirection = S2Core::GBAHouseItemDirection::Down;

	void EditingTab();
	void AddTab();
	void RemoveTab();

	void Back();
	void InitItem(const bool AddMode);
	void SelectItemID(const bool AddMode);
	void SelectItemDirection(const bool AddMode);
	void SelectItem();
	void AddItem();
	void ValueUpdate(const uint8_t C);
	std::string Direction(const S2Core::GBAHouseItemDirection V) const;
	uint8_t DirectionInt(const S2Core::GBAHouseItemDirection V) const;

	/* Logics. */
	void EditLogic(uint32_t hDown, uint32_t hHeld, touchPosition touch);
	void AddLogic(uint32_t hDown, uint32_t hHeld, touchPosition touch);

	const std::vector<PointerStr> EditPositions = {
		{ 1, 0, 106, 20, [this]() { this->EditingTab(); } },
		{ 107, 0, 106, 20, [this]() { this->AddTab(); } },
		{ 213, 0, 106, 20, [this]() { this->RemoveTab(); } },

		{ 222, 30, 24, 24, [this]() { this->SelectItemID(false); } },
		{ 222, 180, 24, 24, [this]() { this->SelectItemDirection(false); } },

		{ 272, 192, 48, 48, [this]() { this->SelectItem(); } },
		{ 0, 223, 17, 17, [this]() { this->Back(); } }
	};

	const std::vector<PointerStr> AddPositions = {
		{ 1, 0, 106, 20, [this]() { this->EditingTab(); } },
		{ 107, 0, 106, 20, [this]() { this->AddTab(); } },
		{ 213, 0, 106, 20 }, // Do not remove on adding Tab.

		{ 222, 30, 24, 24, [this]() { this->SelectItemID(true); } },
		{ 222, 180, 24, 24, [this]() { this->SelectItemDirection(true); } },

		{ 80, 210, 160, 24, [this]() { this->AddItem(); } },
		{ 0, 223, 17, 17, [this]() { this->Back(); } }
	};
};

#endif