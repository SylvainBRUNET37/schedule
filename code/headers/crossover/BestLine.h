#pragma once
#include "../../headers/solution/Solution.hpp"
#include "../../headers/validator/SolutionValidator.h"
#include "CrossoverStrategy.h"

/**
 * @class BestLine
 * @brief A crossover strategy that selects the best repaired individuals for two children.
 *
 * This strategy operates by evaluating each individual in the parent solutions
 * and selecting the one that violates the fewest constraints. If both individuals
 * violate the same number of constraints, the choice is made randomly.
 *
 * The crossover operation produces two child solutions:
 * - The first child is composed of the best repaired individuals.
 * - The second child is made up of the individuals with the most violations.
 */
class BestLine : public CrossoverStrategy
{
public: 
	BestLine(Instance* instance) : validator(instance) {

	}
 /**
   * @brief Executes the BestLine crossover between two parent solutions.
   *
   * This method performs the crossover by evaluating the parent solutions,
   * selecting individuals based on constraint violations, and constructing
   * two child solutions.
   *
   * @param firstChild Pointer to the first child solution.
   * @param secondChild Pointer to the second child solution.
   */
	void execute(Solution* firstChild, Solution* secondChild) override;
	~BestLine();

private :
	SolutionValidator validator;
 /**
   * @brief Swaps the lines between the two child solutions at a specific index.
   *
   * This helper function swaps the lines between the first and second child
   * solutions based on the given index.
   *
   * @param firstChild Pointer to the first child solution.
   * @param secondChild Pointer to the second child solution.
   * @param index The index of the line to swap.
   */
	void swapLines(Solution* firstChild, Solution* secondChild, int index);
};

