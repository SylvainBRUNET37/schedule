#ifndef LINE_TWO_POINT_CROSSOVER_H
#define LINE_TWO_POINT_CROSSOVER_H

#include "CrossoverStrategy.h"
/**
 * @class LineTwoPointCrossover
 * @brief A crossover strategy that performs two-point crossover on the lines of solutions.
 *
 * This class implements the two-point crossover strategy, where two crossover points
 * are chosen on the solutions' lines, and the segments between those points are exchanged
 * between the two parent solutions to create two child solutions.
 */
class LineTwoPointCrossover : public CrossoverStrategy
{
private:

public:
    /**
    * @brief Executes the two-point crossover operation on the parent solutions.
    *
    * This method performs the two-point crossover by selecting two points in the
    * lines of the parent solutions, exchanging the segments between those points,
    * and generating two child solutions.
    *
    * @param firstChild Pointer to the first child solution.
    * @param secondChild Pointer to the second child solution.
    */
	void execute(Solution* firstChild, Solution* secondChild) override;
};

#endif
