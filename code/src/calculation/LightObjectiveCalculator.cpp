#include "../../headers/calculation/LightObjectiveCalculator.h"

int LightObjectiveCalculator::calculateObjectiveFunction()
{
	// Fonction objectif sans les pénalités sur les refus d'affectations et les refus de repos
	return ObjectiveCalculator::calculateUnderstaffingCost() + ObjectiveCalculator::calculateOverstaffingCost();
}
