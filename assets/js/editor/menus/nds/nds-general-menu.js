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

import { SimUtils_SimoleonFormat } from "../../../core/shared/simutils.js";
import { NDSActiveSlot, NDSCurrentSlot } from "./nds-slot-menu.js";


/*
	Initializes the Nintendo DS General Menu.
*/
export function InitNDSGeneralEditor() {
	if (NDSActiveSlot != undefined) {
		/* Main General. */
		document.getElementById("nds-general-name").value = NDSActiveSlot.Name();
		document.getElementById("nds-general-simoleons").value = NDSActiveSlot.Simoleons();

		/* Collectibles. */
		document.getElementById("nds-general-fuelrods-amount").value = NDSActiveSlot.Fuelrods();
		document.getElementById("nds-general-plates-amount").value = NDSActiveSlot.Plates();
		document.getElementById("nds-general-gourds-amount").value = NDSActiveSlot.Gourds();
		document.getElementById("nds-general-spaceship-amount").value = NDSActiveSlot.Spaceship();

		/* Skillpoints. */
		document.getElementById("nds-general-creativity").value = NDSActiveSlot.Creativity();
		document.getElementById("nds-general-business").value = NDSActiveSlot.Business();
		document.getElementById("nds-general-body").value = NDSActiveSlot.Body();
		document.getElementById("nds-general-charisma").value = NDSActiveSlot.Charisma();
		document.getElementById("nds-general-mechanical").value = NDSActiveSlot.Mechanical();
	}
};


/*
	The following functions update the slot info display as well.
*/
function UpdateName() {
	if (document.getElementById("nds-general-name").value == "") return; // Don't let it blank.

	NDSActiveSlot.Name(document.getElementById("nds-general-name").value);
	document.getElementById(NDSCurrentSlot + "-name").innerText = NDSActiveSlot.Name();
};

function UpdateSimoleons() {
	NDSActiveSlot.Simoleons(document.getElementById("nds-general-simoleons").value);
	document.getElementById(NDSCurrentSlot + "-simoleons").innerText = SimUtils_SimoleonFormat(NDSActiveSlot.Simoleons());
};


/* Set Generals. */
document.getElementById("nds-general-name").onchange = () => UpdateName();
document.getElementById("nds-general-simoleons").onchange = () => UpdateSimoleons();

/* Set Collectibles. */
document.getElementById("nds-general-fuelrods-amount").onchange = () => NDSActiveSlot.Fuelrods(document.getElementById("nds-general-fuelrods-amount").value);
document.getElementById("nds-general-plates-amount").onchange = () => NDSActiveSlot.Plates(document.getElementById("nds-general-plates-amount").value);
document.getElementById("nds-general-gourds-amount").onchange = () => NDSActiveSlot.Gourds(document.getElementById("nds-general-gourds-amount").value);
document.getElementById("nds-general-spaceship-amount").onchange = () => NDSActiveSlot.Spaceship(document.getElementById("nds-general-spaceship-amount").value);

/* Set Skillpoints. */
document.getElementById("nds-general-creativity").onchange = () => NDSActiveSlot.Creativity(document.getElementById("nds-general-creativity").value);
document.getElementById("nds-general-business").onchange = () => NDSActiveSlot.Business(document.getElementById("nds-general-business").value);
document.getElementById("nds-general-body").onchange = () => NDSActiveSlot.Body(document.getElementById("nds-general-body").value);
document.getElementById("nds-general-charisma").onchange = () => NDSActiveSlot.Charisma(document.getElementById("nds-general-charisma").value);
document.getElementById("nds-general-mechanical").onchange = () => NDSActiveSlot.Mechanical(document.getElementById("nds-general-mechanical").value);