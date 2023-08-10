#include <iostream>
#include <deque>

#include "elevatorMode.h"
#include "elevatorStatus.h"

class Elevator {
    private:
        int currentFloor;
        int totalFloors;
        ElevatorMode opMode;
        ElevatorStatus status;
        std::deque<int> floorRequests;
        const double floorTravelTime = 10.0;
        const double doorsTime = 0.0;
        const double loadingTime = 0.0;

    public:
        // Constructor
        Elevator(int startFloor = 1, int floors = 10, ElevatorMode opMode = ElevatorMode::DIRECT);

        void moveUp();
        void moveDown();

        // Request the elevator to a specific floor
        void requestFloor(int floor);

        // Move the elevator
        void move();

        void tick();

        // Get the current floor
        int getCurrentFloor() const;

        ElevatorStatus getStatus() const;

        ElevatorMode getOpMode() const;

        double getFloorTravelTime() const;
        double getDoorsTime() const;
        double getLoadingTime() const;

        double getTotalTravelTime(ElevatorStatus status);
};