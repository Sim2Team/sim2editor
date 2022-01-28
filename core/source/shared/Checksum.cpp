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

#include "Checksum.hpp"


namespace S2Core {
	/*
		I rewrote the Checksum calculation function, to WORK with both, GBA and NDS versions.

		const uint8_t *Buffer: The SavBuffer.
		const uint16_t StartOffs: The Start offset. (NOTE: You'll have to do '/ 2', because it's 2 byte based).
		const uint16_t EndOffs: The End offset. Same NOTE as above applies here as well.
		const std::vector<uint32_t> &Skipoffs:
			The Offsets which to skip (Only needed on the NDS version, also same NOTE as above applies as well).
	*/
	uint16_t Checksum::Calc(const uint8_t *Buffer, const uint16_t StartOffs, const uint16_t EndOffs, const std::vector<uint32_t> &SkipOffs) {
		uint8_t Byte1 = 0, Byte2 = 0;
		bool Skip = false;

		for (uint16_t Idx = StartOffs; Idx < EndOffs; Idx++) {
			if (!SkipOffs.empty()) { // Only do this, if it isn't empty.
				for (uint8_t I = 0; I < SkipOffs.size(); I++) {
					if (Idx == SkipOffs[I]) {
						Skip = true; // We'll skip those bytes here.
						break;
					}
				}
			}

			if (Skip) {
				Skip = false;
				continue;
			}

			if (Buffer[Idx * 2] + Byte1 > 255) Byte2++;
			Byte1 += Buffer[Idx * 2];
			Byte2 += Buffer[(Idx * 2) + 1];
		}

		Byte2++;
		return (256 * (uint8_t)-Byte2) + (uint8_t)-Byte1;
	};
};