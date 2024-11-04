#include "../../headers/selection/TournamentSelection.h"

Solution& TournamentSelection::execute(Solution& solution1, Solution& solution2)
{
	if (solution1.i_valeur_fonction_objectif > solution2.i_valeur_fonction_objectif)
		return solution1;
	else
		return solution2;
}
