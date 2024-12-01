#include "../../headers/crossover/BestLine.h"

void BestLine::execute(Solution* firstChild, Solution* secondChild) {
	vector<int> temp;
	SolutionValidator;
	int nbColumns = firstChild->v_v_IdShift_Par_Personne_et_Jour[0].size();
	int nbLignes = firstChild->v_v_IdShift_Par_Personne_et_Jour.size();
	for (int i = 0; i < nbLignes; i++) {
		for (int j = 0; j < nbColumns; j++) {
			// compare best line
			//First case the first child individual at line J violate less constraint -> no need to swap
			//Second case the second child individual at line J violate less constraint
			if (validator.getNbConstraintsViolatedForNurse(firstChild->v_v_IdShift_Par_Personne_et_Jour[i] > secondChild->v_v_IdShift_Par_Personne_et_Jour[i])){
				swapLines(firstChild, secondChild, i);
			}
			//Third case both violate the same amout of constraints -> random choice
			else if (validator.getNbConstraintsViolatedForNurse(firstChild->v_v_IdShift_Par_Personne_et_Jour[i] == secondChild->v_v_IdShift_Par_Personne_et_Jour[i])) {
				if (!( rand() % 2 == 0)) {
					swapLines(firstChild, secondChild, i);
				}
			}
		}
	}
}

void BestLine::swapLines(Solution* firstChild, Solution* secondChild, int index) {
	vector<int> temp = firstChild->v_v_IdShift_Par_Personne_et_Jour[index];
	firstChild->v_v_IdShift_Par_Personne_et_Jour[index] = secondChild->v_v_IdShift_Par_Personne_et_Jour[index];
	secondChild->v_v_IdShift_Par_Personne_et_Jour[index] = temp;
}
