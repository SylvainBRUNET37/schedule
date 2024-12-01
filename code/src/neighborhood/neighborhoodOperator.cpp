#include "../../headers/neighborhood/neighborhoodOperator.h"

#include <random>
#include <algorithm>
#include <iostream>

void NeighborhoodOperator::execute(Solution& solution, Instance& instance)
{
	random_device rd;
	mt19937 eng(rd());

	// Get the number of columns and lines
	unsigned int nbNurse = solution.v_v_IdShift_Par_Personne_et_Jour.size();
	unsigned int nbDay = solution.v_v_IdShift_Par_Personne_et_Jour[0].size();

	// Generate a random nurse
	uniform_int_distribution<unsigned int> nurseDist(0, nbNurse - 1);
	unsigned int nurseId = nurseDist(eng);
	vector<int>& nurseAssignement = solution.v_v_IdShift_Par_Personne_et_Jour[nurseId];

	// Random shift generator
	uniform_int_distribution<unsigned int> distShift(0, instance.get_Nombre_Shift() - 1);

	// Try to repair
	for (unsigned int dayId = 0; dayId < nbDay; ++dayId)
	{
		// Get the minimum number of worked days for the nurse
		unsigned int nbMinConsecutiveWorkedDay = instance.get_Personne_Nbre_Shift_Consecutif_Min(nurseId);
		unsigned int consecutiveWorkedDay = 0;

		//
		if (solution.v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId] != -1)
			++consecutiveWorkedDay;
		else
			consecutiveWorkedDay = 0;

		if (dayId > nbMinConsecutiveWorkedDay)
		{
			// If the nurse has not reached the minimum number of consecutive worked days, repair
			if ((consecutiveWorkedDay < nbMinConsecutiveWorkedDay) && (consecutiveWorkedDay != 0) && ((dayId - nbMinConsecutiveWorkedDay) >= 0))
			{
				if (solution.v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId] != 1)
					nurseAssignement[dayId] = distShift(eng);
				else if (solution.v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId - nbMinConsecutiveWorkedDay - 1] == -1)
					nurseAssignement[dayId - nbMinConsecutiveWorkedDay - 1] = distShift(eng);
				else
					nurseAssignement[dayId - 1] = -1;
			}
		}
	}
}
