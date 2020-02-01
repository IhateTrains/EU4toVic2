#include "CultureMappingRule.h"
#include "ParserHelpers.h"
#include "../../EU4World/Regions/Regions.h"
#include "Log.h"

mappers::CultureMappingRule::CultureMappingRule(std::istream& theStream)
{
	registerKeyword("vic2", [this](const std::string& unused, std::istream& theStream) 
		{
			const commonItems::singleString v2Str(theStream);
			destinationCulture = v2Str.getString();
		});
	registerKeyword("region", [this](const std::string& unused, std::istream& theStream)
		{
			const commonItems::singleString regionStr(theStream);
			regions.insert(regionStr.getString());
		});
	registerKeyword("religion", [this](const std::string& unused, std::istream& theStream)
		{
			const commonItems::singleString religionStr(theStream);
			religions.insert(religionStr.getString());
		});
	registerKeyword("owner", [this](const std::string& unused, std::istream& theStream)
		{
			const commonItems::singleString ownerStr(theStream);
			owners.insert(ownerStr.getString());
		});
	registerKeyword("provinceid", [this](const std::string& unused, std::istream& theStream)
		{
			const commonItems::singleString provinceStr(theStream);
			try
			{
				provinces.insert(stoi(provinceStr.getString()));
			}
			catch (std::exception&)
			{
				Log(LogLevel::Warning) << "Invalid province ID in culture mapper: " << provinceStr.getString();
			}
		});
	registerKeyword("eu4", [this](const std::string& unused, std::istream& theStream)
		{
			const commonItems::singleString eu4Str(theStream);
			cultures.insert(eu4Str.getString());
		});
	registerRegex("[a-zA-Z0-9\\_.:]+", commonItems::ignoreItem);

	parseStream(theStream);
	clearRegisteredKeywords();
}

std::optional<std::string> mappers::CultureMappingRule::cultureMatch(
	const EU4::Regions& eu4Regions,
	const std::string& eu4culture,
	const std::string& eu4religion,
	int eu4Province,
	const std::string& eu4ownerTag
) const
{
	// We need at least a viable EU4culture.
	if (eu4culture.empty()) return std::nullopt;
		
	if (!cultures.count(eu4culture)) return std::nullopt;

	if (!eu4ownerTag.empty() && !owners.empty()) 
		if (!owners.count(eu4ownerTag)) return std::nullopt;

	if (!eu4religion.empty() && !religions.empty()) 
		if (!religions.count(eu4religion)) return std::nullopt;

	// This is a provinces check, not regions.
	if (eu4Province && !provinces.empty()) 
		if (!provinces.count(eu4Province)) return std::nullopt;

	// This is a regions check, that checks if a provided province is within that region.
	if (eu4Province && !regions.empty())
	{
		auto regionMatch = false;
		for (const auto& region: regions)
		{
			if (!eu4Regions.regionIsValid(region))
			{
				Log(LogLevel::Warning) << "Checking for culture " << eu4culture << " inside invalid region: " << region << "! Fix the mapping rules!";
				// We could say this was a match, and thus pretend this region entry doesn't exist, but it's better
				// for the converter to explode across the logs and scream all invalid names. So, continue.
				continue;
			}
			if (eu4Regions.provinceInRegion(eu4Province, region)) regionMatch = true;
		}
		if (!regionMatch) return std::nullopt;
	}
	return destinationCulture;
}