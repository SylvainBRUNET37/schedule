#include <algorithm>
#include <random>
#include <iostream>
#include <functional>

#include "../../headers/algorithm/OtherHeuristicAlgorithm.h"
#include "../../headers/calculation/ObjectiveCalculator.h"
#include "../../headers/neighborhood/neighborhoodOperator.h"

/*****************************************************
*                 GLOBAL VERIFICATION                *
*****************************************************/

bool OtherHeuristicAlgorithm::isAvailableThisDay(unsigned int nurseId, unsigned int dayId)
{
	// Early exit if the nurse is on a day off
	if (validator.isOnDayOff(nurseId, dayId)) return false;

	if (dayId != 0 && dayId < instance.get_Nombre_Jour() - 1)
		if (validator.isOnDayOff(nurseId, dayId + 1) && !validator.isWorkingThisDay(nurseId, dayId - 1)) return false;

	// Early exit if at the end of consecutive days off
	if (!validator.isAtEndOfConsecutiveDayOff(nurseId, dayId)) return false;

	// Check if the day is a weekend and if the nurse can work this weekend
	if (validator.isWeekendDay(dayId) && !validator.isAbleToWorkThisWeekend(nurseId)) return false;

	// If the previous day is saturday and the nurse wasn't working this saturday, do not work this sunday
	if (dayId != 0 && ((dayId - 1) % 7) == 5 && !validator.isWorkingThisDay(nurseId, dayId - 1))
		return false;

	// Fait travailler si le nombre de jours minimum de travail consécutif n'est pas atteint
	//if (!validator.haveDoneMinConsecutiveWorkedDay(nurseId, dayId)) return true;

	// Check if at max consecutive worked days
	if (validator.isAtMaxConsecutiveWorkedDay(nurseId, dayId)) return false;

	return true;
}

bool OtherHeuristicAlgorithm::isAvailableForShift(unsigned int nurseId, unsigned int dayId, unsigned int shiftId)
{
	// Check if it's not the first day and if the nurse worked the previous day
	if (dayId != 0 && validator.isWorkingThisDay(nurseId, dayId - 1))
		if (validator.isSuccessionForbidden(shiftId, bestSolution.v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId - 1])) return false;  // Medium frequency

	// Check for the specific shift type's limits
	if (validator.isAtMaxWorkedShift(nurseId, shiftId)) return false;

	// Check if the nurse has reached the max worked time
	if (validator.isAtMaxWorkedTime(nurseId, shiftId)) return false;

	return true;
}

Solution& OtherHeuristicAlgorithm::run()
{
	unsigned int dayId = 0;
	unsigned int nbDay = instance.get_Nombre_Jour();

	random_device rd;
	mt19937 eng(rd());

	for (unsigned int dayId : data.days)
	{
		vector<unsigned int> availableNurses;

		// Insert available nurses
		for (unsigned int nurseId : data.nurses)
		{
			// Increment the number of weekend worked if the nurse worked past weekend
			if (validator.isMonday(dayId))
			{
				if (validator.isWorkingThisDay(nurseId, dayId - 1) || validator.isWorkingThisDay(nurseId, dayId - 2))
					++(data.nbWeekendWorked[nurseId]);
			}

			if (isAvailableThisDay(nurseId, dayId))
				availableNurses.push_back(nurseId);
		}

		shuffle(availableNurses.begin(), availableNurses.end(), eng);

		// Allocate every nurse
		allocateDay(dayId, availableNurses);
	}

	NeighborhoodOperator neighborhoodOperator;
	neighborhoodOperator.executeTotalMinConsecutiveDayRepair(bestSolution, instance);

	ObjectiveCalculator calculator;

	bestSolution.i_valeur_fonction_objectif = calculator.calculateWeightedObjectiveFunction(instance, bestSolution);

	return bestSolution;
}
