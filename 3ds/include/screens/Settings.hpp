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

#ifndef _SIM2EDITOR_SETTINGS_HPP
#define _SIM2EDITOR_SETTINGS_HPP

#include "screen.hpp"
#include "Pointer.hpp"
#include <vector>

class Settings : public Screen {
public:
	Settings() { Pointer::SetPos(this->Positions[0]); }
	void Draw(void) const override;
	void Logic(u32 hDown, u32 hHeld, touchPosition touch) override;
private:
	enum class SettingsTab : uint8_t { Configuration, AppInfo };

	SettingsTab Tab = SettingsTab::Configuration;
	const std::vector<std::string> TabNames = { "Configuration", "App Information" };

	void DrawCredits() const;
	void DrawPages() const;
	void DrawSettingStripe() const;

	void ConfigTab();
	void AppinfoTab();
	void ToggleBackups();
	void TogglePointer();
	void SetDefaultPath();
	void SetPointerSpeed();
	void Back();

	const std::vector<PointerStr> Positions = {
		{ 0, 0, 160, 20, [this]() { this->ConfigTab(); } },
		{ 160, 0, 160, 20, [this]() { this->AppinfoTab(); } },

		{ 263, 39, 24, 24, [this]() { this->ToggleBackups(); } },
		{ 263, 79, 24, 24, [this]() { this->SetDefaultPath(); } },
		{ 263, 119, 24, 24, [this]() { this->SetPointerSpeed(); } },
		{ 263, 159, 24, 24 },
		{ 263, 199, 24, 24 }, // Unused yet.
		{ 0, 223, 17, 17, [this]() { this->Back(); } }
	};
};

#endif