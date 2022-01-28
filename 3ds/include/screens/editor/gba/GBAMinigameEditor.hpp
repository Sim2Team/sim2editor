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

#ifndef _SIM2EDITOR_GBA_MINIGAME_EDITOR_HPP
#define _SIM2EDITOR_GBA_MINIGAME_EDITOR_HPP

#include "GBAMinigame.hpp"
#include "GBASlot.hpp"
#include "NumInputLabel.hpp"
#include "Pointer.hpp"
#include "screen.hpp"
#include <vector>

class GBAMinigameEditor : public Screen {
public:
	GBAMinigameEditor(std::shared_ptr<S2Core::GBASlot> &Slot) : Slot(Slot) { this->InitGame(0); }
	void Draw(void) const override;
	void Logic(u32 hDown, u32 hHeld, touchPosition touch) override;
private:
	enum class Tabs : uint8_t { Main, Misc };

	std::unique_ptr<S2Core::GBAMinigame> ActiveMinigame = nullptr;
	std::shared_ptr<S2Core::GBASlot> Slot = nullptr;
	std::unique_ptr<NumInputLabel<uint8_t>> LevelLabel = nullptr;
	Tabs Tab = Tabs::Main;
	bool Exit = false;

	/* Shared things. */
	void MainTab() { this->Tab = Tabs::Main; }
	void MiscTab() { this->Tab = Tabs::Misc; }
	void Back();
	void InitGame(const uint8_t Game);
	void SelectMinigame();

	/* Main Tab. */
	void TogglePlayed();

	const std::vector<PointerStr> Positions = {
		{ 0, 0, 160, 20, [this]() { this->MainTab(); } },
		{ 160, 0, 160, 20, [this]() { this->MiscTab(); } },

		{ 140, 120, 24, 24, [this]() { this->TogglePlayed(); } },

		{ 272, 192, 48, 48, [this]() { this->SelectMinigame(); } },
		{ 0, 223, 17, 17, [this]() { this->Back(); } }
	};

	/* Miscellaneous Tab. */
	void ResetLevels();
	void MaxLevels();
	void AllUnplayed();
	void AllPlayed();

	const std::vector<PointerStr> MassPos = {
		{ 0, 0, 160, 20, [this]() { this->MainTab(); } },
		{ 160, 0, 160, 20, [this]() { this->MiscTab(); } },

		{ 80, 35, 160, 35, [this]() { this->ResetLevels(); } },
		{ 80, 80, 160, 35, [this]() { this->MaxLevels(); } },
		{ 80, 125, 160, 35, [this]() { this->AllUnplayed(); } },
		{ 80, 170, 160, 35, [this]() { this->AllPlayed(); } },

		{ 272, 192, 48, 48, [this]() { this->SelectMinigame(); } },
		{ 0, 223, 17, 17, [this]() { this->Back(); } }
	};

	const std::vector<std::string> MiscNames = { "Reset all Levels", "Max out all Levels", "Set all unplayed", "Set all played" };
};

#endif