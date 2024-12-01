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
	unsigned int nbColumnToSwap = distSize(eng);

	// Intialize start points
    uniform_int_distribution<int> distColumn(0, (nbColumn - nbColumnToSwap) - 1);
    unsigned int startPoint1 = distColumn(eng);
    unsigned int startPoint2 = distColumn(eng);

    // Perform the crossover
    for (size_t nurseId = 0; nurseId < nbLine; ++nurseId)
        for (size_t dayId = 0; dayId < nbColumnToSwap; ++dayId)
            swap(firstChild->v_v_IdShift_Par_Personne_et_Jour[nurseId][startPoint1 + dayId], 
                secondChild->v_v_IdShift_Par_Personne_et_Jour[nurseId][startPoint2 + dayId]);
}