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
	Initializes the Game Boy Advance Social Moves Menu.
*/
export function InitGBASocialMoveEditor() {
	if (GBAActiveSlot != undefined) {
		/* Initialize all 15 Social Moves. */
		for (let Idx = 0; Idx < 15; Idx++) {
			let SMove = GBAActiveSlot.SocialMove(Idx);

			/* Level of the social move ( 1 - 3 ). */
			document.getElementById("gba-social-move-" + Idx.toString() + "-level").value = SMove.Level() + 1; // + 1, because 0 is actually 1.

			/* State / Flag of the Social Move (Unlocked, Locked, Blocked). */
			document.getElementById("gba-social-move-" + Idx.toString() + "-state").value = SMove.Flag();
		}
	}
};


/* Set Chit-Chat. */
document.getElementById("gba-social-move-0-level").onchange = () => GBAActiveSlot.SocialMove(0).Level(document.getElementById("gba-social-move-0-level").value - 1);
document.getElementById("gba-social-move-0-state").onchange = () => GBAActiveSlot.SocialMove(0).Flag(document.getElementById("gba-social-move-0-state").value);

/* Set Entertain. */
document.getElementById("gba-social-move-1-level").onchange = () => GBAActiveSlot.SocialMove(1).Level(document.getElementById("gba-social-move-1-level").value - 1);
document.getElementById("gba-social-move-1-state").onchange = () => GBAActiveSlot.SocialMove(1).Flag(document.getElementById("gba-social-move-1-state").value);

/* Set Hug. */
document.getElementById("gba-social-move-2-level").onchange = () => GBAActiveSlot.SocialMove(2).Level(document.getElementById("gba-social-move-2-level").value - 1);
document.getElementById("gba-social-move-2-state").onchange = () => GBAActiveSlot.SocialMove(2).Flag(document.getElementById("gba-social-move-2-state").value);

/* Set Brag. */
document.getElementById("gba-social-move-3-level").onchange = () => GBAActiveSlot.SocialMove(3).Level(document.getElementById("gba-social-move-3-level").value - 1);
document.getElementById("gba-social-move-3-state").onchange = () => GBAActiveSlot.SocialMove(3).Flag(document.getElementById("gba-social-move-3-state").value);

/* Set Appologize. */
document.getElementById("gba-social-move-4-level").onchange = () => GBAActiveSlot.SocialMove(4).Level(document.getElementById("gba-social-move-4-level").value - 1);
document.getElementById("gba-social-move-4-state").onchange = () => GBAActiveSlot.SocialMove(4).Flag(document.getElementById("gba-social-move-4-state").value);

/* Set Sweet Talk. */
document.getElementById("gba-social-move-5-level").onchange = () => GBAActiveSlot.SocialMove(5).Level(document.getElementById("gba-social-move-5-level").value - 1);
document.getElementById("gba-social-move-5-state").onchange = () => GBAActiveSlot.SocialMove(5).Flag(document.getElementById("gba-social-move-5-state").value);

/* Set Flirt. */
document.getElementById("gba-social-move-6-level").onchange = () => GBAActiveSlot.SocialMove(6).Level(document.getElementById("gba-social-move-6-level").value - 1);
document.getElementById("gba-social-move-6-state").onchange = () => GBAActiveSlot.SocialMove(6).Flag(document.getElementById("gba-social-move-6-state").value);

/* Set Blow Kiss. */
document.getElementById("gba-social-move-7-level").onchange = () => GBAActiveSlot.SocialMove(7).Level(document.getElementById("gba-social-move-7-level").value - 1);
document.getElementById("gba-social-move-7-state").onchange = () => GBAActiveSlot.SocialMove(7).Flag(document.getElementById("gba-social-move-7-state").value);

/* Set Kiss. */
document.getElementById("gba-social-move-8-level").onchange = () => GBAActiveSlot.SocialMove(8).Level(document.getElementById("gba-social-move-8-level").value - 1);
document.getElementById("gba-social-move-8-state").onchange = () => GBAActiveSlot.SocialMove(8).Flag(document.getElementById("gba-social-move-8-state").value);

/* Set Show Off Body. */
document.getElementById("gba-social-move-9-level").onchange = () => GBAActiveSlot.SocialMove(9).Level(document.getElementById("gba-social-move-9-level").value - 1);
document.getElementById("gba-social-move-9-state").onchange = () => GBAActiveSlot.SocialMove(9).Flag(document.getElementById("gba-social-move-9-state").value);

/* Set Annoy. */
document.getElementById("gba-social-move-10-level").onchange = () => GBAActiveSlot.SocialMove(10).Level(document.getElementById("gba-social-move-10-level").value - 1);
document.getElementById("gba-social-move-10-state").onchange = () => GBAActiveSlot.SocialMove(10).Flag(document.getElementById("gba-social-move-10-state").value);

/* Set Insult. */
document.getElementById("gba-social-move-11-level").onchange = () => GBAActiveSlot.SocialMove(11).Level(document.getElementById("gba-social-move-11-level").value - 1);
document.getElementById("gba-social-move-11-state").onchange = () => GBAActiveSlot.SocialMove(11).Flag(document.getElementById("gba-social-move-11-state").value);

/* Set Threaten. */
document.getElementById("gba-social-move-12-level").onchange = () => GBAActiveSlot.SocialMove(12).Level(document.getElementById("gba-social-move-12-level").value - 1);
document.getElementById("gba-social-move-12-state").onchange = () => GBAActiveSlot.SocialMove(12).Flag(document.getElementById("gba-social-move-12-state").value);

/* Set Rude Gesture. */
document.getElementById("gba-social-move-13-level").onchange = () => GBAActiveSlot.SocialMove(13).Level(document.getElementById("gba-social-move-13-level").value - 1);
document.getElementById("gba-social-move-13-state").onchange = () => GBAActiveSlot.SocialMove(13).Flag(document.getElementById("gba-social-move-13-state").value);

/* Set Karate Moves. */
document.getElementById("gba-social-move-14-level").onchange = () => GBAActiveSlot.SocialMove(14).Level(document.getElementById("gba-social-move-14-level").value - 1);
document.getElementById("gba-social-move-14-state").onchange = () => GBAActiveSlot.SocialMove(14).Flag(document.getElementById("gba-social-move-14-state").value);