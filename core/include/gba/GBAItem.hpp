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

#ifndef _SIM2EDITOR_CPP_CORE_GBA_ITEM_HPP
#define _SIM2EDITOR_CPP_CORE_GBA_ITEM_HPP

#include "../shared/CoreCommon.hpp"


/*
	NOTE:
		Items from your Inventory and the one from your House have different structures, hence it's a separate class.

		The GBAItem class can be moreso seen as like a package of 6 Items.
		The Pawnshop, Saloon, Skillbook seller, Mailbox and the Inventory have 6 Item Slots.
		The first byte contains the Item Count, while the following things contain the item data.

		0xE6 is known as an Empty Item ID.
*/
namespace S2Core {
	class GBAItem {
	public:
		GBAItem(const uint32_t Offset)
			: Offs(Offset) { };

		uint8_t Count() const;
		void Count(const uint8_t V);

		uint8_t ID(const uint8_t Index) const;
		void ID(const uint8_t Index, const uint8_t V);

		/* Flag and Use count. */
		uint8_t Flag(const uint8_t Idx) const;
		void Flag(const uint8_t Idx, const uint8_t V);
		uint8_t UseCount(const uint8_t Idx) const;
		void UseCount(const uint8_t Idx, const uint8_t V);
	private:
		uint32_t Offs = 0;
	};
};

#endif