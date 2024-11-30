#include "../../headers/crossover/LineTwoPointCrossover.h"

#include <random>

void LineTwoPointCrossover::execute(Solution* firstChild, Solution* secondChild)
{
	// Intialize random distribution between 0 and the number of nurses
	random_device rd;
	mt19937 eng(rd());
	uniform_int_distribution<int> dist(0, firstChild->v_v_IdShift_Par_Personne_et_Jour.size() - 1);

	// Select 2 random crossover points
	int firstCrossoverPoint = dist(eng);
	int secondCrossoverPoint = dist(eng);

	// If the second crossover point is before the first, swap them
	if (firstCrossoverPoint > secondCrossoverPoint)
		swap(firstCrossoverPoint, secondCrossoverPoint);

	// Perform two-point crossover on line
	for (size_t nurseId = firstCrossoverPoint; nurseId < secondCrossoverPoint; ++nurseId)
		swap(firstChild->v_v_IdShift_Par_Personne_et_Jour[nurseId], secondChild->v_v_IdShift_Par_Personne_et_Jour[nurseId]);
}
