/*
*   This file is part of Sim2Editor
*   Copyright (C) 2021 SuperSaiyajinStackZ
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

import { SimUtils_SimoleonFormat } from "../../../Sim2Editor-Core/shared/simutils.js"
import { SAV } from "../../../Sim2Editor-Core/shared/savutils.js";
import { ReinitCurrentMenu, SwitchMenu } from "../../main.js";

let InitialLoad = true;
export let NDSActiveSlot = undefined, NDSCurrentSlot = "";


/*
	Initializes the Nintendo DS Save Slot Menu.

	This includes filling out the proper slot informations on the Slot cards and enable Loading.
*/
export function InitializeNDSSlotEditor() {
	/* Initialize all existing Slots. */
	for (let _Slot = 0; _Slot < 3; _Slot++) {
		if (SAV.SlotExist(_Slot)) { // Ensure slot exist.
			let CurSlot = SAV.Slot(_Slot);

			document.getElementById("nds-slot" + (1 + _Slot).toString() + "-name").innerText = CurSlot.Name();
			document.getElementById("nds-slot" + (1 + _Slot).toString() + "-simoleons").innerText = SimUtils_SimoleonFormat(CurSlot.Simoleons());

			document.getElementById("nds-slot" + (1 + _Slot).toString() + "-load").disabled = false; // Set that Slot can be loaded.

		} else {
			document.getElementById("nds-slot" + (1 + _Slot).toString() + "-load").disabled = true; // Disabled!
		}
	}
};


/*
	Initialize a Nintendo DS Save Slot.

	_Slot: The Slot to initialize ( 0 - 2 ).
*/
function InitSlot(_Slot) {
	/* Remove selected border of the old slot. */
	if (!InitialLoad) document.getElementById(NDSCurrentSlot).classList.remove("selected-slot");

	/* Initialize the active Slot and display it as the new state. */
	NDSActiveSlot = SAV.Slot(_Slot);
	NDSCurrentSlot = "nds-slot" + (1 + _Slot).toString();
	document.getElementById(NDSCurrentSlot).classList.add("selected-slot");
	document.getElementById("nds-slot-load-text").innerText = "Loaded Slot: " + (1 + _Slot).toString();

	/* Initial Load --> Show the Editor Tabs + actual Menus. */
	if (InitialLoad) {
		document.getElementById("sub-tab").classList.remove("hide"); // Show the main editor Tab.
		document.getElementById("nds-tabs").classList.remove("hide"); // Show the NDS Editor Tabs.

		document.getElementById("menus").classList.remove("hide"); // Show the main Menus.
		document.getElementById("nds-menus").classList.remove("hide"); // Show the actual NDS Menus.

		SwitchMenu("nds-general");
		InitialLoad = false;

	} else {
		/* Re-Init the current Menu. */
		ReinitCurrentMenu();
	}
};


/* Handle Slot Loading. */
document.getElementById("nds-slot1-load").onclick = () => InitSlot(0);
document.getElementById("nds-slot2-load").onclick = () => InitSlot(1);
document.getElementById("nds-slot3-load").onclick = () => InitSlot(2);