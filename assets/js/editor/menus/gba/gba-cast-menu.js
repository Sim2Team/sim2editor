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
	Initializes the Game Boy Advance Cast Member Menu.
*/
export function InitGBACastEditor() {
	if (GBAActiveSlot != undefined) {
		/* Initialize all 26 Cast Members. */
		for (let Idx = 0; Idx < 26; Idx++) {
			let CST = GBAActiveSlot.Cast(Idx);

			/* Interaction Levels. */
			document.getElementById("gba-cast-" + Idx.toString() + "-friendly").value = CST.Friendly();
			document.getElementById("gba-cast-" + Idx.toString() + "-romance").value = CST.Romance();
			document.getElementById("gba-cast-" + Idx.toString() + "-intimidate").value = CST.Intimidate();

			/* Feeling. */
			if (CST.Feeling() <= 3) document.getElementById("gba-cast-" + Idx.toString() + "-feeling").value = CST.Feeling();

			/* States. */
			document.getElementById("gba-cast-" + Idx.toString() + "-phone").checked = CST.RegisteredOnPhone();
			document.getElementById("gba-cast-" + Idx.toString() + "-secret").checked = CST.Secret();
		}
	}
};


/* Set Emperor Xizzle. */
document.getElementById("gba-cast-0-friendly").onchange = () => GBAActiveSlot.Cast(0).Friendly(document.getElementById("gba-cast-0-friendly").value);
document.getElementById("gba-cast-0-romance").onchange = () => GBAActiveSlot.Cast(0).Romance(document.getElementById("gba-cast-0-romance").value);
document.getElementById("gba-cast-0-intimidate").onchange = () => GBAActiveSlot.Cast(0).Intimidate(document.getElementById("gba-cast-0-intimidate").value);
document.getElementById("gba-cast-0-feeling").onchange = () => GBAActiveSlot.Cast(0).Feeling(document.getElementById("gba-cast-0-feeling").value);
document.getElementById("gba-cast-0-phone").onchange = () => GBAActiveSlot.Cast(0).Phone(document.getElementById("gba-cast-0-phone").checked);
document.getElementById("gba-cast-0-secret").onchange = () => GBAActiveSlot.Cast(0).Secret(document.getElementById("gba-cast-0-secret").checked);

/* Set Burple. */
document.getElementById("gba-cast-1-friendly").onchange = () => GBAActiveSlot.Cast(1).Friendly(document.getElementById("gba-cast-1-friendly").value);
document.getElementById("gba-cast-1-romance").onchange = () => GBAActiveSlot.Cast(1).Romance(document.getElementById("gba-cast-1-romance").value);
document.getElementById("gba-cast-1-intimidate").onchange = () => GBAActiveSlot.Cast(1).Intimidate(document.getElementById("gba-cast-1-intimidate").value);
document.getElementById("gba-cast-1-feeling").onchange = () => GBAActiveSlot.Cast(1).Feeling(document.getElementById("gba-cast-1-feeling").value);
document.getElementById("gba-cast-1-phone").onchange = () => GBAActiveSlot.Cast(1).Phone(document.getElementById("gba-cast-1-phone").checked);
document.getElementById("gba-cast-1-secret").onchange = () => GBAActiveSlot.Cast(1).Secret(document.getElementById("gba-cast-1-secret").checked);

/* Set Ara Fusilli. */
document.getElementById("gba-cast-2-friendly").onchange = () => GBAActiveSlot.Cast(2).Friendly(document.getElementById("gba-cast-2-friendly").value);
document.getElementById("gba-cast-2-romance").onchange = () => GBAActiveSlot.Cast(2).Romance(document.getElementById("gba-cast-2-romance").value);
document.getElementById("gba-cast-2-intimidate").onchange = () => GBAActiveSlot.Cast(2).Intimidate(document.getElementById("gba-cast-2-intimidate").value);
document.getElementById("gba-cast-2-feeling").onchange = () => GBAActiveSlot.Cast(2).Feeling(document.getElementById("gba-cast-2-feeling").value);
document.getElementById("gba-cast-2-phone").onchange = () => GBAActiveSlot.Cast(2).Phone(document.getElementById("gba-cast-2-phone").checked);
document.getElementById("gba-cast-2-secret").onchange = () => GBAActiveSlot.Cast(2).Secret(document.getElementById("gba-cast-2-secret").checked);

/* Set Auda Sherif. */
document.getElementById("gba-cast-3-friendly").onchange = () => GBAActiveSlot.Cast(3).Friendly(document.getElementById("gba-cast-3-friendly").value);
document.getElementById("gba-cast-3-romance").onchange = () => GBAActiveSlot.Cast(3).Romance(document.getElementById("gba-cast-3-romance").value);
document.getElementById("gba-cast-3-intimidate").onchange = () => GBAActiveSlot.Cast(3).Intimidate(document.getElementById("gba-cast-3-intimidate").value);
document.getElementById("gba-cast-3-feeling").onchange = () => GBAActiveSlot.Cast(3).Feeling(document.getElementById("gba-cast-3-feeling").value);
document.getElementById("gba-cast-3-phone").onchange = () => GBAActiveSlot.Cast(3).Phone(document.getElementById("gba-cast-3-phone").checked);
document.getElementById("gba-cast-3-secret").onchange = () => GBAActiveSlot.Cast(3).Secret(document.getElementById("gba-cast-3-secret").checked);

/* Set Ava Cadavra. */
document.getElementById("gba-cast-4-friendly").onchange = () => GBAActiveSlot.Cast(4).Friendly(document.getElementById("gba-cast-4-friendly").value);
document.getElementById("gba-cast-4-romance").onchange = () => GBAActiveSlot.Cast(4).Romance(document.getElementById("gba-cast-4-romance").value);
document.getElementById("gba-cast-4-intimidate").onchange = () => GBAActiveSlot.Cast(4).Intimidate(document.getElementById("gba-cast-4-intimidate").value);
document.getElementById("gba-cast-4-feeling").onchange = () => GBAActiveSlot.Cast(4).Feeling(document.getElementById("gba-cast-4-feeling").value);
document.getElementById("gba-cast-4-phone").onchange = () => GBAActiveSlot.Cast(4).Phone(document.getElementById("gba-cast-4-phone").checked);
document.getElementById("gba-cast-4-secret").onchange = () => GBAActiveSlot.Cast(4).Secret(document.getElementById("gba-cast-4-secret").checked);

/* Set Bigfoot. */
document.getElementById("gba-cast-5-friendly").onchange = () => GBAActiveSlot.Cast(5).Friendly(document.getElementById("gba-cast-5-friendly").value);
document.getElementById("gba-cast-5-romance").onchange = () => GBAActiveSlot.Cast(5).Romance(document.getElementById("gba-cast-5-romance").value);
document.getElementById("gba-cast-5-intimidate").onchange = () => GBAActiveSlot.Cast(5).Intimidate(document.getElementById("gba-cast-5-intimidate").value);
document.getElementById("gba-cast-5-feeling").onchange = () => GBAActiveSlot.Cast(5).Feeling(document.getElementById("gba-cast-5-feeling").value);
document.getElementById("gba-cast-5-phone").onchange = () => GBAActiveSlot.Cast(5).Phone(document.getElementById("gba-cast-5-phone").checked);
document.getElementById("gba-cast-5-secret").onchange = () => GBAActiveSlot.Cast(5).Secret(document.getElementById("gba-cast-5-secret").checked);

/* Set Frankie Fusilli. */
document.getElementById("gba-cast-6-friendly").onchange = () => GBAActiveSlot.Cast(6).Friendly(document.getElementById("gba-cast-6-friendly").value);
document.getElementById("gba-cast-6-romance").onchange = () => GBAActiveSlot.Cast(6).Romance(document.getElementById("gba-cast-6-romance").value);
document.getElementById("gba-cast-6-intimidate").onchange = () => GBAActiveSlot.Cast(6).Intimidate(document.getElementById("gba-cast-6-intimidate").value);
document.getElementById("gba-cast-6-feeling").onchange = () => GBAActiveSlot.Cast(6).Feeling(document.getElementById("gba-cast-6-feeling").value);
document.getElementById("gba-cast-6-phone").onchange = () => GBAActiveSlot.Cast(6).Phone(document.getElementById("gba-cast-6-phone").checked);
document.getElementById("gba-cast-6-secret").onchange = () => GBAActiveSlot.Cast(6).Secret(document.getElementById("gba-cast-6-secret").checked);

/* Set Dusty Hogg. */
document.getElementById("gba-cast-7-friendly").onchange = () => GBAActiveSlot.Cast(7).Friendly(document.getElementById("gba-cast-7-friendly").value);
document.getElementById("gba-cast-7-romance").onchange = () => GBAActiveSlot.Cast(7).Romance(document.getElementById("gba-cast-7-romance").value);
document.getElementById("gba-cast-7-intimidate").onchange = () => GBAActiveSlot.Cast(7).Intimidate(document.getElementById("gba-cast-7-intimidate").value);
document.getElementById("gba-cast-7-feeling").onchange = () => GBAActiveSlot.Cast(7).Feeling(document.getElementById("gba-cast-7-feeling").value);
document.getElementById("gba-cast-7-phone").onchange = () => GBAActiveSlot.Cast(7).Phone(document.getElementById("gba-cast-7-phone").checked);
document.getElementById("gba-cast-7-secret").onchange = () => GBAActiveSlot.Cast(7).Secret(document.getElementById("gba-cast-7-secret").checked);

/* Set Giuseppi Mezzoalto. */
document.getElementById("gba-cast-8-friendly").onchange = () => GBAActiveSlot.Cast(8).Friendly(document.getElementById("gba-cast-8-friendly").value);
document.getElementById("gba-cast-8-romance").onchange = () => GBAActiveSlot.Cast(8).Romance(document.getElementById("gba-cast-8-romance").value);
document.getElementById("gba-cast-8-intimidate").onchange = () => GBAActiveSlot.Cast(8).Intimidate(document.getElementById("gba-cast-8-intimidate").value);
document.getElementById("gba-cast-8-feeling").onchange = () => GBAActiveSlot.Cast(8).Feeling(document.getElementById("gba-cast-8-feeling").value);
document.getElementById("gba-cast-8-phone").onchange = () => GBAActiveSlot.Cast(8).Phone(document.getElementById("gba-cast-8-phone").checked);
document.getElementById("gba-cast-8-secret").onchange = () => GBAActiveSlot.Cast(8).Secret(document.getElementById("gba-cast-8-secret").checked);

/* Set Honest Jackson. */
document.getElementById("gba-cast-9-friendly").onchange = () => GBAActiveSlot.Cast(9).Friendly(document.getElementById("gba-cast-9-friendly").value);
document.getElementById("gba-cast-9-romance").onchange = () => GBAActiveSlot.Cast(9).Romance(document.getElementById("gba-cast-9-romance").value);
document.getElementById("gba-cast-9-intimidate").onchange = () => GBAActiveSlot.Cast(9).Intimidate(document.getElementById("gba-cast-9-intimidate").value);
document.getElementById("gba-cast-9-feeling").onchange = () => GBAActiveSlot.Cast(9).Feeling(document.getElementById("gba-cast-9-feeling").value);
document.getElementById("gba-cast-9-phone").onchange = () => GBAActiveSlot.Cast(9).Phone(document.getElementById("gba-cast-9-phone").checked);
document.getElementById("gba-cast-9-secret").onchange = () => GBAActiveSlot.Cast(9).Secret(document.getElementById("gba-cast-9-secret").checked);

/* Set Jebediah Jerky. */
document.getElementById("gba-cast-10-friendly").onchange = () => GBAActiveSlot.Cast(10).Friendly(document.getElementById("gba-cast-10-friendly").value);
document.getElementById("gba-cast-10-romance").onchange = () => GBAActiveSlot.Cast(10).Romance(document.getElementById("gba-cast-10-romance").value);
document.getElementById("gba-cast-10-intimidate").onchange = () => GBAActiveSlot.Cast(10).Intimidate(document.getElementById("gba-cast-10-intimidate").value);
document.getElementById("gba-cast-10-feeling").onchange = () => GBAActiveSlot.Cast(10).Feeling(document.getElementById("gba-cast-10-feeling").value);
document.getElementById("gba-cast-10-phone").onchange = () => GBAActiveSlot.Cast(10).Phone(document.getElementById("gba-cast-10-phone").checked);
document.getElementById("gba-cast-10-secret").onchange = () => GBAActiveSlot.Cast(10).Secret(document.getElementById("gba-cast-10-secret").checked);

/* Set Jimmy the Neck. */
document.getElementById("gba-cast-11-friendly").onchange = () => GBAActiveSlot.Cast(11).Friendly(document.getElementById("gba-cast-11-friendly").value);
document.getElementById("gba-cast-11-romance").onchange = () => GBAActiveSlot.Cast(11).Romance(document.getElementById("gba-cast-11-romance").value);
document.getElementById("gba-cast-11-intimidate").onchange = () => GBAActiveSlot.Cast(11).Intimidate(document.getElementById("gba-cast-11-intimidate").value);
document.getElementById("gba-cast-11-feeling").onchange = () => GBAActiveSlot.Cast(11).Feeling(document.getElementById("gba-cast-11-feeling").value);
document.getElementById("gba-cast-11-phone").onchange = () => GBAActiveSlot.Cast(11).Phone(document.getElementById("gba-cast-11-phone").checked);
document.getElementById("gba-cast-11-secret").onchange = () => GBAActiveSlot.Cast(11).Secret(document.getElementById("gba-cast-11-secret").checked);

/* Set Kayleigh Wintercrest. */
document.getElementById("gba-cast-12-friendly").onchange = () => GBAActiveSlot.Cast(12).Friendly(document.getElementById("gba-cast-12-friendly").value);
document.getElementById("gba-cast-12-romance").onchange = () => GBAActiveSlot.Cast(12).Romance(document.getElementById("gba-cast-12-romance").value);
document.getElementById("gba-cast-12-intimidate").onchange = () => GBAActiveSlot.Cast(12).Intimidate(document.getElementById("gba-cast-12-intimidate").value);
document.getElementById("gba-cast-12-feeling").onchange = () => GBAActiveSlot.Cast(12).Feeling(document.getElementById("gba-cast-12-feeling").value);
document.getElementById("gba-cast-12-phone").onchange = () => GBAActiveSlot.Cast(12).Phone(document.getElementById("gba-cast-12-phone").checked);
document.getElementById("gba-cast-12-secret").onchange = () => GBAActiveSlot.Cast(12).Secret(document.getElementById("gba-cast-12-secret").checked);

/* Set Luthor L. Bigbucks. */
document.getElementById("gba-cast-13-friendly").onchange = () => GBAActiveSlot.Cast(13).Friendly(document.getElementById("gba-cast-13-friendly").value);
document.getElementById("gba-cast-13-romance").onchange = () => GBAActiveSlot.Cast(13).Romance(document.getElementById("gba-cast-13-romance").value);
document.getElementById("gba-cast-13-intimidate").onchange = () => GBAActiveSlot.Cast(13).Intimidate(document.getElementById("gba-cast-13-intimidate").value);
document.getElementById("gba-cast-13-feeling").onchange = () => GBAActiveSlot.Cast(13).Feeling(document.getElementById("gba-cast-13-feeling").value);
document.getElementById("gba-cast-13-phone").onchange = () => GBAActiveSlot.Cast(13).Phone(document.getElementById("gba-cast-13-phone").checked);
document.getElementById("gba-cast-13-secret").onchange = () => GBAActiveSlot.Cast(13).Secret(document.getElementById("gba-cast-13-secret").checked);

/* Set Mamma Hogg. */
document.getElementById("gba-cast-14-friendly").onchange = () => GBAActiveSlot.Cast(14).Friendly(document.getElementById("gba-cast-14-friendly").value);
document.getElementById("gba-cast-14-romance").onchange = () => GBAActiveSlot.Cast(14).Romance(document.getElementById("gba-cast-14-romance").value);
document.getElementById("gba-cast-14-intimidate").onchange = () => GBAActiveSlot.Cast(14).Intimidate(document.getElementById("gba-cast-14-intimidate").value);
document.getElementById("gba-cast-14-feeling").onchange = () => GBAActiveSlot.Cast(14).Feeling(document.getElementById("gba-cast-14-feeling").value);
document.getElementById("gba-cast-14-phone").onchange = () => GBAActiveSlot.Cast(14).Phone(document.getElementById("gba-cast-14-phone").checked);
document.getElementById("gba-cast-14-secret").onchange = () => GBAActiveSlot.Cast(14).Secret(document.getElementById("gba-cast-14-secret").checked);

/* Set Misty Waters. */
document.getElementById("gba-cast-15-friendly").onchange = () => GBAActiveSlot.Cast(15).Friendly(document.getElementById("gba-cast-15-friendly").value);
document.getElementById("gba-cast-15-romance").onchange = () => GBAActiveSlot.Cast(15).Romance(document.getElementById("gba-cast-15-romance").value);
document.getElementById("gba-cast-15-intimidate").onchange = () => GBAActiveSlot.Cast(15).Intimidate(document.getElementById("gba-cast-15-intimidate").value);
document.getElementById("gba-cast-15-feeling").onchange = () => GBAActiveSlot.Cast(15).Feeling(document.getElementById("gba-cast-15-feeling").value);
document.getElementById("gba-cast-15-phone").onchange = () => GBAActiveSlot.Cast(15).Phone(document.getElementById("gba-cast-15-phone").checked);
document.getElementById("gba-cast-15-secret").onchange = () => GBAActiveSlot.Cast(15).Secret(document.getElementById("gba-cast-15-secret").checked);

/* Set Lord Mole. */
document.getElementById("gba-cast-16-friendly").onchange = () => GBAActiveSlot.Cast(16).Friendly(document.getElementById("gba-cast-16-friendly").value);
document.getElementById("gba-cast-16-romance").onchange = () => GBAActiveSlot.Cast(16).Romance(document.getElementById("gba-cast-16-romance").value);
document.getElementById("gba-cast-16-intimidate").onchange = () => GBAActiveSlot.Cast(16).Intimidate(document.getElementById("gba-cast-16-intimidate").value);
document.getElementById("gba-cast-16-feeling").onchange = () => GBAActiveSlot.Cast(16).Feeling(document.getElementById("gba-cast-16-feeling").value);
document.getElementById("gba-cast-16-phone").onchange = () => GBAActiveSlot.Cast(16).Phone(document.getElementById("gba-cast-16-phone").checked);
document.getElementById("gba-cast-16-secret").onchange = () => GBAActiveSlot.Cast(16).Secret(document.getElementById("gba-cast-16-secret").checked);

/* Set Mummy. */
document.getElementById("gba-cast-17-friendly").onchange = () => GBAActiveSlot.Cast(17).Friendly(document.getElementById("gba-cast-17-friendly").value);
document.getElementById("gba-cast-17-romance").onchange = () => GBAActiveSlot.Cast(17).Romance(document.getElementById("gba-cast-17-romance").value);
document.getElementById("gba-cast-17-intimidate").onchange = () => GBAActiveSlot.Cast(17).Intimidate(document.getElementById("gba-cast-17-intimidate").value);
document.getElementById("gba-cast-17-feeling").onchange = () => GBAActiveSlot.Cast(17).Feeling(document.getElementById("gba-cast-17-feeling").value);
document.getElementById("gba-cast-17-phone").onchange = () => GBAActiveSlot.Cast(17).Phone(document.getElementById("gba-cast-17-phone").checked);
document.getElementById("gba-cast-17-secret").onchange = () => GBAActiveSlot.Cast(17).Secret(document.getElementById("gba-cast-17-secret").checked);

/* Set Optimum Alfred. */
document.getElementById("gba-cast-18-friendly").onchange = () => GBAActiveSlot.Cast(18).Friendly(document.getElementById("gba-cast-18-friendly").value);
document.getElementById("gba-cast-18-romance").onchange = () => GBAActiveSlot.Cast(18).Romance(document.getElementById("gba-cast-18-romance").value);
document.getElementById("gba-cast-18-intimidate").onchange = () => GBAActiveSlot.Cast(18).Intimidate(document.getElementById("gba-cast-18-intimidate").value);
document.getElementById("gba-cast-18-feeling").onchange = () => GBAActiveSlot.Cast(18).Feeling(document.getElementById("gba-cast-18-feeling").value);
document.getElementById("gba-cast-18-phone").onchange = () => GBAActiveSlot.Cast(18).Phone(document.getElementById("gba-cast-18-phone").checked);
document.getElementById("gba-cast-18-secret").onchange = () => GBAActiveSlot.Cast(18).Secret(document.getElementById("gba-cast-18-secret").checked);

/* Set Penelope Redd. */
document.getElementById("gba-cast-19-friendly").onchange = () => GBAActiveSlot.Cast(19).Friendly(document.getElementById("gba-cast-19-friendly").value);
document.getElementById("gba-cast-19-romance").onchange = () => GBAActiveSlot.Cast(19).Romance(document.getElementById("gba-cast-19-romance").value);
document.getElementById("gba-cast-19-intimidate").onchange = () => GBAActiveSlot.Cast(19).Intimidate(document.getElementById("gba-cast-19-intimidate").value);
document.getElementById("gba-cast-19-feeling").onchange = () => GBAActiveSlot.Cast(19).Feeling(document.getElementById("gba-cast-19-feeling").value);
document.getElementById("gba-cast-19-phone").onchange = () => GBAActiveSlot.Cast(19).Phone(document.getElementById("gba-cast-19-phone").checked);
document.getElementById("gba-cast-19-secret").onchange = () => GBAActiveSlot.Cast(19).Secret(document.getElementById("gba-cast-19-secret").checked);

/* Set Pepper Pete. */
document.getElementById("gba-cast-20-friendly").onchange = () => GBAActiveSlot.Cast(20).Friendly(document.getElementById("gba-cast-20-friendly").value);
document.getElementById("gba-cast-20-romance").onchange = () => GBAActiveSlot.Cast(20).Romance(document.getElementById("gba-cast-20-romance").value);
document.getElementById("gba-cast-20-intimidate").onchange = () => GBAActiveSlot.Cast(20).Intimidate(document.getElementById("gba-cast-20-intimidate").value);
document.getElementById("gba-cast-20-feeling").onchange = () => GBAActiveSlot.Cast(20).Feeling(document.getElementById("gba-cast-20-feeling").value);
document.getElementById("gba-cast-20-phone").onchange = () => GBAActiveSlot.Cast(20).Phone(document.getElementById("gba-cast-20-phone").checked);
document.getElementById("gba-cast-20-secret").onchange = () => GBAActiveSlot.Cast(20).Secret(document.getElementById("gba-cast-20-secret").checked);

/* Set Kent Hackett. */
document.getElementById("gba-cast-21-friendly").onchange = () => GBAActiveSlot.Cast(21).Friendly(document.getElementById("gba-cast-21-friendly").value);
document.getElementById("gba-cast-21-romance").onchange = () => GBAActiveSlot.Cast(21).Romance(document.getElementById("gba-cast-21-romance").value);
document.getElementById("gba-cast-21-intimidate").onchange = () => GBAActiveSlot.Cast(21).Intimidate(document.getElementById("gba-cast-21-intimidate").value);
document.getElementById("gba-cast-21-feeling").onchange = () => GBAActiveSlot.Cast(21).Feeling(document.getElementById("gba-cast-21-feeling").value);
document.getElementById("gba-cast-21-phone").onchange = () => GBAActiveSlot.Cast(21).Phone(document.getElementById("gba-cast-21-phone").checked);
document.getElementById("gba-cast-21-secret").onchange = () => GBAActiveSlot.Cast(21).Secret(document.getElementById("gba-cast-21-secret").checked);

/* Set Sancho Paco Panza. */
document.getElementById("gba-cast-22-friendly").onchange = () => GBAActiveSlot.Cast(22).Friendly(document.getElementById("gba-cast-22-friendly").value);
document.getElementById("gba-cast-22-romance").onchange = () => GBAActiveSlot.Cast(22).Romance(document.getElementById("gba-cast-22-romance").value);
document.getElementById("gba-cast-22-intimidate").onchange = () => GBAActiveSlot.Cast(22).Intimidate(document.getElementById("gba-cast-22-intimidate").value);
document.getElementById("gba-cast-22-feeling").onchange = () => GBAActiveSlot.Cast(22).Feeling(document.getElementById("gba-cast-22-feeling").value);
document.getElementById("gba-cast-22-phone").onchange = () => GBAActiveSlot.Cast(22).Phone(document.getElementById("gba-cast-22-phone").checked);
document.getElementById("gba-cast-22-secret").onchange = () => GBAActiveSlot.Cast(22).Secret(document.getElementById("gba-cast-22-secret").checked);

/* Set Tank Grunt. */
document.getElementById("gba-cast-23-friendly").onchange = () => GBAActiveSlot.Cast(23).Friendly(document.getElementById("gba-cast-23-friendly").value);
document.getElementById("gba-cast-23-romance").onchange = () => GBAActiveSlot.Cast(23).Romance(document.getElementById("gba-cast-23-romance").value);
document.getElementById("gba-cast-23-intimidate").onchange = () => GBAActiveSlot.Cast(23).Intimidate(document.getElementById("gba-cast-23-intimidate").value);
document.getElementById("gba-cast-23-feeling").onchange = () => GBAActiveSlot.Cast(23).Feeling(document.getElementById("gba-cast-23-feeling").value);
document.getElementById("gba-cast-23-phone").onchange = () => GBAActiveSlot.Cast(23).Phone(document.getElementById("gba-cast-23-phone").checked);
document.getElementById("gba-cast-23-secret").onchange = () => GBAActiveSlot.Cast(23).Secret(document.getElementById("gba-cast-23-secret").checked);

/* Set Tristan Legend. */
document.getElementById("gba-cast-24-friendly").onchange = () => GBAActiveSlot.Cast(24).Friendly(document.getElementById("gba-cast-24-friendly").value);
document.getElementById("gba-cast-24-romance").onchange = () => GBAActiveSlot.Cast(24).Romance(document.getElementById("gba-cast-24-romance").value);
document.getElementById("gba-cast-24-intimidate").onchange = () => GBAActiveSlot.Cast(24).Intimidate(document.getElementById("gba-cast-24-intimidate").value);
document.getElementById("gba-cast-24-feeling").onchange = () => GBAActiveSlot.Cast(24).Feeling(document.getElementById("gba-cast-24-feeling").value);
document.getElementById("gba-cast-24-phone").onchange = () => GBAActiveSlot.Cast(24).Phone(document.getElementById("gba-cast-24-phone").checked);
document.getElementById("gba-cast-24-secret").onchange = () => GBAActiveSlot.Cast(24).Secret(document.getElementById("gba-cast-24-secret").checked);

/* Set Yeti. */
document.getElementById("gba-cast-25-friendly").onchange = () => GBAActiveSlot.Cast(25).Friendly(document.getElementById("gba-cast-25-friendly").value);
document.getElementById("gba-cast-25-romance").onchange = () => GBAActiveSlot.Cast(25).Romance(document.getElementById("gba-cast-25-romance").value);
document.getElementById("gba-cast-25-intimidate").onchange = () => GBAActiveSlot.Cast(25).Intimidate(document.getElementById("gba-cast-25-intimidate").value);
document.getElementById("gba-cast-25-feeling").onchange = () => GBAActiveSlot.Cast(25).Feeling(document.getElementById("gba-cast-25-feeling").value);
document.getElementById("gba-cast-25-phone").onchange = () => GBAActiveSlot.Cast(25).Phone(document.getElementById("gba-cast-25-phone").checked);
document.getElementById("gba-cast-25-secret").onchange = () => GBAActiveSlot.Cast(25).Secret(document.getElementById("gba-cast-25-secret").checked);