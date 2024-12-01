#ifndef SOLUTION_VALIDATOR_H
#define SOLUTION_VALIDATOR_H

#include <algorithm>
#include <iostream>

#include "../solution/Instance.hpp"
#include "../solution/Solution.hpp"
#include "../solution/NurseSchedulingData.h"

/**
 * @class SolutionValidator
 * @brief This class is responsible for validating the nurse scheduling solution against various constraints.
 *
 * The SolutionValidator checks whether the current solution (nurse schedule) adheres to the scheduling constraints.
 * It performs validation based on the provided instance data (e.g., number of shifts, days off, maximum work time) and the
 * specific nurse scheduling data. The solution is validated for hard constraints such as maximum consecutive workdays,
 * shift types, and day-offs, ensuring the scheduling is feasible and within the limits.
 */
class SolutionValidator
{
private:
    const unsigned int DAYS_IN_WEEK = 7; ///< Number of days in a week.

    Instance* instance; ///< Pointer to the Instance object that holds the scheduling data.
    Solution* solution; ///< Pointer to the Solution object that holds the current nurse schedule.
    NurseSchedulingData* schedulingData; ///< Pointer to the NurseSchedulingData object holding nurse-specific scheduling data.

public:
    /*****************************************************
    *              CONTRUCTORS / DESTRUCTOR              *
    *****************************************************/

    /**
     * @brief Constructor for the SolutionValidator class.
     *
     * Initializes the SolutionValidator object with an Instance, Solution, and NurseSchedulingData.
     *
     * @param instance Reference to the Instance object containing general scheduling data.
     * @param solution Reference to the Solution object representing the current schedule.
     * @param schedulingData Reference to the NurseSchedulingData object with nurse-specific data.
     */
    SolutionValidator(Instance* instance, Solution* solution, NurseSchedulingData* schedulingData)
        : instance(instance), solution(solution), schedulingData(schedulingData) {
    }

    /**
     * @brief Overloaded constructor for the SolutionValidator class when only an Instance is provided.
     *
     * @param instance Reference to the Instance object containing general scheduling data.
     */
    SolutionValidator(Instance* instance)
        : instance(instance), solution(nullptr), schedulingData(nullptr) {
    }

    /**
     * @brief Sets a new Instance object.
     *
     * @param newInstance The new Instance object to set.
     */
    void setInstance(Instance* newInstance) {
        instance = newInstance;
    }

    /**
     * @brief Sets a new Solution object.
     *
     * @param newSolution The new Solution object to set.
     */
    void setSolution(Solution* newSolution) {
        solution = newSolution;
    }

    /**
     * @brief Sets a new NurseSchedulingData object.
     *
     * @param newSchedulingData The new NurseSchedulingData object to set.
     */
    void setSchedulingData(NurseSchedulingData* newSchedulingData) {
        schedulingData = newSchedulingData;
    }

    /*****************************************************
    *                  OTHER VERIFICATION                *
    *****************************************************/

    /**
     * @brief Returns the number of constraints violated on a specific day off.
     *
     * @param nurseId The unique identifier of the nurse.
     * @param dayId The unique identifier of the day being checked.
     * @param consecutiveWorkedShift The number of consecutive shifts worked prior to the day off.
     * @return The number of constraints violated for the specified day off.
     */
    unsigned int getNbConstraintsViolatedOnDayOff(unsigned int nurseId, unsigned int dayId, unsigned int consecutiveWorkedShift);

    /**
     * @brief Returns the number of constraints violated on a specific worked day.
     *
     * @param nurseId The unique identifier of the nurse.
     * @param dayId The unique identifier of the day being checked.
     * @param consecutiveWorkedShift The number of consecutive shifts worked prior to the day.
     * @return The number of constraints violated for the specified worked day.
     */
    unsigned int getNbConstraintsViolatedOnWorkedDay(unsigned int nurseId, unsigned int dayId, unsigned int consecutiveWorkedShift);

    /**
     * @brief Returns the number of constraints violated based on the nurse's scheduling data.
     *
     * @param nurseId The unique identifier of the nurse.
     * @return The number of constraints violated based on the nurse's total worked time, weekend work, and shift type limits.
     */
    unsigned int getNbContraintsViolatedWithData(unsigned int nurseId);

    /*****************************************************
    *                 GLOBAL VERIFICATION                *
    *****************************************************/

    /**
     * @brief Returns the total number of constraints violated for a nurse across all days.
     *
     * @param nurseId The unique identifier of the nurse.
     * @return The total number of constraints violated for the nurse.
     */
    unsigned int getNbConstraintsViolatedForNurse(unsigned int nurseId);

    /**
     * @brief Checks if a nurse is scheduled to work on a specific day.
     *
     * @param nurseId The ID of the nurse.
     * @param dayId The ID of the day to check.
     * @return True if the nurse is working on that day; false otherwise.
     */
    bool isWorkingThisDay(unsigned int nurseId, unsigned int dayId) { return (solution->v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId] != -1); }

    /**
     * @brief Checks if the given day is either a Saturday or Sunday.
     *
     * @param dayId The day of the week represented as an integer.
     * @return true If `dayId` is a Saturday or Sunday.
     * @return false If `dayId` is neither.
     */
    bool isWeekendDay(int dayId) const
    {
        return (dayId >= 5 && (dayId + 2) % DAYS_IN_WEEK == 0) ||
            (dayId >= 6 && (dayId + 1) % DAYS_IN_WEEK == 0);
    }

    /**
     * @brief Checks if the given day is a Monday.
     *
     * @param dayId The day of the week represented as an integer.
     * @return True if the day is a Monday; false otherwise.
     */
    bool isMonday(int dayId) const
    {
        return (dayId > 0 && dayId % DAYS_IN_WEEK == 0);
    }

    /*****************************************************
    *             HARD CONDITION VERIFICATION            *
    *****************************************************/

    /**
     * @brief Checks if a nurse has a day off.
     *
     * @param nurseId The ID of the nurse.
     * @param dayId The ID of the day to check.
     * @return True if the nurse has the day off; false otherwise.
     */
    bool isOnDayOff(unsigned int nurseId, unsigned int dayId)
    {
        vector<int> nursesDaysOff = instance->get_vector_Personne_Id_Jour_Conges(nurseId);
        return binary_search(nursesDaysOff.begin(), nursesDaysOff.end(), dayId);
    }

    /**
     * @brief Checks if a nurse has reached the maximum number of consecutive worked days.
     *
     * @param nurseId The ID of the nurse.
     * @param actualDay The current day to check against.
     * @return True if the nurse has reached the maximum consecutive worked days; false otherwise.
     */
    bool isAtMaxConsecutiveWorkedDay(unsigned int nurseId, unsigned int actualDay);

    /**
     * @brief Checks if a nurse has exceeded the maximum total working time.
     *
     * @param nurseId The ID of the nurse.
     * @param shiftId The ID of the shift currently being considered.
     * @return True if the nurse has worked more minutes than the maximum allowed; false otherwise.
     */
    bool isAtMaxWorkedTime(unsigned int nurseId, unsigned int shiftId)
    {
        return ((schedulingData->nbMinuteWorked[nurseId] + instance->get_Shift_Duree(shiftId)) > instance->get_Personne_Duree_total_Max(nurseId));
    }

    /**
     * @brief Checks if a nurse has reached the maximum number of shifts for a specific shift type.
     *
     * @param nurseId The ID of the nurse.
     * @param shiftId The ID of the shift type to check.
     * @return True if the nurse has no remaining shifts to work for the specified shift; false otherwise.
     */
    bool isAtMaxWorkedShift(unsigned int nurseId, unsigned int shiftId) { return (schedulingData->maxShiftsPerType[nurseId][shiftId] == 0); }

    /**
     * @brief Checks if a nurse is at the end of the required consecutive days off.
     *
     * @param nurseId The unique identifier of the nurse.
     * @param actualDay The current day represented as an unsigned integer.
     * @return true If the nurse has met or exceeded the required consecutive days off.
     * @return false If the nurse has not met the required consecutive days off by actualDay.
     */
    bool isAtEndOfConsecutiveDayOff(unsigned int nurseId, unsigned int actualDay);

    /**
     * @brief Checks if the nurse is able to work this weekend.
     *
     * @param nurseId ID of the nurse to check.
     * @return True if the nurse can work this weekend, false otherwise.
     */
    bool isAbleToWorkThisWeekend(unsigned int nurseId)
    {
        return !(schedulingData->nbWeekendWorked[nurseId] >= instance->get_Personne_Nbre_WE_Max(nurseId));
    }

    /**
     * @brief Checks if a shift succession is forbidden for a nurse.
     *
     * @param previousShift ID of the previous shift worked by the nurse.
     * @param actualShift ID of the shift currently being considered.
     * @return True if the specified succession is forbidden, false otherwise.
     */
    bool isSuccessionForbidden(unsigned int previousShift, unsigned int actualShift)
    {
        vector<int> prohibitedShift = instance->get_vector_Shift_Suc_Interdit(actualShift);
        return binary_search(prohibitedShift.begin(), prohibitedShift.end(), previousShift);
    }

    /**
     * @brief Checks if a nurse has worked the required minimum number of consecutive days.
     *
     * @param nurseId The unique identifier of the nurse.
     * @param actualDay The current day for which the check is being performed.
     * @return true if the nurse has worked at least the minimum number of consecutive days, false otherwise.
     */
    bool haveDoneMinConsecutiveWorkedDay(unsigned int nurseId, unsigned int actualDay);

    /**
     * @brief Checks if a nurse has worked the required minimum total time.
     *
     * @param nurseId The unique identifier of the nurse.
     * @return true if the nurse has worked at least the minimum required time, false otherwise.
     */
    bool haveDoneMinWorkedTime(unsigned int nurseId) { return schedulingData->nbMinuteWorked[nurseId] >= instance->get_Personne_Duree_total_Min(nurseId); }
};

#endif
