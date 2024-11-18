#ifndef UNIFORM_CROSSOVER_H
#define UNIFORM_CROSSOVER_H

#include "CrossoverStrategy.h"

using namespace std;

class UniformCrossover : public CrossoverStrategy
{
private:
	
public:
	void execute(Solution& firstChild, Solution& secondChild) override;
	virtual ~UniformCrossover() = default;
};

#endif
