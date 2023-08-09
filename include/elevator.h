#include <iostream>
#include <vector>

class Elevator {
    private:
        int currentFloor;
        int totalFloors;
        bool isMoving;
        std::vector<bool> floorQueue;

    public:
        // Constructor
        Elevator(int floors = 10);

        // Request the elevator to a specific floor
        void requestFloor(int floor);

        // Move the elevator
        void move();

        // Get the current floor
        int getCurrentFloor() const;
};