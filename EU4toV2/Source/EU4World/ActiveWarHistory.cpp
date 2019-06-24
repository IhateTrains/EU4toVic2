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



#include "ActiveWarHistory.h"
#include "WarDateItem.h"
#include "WarDateItems.h"
#include "Provinces/DateItems.h"
#include "../Configuration.h"
#include "Log.h"
#include "ParserHelpers.h"



const date STARTING_DATE("1444.11.11");
const date ENDING_DATE("1821.1.3");
const date FUTURE_DATE("2000.1.1");



EU4::ActiveWarHistory::ActiveWarHistory(std::istream& theStream)
{
	LOG(LogLevel::Error) << "blabla reading war history"; // debug
	
	registerKeyword(std::regex("\\d+\\.\\d+\\.\\d+"), [this](const std::string& dateString, std::istream& theStream) { // unfinished and unneded
		WarDateItems theItems(dateString, theStream);
		for (WarDateItem item : theItems.getItems())
		{
			if (item.getType() == WarDateItemType::ADD_ATTACKER)
			{
				LOG(LogLevel::Error) << "ADD_ATTACKER";// debug
			}
			else if (item.getType() == WarDateItemType::ADD_DEFENDER)
			{
				LOG(LogLevel::Error) << "ADD_DEFENDER";// debug
			}
			else if (item.getType() == WarDateItemType::REMOVE_ATTACKER)
			{
				LOG(LogLevel::Error) << "REMOVE_ATTACKER";// debug
			}
			else if (item.getType() == WarDateItemType::REMOVE_DEFENDER)
			{
				LOG(LogLevel::Error) << "REMOVE_DEFENDER";// debug
			}
		}
	});
	
	registerKeyword(std::regex("[a-zA-Z0-9_]+"), commonItems::ignoreItem);

	parseStream(theStream);
}