/*
*   This file is part of Sim2Editor-JSCore
*   Copyright (C) 2020-2022 Sim2Team
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


import { SavUtils_Read, SavUtils_Write } from "../shared/savutils.js";


export class S2Editor_GBACast {
	constructor(Offs, Cast) {
		this.Offs = Offs;
		this.Cast = Cast;
	};

	/* Get Cast Index. */
	Index() { return this.Cast; };

	/* Get and Set Friendly Conversation level. */
	Friendly(V) {
		if (V != undefined) SavUtils_Write("uint8_t", this.Offs, Math.min(3, V));
		else return SavUtils_Read("uint8_t", this.Offs);
	};

	/* Get and Set Romance Conversation level. */
	Romance(V) {
		if (V != undefined) SavUtils_Write("uint8_t", this.Offs + 0x1, Math.min(3, V));
		else return SavUtils_Read("uint8_t", this.Offs + 0x1);
	};

	/* Get and Set Intimidate Conversation level. */
	Intimidate(V) {
		if (V != undefined) SavUtils_Write("uint8_t", this.Offs + 0x2, Math.min(3, V));
		else return SavUtils_Read("uint8_t", this.Offs + 0x2);
	};

	/*
		Get and Set the Feeling.

		0:  Neutral.
		1:  Happy.
		2:  Angry.
		3:  Romantic.
		4+: Invalid.
	*/
	Feeling(V) {
		if (V != undefined) SavUtils_Write("uint8_t", this.Offs + 0x3, Math.min(4, V));
		else return SavUtils_Read("uint8_t", this.Offs + 0x3);
	};

	/* Get and Set the Feeling Effect Hours. */
	FeelingEffectHours(V) {
		if (V != undefined) SavUtils_Write("uint8_t", this.Offs + 0x6, V);
		else return SavUtils_Read("uint8_t", this.Offs + 0x6);
	};

	/* Get and Set the registered on phone state. */
	RegisteredOnPhone(V) {
		if (V != undefined) SavUtils_Write("uint8_t", this.Offs + 0x7, Math.min(1, V));
		else return SavUtils_Read("uint8_t", this.Offs + 0x7) == 1;
	};

	/* Get and Set Secret Unlock state. */
	Secret(V) {
		if (V != undefined) SavUtils_Write("uint8_t", this.Offs + 0x8, Math.min(1, V));
		else return SavUtils_Read("uint8_t", this.Offs + 0x8) == 1;
	};
};