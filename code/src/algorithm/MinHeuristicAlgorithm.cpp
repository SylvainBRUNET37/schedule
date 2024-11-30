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
	// Early exit if the nurse is on a day off
	if (validator.isOnDayOff(nurseId, dayId)) return false;  // High frequency

	// Early exit if at the end of consecutive days off
	if (!validator.isAtEndOfConsecutiveDayOff(nurseId, dayId)) return false;  // Medium frequency

	// Check if the day is a weekend and if the nurse can work this weekend
	if (validator.isWeekendDay(dayId) && validator.isAbleToWorkThisWeekend(nurseId)) return false; // Low to Medium frequency

	// Check min worked days
	if (dayId != 0 && !validator.isWorkingThisDay(nurseId, dayId - 1))
	{
		unsigned int nbDay = instance.get_Nombre_Jour();
		unsigned int minConsecutiveWorkedDay = instance.get_Personne_Nbre_Shift_Consecutif_Min(nurseId);
		unsigned int endDay = dayId + minConsecutiveWorkedDay;

		// Restrict the end day to the last day of the schedule
		if (endDay >= nbDay)
			endDay = nbDay - 1;

		for (unsigned int nextDay = dayId; nextDay < endDay; ++nextDay)
		{
			if (validator.isOnDayOff(nurseId, nextDay) || (validator.isWeekendDay(nextDay) && validator.isAbleToWorkThisWeekend(nurseId)))
				return false;
		}
	}

	// Check if at max consecutive worked days
	if (validator.isAtMaxConsecutiveWorkedDay(nurseId, dayId)) return false;  // Medium frequency

	return true;
}

bool MinHeuristicAlgorithm::isAvailableForShift(unsigned int nurseId, unsigned int dayId, unsigned int shiftId)
{
	if (dayId != 0 && validator.isWorkingThisDay(nurseId, dayId - 1))
	{
		if (validator.isSuccessionForbidden(shiftId, bestSolution.v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId - 1]) 
			&& !validator.haveDoneMinConsecutiveWorkedDay(nurseId, dayId))
		{
			for (unsigned int testShiftId : data.shifts)
			{
				if (!validator.isAtMaxWorkedShift(nurseId, testShiftId))
				{
					if (!validator.isSuccessionForbidden(shiftId, testShiftId))
					{
						++data.maxShiftsPerType[nurseId][bestSolution.v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId]];
						bestSolution.v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId - 1] = testShiftId;
						--data.maxShiftsPerType[nurseId][testShiftId];
						break;
					}
				}
			}
		}

		if (validator.isSuccessionForbidden(shiftId, bestSolution.v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId - 1]))
			return false;
	}

	// Check for the specific shift type's limits
	if (validator.isAtMaxWorkedShift(nurseId, shiftId)) return false;	

	return true;
}
