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

#ifndef _SIM2EDITOR_CPP_CORE_GBA_HOUSE_ITEM_HPP
#define _SIM2EDITOR_CPP_CORE_GBA_HOUSE_ITEM_HPP

#include "../shared/CoreCommon.hpp"


/*
	NOTE:
		Items from your Inventory and the ones from your House have different structures, hence it's a separate class.
		Also the House Items are annoying handled as well.
		Each item of the room changes the offsets to + 0x6 for data after 0xD6 of the SavSlot.
*/
namespace S2Core {
	enum class GBAHouseItemDirection : uint8_t { Right = 0x1, Down = 0x3, Left = 0x5, Up = 0x7, Invalid = 0xFF };

	class GBAHouseItem {
	public:
		GBAHouseItem(const uint32_t Offset)
			: Offs(Offset) { };

		uint8_t Count() const;
		void Count(const uint8_t V);

		uint8_t ID(const uint8_t Index) const;
		void ID(const uint8_t Index, const uint8_t V);

		/* Flag and Use count. */
		uint8_t Flag(const uint8_t Index) const;
		void Flag(const uint8_t Index, const uint8_t V);
		uint8_t UseCount(const uint8_t Index) const;
		void UseCount(const uint8_t Index, const uint8_t V);

		/* Positions. */
		uint8_t XPos(const uint8_t Index) const;
		void XPos(const uint8_t Index, const uint8_t V);
		uint8_t YPos(const uint8_t Index) const;
		void YPos(const uint8_t Index, const uint8_t V);

		GBAHouseItemDirection Direction(const uint8_t Index) const;
		void Direction(const uint8_t Index, const GBAHouseItemDirection V);

		/* Add and Remove. */
		bool AddItem(const uint8_t ID, const uint8_t Flag, const uint8_t UseCount, const uint8_t XPos, const uint8_t YPos, const GBAHouseItemDirection Direction);
		bool RemoveItem(const uint8_t Index);
	private:
		uint32_t Offs = 0;
	};
};

#endif