#ifndef COLUMN_H
#define COLUMN_H

#include "../../headers/solution/Solution.hpp"
#include "CrossoverStrategy.h"

class Column : public CrossoverStrategy
{
public:
	void execute(Solution* firstChild, Solution* secondChild) override;
	virtual ~Column() = default;
};

#endif
