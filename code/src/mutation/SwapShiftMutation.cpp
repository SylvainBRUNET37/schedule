#include "../../headers/mutation/SwapShiftMutation.h"

#include <random>

void SwapShiftMutation::execute(Solution& solution)
{
    // Generate a random number to select a nurse
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> nurseDistribution(0, solution.v_v_IdShift_Par_Personne_et_Jour.size() - 1);
    int randomNurseId = nurseDistribution(gen);

    // Get the nurse's assignments
    vector<int>& nurseAssignments = solution.v_v_IdShift_Par_Personne_et_Jour[randomNurseId];

    // Generate a random number to select a shift
    uniform_int_distribution<> shiftDistribution(0, nurseAssignments.size() - 1);
    int shiftId1 = 0;
    int shiftId2 = 0;

    // Find the first shift assigned to the nurse
    shiftId1 = shiftDistribution(gen);

    // Find the second shift assigned to the nurse
    shiftId2 = shiftDistribution(gen);

    // Swap the shifts
    swap(nurseAssignments[shiftId1], nurseAssignments[shiftId2]);
}