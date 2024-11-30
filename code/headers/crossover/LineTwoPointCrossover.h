#ifndef LINE_TWO_POINT_CROSSOVER_H
#define LINE_TWO_POINT_CROSSOVER_H

#include "CrossoverStrategy.h"

class LineTwoPointCrossover : public CrossoverStrategy
{
private:

public:
	void execute(Solution* firstChild, Solution* secondChild) override;
};

#endif
