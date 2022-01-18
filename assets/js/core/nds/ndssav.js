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


import { SavUtils_Read, NDSIdent, SavData } from "../shared/savutils.js";
import { S2Editor_NDSSlot } from "./ndsslot.js";
import { S2Editor_NDSPainting } from "./ndspainting.js";


export class S2Editor_NDSSav {
	/*
		Region being passed is:
		-1: Unknown / Invalid.
		0: USA International.
		1: Europe International.
		2: Japanese.
	*/
	constructor(Region) {
		this.ChangesMade = false;
		this.Slots = new Int8Array(0x3);
		this.Region = Region;
		this.ValidationCheck();
	};

	/* Some Save Validation checks. */
	ValidationCheck() {
		if (!SavData) return;

		let Count = 0;
		for (let Slot = 0; Slot < 5; Slot++) { // Check for all 5 possible Slots.
			Count = 0; // Reset Count here.

			for (let ID = 0; ID < 8; ID++) {
				if (SavUtils_Read("uint8_t", (Slot * 0x1000) + ID) == NDSIdent[ID] + (ID == 0x4 ? this.Region : 0x0)) Count++;
			}

			if (Count == 8) {
				this.SavValid = true;
				break;
			}
		}

		if (this.SavValid) {
			for (let Idx = 0; Idx < 3; Idx++) this.Slots[Idx] = this.FetchSlot(Idx); // Fetch Slot Locations.
		}
	};

	/*
		This one is called at NDSSav class constructor 3 times, to get the proper SavSlot offset.

		This function has been ported of the LSSD Tool, SuperSaiyajinStackZ created.
	*/
	FetchSlot(SavSlot) {
		if (!this.SavValid || this.Region == -1) return -1;

		let LastSavedSlot = -1, IDCount = 0;
		let SavCount = new Uint32Array(0x5);
		let SavSlotExist = new Boolean(0x5);

		/* Looping through all possible Locations. */
		for (let Slot = 0; Slot < 5; Slot++) {
			IDCount = 0; // First reset here to 0.

			/* Check for Identifier. */
			for (let ID = 0; ID < 8; ID++) {
				if (SavUtils_Read("uint8_t", (Slot * 0x1000) + ID) == NDSIdent[ID] + (ID == 0x4 ? this.Region : 0x0)) IDCount++;
			}

			/* If 8, then it properly passed the slot existence check. */
			if (IDCount == 8) {
				/* Check, if current slot is also the actual SavSlot. It seems 0xC and 0xD added is the Slot, however 0xD seems never be touched from the game and hence like all the time 0x0? */
				if ((SavUtils_Read("uint8_t", (Slot * 0x1000) + 0xC) + SavUtils_Read("uint8_t", (Slot * 0x1000) + 0xD)) == SavSlot) {
					/* Now get the SavCount. */
					SavCount[Slot] = SavUtils_Read("uint32_t", (Slot * 0x1000) + 0x8);
					SavSlotExist[Slot] = true;
				}
			}
		}

		/* Here we check and return the proper last Saved Slot. */
		let HighestCount = 0;

		for (let Slot = 0; Slot < 5; Slot++) {
			if (SavSlotExist[Slot]) { // Ensure the Slot existed before.
				if (SavCount[Slot] > HighestCount) { // Ensure count is higher.
					HighestCount = SavCount[Slot];
					LastSavedSlot = Slot;
				}
			}
		}

		return LastSavedSlot;
	};

	/*
		Return a NDSSlot class.

		const uint8_t Slot: The NDSSav Slot ( 0 - 2 ).
	*/
	Slot(Slot) {
		if (!this.SlotExist(Slot)) return undefined;

		return new S2Editor_NDSSlot(this.Slots[Slot], this.Region);
	};

	/*
		Return, wheter a Slot is valid / exist.

		const uint8_t Slot: The Slot to check.
	*/
	SlotExist(Slot) {
		if (Slot > 2 || !this.GetValid()) return false;

		return this.Slots[Slot] != -1;
	};

	/* Returns a painting class. */
	Painting(Idx) { return new S2Editor_NDSPainting(0x5000 + (Math.min(19, Idx) * 0x400)); };

	/* Return if the Sav is valid. */
	GetValid() { return this.SavValid; };

	/* Get and Set if changes made. */
	GetChangesMade() { return this.ChangesMade; };
	SetChangesMade(V) { this.ChangesMade = V; };

	/*
		Finish call before writting to file.

		Fix the Checksum of all existing Slots, if invalid.
	*/
	Finish() {
		if (!this.GetValid()) return;

		for (let Slot = 0; Slot < 3; Slot++) {
			if (this.SlotExist(Slot)) this.Slot(Slot).FixChecksum();
		}
	};
};