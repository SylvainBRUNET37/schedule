#ifndef COLUMN_TWO_POINT_CROSSOVER_H
#define COLUMN_TWO_POINT_CROSSOVER_H

#include "CrossoverStrategy.h"

class ColumnTwoPointCrossover : public CrossoverStrategy
{
private:

public:
	void execute(Solution* firstChild, Solution* secondChild) override;
};

#endif
