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

#ifndef _SIM2EDITOR_CPP_CORE_NDS_PAINTING_HPP
#define _SIM2EDITOR_CPP_CORE_NDS_PAINTING_HPP

#include "../shared/CoreCommon.hpp"


namespace S2Core {
	class NDSPainting {
	public:
		NDSPainting(const uint8_t Idx)
			: Offs(0x5000 + (Idx * 0x400)) { };

		bool Valid() const;

		uint32_t Index() const;
		void Index(const uint32_t V);
		uint8_t Slot() const;
		void Slot(const uint8_t V);
		uint8_t CanvasIdx() const;
		void CanvasIdx(const uint8_t V);

		uint8_t Pixel(const uint16_t Idx) const;
		void Pixel(const uint16_t Idx, const uint8_t V);
		uint8_t PixelPos(const uint8_t X, const uint8_t Y) const;
		void PixelPos(const uint8_t X, const uint8_t Y, const uint8_t V);

		uint8_t Flag() const;
		void Flag(const uint8_t V);
		uint8_t Palette() const;
		void Palette(const uint8_t V);

		std::string RankName() const;
		void UpdateChecksum();
	private:
		uint32_t Offs = 0;
		static constexpr uint8_t Identifier[0x5] = { 0x70, 0x74, 0x67, 0x0, 0xF };
	};
};

#endif