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



#ifndef V2WAR_H_
#define V2WAR_H_



#include "../Configuration.h"
#include "../EU4World/World.h"
#include "../EU4World/EU4Country.h"
#include "../Mappers/ProvinceMappings/ProvinceMapper.h"

class V2War
{
	public:
		V2War(string _filename);
		void output() const;

		void addAttacker(string);
		void addDefender(string);

		void				clearAttackers() { attackers.clear(); }
		void				clearDefenders() { defenders.clear(); }
		void				setName(string _name)						{ name = _name; }
		void				setController(string _controller)						{ controller = _controller; }

		const EU4::ActiveWar*	getSrcProvince()		const { return srcProvince; }
		string					getController()				const { return controller; }
		int						getNum()					const { return num; }
		string					getName()				const { return name; }

	private:

		const EU4::ActiveWar*		srcProvince;

		string						filename;
		int							num;
		string						name;
		string						controller;
		vector<string>				attackers;
		vector<string>				defenders;
};



#endif // V2WAR_H_