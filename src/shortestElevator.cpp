#include "shortestElevator.h"

ShortestElevator::ShortestElevator(int startFloor, int floors) : Elevator(startFloor, floors) {}

void ShortestElevator::requestFloor(int floor) {
    if (floor >= 1 && floor <= totalFloors && floor != currentFloor) {
        floorRequests.insert(floor);
    } else {
        std::cerr << "Invalid Floor Requested: " << floor << std::endl;
    }
}

void ShortestElevator::tick() {
    if (floorRequests.empty()) {
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

    findNextFloor();

    if (currentFloor < nextFloor) {
        moveUp();
    } else if (currentFloor > nextFloor) {
        moveDown();
    } else {
        // The elevator is on the requested floor
        status = ElevatorStatus::DOORS_OPEN;
        floorRequests.erase(currentFloor);

        return;
    }
}

void ShortestElevator::findNextFloor() {
    // "max" value initialization
    int minDistance = totalFloors;
    int closestFloor = currentFloor;

    for (const int& floor: floorRequests) {
        int distance = std::abs(currentFloor - floor);
        if (distance < minDistance) {
            minDistance = distance;
            closestFloor = floor;
        }
    }

    nextFloor = closestFloor;
}