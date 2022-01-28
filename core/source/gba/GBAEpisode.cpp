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

#include "GBAEpisode.hpp"
#include "../shared/SavUtils.hpp"


namespace S2Core {
	/* Get and Set Episode Ratings. */
	uint8_t GBAEpisode::Rating(const uint8_t Category) const { return SavUtils::Read<uint8_t>(this->Offs + std::min<uint8_t>(3, Category)); };
	void GBAEpisode::Rating(const uint8_t Category, const uint8_t V) { SavUtils::Write<uint8_t>(this->Offs + std::min<uint8_t>(3, Category), std::min<uint8_t>(25, V)); };

	/* Get and Set the Unlocked State. */
	bool GBAEpisode::Unlocked() const { return SavUtils::ReadBit(this->Offs + 0x4, 0x0); };
	void GBAEpisode::Unlocked(const bool V) { SavUtils::WriteBit(this->Offs + 0x4, 0x0, V); };

	/* Get and Set the Played State. */
	bool GBAEpisode::Played() const { return SavUtils::ReadBit(this->Offs + 0x4, 0x1); };
	void GBAEpisode::Played(const bool V) { SavUtils::WriteBit(this->Offs + 0x4, 0x1, V); };
};