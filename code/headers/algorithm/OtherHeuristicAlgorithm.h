#ifndef OTHER_HEURISTIC_AGLORITHM_H
#define OTHER_HEURISTIC_AGLORITHM_H

#include "ResolutionAlgorithm.h"

class OtherHeuristicAlgorithm : public ResolutionAlgorithm
{
private:

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
	bool isAvailableThisDay(unsigned int nurseId, unsigned int dayId);

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
	bool isAvailableForShift(unsigned int nurseId, unsigned int dayId, unsigned int shiftId);

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
	OtherHeuristicAlgorithm(Instance& instance) : ResolutionAlgorithm(instance) {
		// Initialize the solution: set every nurse's shift assignment for each day to -1 (meaning the nurse is not working that day
		bestSolution.v_v_IdShift_Par_Personne_et_Jour.resize(instance.get_Nombre_Personne(), vector<int>(instance.get_Nombre_Jour(), -1));
	}

	/*****************************************************
	*                  ALGORITHM PARTS                   *
	*****************************************************/

	/**
	 * @brief Executes the heuristic algorithm to find the best scheduling solution.
	 *
	 * @return A pointer to the bestSolution object containing the scheduling results.
	 */
	Solution& run() override;

	/**
	 * @brief Allocates shifts for a specific day.
	 *
	 * @param dayId The ID of the day for which shifts are being allocated.
	 *
	 * Assigns nurses to shifts based on requirements for the day.
	 * Continues allocating until all shifts are filled or no more nurses are available.
	 */
	void allocateDay(unsigned int dayId, vector<unsigned int>& availableNurses);

	/**
	 * @brief Allocates a specific shift to a nurse.
	 *
	 * @param nurseId The ID of the nurse to allocate.
	 * @param dayId The ID of the day for the shift.
	 * @param shiftId The ID of the shift to be allocated.
	 *
	 * @return True if the shift was allocated successfully; false otherwise.
	 */
	bool allocateShift(unsigned int nurseId, unsigned int dayId, unsigned int shiftId);
};

#endif
