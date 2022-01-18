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


import { Checksum_CalcGBASettings } from "../shared/checksum.js";
import { SavData, SavUtils_Read, SavUtils_Write } from "../shared/savutils.js";

/*
	enum class GBALanguage : uint8_t {
		EN, // English 0x0
		NL, // Nederlands 0x1
		FR, // Français 0x2
		DE, // Deutsch 0x3
		IT, // Italiano 0x4
		ES  // Español 0x5
	};
*/

/* Sound Effect and Music Levels. */
const SFXLevels = [ 0x0, 0x0C, 0x18, 0x24, 0x30, 0x3C, 0x48, 0x54, 0x60, 0x6C, 0x80 ];
const MUSLevels = [ 0x0, 0x19, 0x32, 0x4B, 0x64, 0x7D, 0x96, 0xAF, 0xC8, 0xE1, 0xFF ];


export class S2Editor_GBASettings {
	constructor() { };

	/* Get and Set the Sound Effect Volume. */
	SFX(V) {
		if (V != undefined) {
			if (V > 10) return; // 0 - 10 only valid.
			SavUtils_Write("uint8_t", 0x8, SFXLevels[V]);

		} else {
			return SavUtils_Read("uint8_t", 0x8);
		}
	};

	/* Get and Set the Music Volume. */
	Music(V) {
		if (V != undefined) {
			if (V > 10) return; // 0 - 10 only valid.
			SavUtils_Write("uint8_t", 0x9, MUSLevels[V]);

		} else {
			return SavUtils_Read("uint8_t", 0x9);
		}
	};

	/* Get and Set the Language. See commented out C++ enum class above for more. */
	Language(V) {
		if (V != undefined) {
			if (V > 5) return;
			SavUtils_Write("uint8_t", 0xA, V);

		} else {
			if (SavUtils_Read("uint8_t", 0xA) > 5) return 0;
			return SavUtils_Read("uint8_t", 0xA);
		}
	};

	/* Update the Checksum of the GBA Settings. */
	UpdateChecksum() {
		const CurCHKS = SavUtils_Read("uint16_t", 0xE);
		const Calced = Checksum_CalcGBASettings(SavData);

		/* If the calced result is NOT the current checksum. */
		if (Calced != CurCHKS) SavUtils_Write("uint16_t", 0xE, Calced);
	};
};