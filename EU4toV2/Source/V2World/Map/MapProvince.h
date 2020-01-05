#ifndef MAP_PROVINCE_H
#define MAP_PROVINCE_H

#include "newParser.h"
#include <set>

namespace mappers
{
	class MapProvince : commonItems::parser
	{
	public:
		MapProvince();
		std::set<int> getNavalProvinces() const { return navalProvinces; }

	private:
		std::set<int> navalProvinces;
	};
}

#endif // MAP_PROVINCE_H
