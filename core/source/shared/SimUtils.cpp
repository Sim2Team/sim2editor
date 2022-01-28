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

#include "SimUtils.hpp"
#include "../Strings.hpp"


namespace S2Core {
	/*
		Returns the current time as a 24 Hr or 12 Hr string.

		const uint16_t Time: The current time as an uint16_t.
		const bool AMPM: If using AM / PM or 24 Hours.

		This Results in: '13:44' or '01:44 PM'.
	*/
	const std::string SimUtils::TimeString(const uint16_t Time, const bool AMPM) {
		char TimeBuffer[(AMPM ? 11 : 8)];
		const uint8_t Minute = (uint8_t)(Time >> 8), Hour = (uint8_t)Time;

		if (AMPM) {
			snprintf(TimeBuffer, sizeof(TimeBuffer), "%02d:%02d %s", (Hour > 11 ? Hour - 12 : Hour), Minute, (Hour > 11 ? "PM" : "AM"));

		} else {
			snprintf(TimeBuffer, sizeof(TimeBuffer), "%02d:%02d", Hour, Minute);
		}

		return TimeBuffer;
	};


	/*
		Returns the current Simoleon amount as a string.

		const uint32_t Simoleons: The current Simoleons.

		This results in 123.456$.
	*/
	const std::string SimUtils::SimoleonsString(const uint32_t Simoleons) {
		std::string SString = std::to_string(Simoleons);

		/* Here we'll add the periods. */
		switch(SString.size()) {
			case 4:
			case 5:
			case 6:
				SString.insert(SString.end() - 3, '.');
				break;

			case 7: // Technically, 7 Digits are possible too for the Sav, but that should never happen.
			case 8:
			case 9:
				SString.insert(SString.end() - 6, '.');
				SString.insert(SString.end() - 3, '.');
				break;

			default:
				break;
		}

		SString += "§"; // Simoleons sign.
		return SString;
	};


	/*
		Returns the current Ratings as a string.

		const uint16_t Ratings: The current Ratings.

		This results in 1.345.
	*/
	const std::string SimUtils::RatingString(const uint16_t Ratings) {
		std::string RString = std::to_string(Ratings);

		/* That's how it's handled in The Sims 2 GBA. If there are more THAN 3 digits, a '.' is being added. */
		if (RString.size() > 3) RString.insert(RString.end() - 3, '.');
		return RString;
	};


	/*
		Return the Name from an GBA Item.

		const uint8_t ID: The Item's ID.
	*/
	const std::string SimUtils::GBAItemName(const uint8_t ID) { return Strings::GBAItemNames_EN[ID]; };
};