/*
*   This file is part of Sim2Editor
*   Copyright (C) 2021-2022 Sim2Team
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

import { SimUtils_RatingFormat, SimUtils_SimoleonFormat, SimUtils_TimeString } from "../../../core/shared/simutils.js"
import { Sav } from "../../../core/shared/savutils.js";
import { ReinitCurrentMenu, SwitchMenu } from "../../main.js";

let InitialLoad = true;
export let GBAActiveSlot = undefined, GBACurrentSlot = "";


/*
	Initializes the Game Boy Advance Save Slot Menu.

	This includes filling out the proper Slot informations on the Slot cards and enable Loading.
*/
export function InitializeGBASlotEditor() {
	/* Initialize all existing Slots. */
	for (let Slot = 1; Slot < 5; Slot++) {
		if (Sav.SlotExist(Slot)) { // Ensure Slot exist.
			let CurSlot = Sav.Slot(Slot);

			/* Init Name, Simoleons, Ratings and Time Slot info. */
			document.getElementById("gba-slot" + Slot.toString() + "-name").innerText = CurSlot.Name();
			document.getElementById("gba-slot" + Slot.toString() + "-simoleons").innerText = SimUtils_SimoleonFormat(CurSlot.Simoleons());
			document.getElementById("gba-slot" + Slot.toString() + "-ratings").innerText = SimUtils_RatingFormat(CurSlot.Ratings());
			document.getElementById("gba-slot" + Slot.toString() + "-time").innerText = SimUtils_TimeString(CurSlot.Time(), false);

			document.getElementById("gba-slot" + Slot.toString() + "-load").disabled = false; // Set that Slot can be loaded.

		} else {
			document.getElementById("gba-slot" + Slot.toString() + "-load").disabled = true; // Disabled!
		}
	}
};


/*
	Initialize a Game Boy Advance Save Slot.

	Slot: The Slot to initialize ( 1 - 4 ).
*/
function InitSlot(Slot) {
	/* Remove selected border of the old slot. */
	if (!InitialLoad) document.getElementById(GBACurrentSlot).classList.remove("selected-slot");

	/* Initialize the active Slot and display it as the new state. */
	GBAActiveSlot = Sav.Slot(Slot);
	GBACurrentSlot = "gba-slot" + Slot.toString();
	document.getElementById(GBACurrentSlot).classList.add("selected-slot");
	document.getElementById("gba-slot-load-text").innerText = "Loaded Slot: " + Slot.toString();

	/* Initial Load --> Show the Editor Tabs + actual Menus. */
	if (InitialLoad) {
		document.getElementById("sub-tab").classList.remove("hide"); // Show the main editor Tab.
		document.getElementById("gba-tabs").classList.remove("hide"); // Show the GBA Editor Tabs.

		document.getElementById("menus").classList.remove("hide"); // Show the main Menus.
		document.getElementById("gba-menus").classList.remove("hide"); // Show the actual GBA Menus.

		SwitchMenu("gba-general");
		InitialLoad = false;

	} else {
		/* Re-Init the current Menu. */
		ReinitCurrentMenu();
	}
};


/* Handle Slot Loading. */
document.getElementById("gba-slot1-load").onclick = () => InitSlot(1);
document.getElementById("gba-slot2-load").onclick = () => InitSlot(2);
document.getElementById("gba-slot3-load").onclick = () => InitSlot(3);
document.getElementById("gba-slot4-load").onclick = () => InitSlot(4);