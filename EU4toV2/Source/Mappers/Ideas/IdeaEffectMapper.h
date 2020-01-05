#ifndef IDEA_EFFECT_MAPPER_H
#define IDEA_EFFECT_MAPPER_H

#include "newParser.h"
#include <map>
#include <set>
#include <string>

namespace mappers
{

class IdeaEffectMapper: commonItems::parser
{
	public:
		IdeaEffectMapper();
		IdeaEffectMapper(std::istream& theStream);

		std::string getEnforceFromIdea(const std::string& ideaName, int ideaLevel) const;

		int getArmyFromIdea(const std::string& ideaName, int ideaLevel) const;
		int getCommerceFromIdea(const std::string& ideaName, int ideaLevel) const;
		int getCultureFromIdea(const std::string& ideaName, int ideaLevel) const;
		int getIndustryFromIdea(const std::string& ideaName, int ideaLevel) const;
		int getNavyFromIdea(const std::string& ideaName, int ideaLevel) const;

		int getSlaveryFromIdea(const std::string& ideaName, int ideaLevel) const;
		int getUpper_house_compositionFromIdea(const std::string& ideaName, int ideaLevel) const;
		int getVote_franchiseFromIdea(const std::string& ideaName, int ideaLevel) const;
		int getVoting_systemFromIdea(const std::string& ideaName, int ideaLevel) const;
		int getPublic_meetingsFromIdea(const std::string& ideaName, int ideaLevel) const;
		int getPress_rightsFromIdea(const std::string& ideaName, int ideaLevel) const;
		int getTrade_unionsFromIdea(const std::string& ideaName, int ideaLevel) const;
		int getPolitical_partiesFromIdea(const std::string& ideaName, int ideaLevel) const;

		int getLibertyFromIdea(const std::string& ideaName, int ideaLevel) const;
		int getEqualityFromIdea(const std::string& ideaName, int ideaLevel) const;
		int getOrderFromIdea(const std::string& ideaName, int ideaLevel) const;
		int getLiteracyFromIdea(const std::string& ideaName, int ideaLevel) const;

		int getReactionaryFromIdea(const std::string& ideaName, int ideaLevel) const;
		int getLiberalFromIdea(const std::string& ideaName, int ideaLevel) const;

		void registerKeys();

	private:
		std::map<std::string, std::string> enforceIdeas;

		std::map<std::string, int> armyIdeas;
		std::map<std::string, int> commerceIdeas;
		std::map<std::string, int> cultureIdeas;
		std::map<std::string, int> industryIdeas;
		std::map<std::string, int> navyIdeas;

		std::map<std::string, int> libertyIdeas;
		std::map<std::string, int> equalityIdeas;
		std::map<std::string, int> orderIdeas;
		std::map<std::string, int> literacyIdeas;

		std::map<std::string, int> slaveryIdeas;
		std::map<std::string, int> upper_house_compositionIdeas;
		std::map<std::string, int> vote_franchiseIdeas;
		std::map<std::string, int> voting_systemIdeas;
		std::map<std::string, int> public_meetingsIdeas;
		std::map<std::string, int> press_rightsIdeas;
		std::map<std::string, int> trade_unionsIdeas;
		std::map<std::string, int> political_partiesIdeas;

		std::map<std::string, int> reactionaryIdeas;
		std::map<std::string, int> liberalIdeas;

};

}



#endif // IDEA_EFFECT_MAPPER_H
