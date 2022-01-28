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

#ifndef _SIM2EDITOR_GBA_SOCIAL_MOVE_EDITOR_HPP
#define _SIM2EDITOR_GBA_SOCIAL_MOVE_EDITOR_HPP

#include "GBASocialMove.hpp"
#include "GBASlot.hpp"
#include "NumInputLabel.hpp"
#include "Pointer.hpp"
#include "screen.hpp"
#include <string>
#include <vector>

class GBASocialMoveEditor : public Screen {
public:
	GBASocialMoveEditor(std::shared_ptr<S2Core::GBASlot> &Slot) : Slot(Slot) { this->ActiveMove = this->Slot->SocialMove(0); }
	void Draw(void) const override;
	void Logic(u32 hDown, u32 hHeld, touchPosition touch) override;
private:
	uint8_t SelectedMove = 0;
	bool MoveSelection = false;
	std::shared_ptr<S2Core::GBASlot> Slot = nullptr;
	std::unique_ptr<S2Core::GBASocialMove> ActiveMove = nullptr;

	/* Social Move Selection. */
	void DrawMoveSelector(void) const;
	void MoveSelectorLogic(u32 hDown, u32 hHeld, touchPosition touch);

	void PrevMove();
	void NextMove();
	void Select();
	void CancelSelection();

	const std::vector<PointerStr> MoveSelector = {
		{ 0, 25, 25, 215, [this]() { this->PrevMove(); } },
		{ 375, 25, 25, 215, [this]() { this->NextMove(); } },
		{ 100, 200, 200, 20, [this]() { this->Select(); } }
	};

	const std::vector<PointerStr> MoveSelectorBot = {
		{ 70, 75, 25, 90, [this]() { this->PrevMove(); } },
		{ 123, 109, 74, 22, [this]() { this->Select(); } },
		{ 225, 75, 25, 90, [this]() { this->NextMove(); } },
		{ 0, 223, 17, 17, [this]() { this->CancelSelection(); } }
	};

	/* Main Tab. */
	void DrawStripes() const;
	void ChangeFlag();
	void ChangeMassFlag();
	void ChangeLevel();
	void ChangeMassLevel();
	void SelectMove();
	void Back();

	const std::vector<std::string> Flags = { "Locked", "Unlocked", "Blocked" };
	const std::vector<std::string> Levels = { "Level 1", "Level 2", "Level 3", "Level None" };

	const std::vector<PointerStr> Positions = {
		{ 263, 29, 24, 24, [this]() { this->ChangeFlag(); } },
		{ 263, 69, 24, 24, [this]() { this->ChangeMassFlag(); } },
		{ 263, 109, 24, 24, [this]() { this->ChangeLevel(); } },
		{ 263, 149, 24, 24, [this]() { this->ChangeMassLevel(); } },

		{ 272, 192, 48, 48, [this]() { this->SelectMove(); } },
		{ 0, 223, 17, 17, [this]() { this->Back(); } }
	};
};

#endif