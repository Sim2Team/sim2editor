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


import { SavData, SavUtils_Read, SavUtils_Write } from "../shared/savutils.js";


/*
	enum class GBAHouseItemDirection : uint8_t {
		Right = 0x1,
		Down = 0x3,
		Left = 0x5,
		Up = 0x7,
		Invalid = 0xFF
	};
*/

export class S2Editor_GBAHouseItem {
	constructor(Offs) { this.Offs = Offs; };

	/* Get and Set the Item Count. */
	Count(V) {
		if (V != undefined) SavUtils_Write("uint8_t", this.Offs, Math.min(12, V));
		else return SavUtils_Read("uint8_t", this.Offs);
	};

	/* Get and Set the Item ID. */
	ID(Index, V) {
		if (V != undefined) {
			if (this.Count() == 0) return;
			SavUtils_Write("uint8_t", this.Offs + 0x1 + (Math.min(this.Count() - 1, Index) * 0x6), V);

		} else {
			if (this.Count() == 0) return 0xE6; // Empty.
			return SavUtils_Read("uint8_t", this.Offs + 0x1 + (Math.min(this.Count() - 1, Index) * 0x6));
		}
	};

	/* Get and Set the Item Flag. */
	Flag(Index, V) {
		if (V != undefined) {
			if (this.Count() == 0) return;
			SavUtils_Write("uint8_t", this.Offs + 0x2 + (Math.min(this.Count() - 1, Index) * 0x6), V);

		} else {
			if (this.Count() == 0) return 0x0; // No flags.
			return SavUtils_Read("uint8_t", this.Offs + 0x2 + (Math.min(this.Count() - 1, Index) * 0x6));
		}
	};

	/* Get and Set the Use Count(?). */
	UseCount(Index, V) {
		if (V != undefined) {
			if (this.Count() == 0) return;
			SavUtils_Write("uint8_t", this.Offs + 0x3 + (Math.min(this.Count() - 1, Index) * 0x6), V);

		} else {
			if (this.Count() == 0) return 0x0; // No Count.
			return SavUtils_Read("uint8_t", this.Offs + 0x3 + (Math.min(this.Count() - 1, Index) * 0x6));
		}
	};

	/* Get and Set the X Position of the Item. */
	XPos(Index, V) {
		if (V != undefined) {
			if (this.Count() == 0) return;
			SavUtils_Write("uint8_t", this.Offs + 0x4 + (Math.min(this.Count() - 1, Index) * 0x6), V);

		} else {
			if (this.Count() == 0) return 0x0; // Position 0.
			return SavUtils_Read("uint8_t", this.Offs + 0x4 + (Math.min(this.Count() - 1, Index) * 0x6));
		}
	};

	/* Get and Set the Y Position of the Item. */
	YPos(Index, V) {
		if (V != undefined) {
			if (this.Count() == 0) return;
			SavUtils_Write("uint8_t", this.Offs + 0x5 + (Math.min(this.Count() - 1, Index) * 0x6), V);

		} else {
			if (this.Count() == 0) return 0x0; // Position 0.
			return SavUtils_Read("uint8_t", this.Offs + 0x5 + (Math.min(this.Count() - 1, Index) * 0x6));
		}
	};

	/* Get and Set the Item Direction. See commented out code of the C++ enum class version of the direction above for more info. */
	Direction(Index, V) {
		if (V != undefined) {
			if (this.Count() == 0 || V > 4) return;
			const Positions = [ 0x0, 0x1, 0x3, 0x5, 0x7 ];
			SavUtils_Write("uint8_t", this.Offs + 0x6 + (Math.min(this.Count() - 1, Index) * 0x6), Positions[V]);

		} else {
			if (this.Count() == 0) return 0x0; // Position 0.

			const Res = SavUtils_Read("uint8_t", this.Offs + 0x6 + (Math.min(this.Count() - 1, Index) * 0x6));
			switch(Res) {
				case 0x1:
					return 0x1; // Right.

				case 0x3:
					return 0x2; // Down.

				case 0x5:
					return 0x3; // Left.

				case 0x7:
					return 0x4; // Up.

				default:
					return 0x0; // Invalid.
			}
		}
	};

	/*
		Add an Item to the House.
		This needs to be handled like this, because things move 0x6 bytes up when an Item is being added.

		NOTE:
			The game seems to handle it the other way than this;
			by doing an insert or something at the 0xD7'th byte, but this way works too.

	*/
	AddItem(ID, Flag, UseCount, XPos, YPos, Direction) {
		if (this.Count() == 0xC) return false; // Not allowed to add more than 0xC / 12 Items.

		const CT = this.Count();
		this.Count(CT + 0x1);

		let TMP = new Uint8Array(0xF26 - (this.Count() * 6));
		/* Copy first to a TMP buffer. */
		for (let Idx = 0; Idx < 0xF26 - (this.Count() * 6); Idx++) {
			TMP[Idx] = SavUtils_Read("uint8_t", (this.Offs + 0x1) + (CT * 0x6) + Idx);
		}

		/* Then copy to the actual location from the TMP buffer. */
		for (let Idx = 0; Idx < 0xF26 - (this.Count() * 6); Idx++) {
			SavData.setUint8((this.Offs + 0x1) + (this.Count() * 0x6) + Idx, TMP[Idx]);
		}

		/* Set Item Data. */
		this.ID(CT, ID);
		this.Flag(CT, Flag);
		this.UseCount(CT, UseCount);
		this.XPos(CT, XPos);
		this.YPos(CT, YPos);
		this.Direction(CT, Direction);

		return true;
	};

	/*
		Remove an Item from the House.
		This needs to be handled like this, because things move 0x6 bytes down when an Item is being removed.
	*/
	RemoveItem(Index) {
		if ((this.Count() == 0) || (this.Count() - 1 < Index)) return false; // Nanana, Index and or Count is not good.

		this.Count(this.Count() - 0x1);
		let TMP = new Uint8Array(0xF26 - (this.Count() * 6));

		/* Copy first to a TMP buffer. */
		for (let Idx = 0; Idx < 0xF26 - (this.Count() * 6); Idx++) {
			TMP[Idx] = SavUtils_Read("uint8_t", (this.Offs + 0x1) + ((Index + 0x1) * 0x6) + Idx);
		}

		/* Then copy to the actual location from the TMP buffer. */
		for (let Idx = 0; Idx < 0xF26 - (this.Count() * 6); Idx++) {
			SavData.setUint8((this.Offs + 0x1) + (Index * 0x6) + Idx, TMP[Idx]);
		}

		return true;
	};
};