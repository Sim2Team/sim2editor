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

#include "SavUtils.hpp"
#include <ctime>
#include <unistd.h>


namespace S2Core {
	std::unique_ptr<SAV> SavUtils::Sav = nullptr;

	/*
		Load a SavFile.

		const std::string &File: Path to the SavFile.
		const std::string &BasePath: The base path where to create the Backups (Optional).
		const bool DoBackup: If creating a backup or not after loading the SavFile (Optional).

		Returns the SavType of the detected Save.
	*/
	SavType SavUtils::LoadSav(const std::string &File, const std::string &BasePath, const bool DoBackup) {
		SavUtils::Sav = std::make_unique<SAV>(File);

		if (SavUtils::Sav->GetType() != SavType::_NONE) {
			if (DoBackup && SavUtils::Sav->GetValid()) SavUtils::CreateBackup(BasePath); // Create Backup, if true.
		}

		return SavUtils::Sav->GetType();
	};


	/*
		Load a Sav from a raw buffer.

		std::unique_ptr<uint8_t[]> &Data: The Raw Save Buffer.
		const uint32_t Size: The Save Buffer Size.
		const std::string &BasePath: The base path where to create the Backups (Optional).
		const bool DoBackup: If creating a backup or not after loading the SavFile (Optional).

		Returns the SavType of the detected Save.
	*/
	SavType SavUtils::LoadSav(std::unique_ptr<uint8_t[]> &Data, const uint32_t Size, const std::string &BasePath, const bool DoBackup) {
		SavUtils::Sav = std::make_unique<SAV>(Data, Size);

		if (SavUtils::Sav->GetType() != SavType::_NONE) {
			if (DoBackup && SavUtils::Sav->GetValid()) SavUtils::CreateBackup(BasePath); // Create Backup, if true.
		}

		return SavUtils::Sav->GetType();
	};


	/*
		Create a Backup of the current loaded Sav.

		const std::string &BasePath: The base path where to create the Backups.

		Backup Format would be: 'Sims2-Year.Month.Day-Hour.Minute.Second.Sav'
	*/
	bool SavUtils::CreateBackup(const std::string &BasePath) {
		if (!SavUtils::Sav || !SavUtils::Sav->GetValid()) return false;

		std::string BackupPath = BasePath + "/Backups/"; // Base path.
		bool CreateIt = false;

		/* Fetch Time there. */
		time_t Rawtime;
		struct tm *TimeInfo;
		char TimeBuffer[80];
		time(&Rawtime);
		TimeInfo = localtime(&Rawtime);
		strftime(TimeBuffer, sizeof(TimeBuffer), "%Y.%m.%d-%H.%M.%S", TimeInfo); // Get the Time as String.

		switch(SavUtils::Sav->GetType()) {
			case SavType::_GBA:
				BackupPath += "GBA/Sims2-" + std::string(TimeBuffer) + ".Sav";
				CreateIt = true;
				break;

			case SavType::_NDS:
				BackupPath += "NDS/Sims2-" + std::string(TimeBuffer) + ".Sav";
				CreateIt = true;
				break;

			case SavType::_NONE:
				break;
		}

		if (CreateIt) {
			FILE *Out = fopen(BackupPath.c_str(), "w");

			if (Out) {
				fwrite(SavUtils::Sav->GetData(), 1, SavUtils::Sav->GetSize(), Out);
				fclose(Out);
			}
		}

		return CreateIt;
	};


	/*
		Finish Sav Editing and unload everything.

		const bool Reset: If resetting the Sav Pointer to nullptr after the action or not (True by Default).
	*/
	void SavUtils::Finish(const bool Reset) {
		if (!SavUtils::Sav || !SavUtils::Sav->GetValid() || SavUtils::Sav->GetPath() == "") return;

		/* Ensure that we made changes, otherwise writing is useless. */
		if (SavUtils::Sav->GetChangesMade()) {
			SavUtils::Sav->Finish(); // The Finish action.

			FILE *Out = fopen(SavUtils::Sav->GetPath().c_str(), "rb+");

			if (Out) {
				fwrite(SavUtils::Sav->GetData(), 1, SavUtils::Sav->GetSize(), Out);
				fclose(Out);
			}
		}

		if (Reset) SavUtils::Sav = nullptr;
	};


	/*
		Return, if changes are made.
	*/
	bool SavUtils::ChangesMade() {
		if (SavUtils::Sav && SavUtils::Sav->GetValid()) {
			switch(SavUtils::Sav->GetType()) {
				case SavType::_GBA:
				case SavType::_NDS:
					return SavUtils::Sav->GetChangesMade();

				case SavType::_NONE:
					return false;
			}
		}

		return false;
	};


	/*
		Read a bit from the SavData.

		const uint32_t Offs: The Offset where to read from.
		const uint8_t BitIndex: The bit index ( 0 - 7 ).
	*/
	const bool SavUtils::ReadBit(const uint32_t Offs, const uint8_t BitIndex) {
		if (!SavUtils::Sav || !SavUtils::Sav->GetValid() || BitIndex > 0x7) return false;

		return DataHelper::ReadBit(SavUtils::Sav->GetData(), Offs, BitIndex);
	};

	/*
		Write a bit to the SavData.

		const uint32_t Offs: The Offset where to write to.
		const uint8_t BitIndex: The bit index ( 0 - 7 ).
		const bool IsSet: If the bit is set (1) or not (0).
	*/
	void SavUtils::WriteBit(const uint32_t Offs, const uint8_t BitIndex, const bool IsSet) {
		if (!SavUtils::Sav || !SavUtils::Sav->GetValid() || BitIndex > 0x7) return;

		if (DataHelper::WriteBit(SavUtils::Sav->GetData(), Offs, BitIndex, IsSet)) {
			if (!SavUtils::Sav->GetChangesMade()) SavUtils::Sav->SetChangesMade(true);
		}
	};


	/*
		Read Lower / Upperbits from the SavBuffer.

		const uint32_t Offs: The Offset where to read from.
		const bool First: If reading from the first 4 bits, or the last 4.
	*/
	const uint8_t SavUtils::ReadBits(const uint32_t Offs, const bool First) {
		if (!SavUtils::Sav || !SavUtils::Sav->GetValid()) return 0;

		return DataHelper::ReadBits(SavUtils::Sav->GetData(), Offs, First);
	};

	/*
		Write Lower / Upperbits to the SavBuffer.

		const uint32_t Offs: The Offset where to write to.
		const bool First: If writing on the first 4 bits, or the last 4.
		const uint8_t Data: The Data to write.
	*/
	void SavUtils::WriteBits(const uint32_t Offs, const bool First, const uint8_t Data) {
		if (!SavUtils::Sav || !SavUtils::Sav->GetValid() || Data > 0xF) return;

		if (DataHelper::WriteBits(SavUtils::Sav->GetData(), Offs, First, Data)) {
			if (!SavUtils::Sav->GetChangesMade()) SavUtils::Sav->SetChangesMade(true);
		}
	};


	/*
		Read a string from the SavBuffer.

		const uint32_t Offs: The Offset from where to read from.
		const uint32_t Length: The Length to read.
	*/
	const std::string SavUtils::ReadString(const uint32_t Offs, const uint32_t Length) {
		if (!SavUtils::Sav || !SavUtils::Sav->GetValid()) return "";

		if (SavUtils::Sav->GetType() == SavType::_GBA || (SavUtils::Sav->GetType() == SavType::_NDS && SavUtils::Sav->GetRegion() == NDSSavRegion::Int)) return DataHelper::ReadString(SavUtils::Sav->GetData(), Offs, Length, true);
		else return ""; // For now only for DS Japanese.
	};
	
	/*
		Write a string to the SavBuffer.

		const uint32_t Offs: The offset from where to write to.
		const uint32_t Length: The length to write.
		const std::string &Str: The string to write.
	*/
	void SavUtils::WriteString(const uint32_t Offs, const uint32_t Length, const std::string &Str) {
		if (!SavUtils::Sav || !SavUtils::Sav->GetValid()) return;

		/* TODO: Japanese DS Handle. */
		if (SavUtils::Sav->GetType() == SavType::_GBA || (SavUtils::Sav->GetType() == SavType::_NDS && SavUtils::Sav->GetRegion() == NDSSavRegion::Int)) {
			if (DataHelper::WriteString(SavUtils::Sav->GetData(), Offs, Length, Str, true)) {
				if (!SavUtils::Sav->GetChangesMade()) SavUtils::Sav->SetChangesMade(true);
			}
		}
	};


	/*
		Return the detected Save Region from the Savefile.
	*/
	NDSSavRegion SavUtils::GetRegion() {
		if (!SavUtils::Sav || !SavUtils::Sav->GetValid()) return NDSSavRegion::Unknown;

		return SavUtils::Sav->GetRegion();
	};
};