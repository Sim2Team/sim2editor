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
	Calculates the Checksum and returns it as an uint16_t.

	Buffer: The Save Buffer.
	StartOffs: The Start offset. (NOTE: You'll have to do '/ 2', because it's 2 byte based).
	EndOffs: The End offset. Same NOTE as above applies here as well.
	Skipoffs: The Offsets which to skip. same NOTE as above applies as well).
*/
export function Checksum_Calc(Buffer, StartOffs, EndOffs, SkipOffs) {
	if (!Buffer) return -1;

	let Checksum = 0;

	for(let Index = StartOffs; Index < EndOffs; Index++) {
		if (SkipOffs != undefined && SkipOffs.includes(Index)) continue; // Skip, if found in the Skip Offsets.

		Checksum = (Checksum + Buffer.getUint16(Index * 2, true)) % 0x10000; // Don't go over an uint16_t, hence % 0x10000.
	}

	return (0x10000 - Checksum) % 0x10000;
};



/*
	Calculate the GBA Slot's checksum.

	Buffer: The Savebuffer.
	Slot: The slot to calculate.
*/
export function Checksum_CalcGBASlot(Buffer, Slot) {
	return Checksum_Calc(Buffer, (Slot * 0x1000) / 2, ((Slot * 0x1000) + 0xFFE) / 2);
};


/*
	Calculate the GBA Settings checksum.

	Buffer: The Savebuffer.
*/
export function Checksum_CalcGBASettings(Buffer) {
	return Checksum_Calc(Buffer, 0x0, (0x18 / 2), [(0xE / 2)]);
};



/*
	Calculate the NDS Slot's Main checksum.

	Buffer: The Savebuffer.
	Slot: The slot to calculate.
*/
export function Checksum_CalcNDSSlotMain(Buffer, Slot) {
	return Checksum_Calc(
		Buffer, ((Slot * 0x1000) + 0x10) / 2, ((Slot * 0x1000) + 0x1000) / 2,
		[(((Slot * 0x1000) + 0x12) / 2), (((Slot * 0x1000) + 0x28) / 2)] // Skipped Offsets.
	);
};


/*
	Calculate the NDS Slot's Shared checksum.

	Buffer: The Savebuffer.
	Slot: The slot to calculate.
*/
export function Checksum_CalcNDSSlotShared(Buffer, Slot) {
	return Checksum_Calc(
		Buffer, ((Slot * 0x1000) + 0x14) / 2, ((Slot * 0x1000) + 0x1000) / 2
	);
};


/*
	Calculate the NDS Slot's Header checksum.

	Buffer: The Savebuffer.
	Slot: The slot to calculate.
*/
export function Checksum_CalcNDSSlotHeader(Buffer, Slot) {
	return Checksum_Calc(
		Buffer, (Slot * 0x1000) / 2, ((Slot * 0x1000) + 0x13) / 2, [(((Slot * 0x1000) + 0xE) / 2)]
	);
};