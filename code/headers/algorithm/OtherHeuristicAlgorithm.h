#ifndef OTHER_HEURISTIC_AGLORITHM_H
#define OTHER_HEURISTIC_AGLORITHM_H

#include <algorithm>
#include <random>

#include "HeuristicAlgorithm.h"

class OtherHeuristicAlgorithm : public HeuristicAlgorithm
{
private:

protected:
	/*****************************************************
	*                 GLOBAL VERIFICATION                *
	*****************************************************/

	/**
	 * @brief Checks if a nurse is available to work on a given day.
	 *
	 * @param nurseId ID of the nurse to check.
	 * @param dayId ID of the day to check.
	 *
	 * @return True if the nurse is available, false otherwise.
	 *
	 * Verifies various conditions such as day off status, weekend availability, maximum worked time,
	 * and maximum consecutive worked days to determine if the nurse is available.
	 */
	bool isAvailableThisDay(unsigned int nurseId, unsigned int dayId) override;

	/**
	 * @brief Checks if a nurse is available to work a specific shift on a given day.
	 *
	 * @param nurseId ID of the nurse to check.
	 * @param dayId ID of the day to check.
	 * @param shiftId ID of the shift to check.
	 *
	 * @return True if the nurse is available for the shift, false otherwise.
	 *
	 * Verifies the availability of the nurse based on the previous day's work and shift type limits.
	 */
	bool isAvailableForShift(unsigned int nurseId, unsigned int dayId, unsigned int shiftId) override;

public:
	/*****************************************************
	*              CONTRUCTORS / DESTRUCTOR              *
	*****************************************************/

	/**
	 * @brief Constructor for the HeuristicAlgorithm class.
	 *
	 * @param instance An Instance object containing data about nurses and scheduling.
	 *
	 * Initializes the algorithm with the given instance,
	 * fills the list of nurses, and fill the solution matrix with -1.
	 */
	OtherHeuristicAlgorithm(Instance& instance) : HeuristicAlgorithm(instance) {
		// Initialize the solution: set every nurse's shift assignment for each day to -1 (meaning the nurse is not working that day
		bestSolution.v_v_IdShift_Par_Personne_et_Jour.resize(instance.get_Nombre_Personne(), vector<int>(instance.get_Nombre_Jour(), -1));
	}

	Solution& run() override;
};

#endif
