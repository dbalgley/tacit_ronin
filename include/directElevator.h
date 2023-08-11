#include "elevator.h"

class DirectElevator : public Elevator {
    private:
        std::deque<int> floorRequests;
    
    public:
        DirectElevator(int startFloor, int floors);

        void requestFloor(int floor) override;
        void tick() override;
};