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

#ifndef _SIM2EDITOR_CONFIG_HPP
#define _SIM2EDITOR_CONFIG_HPP

#include "JSON.hpp"

class Config {
public:
	Config() { this->Load(); }
	void Load();
	void Initialize();
	void Sav();

	/* The speed of the Pointer scroll. */
	uint8_t PointerSpeed() const { return this->VPointerSpeed; }
	void PointerSpeed(const uint8_t V) { this->VPointerSpeed = V; if (!this->ChangesMade) this->ChangesMade = true; }

	/* If Creating Backups or not. */
	bool CreateBackups() const { return this->VCreateBackups; }
	void CreateBackups(const bool V) { this->VCreateBackups = V; if (!this->ChangesMade) this->ChangesMade = true; }

	/* The default SAVPath. */
	std::string SAVPath() const { return this->VSAVPath; }
	void SAVPath(const std::string &V) { this->VSAVPath = V; if (!this->ChangesMade) this->ChangesMade = true; }

	/* If it's the first Start (Displays a first message then) or not. */
	bool FirstStart() const { return this->VFirstStart; }
	void FirstStart(const bool V) { this->VFirstStart = V; if (!this->ChangesMade) this->ChangesMade = true; }
private:
	template <typename T>
	T Get(const std::string &Key, const T IfNotFound) {
		if (this->CFG.is_discarded() || !this->CFG.contains(Key)) return IfNotFound;

		return this->CFG.at(Key).get_ref<const T &>();
	}

	template <typename T>
	void Set(const std::string &Key, const T Data) {
		if (!this->CFG.is_discarded()) this->CFG[Key] = Data;
	}

	bool ChangesMade = false;
	nlohmann::json CFG = nullptr;
	uint8_t VPointerSpeed = 4;
	bool VCreateBackups = true, VFirstStart = true;
	std::string VSAVPath = "sdmc:/";
};

#endif