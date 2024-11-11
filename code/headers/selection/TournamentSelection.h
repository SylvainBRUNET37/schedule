#ifndef TOURNAMENT_STRATEGY_H
#define TOURNAMENT_STRATEGY_H

#include "SelectionStrategy.h"

class TournamentSelection : public SelectionStrategy
{
private:

public:
	TournamentSelection() {}

	/**
	 * @brief Executes a tournament selection between two solutions.
	 *
	 * Compares the objective function values of two solutions and selects
	 * the one with the higher or equal objective value as the "better" solution.
	 *
	 * @param solution1 The first solution to compare.
	 * @param solution2 The second solution to compare.
	 *
	 * @return Solution& A reference to the selected solution with the greater or equal objective function value.
	 *
	 * If `solution1` has an objective value greater than or equal to that of `solution2`,
	 * `solution1` is returned. Otherwise, `solution2` is returned.
	 */
	Solution& execute(Solution& solution1, Solution& solution2) override;
};

#endif
