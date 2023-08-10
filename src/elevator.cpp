#include "elevator.h"

Elevator::Elevator(int floors) : currentFloor(1), totalFloors(floors), status("Idle") {}

void Elevator::moveUp() {
    if(currentFloor < totalFloors) {
        currentFloor++;
        status = "MovingUp";
    } else {
        status = "Idle";
    }
}

void Elevator::moveDown() {
    if(currentFloor > 1) {
        currentFloor--;
        status = "MovingDown";
    } else {
        status = "Idle";
    }
}

void Elevator::requestFloor(int floor) {
    if (floor >= 1 && floor <= totalFloors && floor != currentFloor) {
        floorRequests.push_back(floor);
        if(floor > currentFloor) {
            moveUp();
        } else {
            moveDown();
        }
    } else {
        std::cerr << "Invalid floor requested: " << floor << std::endl;
    }
}

void Elevator::tick() {
    if (floorRequests.empty()) {
        status = "Idle";
        return;
    }

    int nextFloor = floorRequests.front();

    if (currentFloor == nextFloor) {
        status = "DoorsOpen";
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

std::string Elevator::getStatus() const {
    return status;
}