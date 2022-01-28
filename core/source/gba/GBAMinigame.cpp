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

#include "GBAMinigame.hpp"
#include "../shared/SavUtils.hpp"


namespace S2Core {
	/* Get and Set if you played that game already today. */
	bool GBAMinigame::Played() const { return SavUtils::ReadBit(this->Offs, this->Game); };
	void GBAMinigame::Played(const bool V) { SavUtils::WriteBit(this->Offs, this->Game, V); };

	/* Get and Set the Minigame Level. */
	uint8_t GBAMinigame::Level() const { return SavUtils::Read<uint8_t>(this->Offs + 0x24 + this->Game); };
	void GBAMinigame::Level(const uint8_t V, const bool MetaData) {
		SavUtils::Write<uint8_t>(this->Offs + 0x24 + this->Game, std::min<uint8_t>(5, V));

		/* Optionally: Set to Metadata / Settings as well. */
		if (MetaData) SavUtils::WriteBits(0x10 + (this->Game / 2), ((this->Game % 2) == 0), std::min<uint8_t>(5, V));
	};
};