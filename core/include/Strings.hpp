/*
*   This file is part of Sim2Editor-CPPCore
*   Copyright (C) 2020-2022 Sim2Team
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

#ifndef _SIM2EDITOR_CPP_CORE_STRINGS_HPP
#define _SIM2EDITOR_CPP_CORE_STRINGS_HPP

#include <string>
#include <vector>


namespace S2Core {
	namespace Strings {
		/* GBA Strings. */
		extern const std::vector<std::string> GBACastNames_DE, GBACastNames_EN; // GBA Casts.
		extern const std::vector<std::string> GBASocialMoveNames_DE, GBASocialMoveNames_EN; // GBA Social Moves.
		extern const std::vector<std::string> GBAEpisodeNames_DE, GBAEpisodeNames_EN; // GBA Episodes.
		extern const std::vector<std::string> GBASkillPointNames_DE, GBASkillPointNames_EN; // GBA Skill Points.
		extern const std::vector<std::string> GBAItemNames_EN; // GBA Items.
		extern const std::vector<std::string> GBAMinigameNames_DE, GBAMinigameNames_EN; // GBA Minigames.

		/* NDS Strings. */
		extern const std::vector<std::string> NDSPaintingRankNames_EN; // NDS Painting Ranks.
		extern const std::vector<std::string> NDSSkillPointNames_DE, NDSSkillPointNames_EN; // NDS Skill Points.
	};
};

#endif