#include "directElevator.h"

DirectElevator::DirectElevator(int startFloor, int floors, double travelTime, double actuateTime, double loadTime) : Elevator(startFloor, floors, travelTime, actuateTime, loadTime) {}

void DirectElevator::requestFloor(int floor) {
    if (floor >= 1 && floor <= totalFloors && floor != currentFloor) {
        floorRequests.push_back(floor);
    } else {
        std::cout << "Invalid floor requested: " << floor << std::endl;
    }
}

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