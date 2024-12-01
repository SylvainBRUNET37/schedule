#ifndef UNIFORM_CROSSOVER_H
#define UNIFORM_CROSSOVER_H

#include "CrossoverStrategy.h"

/**
 * @class UniformCrossover
 * @brief A crossover strategy that performs uniform crossover between two parent solutions.
 *
 * This class implements the uniform crossover strategy, where each element
 * in the child solutions is randomly selected from one of the two parent solutions.
 * The result is two child solutions that inherit characteristics from both parents.
 */
class UniformCrossover : public CrossoverStrategy
{
private:
	
public:
    /**
    * @brief Executes the uniform crossover operation between two parent solutions.
    *
    * This method performs the uniform crossover by selecting random elements
    * from the parents' solutions and assigning them to the corresponding positions
    * in the child solutions.
    *
    * @param firstChild Pointer to the first child solution.
    * @param secondChild Pointer to the second child solution.
    */
	void execute(Solution* firstChild, Solution* secondChild) override;
};

#endif
