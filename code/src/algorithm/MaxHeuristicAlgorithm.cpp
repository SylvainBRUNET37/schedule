#include <algorithm>
#include <random>
#include <iostream>
#include <functional>

#include "../../headers/algorithm/MaxHeuristicAlgorithm.h"
#include "../../headers/calculation/ObjectiveCalculator.h"
#include "../../headers/repair/Reparator.h"

/*****************************************************
*                 GLOBAL VERIFICATION                *
*****************************************************/

bool MaxHeuristicAlgorithm::isAvailableThisDay(unsigned int nurseId, unsigned int dayId)
{
	// Return false if the nurse is on a day off
	if (validator.isOnDayOff(nurseId, dayId)) return false;

	// Return false if ????????????
	if (dayId != 0 && dayId < instance.get_Nombre_Jour() - 1)
		if (validator.isOnDayOff(nurseId, dayId + 1) && !validator.isWorkingThisDay(nurseId, dayId - 1)) return false;

	// Return false if at the end of consecutive days off
	if (!validator.isAtEndOfConsecutiveDayOff(nurseId, dayId)) return false;

	// Return false if the day is a weekend and if the nurse cannot work this weekend
	if (validator.isWeekendDay(dayId) && !validator.isAbleToWorkThisWeekend(nurseId)) return false;

	// Return false if the previous day is saturday and the nurse wasn't working this saturday, do not work this sunday
	if (dayId != 0 && ((dayId - 1) % 7) == 5 && !validator.isWorkingThisDay(nurseId, dayId - 1))
		return false;

	// Return false if at max consecutive worked days
	if (validator.isAtMaxConsecutiveWorkedDay(nurseId, dayId)) return false;

	return true;
}

bool MaxHeuristicAlgorithm::isAvailableForShift(unsigned int nurseId, unsigned int dayId, unsigned int shiftId)
{
	// Return false if the shift succession is forbidden
	if (dayId != 0 && validator.isWorkingThisDay(nurseId, dayId - 1))
		if (validator.isSuccessionForbidden(shiftId, bestSolution.v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId - 1])) return false;  // Medium frequency

	// Return false if the nurse is at the specific shift type's limits
	if (validator.isAtMaxWorkedShift(nurseId, shiftId)) return false;

	// Return false if the nurse has reached the max worked time
	if (validator.isAtMaxWorkedTime(nurseId, shiftId)) return false;

	return true;
}

/*****************************************************
*                  ALGORITHM PARTS                   *
*****************************************************/

Solution& MaxHeuristicAlgorithm::run()
{
	// Intialize random device and engine
	random_device rd;
	mt19937 eng(rd());

	// Loop on each day
	for (unsigned int dayId : data.days)
	{
		vector<unsigned int> availableNurses;

		// Insert available nurses
		for (unsigned int nurseId : data.nurses)
		{
			// If it's the first day of the week, check if the nurse worked past weekend
			if (validator.isMonday(dayId))
			{
				// Increment the number of weekend worked if the nurse worked past weekend
				if (validator.isWorkingThisDay(nurseId, dayId - 1) || validator.isWorkingThisDay(nurseId, dayId - 2))
					++(data.nbWeekendWorked[nurseId]);
			}

			// Add to the list of available nurses available nurses
			if (isAvailableThisDay(nurseId, dayId))
				availableNurses.push_back(nurseId);
		}

		// Shuffle the list of available nurses to add randomness
		shuffle(availableNurses.begin(), availableNurses.end(), eng);

		// Allocate every nurse
		allocateDay(dayId, availableNurses);
	}

	// Repair the solution for the minimum worked consecutive days constraint
	Reparator reparator;
	reparator.executeTotalMinConsecutiveDayRepair(bestSolution, instance);

	// Calculate the weighted objective function value of the best solution and return the solution
	ObjectiveCalculator calculator;
	bestSolution.i_valeur_fonction_objectif = calculator.calculateWeightedObjectiveFunction(instance, bestSolution);
	return bestSolution;
}
