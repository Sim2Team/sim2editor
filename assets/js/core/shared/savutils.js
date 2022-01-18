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


export const GBAIdent = [ 0x53, 0x54, 0x57, 0x4E, 0x30, 0x32, 0x34, 0x0 ]; // GBA Header Identifier.
export const NDSIdent = [ 0x64, 0x61, 0x74, 0x0, 0x1F, 0x0, 0x0, 0x0 ]; // NDS Slot Header Identifier.


/*
	Sav: The Sav class of the active save. It can be a GBASav, or NDSSav or undefined.
	SavName: The name of the Save you loaded.
	SavBuffer: The main Raw Buffer of the Save you loaded.
	SavData: The DataView of the SavBuffer, so you can also read them like 'getUint8(...)' etc.
	SavSize: The size of the Save you loaded.
	SavType: The SavType of the Save you loaded, see below for types and values.

	-1: Invalid.
	 0: Game Boy Advance EUR / USA.
	 1: Nintendo DS USA International.
	 2: Nintendo DS EUR International.
	 3: Nintendo DS JPN Japanese.
*/
export let Sav, SavName, SavBuffer, SavData, SavSize, SavType; // See above.

/* Import Sav classes. */
import { S2Editor_GBASav } from "../gba/gbasav.js";
import { S2Editor_NDSSav } from "../nds/ndssav.js";

/* String Handlers. */
import { GBAStringHandler_ReadString, GBAStringHandler_GetStringArray } from "../gba/gbastringhandler.js";
import { NDSStringHandler_ReadString, NDSStringHandler_GetStringArray } from "../nds/ndsstringhandler.js";


/*
	Detect the SavType of a SavFile.

	Data: The DataView of the SavData.
	Size: The size of the SavFile.

	Returns -1 for Invalid, 0 for GBA and 1 for NDS.
*/
export function SavUtils_DetectType(Data, Size) {
	if (!Data) {
		console.log("No Data provided.");
		return -1;
	}

	let Count = 0, Reg = 0;

	/* Checking SavType here. */
	switch(Size) {
		case 0x10000:
		case 0x20000: // 64, 128 KB is a GBA Size.
			for (let ID = 0; ID < 8; ID++) {
				if (Data.getUint8(ID) == GBAIdent[ID]) Count++;
			}; // Identifier Checks.

			if (Count == 8) return 0;
			else return -1;

		case 0x40000:
		case 0x80000: // 256, 512 KB is a NDS Size.
			for (let Slot = 0; Slot < 5; Slot++) { // Check for all 5 possible Slots.
				Count = 0; // Reset Count here.

				for (let ID = 0; ID < 8; ID++) { // Identifier Checks.
					if (ID == 0x4) { // 0x4 is the region specifier.
						for (Reg = 0; Reg < 3; Reg++) {
							if (Data.getUint8((Slot * 0x1000) + ID) == NDSIdent[ID] + Reg) {
								Count++;
								break;
							}
						}

					} else {
						if (Data.getUint8((Slot * 0x1000) + ID) == NDSIdent[ID]) Count++;
					}
				}

				if (Count == 8) return 1 + Reg;
			}

			return -1; // There were no 8 Count matches on all 5 Slots, hence invalid.

		default:
			return -1;
	}
};


/*
	Load the Sav.

	SavFile: The Savefile.
	LoadCallback: The Action that happens, after the SaveFile is valid and has been read (Like the Menu Handle).
	ErrorCallback: The Action that happens, after the Savefile is loaded, however invalid (Like an error telling something).

	returns -1 for invalid, 0 for GBA, 1, 2 or 3 for NDS.
*/
export function SavUtils_LoadSav(SavFile, LoadCallback, ErrorCallback) {
	if (!SavFile) {
		if (ErrorCallback != undefined) ErrorCallback();
		return -1;
	}

	SavName = SavFile.name;
	SavSize = SavFile.size;

	let Reader = new FileReader();
	Reader.readAsArrayBuffer(SavFile);

	Reader.onload = function() {
		SavBuffer = new Uint8Array(this.result);
		SavData = new DataView(SavBuffer.buffer);
		SavType = SavUtils_DetectType(SavData, SavSize); // Detect SavType.

		switch(SavType) {
			case 0: // GBA EUR / USA.
				Sav = new S2Editor_GBASav(); // We are using a GBA Sav.
				break;

			case 1: // NDS USA.
			case 2: // NDS EUR.
			case 3: // NDS JPN.
				Sav = new S2Editor_NDSSav(SavType - 1); // We are using a NDS Sav.
				break;

			default:
				Sav = undefined; // Invalid Sav.
				break;
		}

		/*
			Returns true if the Sav is not undefined and SavType is between 0 and 3, which is

			0: GBA EUR / USA.
			1: NDS USA.
			2: NDS EUR.
			3: NDS JPN.
		*/
		const State = (Sav != undefined && SavType != undefined && SavType >= 0 && SavType <= 3);

		/* Handle if doing the Loader Callback or Error Callback. */
		if (State) {
			if (LoadCallback != undefined) LoadCallback();

		} else {
			if (ErrorCallback != undefined) ErrorCallback();
		}
	};
};


/*
	Return, if changes have been made.

	Returns false or true, depending on changes made status.
*/
export function SavUtils_ChangesMade() {
	if (SavType == undefined) return false;

	switch(SavType) {
		case 0: // GBA EUR / USA.
		case 1: // NDS USA (International).
		case 2: // NDS EUR (International).
		case 3: // NDS JPN (Japanese).
			return Sav.GetChangesMade();

		default: // Invalid.
			return false;
	}
};


/*
	Read something from the SavData.

	Type: The type to read.
	Offs: Where to read from.

	I used this style, because it seems similar at some point to the C++ version.
*/
export function SavUtils_Read(Type, Offs) {
	if (SavType == undefined || SavType == -1 || SavData == undefined) return 0; // -1 -> Invalid.

	switch(Type) {
		case "uint8_t":
		case "u8":
			return SavData.getUint8(Offs);

		case "uint16_t":
		case "u16":
			return SavData.getUint16(Offs, true);

		case "uint32_t":
		case "u32":
			return SavData.getUint32(Offs, true);

		default:
			return 0;
	}
};


/*
	Write something to the SavData.

	Type: The type to write.
	Offs: Where to write to.
	Data: What to write.

	I used this style, because it seems similar at some point to the C++ version.
*/
export function SavUtils_Write(Type, Offs, Data) {
	if (SavType == undefined || SavType == -1 || SavData == undefined) return; // -1 -> Invalid.

	switch(Type) {
		case "uint8_t":
		case "u8":
			SavData.setUint8(Offs, Math.min(0xFF, Data));
			if (!Sav.GetChangesMade()) Sav.SetChangesMade(true);
			break;

		case "uint16_t":
		case "u16":
			SavData.setUint16(Offs, Math.min(0xFFFF, Data), true);
			if (!Sav.GetChangesMade()) Sav.SetChangesMade(true);
			break;

		case "uint32_t":
		case "u32":
			SavData.setUint32(Offs, Math.min(0xFFFFFFFF, Data), true);
			if (!Sav.GetChangesMade()) Sav.SetChangesMade(true);
			break;
	}
};


/*
	Return a bit from the SavData.

	Offs: The Offset to read from.
	BitIndex: The Bit index ( 0 - 7 ).
*/
export function SavUtils_ReadBit(Offs, BitIndex) {
	if (SavType == undefined || SavType == -1 || SavData == undefined) return; // -1 -> Invalid.

	return (SavUtils_Read("uint8_t", Offs) >> BitIndex & 1) != 0;
};


/*
	Set a bit to the SavData.

	Offs: The Offset to write to.
	BitIndex: The Bit index ( 0 - 7 ).
	IsSet: If it's set (1) or not (0).
*/
export function SavUtils_WriteBit(Offs, BitIndex, IsSet) {
	if (SavType == undefined || SavType == -1 || SavBuffer == undefined) return; // -1 -> Invalid.

	SavBuffer[Offs] &= ~(1 << BitIndex);
	SavBuffer[Offs] |= (IsSet ? 1 : 0) << BitIndex;

	if (!Sav.GetChangesMade()) Sav.SetChangesMade(true);
};


/*
	Read Lower / Upper Bits.

	Offs: The offset where to read from.
	First: If Reading from the first four bits, or second.
*/
export function SavUtils_ReadBits(Offs, First) {
	if (SavType == undefined || SavType == -1 || SavData == undefined) return 0x0;

	if (First) return (SavData.getUint8(Offs) & 0xF); // Bit 0 - 3.
	else return (SavData.getUint8(Offs) >> 4); // Bit 4 - 7.
};


/*
	Write Lower / Upper Bits.

	Offs: The offset where to write to.
	First: If Writing on the first four bits, or second.
	Data: The Data to write.
*/
export function SavUtils_WriteBits(Offs, First, Data) {
	if (Data > 0xF || SavData == undefined || SavType == undefined || SavType == -1) return;

	if (First) SavUtils_Write("uint8_t", Offs, (SavData.getUint8(Offs) & 0xF0) | (Data & 0xF)); // Bit 0 - 3.
	else SavUtils_Write("uint8_t", Offs, (SavData.getUint8(Offs) & 0x0F) | (Data << 4)); // Bit 4 - 7.
};


/*
	Read a String from the SavData.

	Offs: Where to read from.
	Length: The length to read.
*/
export function SavUtils_ReadString(Offs, Length) {
	if (SavType == undefined || SavType == -1 || SavData == undefined) return ""; // -1 -> Invalid.
	let Str = "";

	/* GBA Handling. */
	if (SavType == 0) {
		Str = GBAStringHandler_ReadString(SavData, Offs, Length);

	/* NDS Handling. */
	} else if (SavType >= 1 && SavType <= 3) {
		Str = NDSStringHandler_ReadString(SavData, Offs, Length);
	}

	return Str;
};


/*
	Write a String to the SavData.

	Offs: Where to write to.
	Length: The length to write.
	Str: What to write.
*/
export function SavUtils_WriteString(Offs, Length, Str) {
	if (SavType == undefined || SavType == -1 || Str == undefined || SavData == undefined) return;
	let Buffer = [ ];

	/* GBA Handling. */
	if (SavType == 0) {
		Buffer = GBAStringHandler_GetStringArray(Str, Length);

	/* NDS Handling. */
	} else if (SavType >= 1 && SavType <= 3) {
		Buffer = NDSStringHandler_GetStringArray(Str, Length);
	}

	/* Now write the String Buffer to the SavData. */
	for (let Idx = 0; Idx < Buffer.length; Idx++) SavData.setUint8(Offs + Idx, Buffer[Idx]);

	if (!Sav.GetChangesMade()) Sav.SetChangesMade(true); // Changes have been made.
};


/*
	Call this when you are done.

	This updates the checksums etc and downloads the SavFile.
	NOTE: Everything is being reset which is Sav Related, keep that in mind.
*/
export function SavUtils_Finish(ShouldReset) {
	if (SavType == undefined || SavType == -1 || SavType == undefined) return;

	Sav.Finish(); // Finish Sav Call.

	/* Setup and prepare Download Click. */
	let _Blob = new Blob([SavBuffer], { type: "application/octet-stream" });
	let Element = document.createElement('a');
	let Url = window.URL.createObjectURL(_Blob);
	Element.href = Url;
	Element.download = SavName;
	Element.click(); // Download the SaveFile.

	/* Make the reset optional, i guess. */
	if (ShouldReset == true) {
		/* Reset the Sav. */
		SavType = -1;
		SavName = '';
		Sav = undefined;
		SavData = undefined;
		SavBuffer = undefined;
		SavSize = 0;
	}
};