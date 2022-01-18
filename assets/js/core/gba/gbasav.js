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


import { GBAIdent, SavData, SavUtils_Read, SavUtils_Write } from "../shared/savutils.js";
import { S2Editor_GBASlot } from "./gbaslot.js";
import { S2Editor_GBASettings } from "./gbasettings.js";


export class S2Editor_GBASav {
	constructor() {
		this.ChangesMade = false;
		this.ValidationCheck();
	};

	/* Some Save Validation checks. */
	ValidationCheck() {
		if (!SavData) return;

		/* Now do the Validation check through the Save Header with the GBAIdents. */
		let Res = true;
		for (let Idx = 0; Idx < 8; Idx++) {
			if (SavUtils_Read("uint8_t", Idx) != GBAIdent[Idx]) {
				Res = false;
				break;
			}
		}

		/* Language Checks as well, because why not. */
		if (SavUtils_Read("uint8_t", 0xA) > 5) { // Language Index is 6 or larger, which is "blank" and can break the game.
			SavUtils_Write("uint8_t", 0xA, 0); // English.
			this.ChangesMade = true;
		}

		this.SavValid = Res;
	};

	/*
		Return, wheter a Slot is valid / exist.

		Slot: The Slot to check.
	*/
	SlotExist(Slot) {
		if (Slot < 1 || Slot > 4 || !this.GetValid()) return false;

		return SavUtils_Read("uint8_t", (Slot * 0x1000) + 0xD) != 0x0;
	};

	/*
		Return a GBASlot class.

		Slot: The GBASav Slot ( 1 - 4 ).
	*/
	Slot(Slot) {
		if (!this.SlotExist(Slot)) return undefined;

		return new S2Editor_GBASlot(Slot);
	};

	/* Get a Settings class. */
	Settings() { return new S2Editor_GBASettings(); };

	/*
		Finish call before writting to file.

		Fix the Checksum of all existing Slots and the Settings (TODO), if invalid.
	*/
	Finish() {
		if (!this.GetValid()) return;

		for (let Slot = 1; Slot < 5; Slot++) {
			if (this.SlotExist(Slot)) this.Slot(Slot).FixChecksum();
		}

		/* Do the same with the Settings. */
		this.Settings().UpdateChecksum();
	};

	/* Return if the Sav is valid. */
	GetValid() { return this.SavValid; };

	/* Get and Set if changes made. */
	GetChangesMade() { return this.ChangesMade; };
	SetChangesMade(V) { this.ChangesMade = V; };
};