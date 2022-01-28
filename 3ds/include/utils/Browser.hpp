/*
*   This file is part of Sim2Editor
*   Copyright (C) 2020-2022 Universal-Team, Sim2Team
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

#ifndef _SIM2EDITOR_BROWSER_HPP
#define _SIM2EDITOR_BROWSER_HPP

#include <string>
#include <vector>

/* Browser Types. */
enum class BrowserType {
	File, // For File Selection.
	List // For Vector of Strings as an example.
};

/* Directory Struct. */
struct DirEntry {
	std::string Name;
	std::string Path;
	bool IsDirectory;
};

class Browser {
public:
	Browser(const std::string &Path, const std::vector<std::string> &Extensions);
	Browser(const std::vector<std::string> &List);

	/* Actions. */
	void Up();
	void Down();
	void Right(const int Amount);
	void Left(const int Amount);
	bool OpenHandle();
	bool CanDirBack();
	void GoDirBack();
	void GoDirUp();
	bool SetSelection(const int Selection);

	/* Getters. */
	std::vector<std::string> GetList() { return (this->Type == BrowserType::File ? this->GetFileList() : this->ListEntries); };
	int GetSelectedIndex() const { return this->Selected; };
	std::string GetSelectedName() const { return (this->Type == BrowserType::File ? this->DirEntries[this->Selected].Name : this->ListEntries[this->Selected]); };
	std::string GetSelectedPath() const { return (this->Type == BrowserType::File ? (this->GetPath() + this->DirEntries[this->Selected].Name) : ""); };
	bool GetRefresh() const { return this->Refresh; };
	bool GetEmpty() const { return (this->Type == BrowserType::File ? this->DirEntries.empty() : this->ListEntries.empty()); };
	std::string GetPath() const;
private:
	int Selected = 0;
	bool Refresh = false;
	BrowserType Type = BrowserType::File;
	std::vector<DirEntry> DirEntries = { }; // Only used in File mode.
	std::vector<std::string> ListEntries = { }; // Only used in List mode.
	std::vector<std::string> ExtensionList; // Well, the Extensions for File mode.

	bool NameEndsWith(const std::string &Name, const std::vector<std::string> &ExtensionList);
	void FetchDirectoryEntries(const std::vector<std::string> &ExtList = { });
	std::vector<std::string> GetFileList();
};

#endif