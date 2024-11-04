#include "../../headers/calculation/LightObjectiveCalculator.h"

int LightObjectiveCalculator::calculateObjectiveFunction()
{
	return ObjectiveCalculator::calculateUnderstaffingCost() + ObjectiveCalculator::calculateOverstaffingCost();
}
