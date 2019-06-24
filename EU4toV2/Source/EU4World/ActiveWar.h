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



#ifndef ACTIVEWAR_H_
#define ACTIVEWAR_H_



#include "Date.h"
#include "ActiveWarHistory.h"
#include "newParser.h"
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <set>


// based on EU4Province


namespace EU4
{


class ActiveWar: commonItems::parser
{
	public:
		ActiveWar(const std::string& numString, std::istream& theStream);

		//void addCore(const std::string& tag) { cores.insert(tag); }
		//void removeCore(const std::string& tag) { cores.erase(tag); }

		double getCulturePercent(const std::string& culture) const;

		//int getNum() const { return num; }
		std::string getName() const { return name; }
		std::string getControllerString() const { return controllerString; }
		std::set<std::string> getAttackers() const { return attackers; }
		std::set<std::string> getDefenders() const { return defenders; }

	private:

		std::string	name;
		std::string controllerString;
		std::set<std::string> attackers;
		std::set<std::string> defenders;

		std::unique_ptr<EU4::ActiveWarHistory> activeWarHistory;
};

}



#endif // ACTIVEWAR_H_
