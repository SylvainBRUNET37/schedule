#include "../../headers/validator/SolutionValidator.h"

#include <iostream>

/*****************************************************
*                OTHER VERIFICATION                  *
*****************************************************/

unsigned int SolutionValidator::getNbConstraintsViolatedOnDayOff(unsigned int nurseId, unsigned int dayId, unsigned int consecutiveWorkedShift)

{
    bool isFirstDayOff = false;
    unsigned int nbConstraintsViolated = 0;
    unsigned int nbMinConsecutiveWorkedShift = instance->get_Personne_Nbre_Shift_Consecutif_Min(nurseId);
    unsigned int nbMinConsecutiveDayOff = instance->get_Personne_Jour_OFF_Consecutif_Min(nurseId);

    // If the nurse has not reached the minimum number of consecutive worked days, increment the counter
    if ((consecutiveWorkedShift < nbMinConsecutiveWorkedShift) && (consecutiveWorkedShift != 0) && ((dayId - nbMinConsecutiveWorkedShift) >= 0))
        ++nbConstraintsViolated;

    // Verify if the past day is a day off
    if (dayId != 0)
        if (solution->v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId - 1] != -1)
            isFirstDayOff = true;

    // If it's the first consecutive day off of the nurse, check if the minimum number of consecutive days off is respected
    if (isFirstDayOff)
    {
        isFirstDayOff = false;
        for (unsigned int nextDayId = dayId; nextDayId < (dayId + nbMinConsecutiveDayOff); ++nextDayId)
        {
            if (nextDayId < solution->v_v_IdShift_Par_Personne_et_Jour[nurseId].size())
                if (solution->v_v_IdShift_Par_Personne_et_Jour[nurseId][nextDayId] != -1)
                {
                    ++nbConstraintsViolated;
                    break;
                }
        }
    }

    // Verify if the shift succession if forbiden
    if (dayId != (solution->v_v_IdShift_Par_Personne_et_Jour[nurseId].size() - 1))
        if ((solution->v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId] != -1) && (solution->v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId + 1] != -1))
            if (!instance->is_possible_Shift_Succede(solution->v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId], solution->v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId + 1]))
                ++nbConstraintsViolated;

    return nbConstraintsViolated;
}

unsigned int SolutionValidator::getNbConstraintsViolatedOnWorkedDay(unsigned int nurseId, unsigned int dayId, unsigned int consecutiveWorkedShift)
{
    unsigned int nbConstraintsViolated = 0;
    unsigned int nbMaxConsecutiveWorkedShift = instance->get_Personne_Nbre_Shift_Consecutif_Max(nurseId);

    // If the nurse has exceed the maximum number of consecutive worked days, increment the counter
    if (consecutiveWorkedShift > instance->get_Personne_Nbre_Shift_Consecutif_Max(nurseId))
        ++nbConstraintsViolated;

    // If the nurse is working on a day off, incrment the counter
    if (isOnDayOff(nurseId, dayId))
        ++nbConstraintsViolated;

    return nbConstraintsViolated;
}

unsigned int SolutionValidator::getNbContraintsViolatedWithData(unsigned int nurseId)

{
    unsigned int nbConstraintsViolated = 0;

    // Verify if the number of minutes worked by the nurse is within the allowed range
    if ((schedulingData->nbMinuteWorked[nurseId] > instance->get_Personne_Duree_total_Max(nurseId)) || (schedulingData->nbMinuteWorked[nurseId] < instance->get_Personne_Duree_total_Min(nurseId)))
        ++nbConstraintsViolated;

    // Verify the number of worked weekends by the nurse
    if (schedulingData->nbWeekendWorked[nurseId] > instance->get_Personne_Nbre_WE_Max(nurseId))
        ++nbConstraintsViolated;

    // Verify the number of shifts worked by the nurse
    for (unsigned int shiftId = 0; shiftId < instance->get_Nombre_Shift(); ++shiftId)
        if (schedulingData->shifts[shiftId] > instance->get_Personne_Shift_Nbre_Max(nurseId, shiftId))
            ++nbConstraintsViolated;

    return nbConstraintsViolated;
}

unsigned int SolutionValidator::getNbConstraintsViolatedForNurse(unsigned int nurseId)

{
    unsigned int nbConstraintsViolated = 0;
    unsigned int consecutiveWorkedShift = 0;
    unsigned int shiftId = 0;

    if (schedulingData == nullptr)
    {
        schedulingData = new NurseSchedulingData();
        schedulingData->initData(*instance);
    }

    unsigned int nbShift = instance->get_Nombre_Shift();
    unsigned int nbDay = instance->get_Nombre_Jour();

    for (unsigned int dayId = 0; dayId < nbDay; ++dayId)
    {
        if (solution->v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId] == -1)
        {
            nbConstraintsViolated += getNbConstraintsViolatedOnDayOff(nurseId, dayId, consecutiveWorkedShift);
            consecutiveWorkedShift = 0;
        }
        else
        {
            nbConstraintsViolated += getNbConstraintsViolatedOnWorkedDay(nurseId, dayId, consecutiveWorkedShift);

            shiftId = solution->v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId];

            // Update nb weekend worked
            if ((dayId % 7) == 5)
                schedulingData->nbWeekendWorked[nurseId] += 1;
            if (((dayId % 7) == 6) && (solution->v_v_IdShift_Par_Personne_et_Jour[nurseId][dayId - 1] == -1))
                schedulingData->nbWeekendWorked[nurseId] += 1;

            // Update nurse data
            schedulingData->maxShiftsPerType[nurseId][shiftId] -= 1;
            schedulingData->nbMinuteWorked[nurseId] += instance->get_Shift_Duree(shiftId);
            ++consecutiveWorkedShift;
        }
    }

    nbConstraintsViolated += getNbContraintsViolatedWithData(nurseId);

    return nbConstraintsViolated;
}

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

    if (actualDay == 0)
        return true;

    unsigned int nbConsecutiveDayOff = 0;
	int dayId = actualDay - 1;
    int endDay = actualDay - minConsecutiveDaysOff;

    while (dayId >= endDay && dayId >= 0 && !isWorkingThisDay(nurseId, dayId))
    {
        ++nbConsecutiveDayOff;
        --dayId;
    }

    if (nbConsecutiveDayOff != 0 && nbConsecutiveDayOff < minConsecutiveDaysOff)
        return false;		

    return true;
}

bool SolutionValidator::haveDoneMinConsecutiveWorkedDay(unsigned int nurseId, unsigned int actualDay)
{
    unsigned int minConsecutiveWorkedDay = instance->get_Personne_Nbre_Shift_Consecutif_Min(nurseId);

    if (actualDay < minConsecutiveWorkedDay || !isWorkingThisDay(nurseId, actualDay - 1))
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
