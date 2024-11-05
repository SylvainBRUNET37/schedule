#include "../../headers/crossover/Column.h"

void Column::execute(Solution& firstChild, Solution& secondChild) {
	//nb aléatoire mais pas trop (+/- 15 % de la moitié de la taille de la solution)
	int nbColumns = firstChild.v_v_IdShift_Par_Personne_et_Jour.size();
	int min = nbColumns - (15 / 100 * nbColumns);
	int max = nbColumns + (15 / 100 * nbColumns);
	int separator = min + std::rand() % (max - min + 1);

		//swap par colonnes du separator jusqu'a la fin des matrices.
		for (int i = separator; i < nbColumns; i++){
			std::swap(firstChild.v_v_IdShift_Par_Personne_et_Jour[i], secondChild.v_v_IdShift_Par_Personne_et_Jour[i]);
		}


}