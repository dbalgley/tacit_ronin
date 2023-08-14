#pragma once

#include <set>
#include "elevator.h"

/**
 * @brief Implements the SCAN scheduling algorithm for an elevator.
 * 
 * The ScanElevator class extends the Elevator base class to provide a SCAN algorithm behavior.
 * The SCAN algorithm moves the elevator towards the highest floor requested until it has no more requests in 
 * that direction, at which point it reverses direction.
 */
class ScanElevator : public Elevator {
    private:
        std::set<int> upRequests;       ///< Set of floor requests in the upwards direction.
        std::set<int> downRequests;     ///< Set of floor requests in the downwards direction.
        bool goingUp;                   ///< Flag indicating the current direction of the elevator.

        /**
         * @brief Checks if a floor is in a set of requests.
         * @param requests A set of requested floors.
         * @param floor The floor to check.
         * @return True if the floor is requested, otherwise false.
         */
        bool isFloorRequested(const std::set<int>& requests, int floor) const;

    public:
        /**
         * @brief Constructs a ScanElevator object.
         * @param startFloor The initial floor of the elevator.
         * @param floors The total number of floors in the building.
         * @param travelTime Time taken to travel between floors.
         * @param actuateTime Time taken to open/close doors.
         * @param loadTime Time taken to load/unload passengers.
         */
        ScanElevator(int startFloor, int floors, double travelTime, double actuateTime, double loadTime);

        /**
         * @brief Request the elevator to visit a floor.
         * @param floor The floor to be visited.
         */
        void requestFloor(int floor) override;

        /**
         * @brief Advances the state of the elevator by one time unit.
         */
        void tick() override;
};