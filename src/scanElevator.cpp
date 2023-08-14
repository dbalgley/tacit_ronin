#include "scanElevator.h"

/**
 * Constructor for ScanElevator.
 * @param startFloor: The floor the elevator starts on.
 * @param floors: The total number of floors.
 * @param travelTime: Time taken to travel between floors.
 * @param actuateTime: Time taken to open/close doors.
 * @param loadTime: Time taken for passengers to enter/exit.
 */
ScanElevator::ScanElevator(int startFloor, int floors, double travelTime, double actuateTime, double loadTime)
    : Elevator(startFloor, floors, travelTime, actuateTime, loadTime), goingUp(true) {}

/**
 * Request the elevator to stop at a specific floor.
 * @param floor: The floor to stop at.
 */
void ScanElevator::requestFloor(int floor) {
    if (floor == currentFloor) return;

    if (floor > currentFloor) {
        upRequests.insert(floor);
    } else {
        downRequests.insert(floor);
    }
}

/**
 * Check if a specific floor is in the requested floors list.
 * @param requests: The set of requested floors.
 * @param floor: The floor to check.
 * @return true if the floor is requested, false otherwise.
 */
bool ScanElevator::isFloorRequested(const std::set<int>& requests, int floor) const {
    return requests.find(floor) != requests.end();
}

/**
 * Update the elevator's status and position for each "tick".
 */
void ScanElevator::tick() {
    if ((upRequests.empty() && downRequests.empty()) && status == ElevatorStatus::DOORS_CLOSE) {
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

    if (goingUp) {
        if (upRequests.empty()) {
            goingUp = false;
            moveDown();
        } else {
            moveUp();
            if (isFloorRequested(upRequests, currentFloor)) {
                upRequests.erase(currentFloor);

                updateTotalTravelTime();

                status = ElevatorStatus::DOORS_OPEN;

                return;
            }
        }
    } else {
        if (downRequests.empty()) {
            goingUp = true;
            moveUp();
        } else {
            moveDown();
            if (isFloorRequested(downRequests, currentFloor)) {
                downRequests.erase(currentFloor);

                updateTotalTravelTime();

                status = ElevatorStatus::DOORS_OPEN;

                return;
            }
        }
    }
}