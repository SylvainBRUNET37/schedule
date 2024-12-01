#ifndef SWAP_SHIFT_MUTATION_H
#define SWAP_SHIFT_MUTATION_H

#include "MutationStrategy.h"

/**
 * @brief Implements a mutation strategy that swaps shifts within a nurse's schedule.
 *
 * The `SwapShiftMutation` class performs a mutation by randomly selecting a nurse's schedule
 * and rotating shifts between two randomly chosen points to introduce variability.
 */
class SwapShiftMutation : public MutationStrategy
{
private:

public:
    /**
     * @brief Executes a swap shift mutation on a nurse's schedule.
     *
     * @param solution A reference to the current solution containing schedules for all nurses.
     *
     * This mutation modifies the schedule of a randomly selected nurse by rotating
     * the shifts between two randomly chosen crossover points.
     */
    void execute(Solution& solution) override;
};

#endif
