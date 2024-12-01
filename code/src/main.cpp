#define CHEMIN_DOSSIER_DONNEES "./data/"
#define NOM_FICHIER_LISTE_FICHIER_DONNEES "data.txt"
#define NOM_FICHIER_LISTE_SORTIE "sortie.txt"

//#define RELEASE_PERFORMANCE
//#define RELEASE
//#define MAX_HEURISTIC_ALGORITHM
#define MIN_HEURISTIC_ALGORITHM
//#define OTHER_HEURISTIC_ALGORITHM

#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>

// Include crossover strategies
#include "../headers/crossover/Column.h"
#include "../headers/crossover/Line.h"
#include "../headers/crossover/UniformCrossover.h"
#include "../headers/crossover/LineTwoPointCrossover.h"
#include "../headers/crossover/ColumnTwoPointCrossover.h"

// Include algorithms
#include "../headers/algorithm/GeneticAlgorithm.h"
#include "../headers/algorithm/HeuristicAlgorithm.h"
#include "../headers/algorithm/MinHeuristicAlgorithm.h"
#include "../headers/algorithm/OtherHeuristicAlgorithm.h"

// Include solution and instance
#include "../headers/solution/Instance.hpp"
#include "../headers/solution/Solution.hpp"

// Include other things
#include "../headers/calculation/CompleteObjectiveCalculator.h"
#include "../headers/selection/TournamentSelection.h"
#include "../headers/mutation/SwapShiftMutation.h"
#include "../headers/repair/Reparator.h"


using namespace std;

int Resolution(Instance* instance);

int main(int argc, const char* argv[])
{
	try
	{
		string s_tmp;
		string s_chemin = CHEMIN_DOSSIER_DONNEES;
		s_chemin.append(NOM_FICHIER_LISTE_FICHIER_DONNEES);

		ifstream fichier(s_chemin.c_str(), std::ios::in); std::ofstream fichier_Sortie_Resume;
		s_chemin = CHEMIN_DOSSIER_DONNEES;
		s_chemin.append(NOM_FICHIER_LISTE_SORTIE);
		ofstream fichier_Sortie(s_chemin.c_str(), std::ios::out | std::ios::app);

		if (fichier)
		{
			if (fichier_Sortie)
			{
				fichier_Sortie << "Fichier donnees\t Tps de resolution \t Best solution" << endl;
				getline(fichier, s_tmp);
				while (s_tmp != "")
				{
					Instance* instance = new Instance();
					chrono::time_point<chrono::system_clock> chrono_start, chrono_end;
					chrono::duration<double> elapsed;
					int i_best_solution_score = 0;
					s_chemin = CHEMIN_DOSSIER_DONNEES;
					cout << "Resolution de " << s_tmp << endl;
					s_chemin.append(s_tmp);
					s_chemin.erase(remove(s_chemin.begin(), s_chemin.end(), '\r'), s_chemin.end());
					s_chemin.erase(remove(s_chemin.begin(), s_chemin.end(), '\n'), s_chemin.end());

					instance->chargement_Instance(s_chemin);
					chrono_start = chrono::system_clock::now();
					i_best_solution_score = Resolution(instance);
					cout << "Fin de resolution de " << s_tmp << endl;
					chrono_end = chrono::system_clock::now();
					elapsed = chrono_end - chrono_start;
					fichier_Sortie << s_chemin << "\t" << elapsed.count() << "\t" << i_best_solution_score << endl;
					s_tmp = "";
					getline(fichier, s_tmp);
					delete instance;
				}
				fichier_Sortie.close();
			}
			else
			{
				cout << "Erreur lecture des donnees : chemin vers la sortie non valide. " << endl;
			}
			fichier.close();
		}
		else
		{
			cout << "Erreur lecture des donnees : chemin listant l'ensemble des donnees non valide. " << endl;
		}
	}

	catch (string err)
	{
		cout << "Erreur fatale : " << endl;
		cout << err << endl;
	}
	return 0;
}

void displayMatrix(const std::vector<std::vector<int>>& matrix) {
	for (const auto& row : matrix) { // Parcourir chaque ligne
		for (int value : row) {       // Parcourir chaque élément de la ligne
			std::cout << value << " "; // Afficher l'élément
		}
		std::cout << std::endl;         // Nouvelle ligne après chaque ligne de la matrice
	}
}

void displayMatrixAlenvers(const std::vector<std::vector<int>>& matrix) {
	if (matrix.empty()) return; // Vérifier si la matrice est vide

	// Obtenez le nombre de lignes et de colonnes
	unsigned int rowCount = matrix.size();
	unsigned int colCount = matrix[0].size();

	// Parcourez les colonnes de la matrice originale pour les afficher comme des lignes
	for (unsigned int col = 0; col < colCount; ++col) {
		for (unsigned int row = 0; row < rowCount; ++row) {
			std::cout << matrix[row][col] << " "; // Afficher l'élément transposé
		}
		std::cout << std::endl; // Nouvelle ligne après chaque ligne transposée
	}
}

void displayArray(const std::vector<int>& array) {
	for (const auto& value : array)
		std::cout << value << " ";
	std::cout << std::endl;
}

void countMinuteWorked(std::vector<unsigned int>& array) {
	int totalValue = 0;
	for (const auto& value : array)
		totalValue += value;
	std::cout << totalValue << std::endl << endl;
}

void countMinuteMaxWorked(Instance* instance) {
	int totalValue = 0;
	for (int i = 0; i < instance->get_Nombre_Personne(); ++i)
		totalValue += instance->get_Personne_Duree_total_Max(i);
	std::cout << totalValue << std::endl << endl;
}

#ifdef RELEASE

int Resolution(Instance* instance)
{
	int objectiveFunctionValue = 0;

	GeneticAlgorithm algo(*instance, 500);
	//set the differents strategies
	algo.setSelectionStrategy(make_unique<TournamentSelection>());
	algo.setCrossoverStrategy(make_unique<Column>()); // Column, LineTwoPointCrossover are working well
	algo.setMutationStrategy(make_unique <SwapShiftMutation>());
	algo.setObjectiveCalculator(make_unique <CompleteObjectiveCalculator>());
	Solution solution = algo.run();
	ObjectiveCalculator objectiveCalculator;

	// Display the solution
	cout << "Solution : " << endl;
	displayMatrix(solution.v_v_IdShift_Par_Personne_et_Jour);

	// Calculate objective function
	objectiveFunctionValue = objectiveCalculator.calculateObjectiveFunction(*instance, solution);

	// Verify solution & objective function
	solution.Verification_Solution(instance);

	// Display objective function
	cout << endl << "Objective function value (basic) : " << objectiveFunctionValue << endl;
	cout << endl << "Objective function value (with weights) : " << algo.getBestSolution().i_valeur_fonction_objectif << endl << endl;

	return objectiveFunctionValue;
}
#endif

#ifdef RELEASE_PERFORMANCE

int Resolution(Instance* instance)
{
	int objectiveFunctionValue = 0;

	GeneticAlgorithm algo(*instance, 25);
	//set the differents strategies
	algo.setSelectionStrategy(make_unique<TournamentSelection>());
	algo.setCrossoverStrategy(make_unique<Column>());
	algo.setMutationStrategy(make_unique <SwapShiftMutation>());
	algo.setObjectiveCalculator(make_unique <CompleteObjectiveCalculator>());
	Solution solution = algo.run();
	ObjectiveCalculator objectiveCalculator;

	// Calculate objective function
	objectiveFunctionValue = objectiveCalculator.calculateObjectiveFunction(*instance, solution);

	// Display objective function
	cout << endl << "Objective function value (basic) : " << objectiveFunctionValue << endl;
	cout << endl << "Objective function value (with weights) : " << algo.getBestSolution().i_valeur_fonction_objectif << endl << endl;

	return objectiveFunctionValue;
}
#endif

#ifdef MAX_HEURISTIC_ALGORITHM

int Resolution(Instance* instance)
{
	int objectiveFunctionValue = 0;

	HeuristicAlgorithm maxAlgo(*instance);

	Solution& solution = maxAlgo.run();
	ObjectiveCalculator objectiveCalculator;
	CompleteObjectiveCalculator completeObjectiveCalculator;

	// Display the solution
	cout << "Solution : " << endl;
	displayMatrix(solution.v_v_IdShift_Par_Personne_et_Jour);

	// Calculate objective function
	objectiveFunctionValue = objectiveCalculator.calculateObjectiveFunction(*instance, solution);

	// Verify solution & objective function
	solution.Verification_Solution(instance);

	// Display objective function
	cout << endl << "Objective function value (basic) : " << objectiveFunctionValue << endl;
	cout << endl << "Objective function value (with weights) : " << completeObjectiveCalculator.calculateObjectiveFunction(*instance, solution) << endl;

	cout << endl << "Minute worked : " << endl;
	countMinuteWorked(maxAlgo.getSchedulingData().nbMinuteWorked);

	cout << endl << "Max minute worked : " << endl;
	countMinuteMaxWorked(instance);

	return objectiveFunctionValue;
}

#endif

#ifdef MIN_HEURISTIC_ALGORITHM

int Resolution(Instance* instance)
{
	int objectiveFunctionValue = 0;

	MinHeuristicAlgorithm minAlgo(*instance);

	Solution& solution = minAlgo.run();
	ObjectiveCalculator objectiveCalculator;

	// Display the solution
	cout << "Solution : " << endl;
	displayMatrix(solution.v_v_IdShift_Par_Personne_et_Jour);

	// Repair the solution
	//Reparator reparator(instance);
	//reparator.execute(solution, *instance);

	// Calculate objective function
	objectiveFunctionValue = objectiveCalculator.calculateObjectiveFunction(*instance, solution);
	objectiveFunctionValue = minAlgo.getBestSolution().i_valeur_fonction_objectif;

	// Verify solution & objective function
	solution.Verification_Solution(instance);

	cout << endl << "Objective function value : " << objectiveFunctionValue << endl << endl;

	return objectiveFunctionValue;
}

#endif

#ifdef OTHER_HEURISTIC_ALGORITHM

int Resolution(Instance* instance)
{
	int objectiveFunctionValue = 0;

	OtherHeuristicAlgorithm minAlgo(*instance);

	Solution& solution = minAlgo.run();
	ObjectiveCalculator objectiveCalculator;

	// Display the solution
	cout << "Solution : " << endl;
	displayMatrix(solution.v_v_IdShift_Par_Personne_et_Jour);

	// Calculate objective function
	objectiveFunctionValue = objectiveCalculator.calculateObjectiveFunction(*instance, solution);
	objectiveFunctionValue = minAlgo.getBestSolution().i_valeur_fonction_objectif;

	// Verify solution & objective function
	solution.Verification_Solution(instance);

	cout << endl << "Objective function value : " << objectiveFunctionValue << endl << endl;

	return objectiveFunctionValue;
}

#endif