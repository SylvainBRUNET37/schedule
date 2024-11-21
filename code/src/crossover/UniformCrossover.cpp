#include "../../headers/crossover/UniformCrossover.h"

#include <random>
#include <iostream>

void UniformCrossover::execute(Solution* firstChild, Solution* secondChild)
{
	int nbColumns = firstChild->v_v_IdShift_Par_Personne_et_Jour[0].size();
	int nbLignes = firstChild->v_v_IdShift_Par_Personne_et_Jour.size();

	// Assume that solutions have a vector representation
	random_device rd;
	mt19937 eng(rd());
	uniform_int_distribution<int> dist(0, nbLignes - 1);

	int crossoverPoint = dist(eng); // Select random crossover point

	// Perform one-point crossover
	for (size_t i = crossoverPoint; i < nbLignes; ++i)
		swap(firstChild->v_v_IdShift_Par_Personne_et_Jour[i], secondChild->v_v_IdShift_Par_Personne_et_Jour[i]);
}