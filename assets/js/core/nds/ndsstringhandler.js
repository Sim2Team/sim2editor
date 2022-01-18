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


/*
	TODO: This whole file, because that game supports Japanese as well which would be pain.
*/


/*
	The character whitelist for now until it's fully implemented.
*/
const CurrentWhiteList = [
	/* UPPERCASE characters. */
	'A', 'B', 'C', 'D', 'E', 'F', 'G',
	'H', 'I', 'J', 'K', 'L', 'M',
	'N', 'O', 'P', 'Q', 'R', 'S',
	'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
	/* UPPERCASE Numbers. */
	'0', '1', '2', '3', '4',
	'5', '6', '7', '8', '9',
	/* LOWERCASE characters. */
	'a', 'b', 'c', 'd', 'e', 'f', 'g',
	'h', 'i', 'j', 'k', 'l', 'm',
	'n', 'o', 'p', 'q', 'r', 's',
	't', 'u', 'v', 'w', 'x', 'y', 'z',
	/* LOWERCASE Special signs. */
	'!', '+', '#', '$', '%',
	'&', '_', '*', '(', ')'
];


/*
	Handle the Sims 2 NDS specific SavData String Read stuff.

	DTView: The DataView of the SavData.
	Offs: The Start offset from where to read.
	Len: The length to read.

	NOTE: TODO - handle properly.
*/
export function NDSStringHandler_ReadString(DTView, Offs, Len) {
	let Str = "";

	for (let Idx = 0; Idx < Len; Idx++) {
		if (DTView.getUint8(Offs + Idx) == 0x0) break; // Do not continue to read.

		Str += String.fromCharCode(DTView.getUint8(Offs + Idx));
	}

	return Str;
};


/*
	Handle the Sims 2 NDS specific SavData String Write stuff.

	Str: The string to write.
	Len: The length to write.

	NOTE: This returns a byte array, which you'd have to handle for the actual SaveData Write.
	NOTE: TODO - handle properly.
*/
export function NDSStringHandler_GetStringArray(Str, Len) {
	let ByteArray = [ ];
	let Index = 0, Filler = false;

	while(Index < Len) {
		Index++;

		if (Filler) ByteArray.push(0);
		else {
			let CouldFind = false;

			for (let Idx = 0; Idx < 72; Idx++) {
				if (Str.charAt(Index - 1) == CurrentWhiteList[Idx]) {
					ByteArray.push(Str.charCodeAt(Index - 1));
					CouldFind = true;
					break;
				}
			}

			if (!CouldFind) {
				Filler = true;
				ByteArray.push(0);
			}
		}
	}

	return ByteArray;
};