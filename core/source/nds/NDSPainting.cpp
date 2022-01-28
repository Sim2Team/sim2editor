/*
*   This file is part of Sim2Editor-CPPCore
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

#include "NDSPainting.hpp"
#include "../Strings.hpp"
#include "../shared/Checksum.hpp"
#include "../shared/SavUtils.hpp"


namespace S2Core {
	/*
		Checks, if the Painting is valid by checking it's 5 byte Identifier.
	*/
	bool NDSPainting::Valid() const {
		for (uint8_t Idx = 0; Idx < 5; Idx++) {
			if (SavUtils::Read<uint8_t>(this->Offs + Idx) != this->Identifier[Idx]) return false; // Invalid.
		}

		return true;
	};

	/* Get and Set the Index of the Painting. It is similar to a creation count though. */
	uint32_t NDSPainting::Index() const { return SavUtils::Read<uint32_t>(this->Offs + 0x8); };
	void NDSPainting::Index(const uint32_t V) { SavUtils::Write<uint32_t>(this->Offs + 0x8, V); };

	/* Get and Set to which Slot the Painting exist. */
	uint8_t NDSPainting::Slot() const { return SavUtils::Read<uint8_t>(this->Offs + 0xC); };
	void NDSPainting::Slot(const uint8_t V) { SavUtils::Write<uint8_t>(this->Offs + 0xC, std::min<uint8_t>(5, V)); };

	/* Get and Set to which Canvas the Painting is drawn on. */
	uint8_t NDSPainting::CanvasIdx() const { return SavUtils::Read<uint8_t>(this->Offs + 0xD); };
	void NDSPainting::CanvasIdx(const uint8_t V) { SavUtils::Write<uint8_t>(this->Offs + 0xD, std::min<uint8_t>(5, V)); };

	/* Get and Set the Pixel of the Painting Image Data. */
	uint8_t NDSPainting::Pixel(const uint16_t Idx) const {
		if (Idx >= 0x600) return 0;

		return SavUtils::ReadBits(this->Offs + 0x14 + (Idx / 2), (Idx % 2 == 0));
	};
	void NDSPainting::Pixel(const uint16_t Idx, const uint8_t V) {
		if (Idx >= 0x600 || V > 0xF) return;

		SavUtils::WriteBits(this->Offs + 0x14 + (Idx / 2), (Idx % 2 == 0), V);
	};

	/* Same as above, but instead of an raw index, it is being done with an X and Y Position. */
	uint8_t NDSPainting::PixelPos(const uint8_t X, const uint8_t Y) const {
		if (X >= 32 || Y >= 32) return 0;

		return this->Pixel((Y * 32) + X);
	};
	void NDSPainting::PixelPos(const uint8_t X, const uint8_t Y, const uint8_t V) {
		if (X >= 32 || Y >= 32) return;
		
		this->Pixel((Y * 32) + X, V);
	};

	/* Get and Set the Painting Flag, used for the Painting "Rank". */
	uint8_t NDSPainting::Flag() const { return SavUtils::Read<uint8_t>(this->Offs + 0x314); };
	void NDSPainting::Flag(const uint8_t V) { SavUtils::Write<uint8_t>(this->Offs + 0x314, V); };

	/* Get and Set the Painting Palette. */
	uint8_t NDSPainting::Palette() const { return SavUtils::Read<uint8_t>(this->Offs + 0x315); };
	void NDSPainting::Palette(const uint8_t V) { SavUtils::Write<uint8_t>(this->Offs + 0x315, std::min<uint8_t>(0xF, V)); };

	/* Get the Rank name of the Painting. */
	std::string NDSPainting::RankName() const {
		if (this->Flag() >= 0x29) return Strings::NDSPaintingRankNames_EN[0]; // 0x29+ is out of scope. Only range 0x0 - 0x28 is valid.

		const uint8_t Category = 1 + (this->Flag() / 8);
		return (this->Flag() % 2 == 0 ? Strings::NDSPaintingRankNames_EN[0] : Strings::NDSPaintingRankNames_EN[std::min<uint8_t>(5, Category)]);
	};

	/* Update the Checksum of the Painting. */
	void NDSPainting::UpdateChecksum() {
		/* First: Main. */
		uint16_t Calced = Checksum::Calc(SavUtils::Sav->GetData(), (this->Offs + 0x10) / 2, (this->Offs + 0x400) / 2, { (this->Offs + 0x10) / 2 });
		uint16_t CurCHKS = SavUtils::Read<uint16_t>(this->Offs + 0x10);
		if (CurCHKS != Calced) SavUtils::Write<uint16_t>(this->Offs + 0x10, Calced);

		/* Then: Header. */
		Calced = Checksum::Calc(SavUtils::Sav->GetData(), (this->Offs) / 2, (this->Offs + 0x13) / 2, { (this->Offs + 0xE) / 2 });
		CurCHKS = SavUtils::Read<uint16_t>(this->Offs + 0xE);
		if (CurCHKS != Calced) SavUtils::Write<uint16_t>(this->Offs + 0xE, Calced);
	};
};