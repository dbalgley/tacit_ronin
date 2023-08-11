#pragma once

#include <iostream>
#include <deque>

#include "elevatorStatus.h"

class Elevator {
    protected:
        int currentFloor;
        int totalFloors;

        ElevatorStatus status;
        const double floorTravelTime = 10.0;
        const double doorsTime = 0.0;
        const double loadingTime = 0.0;

    public:
        // Constructor
        Elevator(int startFloor = 1, int floors = 10);

        // Pure virtual request function
        virtual void requestFloor(int floor) = 0;

        // Pure virtual tick function
        virtual void tick() = 0;

        void moveUp();
        void moveDown();

        // Move the elevator
        void move();

        // Get the current floor
        int getCurrentFloor() const;

        ElevatorStatus getStatus() const;

        double getFloorTravelTime() const;
        double getDoorsTime() const;
        double getLoadingTime() const;

        double getTotalTravelTime(ElevatorStatus status);
};