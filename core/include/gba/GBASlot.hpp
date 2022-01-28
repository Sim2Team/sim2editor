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

#ifndef _SIM2EDITOR_CPP_CORE_GBA_SLOT_HPP
#define _SIM2EDITOR_CPP_CORE_GBA_SLOT_HPP

#include "GBACast.hpp"
#include "GBAEpisode.hpp"
#include "GBAHouse.hpp"
#include "GBAItem.hpp"
#include "GBAMinigame.hpp"
#include "GBASocialMove.hpp"
#include "../shared/CoreCommon.hpp"


namespace S2Core {
	class GBASlot {
	public:
		GBASlot(const uint8_t Slot)
			: Slot(Slot), Offs(Slot * 0x1000) { };

		/* Main things. */
		uint16_t Time() const;
		void Time(const uint16_t V);
		uint32_t Simoleons() const;
		void Simoleons(const uint32_t V);
		uint16_t Ratings() const;
		void Ratings(const uint16_t V);
		std::string Name() const;
		void Name(const std::string &V);

		/* Appearance. */
		uint8_t Hairstyle() const;
		void Hairstyle(const uint8_t V);
		uint8_t Shirtcolor3() const;
		void Shirtcolor3(const uint8_t V);
		uint8_t Tan() const;
		void Tan(const uint8_t V);
		uint8_t Shirtcolor2() const;
		void Shirtcolor2(const uint8_t V);
		uint8_t Haircolor() const;
		void Haircolor(const uint8_t V);
		uint8_t Hatcolor() const;
		void Hatcolor(const uint8_t V);
		uint8_t Shirt() const;
		void Shirt(const uint8_t V);
		uint8_t Shirtcolor1() const;
		void Shirtcolor1(const uint8_t V);
		uint8_t Pants() const;
		void Pants(const uint8_t V);
		uint8_t Pantscolor() const;
		void Pantscolor(const uint8_t V);

		/* Skill Points. */
		uint8_t Confidence() const;
		void Confidence(const uint8_t V);
		uint8_t Mechanical() const;
		void Mechanical(const uint8_t V);
		uint8_t Strength() const;
		void Strength(const uint8_t V);
		uint8_t Personality() const;
		void Personality(const uint8_t V);
		uint8_t Hotness() const;
		void Hotness(const uint8_t V);
		uint8_t Intellect() const;
		void Intellect(const uint8_t V);
		uint8_t Sanity() const;
		void Sanity(const uint8_t V);
		uint8_t Aspiration() const;
		void Aspiration(const uint8_t V);

		/* Items. */
		std::unique_ptr<GBAItem> PawnShop() const;
		std::unique_ptr<GBAItem> Saloon() const;
		std::unique_ptr<GBAItem> Skills() const;
		std::unique_ptr<GBAItem> Mailbox() const;
		std::unique_ptr<GBAItem> Inventory() const;

		/* House data. */
		std::unique_ptr<GBAHouse> House() const;

		/* Collectables Amount. */
		uint8_t Cans() const;
		void Cans(const uint8_t V);
		uint8_t Cowbells() const;
		void Cowbells(const uint8_t V);
		uint8_t Spaceship() const;
		void Spaceship(const uint8_t V);
		uint8_t Fuelrods() const;
		void Fuelrods(const uint8_t V);

		/* Collectables Price. */
		uint8_t CansPrice() const;
		void CansPrice(const uint8_t V);
		uint8_t CowbellsPrice() const;
		void CowbellsPrice(const uint8_t v);
		uint8_t SpaceshipPrice() const;
		void SpaceshipPrice(const uint8_t V);
		uint8_t FuelrodsPrice() const;
		void FuelrodsPrice(const uint8_t V);

		/* Episode stuff. */
		uint8_t CurrentEpisode() const;
		void CurrentEpisode(const uint8_t V, const bool ValidCheck = true);

		/* Minigames. */
		std::unique_ptr<GBAMinigame> Minigame(const uint8_t Game);

		/* Plot Points stuff. */
		bool MysteryPlot() const;
		void MysteryPlot(const bool V);
		bool FriendlyPlot() const;
		void FriendlyPlot(const bool V);
		bool RomanticPlot() const;
		void RomanticPlot(const bool V);
		bool IntimidatingPlot() const;
		void IntimidatingPlot(const bool V);
		bool TheChopperPlot() const;
		void TheChopperPlot(const bool V);
		bool WeirdnessPlot() const;
		void WeirdnessPlot(const bool V);

		uint8_t TheChopperColor() const;
		void TheChopperColor(const uint8_t V);

		/* Some class pointers. */
		std::unique_ptr<GBAEpisode> Episode(const uint8_t EP) const;
		std::unique_ptr<GBASocialMove> SocialMove(const uint8_t Move) const;
		std::unique_ptr<GBACast> Cast(const uint8_t CST) const;

		bool FixChecksum();
	private:
		uint8_t Slot = 0;
		uint32_t Offs = 0;

		uint32_t Offset(const uint32_t DefaultOffs = 0x0) const;

		/* This contains all official Episode Values found at offset (Slot * 0x1000) + 0x1A9. */
		static constexpr uint8_t EPVals[12] = {
			0x0, 0x1, 0x3, 0x7, // Tutorial + Season 1.
			0x6, 0xA, 0x8, 0xF, // Season 2.
			0xD, 0x5, 0x16, 0x15 // Season 3.
		};
	};
};

#endif