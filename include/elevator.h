#pragma once

#include <iostream>
#include <deque>
#include <vector>

#include "elevatorStatus.h"

/**
 * @brief Abstract base class for different elevator algorithms.
 */
class Elevator {
    protected:
        int currentFloor;                       ///< Current floor of the elevator.
        int totalFloors;                        ///< Total floors in the building.
        ElevatorStatus status;                  ///< Current status of the elevator (IDLE, MOVING, etc.)
        double totalTravelTime = 0;             ///< Total travel time.
        std::vector<int> floorsVisited;         ///< Vector of floors that elevator has visited.

        const double floorTravelTime = 10.0;    ///< Time taken to travel between floors.
        const double doorsTime = 0.0;           ///< Time taken for doors to open/close.
        const double loadingTime = 0.0;         ///< Time taken for loading/unloading passengers.

    public:
        /**
         * @brief Construct a new Elevator object.
         * 
         * @param startFloor Initial floor of the elevator.
         * @param floors Total number of floors in the building.
         * @param travelTime Time taken to travel between floors.
         * @param actuateTime Time taken for doors to open/close.
         * @param loadTime Time taken for loading/unloading passengers.
         */
        Elevator(int startFloor = 1, int floors = 10, double travelTime = 10.0, double actuateTime = 0.0, double loadTime = 0.0);

        /**
         * @brief Request the elevator to stop at a specific floor. To be implemented by derived classes.
         * 
         * @param floor Floor to stop at.
         */
        virtual void requestFloor(int floor) = 0;

        /**
         * @brief Update the elevator's state each tick. To be implemented by derived classes.
         */
        virtual void tick() = 0;

        void moveUp();      ///< Move the elevator up by one floor.
        void moveDown();    ///< Move the elevator down by one floor.

        /**
         * @brief Update the total travel time of the elevator.
         * This function is used to accumulate the time as the elevator moves, loads/unloads, and actuates its doors.
         */
        void updateTotalTravelTime();

        /**
         * @brief Get the current floor where the elevator is located.
         * 
         * @return int Current floor number.
         */
        int getCurrentFloor() const;

        /**
         * @brief Get the time taken to travel between floors.
         * 
         * @return double Time in seconds for elevator to travel between two adjacent floors.
         */
        ElevatorStatus getStatus() const;

        /**
         * @brief Get the time taken to travel between floors.
         * 
         * @return double Time in seconds for elevator to travel between two adjacent floors.
         */
        double getFloorTravelTime() const;

        /**
         * @brief Get the time taken for the elevator doors to open or close.
         * 
         * @return double Time in seconds for elevator doors to actuate.
         */
        double getDoorsTime() const;

        /**
         * @brief Get the time taken for passengers to load or unload from the elevator.
         * 
         * @return double Time in seconds for passenger loading or unloading.
         */
        double getLoadingTime() const;

        /**
         * @brief Get the total accumulated travel time of the elevator since it started.
         * 
         * @return double Total time in seconds that the elevator has been active.
         */
        double getTotalTravelTime() const;

        /**
         * @brief Display or log the results of the elevator's operations.
         * This function can be used for debugging, reporting, or analytics.
         */
        void outputResults();
};