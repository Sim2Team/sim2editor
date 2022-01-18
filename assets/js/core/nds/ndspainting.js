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


import { Checksum_Calc } from "../shared/checksum.js";
import { SavData, SavUtils_Read, SavUtils_ReadBits, SavUtils_Write, SavUtils_WriteBits } from "../shared/savutils.js";


/*
	Painting Palettes.
	15 Colors for each of the 16 Palettes.

	Format is: R G B in Hexadecimal.
*/
export const PaintingPalette = [
	"F8F8F8", "C0C0C0", "808080", "000000", "00A0F8", "0078E0", "0048C8", "50F800", "28C000", "008000", "F8F800", "E8C800", "D09000", "F83038", "C00000",
	"F8F8F8", "C0C0C0", "808080", "484848", "A0D8F8", "80B8E0", "5898C8", "B8F898", "98D080", "78F890", "F8F890", "D8D070", "B8A850", "F8B8B8", "F89090",
	"F8F8F8", "986820", "000000", "D000F8", "8828F8", "3070F8", "0090F8", "18A8A8", "38B850", "50D000", "A8E000", "F8E800", "F8B000", "F87800", "F84000",
	"F8F8F8", "2880D8", "1898E0", "08B8F0", "00D0F8", "00B8A8", "00A850", "009800", "F8E070", "F8A858", "F87048", "F80828", "F890E0", "E878B0", "D06080",
	"F8F8F8", "C0C8F8", "8898F8", "4068D8", "0038B8", "B8C000", "A0A800", "889000", "708000", "586800", "E0C098", "D08048", "C04000", "803000", "401800",
	"F8F8F8", "78E8F8", "00D0F8", "00B8F8", "00A0F8", "80F000", "40D008", "00B010", "008008", "005800", "C89000", "B08000", "986800", "785800", "604000",
	"F8F8F8", "808080", "000000", "00F8F8", "00A0A8", "004850", "C0F800", "80A800", "385000", "F84878", "A82850", "581028", "F820F8", "A820A8", "501850",
	"F8F8F8", "B8B8B8", "000000", "18B8F8", "0898D0", "0078A8", "D0E878", "90B840", "508010", "F8B838", "C89018", "A07000", "F880A0", "F84878", "981030",
	"F8F8F8", "C0C0C0", "808080", "000000", "F8A090", "D87870", "B85848", "983028", "E0B078", "C8A068", "A88858", "907040", "90D890", "50B870", "10A058",
	"F8F8F8", "A8A8A8", "505050", "E80040", "B00030", "780020", "B860F8", "8848C0", "603880", "403060", "0070D8", "0058A8", "004080", "002850", "000000",
	"F8F8F8", "C0C0C0", "808080", "484848", "000000", "98A8F8", "8080D8", "6060B8", "484090", "281870", "F8F878", "F0C038", "E88000", "E04000", "C00000",
	"F8F8F8", "B07858", "A06040", "885028", "703818", "602800", "B08030", "906818", "685000", "5070A8", "303850", "100000", "F0C000", "D8A000", "C88000",
	"F8F8F8", "F8D0A8", "E8B890", "D0A070", "B88050", "A06838", "F8E070", "E0A038", "C06000", "884000", "582000", "200000", "0068C8", "205090", "403860",
	"F8F8F8", "E0F0F8", "C8E0F0", "B0D0E8", "98C0E0", "80B0E0", "68A0D8", "5090D0", "4880B8", "4070A8", "386090", "305078", "284060", "203050", "101828",
	"F8F8F8", "F0E8D8", "E8D8B8", "E0C898", "D8B870", "D0A858", "C89840", "C08830", "B87818", "A87010", "986010", "805008", "704008", "583000", "482000",
	"F8F8F8", "F0F0F0", "E0E0E0", "D0D0D0", "C0C0C0", "B0B0B0", "A0A0A0", "909090", "888888", "787878", "686868", "585858", "484848", "383838", "000000"
];


/*
	For reference, see here: https://sim2team.github.io/wiki/research/sims2nds/painting.
*/

export class S2Editor_NDSPainting {
	constructor(Offset) { this.Offs = Offset };

	/* Get and Set the Painting Index. The higher, the more likely it's an actual used Painting. */
	Index(V) {
		if (V != undefined) SavUtils_Write("uint32_t", this.Offs + 0x8, V);
		else return SavUtils_Read("uint32_t", this.Offs + 0x8);
	};

	/* Get and Set to which Slot the Painting is. */
	Slot(V) {
		if (V != undefined) SavUtils_Write("uint8_t", this.Offs + 0xC, V);
		else return SavUtils_Read("uint8_t", this.Offs + 0xC);
	};

	/* Get and Set the Canvas Index. */
	CanvasIdx(V) {
		if (V != undefined) SavUtils_Write("uint8_t", this.Offs + 0xD, Math.min(0x5, V));
		else return SavUtils_Read("uint8_t", this.Offs + 0xD);
	};

	/* Get and Set the Palette Index of the Painting Image. */
	Palette(V) {
		if (V != undefined) SavUtils_Write("uint8_t", this.Offs + 0x315, Math.min(0xF, V));
		else return SavUtils_Read("uint8_t", this.Offs + 0x315);
	};

	/* Get and Set the Painting Image Flag. */
	Flag(V) {
		if (V != undefined) SavUtils_Write("uint8_t", this.Offs + 0x314, V);
		else return SavUtils_Read("uint8_t", this.Offs + 0x314);
	};

	/* Get and Set a Pixel of the Painting Image. */
	Pixel(Idx, V) {
		if (Idx >= 0x600) return 0; // Out of scope.

		if (V != undefined) SavUtils_WriteBits(this.Offs + 0x14 + (Idx / 2), (Idx % 2 == 0), Math.min(0xF, V));
		else return SavUtils_ReadBits(this.Offs + 0x14 + (Idx / 2), (Idx % 2 == 0));
	};

	/* Same as the Pixel function, but with X and Y Position instead of full index. */
	PixelPos(X, Y, V) {
		if (V != undefined) this.Pixel(X + (Y * 48), V);
		else return this.Pixel(X + (Y * 48));
	};


	/*
		Returns the Painting Image as a <canvas> element.

		Scale: The scale of the canvas, by default 48x32 (original size).
	*/
	Image(Scale = 1) {
		/* Create a new canvas. */
		let Img = document.createElement("canvas");
		Img.width  = 48 * Scale;
		Img.height = 32 * Scale;
		let ImgContext = Img.getContext("2d");

		for (let Y = 0; Y < 32; Y++) {
			for (let X = 0; X < 48; X++) {
				ImgContext.fillStyle = "#" + PaintingPalette[Math.max(0, this.PixelPos(X, Y) - 1) + (this.Palette() * 15)];
				ImgContext.fillRect(X * Scale, Y * Scale, Scale, Scale);
			}
		}

		return Img;
	};

	/*
		Update the header and "main" checksum of the Painting.

		Updating the Main one first is IMPORTANT, as the Header relies on the "main" checksum value.
	*/
	UpdateChecksum() {
		/* First: Main. */
		let Calced = Checksum_Calc(SavData, (this.Offs + 0x10) / 2, (this.Offs + 0x400) / 2, [(this.Offs + 0x10) / 2]);
		let CurCHKS = SavUtils_Read("uint16_t", this.Offs + 0x10);
		if (CurCHKS != Calced) SavUtils_Write("uint16_t", this.Offs + 0x10, Calced);

		/* Then: Header. */
		Calced = Checksum_Calc(SavData, (this.Offs) / 2, (this.Offs + 0x13) / 2, [(this.Offs + 0xE) / 2]);
		CurCHKS = SavUtils_Read("uint16_t", this.Offs + 0xE);
		if (CurCHKS != Calced) SavUtils_Write("uint16_t", this.Offs + 0xE, Calced);
	};
};