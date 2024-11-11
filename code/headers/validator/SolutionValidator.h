#ifndef SOLUTION_VALIDATOR_H
#define SOLUTION_VALIDATOR_H

#include <algorithm>

#include "../solution/Instance.hpp"
#include "../solution/Solution.hpp"
#include "../solution/NurseSchedulingData.h"

class SolutionValidator
{
private:
	const unsigned int DAYS_IN_WEEK = 7; ///< Number of days in a week.

	Instance& instance;
	Solution& solution;
	NurseSchedulingData& schedulingData;

public:
	/*****************************************************
	*              CONTRUCTORS / DESTRUCTOR              *
	*****************************************************/

	SolutionValidator(Instance& instance, Solution& solution, NurseSchedulingData schedulingData) : instance(instance), solution(solution), schedulingData(schedulingData) {}

	/*****************************************************
	*                 GLOBAL VERIFICATION                *
	*****************************************************/

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
	bool isWorkingThisDay(unsigned int nurseId, unsigned int dayId) { return (solution.v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId] != -1); }

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
		vector<int> nursesDaysOff = instance.get_vector_Personne_Id_Jour_Conges(nurseId);
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
	bool isAtMaxWorkedTime(unsigned int nurseId) { return (schedulingData.nbMinuteWorked[nurseId] > instance.get_Personne_Duree_total_Max(nurseId)); }

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
	bool isAtMaxWorkedShift(unsigned int nurseId, unsigned int shiftId) { return (schedulingData.maxShiftsPerType[nurseId][shiftId] == 0); }

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
	 * @param actualDay The current day in the scheduling instance.
	 *
	 * @return True if the nurse can work this weekend, false otherwise.
	 *
	 * This function verifies whether the nurse has reached the maximum allowed number of worked weekends.
	 */
	bool isAbleToWorkThisWeekend(unsigned int nurseId)
	{
		return !(schedulingData.nbWeekendWorked[nurseId] >= instance.get_Personne_Nbre_WE_Max(nurseId));
	}

	/**
	 * @brief Checks if the nurse is able to work this weekend.
	 *
	 * @param nurseId ID of the nurse to check.
	 * @param actualDay The current day in the scheduling instance.
	 *
	 * @return True if the nurse can work this weekend, false otherwise.
	 *
	 * This function verifies whether the nurse has reached the maximum allowed number of worked weekends.
	 */
	bool isSuccessionForbidden(unsigned int previousShift, unsigned int actualShift)
	{
		vector<int> prohibitedShift = instance.get_vector_Shift_Suc_Interdit(actualShift);
		return binary_search(prohibitedShift.begin(), prohibitedShift.end(), previousShift);
	}
};

#endif
