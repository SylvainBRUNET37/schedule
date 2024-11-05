#ifndef TOURNAMENT_STRATEGY_H
#define TOURNAMENT_STRATEGY_H

#include "SelectionStrategy.h"

class TournamentSelection : public SelectionStrategy
{
private:

public:
	TournamentSelection() {}

	Solution& execute(Solution& solution1, Solution& solution2) override;
};

#endif
