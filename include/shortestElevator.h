#pragma once

#include <set>

#include "elevator.h"

class ShortestElevator : public Elevator {
    private:
        std::set<int> floorRequests;
        int nextFloor;
        
        void findNextFloor();

    public:
        ShortestElevator(int startFloor, int floors);

        void requestFloor(int floor) override;
        void tick() override;
};