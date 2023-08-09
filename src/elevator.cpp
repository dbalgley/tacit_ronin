#include "elevator.h"

Elevator::Elevator(int floors) : currentFloor(1), totalFloors(floors), isMoving(false) {
    floorQueue.resize(floors, false);
}

void Elevator::requestFloor(int floor) {
    if (floor > 0 && floor <= totalFloors) {
        floorQueue[floor - 1] = true; // Mark the floor for a stop
        move();
    } else {
        std::cerr << "Invalid floor requested: " << floor << std::endl;
    }
}

void Elevator::move() {
    if(!isMoving) {
        isMoving = true;

        // Real simple version, move to top, then move down
        for (int i = 0; i < totalFloors; ++i) {
            if (floorQueue[i]) {
                currentFloor = i + 1;
                floorQueue[i] = false;
                std::cout << "Elevator stopping at floor: " << currentFloor << std::endl;
            }
        }

        isMoving = false;
    }
}

int Elevator::getCurrentFloor() const {
    return currentFloor;
}