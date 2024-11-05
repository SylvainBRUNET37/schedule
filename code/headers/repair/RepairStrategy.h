#ifndef REPAIR_STRATEGY_H
#define REPAIR_STRATEGY_H

#include "../solution/Solution.hpp"

class RepairStrategy
{
private:

public:
	RepairStrategy() {}

	virtual void execute(Solution& solution) = 0;
};

#endif