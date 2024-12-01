#ifndef MAX_HEURISTIC_AGLORITHM_H
#define MAX_HEURISTIC_AGLORITHM_H

#include <algorithm>
#include <random>

#include "HeuristicAlgorithm.h"

/**
 * @class MaxHeuristicAlgorithm
 * @brief A class that implements a heuristic approach for solving nurse scheduling problems with a focus on maximizing shift allocation.
 *
 * This class extends the `HeuristicAlgorithm` class and provides a specialized approach to the nurse scheduling problem.
 * It incorporates specific methods to allocate shifts for nurses with the objective of maximizing the shift assignments
 * while respecting scheduling constraints. This algorithm improves upon the base heuristic algorithm by prioritizing the
 * allocation of available shifts to nurses more efficiently.
 *
 * The class overrides the nurse availability checks to fine-tune the scheduling and ensure the constraints are respected.
 */
class MaxHeuristicAlgorithm : public HeuristicAlgorithm
{
private:

    /*****************************************************
    *                 GLOBAL VERIFICATION                *
    *****************************************************/

    /**
     * @brief Checks if a nurse is available to work on a given day.
     *
     * This method verifies whether a nurse is available to work on a particular day by checking various conditions such as
     * the nurse's day off status, weekend availability, maximum worked time, and maximum consecutive worked days.
     *
     * @param nurseId ID of the nurse to check.
     * @param dayId ID of the day to check.
     *
     * @return True if the nurse is available, false otherwise.
     */
    bool isAvailableThisDay(unsigned int nurseId, unsigned int dayId) override;

    /**
     * @brief Checks if a nurse is available to work a specific shift on a given day.
     *
     * This method checks whether a nurse is available to work a specific shift on a given day by verifying their prior work
     * on the previous day and ensuring the shift type limits are respected.
     *
     * @param nurseId ID of the nurse to check.
     * @param dayId ID of the day to check.
     * @param shiftId ID of the shift to check.
     *
     * @return True if the nurse is available for the shift, false otherwise.
     */
    bool isAvailableForShift(unsigned int nurseId, unsigned int dayId, unsigned int shiftId) override;

public:
    /*****************************************************
    *              CONTRUCTORS / DESTRUCTOR              *
    *****************************************************/

    /**
     * @brief Constructor for the MaxHeuristicAlgorithm class.
     *
     * This constructor initializes the max heuristic algorithm with the provided instance, which contains the scheduling data.
     * It also sets up the solution matrix, where each nurse's shift assignment for each day is initially set to -1,
     * meaning the nurse is not assigned to work on any day by default.
     *
     * @param instance An Instance object containing the data about nurses, shifts, and scheduling constraints.
     */
    MaxHeuristicAlgorithm(Instance& instance) : HeuristicAlgorithm(instance) {
        // Initialize the solution: set every nurse's shift assignment for each day to -1 (meaning the nurse is not working that day)
        bestSolution.v_v_IdShift_Par_Personne_et_Jour.resize(instance.get_Nombre_Personne(), vector<int>(instance.get_Nombre_Jour(), -1));
    }

    /*****************************************************
    *                  ALGORITHM PARTS                   *
    *****************************************************/

    /**
     * @brief Executes the max heuristic algorithm to find the best scheduling solution.
     *
     * This method runs the max heuristic algorithm, aiming to maximize shift assignments for the nurses while respecting
     * constraints. It optimizes the shift allocation based on nurse availability and shift requirements.
     *
     * @return A reference to the `bestSolution` object that contains the results of the scheduling process.
     */
    Solution& run() override;
};

#endif
