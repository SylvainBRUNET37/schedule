#ifndef MIN_HEURISTIC_AGLORITHM_H
#define MIN_HEURISTIC_AGLORITHM_H

#include "HeuristicAlgorithm.h"

/**
 * @class MinHeuristicAlgorithm
 * @brief A class that implements a heuristic approach for solving nurse scheduling problems with a focus on minimizing shift allocation.
 *
 * This class extends the `HeuristicAlgorithm` class and provides a specialized approach to the nurse scheduling problem.
 * It focuses on minimizing the number of shifts assigned to nurses while respecting scheduling constraints. The algorithm
 * aims to minimize shift allocation while still adhering to nurse availability, days off, and other constraints.
 *
 * The class overrides the nurse availability checks to ensure that the constraints are respected while attempting to minimize
 * the shift assignments.
 */
class MinHeuristicAlgorithm : public HeuristicAlgorithm
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
     * @brief Constructor for the MinHeuristicAlgorithm class.
     *
     * This constructor initializes the min heuristic algorithm with the provided instance, which contains the scheduling data.
     * It sets up the solution matrix, where each nurse's shift assignment for each day is initially set to -1,
     * indicating that no nurse is assigned a shift by default.
     *
     * @param instance An Instance object containing the data about nurses, shifts, and scheduling constraints.
     */
    MinHeuristicAlgorithm(Instance& instance) : HeuristicAlgorithm(instance) {}
};

#endif
