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


import { Checksum_CalcNDSSlotHeader, Checksum_CalcNDSSlotMain, Checksum_CalcNDSSlotShared } from "../shared/checksum.js";
import { SavUtils_Read, SavUtils_Write, SavUtils_WriteString, SavUtils_ReadString, SavData } from "../shared/savutils.js";


export class S2Editor_NDSSlot {
	/* Region is important for later i suppose because of Japanese. */
	constructor(Slot, Region) {
		this.Offs = (Slot * 0x1000);
		this.Slot = Slot;
		this.Region = Region;
	};

	/* Get and Set Simoleons. */
	Simoleons(V) {
		if (V != undefined) SavUtils_Write("uint32_t", this.Offs + 0x2C, Math.min(999999, V));
		else return SavUtils_Read("uint32_t", this.Offs + 0x2C);
	};

	/* Get and Set Name. */
	Name(V) {
		if (V != undefined) SavUtils_WriteString(this.Offs + 0x30, 0x7, V);
		else return SavUtils_ReadString(this.Offs + 0x30, 0x7);
	};

	/* Get and Set Nuclear Fuelrods. */
	Fuelrods(V) {
		if (V != undefined) SavUtils_Write("uint8_t", this.Offs + 0xBC, Math.min(250, V));
		else return SavUtils_Read("uint8_t", this.Offs + 0xBC);
	};

	/* Get and Set License Plates. */
	Plates(V) {
		if (V != undefined) SavUtils_Write("uint8_t", this.Offs + 0xBD, Math.min(250, V));
		else return SavUtils_Read("uint8_t", this.Offs + 0xBD);
	};

	/* Get and Set Strange Gourds. */
	Gourds(V) {
		if (V != undefined) SavUtils_Write("uint8_t", this.Offs + 0xBE, Math.min(250, V));
		else return SavUtils_Read("uint8_t", this.Offs + 0xBE);
	};

	/* Get and Set Alien Spaceship Parts. */
	Spaceship(V) {
		if (V != undefined) SavUtils_Write("uint8_t", this.Offs + 0xBF, Math.min(250, V));
		else return SavUtils_Read("uint8_t", this.Offs + 0xBF);
	};

	/* Get and Set Creativity Skill Points. */
	Creativity(V) {
		if (V != undefined) SavUtils_Write("uint8_t", this.Offs + 0xDF, Math.min(10, V));
		else return SavUtils_Read("uint8_t", this.Offs + 0xDF);
	};

	/* Get and Set Business Skill Points. */
	Business(V) {
		if (V != undefined) SavUtils_Write("uint8_t", this.Offs + 0xE0, Math.min(10, V));
		else return SavUtils_Read("uint8_t", this.Offs + 0xE0);
	};

	/* Get and Set Body Skill Points. */
	Body(V) {
		if (V != undefined) SavUtils_Write("uint8_t", this.Offs + 0xE1, Math.min(10, V));
		else return SavUtils_Read("uint8_t", this.Offs + 0xE1);
	};

	/* Get and Set Charisma Skill Points. */
	Charisma(V) {
		if (V != undefined) SavUtils_Write("uint8_t", this.Offs + 0xE2, Math.min(10, V));
		else return SavUtils_Read("uint8_t", this.Offs + 0xE2);
	};

	/* Get and Set Mechanical Skill Points. */
	Mechanical(V) {
		if (V != undefined) SavUtils_Write("uint8_t", this.Offs + 0xE3, Math.min(10, V));
		else return SavUtils_Read("uint8_t", this.Offs + 0xE3);
	};

	/* Get and Set the Pocket Item Count. */
	PocketCount(V) {
		if (V != undefined) SavUtils_Write("uint8_t", this.Offs + 0xCF, Math.min(6, V));
		else return SavUtils_Read("uint8_t", this.Offs + 0xCF);
	};

	PocketID(Index, V) {
		if (V != undefined) {
			SavUtils_Write("uint16_t", this.Offs + 0xC3 + (Math.min(6, Index) * 2), V);

			let Count = 0;
			for (let Idx = 0; Idx < 6; Idx++) {
				if (this.PocketID(Idx) != 0x0) Count++;
			}

			this.PocketCount(Count);

		} else {
			return SavUtils_Read("uint16_t", this.Offs + 0xC3 + (Math.min(6, Index) * 2));
		}
	};


	/*
		Fix the Checksum of the current Slot, if invalid.

		Returns false if Slot > 4 or already valid, true if got fixed.
	*/
	FixChecksum() {
		if (this.Slot > 4) return false;

		let Fixed = false;

		/* First: Fix the main part. */
		let CurCHKS = SavUtils_Read("uint16_t", this.Offs + 0x28);
		let Calced = Checksum_CalcNDSSlotMain(SavData, this.Slot);

		if (Calced != CurCHKS) {
			SavUtils_Write("uint16_t", this.Offs + 0x28, Calced);
			Fixed = true;
		}

		/* Second: Fix the shared part. */
		Calced = Checksum_CalcNDSSlotShared(SavData, this.Slot);
		CurCHKS = SavUtils_Read("uint16_t", this.Offs + 0x10);

		if (CurCHKS != Calced) {
			SavUtils_Write("uint16_t", this.Offs + 0x10, Calced);
			Fixed = true;
		}

		/* Third: Fix the header part. */
		Calced = Checksum_CalcNDSSlotHeader(SavData, this.Slot);
		CurCHKS = SavUtils_Read("uint16_t", this.Offs + 0xE);

		if (CurCHKS != Calced) {
			SavUtils_Write("uint16_t", this.Offs + 0xE, Calced);
			Fixed = true;
		}

		return Fixed;
	};
};