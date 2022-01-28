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

#ifndef _SIM2EDITOR_GBA_EPISODE_EDITOR_HPP
#define _SIM2EDITOR_GBA_EPISODE_EDITOR_HPP

#include "GBAEpisode.hpp"
#include "GBASlot.hpp"
#include "NumInputLabel.hpp"
#include "Pointer.hpp"
#include "screen.hpp"
#include <string>
#include <vector>

class GBAEpisodeEditor : public Screen {
public:
	GBAEpisodeEditor(std::shared_ptr<S2Core::GBASlot> &Slot);
	void Draw(void) const override;
	void Logic(u32 hDown, u32 hHeld, touchPosition touch) override;
private:
	enum class Tabs : uint8_t { Main, Misc };

	uint8_t SelectedEpisode = 0, Season = 1;
	bool EpisodeSelect = false;
	std::shared_ptr<S2Core::GBASlot> Slot = nullptr;
	std::unique_ptr<S2Core::GBAEpisode> ActiveEpisode = nullptr;
	std::vector<std::unique_ptr<NumInputLabel<uint8_t>>> Boxes = { };
	Tabs Tab = Tabs::Main;
	bool Exit = false;

	/* Shared. */
	void SetInputBoxes();
	void MainTab() { this->Tab = Tabs::Main; }
	void MiscTab() { this->Tab = Tabs::Misc; }
	void SelectEpisode();
	void Back();

	/* Episode Selection. */
	void DrawEpisodeSelection(void) const;
	void EpisodeSelectLogic(u32 hDown, u32 hHeld, touchPosition touch);
	void PrevSeason();
	void NextSeason();
	void Select(const int Idx);
	void CancelSelection();

	const std::vector<PointerStr> EPSelect = {
		{ 0, 25, 25, 190, [this]() { this->PrevSeason(); } },

		{ 50, 30, 300, 32, [this]() { this->Select(0); } },
		{ 50, 67, 300, 32, [this]() { this->Select(1); } },
		{ 50, 104, 300, 32, [this]() { this->Select(2); } },
		{ 50, 141, 300, 32, [this]() { this->Select(3); } },

		{ 375, 25, 25, 190, [this]() { this->NextSeason(); } }
	};

	/* Same as above, but on the bottom for touch compatibility! */
	const std::vector<PointerStr> EPSelectBot = {
		{ 70, 25, 25, 190, [this]() { this->PrevSeason(); } },

		{ 95, 30, 130, 32, [this]() { this->Select(0); } },
		{ 95, 67, 130, 32, [this]() { this->Select(1); } },
		{ 95, 104, 130, 32, [this]() { this->Select(2); } },
		{ 95, 141, 130, 32, [this]() { this->Select(3); } },

		{ 225, 25, 25, 190, [this]() { this->NextSeason(); } },
		{ 0, 223, 17, 17, [this]() { this->CancelSelection(); } }
	};

	/* MAIN. */
	void ToggleEpisode();
	void DrawStripes(void) const;


	const std::vector<PointerStr> MainPositions = {
		{ 0, 0, 160, 20, [this]() { this->MainTab(); } },
		{ 160, 0, 160, 20, [this]() { this->MiscTab(); } },
		{ 220, 196, 24, 24, [this]() { this->ToggleEpisode(); } },
		{ 272, 192, 48, 48, [this]() { this->SelectEpisode(); } },
		{ 0, 223, 17, 17, [this]() { this->Back(); } }
	};


	/* Miscellaneous Tab. */
	void Lockall();
	void Unlockall();
	void ClearRatings();
	void MaxRatings();

	const std::vector<PointerStr> MassPos = {
		{ 0, 0, 160, 20, [this]() { this->MainTab(); } },
		{ 160, 0, 160, 20, [this]() { this->MiscTab(); } },

		{ 80, 35, 160, 35, [this]() { this->Lockall(); } },
		{ 80, 80, 160, 35, [this]() { this->Unlockall(); } },
		{ 80, 125, 160, 35, [this]() { this->ClearRatings(); } },
		{ 80, 170, 160, 35, [this]() { this->MaxRatings(); } },

		{ 272, 192, 48, 48, [this]() { this->SelectEpisode(); } },
		{ 0, 223, 17, 17, [this]() { this->Back(); } }
	};

	const std::vector<std::string> MiscNames = { "Lock all Episodes", "Unlock all Episodes", "Clear all Ratings", "Set all Ratings to max" };
};

#endif