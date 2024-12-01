#pragma once
#include "../../headers/solution/Solution.hpp"
#include "../../headers/validator/SolutionValidator.h"
#include "CrossoverStrategy.h"

/**
 * @brief A crossover strategy to generate two children from two parents.
 *
 * This operator examines each individual in the solution and selects the one
 * that violates the fewest constraints. If both individuals violate the same
 * number of constraints, the choice is made randomly.
 *
 * After selection, the solution is repaired to comply with all constraints:
 * - The first child consists of all the best-repaired individuals.
 * - The second child consists of all the less optimal individuals.
 */
class BestLineReparator : public CrossoverStrategy
{
public: 
    /**
     * @brief Constructs a BestLineReparator with the given instance.
     *
     * Initializes the crossover strategy with an instance to validate the
     * solutions during the crossover process.
     *
     * @param instance Pointer to the instance used for solution validation.
     */
    BestLineReparator(Instance* instance) : validator(instance) {};
    /**
    * @brief Executes the best line crossover and repairs the resulting solutions.
    *
    * This method performs the crossover by selecting the best lines from the
    * parent solutions, repairing them to meet the problem's constraints,
    * and creating two child solutions.
    *
    * @param firstChild Pointer to the first child solution.
    * @param secondChild Pointer to the second child solution.
    */
	void execute(Solution* firstChild, Solution* secondChild) override;
	~BestLineReparator();

private :
	SolutionValidator validator;
};

