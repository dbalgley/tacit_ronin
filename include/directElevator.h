#include "elevator.h"

/**
 * @brief DirectElevator represents an elevator that processes floor requests in the order they're received.
 *
 * This is an implementation of the Elevator class that uses a First Come, First Serve (FCFS) 
 * approach to handle floor requests.
 */
class DirectElevator : public Elevator {
    private:
        std::deque<int> floorRequests;  ///< Queue of floor requests in the upwards direction.
    
    public:
        /**
         * @brief Construct a new Direct Elevator object.
         * 
         * @param startFloor: The floor the elevator starts on.
         * @param floors: The total number of floors.
         * @param travelTime: Time taken to travel between floors.
         * @param actuateTime: Time taken to open/close doors.
         * @param loadTime: Time taken for passengers to enter/exit.
         */
        DirectElevator(int startFloor, int floors, double travelTime, double actuateTime, double loadTime);

        /**
         * @brief Request the elevator to move to a specific floor.
         * 
         * If the floor is invalid (outside the range of floors, or is the current floor), it prints an error.
         * 
         * @param floor The floor number to move to.
         */
        void requestFloor(int floor) override;

        /**
         * @brief A simulation tick for the DirectElevator.
         * 
         * This function simulates one time unit for the elevator's operations, such as moving between floors, 
         * opening/closing doors, or loading passengers.
         */
        void tick() override;
};