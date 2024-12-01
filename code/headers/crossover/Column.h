#ifndef COLUMN_H
#define COLUMN_H

#include "../../headers/solution/Solution.hpp"
#include "CrossoverStrategy.h"
/**
 * @class Column
 * @brief A crossover strategy that operates on columns of the solutions.
 *
 * This class implements the crossover strategy where the operation
 * is performed specifically on the columns of the given solutions.
 */
class Column : public CrossoverStrategy
{
public:
 /**
   * @brief Executes the column-based crossover between two solutions.
   *
   * This method performs the crossover operation on the columns of
   * the given child solutions to create new offspring.
   *
   * @param firstChild Pointer to the first child solution.
   * @param secondChild Pointer to the second child solution.
   */
	void execute(Solution* firstChild, Solution* secondChild) override;
	virtual ~Column() = default;
};

#endif
