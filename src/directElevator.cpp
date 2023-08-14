#include "directElevator.h"

/**
 * @brief Construct a new Direct Elevator object.
 * 
 * @param startFloor The starting floor of the elevator.
 * @param floors Total number of floors the elevator can access.
 * @param travelTime Time taken to travel between floors.
 * @param actuateTime Time for door actuation (open/close).
 * @param loadTime Time for loading/unloading passengers.
 */
DirectElevator::DirectElevator(int startFloor, int floors, double travelTime, double actuateTime, double loadTime)
    : Elevator(startFloor, floors, travelTime, actuateTime, loadTime) {}

/**
 * @brief Request the elevator to move to a specific floor.
 * 
 * If the floor is invalid (outside the range of floors, or is the current floor), it prints an error.
 * 
 * @param floor The floor number to move to.
 */
void DirectElevator::requestFloor(int floor) {
    if (floor >= 1 && floor <= totalFloors && floor != currentFloor) {
        floorRequests.push_back(floor);
    } else {
        std::cout << "Invalid floor requested: " << floor << std::endl;
    }
}

/**
 * @brief A simulation tick for the DirectElevator.
 * 
 * This function simulates one time unit for the elevator's operations, such as moving between floors, 
 * opening/closing doors, or loading passengers.
 */
void DirectElevator::tick() {
    if (floorRequests.empty() && status == ElevatorStatus::DOORS_CLOSE) {
        status = ElevatorStatus::IDLE;
        return;
    }

    if (status == ElevatorStatus::DOORS_OPEN) {
        status = ElevatorStatus::LOADING;
        return;
    }

    if (status == ElevatorStatus::LOADING) {
        status = ElevatorStatus::DOORS_CLOSE;
        return;
    }

    int nextFloor = floorRequests.front();

    if (currentFloor < nextFloor) {
        moveUp();
    } else {
        moveDown();
    }

    if (currentFloor == nextFloor) {
        status = ElevatorStatus::DOORS_OPEN;
        floorRequests.pop_front();

        return;
    }
}