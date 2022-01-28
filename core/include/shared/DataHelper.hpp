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

#ifndef _SIM2EDITOR_CPP_CORE_DATA_HELPER_HPP
#define _SIM2EDITOR_CPP_CORE_DATA_HELPER_HPP

#include "CoreCommon.hpp"


namespace S2Core {
	namespace DataHelper {
		/*
			Read from a Buffer.

			const uint8_t *Buffer: The Buffer.
			const uint32_t Offs: The Offset from where to read.
		*/
		template <typename T>
		T Read(const uint8_t *Buffer, const uint32_t Offs) {
			if (!Buffer) return 0; // Return 0, if nullptr.

			T Res = 0;
			memcpy(&Res, Buffer + Offs, sizeof(T));
			return Res;
		};

		/*
			Write to a Buffer.

			uint8_t *Buffer: The Buffer.
			const uint32_t Offs: The Offset where to write to.
			T Data: The data which to write.

			Returns true if success, false if not.
		*/
		template <typename T>
		bool Write(uint8_t *Buffer, const uint32_t Offs, T Data) {
			if (!Buffer) return false;

			for (size_t Idx = 0; Idx < sizeof(T); Idx++) {
				Buffer[Offs + Idx] = (uint8_t)Data;
				Data >>= 8; // Go to next byte.
			}

			return true;
		};

		/* BIT stuff. */
		const bool ReadBit(const uint8_t *Buffer, const uint32_t Offs, const uint8_t BitIndex);
		bool WriteBit(uint8_t *Buffer, const uint32_t Offs, const uint8_t BitIndex, const bool IsSet);
		const uint8_t ReadBits(const uint8_t *Buffer, const uint32_t Offs, const bool First = true);
		bool WriteBits(uint8_t *Buffer, const uint32_t Offs, const bool First = true, const uint8_t Data = 0x0);

		/* String stuff. */
		const std::string ReadString(const uint8_t *Buffer, const uint32_t Offs, const uint32_t Length, const bool International = true);
		bool WriteString(uint8_t *Buffer, const uint32_t Offs, const uint32_t Length, const std::string &Str, const bool International = true);
	};
};

#endif