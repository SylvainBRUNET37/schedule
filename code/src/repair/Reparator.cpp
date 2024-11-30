#include "../../headers/repair/Reparator.h"

void Reparator::execute(Solution& solution, Instance& instance) {
	int nbIndividus = solution.v_v_IdShift_Par_Personne_et_Jour.size();
	//for each individual rebuild the line to comply with these 2 constraints :
	// - total duration for individual too high (we)
	// - minimum shifts consecutive 

	for (int i = 0; i < nbIndividus; i++) {		
		random_device rd;
		mt19937 eng(rd());
		//count nb shifts worked
		int nbDays = instance.get_Nombre_Jour();
		{
			int nbWorkDays = 0;
			for (int j = 0; j <= nbDays; j++) {
				if (solution.v_v_IdShift_Par_Personne_et_Jour[i][j] != -1) nbWorkDays++;
			}

			// add days off based on existing we/days of until this condition is satisfied
			int diff = nbWorkDays - instance.get_Personne_Duree_total_Max(i);
			if (diff > 0 ) { // loop until no more extras workDays 
				for (int j = 0; j <= diff; j++) {
					int randAcces = rand() % solution.v_v_IdShift_Par_Personne_et_Jour[i].size();
					//if working this day -> advance until day of
					if (solution.v_v_IdShift_Par_Personne_et_Jour[i][randAcces] != -1) {
						while (solution.v_v_IdShift_Par_Personne_et_Jour[i][randAcces] == -1) {
							randAcces++;
						}
						solution.v_v_IdShift_Par_Personne_et_Jour[i][randAcces - 1] = -1;
					}
					//else advance until day on
					else {
						while (solution.v_v_IdShift_Par_Personne_et_Jour[i][randAcces] != -1) {
							randAcces++;
						}
						solution.v_v_IdShift_Par_Personne_et_Jour[i][randAcces] = -1;
					}
				}
			}
		}
	}
}