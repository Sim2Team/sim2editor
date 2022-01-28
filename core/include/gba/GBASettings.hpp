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

#ifndef _SIM2EDITOR_CPP_CORE_GBA_SETTINGS_HPP
#define _SIM2EDITOR_CPP_CORE_GBA_SETTINGS_HPP

#include "../shared/CoreCommon.hpp"


namespace S2Core {
	/* GBA Languages. */
	enum class GBALanguage : uint8_t {
		EN, // English
		NL, // Nederlands
		FR, // Français
		DE, // Deutsch
		IT, // Italiano
		ES  // Español
	};

	class GBASettings {
	public:
		GBASettings() { };

		/* Volume Levels. */
		uint8_t SFX() const;
		void SFX(const uint8_t V);
		uint8_t Music() const;
		void Music(const uint8_t V);

		GBALanguage Language() const;
		void Language(const GBALanguage V);

		void UpdateChecksum();
	private:
		static constexpr uint8_t MusicLevels[11] = { 0x0, 0x19, 0x32, 0x4B, 0x64, 0x7D, 0x96, 0xAF, 0xC8, 0xE1, 0xFF };
		static constexpr uint8_t SFXLevels[11]   = { 0x0, 0x0C, 0x18, 0x24, 0x30, 0x3C, 0x48, 0x54, 0x60, 0x6C, 0x80 };
	};
};

#endif