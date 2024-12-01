#include <algorithm>
#include <random>
#include <iostream>
#include <functional>

#include "../../headers/algorithm/MinHeuristicAlgorithm.h"

/*****************************************************
*                 GLOBAL VERIFICATION                *
*****************************************************/

bool MinHeuristicAlgorithm::isAvailableThisDay(unsigned int nurseId, unsigned int dayId)
{
	// Return false if the nurse is on a day off
	if (validator.isOnDayOff(nurseId, dayId)) return false;

	// Return false if at the end of consecutive days off
	if (!validator.isAtEndOfConsecutiveDayOff(nurseId, dayId)) return false;

	// Return false if the day is a weekend and if the nurse cannot work this weekend
	if (validator.isWeekendDay(dayId) && !validator.isAbleToWorkThisWeekend(nurseId)) return false; // Low to Medium frequency

	// If the previous day is saturday and the nurse wasn't working this saturday, do not work this sunday
	if (dayId != 0 && ((dayId - 1) % 7) == 5 && !validator.isWorkingThisDay(nurseId, dayId - 1))
		return false;	

	// Avoid the non respect of min worked days
	if (dayId != 0 && !validator.isWorkingThisDay(nurseId, dayId - 1))
	{
		unsigned int nbDay = instance.get_Nombre_Jour();
		unsigned int minConsecutiveWorkedDay = instance.get_Personne_Nbre_Shift_Consecutif_Min(nurseId);
		unsigned int endDay = dayId + minConsecutiveWorkedDay;

		// Restrict the end day to the last day of the schedule
		if (endDay >= nbDay)
			endDay = nbDay;

		// Check future days to respect the min worked days
		for (unsigned int nextDay = dayId; nextDay < endDay; ++nextDay)
			if (validator.isOnDayOff(nurseId, nextDay) || (validator.isWeekendDay(nextDay) && !validator.isAbleToWorkThisWeekend(nurseId)))
				return false;
	}

	// Check if at max consecutive worked days
	if (validator.isAtMaxConsecutiveWorkedDay(nurseId, dayId)) return false;  // Medium frequency

	return true;
}

bool MinHeuristicAlgorithm::isAvailableForShift(unsigned int nurseId, unsigned int dayId, unsigned int shiftId)
{
	// Check if the nurse was working the previous day
	if (dayId != 0 && validator.isWorkingThisDay(nurseId, dayId - 1))
	{
		// If the succession is forbidden and the nurse hasn't done the minimum consecutive worked days, try to repair
		if (validator.isSuccessionForbidden(shiftId, bestSolution.v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId - 1]) 
			&& !validator.haveDoneMinConsecutiveWorkedDay(nurseId, dayId))
		{
			// Loop through the shifts to find a valid one for the previous day
			for (unsigned int testShiftId : data.shifts)
			{
				// If the shift is not forbidden and the nurse can work it, change the previous day's shift
				if (!validator.isAtMaxWorkedShift(nurseId, testShiftId))
				{
					if (!validator.isSuccessionForbidden(shiftId, testShiftId))
					{
						// Change the previous day's shift and update the number of worked shifts
						++data.maxShiftsPerType[nurseId][bestSolution.v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId - 1]];
						bestSolution.v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId - 1] = testShiftId;
						--data.maxShiftsPerType[nurseId][testShiftId];
						break;
					}
				}
			}
		}

		// If the succession is forbidden (or still forbidden even after trying to repair), return false
		if (validator.isSuccessionForbidden(shiftId, bestSolution.v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId - 1]))
			return false;
	}

	// Check for the specific shift type's limits
	if (validator.isAtMaxWorkedShift(nurseId, shiftId)) return false;	

	return true;
}
