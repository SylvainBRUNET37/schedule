#include "../../headers/repair/Reparator.h"

// for each individual rebuild the line to comply with these constraints :
//		- minimum shifts consecutive 
void Reparator::execute(Solution& solution, Instance& instance) 
{
	unsigned int nbNurse = instance.get_Nombre_Personne();
	unsigned int nbDay = instance.get_Nombre_Jour();

	random_device rd;
	mt19937 eng(rd());
	uniform_int_distribution<int> dist(1, nbDay - 2);

	for (unsigned int nurseId = 0; nurseId < nbNurse; ++nurseId)
	{
		// Count nb worked days
		unsigned int nbMinuteWorked = 0;
		for (unsigned int dayId = 0; dayId < nbDay; ++dayId)
			if (solution.v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId] != -1)
				nbMinuteWorked += instance.get_Shift_Duree(solution.v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId]);

		// Calculate the difference between the number of worked days and the maximum number of working day for the nurse
		int minuteWorkedDifference = nbMinuteWorked - instance.get_Personne_Duree_total_Max(nurseId);

		// Add days off until the maximum worked time condition is satisfied
		unsigned int dayId = 0;
		while (minuteWorkedDifference > 0)
		{
			// Generate a random day
			dayId = dist(eng);

			// Check if the nurse is working this day. If not, pass
			if (solution.v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId] != -1)
			{
				if (solution.v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId - 1] == -1 && solution.v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId + 1] != -1)
				{
					minuteWorkedDifference -= instance.get_Shift_Duree(solution.v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId]);
					solution.v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId] = -1;
				}
				else if (solution.v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId - 1] != -1 && solution.v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId + 1] == -1)
				{
					minuteWorkedDifference -= instance.get_Shift_Duree(solution.v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId]);
					solution.v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId] = -1;
				}
			}
		}

		cout << "Nurse " << nurseId << " : " << minuteWorkedDifference << " minutes worked diff" << endl;
	}
}