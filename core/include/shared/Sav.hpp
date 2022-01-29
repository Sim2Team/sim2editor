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

#ifndef _SIM2EDITOR_CPP_CORE_SAV_HPP
#define _SIM2EDITOR_CPP_CORE_SAV_HPP

#include "CoreCommon.hpp"
#include "../gba/GBASettings.hpp"
#include "../gba/GBASlot.hpp"
#include "../nds/NDSPainting.hpp"
#include "../nds/NDSSlot.hpp"


namespace S2Core {
	class SAV {
	public:
		SAV(const std::string &SavFile);
		SAV(std::unique_ptr<uint8_t[]> &Data, const uint32_t Size);

		void ValidationCheck();
		bool SlotExist(const uint8_t Slot) const;
		void SetChangesMade(const bool V) { this->ChangesMade = V; };
		void Finish();

		/* GBA Core returns. */
		std::unique_ptr<GBASlot> _GBASlot(const uint8_t Slot) const;
		std::unique_ptr<GBASettings> _GBASettings() const;

		/* NDS Core returns. */
		std::unique_ptr<NDSSlot> _NDSSlot(const uint8_t Slot) const;
		std::unique_ptr<NDSPainting> _NDSPainting(const uint8_t Idx) const;

		/* Some basic returns. */
		uint32_t GetSize() const { return this->SavSize; };
		uint8_t *GetData() const { return this->SavData.get(); };
		SavType GetType() const { return this->SType; };
		bool GetChangesMade() const { return this->ChangesMade; };
		bool GetValid() const { return this->SavValid; };
		std::string GetPath() const { return this->SavPath; };

		/* NDS returns. */
		NDSSavRegion GetRegion() const { return this->Region; };
	private:
		/* Some basic vars. */
		std::unique_ptr<uint8_t[]> SavData = nullptr;
		uint32_t SavSize = 0;
		bool SavValid = false, ChangesMade = false;
		std::string SavPath = "";

		/* Savtype & NDS Region. */
		SavType SType = SavType::_NONE;
		NDSSavRegion Region = NDSSavRegion::Unknown;

		/* NDS only Related things. */
		int8_t NDSSlots[3] = { -1, -1, -1 };
		int8_t InitNDSSlotIdxs(const uint8_t SavSlot, const uint8_t Reg);

		/* Identifiers to check for Savetypes. */
		static constexpr uint8_t GBAIdent[0x8] = { 0x53, 0x54, 0x57, 0x4E, 0x30, 0x32, 0x34, 0x0 };
		static constexpr uint8_t NDSIdent[0x8] = { 0x64, 0x61, 0x74, 0x0, 0x1F, 0x0, 0x0, 0x0 };
	};
};

#endif