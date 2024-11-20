#include "../../headers/validator/SolutionValidator.h"

#include <iostream>

/*****************************************************
*             HARD CONDITION VERIFICATION            *
*****************************************************/

bool SolutionValidator::isAtMaxConsecutiveWorkedDay(unsigned int nurseId, unsigned int actualDay)
{
    // Get the maximum number of consecutive shifts that the nurse can work
    unsigned int maxConsecutiveShift = instance->get_Personne_Nbre_Shift_Consecutif_Max(nurseId);
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
    unsigned int minConsecutiveDaysOff = instance->get_Personne_Jour_OFF_Consecutif_Min(nurseId);

    if (actualDay < minConsecutiveDaysOff)
        return true;

    unsigned int nbConsecutiveDayOff = 0;
	int dayId = actualDay - 1;
    int endDay = actualDay - minConsecutiveDaysOff;

    while (dayId >= endDay && !isWorkingThisDay(nurseId, dayId))
    {
        ++nbConsecutiveDayOff;
        --dayId;
    }

    if (nbConsecutiveDayOff != 0 && nbConsecutiveDayOff <= minConsecutiveDaysOff - 1)
        return false;		

    return true;
}

bool SolutionValidator::haveDoneMinConsecutiveWorkedDay(unsigned int nurseId, unsigned int actualDay)
{
    unsigned int minConsecutiveWorkedDay = instance->get_Personne_Nbre_Shift_Consecutif_Min(nurseId);

    if (actualDay < minConsecutiveWorkedDay)
        return true;

    unsigned int nbConsecutiveWorkedDay = 0;
    int endDay = actualDay - minConsecutiveWorkedDay;
    int dayId = actualDay - 1;

    while (dayId >= endDay && isWorkingThisDay(nurseId, dayId))
    {
        ++nbConsecutiveWorkedDay;
        --dayId;
    }

    if (nbConsecutiveWorkedDay != 0 && nbConsecutiveWorkedDay <= minConsecutiveWorkedDay - 1)
        return false;
        
    return true;
}
