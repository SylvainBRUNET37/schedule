#ifndef NEIGHBORHOOD_OPERATOR_H
#define NEIGHBORHOOD_OPERATOR_H

#include "../solution/Solution.hpp"
#include "../solution/Instance.hpp"

class NeighborhoodOperator
{
private:

public:
	// change the solution given in paramter
	void execute(Solution& solution, Instance& instance);
};

#endif