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

#ifndef _SIM2EDITOR_CPP_CORE_GBA_EPISODE_HPP
#define _SIM2EDITOR_CPP_CORE_GBA_EPISODE_HPP

#include "../shared/CoreCommon.hpp"


namespace S2Core {
	class GBAEpisode {
	public:
		GBAEpisode(const uint8_t Slot, const uint8_t Episode, const uint8_t Move = 0x0)
			: Episode(Episode), Offs((Slot * 0x1000) + this->SetOffset(std::min<uint8_t>(Move, 10))) { };
		uint8_t Index() const { return this->Episode; };

		uint8_t Rating(const uint8_t Category) const;
		void Rating(const uint8_t Category, const uint8_t V);

		bool Unlocked() const;
		void Unlocked(const bool V);
		bool Played() const;
		void Played(const bool V);
	private:
		uint8_t Episode = 0;
		uint32_t Offs = 0;

		static constexpr uint32_t EPOffs[11] = { 0x104, 0x10E, 0x122, 0x11D, 0x131, 0x127, 0x14A, 0x140, 0x118, 0x16D, 0x168 }; // 11 Episodes.

		/* Sets the base offset for the Episodes. */
		uint32_t SetOffset(const uint8_t Move) const { return this->EPOffs[this->Episode] + (Move * 0x6); };
	};
};

#endif