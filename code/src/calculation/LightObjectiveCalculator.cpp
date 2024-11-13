#include "../../headers/calculation/LightObjectiveCalculator.h"

int LightObjectiveCalculator::calculateObjectiveFunction(Instance& instance, Solution& solution, NurseSchedulingData& schedulingData)
{
	// Fonction objectif sans les pénalités sur les refus d'affectations et les refus de repos
	return ObjectiveCalculator::calculateUnderstaffingCost(instance, solution, schedulingData) + ObjectiveCalculator::calculateOverstaffingCost(instance, solution, schedulingData);
}
