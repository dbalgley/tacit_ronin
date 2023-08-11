#include "scanElevator.h"

ScanElevator::ScanElevator(int startFloor, int floors) : Elevator(startFloor, floors), goingUp(true) {}

void ScanElevator::requestFloor(int floor) {
    if (floor == currentFloor) return;

    if (floor > currentFloor) {
        upRequests.insert(floor);
    } else {
        downRequests.insert(floor);
    }
}

void ScanElevator::tick() {
    if (upRequests.empty() && downRequests.empty()) {
        status = ElevatorStatus::IDLE;
        return;
    }

    if (goingUp) {
        if (upRequests.empty()) {
            goingUp = false;
            moveDown();
        } else {
            moveUp();
            if (upRequests.find(currentFloor) != upRequests.end()) {
                upRequests.erase(currentFloor);
            }
        }
    } else {
        if (downRequests.empty()) {
            goingUp = true;
            moveUp();
        } else {
            moveDown();
            if (downRequests.find(currentFloor) != downRequests.end()) {
                downRequests.erase(currentFloor);
            }
        }
    }
}