#ifndef CULTURE_MAPPER_H
#define CULTURE_MAPPER_H

#include "newParser.h"
#include "../../EU4World/Regions/Regions.h"
#include <optional>
#include <string>
#include <vector>
#include "CultureMappingRule.h"

namespace mappers
{
	class CultureMapper: commonItems::parser
	{
	public:
		CultureMapper() = default;
		explicit CultureMapper(std::istream& theStream);
		
		void loadFile(const std::string& fileName);

		[[nodiscard]] std::optional<std::string> cultureMatch(
			const EU4::Regions& eu4Regions,
			const std::string& eu4culture,
			const std::string& eu4religion,
			int eu4Province,
			const std::string& eu4ownerTag) const;

	private:
		void registerKeys();
		
		std::vector<CultureMappingRule> cultureMapRules;
	};
}

#endif // CULTURE_MAPPER_H