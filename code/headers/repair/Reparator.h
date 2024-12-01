#ifndef REPAIR_STRATEGY_H
#define REPAIR_STRATEGY_H

#include "../solution/Solution.hpp"
#include "../validator/SolutionValidator.h"	

/**
 * @class Reparator
 * @brief A class responsible for repairing scheduling solutions to comply with constraints.
 *
 * This class provides methods to repair scheduling solutions line by line in order to meet two primary constraints:
 * - The total duration worked by individual nurses.
 * - The minimum number of consecutive shifts a nurse can work.
 *
 * The class offers several repair methods, including max time worked and consecutive shift repairs, which modify the solution
 * according to the specified constraints.
 */
class Reparator
{
private:
    const unsigned int DAYS_IN_WEEK = 7; ///< Number of days in a week.

public:
    /**
     * @brief Repairs the solution to ensure no nurse exceeds the maximum total time worked.
     *
     * This method checks if any nurse exceeds their allowed maximum working time, and if so, repairs the schedule
     * to adhere to the limit.
     *
     * @param solution The current solution to be repaired.
     * @param instance The instance containing the relevant data, such as the time constraints.
     */
    void executeMaxTimeWorkedRepair(Solution& solution, Instance& instance);

    /**
     * @brief Calculates the total minutes worked by a nurse.
     *
     * This function computes the total minutes worked by the specified nurse within the given solution.
     *
     * @param solution The current solution.
     * @param instance The instance containing time data.
     * @param nurseId The ID of the nurse whose worked time is to be calculated.
     *
     * @return The total minutes worked by the nurse.
     */
    int nbMinWorked(Solution& solution, Instance& instance, int nurseId);

    /**
     * @brief Checks if the given day is a weekend (Saturday or Sunday).
     *
     * This method checks if the day represented by `dayId` corresponds to a weekend, either Saturday or Sunday.
     *
     * @param dayId The day of the week, represented as an integer.
     *
     * @return true If `dayId` is a Saturday or Sunday.
     * @return false If `dayId` is neither Saturday nor Sunday.
     *
     * The weekend days are determined as follows:
     * - Saturdays: days with IDs 5, 12, 19, 26, ...
     * - Sundays: days with IDs 6, 13, 20, 27, ...
     */
    bool isWeekendDay(int dayId) const
    {
        return (dayId >= 5 && (dayId + 2) % DAYS_IN_WEEK == 0) ||
            (dayId >= 6 && (dayId + 1) % DAYS_IN_WEEK == 0);
    }

    /**
     * @brief Repairs the given nurse assignement.
     *
     * @param solution The current solution to be repaired.
     * @param instance The instance containing the relevant constraints.
     * @param nurseId The ID of the nurse whose consecutive shift assignments will be repaired.
     */
    void executeMinConsecutiveDayRepair(Solution& solution, Instance& instance, unsigned int nurseId);

    /**
     * @brief Repairs a random nurse assignement.
     *
     * @param solution The current solution to be repaired.
     * @param instance The instance containing the relevant constraints.
     */
    void executeRandomMinConsecutiveDayRepair(Solution& solution, Instance& instance);

    /**
     * @brief Repairs the solution to ensure nurses do not work too few consecutive days.
     *
     * @param solution The current solution to be repaired.
     * @param instance The instance containing the relevant constraints.
     */
    void executeTotalMinConsecutiveDayRepair(Solution& solution, Instance& instance);
};

#endif
