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

import { SimUtils_RatingFormat, SimUtils_SimoleonFormat, SimUtils_TimeString } from "../../../Sim2Editor-Core/shared/simutils.js";
import { GBAActiveSlot, GBACurrentSlot } from "./gba-slot-menu.js";


/*
	Initializes the Game Boy Advance General Menu.
*/
export function InitGBAGeneralEditor() {
	if (GBAActiveSlot != undefined) {
		/* Main General. */
		document.getElementById("gba-general-name").value = GBAActiveSlot.Name();
		document.getElementById("gba-general-simoleons").value = GBAActiveSlot.Simoleons();
		document.getElementById("gba-general-ratings").value = GBAActiveSlot.Ratings();
		document.getElementById("gba-general-time-hour").value = GBAActiveSlot.Time()[0];
		document.getElementById("gba-general-time-minute").value = GBAActiveSlot.Time()[1];

		/* Collectables - Amount. */
		document.getElementById("gba-general-cans-amount").value = GBAActiveSlot.Cans();
		document.getElementById("gba-general-cowbells-amount").value = GBAActiveSlot.Cowbells();
		document.getElementById("gba-general-spaceship-amount").value = GBAActiveSlot.Spaceship();
		document.getElementById("gba-general-fuelrods-amount").value = GBAActiveSlot.Fuelrods();

		/* Collectables - Sell Prices. */
		document.getElementById("gba-general-cans-price").value = GBAActiveSlot.CansPrice();
		document.getElementById("gba-general-cowbells-price").value = GBAActiveSlot.CowbellsPrice();
		document.getElementById("gba-general-spaceship-price").value = GBAActiveSlot.SpaceshipPrice();
		document.getElementById("gba-general-fuelrods-price").value = GBAActiveSlot.FuelrodsPrice();

		/* Skillpoints. */
		document.getElementById("gba-general-confidence").value = GBAActiveSlot.Confidence();
		document.getElementById("gba-general-mechanical").value = GBAActiveSlot.Mechanical();
		document.getElementById("gba-general-strength").value = GBAActiveSlot.Strength();
		document.getElementById("gba-general-personality").value = GBAActiveSlot.Personality();
		document.getElementById("gba-general-hotness").value = GBAActiveSlot.Hotness();
		document.getElementById("gba-general-intellect").value = GBAActiveSlot.Intellect();
	}
};

/*
	The following functions update the slot info display as well.
*/
function UpdateName() {
	GBAActiveSlot.Name(document.getElementById("gba-general-name").value);
	document.getElementById(GBACurrentSlot + "-name").innerText = GBAActiveSlot.Name();
};

function UpdateSimoleons() {
	GBAActiveSlot.Simoleons(document.getElementById("gba-general-simoleons").value);
	document.getElementById(GBACurrentSlot + "-simoleons").innerText = SimUtils_SimoleonFormat(GBAActiveSlot.Simoleons());
};

function UpdateRatings() {
	GBAActiveSlot.Ratings(document.getElementById("gba-general-ratings").value);
	document.getElementById(GBACurrentSlot + "-ratings").innerText = SimUtils_RatingFormat(GBAActiveSlot.Ratings());
};

function UpdateTime() {
	let EditedTime = new Uint8Array(0x2);
	EditedTime[0] = document.getElementById("gba-general-time-hour").value;
	EditedTime[1] = document.getElementById("gba-general-time-minute").value;

	/* Ensure no invalid time has been entered. */
	if (EditedTime[0] < 24 && EditedTime[1] < 60) {
		GBAActiveSlot.Time(EditedTime);

		document.getElementById(GBACurrentSlot + "-time").innerText = SimUtils_TimeString(GBAActiveSlot.Time(), false);
	}
};


/* Set Generals. */
document.getElementById("gba-general-name").onchange = () => UpdateName();
document.getElementById("gba-general-simoleons").onchange = () => UpdateSimoleons();
document.getElementById("gba-general-ratings").onchange = () => UpdateRatings();
document.getElementById("gba-general-time-hour").onchange = () => UpdateTime();
document.getElementById("gba-general-time-minute").onchange = () => UpdateTime();

/* Set Collectables - Amounts. */
document.getElementById("gba-general-cans-amount").onchange = () => GBAActiveSlot.Cans(document.getElementById("gba-general-cans-amount").value);
document.getElementById("gba-general-cowbells-amount").onchange = () => GBAActiveSlot.Cowbells(document.getElementById("gba-general-cowbells-amount").value);
document.getElementById("gba-general-spaceship-amount").onchange = () => GBAActiveSlot.Spaceship(document.getElementById("gba-general-spaceship-amount").value);
document.getElementById("gba-general-fuelrods-amount").onchange = () => GBAActiveSlot.Fuelrods(document.getElementById("gba-general-fuelrods-amount").value);

/* Set Collectables - Sell Prices. */
document.getElementById("gba-general-cans-price").onchange = () => GBAActiveSlot.CansPrice(document.getElementById("gba-general-cans-price").value);
document.getElementById("gba-general-cowbells-price").onchange = () => GBAActiveSlot.CowbellsPrice(document.getElementById("gba-general-cowbells-price").value);
document.getElementById("gba-general-spaceship-price").onchange = () => GBAActiveSlot.SpaceshipPrice(document.getElementById("gba-general-spaceship-price").value);
document.getElementById("gba-general-fuelrods-price").onchange = () => GBAActiveSlot.FuelrodsPrice(document.getElementById("gba-general-fuelrods-price").value);

/* Set Skillpoints. */
document.getElementById("gba-general-confidence").onchange = () => GBAActiveSlot.Confidence(document.getElementById("gba-general-confidence").value);
document.getElementById("gba-general-mechanical").onchange = () => GBAActiveSlot.Mechanical(document.getElementById("gba-general-mechanical").value);
document.getElementById("gba-general-strength").onchange = () => GBAActiveSlot.Strength(document.getElementById("gba-general-strength").value);
document.getElementById("gba-general-personality").onchange = () => GBAActiveSlot.Personality(document.getElementById("gba-general-personality").value);
document.getElementById("gba-general-hotness").onchange = () => GBAActiveSlot.Hotness(document.getElementById("gba-general-hotness").value);
document.getElementById("gba-general-intellect").onchange = () => GBAActiveSlot.Intellect(document.getElementById("gba-general-intellect").value);