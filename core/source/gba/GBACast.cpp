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

#include "GBACast.hpp"
#include "../shared/SavUtils.hpp"


namespace S2Core {
	/* Get and Set Friendly Conversation level. */
	uint8_t GBACast::Friendly() const { return SavUtils::Read<uint8_t>(this->Offs); };
	void GBACast::Friendly(const uint8_t V) { SavUtils::Write<uint8_t>(this->Offs, std::min<uint8_t>(3, V)); };

	/* Get and Set Romance Conversation level. */
	uint8_t GBACast::Romance() const { return SavUtils::Read<uint8_t>(this->Offs + 0x1); };
	void GBACast::Romance(const uint8_t V) { SavUtils::Write<uint8_t>(this->Offs + 0x1, std::min<uint8_t>(3, V)); };

	/* Get and Set Intimidate Conversation level. */
	uint8_t GBACast::Intimidate() const { return SavUtils::Read<uint8_t>(this->Offs + 0x2); };
	void GBACast::Intimidate(const uint8_t V) { SavUtils::Write<uint8_t>(this->Offs + 0x2, std::min<uint8_t>(3, V)); };

	/* Get and Set Cast Feeling. */
	GBACastFeeling GBACast::Feeling() const { return (GBACastFeeling)SavUtils::Read<uint8_t>(this->Offs + 0x3); };
	void GBACast::Feeling(const GBACastFeeling V) { SavUtils::Write<uint8_t>(this->Offs + 0x3, (uint8_t)V); };

	/* Get and Set the hours how long the feeling lasts. */
	uint8_t GBACast::FeelingEffectHours() const { return SavUtils::Read<uint8_t>(this->Offs + 0x6); };
	void GBACast::FeelingEffectHours(const uint8_t V) { SavUtils::Write<uint8_t>(this->Offs + 0x6, V); };

	/* Get and Set registered on phone state. */
	bool GBACast::RegisteredOnPhone() const { return SavUtils::Read<uint8_t>(this->Offs + 0x7); };
	void GBACast::RegisteredOnPhone(const bool V) { SavUtils::Write<uint8_t>(this->Offs + 0x7, V); };

	/* Get and Set Secret Unlock state. */
	bool GBACast::Secret() const { return SavUtils::Read<uint8_t>(this->Offs + 0x8); };
	void GBACast::Secret(const bool V) { SavUtils::Write<uint8_t>(this->Offs + 0x8, V); };
};