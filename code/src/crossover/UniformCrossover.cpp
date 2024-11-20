#include "../../headers/crossover/UniformCrossover.h"

#include <random>
#include <iostream>

void UniformCrossover::execute(Solution* firstChild, Solution* secondChild)
{
    random_device rd;
    mt19937 gen(rd());
    bernoulli_distribution dist(0.5);

	unsigned int nbNurse = firstChild->v_v_IdShift_Par_Personne_et_Jour.size();
    unsigned int nbDay = firstChild->v_v_IdShift_Par_Personne_et_Jour[0].size();

    for (size_t nurseId = 0; nurseId < nbNurse; ++nurseId)
        for (size_t dayId = 0; dayId < nbDay; ++dayId)
            if (dist(gen) == 0)
                swap(firstChild->v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId], secondChild->v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId]);
}