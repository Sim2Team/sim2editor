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

/*
	enum class SocialMoveFlag : uint8_t {
		Locked = 0x0,
		Unlocked = 0x1,
		Blocked = 0x2
	};
*/


export class S2Editor_GBASocialMove {
	constructor(Offs, Move) {
		this.Offs = Offs;
		this.Move = Move;
	};

	/* Get Social Move Index. */
	Index() { return this.Move; };

	/* Get and Set the Social Move Flag. See commented enum class C++ version above for reference of values. */
	Flag(V) {
		if (V != undefined) SavUtils_Write("uint8_t", this.Offs, Math.min(2, V));
		else return SavUtils_Read("uint8_t", this.Offs);
	};

	/* Get and Set the Social Move Level. */
	Level(V) {
		if (V != undefined) SavUtils_Write("uint8_t", this.Offs + 0x4, Math.min(3, V));
		else return SavUtils_Read("uint8_t", this.Offs + 0x4);
	};

	/* Get and Set the Social Move Blocked Hours. */
	BlockedHours(V) {
		if (V != undefined) SavUtils_Write("uint8_t", this.Offs + 0x6, V);
		else return SavUtils_Read("uint8_t", this.Offs + 0x6);
	};
};