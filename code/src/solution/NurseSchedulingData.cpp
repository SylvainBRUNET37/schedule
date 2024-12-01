#include "../../headers/solution/NurseSchedulingData.h"

void NurseSchedulingData::initData(Instance& instance)
{
    unsigned int nbNurse = instance.get_Nombre_Personne();
    unsigned int nbShift = instance.get_Nombre_Shift();
    unsigned int nbDay = instance.get_Nombre_Jour();

    // Resize vectors that contains every nurse id to the number of nurse
    nurses.resize(nbNurse, 0);
    nbMinuteWorked.resize(nbNurse, 0);
    nbWeekendWorked.resize(nbNurse, 0);
    maxShiftsPerType.resize(nbNurse, vector<unsigned int>(nbShift, 0));

    // Resize shift and day vector
    shifts.resize(nbShift, 0);
    days.resize(nbDay, 0);

    // Initialize shift ids
    for (unsigned int shiftId = 0; shiftId < nbShift; ++shiftId)
        shifts[shiftId] = shiftId;

    // Initialize data structures for tracking the work assignments for each nurse
    for (unsigned int nurseId = 0; nurseId < nbNurse; ++nurseId)
    {
        // Fill the vector that contains every nurse id
        nurses[nurseId] = nurseId;

        // Initialize maximum shifts for each nurse per shift type
        for (unsigned int shiftId = 0; shiftId < nbShift; ++shiftId)
            maxShiftsPerType[nurseId][shiftId] = instance.get_Personne_Shift_Nbre_Max(nurseId, shiftId);
    }
}