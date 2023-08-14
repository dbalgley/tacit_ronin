#include "elevator.h"

class DirectElevator : public Elevator {
    private:
        std::deque<int> floorRequests;
    
    public:
        DirectElevator(int startFloor, int floors, double travelTime, double actuateTime, double loadTime);

        void requestFloor(int floor) override;
        void tick() override;
};