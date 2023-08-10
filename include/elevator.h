#include <iostream>
#include <deque>

class Elevator {
    private:
        int currentFloor;
        int totalFloors;
        std::string status;
        std::deque<int> floorRequests;

    public:
        // Constructor
        Elevator(int floors = 10);

        void moveUp();
        void moveDown();

        // Request the elevator to a specific floor
        void requestFloor(int floor);

        // Move the elevator
        void move();

        void tick();

        // Get the current floor
        int getCurrentFloor() const;

        std::string getStatus() const;
};