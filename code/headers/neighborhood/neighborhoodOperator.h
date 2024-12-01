#ifndef NEIGHBORHOOD_OPERATOR_H
#define NEIGHBORHOOD_OPERATOR_H

#include "../solution/Solution.hpp"
#include "../solution/Instance.hpp"

class NeighborhoodOperator
{
private:

public:
	// repair

	void executeMinConsecutiveDayRepair(Solution& solution, Instance& instance, unsigned int nurseId);

	void executeRandomMinConsecutiveDayRepair(Solution& solution, Instance& instance);

	void executeTotalMinConsecutiveDayRepair(Solution& solution, Instance& instance);
};

#endif