#include <algorithm>
#include <random>
#include <iostream>
#include <functional>

#include "../../headers/algorithm/OtherHeuristicAlgorithm.h"
#include "../../headers/calculation/CompleteObjectiveCalculator.h"

/*****************************************************
*                 GLOBAL VERIFICATION                *
*****************************************************/

bool OtherHeuristicAlgorithm::isAvailableThisDay(unsigned int nurseId, unsigned int dayId)
{
	// Early exit if the nurse is on a day off
	if (validator.isOnDayOff(nurseId, dayId)) return false;

	// Early exit if at the end of consecutive days off
	if (!validator.isAtEndOfConsecutiveDayOff(nurseId, dayId)) return false;

	// Check if the day is a weekend and if the nurse can work this weekend
	if (validator.isWeekendDay(dayId) && !validator.isAbleToWorkThisWeekend(nurseId)) return false;

	// Check if at max consecutive worked days
	if (validator.isAtMaxConsecutiveWorkedDay(nurseId, dayId)) return false;

	// If the previous day is saturday and the nurse wasn't working this saturday, do not work this sunday
	if (dayId != 0 && ((dayId - 1) % 7) == 5 && !validator.isWorkingThisDay(nurseId, dayId - 1))
		return false;

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
	if (validator.isAtMaxWorkedTime(nurseId, shiftId)) return false;

	return true;
}


/////////////////////////////////////////

void OtherHeuristicAlgorithm::allocateDay(unsigned int dayId, vector<unsigned int>& availableNurses)
{
	random_device rd;
	mt19937 eng(rd());
	unsigned int nbShift = instance.get_Nombre_Shift();

	for (auto nurseIterator = availableNurses.begin(); nurseIterator != availableNurses.end();)
	{
		unsigned int nurseId = *nurseIterator;
		bool shifted = false;

		shuffle(data.shifts.begin(), data.shifts.end(), eng);

		for (unsigned int shiftId : data.shifts)
		{
			if (data.missingNursePerShift[dayId][shiftId] > 0)
			{
				if (allocateShift(nurseId, dayId, shiftId))
				{
					// Affectation réussie, marquer comme décalée
					shifted = true;
					// Supprimer l'infirmière de l'ensemble
					nurseIterator = availableNurses.erase(nurseIterator); // Supprimer et obtenir le nouvel itérateur
					break; // Sortir de la boucle de shifts
				}
			}
		}

		if (!shifted)
			++nurseIterator; // Passer à l'infirmière suivante si aucune affectation n'a eu lieu

		if (availableNurses.empty())
			return; // Sortir si plus d'infirmières disponibles
	}
}