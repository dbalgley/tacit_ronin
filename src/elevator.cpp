#include "elevator.h"

#include "elevatorMode.h"
#include "elevatorStatus.h"

Elevator::Elevator(int startFloor, int floors) : currentFloor(startFloor), totalFloors(floors), status(ElevatorStatus::IDLE) {}

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

int Elevator::getCurrentFloor() const {
    return currentFloor;
}

ElevatorStatus Elevator::getStatus() const {
    return status;
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