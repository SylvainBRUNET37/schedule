#ifndef LINE_H
#define LINE_H

#include "../../headers/solution/Solution.hpp"
#include "CrossoverStrategy.h"

/**
 * @class Line
 * @brief A crossover strategy that operates on the lines of the solutions.
 *
 * This class implements the crossover operator that focuses on the lines
 * of the parent solutions. The operator selects and combines parts of
 * the parents' solutions to create two child solutions.
 */
class Line : public CrossoverStrategy
{
private:

public :
  /**
    * @brief Executes the line-based crossover between two parent solutions.
    *
    * This method applies the crossover operator on the lines of the parent
    * solutions to generate two child solutions.
    *
    * @param firstChild Pointer to the first child solution.
    * @param secondChild Pointer to the second child solution.
    */
	void execute(Solution* firstChild, Solution* secondChild) override;
};

#endif
