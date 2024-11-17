#include "../../headers/validator/SolutionValidator.h"

#include <iostream>

/*****************************************************
*             HARD CONDITION VERIFICATION            *
*****************************************************/

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

    // If the nurse was working yesterday, return true
    if (isWorkingThisDay(nurseId, actualDay - 1))
        return true;

    // Iterate over the days preceding 'actualDay' to check if the nurse had the required consecutive days off
    unsigned int startDay = actualDay - minConsecutiveDaysOff;

    for (unsigned int dayId = startDay; dayId < actualDay; ++dayId)
    {
        // Increment the counter if the nurse is not working on the current day
        if (isWorkingThisDay(nurseId, dayId))
            return false;
    }

    return true; // Return false if the nurse does not have the required consecutive days off by 'actualDay'
}

bool SolutionValidator::haveDoneMinConsecutiveWorkedDay(unsigned int nurseId, unsigned int actualDay)
{
    unsigned int minConsecutiveWorkedDay = instance.get_Personne_Nbre_Shift_Consecutif_Min(nurseId);

    if (actualDay < minConsecutiveWorkedDay)
        return false;

	// If the nurse wasn't working yesterday, return true
    if (!isWorkingThisDay(nurseId, actualDay - 1))
        return true;

    // Iterate over the days preceding 'actualDay' to check if the nurse had the required consecutive worked day
    unsigned int startDay = actualDay - minConsecutiveWorkedDay;
    for (unsigned int dayId = startDay; dayId < actualDay; ++dayId)
    {
        // 
        if (!isWorkingThisDay(nurseId, dayId))
            return false;
    }

    return true; // 
}