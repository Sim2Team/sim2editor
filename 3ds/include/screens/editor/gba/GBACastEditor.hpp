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

#ifndef _SIM2EDITOR_GBA_CAST_EDITOR_HPP
#define _SIM2EDITOR_GBA_CAST_EDITOR_HPP

#include "GBACast.hpp"
#include "GBASlot.hpp"
#include "Pointer.hpp"
#include "screen.hpp"
#include <vector>

class GBACastEditor : public Screen {
public:
	GBACastEditor(std::shared_ptr<S2Core::GBASlot> &Slot) : Slot(Slot) { this->ActiveCast = this->Slot->Cast(0); }
	void Draw(void) const override;
	void Logic(u32 hDown, u32 hHeld, touchPosition touch) override;
private:
	enum class Tabs : uint8_t { Main, Misc };

	bool CastSelection = false;
	uint8_t SelectedCast = 0;
	std::unique_ptr<S2Core::GBACast> ActiveCast = nullptr;
	std::shared_ptr<S2Core::GBASlot> Slot = nullptr;
	Tabs Tab = Tabs::Main;

	/* Shared things. */
	void MainTab() { this->Tab = Tabs::Main; }
	void MiscTab() { this->Tab = Tabs::Misc; }
	void SelectCast();
	void Back();

	/* Cast Selector. */
	void DrawCastSelector(void) const;
	void CastSelectorLogic(u32 hDown, u32 hHeld, touchPosition touch);

	void PrevCast();
	void NextCast();
	void Select();
	void CancelSelection();

	const std::vector<PointerStr> CastSelector = {
		{ 0, 25, 25, 215, [this]() { this->PrevCast(); } },
		{ 375, 25, 25, 215, [this]() { this->NextCast(); } },
		{ 100, 200, 200, 20, [this]() { this->Select(); } }
	};

	const std::vector<PointerStr> CastSelectorBot = {
		{ 70, 75, 25, 90, [this]() { this->PrevCast(); } },
		{ 123, 109, 74, 22, [this]() { this->Select(); } },
		{ 225, 75, 25, 90, [this]() { this->NextCast(); } },
		{ 0, 223, 17, 17, [this]() { this->CancelSelection(); } }
	};

	/* Main Tab. */
	void ChangeFriendly();
	void ChangeRomance();
	void ChangeIntimidate();
	void SetFeeling();
	void ToggleSecret();

	const std::vector<PointerStr> Positions = {
		{ 0, 0, 160, 20, [this]() { this->MainTab(); } },
		{ 160, 0, 160, 20, [this]() { this->MiscTab(); } },

		{ 26, 50, 73, 80, [this]() { this->ChangeFriendly(); } },
		{ 124, 50, 73, 80, [this]() { this->ChangeRomance(); } },
		{ 222, 50, 73, 80, [this]() { this->ChangeIntimidate(); } },
		{ 106, 140, 24, 24, [this]() { this->SetFeeling(); } },
		{ 106, 180, 24, 24, [this]() { this->ToggleSecret(); } },
		{ 272, 192, 48, 48, [this]() { this->SelectCast(); } },
		{ 0, 223, 17, 17, [this]() { this->Back(); } }
	};

	/* Miscellaneous Tab. */
	void MinConversation();
	void MaxConversation();
	void SecretUnlocks();
	void MassFeelingChange();

	const std::vector<PointerStr> MassPos = {
		{ 0, 0, 160, 20, [this]() { this->MainTab(); } },
		{ 160, 0, 160, 20, [this]() { this->MiscTab(); } },

		{ 80, 35, 160, 35, [this]() { this->MinConversation(); } },
		{ 80, 80, 160, 35, [this]() { this->MaxConversation(); } },
		{ 80, 125, 160, 35, [this]() { this->SecretUnlocks(); } },
		{ 80, 170, 160, 35, [this]() { this->MassFeelingChange(); } },

		{ 272, 192, 48, 48, [this]() { this->SelectCast(); } },
		{ 0, 223, 17, 17, [this]() { this->Back(); } }
	};

	const std::vector<std::string> MiscNames = { "Clear Conversations", "Max out Conversations", "Unlock all Secrets", "Set all Pictures" };
	const std::vector<std::string> Feelings = { "Neutral", "Friendly", "Angry", "Love", "Invalid" };
};

#endif