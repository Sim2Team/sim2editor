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

import S2Editor_GBAItemList_EN from "../../../core/strings/en/gba/itemlist.js";
import { GBAActiveSlot } from "./gba-slot-menu.js";

let ListInitialized = false;

/*
	Initializes the Game Boy Advance Item Package Menu.
*/
export function InitGBAItemPackageEditor() {
	/* Only do this ONE time. */
	if (!ListInitialized) {
		ListInitialized = true;

		/* Initialize Game Boy Advance Item list. */
		for (let Idx = 0; Idx < 256; Idx++) {
			let Item = document.createElement("option");

			Item.value = Idx;
			Item.innerHTML = S2Editor_GBAItemList_EN[Idx];

			document.getElementById("gba-item-package-item-selector").appendChild(Item);
		}

		document.getElementById("gba-item-package-item-selector").value = 0xE6;
	}

	if (GBAActiveSlot != undefined) {
		/* Init Pawnshop Items. */
		for (let Idx = 0; Idx < 6; Idx++) {
			let Package = GBAActiveSlot.Pawnshop();

			document.getElementById("gba-pawnshop-" + Idx.toString() + "-name").innerText = S2Editor_GBAItemList_EN[Package.ID(Idx)];
			document.getElementById("gba-pawnshop-" + Idx.toString() + "-id").innerText = Package.ID(Idx).toString();
		}

		/* Init Saloon Items. */
		for (let Idx = 0; Idx < 6; Idx++) {
			let Package = GBAActiveSlot.Saloon();

			document.getElementById("gba-saloon-" + Idx.toString() + "-name").innerText = S2Editor_GBAItemList_EN[Package.ID(Idx)];
			document.getElementById("gba-saloon-" + Idx.toString() + "-id").innerText = Package.ID(Idx).toString();
		}

		/* Init Skillbook Seller Items. */
		for (let Idx = 0; Idx < 6; Idx++) {
			let Package = GBAActiveSlot.Skills();

			document.getElementById("gba-skillbook-" + Idx.toString() + "-name").innerText = S2Editor_GBAItemList_EN[Package.ID(Idx)];
			document.getElementById("gba-skillbook-" + Idx.toString() + "-id").innerText = Package.ID(Idx).toString();
		}

		/* Init Mailbox Items. */
		for (let Idx = 0; Idx < 6; Idx++) {
			let Package = GBAActiveSlot.Mailbox();

			document.getElementById("gba-mailbox-" + Idx.toString() + "-name").innerText = S2Editor_GBAItemList_EN[Package.ID(Idx)];
			document.getElementById("gba-mailbox-" + Idx.toString() + "-id").innerText = Package.ID(Idx).toString();
		}

		/* Init Inventory Items. */
		for (let Idx = 0; Idx < 6; Idx++) {
			let Package = GBAActiveSlot.Inventory();

			document.getElementById("gba-inventory-" + Idx.toString() + "-name").innerText = S2Editor_GBAItemList_EN[Package.ID(Idx)];
			document.getElementById("gba-inventory-" + Idx.toString() + "-id").innerText = Package.ID(Idx).toString();
		}
	}
};


/* Pawnshop Getter and Setter. */
function GetPawnshop(Idx) {
	document.getElementById("gba-item-package-item-selector").value = GBAActiveSlot.Pawnshop().ID(Idx);
};
function SetPawnshop(Idx) {
	GBAActiveSlot.Pawnshop().ID(Idx, document.getElementById("gba-item-package-item-selector").value);

	/* Refresh display. */
	document.getElementById("gba-pawnshop-" + Idx.toString() + "-name").innerText = S2Editor_GBAItemList_EN[GBAActiveSlot.Pawnshop().ID(Idx)];
	document.getElementById("gba-pawnshop-" + Idx.toString() + "-id").innerText = GBAActiveSlot.Pawnshop().ID(Idx).toString();
};

/* Pawnshop Getters. */
document.getElementById("gba-pawnshop-0-get").onclick = () => GetPawnshop(0);
document.getElementById("gba-pawnshop-1-get").onclick = () => GetPawnshop(1);
document.getElementById("gba-pawnshop-2-get").onclick = () => GetPawnshop(2);
document.getElementById("gba-pawnshop-3-get").onclick = () => GetPawnshop(3);
document.getElementById("gba-pawnshop-4-get").onclick = () => GetPawnshop(4);
document.getElementById("gba-pawnshop-5-get").onclick = () => GetPawnshop(5);

/* Pawnshop Setters. */
document.getElementById("gba-pawnshop-0-set").onclick = () => SetPawnshop(0);
document.getElementById("gba-pawnshop-1-set").onclick = () => SetPawnshop(1);
document.getElementById("gba-pawnshop-2-set").onclick = () => SetPawnshop(2);
document.getElementById("gba-pawnshop-3-set").onclick = () => SetPawnshop(3);
document.getElementById("gba-pawnshop-4-set").onclick = () => SetPawnshop(4);
document.getElementById("gba-pawnshop-5-set").onclick = () => SetPawnshop(5);



/* Saloon Getter and Setter. */
function GetSaloon(Idx) {
	document.getElementById("gba-item-package-item-selector").value = GBAActiveSlot.Saloon().ID(Idx);
};
function SetSaloon(Idx) {
	GBAActiveSlot.Saloon().ID(Idx, document.getElementById("gba-item-package-item-selector").value);

	/* Refresh display. */
	document.getElementById("gba-saloon-" + Idx.toString() + "-name").innerText = S2Editor_GBAItemList_EN[GBAActiveSlot.Saloon().ID(Idx)];
	document.getElementById("gba-saloon-" + Idx.toString() + "-id").innerText = GBAActiveSlot.Saloon().ID(Idx).toString();
};

/* Saloon Getters. */
document.getElementById("gba-saloon-0-get").onclick = () => GetSaloon(0);
document.getElementById("gba-saloon-1-get").onclick = () => GetSaloon(1);
document.getElementById("gba-saloon-2-get").onclick = () => GetSaloon(2);
document.getElementById("gba-saloon-3-get").onclick = () => GetSaloon(3);
document.getElementById("gba-saloon-4-get").onclick = () => GetSaloon(4);
document.getElementById("gba-saloon-5-get").onclick = () => GetSaloon(5);

/* Saloon Setters. */
document.getElementById("gba-saloon-0-set").onclick = () => SetSaloon(0);
document.getElementById("gba-saloon-1-set").onclick = () => SetSaloon(1);
document.getElementById("gba-saloon-2-set").onclick = () => SetSaloon(2);
document.getElementById("gba-saloon-3-set").onclick = () => SetSaloon(3);
document.getElementById("gba-saloon-4-set").onclick = () => SetSaloon(4);
document.getElementById("gba-saloon-5-set").onclick = () => SetSaloon(5);



/* Skillbook Seller Getter and Setter. */
function GetSkillbooks(Idx) {
	document.getElementById("gba-item-package-item-selector").value = GBAActiveSlot.Skills().ID(Idx);
};
function SetSkillbooks(Idx) {
	GBAActiveSlot.Skills().ID(Idx, document.getElementById("gba-item-package-item-selector").value);

	/* Refresh display. */
	document.getElementById("gba-skillbook-" + Idx.toString() + "-name").innerText = S2Editor_GBAItemList_EN[GBAActiveSlot.Skills().ID(Idx)];
	document.getElementById("gba-skillbook-" + Idx.toString() + "-id").innerText = GBAActiveSlot.Skills().ID(Idx).toString();
};

/* Skillbook Seller Getters. */
document.getElementById("gba-skillbook-0-get").onclick = () => GetSkillbooks(0);
document.getElementById("gba-skillbook-1-get").onclick = () => GetSkillbooks(1);
document.getElementById("gba-skillbook-2-get").onclick = () => GetSkillbooks(2);
document.getElementById("gba-skillbook-3-get").onclick = () => GetSkillbooks(3);
document.getElementById("gba-skillbook-4-get").onclick = () => GetSkillbooks(4);
document.getElementById("gba-skillbook-5-get").onclick = () => GetSkillbooks(5);

/* Skillbook Seller Setters. */
document.getElementById("gba-skillbook-0-set").onclick = () => SetSkillbooks(0);
document.getElementById("gba-skillbook-1-set").onclick = () => SetSkillbooks(1);
document.getElementById("gba-skillbook-2-set").onclick = () => SetSkillbooks(2);
document.getElementById("gba-skillbook-3-set").onclick = () => SetSkillbooks(3);
document.getElementById("gba-skillbook-4-set").onclick = () => SetSkillbooks(4);
document.getElementById("gba-skillbook-5-set").onclick = () => SetSkillbooks(5);



/* Mailbox Getter and Setter. */
function GetMailbox(Idx) {
	document.getElementById("gba-item-package-item-selector").value = GBAActiveSlot.Mailbox().ID(Idx);
};
function SetMailbox(Idx) {
	GBAActiveSlot.Mailbox().ID(Idx, document.getElementById("gba-item-package-item-selector").value);

	/* Refresh display. */
	document.getElementById("gba-mailbox-" + Idx.toString() + "-name").innerText = S2Editor_GBAItemList_EN[GBAActiveSlot.Mailbox().ID(Idx)];
	document.getElementById("gba-mailbox-" + Idx.toString() + "-id").innerText = GBAActiveSlot.Mailbox().ID(Idx).toString();
};

/* Mailbox Getters. */
document.getElementById("gba-mailbox-0-get").onclick = () => GetMailbox(0);
document.getElementById("gba-mailbox-1-get").onclick = () => GetMailbox(1);
document.getElementById("gba-mailbox-2-get").onclick = () => GetMailbox(2);
document.getElementById("gba-mailbox-3-get").onclick = () => GetMailbox(3);
document.getElementById("gba-mailbox-4-get").onclick = () => GetMailbox(4);
document.getElementById("gba-mailbox-5-get").onclick = () => GetMailbox(5);

/* Mailbox Setters. */
document.getElementById("gba-mailbox-0-set").onclick = () => SetMailbox(0);
document.getElementById("gba-mailbox-1-set").onclick = () => SetMailbox(1);
document.getElementById("gba-mailbox-2-set").onclick = () => SetMailbox(2);
document.getElementById("gba-mailbox-3-set").onclick = () => SetMailbox(3);
document.getElementById("gba-mailbox-4-set").onclick = () => SetMailbox(4);
document.getElementById("gba-mailbox-5-set").onclick = () => SetMailbox(5);



/* Inventory Getter and Setter. */
function GetInventory(Idx) {
	document.getElementById("gba-item-package-item-selector").value = GBAActiveSlot.Inventory().ID(Idx);
};
function SetInventory(Idx) {
	GBAActiveSlot.Inventory().ID(Idx, document.getElementById("gba-item-package-item-selector").value);

	/* Refresh display. */
	document.getElementById("gba-inventory-" + Idx.toString() + "-name").innerText = S2Editor_GBAItemList_EN[GBAActiveSlot.Inventory().ID(Idx)];
	document.getElementById("gba-inventory-" + Idx.toString() + "-id").innerText = GBAActiveSlot.Inventory().ID(Idx).toString();
};

/* Inventory Getters. */
document.getElementById("gba-inventory-0-get").onclick = () => GetInventory(0);
document.getElementById("gba-inventory-1-get").onclick = () => GetInventory(1);
document.getElementById("gba-inventory-2-get").onclick = () => GetInventory(2);
document.getElementById("gba-inventory-3-get").onclick = () => GetInventory(3);
document.getElementById("gba-inventory-4-get").onclick = () => GetInventory(4);
document.getElementById("gba-inventory-5-get").onclick = () => GetInventory(5);

/* Inventory Setters. */
document.getElementById("gba-inventory-0-set").onclick = () => SetInventory(0);
document.getElementById("gba-inventory-1-set").onclick = () => SetInventory(1);
document.getElementById("gba-inventory-2-set").onclick = () => SetInventory(2);
document.getElementById("gba-inventory-3-set").onclick = () => SetInventory(3);
document.getElementById("gba-inventory-4-set").onclick = () => SetInventory(4);
document.getElementById("gba-inventory-5-set").onclick = () => SetInventory(5);