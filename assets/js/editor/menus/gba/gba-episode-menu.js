/*
*   This file is part of Sim2Editor
*   Copyright (C) 2021 Sim2Team
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
	Initializes the Game Boy Advance Episode Menu.
*/
export function InitGBAEpisodeEditor() {
	if (GBAActiveSlot != undefined) {
		/* Initialize all 11 Episodes. */
		for (let Idx = 0; Idx < 11; Idx++) {
			let EP = GBAActiveSlot.Episode(Idx);

			/* Initialize the 4 Rating categories. */
			for (let Idx2 = 0; Idx2 < 4; Idx2++) {
				document.getElementById("gba-episode-" + Idx.toString() + "-rating-" + Idx2.toString()).value = EP.Rating(Idx2);
			}

			/* Episode Unlocked state. */
			document.getElementById("gba-episode-" + Idx.toString() + "-unlocked").checked = EP.State();
		}
	}
};


/* Set Buried by the Mob. */
document.getElementById("gba-episode-0-rating-0").onchange = () => GBAActiveSlot.Episode(0).Rating(0, document.getElementById("gba-episode-0-rating-0").value);
document.getElementById("gba-episode-0-rating-1").onchange = () => GBAActiveSlot.Episode(0).Rating(1, document.getElementById("gba-episode-0-rating-1").value);
document.getElementById("gba-episode-0-rating-2").onchange = () => GBAActiveSlot.Episode(0).Rating(2, document.getElementById("gba-episode-0-rating-2").value);
document.getElementById("gba-episode-0-rating-3").onchange = () => GBAActiveSlot.Episode(0).Rating(3, document.getElementById("gba-episode-0-rating-3").value);
document.getElementById("gba-episode-0-unlocked").onchange = () => GBAActiveSlot.Episode(0).State(document.getElementById("gba-episode-0-unlocked").checked);

/* Set What Digs Beneath. */
document.getElementById("gba-episode-1-rating-0").onchange = () => GBAActiveSlot.Episode(1).Rating(0, document.getElementById("gba-episode-1-rating-0").value);
document.getElementById("gba-episode-1-rating-1").onchange = () => GBAActiveSlot.Episode(1).Rating(1, document.getElementById("gba-episode-1-rating-1").value);
document.getElementById("gba-episode-1-rating-2").onchange = () => GBAActiveSlot.Episode(1).Rating(2, document.getElementById("gba-episode-1-rating-2").value);
document.getElementById("gba-episode-1-rating-3").onchange = () => GBAActiveSlot.Episode(1).Rating(3, document.getElementById("gba-episode-1-rating-3").value);
document.getElementById("gba-episode-1-unlocked").onchange = () => GBAActiveSlot.Episode(1).State(document.getElementById("gba-episode-1-unlocked").checked);

/* Set Aliens Arrived. */
document.getElementById("gba-episode-2-rating-0").onchange = () => GBAActiveSlot.Episode(2).Rating(0, document.getElementById("gba-episode-2-rating-0").value);
document.getElementById("gba-episode-2-rating-1").onchange = () => GBAActiveSlot.Episode(2).Rating(1, document.getElementById("gba-episode-2-rating-1").value);
document.getElementById("gba-episode-2-rating-2").onchange = () => GBAActiveSlot.Episode(2).Rating(2, document.getElementById("gba-episode-2-rating-2").value);
document.getElementById("gba-episode-2-rating-3").onchange = () => GBAActiveSlot.Episode(2).Rating(3, document.getElementById("gba-episode-2-rating-3").value);
document.getElementById("gba-episode-2-unlocked").onchange = () => GBAActiveSlot.Episode(2).State(document.getElementById("gba-episode-2-unlocked").checked);

/* Set Blackout!. */
document.getElementById("gba-episode-3-rating-0").onchange = () => GBAActiveSlot.Episode(3).Rating(0, document.getElementById("gba-episode-3-rating-0").value);
document.getElementById("gba-episode-3-rating-1").onchange = () => GBAActiveSlot.Episode(3).Rating(1, document.getElementById("gba-episode-3-rating-1").value);
document.getElementById("gba-episode-3-rating-2").onchange = () => GBAActiveSlot.Episode(3).Rating(2, document.getElementById("gba-episode-3-rating-2").value);
document.getElementById("gba-episode-3-rating-3").onchange = () => GBAActiveSlot.Episode(3).Rating(3, document.getElementById("gba-episode-3-rating-3").value);
document.getElementById("gba-episode-3-unlocked").onchange = () => GBAActiveSlot.Episode(3).State(document.getElementById("gba-episode-3-unlocked").checked);

/* Set A Brand New Scent. */
document.getElementById("gba-episode-4-rating-0").onchange = () => GBAActiveSlot.Episode(4).Rating(0, document.getElementById("gba-episode-4-rating-0").value);
document.getElementById("gba-episode-4-rating-1").onchange = () => GBAActiveSlot.Episode(4).Rating(1, document.getElementById("gba-episode-4-rating-1").value);
document.getElementById("gba-episode-4-rating-2").onchange = () => GBAActiveSlot.Episode(4).Rating(2, document.getElementById("gba-episode-4-rating-2").value);
document.getElementById("gba-episode-4-rating-3").onchange = () => GBAActiveSlot.Episode(4).Rating(3, document.getElementById("gba-episode-4-rating-3").value);
document.getElementById("gba-episode-4-unlocked").onchange = () => GBAActiveSlot.Episode(4).State(document.getElementById("gba-episode-4-unlocked").checked);

/* Set The New Cola. */
document.getElementById("gba-episode-5-rating-0").onchange = () => GBAActiveSlot.Episode(5).Rating(0, document.getElementById("gba-episode-5-rating-0").value);
document.getElementById("gba-episode-5-rating-1").onchange = () => GBAActiveSlot.Episode(5).Rating(1, document.getElementById("gba-episode-5-rating-1").value);
document.getElementById("gba-episode-5-rating-2").onchange = () => GBAActiveSlot.Episode(5).Rating(2, document.getElementById("gba-episode-5-rating-2").value);
document.getElementById("gba-episode-5-rating-3").onchange = () => GBAActiveSlot.Episode(5).Rating(3, document.getElementById("gba-episode-5-rating-3").value);
document.getElementById("gba-episode-5-unlocked").onchange = () => GBAActiveSlot.Episode(5).State(document.getElementById("gba-episode-5-unlocked").checked);

/* Set There Was This Mummy. */
document.getElementById("gba-episode-6-rating-0").onchange = () => GBAActiveSlot.Episode(6).Rating(0, document.getElementById("gba-episode-6-rating-0").value);
document.getElementById("gba-episode-6-rating-1").onchange = () => GBAActiveSlot.Episode(6).Rating(1, document.getElementById("gba-episode-6-rating-1").value);
document.getElementById("gba-episode-6-rating-2").onchange = () => GBAActiveSlot.Episode(6).Rating(2, document.getElementById("gba-episode-6-rating-2").value);
document.getElementById("gba-episode-6-rating-3").onchange = () => GBAActiveSlot.Episode(6).Rating(3, document.getElementById("gba-episode-6-rating-3").value);
document.getElementById("gba-episode-6-unlocked").onchange = () => GBAActiveSlot.Episode(6).State(document.getElementById("gba-episode-6-unlocked").checked);

/* Set Triassic Trouble. */
document.getElementById("gba-episode-7-rating-0").onchange = () => GBAActiveSlot.Episode(7).Rating(0, document.getElementById("gba-episode-7-rating-0").value);
document.getElementById("gba-episode-7-rating-1").onchange = () => GBAActiveSlot.Episode(7).Rating(1, document.getElementById("gba-episode-7-rating-1").value);
document.getElementById("gba-episode-7-rating-2").onchange = () => GBAActiveSlot.Episode(7).Rating(2, document.getElementById("gba-episode-7-rating-2").value);
document.getElementById("gba-episode-7-rating-3").onchange = () => GBAActiveSlot.Episode(7).Rating(3, document.getElementById("gba-episode-7-rating-3").value);
document.getElementById("gba-episode-7-unlocked").onchange = () => GBAActiveSlot.Episode(7).State(document.getElementById("gba-episode-7-unlocked").checked);

/* Set The Doomed Earth. */
document.getElementById("gba-episode-8-rating-0").onchange = () => GBAActiveSlot.Episode(8).Rating(0, document.getElementById("gba-episode-8-rating-0").value);
document.getElementById("gba-episode-8-rating-1").onchange = () => GBAActiveSlot.Episode(8).Rating(1, document.getElementById("gba-episode-8-rating-1").value);
document.getElementById("gba-episode-8-rating-2").onchange = () => GBAActiveSlot.Episode(8).Rating(2, document.getElementById("gba-episode-8-rating-2").value);
document.getElementById("gba-episode-8-rating-3").onchange = () => GBAActiveSlot.Episode(8).Rating(3, document.getElementById("gba-episode-8-rating-3").value);
document.getElementById("gba-episode-8-unlocked").onchange = () => GBAActiveSlot.Episode(8).State(document.getElementById("gba-episode-8-unlocked").checked);

/* Set It All Came to an End. */
document.getElementById("gba-episode-9-rating-0").onchange = () => GBAActiveSlot.Episode(9).Rating(0, document.getElementById("gba-episode-9-rating-0").value);
document.getElementById("gba-episode-9-rating-1").onchange = () => GBAActiveSlot.Episode(9).Rating(1, document.getElementById("gba-episode-9-rating-1").value);
document.getElementById("gba-episode-9-rating-2").onchange = () => GBAActiveSlot.Episode(9).Rating(2, document.getElementById("gba-episode-9-rating-2").value);
document.getElementById("gba-episode-9-rating-3").onchange = () => GBAActiveSlot.Episode(9).Rating(3, document.getElementById("gba-episode-9-rating-3").value);
document.getElementById("gba-episode-9-unlocked").onchange = () => GBAActiveSlot.Episode(9).State(document.getElementById("gba-episode-9-unlocked").checked);

/* Set A Very Special Reunion. */
document.getElementById("gba-episode-10-rating-0").onchange = () => GBAActiveSlot.Episode(10).Rating(0, document.getElementById("gba-episode-10-rating-0").value);
document.getElementById("gba-episode-10-rating-1").onchange = () => GBAActiveSlot.Episode(10).Rating(1, document.getElementById("gba-episode-10-rating-1").value);
document.getElementById("gba-episode-10-rating-2").onchange = () => GBAActiveSlot.Episode(10).Rating(2, document.getElementById("gba-episode-10-rating-2").value);
document.getElementById("gba-episode-10-rating-3").onchange = () => GBAActiveSlot.Episode(10).Rating(3, document.getElementById("gba-episode-10-rating-3").value);
document.getElementById("gba-episode-10-unlocked").onchange = () => GBAActiveSlot.Episode(10).State(document.getElementById("gba-episode-10-unlocked").checked);