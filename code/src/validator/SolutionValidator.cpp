#include "../../headers/validator/SolutionValidator.h"

/*****************************************************
*                 GLOBAL VERIFICATION                *
*****************************************************/

// in header file

/*****************************************************
*             HARD CONDITION VERIFICATION            *
*****************************************************/

bool SolutionValidator::isAvailableThisDay(unsigned int nurseId, unsigned int dayId)
{
    // Early exit if the nurse is on a day off
    if (isOnDayOff(nurseId, dayId)) return false;  // High frequency

    // Early exit if at the end of consecutive days off
    if (!isAtEndOfConsecutiveDayOff(nurseId, dayId)) return false;  // Medium frequency

    // Check if the day is a weekend and if the nurse can work this weekend
    if (isWeekendDay(dayId) && isAbleToWorkThisWeekend(nurseId)) return false; // Low to Medium frequency

    // Check if the nurse has reached the max worked time
    if (isAtMaxWorkedTime(nurseId)) return false;  // Medium frequency

    // Check if at max consecutive worked days
    if (isAtMaxConsecutiveWorkedDay(nurseId, dayId)) return false;  // Medium frequency

    return true;
}

bool SolutionValidator::isAvailableForShift(unsigned int nurseId, unsigned int dayId, unsigned int shiftId)
{
    // Check if it's not the first day and if the nurse worked the previous day
    if (dayId != 0 && isWorkingThisDay(nurseId, dayId - 1))
        if (isSuccessionForbidden(shiftId, solution.v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId - 1])) return false;  // Medium frequency

    // Check for the specific shift type's limits
    return !isAtMaxWorkedShift(nurseId, shiftId);  // Low frequency, return true if not at max
}

bool SolutionValidator::isAtMaxConsecutiveWorkedDay(unsigned int nurseId, unsigned int actualDay)
{
    // Get the maximum number of consecutive shifts that the nurse can work
    unsigned int maxConsecutiveShift = instance.get_Personne_Nbre_Shift_Consecutif_Max(nurseId);
    // Calculate the starting day to check for consecutive work shifts
    unsigned int startDay = actualDay - maxConsecutiveShift;

    unsigned int nbShiftWorkedConsecutive = 0;
    // Iterate over the range of days from 'startDay' to 'actualDay'
    for (unsigned int dayId = startDay; dayId < actualDay; ++dayId)
    {
        // Increment the counter if the nurse is working on this day
        if (isWorkingThisDay(nurseId, dayId))
            ++nbShiftWorkedConsecutive;

        // If the nurse has worked the maximum allowed consecutive shifts, return true
        if (nbShiftWorkedConsecutive == maxConsecutiveShift)
            return true;
    }

    // Return false if the nurse has not reached the maximum number of consecutive worked days
    return false;
}

bool SolutionValidator::isAtEndOfConsecutiveDayOff(unsigned int nurseId, unsigned int actualDay)
{
    // Get the minimum number of consecutive days off required for the nurse
    unsigned int minConsecutiveDaysOff = instance.get_Personne_Jour_OFF_Consecutif_Min(nurseId);

    // Check if the current day is less than the minimum required consecutive days off
    if (actualDay < minConsecutiveDaysOff)
        return true; // Return true, indicating that the requirement for consecutive days off is met

    unsigned int nbConsecutiveDayOff = 0; // Counter for the number of consecutive days off

    // Iterate over the days preceding 'actualDay' to check if the nurse had the required consecutive days off
    unsigned int startDay = actualDay - minConsecutiveDaysOff;
    for (unsigned int dayId = startDay; dayId < actualDay; ++dayId)
    {
        // Increment the counter if the nurse is not working on the current day
        if (!isWorkingThisDay(nurseId, dayId))
            ++nbConsecutiveDayOff;

        // If the nurse has the required number of consecutive days off, return true
        if (nbConsecutiveDayOff == minConsecutiveDaysOff)
            return true;
    }

    return false; // Return false if the nurse does not have the required consecutive days off by 'actualDay'
}

