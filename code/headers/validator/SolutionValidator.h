#ifndef SOLUTION_VALIDATOR_H
#define SOLUTION_VALIDATOR_H

#include <algorithm>
#include <iostream>

#include "../solution/Instance.hpp"
#include "../solution/Solution.hpp"
#include "../solution/NurseSchedulingData.h"

class SolutionValidator
{
private:
	const unsigned int DAYS_IN_WEEK = 7; ///< Number of days in a week.

	Instance* instance;
	Solution* solution;
	NurseSchedulingData* schedulingData;

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
		: instance(instance), solution(solution), schedulingData(schedulingData) {}

	SolutionValidator(Instance* instance)
		: instance(instance), solution(nullptr), schedulingData(nullptr) {}

	void setInstance(Instance* newInstance) {
		instance = newInstance;
	}

	// Setter pour solution
	void setSolution(Solution* newSolution) {
		solution = newSolution;
	}

	// Setter pour schedulingData
	void setSchedulingData(NurseSchedulingData* newSchedulingData) {
		schedulingData = newSchedulingData;
	}

	/*****************************************************
	*                  OTHER VERIFICATION                *
	*****************************************************/

	unsigned int getNbConstraintsViolatedOnDayOff(unsigned int nurseId, unsigned int dayId, unsigned int consecutiveWorkedShift);

	unsigned int getNbConstraintsViolatedOnWorkedDay(unsigned int nurseId, unsigned int dayId, unsigned int consecutiveWorkedShift);

	unsigned int getNbContraintsViolatedWithData(unsigned int nurseId);

	/*****************************************************
	*                 GLOBAL VERIFICATION                *
	*****************************************************/

	unsigned int getNbConstraintsViolatedForNurse(unsigned int nurseId);

	/**
	 * @brief Checks if a nurse is scheduled to work on a specific day.
	 *
	 * @param nurseId The ID of the nurse.
	 * @param dayId The ID of the day to check.
	 *
	 * @return True if the nurse is working on that day; false otherwise.
	 *
	 * This method verifies if the nurse's shift for the specified day is not marked as -1,
	 * which indicates that they are not assigned to work.
	 */
	bool isWorkingThisDay(unsigned int nurseId, unsigned int dayId) { return (solution->v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId] != -1); }

	/**
	 * @brief Checks if the given day is either a Saturday or Sunday.
	 *
	 * @param dayId The day of the week represented as an integer.
	 *
	 * @return true If `dayId` is a Saturday or Sunday.
	 * @return false If `dayId` is neither.
	 *
	 * This function determines if the specified day, represented by the integer `dayId`,
	 * corresponds to a Saturday or Sunday based on the defined sequences:
	 * - Saturdays: 5, 12, 19, 26, ...
	 * - Sundays: 6, 13, 20, 27, ...
	 */
	bool isWeekendDay(int dayId) const
	{
		return (dayId >= 5 && (dayId + 2) % DAYS_IN_WEEK == 0) ||
			(dayId >= 6 && (dayId + 1) % DAYS_IN_WEEK == 0);
	}

	/*****************************************************
	*             HARD CONDITION VERIFICATION            *
	*****************************************************/

	/**
	 * @brief Checks if a nurse has a day off.
	 *
	 * @param nurseId The ID of the nurse.
	 * @param dayId The ID of the day to check.
	 *
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
	 *
	 * @return True if the nurse has reached the maximum consecutive worked days; false otherwise.
	 *
	 * This method counts the number of consecutive days the nurse has worked leading up to
	 * the actual day and checks if it exceeds the allowed maximum.
	 */
	bool isAtMaxConsecutiveWorkedDay(unsigned int nurseId, unsigned int actualDay);

	/**
	 * @brief Checks if a nurse has exceeded the maximum total working time.
	 *
	 * @param nurseId The ID of the nurse.
	 *
	 * @return True if the nurse has worked more minutes than the maximum allowed; false otherwise.
	 *
	 * This method checks the total minutes worked by the nurse against their maximum allowed working time.
	 */
	bool isAtMaxWorkedTime(unsigned int nurseId) { return (schedulingData->nbMinuteWorked[nurseId] > instance->get_Personne_Duree_total_Max(nurseId)); }

	/**
	 * @brief Checks if a nurse has reached the maximum number of shifts for a specific shift type.
	 *
	 * @param nurseId The ID of the nurse.
	 * @param shiftId The ID of the shift type to check.
	 *
	 * @return True if the nurse has no remaining shifts to work for the specified shift; false otherwise.
	 *
	 * This method checks the number of shifts left for a specific shift type for the nurse
	 * to determine if they have met their maximum allocation.
	 */
	bool isAtMaxWorkedShift(unsigned int nurseId, unsigned int shiftId) { return (schedulingData->maxShiftsPerType[nurseId][shiftId] == 0); }

	/**
	 * @brief Checks if a nurse is at the end of the required consecutive days off.
	 *
	 * @param nurseId The unique identifier of the nurse.
	 * @param actualDay The current day represented as an unsigned integer.
	 *
	 * @return true If the nurse has met or exceeded the required consecutive days off.
	 * @return false If the nurse has not met the required consecutive days off by actualDay.
	 *
	 * This function determines if the nurse has reached the end of the minimum
	 * number of consecutive days off required. It checks the days leading up to
	 * the specified actual day and counts how many consecutive days off the nurse has had.
	 */
	bool isAtEndOfConsecutiveDayOff(unsigned int nurseId, unsigned int actualDay);

	/**
	 * @brief Checks if the nurse is able to work this weekend.
	 *
	 * @param nurseId ID of the nurse to check.
	 *
	 * @return True if the nurse can work this weekend, false otherwise.
	 *
	 * This function verifies whether the nurse has reached the maximum allowed number of worked weekends.
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
	 *
	 * @return True if the specified succession is forbidden, false otherwise.
	 *
	 * This function verifies if a shift succession is restricted based on predefined rules for
	 * consecutive shifts, to prevent certain sequences that may violate scheduling constraints.
	 */
	bool isSuccessionForbidden(unsigned int previousShift, unsigned int actualShift)
	{
		vector<int> prohibitedShift = instance->get_vector_Shift_Suc_Interdit(actualShift);
		return binary_search(prohibitedShift.begin(), prohibitedShift.end(), previousShift);
	}

	/**
	 * @brief Checks if a nurse has worked the required minimum number of consecutive days.
	 *
	 * This method determines whether a nurse has fulfilled the minimum consecutive workday
	 * requirement by evaluating the nurse's work schedule for the days preceding a specified day.
	 *
	 * @param nurseId The unique identifier of the nurse.
	 * @param actualDay The current day for which the check is being performed.
	 *
	 * @return `true` if the nurse has worked at least the minimum number of consecutive days, `false` otherwise.
	 *
	 * @note This function assumes that the method `isWorkingThisDay` correctly determines whether
	 *       the nurse worked on a specific day and that the schedule data is accessible and accurate.
	 */
	bool haveDoneMinConsecutiveWorkedDay(unsigned int nurseId, unsigned int actualDay);

	/**
	 * @brief Checks if a nurse has worked the required minimum total time.
	 *
	 * This method evaluates whether a nurse has accumulated the minimum required working time
	 * in minutes, as specified for the nurse in the instance data.
	 *
	 * @param nurseId The unique identifier of the nurse.
	 *
	 * @return `true` if the nurse has worked at least the minimum required time, `false` otherwise.
	 *
	 * @note This function uses the `schedulingData->nbMinuteWorked` array for tracking worked minutes
	 *       and the `instance->get_Personne_Duree_total_Min` method to retrieve the minimum time requirement.
	 */
	bool haveDoneMinWorkedTime(unsigned int nurseId) { return schedulingData->nbMinuteWorked[nurseId] >= instance->get_Personne_Duree_total_Min(nurseId); }
};

#endif
