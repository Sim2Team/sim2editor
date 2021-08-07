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

import { InitGBACastEditor } from "./menus/gba/gba-cast-menu.js";
import { InitGBAEpisodeEditor } from "./menus/gba/gba-episode-menu.js";
import { InitGBAGeneralEditor } from "./menus/gba/gba-general-menu.js";
import { InitGBAMinigameEditor } from "./menus/gba/gba-minigame-menu.js";
import { InitializeGBASlotEditor } from "./menus/gba/gba-slot-menu.js";
import { InitGBASocialMoveEditor } from "./menus/gba/gba-social-move-menu.js";
import { InitNDSGeneralEditor } from "./menus/nds/nds-general-menu.js";
import { InitializeNDSSlotEditor } from "./menus/nds/nds-slot-menu.js";

import { SAVType, SAVUtils_ChangesMade, SAVUtils_Finish, SAVUtils_LoadSAV } from "../Sim2Editor-Core/shared/savutils.js";

let CurrentMenu = ""; // Used so we can keep track of, which sub menu is currently open.


/* Show a warning about the save-editor with an alert at startup. */
window.onload = () => alert("This save-editor is a work in progress.\n\nALWAYS make a backup of your savefile before you try using it, because I cannot 100% guarantee that it always work without issues.\n\nI'm not responsible for any data loss you potential might have.\n\nYou are warned.");


/* Load and Select the SAVFile. */
document.getElementById("sav-selector").onchange = (Event) => SAVUtils_LoadSAV(Event.target.files[0], LoadSAV);


/*
	Save Loading callback.

	Initializes the Menus, if savefile is loaded properly.
*/
function LoadSAV() {
	switch(SAVType) {
		case 0: // GBA EUR | USA (International).
			InitializeMenu(true);
			break;

		case 1: // NDS EUR (International).
		case 2: // NDS USA (International).
		case 3: // NDS JPN (Japanese).
			InitializeMenu(false);
			break;

		default: // Invalid.
			break;
	}
};


/*
	Initial Menu initializer.

	IsGBA: If the Savefile is a Game Boy Advance one (true) or Nintendo DS one (false).

	Basically loads and initializes the Slot Loader for the specific Savetype.
*/
function InitializeMenu(IsGBA) {
	document.getElementById("sav-selector").disabled = true; // Disable the Save Selector, to not conflict.
	document.getElementById("sav-finish").disabled = false; // Enable the finish button.
	document.getElementById("slot-menu").classList.remove("hide"); // Show the Slot Loader Menu.

	if (IsGBA) {
		document.getElementById("gba-slot-menu").classList.remove("hide"); // Show GBA Slot Menu.
		InitializeGBASlotEditor(); // Initialize the GBA Slot Menu.

	} else {
		document.getElementById("nds-slot-menu").classList.remove("hide"); // Show NDS Slot Menu.
		InitializeNDSSlotEditor(); // Initialize the NDS Slot Menu.
	}
};


/*
	Switch the Menus.

	Also reinitialize them after the switch.
*/
export function SwitchMenu(ToSwitch) {
	if (CurrentMenu == ToSwitch) return; // Same menu, no switch.

	/* First: Hide old menu. */
	if (CurrentMenu != "") {
		document.getElementById(CurrentMenu).classList.remove("selected-bar-button");
		document.getElementById(CurrentMenu + "-menu").classList.add("hide");
	}

	/* Second: Show the new menu. */
	CurrentMenu = ToSwitch;
	document.getElementById(CurrentMenu).classList.add("selected-bar-button");
	document.getElementById(CurrentMenu + "-menu").classList.remove("hide");

	/* Third: Re-Init the menu. */
	ReinitCurrentMenu();
};


/*
	Re-Initializes the Current Menu or better said.. refreshes.

	That is being used, in case for tab switches OR switching a save slot.
*/
export function ReinitCurrentMenu() {
	switch(CurrentMenu) {
		case "gba-general":
			InitGBAGeneralEditor();
			break;

		case "gba-cast":
			InitGBACastEditor();
			break;

		case "gba-social-move":
			InitGBASocialMoveEditor();
			break;

		case "gba-episode":
			InitGBAEpisodeEditor();
			break;

		case "gba-minigame":
			InitGBAMinigameEditor();
			break;


		case "nds-general":
			InitNDSGeneralEditor();
			break;
	}
};


/* Handle all sub menus. */
document.getElementById("gba-general").onclick = () => SwitchMenu("gba-general");
document.getElementById("gba-cast").onclick = () => SwitchMenu("gba-cast");
document.getElementById("gba-social-move").onclick = () => SwitchMenu("gba-social-move");
document.getElementById("gba-episode").onclick = () => SwitchMenu("gba-episode");
document.getElementById("gba-minigame").onclick = () => SwitchMenu("gba-minigame");

document.getElementById("nds-general").onclick = () => SwitchMenu("nds-general");


/* Finish of save editing. */
document.getElementById("sav-finish").onclick = function() {
	SAVUtils_Finish(); // Create download for the new savefile.

	/* Hide all menus. */
	document.getElementById("sav-handler").classList.add("hide");
	document.getElementById("slot-menu").classList.add("hide");
	document.getElementById("sub-tab").classList.add("hide");
	document.getElementById("menus").classList.add("hide");

	/* Display "feedback" menu. */
	document.getElementById("feedback-menu").classList.remove("hide");
};


/* Handling of the navigation bar with a warning prompt, if you made any changes to the savefile. */
function HandleMainNav(URL) {
	if (!SAVUtils_ChangesMade()) window.location.href = URL;
	else {
		/* If a valid save is already loaded - warn the user. */
		if (window.confirm("You are about to leave the Save Editor.\n\nAre you sure you want to do that? Any changes will be lost! You're warned.")) {
			window.location.href = URL;
		}
	}
};


/* Top Navigation bars. */
document.getElementById("navbar-home").onclick = () => HandleMainNav("/");
document.getElementById("navbar-about").onclick = () => HandleMainNav("/about");
document.getElementById("navbar-faq").onclick = () => HandleMainNav("/faq");
document.getElementById("navbar-features").onclick = () => HandleMainNav("/features");
document.getElementById("navbar-save-editor").onclick = () => HandleMainNav("/save-editor");

/* Leave to HOME page button after editing finish. */
document.getElementById("leave-page").onclick = () => window.location.href = "/";