#ifndef NURSE_SCHEDULING_DATA_H
#define NURSE_SCHEDULING_DATA_H

#include <vector>

using namespace std;

class NurseSchedulingData
{
private:

public:
	
	// Attributs en public pour les chercher plus vite et pas se faire chier a utiliser des getters et des setters et autres conneries
	vector<unsigned int> nurses; ///< IDs of all nurses.
	vector<unsigned int> shifts; ///< IDs of all shift types.
	vector<vector<unsigned int>> maxShiftsPerType; ///< Maximum shifts allowed per type for each nurse [nurseId][shiftId] (to decrement).
	vector<unsigned int> nbMinuteWorked; ///< Total minutes worked by each nurse [nurseId] (to increment).
	vector<unsigned int> nbWeekendWorked; ///< Total weekends worked by each nurse [nurseId] (to increment).
	vector<int> missingNursePerDay; ///< Nurses needed per day [dayId] (to decrement).
	vector<vector<int>> missingNursePerShift; ///< Nurses needed per shift for each day [dayId][shiftId] (to decrement).
};

#endif
