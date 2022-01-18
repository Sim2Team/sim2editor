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

import { GBAActiveSlot } from "./gba-slot-menu.js";


/*
	Initializes the Game Boy Advance Minigame Menu.
*/
export function InitGBAMinigameEditor() {
	if (GBAActiveSlot != undefined) {
		/* Initialize all 7 Minigames. */
		for (let Idx = 0; Idx < 7; Idx++) {
			let Game = GBAActiveSlot.Minigame(Idx);

			/* Minigame level. */
			document.getElementById("gba-minigame-" + Idx.toString() + "-level").value = Game.Level();

			/* Minigame today played state. */
			document.getElementById("gba-minigame-" + Idx.toString() + "-played").checked = Game.Played();
		}
	}
};


/* Set Bigfoot Love Chickens. */
document.getElementById("gba-minigame-0-level").onchange = () => GBAActiveSlot.Minigame(0).Level(document.getElementById("gba-minigame-0-level").value, false);
document.getElementById("gba-minigame-0-played").onchange = () => GBAActiveSlot.Minigame(0).Played(document.getElementById("gba-minigame-0-played").checked);

/* Set Car Commercial. */
document.getElementById("gba-minigame-1-level").onchange = () => GBAActiveSlot.Minigame(1).Level(document.getElementById("gba-minigame-1-level").value, false);
document.getElementById("gba-minigame-1-played").onchange = () => GBAActiveSlot.Minigame(1).Played(document.getElementById("gba-minigame-1-played").checked);

/* Set Keelhaulin' Cards. */
document.getElementById("gba-minigame-2-level").onchange = () => GBAActiveSlot.Minigame(2).Level(document.getElementById("gba-minigame-2-level").value, false);
document.getElementById("gba-minigame-2-played").onchange = () => GBAActiveSlot.Minigame(2).Played(document.getElementById("gba-minigame-2-played").checked);

/* Set Cattle Cleanup. */
document.getElementById("gba-minigame-3-level").onchange = () => GBAActiveSlot.Minigame(3).Level(document.getElementById("gba-minigame-3-level").value, false);
document.getElementById("gba-minigame-3-played").onchange = () => GBAActiveSlot.Minigame(3).Played(document.getElementById("gba-minigame-3-played").checked);

/* Set King Chug Chug. */
document.getElementById("gba-minigame-4-level").onchange = () => GBAActiveSlot.Minigame(4).Level(document.getElementById("gba-minigame-4-level").value, false);
document.getElementById("gba-minigame-4-played").onchange = () => GBAActiveSlot.Minigame(4).Played(document.getElementById("gba-minigame-4-played").checked);

/* Set Canyon Jumping. */
document.getElementById("gba-minigame-5-level").onchange = () => GBAActiveSlot.Minigame(5).Level(document.getElementById("gba-minigame-5-level").value, false);
document.getElementById("gba-minigame-5-played").onchange = () => GBAActiveSlot.Minigame(5).Played(document.getElementById("gba-minigame-5-played").checked);

/* Set Chop Shop. */
document.getElementById("gba-minigame-6-level").onchange = () => GBAActiveSlot.Minigame(6).Level(document.getElementById("gba-minigame-6-level").value, false);
document.getElementById("gba-minigame-6-played").onchange = () => GBAActiveSlot.Minigame(6).Played(document.getElementById("gba-minigame-6-played").checked);