#ifndef LIGHT_OBJECTIVE_CALCULATOR_H
#define LIGHT_OBJECTIVE_CALCULATOR_H

#include "ObjectiveCalculator.h"

class LightObjectiveCalculator : public ObjectiveCalculator
{
private:

public:
	LightObjectiveCalculator(Instance& instance, Solution& solution, NurseSchedulingData& schedulingData)
		: ObjectiveCalculator(instance, solution, schedulingData) {}

	// Fonction objectif sans les pénalités sur les refus d'affectations et les refus de repos
	int calculateObjectiveFunction() override;

};

#endif
