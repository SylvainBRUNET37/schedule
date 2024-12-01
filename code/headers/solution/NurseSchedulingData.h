#ifndef NURSE_SCHEDULING_DATA_H
#define NURSE_SCHEDULING_DATA_H

#include "Instance.hpp"

/**
 * @class NurseSchedulingData
 * @brief This class stores and manages the data related to nurse scheduling.
 *
 * It contains various vectors that represent the scheduling data, including the nurses, shifts, days, and the
 * number of nurses needed for each shift. It also manages the constraints on the maximum shifts a nurse can
 * work per shift type, and the total minutes and weekends worked by each nurse. This data is used to initialize
 * and track the scheduling system.
 */
class NurseSchedulingData
{
private:

public:
    /*****************************************************
    *                STORAGE INITIALISATION              *
    *****************************************************/

    /**
	 * @brief Initializes the scheduling data for nurses.
	 *
	 * This function sets up the necessary data structures for the nurse scheduling system by resizing vectors
	 * for storing nurse, shift, and day data, and initializing constraints for each nurse's shift assignments.
	 *
	 * @param instance The instance containing the relevant data, such as the number of nurses, shifts, and days.
	 */
	void initData(Instance& instance);

    /*****************************************************
    *                     NURSE DATA                     *
    *****************************************************/
	
	// Public attributes for faster and easier access to the data

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
