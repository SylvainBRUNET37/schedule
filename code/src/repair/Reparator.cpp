#include "../../headers/repair/Reparator.h"

// for each individual rebuild the line to comply with these constraints :
//		- minimum shifts consecutive 
void Reparator::execute(Solution& solution, Instance& instance) 
{
	unsigned int nbNurse = instance.get_Nombre_Personne();
	unsigned int nbDay = instance.get_Nombre_Jour();

	random_device rd;
	mt19937 eng(rd());
	uniform_int_distribution<int> dist(0, nbDay -1);

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
				// TO DO :
				// Checker si c'est possible de mettre un jour de repos, 
				// tout en respectant la contrainte de minimum de jours travaillés consécutifs
			}
		}	
	}
}