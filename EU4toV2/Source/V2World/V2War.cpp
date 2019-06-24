/*Copyright (c) 2019 The Paradox Game Converters Project

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/



#include "V2War.h"
#include "CardinalToOrdinal.h"
#include "Log.h"
#include "Object.h"
#include "OSCompatibilityLayer.h"
#include "ParadoxParser8859_15.h"
#include "../EU4World/World.h"
#include "../EU4World/Provinces/EU4Province.h"
#include "../Mappers/ProvinceMappings/ProvinceMapper.h"
#include "V2Pop.h"
#include "V2Country.h"
#include "V2Factory.h"
#include <algorithm>
#include <fstream>
#include <memory>
#include <sstream>
#include <stdio.h>
using namespace std;



V2War::V2War(string _filename)
{
	srcProvince = NULL;
	filename = _filename;
	num = 0;
	name = "";
	//controller = ""; // disabled because string defaults to "" anyway
	//cores.clear();
	attackers.clear();
	defenders.clear();

	int slash = filename.find_last_of("/");
	int numDigits = filename.find_first_of("-") - slash - 2;
	string temp = filename.substr(slash + 1, numDigits);
	num = atoi(temp.c_str());

	shared_ptr<Object> obj;
	if (Utils::DoesFileExist(string("./blankMod/output/history/wars") + _filename))
	{
		obj = parser_8859_15::doParseFile((string("./blankMod/output/history/wars") + _filename).c_str());
		if (obj == NULL)
		{
			LOG(LogLevel::Error) << "Could not parse ./blankMod/output/history/wars" << _filename;
			exit(-1);
		}
	}
	else
	{
		obj = parser_8859_15::doParseFile((theConfiguration.getVic2Path() + "/history/wars" + _filename).c_str());
		if (obj == NULL)
		{
			LOG(LogLevel::Error) << "Could not parse " << theConfiguration.getVic2Path() << "/history/wars" << _filename;
			exit(-1);
		}
	}
	vector<shared_ptr<Object>> leaves = obj->getLeaves();
	for (vector<shared_ptr<Object>>::iterator itr = leaves.begin(); itr != leaves.end(); itr++)
	{
		if ((*itr)->getKey() == "controller")
		{
			controller = (*itr)->getLeaf().c_str();
		}
		//else if ((*itr)->getKey() == "add_core")
		//{
		//	cores.push_back((*itr)->getLeaf());
		//}
		else if ((*itr)->getKey() == "add_attacker")
		{
			attackers.push_back((*itr)->getLeaf());
		}
		else if ((*itr)->getKey() == "add_defender")
		{
			defenders.push_back((*itr)->getLeaf());
		}
		else
		{
			//log("Unknown key - %s\n", (*itr)->getKey().c_str());
		}
	}
}


void V2War::output() const
{
	int lastSlash = filename.find_last_of('/');
	std::string path = filename.substr(0, lastSlash);
	Utils::TryCreateFolder("Output/" + theConfiguration.getOutputName() + "/history/wars" + path);

	std::ofstream output("Output/" + theConfiguration.getOutputName() + "/history/wars" + filename);
	if (!output.is_open())
	{
		LOG(LogLevel::Error) << "Could not create war history file Output/" << theConfiguration.getOutputName() << "/history/wars/" << filename << " - " << Utils::GetLastErrorString();
		exit(-1);
	}
	output << "name=" << name << "\n";
	//output << "controller=" << controller << "\n";
	//for (auto core: cores)
	//{
	//	output << "add_core=" << core << "\n";
	//}
	for (auto attacker : attackers)
	{
		output << "add_attacker=" << attacker << "\n";
	}
	for (auto defender : defenders)
	{
		output << "add_defender=" << defender << "\n";
	}
	output << "\t\t" << "casus_belli = conquest\n"; // temporarily hardcoded, make mappings
	//output << "\t\t" << "actor = " << FirstAttackerTag << "\n";
	//output << "\t\t" << "receiver = " << FirstDefenderTag << "\n";
	output << "\t}\n";
	output.close();
}

void V2War::addAttacker(string newAttacker)
{
	// only add if unique
	if (find(attackers.begin(), attackers.end(), newAttacker) == attackers.end())
	{
		attackers.push_back(newAttacker);
	}
}
void V2War::addDefender(string newDefender)
{
	// only add if unique
	if (find(defenders.begin(), defenders.end(), newDefender) == defenders.end())
	{
		defenders.push_back(newDefender);
	}
}