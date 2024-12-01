#include "../../headers/repair/Reparator.h"

#include <random>
#include <algorithm>
#include <iostream>

/*****************************************************
*           REPARATION OF MAX WORKED TIME            *
*****************************************************/

void Reparator::executeMaxTimeWorkedRepair(Solution& solution, Instance& instance)
{
	unsigned int nbNurse = instance.get_Nombre_Personne();
	unsigned int nbDay = instance.get_Nombre_Jour();

	random_device rd;
	mt19937 eng(rd());
	uniform_int_distribution<int> dist(0, nbDay - 1);

	for (unsigned int nurseId = 0; nurseId < nbNurse; ++nurseId)
	{
		// Count nb worked days
		int nbMinuteWorked = nbMinWorked(solution, instance, nurseId);
		// Calculate the difference between the number of worked days and the maximum number of working day for the nurse
		int minuteWorkedDifference = nbMinuteWorked - instance.get_Personne_Duree_total_Max(nurseId);
		// Add days off until the maximum worked time condition is satisfied
		unsigned int dayId = 0;
		while (minuteWorkedDifference > 0)
		{
			// Generate a random day
			dayId = dist(eng);
	
			// Check days next to a weekend;
			if (isWeekendDay(dayId) && ((dayId - 1) >= 0 && (dayId + 1) < nbDay)) 
			{
				if (solution.v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId - 1] != -1)
					solution.v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId - 1] = -1;
				else if (solution.v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId + 1] != -1)
					solution.v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId + 1] = -1;
			}

			// Check if the nurse is working this day then navigate to the closest day off
			if (solution.v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId] != -1)
			{
				int i = 0;
				while ((dayId + i) < nbDay) 
				{
					if (solution.v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId + i] == -1) 
					{
						solution.v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId + i -1] = -1;
						break;
					}
					i++;
				}
			}

			// Update the number of worked days
			int currentMinWorked = nbMinWorked(solution, instance, nurseId);
			minuteWorkedDifference = currentMinWorked - instance.get_Personne_Duree_total_Max(nurseId);
		}
	}
}

/*****************************************************
*                      UTILS                         *
*****************************************************/

int Reparator::nbMinWorked(Solution& solution, Instance& instance, int nurseId) 
{
	unsigned int nbMinuteWorked = 0;
	unsigned int nbDay = instance.get_Nombre_Jour();

	// Count the number of worked days for the nurse
	for (unsigned int dayId = 0; dayId < nbDay; ++dayId)
		if (solution.v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId] != -1)
			nbMinuteWorked += instance.get_Shift_Duree(solution.v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId]);

	return nbMinuteWorked;
}

/*****************************************************
*         REPARATION OF MIN CONSECUTIVE DAY          *
*****************************************************/

void Reparator::executeMinConsecutiveDayRepair(Solution& solution, Instance& instance, unsigned int nurseId)
{
	// Get the number of columns and lines
	unsigned int nbNurse = solution.v_v_IdShift_Par_Personne_et_Jour.size();
	unsigned int nbDay = solution.v_v_IdShift_Par_Personne_et_Jour[0].size();

	// Get the nurse assignement
	vector<int>& nurseAssignement = solution.v_v_IdShift_Par_Personne_et_Jour[nurseId];

	// Loop over the days
	for (unsigned int dayId = 0; dayId < nbDay; ++dayId)
	{
		// Get the minimum number of worked days for the nurse
		unsigned int nbMinConsecutiveWorkedDay = instance.get_Personne_Nbre_Shift_Consecutif_Min(nurseId);
		unsigned int consecutiveWorkedDay = 0;

		// Check if the nurse is working on that day
		if (nurseAssignement[dayId] != -1)
		{
			unsigned int endDay = dayId + nbMinConsecutiveWorkedDay;
			vector<unsigned int> workedDays;

			// Prevent the endDay to be out of bound
			if (endDay >= nbDay)
				endDay = nbDay - 1;

			// Count and store the number of consecutive worked days
			for (unsigned int futurDayId = dayId; futurDayId < endDay; ++futurDayId)
			{
				if (nurseAssignement[futurDayId] != -1)
				{
					workedDays.emplace_back(futurDayId);
					++consecutiveWorkedDay;
					++dayId;
				}
			}

			// If the number of consecutive worked days is less than the minimum required, remove the assignement
			if (consecutiveWorkedDay < nbMinConsecutiveWorkedDay)
				for (unsigned int workedDay : workedDays)
					nurseAssignement[workedDay] = -1;
		}
		else
			consecutiveWorkedDay = 0; // Reset the counter
	}
}

void Reparator::executeRandomMinConsecutiveDayRepair(Solution& solution, Instance& instance)
{
	random_device rd;
	mt19937 eng(rd());

	// Repair a random nurse assignement
	uniform_int_distribution<unsigned int> nurseDist(0, solution.v_v_IdShift_Par_Personne_et_Jour.size() - 1);
	executeMinConsecutiveDayRepair(solution, instance, nurseDist(eng));
}

void Reparator::executeTotalMinConsecutiveDayRepair(Solution& solution, Instance& instance)
{
	// Repair all the nurse assignements
	for (unsigned int nurseId = 0; nurseId < instance.get_Nombre_Personne(); ++nurseId)
		executeMinConsecutiveDayRepair(solution, instance, nurseId);
}