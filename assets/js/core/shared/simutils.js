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


/*
	Format a value with proper 0's.

	Value: The Value which to format to a string.
	Nums: The amount of minimum ZERO's for the string.

	Example output: 001.
*/
export function SimUtils_NumberFormat(Value, Nums) {
	let Result = Value.toString();
	/* Add 0 on the beginning. */
	while (Result.length < Nums) { Result = '0' + Result; };
	return Result;
};


/*
	Convert the Time into a 'XX:XX' string.

	Time: A Uint8Array of length 3, while 0 is Hour, 1 is Minute and 2 Seconds.
	AMPM: If using 12 Hour or 24 Hour mode.
	ShowSeconds: If showing seconds (which is normally not visible in game) or not.

	Example output: 23:59:59 / 11:59:59 PM.
*/
export function SimUtils_TimeString(Time, AMPM = false, ShowSeconds = false) {
	/* 24 Hour Handle. */
	if (!AMPM) return SimUtils_NumberFormat(Time[0x0], 2) + ':' + SimUtils_NumberFormat(Time[0x1], 2) + (ShowSeconds ? SimUtils_NumberFormat(Time[0x2], 2) : "");
	else { // 12 Hour handle.
		const IsPM = (Hour > 11);

		return SimUtils_NumberFormat((IsPM ? Time[0x0] - 12 : Time[0x0]), 2) + ':' + SimUtils_NumberFormat(Time[0x1], 2) + (ShowSeconds ? SimUtils_NumberFormat(Time[0x2], 2) : "") + (IsPM ? " PM" : " AM");
	}
};


/*
	Convert the Simoleons into an 'XXX.XXX$' string.

	Simoleons: The Simoleon amount to convert to a string.

	Example output: 999.999$.
*/
export function SimUtils_SimoleonFormat(Simoleons) {
	const SString = Simoleons.toString() + '§';

	/* Here we'll add the periods. */
	switch(SString.length - 1) {
		case 4:
		case 5:
		case 6:
			return (SString.substr(0, SString.length - 4) + '.' + SString.substr(SString.length - 4));

		case 7: // Technically, 7 Digits are possible too for the Sav, but that should never happen.
		case 8:
		case 9:
			return (SString.substr(0, SString.length - 7) + '.' + SString.substr(SString.length - 7, 3) + '.' + SString.substr(SString.length - 4));

		default:
			break;
	}

	return SString;
};


/*
	Convert the Ratings into an 'XXXX' string.

	Ratings: The Rating amount to convert to a string.

	Example output: 9.999.
*/
export function SimUtils_RatingFormat(Ratings) {
	const SRatings = Ratings.toString();

	if (SRatings.length == 4) return SRatings.substr(0, 1) + '.' + SRatings.substr(1);
	return SRatings;
};