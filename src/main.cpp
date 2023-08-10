#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <thread>
#include <chrono>

#include "elevator.h"
#include "elevatorStatus.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        std::cerr << "Usage: " << argv[0] << " <startingFloorN> <floor1> <floor2> ... <floorN>" << std::endl;
        return 1;
    }

    // Parse CL arg to get the starting floor
    int startFloor = std::atoi(argv[1]);

    // Parse CL args to get the floors
    std::vector<int> floorsToVisit;
    for (int i = 2; i < argc; ++i) {
        int floor = std::atoi(argv[i]);
        floorsToVisit.push_back(floor);
    }

    Elevator elevator(startFloor, 32);

    std::cout << "Elevator is starting on floor: " << elevator.getCurrentFloor() << std::endl;

    double travelTime = 0.0f;

    // Sim some floor requests
    for (int floor : floorsToVisit) {
        elevator.requestFloor(floor);
        while(elevator.getCurrentFloor() != floor) {
            elevator.tick();
            travelTime += elevator.getTotalTravelTime(elevator.getStatus());
            std::cout << "Elevator is currently at floor: " << elevator.getCurrentFloor()
                      << " and is " << toString(elevator.getStatus()) << " at " << travelTime << std::endl;

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    std::cout << "Elevator is now on floor: " << elevator.getCurrentFloor()
              << " and took " << travelTime << " to get there " << std::endl;

    return 0;
}