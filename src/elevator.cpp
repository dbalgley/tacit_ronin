#include "elevator.h"

#include "elevatorMode.h"
#include "elevatorStatus.h"

Elevator::Elevator(int startFloor, int floors, ElevatorMode mode) : currentFloor(1), totalFloors(floors), opMode(mode), status(ElevatorStatus::IDLE) {
    currentFloor = startFloor;
}

void Elevator::moveUp() {
    if(currentFloor < totalFloors) {
        currentFloor++;
        status = ElevatorStatus::MOVING_UP;
    } else {
        status = ElevatorStatus::IDLE;
    }
}

void Elevator::moveDown() {
    if(currentFloor > 1) {
        currentFloor--;
        status = ElevatorStatus::MOVING_DOWN;
    } else {
        status = ElevatorStatus::IDLE;
    }
}

void Elevator::requestFloor(int floor) {
    if (floor >= 1 && floor <= totalFloors && floor != currentFloor) {
        floorRequests.push_back(floor);
    } else {
        std::cerr << "Invalid floor requested: " << floor << std::endl;
    }
}

void Elevator::tick() {
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

    int nextFloor = floorRequests.front();

    if (currentFloor == nextFloor) {
        status = ElevatorStatus::DOORS_OPEN;
        floorRequests.pop_front();

        return;
    }

    if (currentFloor < nextFloor) {
        moveUp();
    } else {
        moveDown();
    }
}

int Elevator::getCurrentFloor() const {
    return currentFloor;
}

ElevatorStatus Elevator::getStatus() const {
    return status;
}

ElevatorMode Elevator::getOpMode() const {
    return opMode;
}

double Elevator::getFloorTravelTime() const {
    return floorTravelTime;
}

double Elevator::getDoorsTime() const {
    return doorsTime;
}

double Elevator::getLoadingTime() const {
    return loadingTime;
}

double Elevator::getTotalTravelTime(ElevatorStatus status) {
    if (status == ElevatorStatus::DOORS_OPEN || status == ElevatorStatus::DOORS_CLOSE) {
        return doorsTime;
    } else if (status == ElevatorStatus::LOADING) {
        return loadingTime;
    } else {
        return floorTravelTime;
    }
}