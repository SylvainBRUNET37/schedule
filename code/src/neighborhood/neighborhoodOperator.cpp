#include "../../headers/neighborhood/neighborhoodOperator.h"

#include <random>
#include <algorithm>
#include <iostream>

void NeighborhoodOperator::executeMinConsecutiveDayRepair(Solution& solution, Instance& instance, unsigned int nurseId)
{
	// Get the number of columns and lines
	unsigned int nbNurse = solution.v_v_IdShift_Par_Personne_et_Jour.size();
	unsigned int nbDay = solution.v_v_IdShift_Par_Personne_et_Jour[0].size();

	// Get the nurse assignement
	vector<int>& nurseAssignement = solution.v_v_IdShift_Par_Personne_et_Jour[nurseId];

	// Try to repair
	for (unsigned int dayId = 0; dayId < nbDay; ++dayId)
	{
		// Get the minimum number of worked days for the nurse
		unsigned int nbMinConsecutiveWorkedDay = instance.get_Personne_Nbre_Shift_Consecutif_Min(nurseId);
		unsigned int consecutiveWorkedDay = 0;

		if (nurseAssignement[dayId] != -1)
		{
			unsigned int endDay = dayId + nbMinConsecutiveWorkedDay;

			if (endDay >= nbDay)
				endDay = nbDay - 1;

			vector<unsigned int> workedDays;
			for (unsigned int futurDayId = dayId; futurDayId < endDay; ++futurDayId)
			{
				if (nurseAssignement[futurDayId] != -1)
				{
					workedDays.emplace_back(futurDayId);
					++consecutiveWorkedDay;
					++dayId;
				}
			}

			if (consecutiveWorkedDay < nbMinConsecutiveWorkedDay)
				for (unsigned int workedDay : workedDays)
					nurseAssignement[workedDay] = -1;
		}
		else
			consecutiveWorkedDay = 0;
	}
}

void NeighborhoodOperator::executeRandomMinConsecutiveDayRepair(Solution& solution, Instance& instance)
{
	random_device rd;
	mt19937 eng(rd());

	// Repair a random nurse assignement
	uniform_int_distribution<unsigned int> nurseDist(0, solution.v_v_IdShift_Par_Personne_et_Jour.size() - 1);
	executeMinConsecutiveDayRepair(solution, instance, nurseDist(eng));
}

void NeighborhoodOperator::executeTotalMinConsecutiveDayRepair(Solution& solution, Instance& instance)
{
	for (unsigned int nurseId = 0; nurseId < instance.get_Nombre_Personne(); ++nurseId)
		executeMinConsecutiveDayRepair(solution, instance, nurseId);
}
