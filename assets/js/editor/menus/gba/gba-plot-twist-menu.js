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

import { GBAActiveSlot } from "./gba-slot-menu.js";


/*
	Initializes the Game Boy Advance Plot Twist Menu.
*/
export function InitGBAPlotTwistMenu() {
	if (GBAActiveSlot != undefined) {
		/* Initialize all 6 Plot Twists. */
		document.getElementById("gba-plot-twist-0-unlocked").checked = GBAActiveSlot.MysteryPlot();
		document.getElementById("gba-plot-twist-1-unlocked").checked = GBAActiveSlot.FriendlyPlot();
		document.getElementById("gba-plot-twist-2-unlocked").checked = GBAActiveSlot.RomanticPlot();
		document.getElementById("gba-plot-twist-3-unlocked").checked = GBAActiveSlot.IntimidatingPlot();
		document.getElementById("gba-plot-twist-4-unlocked").checked = GBAActiveSlot.TheChopperPlot();
		document.getElementById("gba-plot-twist-5-unlocked").checked = GBAActiveSlot.WeirdnessPlot();
	}
};


/* Set the Mystery Plot. */
document.getElementById("gba-plot-twist-0-unlocked").onchange = () => GBAActiveSlot.MysteryPlot(document.getElementById("gba-plot-twist-0-unlocked").checked);

/* Set the Friendly Plot. */
document.getElementById("gba-plot-twist-1-unlocked").onchange = () => GBAActiveSlot.FriendlyPlot(document.getElementById("gba-plot-twist-1-unlocked").checked);

/* Set the Romantic Plot. */
document.getElementById("gba-plot-twist-2-unlocked").onchange = () => GBAActiveSlot.RomanticPlot(document.getElementById("gba-plot-twist-2-unlocked").checked);

/* Set the Intimidating Plot. */
document.getElementById("gba-plot-twist-3-unlocked").onchange = () => GBAActiveSlot.IntimidatingPlot(document.getElementById("gba-plot-twist-3-unlocked").checked);

/* Set the "The Chopper" Plot. */
document.getElementById("gba-plot-twist-4-unlocked").onchange = () => GBAActiveSlot.TheChopperPlot(document.getElementById("gba-plot-twist-4-unlocked").checked);

/* Set the Weirdness Plot. */
document.getElementById("gba-plot-twist-5-unlocked").onchange = () => GBAActiveSlot.WeirdnessPlot(document.getElementById("gba-plot-twist-5-unlocked").checked);