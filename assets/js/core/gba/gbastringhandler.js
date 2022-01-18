/*
*   This file is part of Sim2Editor-JSCore
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

const EncodingTable = [
	"©", "œ", "¡", "¿", "À", "Á", "Â", "Ã", "Ä", "Å", "Æ", "Ç", "È", "É", "Ê", "Ë",
	"Ì", "Í", "Î", "Ï", "Ñ", "Ò", "Ó", "Ô", "Õ", "Ö", "Ø", "Ù", "Ú", "Ü", "ß", "à",
	"á", "â", "ã", "ä", "å", "æ", "ç", "è", "é", "ê", "ë", "ì", "í", "î", "ï", "ñ",
	"ò", "ó", "ô", "õ", "ö", "ø", "ù", "ú", "û", "ü", "º", "ª", "…", "™", "", "®", ""
];


/*
	Handle the Sims 2 GBA specific SavData String Read stuff.

	DTView: The DataView of the SavData.
	Offs: The Start offset from where to read.
	Len: The length to read.
*/
export function GBAStringHandler_ReadString(DTView, Offs, Len) {
	let Str = "";

	for (let Idx = 0; Idx < Len; Idx++) {
		let Byte = DTView.getUint8(Offs + Idx);

		/* Out of range, or the last check being a new line which may not be great on names. */
		if ((Byte >= 0x1 && Byte <= 0x9) || (Byte >= 0xB && Byte <= 0x1F) || (Byte >= 0xBC) || (Byte == 0xA)) break;
		else if (Byte >= 0x7B && Byte <= 0xBB) Str += EncodingTable[Byte - 0x7B];
		else {
			if (Byte == 0x0) break;
			Str += String.fromCharCode(Byte);
		}
	}

	return Str;
};


/*
	Handle the Sims 2 GBA specific SavData String Write stuff.

	Str: The string to write.
	Len: The length to write.

	NOTE: This returns a byte array, which you'd have to handle for the actual SaveData Write.
*/
export function GBAStringHandler_GetStringArray(Str, Len) {
	let ByteArray = [ ];

	let Found = false;
	let EncodingLen = 0, EncodingMatchCount = 0;
	let FillEmpty = false;

	for (let Idx = 0; Idx < Len; Idx++) {
		if (FillEmpty) ByteArray.push(0); // Only fill with Zero's.
		else if (Str.len < Idx) {
			FillEmpty = true;
			ByteArray.push(0);
		
		/* First check for invalid ranges, then handle ASCII and special Encoding stuff. */
		} else {
			let Byte = Str.codePointAt(Idx);

			if ((Byte >= 0x1 && Byte <= 0x9) || (Byte >= 0xB && Byte <= 0x1F) || (Byte == 0xA)) {
				FillEmpty = true;
				ByteArray.push(0);

			} else {
				Found = false;

				/* Check for ASCII. */
				for (let ASCIIIdx = 0x20; ASCIIIdx < 0x7A; ASCIIIdx++) {
					if (Byte == ASCIIIdx) {
						ByteArray.push(ASCIIIdx);
						Found = true;
						break;
					}
				}

				if (!Found) {
					/* Check for the Special Encoding. */
					for (let EncodingIdx = 0x0; EncodingIdx < EncodingTable.length; EncodingIdx++) {
						EncodingLen = EncodingTable[EncodingIdx].length; // Get the length of the encoding character.
						EncodingMatchCount = 0;

						if (EncodingLen == 0) continue; // There are also characters that have a size of 0, so skip those to not cause an infinity loop.

						for (let EncodingLenIdx = 0; EncodingLenIdx < EncodingLen; EncodingLenIdx++) {
							if (Str.length - 1 < Idx + EncodingLenIdx) break;
							if (Str[Idx + EncodingLenIdx] == EncodingTable[EncodingIdx][EncodingLenIdx]) EncodingMatchCount++;
							else break;
						}

						/* If the encoding length matches with the equal characters, then we got the right character. */
						if (EncodingMatchCount == EncodingLen) {
							Found = true;
							ByteArray.push(EncodingIdx + 0x7B);
							Idx += EncodingLen - 1;
							break;
						}
					}

					/* If nothing matches here either, end it with a NULL Terminator. */
					if (!Found) {
						FillEmpty = true;
						ByteArray.push(0);
					}
				}
			}
		}
	}

	return ByteArray;
};