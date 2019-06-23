/*Copyright(c) 2019 The Paradox Game Converters Project

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE. */



#include "ActiveWar.h"
#include "Log.h"
#include "ParserHelpers.h"
#include "../Configuration.h"
#include <algorithm>
#include <fstream>
#include <optional>
#include <sstream>



EU4::ActiveWar::ActiveWar(const std::string& unused, std::istream& theStream)
{
	registerKeyword(std::regex("name"), [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString warNameString(theStream);
		//[&]WarName = warNameString.getString();
	});
	registerKeyword(std::regex("history"), [this](const std::string& unused, std::istream& theStream) {
		activeWarHistory = std::make_unique<ActiveWarHistory>(theStream);
	});
	registerKeyword(std::regex("history"), [this](const std::string& unused, std::istream& theStream) {
		registerKeyword(std::regex("\\d+\\.\\d+\\.\\d+"), [this](const std::string& dateString, std::istream& theStream) {
			//[&]WarDate = dateString.getString();
			registerKeyword(std::regex("add_attacker"), [this](const std::string& unused, std::istream & theStream) {
				commonItems::singleString attackerEU4TagString(theStream);
				std::string attackerEU4Tag = attackerEU4TagString.getString();
				std::string attackerEU4TagWithoutQuotes = attackerEU4Tag.substr(1, attackerEU4Tag.size() - 1);
				//if (FirstAttackerTag == "")
				//{
				//	FirstAttackerTag = attackerEU4TagWithoutQuotes;
				//}
			});
			registerKeyword(std::regex("add_defender"), [this](const std::string& unused, std::istream & theStream) {
				commonItems::singleString defenderEU4TagString(theStream);
				std::string defenderEU4Tag = defenderEU4TagString.getString();
				std::string defenderEU4TagWithoutQuotes = defenderEU4Tag.substr(1, defenderEU4Tag.size() - 1);
				//if (FirstDefenderTag == "")
				//{
					///FirstDefenderTag = defenderEU4TagWithoutQuotes;
					///[&](FirstDefenderTag) { defenderEU4TagWithoutQuotes = FirstDefenderTag; }(99);
				//}
			});
		});
	});
	/*
	registerKeyword(std::regex("cores"), [this](const std::string& unused, std::istream& theStream) {
		commonItems::stringList coresStrings(theStream);
		for (auto coreString : coresStrings.getStrings())
		{
			cores.insert(coreString);
		}
	});
	*/
	
	registerKeyword(std::regex("[a-zA-Z0-9_]+"), commonItems::ignoreItem);

	parseStream(theStream);
}