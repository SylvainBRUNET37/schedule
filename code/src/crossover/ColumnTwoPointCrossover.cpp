#include "../../headers/crossover/ColumnTwoPointCrossover.h"

#include <random>

void ColumnTwoPointCrossover::execute(Solution* firstChild, Solution* secondChild)
{
	random_device rd;
	mt19937 eng(rd());

	// Get the number of columns and lines
	int nbColumn = firstChild->v_v_IdShift_Par_Personne_et_Jour[0].size();
	int nbLine = firstChild->v_v_IdShift_Par_Personne_et_Jour.size();

	// Intialize random distribution between 0 and the number of days
	uniform_int_distribution<int> dist(0, nbColumn - 1);

	// Select 2 random crossover points
	int firstCrossoverPoint = dist(eng);
	int secondCrossoverPoint = dist(eng);

	if (firstCrossoverPoint > secondCrossoverPoint)
		swap(firstCrossoverPoint, secondCrossoverPoint);

	// Perform two-point crossover on line
	for (size_t nurseId = 0; nurseId < nbLine; ++nurseId)
		for (size_t dayId = firstCrossoverPoint; dayId < secondCrossoverPoint; ++dayId)
			swap(firstChild->v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId], secondChild->v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId]);
}
