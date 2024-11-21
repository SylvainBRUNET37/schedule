#ifndef REPAIR_STRATEGY_H
#define REPAIR_STRATEGY_H

#include "../solution/Solution.hpp"
#include "../validator/SolutionValidator.h"

class RepairStrategy
{
private:
	SolutionValidator validator;
	Instance& instance;

public:
	RepairStrategy(Instance& instance) : validator(&instance), instance(instance) {}

	void execute(Solution& solution);
};

#endif