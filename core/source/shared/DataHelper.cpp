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

#include "DataHelper.hpp"
#include "StringUtils.hpp"


namespace S2Core {
	/*
		Return a bit from a Buffer.

		const uint8_t *Buffer: The Buffer.
		const uint32_t Offs: The Offset to read from.
		const uint8_t BitIndex: The Bit index ( 0 - 7 ).
	*/
	const bool DataHelper::ReadBit(const uint8_t *Buffer, const uint32_t Offs, const uint8_t BitIndex) {
		if (!Buffer || BitIndex > 7) return false;

		return (Buffer[Offs] >> BitIndex & 1) != 0;
	};

	/*
		Set a bit to a Buffer.

		uint8_t *Buffer: The Buffer.
		const uint32_t Offs: The Offset to write to.
		const uint8_t BitIndex: The Bit index ( 0 - 7 ).
		const bool IsSet: If it's set (1) or not (0).

		Returns true if success, false if not.
	*/
	bool DataHelper::WriteBit(uint8_t *Buffer, const uint32_t Offs, const uint8_t BitIndex, const bool IsSet) {
		if (!Buffer || BitIndex > 7) return false;

		Buffer[Offs] &= ~(1 << BitIndex);
		Buffer[Offs] |= (IsSet ? 1 : 0) << BitIndex;

		return true;
	};


	/*
		Read Lower / Upper Bits.

		const uint8_t *Buffer: The Buffer.
		const uint32_t Offs: The offset where to read from.
		const bool First: If Reading from the first four bits, or second.
	*/
	const uint8_t DataHelper::ReadBits(const uint8_t *Buffer, const uint32_t Offs, const bool First) {
		if (!Buffer) return 0x0;

		if (First) return (Buffer[Offs] & 0xF); // Bit 0 - 3.
		else return (Buffer[Offs] >> 4); // Bit 4 - 7.
	};

	/*
		Write Lower / Upper Bits.

		uint8_t *Buffer: The Buffer.
		const uint32_t Offs: The offset where to write to.
		const bool First: If Writing on the first four bits, or second.
		const uint8_t Data: The Data to write.

		Returns true if success, false if not.
	*/
	bool DataHelper::WriteBits(uint8_t *Buffer, const uint32_t Offs, const bool First, const uint8_t Data) {
		if (Data > 0xF || !Buffer) return false;

		if (First) Buffer[Offs] = (Buffer[Offs] & 0xF0) | (Data & 0xF); // Bit 0 - 3.
		else Buffer[Offs] = (Buffer[Offs] & 0x0F) | (Data << 4); // Bit 4 - 7.

		return true;
	};


	/*
		Read a string from a Buffer.

		const uint8_t *Buffer: The SavBuffer.
		const uint32_t Offs: The Offset from where to read from.
		const uint32_t Length: The Length to read.
		const bool International: If reading into the International (EUR, USA) format or not.

		TODO: Japanese NDS Version String Handling.
	*/
	const std::string DataHelper::ReadString(const uint8_t *Buffer, const uint32_t Offs, const uint32_t Length, const bool International) {
		if (!Buffer) return "";
		std::vector<uint8_t> Bytes = { };

		for (int Idx = 0; Idx < (int)Length; Idx++) {
			if (Buffer[Offs + Idx] == 0x0) break; // 0x0 -> End.

			Bytes.push_back(Buffer[Offs + Idx]);
		}

		if (International) return S2Core::StringUtils::DecodeInternational(Bytes);
		else return ""; // Japanese TODO.
	};

	/*
		Write a string to a Buffer.

		uint8_t *Buffer: The SavBuffer.
		const uint32_t Offs: The offset from where to write to.
		const uint32_t Length: The length to write.
		const std::string &Str: The string to write.
		const bool International: If writing to the International (EUR, USA) format or not.

		TODO: Japanese NDS Version String Handling.

		Returns true if success, false if not.
	*/
	bool DataHelper::WriteString(uint8_t *Buffer, const uint32_t Offs, const uint32_t Length, const std::string &Str, const bool International) {
		if (!Buffer) return false;
		
		std::vector<uint8_t> Bytes = { };
		if (International) Bytes = S2Core::StringUtils::EncodeInternational(Str);

		for (int Idx = 0; Idx < (int)Length; Idx++) {
			if (Idx < (int)Bytes.size()) Buffer[Offs + Idx] = Bytes[Idx]; // The index is inside the string length, so write that.
			else Buffer[Offs + Idx] = 0; // Index outside the string length.. so write 0.
		}

		return true;
	};
};