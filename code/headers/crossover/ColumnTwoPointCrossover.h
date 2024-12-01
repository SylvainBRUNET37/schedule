#ifndef COLUMN_TWO_POINT_CROSSOVER_H
#define COLUMN_TWO_POINT_CROSSOVER_H

#include "CrossoverStrategy.h"

/**
 * @class ColumnTwoPointCrossover
 * @brief A crossover strategy that performs two-point crossover on columns.
 *
 * This class implements the two-point crossover operator on columns of the
 * solutions. It selects two points in the parents' solutions, exchanges the
 * segments between these points, and generates two child solutions.
 */
class ColumnTwoPointCrossover : public CrossoverStrategy
{
private:

public:
   /**
     * @brief Executes the two-point crossover operation between two parent solutions.
     *
     * This method performs the two-point crossover by selecting two points in the
     * columns of the parent solutions, exchanging the segments between the points,
     * and generating two child solutions.
     *
     * @param firstChild Pointer to the first child solution.
     * @param secondChild Pointer to the second child solution.
     */
	void execute(Solution* firstChild, Solution* secondChild) override;
};

#endif
