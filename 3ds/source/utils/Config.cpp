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

#include "Config.hpp"
#include <unistd.h>

/*
	Loads the Configuration file.
*/
void Config::Load() {
	if (access("sdmc:/3ds/Sim2Editor/Config.json", F_OK) != 0) this->Initialize();

	FILE *File = fopen("sdmc:/3ds/Sim2Editor/Config.json", "r");
	this->CFG = nlohmann::json::parse(File, nullptr, false);
	fclose(File);

	if (!this->CFG.is_discarded()) {
		this->PointerSpeed(this->Get<nlohmann::json::number_integer_t>("PointerSpeed", this->PointerSpeed()));
		this->CreateBackups(this->Get<nlohmann::json::boolean_t>("CreateBackups", this->CreateBackups()));
		this->SAVPath(this->Get<std::string>("SAVPath", this->SAVPath()));
		this->FirstStart(this->Get<nlohmann::json::boolean_t>("FirstStart", this->FirstStart()));
	}
}


/*
	Initializes the Configuration file properly as a JSON.
*/
void Config::Initialize() {
	FILE *Temp = fopen("sdmc:/3ds/Sim2Editor/Config.json", "w");
	char Tmp[2] = { '{', '}' }; // Init as valid JSON.
	fwrite(Tmp, sizeof(Tmp), 1, Temp);
	fclose(Temp);
}


/*
	SAV changes to the Configuration, if changes made.
*/
void Config::Sav() {
	if (this->ChangesMade) {
		this->Set<nlohmann::json::number_integer_t>("PointerSpeed", this->PointerSpeed());
		this->Set<nlohmann::json::boolean_t>("CreateBackups", this->CreateBackups());
		this->Set<std::string>("SAVPath", this->SAVPath());
		this->Set<nlohmann::json::boolean_t>("FirstStart", this->FirstStart());

		FILE *Out = fopen("sdmc:/3ds/Sim2Editor/Config.json", "w");
		/* Write changes to file. */
		const std::string Dump = this->CFG.dump(1, '\t');
		fwrite(Dump.c_str(), 1, this->CFG.dump(1, '\t').size(), Out);
		fclose(Out);
	}
}