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

#include "StringUtils.hpp"


namespace S2Core {
	const std::vector<std::string> StringUtils::EncodingTable = {
		/* Special. */
		"©", "œ", "¡", "¿", "À", "Á", "Â", "Ã", "Ä", "Å", "Æ", "Ç", "È", "É", "Ê", "Ë",
		"Ì", "Í", "Î", "Ï", "Ñ", "Ò", "Ó", "Ô", "Õ", "Ö", "Ø", "Ù", "Ú", "Ü", "ß", "à",
		"á", "â", "ã", "ä", "å", "æ", "ç", "è", "é", "ê", "ë", "ì", "í", "î", "ï", "ñ",
		"ò", "ó", "ô", "õ", "ö", "ø", "ù", "ú", "û", "ü", "º", "ª", "…", "™", "", "®", ""
	};

	/*
		Decode bytes to the International Encoding (EUR, USA).

		const std::vector<uint8_t> &DataToDecode: A byte vector that contains the data that should be decoded to a string.
	*/
	std::string StringUtils::DecodeInternational(const std::vector<uint8_t> &DataToDecode) {
		if (DataToDecode.empty()) return "";

		std::string Str = "";

		for (size_t Idx = 0; Idx < DataToDecode.size(); Idx++) {
			const uint8_t Byte = DataToDecode[Idx];

			/* Out of range, or the last check being a new line which may not be great on names. */
			if ((Byte >= 0x1 && Byte <= 0x9) || (Byte >= 0xB && Byte <= 0x1F) || (Byte >= 0xBC) || (Byte == 0xA)) break;

			/* 0x7B - 0xBB is custom encoding, the other one is ASCII. */
			else if (Byte >= 0x7B && Byte <= 0xBB) Str += S2Core::StringUtils::EncodingTable[Byte - 0x7B];
			else {
				if (Byte == 0x0) break;
				Str += Byte;
			}
		}

		return Str;
	};


	/*
		Encode a string to a vector of bytes to the International Encoding (EUR, USA).

		const std::string &Str: The string to encode.
	*/
	std::vector<uint8_t> StringUtils::EncodeInternational(const std::string &Str) {
		if (Str.empty()) return { };

		bool Found = false;
		size_t EncodingLen = 0, EncodingMatchCount = 0;
		std::vector<uint8_t> StringBytes = { };

		/* Get the String Bytes. */
		for (size_t StrIdx = 0; StrIdx < Str.size(); StrIdx++) {
			const uint8_t Byte = (uint8_t)Str[StrIdx];

			/* Values that are too low for ASCII and 0xA for a new line may not be the greatest, so it's blocked for now until there is a valid reason to use one lol. */
			if ((Byte >= 0x1 && Byte <= 0x9) || (Byte >= 0xB && Byte <= 0x1F) || (Byte == 0xA)) break;
			else {
				Found = false;

				/* Check for ASCII. */
				for (size_t ASCIIIdx = 0x20; ASCIIIdx < 0x7A; ASCIIIdx++) {
					if (ASCIIIdx == Byte) {
						Found = true;
						StringBytes.push_back(ASCIIIdx);
						break;
					}
				}

				if (!Found) {
					/* Check for the Special Encoding. */
					for (size_t EncodingIdx = 0x0; EncodingIdx < S2Core::StringUtils::EncodingTable.size(); EncodingIdx++) {
						EncodingLen = S2Core::StringUtils::EncodingTable[EncodingIdx].size(); // Get the length of the encoding character.
						EncodingMatchCount = 0;

						if (EncodingLen == 0) continue; // There are also characters that have a size of 0, so skip those to not cause an infinity loop.

						for (size_t EncodingLenIdx = 0; EncodingLenIdx < EncodingLen; EncodingLenIdx++) {
							if (Str.size() - 1 < StrIdx + EncodingLenIdx) break;
							if (Str[StrIdx + EncodingLenIdx] == S2Core::StringUtils::EncodingTable[EncodingIdx][EncodingLenIdx]) EncodingMatchCount++;
							else break;
						}

						/* If the encoding length matches with the equal characters, then we got the right character. */
						if (EncodingMatchCount == EncodingLen) {
							Found = true;
							StringBytes.push_back(EncodingIdx + 0x7B);
							StrIdx += EncodingLen - 1;
							break;
						}
					}

					/* If nothing matches here either, end it with a NULL Terminator. */
					if (!Found) {
						StringBytes.push_back(0);
						break;
					}
				}
			}
		}

		return StringBytes;
	};
};