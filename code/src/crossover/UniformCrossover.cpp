#include "../../headers/crossover/UniformCrossover.h"

#include <random>
#include <iostream>

void UniformCrossover::execute(Solution* firstChild, Solution* secondChild)
{
    // Get the number of columns and lines
    int nbColumn = firstChild->v_v_IdShift_Par_Personne_et_Jour[0].size();
    int nbLine = firstChild->v_v_IdShift_Par_Personne_et_Jour.size();

	// Intialize random generator
    random_device rd;
    mt19937 eng(rd());
    uniform_int_distribution<int> distSize(1, nbColumn - 1);
    uniform_int_distribution<int> distColumn(0, (nbColumn - distSize(eng)) - 1);

	// TO DO : Implement the crossover
}