#include "../../headers/crossover/Column.h"

#include <iostream>

void Column::execute(Solution& firstChild, Solution& secondChild) {
    // Nombre de colonnes et lignes dans la matrice
    int nbColumns = firstChild.v_v_IdShift_Par_Personne_et_Jour[0].size();
    int nbLignes = firstChild.v_v_IdShift_Par_Personne_et_Jour.size();

    // Calcul du séparateur basé sur 15% autour de la moitié des lignes
    int min = static_cast<int>(0.5 * nbLignes - 0.15 * nbLignes);
    int max = static_cast<int>(0.5 * nbLignes + 0.15 * nbLignes);
    int separator = min + std::rand() % (max - min + 1);

	cout << firstChild.i_valeur_fonction_objectif << endl;
	cout << secondChild.i_valeur_fonction_objectif << endl;

    // Swap des colonnes à partir du "separator" jusqu'à la fin des lignes de la matrice
    for (int i = separator; i < nbLignes; ++i) {
        for (int j = 0; j < nbColumns; ++j) 
        {
            std::swap(firstChild.v_v_IdShift_Par_Personne_et_Jour[i][j],
                secondChild.v_v_IdShift_Par_Personne_et_Jour[i][j]);
        }
    }

	cout << firstChild.i_valeur_fonction_objectif << endl;
	cout << secondChild.i_valeur_fonction_objectif << endl;
}
