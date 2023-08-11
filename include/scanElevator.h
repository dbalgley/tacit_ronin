#pragma once

#include <set>

#include "elevator.h"

class ScanElevator : public Elevator {
    private:
        std::set<int> upRequests;
        std::set<int> downRequests;
        bool goingUp;

    public:
        ScanElevator(int startFloor, int floors);

        void requestFloor(int floor) override;
        void tick() override;
};