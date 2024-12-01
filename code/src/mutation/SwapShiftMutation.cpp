#include "../../headers/mutation/SwapShiftMutation.h"

#include <random>
#include <algorithm>
#include <iostream>

void SwapShiftMutation::execute(Solution& solution)
{
	random_device rd;
	mt19937 eng(rd());

	// Get the number of columns and lines
	unsigned int nbNurse = solution.v_v_IdShift_Par_Personne_et_Jour.size();
	unsigned int nbDay = solution.v_v_IdShift_Par_Personne_et_Jour[0].size();

	// Generate a random nurse
	uniform_int_distribution<unsigned int> nurseDist(0, nbNurse - 1);
	unsigned int nurseId = nurseDist(eng);
	vector<int>& nurseSchedule = solution.v_v_IdShift_Par_Personne_et_Jour[nurseId];

	// Generate 2 random crossover points
	uniform_int_distribution<unsigned int> columnDist(1, nbDay - 2);
	unsigned int firstCrossoverPoint = columnDist(eng);
	unsigned int secondCrossoverPoint = columnDist(eng);

	// Swap the two points if the first is greater than the second
	if (firstCrossoverPoint > secondCrossoverPoint)
		swap(firstCrossoverPoint, secondCrossoverPoint);

	// Rotate the shifts between the two crossover points
	rotate(nurseSchedule.begin() + firstCrossoverPoint,
		   nurseSchedule.begin() + firstCrossoverPoint + (secondCrossoverPoint - firstCrossoverPoint) / 2,
		   nurseSchedule.begin() + secondCrossoverPoint);
}