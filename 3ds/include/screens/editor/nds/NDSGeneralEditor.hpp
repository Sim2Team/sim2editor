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

#ifndef _SIM2EDITOR_NDS_GENERAL_EDITOR_HPP
#define _SIM2EDITOR_NDS_GENERAL_EDITOR_HPP

#include "NumInputLabel.hpp"
#include "NDSSlot.hpp"
#include "Pointer.hpp"
#include "screen.hpp"
#include "StringInputLabel.hpp"
#include <string>
#include <vector>

class NDSGeneralEditor : public Screen {
public:
	NDSGeneralEditor(std::shared_ptr<S2Core::NDSSlot> &Slot);
	void Draw(void) const override;
	void Logic(u32 hDown, u32 hHeld, touchPosition touch) override;
private:
	enum class Tabs : uint8_t { Main, Collectables, SkillPoints };

	std::shared_ptr<S2Core::NDSSlot> Slot = nullptr;
	std::unique_ptr<NumInputLabel<uint32_t>> SimoleonLabel = nullptr; // uint32_t.
	std::vector<std::unique_ptr<NumInputLabel<uint8_t>>> CollectableLabels = { }; // uint8_t.
	std::unique_ptr<StringInputLabel> NameLabel = nullptr;
	std::vector<std::unique_ptr<NumInputLabel<uint8_t>>> SkillLabels = { }; // uint8_t.
	Tabs Tab = Tabs::Main;
	bool Exit = false;

	/* Shared. */
	void MainTab() { this->Tab = Tabs::Main; };
	void CollectableTab() { this->Tab = Tabs::Collectables; };
	void SkillPointsTab() { this->Tab = Tabs::SkillPoints; };
	void Back();

	const std::vector<PointerStr> Positions = {
		{ 1, 0, 106, 20, [this]() { this->MainTab(); } },
		{ 107, 0, 106, 20, [this]() { this->CollectableTab(); } },
		{ 213, 0, 106, 20, [this]() { this->SkillPointsTab(); } },
		{ 0, 223, 17, 17, [this]() { this->Back(); } }
	};

	/* Collectables Tab. */
	void CollectableUpdater(const uint8_t Idx);
	/* Skill Points Tab. */
	void SkillUpdater(const uint8_t Idx);
};

#endif