#include <algorithm>
#include <random>
#include <iostream>
#include <functional>

#include "../../headers/algorithm/OtherHeuristicAlgorithm.h"

/*****************************************************
*                 GLOBAL VERIFICATION                *
*****************************************************/

bool OtherHeuristicAlgorithm::isAvailableThisDay(unsigned int nurseId, unsigned int dayId)
{
	// Early exit if the nurse is on a day off
	if (validator.isOnDayOff(nurseId, dayId)) return false;  // High frequency

	// Early exit if at the end of consecutive days off
	if (!validator.isAtEndOfConsecutiveDayOff(nurseId, dayId)) return false;  // Medium frequency

	// Check if the day is a weekend and if the nurse can work this weekend
	if (validator.isWeekendDay(dayId) && validator.isAbleToWorkThisWeekend(nurseId)) return false; // Low to Medium frequency

	// Fait travailler si le nombre de jours minimum de travail consécutif n'est pas atteint
	//if (!validator.haveDoneMinConsecutiveWorkedDay(nurseId, dayId)) return true;

	// Check if at max consecutive worked days
	if (validator.isAtMaxConsecutiveWorkedDay(nurseId, dayId)) return false;  // Medium frequency

	return true;
}

bool OtherHeuristicAlgorithm::isAvailableForShift(unsigned int nurseId, unsigned int dayId, unsigned int shiftId)
{
	// Check if it's not the first day and if the nurse worked the previous day
	if (dayId != 0 && validator.isWorkingThisDay(nurseId, dayId - 1))
		if (validator.isSuccessionForbidden(shiftId, bestSolution.v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId - 1])) return false;  // Medium frequency

	// Check for the specific shift type's limits
	if (validator.isAtMaxWorkedShift(nurseId, shiftId)) return false;  // Low frequency, return true if not at max

	// Check if the nurse has reached the max worked time
	if (validator.isAtMaxWorkedTime(nurseId, shiftId)) return false;  // Medium frequency

	return true;
}
