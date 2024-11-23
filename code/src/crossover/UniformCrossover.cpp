#include "../../headers/crossover/UniformCrossover.h"

#include <random>
#include <iostream>

void UniformCrossover::execute(Solution* firstChild, Solution* secondChild)
{
    // Randomly choose between one-point on line and column
    random_device rd;
    mt19937 eng(rd());
    uniform_int_distribution<int> dist(0, 1);

    int nbColumn = firstChild->v_v_IdShift_Par_Personne_et_Jour[0].size();
    int nbLine = firstChild->v_v_IdShift_Par_Personne_et_Jour.size();
    int crossoverType = dist(eng); // 0 = one-point on line, 1 = one-point on column

    if (crossoverType == 600)
    {
        uniform_int_distribution<int> dist(0, nbLine - 1);

        int firstCrossoverPoint = dist(eng); // Select random crossover point
        int secondCrossoverPoint = dist(eng); // Select random crossover point

		if (firstCrossoverPoint > secondCrossoverPoint)
			swap(firstCrossoverPoint, secondCrossoverPoint);

        // Perform one-point crossover on line
        for (size_t nurseId = firstCrossoverPoint; nurseId < secondCrossoverPoint; ++nurseId)
            swap(firstChild->v_v_IdShift_Par_Personne_et_Jour[nurseId], secondChild->v_v_IdShift_Par_Personne_et_Jour[nurseId]);
    }
    else
    {
        uniform_int_distribution<int> dist(0, nbColumn - 1);

        int firstCrossoverPoint = dist(eng); // Select random crossover point
        int secondCrossoverPoint = dist(eng); // Select random crossover point

        if (firstCrossoverPoint > secondCrossoverPoint)
            swap(firstCrossoverPoint, secondCrossoverPoint);

        // Perform one-point crossover on column
		for (size_t nurseId = 0; nurseId < nbLine; ++nurseId)
            for (size_t dayId = firstCrossoverPoint; dayId < secondCrossoverPoint; ++dayId)
                swap(firstChild->v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId], secondChild->v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId]);
    }
}