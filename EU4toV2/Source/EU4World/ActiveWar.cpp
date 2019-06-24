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
		LOG(LogLevel::Error) << warNameString.getString();
	});
	
	
	registerKeyword(std::regex("history"), [this](const std::string& unused, std::istream& theStream) { // currently unused data
		activeWarHistory = std::make_unique<ActiveWarHistory>(theStream);
	});
	
	
	registerKeyword(std::regex("attackers"), [this](const std::string& unused, std::istream& theStream) {
		commonItems::stringList attackersStrings(theStream);
		LOG(LogLevel::Error) << "Reading attackers";// debug
		for (auto attackerString : attackersStrings.getStrings())
		{
			attackers.insert(attackerString);
		}
	});
	registerKeyword(std::regex("defenders"), [this](const std::string& unused, std::istream& theStream) {
		commonItems::stringList defendersStrings(theStream);
		LOG(LogLevel::Error) << "Reading defenders";// debug
		for (auto defenderString : defendersStrings.getStrings())
		{
			defenders.insert(defenderString);
		}
	});
	registerKeyword(std::regex("stalled_years"), [this](const std::string& unused, std::istream& theStream) {

		commonItems::singleString stalledyearsvalue(theStream); // unused, just for debug
		LOG(LogLevel::Error) << "stalled_years is read";// debug
	});
	
	registerKeyword(std::regex("[a-zA-Z0-9_]+"), commonItems::ignoreItem);
	//registerKeyword(std::regex("\\d+\\.\\d+\\.\\d+"), commonItems::ignoreItem);

	parseStream(theStream);
}