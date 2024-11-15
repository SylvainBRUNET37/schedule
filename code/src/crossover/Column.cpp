#include "../../headers/crossover/Column.h"

#include <iostream>
#include <random>

void Column::execute(Solution& firstChild, Solution& secondChild) 
{
    int nbColumns = firstChild.v_v_IdShift_Par_Personne_et_Jour[0].size();
    int nbLignes = firstChild.v_v_IdShift_Par_Personne_et_Jour.size();

    // Use a random generator for the separator within a 30-70% range
    int min = static_cast<int>(0.3 * nbLignes);
    int max = static_cast<int>(0.7 * nbLignes);
    int separator = min + std::rand() % (max - min + 1);

    // Swap columns from separator to the end for both firstChild and secondChild
    for (int i = separator; i < nbLignes; ++i) {
        for (int j = 0; j < nbColumns; ++j) {
            // Swap values for both children at position (i, j)
            std::swap(firstChild.v_v_IdShift_Par_Personne_et_Jour[i][j],
                secondChild.v_v_IdShift_Par_Personne_et_Jour[i][j]);
        }
    }
}