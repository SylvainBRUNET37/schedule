#pragma once

#include "../../headers/solution/Solution.hpp"
#include "CrossoverStrategy.h"

class Line : public CrossoverStrategy
{
public :
	void execute(Solution* firstChild, Solution* secondChild) override;
	virtual ~Line() = default;
};

