#pragma once
#include "../../headers/solution/Solution.hpp"
#include "../../headers/validator/SolutionValidator.h"
#include "CrossoverStrategy.h"

/*
 * This crossover strategy takes 2 parents and create 2 childs
 * The operator looks at each individual in the solution and takes the one that violates the fewest constraints. 
 * If the two violate the same number of constraints it's random between them
 * First child is composed with all the best repaired individuals
 * Second child is made with all the bad ones
 */

class BestLine : public CrossoverStrategy
{
public: 
	BestLine(Instance* instance) : validator(instance) {

	}
	void execute(Solution* firstChild, Solution* secondChild) override;
	~BestLine();

private :
	SolutionValidator validator;
	void swapLines(Solution* firstChild, Solution* secondChild, int index);
};

