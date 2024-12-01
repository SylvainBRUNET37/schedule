#ifndef REPAIR_STRATEGY_H
#define REPAIR_STRATEGY_H

#include "../solution/Solution.hpp"
#include "../validator/SolutionValidator.h"	

/*
 * repair a solution line by line so that it comply with 2 constraints
 * repair the line i of the solution for constraints : total duration for individual and minimum shifts consecutive
 * 
*/
class Reparator
{
private:
	const unsigned int DAYS_IN_WEEK = 7; ///< Number of days in a week.

public:
	void executeMaxTimeWorkedRepair(Solution& solution, Instance& instance);

	int nbMinWorked(Solution& solution, Instance& instance, int nurseId);

	/**
	 * @brief Checks if the given day is either a Saturday or Sunday.
	 *
	 * @param dayId The day of the week represented as an integer.
	 *
	 * @return true If `dayId` is a Saturday or Sunday.
	 * @return false If `dayId` is neither.
	 *
	 * This function determines if the specified day, represented by the integer `dayId`,
	 * corresponds to a Saturday or Sunday based on the defined sequences:
	 * - Saturdays: 5, 12, 19, 26, ...
	 * - Sundays: 6, 13, 20, 27, ...
	 */
	bool isWeekendDay(int dayId) const
	{
		return (dayId >= 5 && (dayId + 2) % DAYS_IN_WEEK == 0) ||
			(dayId >= 6 && (dayId + 1) % DAYS_IN_WEEK == 0);
	}

	void executeMinConsecutiveDayRepair(Solution& solution, Instance& instance, unsigned int nurseId);

	void executeRandomMinConsecutiveDayRepair(Solution& solution, Instance& instance);

	void executeTotalMinConsecutiveDayRepair(Solution& solution, Instance& instance);
};

#endif