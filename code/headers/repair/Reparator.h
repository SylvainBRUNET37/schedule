#ifndef REPAIR_STRATEGY_H
#define REPAIR_STRATEGY_H

#include "../solution/Solution.hpp"
#include "../validator/SolutionValidator.h"	

/*
 * repair a solution line by line so that it comply with 2 constraints
 * repair the line i of the solution for constraints : total duration for individual and minimum shifts consecutive
 * 
*/
class Reparator
{
private:
	SolutionValidator solutionValidator;
	Instance* instance;
public:
	Reparator(Instance* instance) : instance(instance), solutionValidator(instance) {};
	

	void execute(Solution& solution, Instance& instance);

	int nbMinWorked(Solution& solution, Instance& instance, int nurseId);

	void executeMinConsecutiveDayRepair(Solution& solution, Instance& instance, unsigned int nurseId);

	void executeRandomMinConsecutiveDayRepair(Solution& solution, Instance& instance);

	void executeTotalMinConsecutiveDayRepair(Solution& solution, Instance& instance);
};

#endif