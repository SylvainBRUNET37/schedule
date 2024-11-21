#ifndef NURSE_SCHEDULING_DATA_H
#define NURSE_SCHEDULING_DATA_H

#include "Instance.hpp"

class NurseSchedulingData
{
private:

public:
    /*****************************************************
    *                STORAGE INITIALISATION              *
    *****************************************************/

    void initData(Instance& instance)
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

    /*****************************************************
    *                     NURSE DATA                     *
    *****************************************************/
	
	// Attributs en public pour les chercher plus vite et pas se faire chier a utiliser des getters et des setters et autres conneries
	vector<unsigned int> nurses; ///< IDs of all nurses.
    vector<unsigned int> days; ///< IDs of all days.
	vector<unsigned int> shifts; ///< IDs of all shift types.
	vector<vector<unsigned int>> maxShiftsPerType; ///< Maximum shifts allowed per type for each nurse [nurseId][shiftId] (to decrement).
	vector<unsigned int> nbMinuteWorked; ///< Total minutes worked by each nurse [nurseId] (to increment).
	vector<unsigned int> nbWeekendWorked; ///< Total weekends worked by each nurse [nurseId] (to increment).
	vector<int> missingNursePerDay; ///< Nurses needed per day [dayId] (to decrement).
	vector<vector<int>> missingNursePerShift; ///< Nurses needed per shift for each day [dayId][shiftId] (to decrement).
};

#endif
