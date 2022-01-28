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

#ifndef _SIM2EDITOR_CPP_CORE_GBA_SOCIAL_MOVE_HPP
#define _SIM2EDITOR_CPP_CORE_GBA_SOCIAL_MOVE_HPP

#include "../shared/CoreCommon.hpp"


namespace S2Core {
	enum class SocialMoveFlag : uint8_t { Locked = 0x0, Unlocked = 0x1, Blocked = 0x2 };

	class GBASocialMove {
	public:
		GBASocialMove(const uint32_t Offs, const uint8_t Move)
			: Move(Move), Offs(Offs) { };
		uint8_t Index() const { return this->Move; };

		SocialMoveFlag Flag() const;
		void Flag(const SocialMoveFlag V);

		uint8_t Level() const;
		void Level(const uint8_t V);

		uint8_t BlockedHours() const;
		void BlockedHours(const uint8_t V);
	private:
		uint8_t Move = 0;
		uint32_t Offs = 0;
	};
};

#endif