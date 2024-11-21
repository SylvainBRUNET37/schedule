#include <algorithm>
#include <random>
#include <iostream>
#include <functional>

#include "../../headers/algorithm/MinHeuristicAlgorithm.h"
#include "../../headers/calculation/CompleteObjectiveCalculator.h"

/*****************************************************
*                 GLOBAL VERIFICATION                *
*****************************************************/

bool MinHeuristicAlgorithm::isAvailableThisDay(unsigned int nurseId, unsigned int dayId)
{
	// Early exit if the nurse is on a day off
	if (validator.isOnDayOff(nurseId, dayId)) return false;  // High frequency

	// Fait travailler si le nombre de jours minimum de travail consécutif n'est pas atteint
	if (!validator.haveDoneMinConsecutiveWorkedDay(nurseId, dayId)) return true;

	// Early exit if at the end of consecutive days off
	if (!validator.isAtEndOfConsecutiveDayOff(nurseId, dayId)) return false;  // Medium frequency

	// Check if the day is a weekend and if the nurse can work this weekend
	if (validator.isWeekendDay(dayId) && validator.isAbleToWorkThisWeekend(nurseId)) return false; // Low to Medium frequency

	// Check if at max consecutive worked days
	if (validator.isAtMaxConsecutiveWorkedDay(nurseId, dayId)) return false;  // Medium frequency

	return true;
}

bool MinHeuristicAlgorithm::isAvailableForShift(unsigned int nurseId, unsigned int dayId, unsigned int shiftId)
{
	// Check if it's not the first day and if the nurse worked the previous day
	if (dayId != 0 && validator.isWorkingThisDay(nurseId, dayId - 1))
		if (validator.isSuccessionForbidden(shiftId, bestSolution.v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId - 1])) return false;  // Medium frequency

	// Check for the specific shift type's limits
	if (validator.isAtMaxWorkedShift(nurseId, shiftId)) return false;  // Low frequency, return true if not at max

	return true;
}

/*****************************************************
*                  ALGORITHM PARTS                   *
*****************************************************/

Solution& MinHeuristicAlgorithm::run()
{
	unsigned int dayId = 0;
	unsigned int nbDay = instance.get_Nombre_Jour();

	random_device rd;
	mt19937 eng(rd());

	//shuffle(data.days.begin(), data.days.end(), eng);

	for (unsigned int dayId : data.days)
	{
		vector<unsigned int> availableNurses;

		// Insert available nurses
		for (unsigned int nurseId : data.nurses)
			if (isAvailableThisDay(nurseId, dayId))
				availableNurses.push_back(nurseId);

		shuffle(availableNurses.begin(), availableNurses.end(), eng);
		shuffle(data.shifts.begin(), data.shifts.end(), eng);

		// Allocate every nurse
		allocateDay(dayId, availableNurses);
	}

	CompleteObjectiveCalculator calculator;

	bestSolution.i_valeur_fonction_objectif = calculator.calculateObjectiveFunction(instance, bestSolution);

	return bestSolution;
}

void MinHeuristicAlgorithm::allocateDay(unsigned int dayId, vector<unsigned int>& availableNurses)
{
	unsigned int nbShift = instance.get_Nombre_Shift();

	for (auto nurseIterator = availableNurses.begin(); nurseIterator != availableNurses.end();)
	{
		unsigned int nurseId = *nurseIterator;
		bool shifted = false;

		for (unsigned int shiftId : data.shifts)
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

		if (!shifted)
			++nurseIterator; // Passer à l'infirmière suivante si aucune affectation n'a eu lieu

		if (availableNurses.empty())
			return; // Sortir si plus d'infirmières disponibles
	}
}

bool MinHeuristicAlgorithm::allocateShift(unsigned int nurseId, unsigned int dayId, unsigned int shiftId)
{
	// Check if the nurse is eligible to work on the specified day and shift
	if (isAvailableForShift(nurseId, dayId, shiftId))
	{
		// Assign the shift to the nurse in the best solution
		bestSolution.v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId] = shiftId; // Allocate shift to the nurse
		data.nbMinuteWorked[nurseId] += instance.get_Shift_Duree(shiftId); // Update the total minutes worked by the nurse

		// Decrement the remaining shifts for this nurse on the current shift
		if (data.maxShiftsPerType[nurseId][shiftId] > 0)
			--data.maxShiftsPerType[nurseId][shiftId];

		// Increment the number of weekend worked if it's a weekend day
		if (validator.isWeekendDay(dayId))
			data.nbWeekendWorked[nurseId] += 1;

		// Decrement the numeber of nurse needed for the shift and the day
		--data.missingNursePerShift[dayId][shiftId];
		--data.missingNursePerDay[dayId];

		return true; // Allocation was successful
	}

	return false; // Allocation failed due to eligibility
}
