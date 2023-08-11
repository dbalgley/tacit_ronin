#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <sstream>
#include <algorithm>

#include "directElevator.h"
#include "elevatorStatus.h"

using namespace std;

std::vector<int> parseFloors(const std::string& input) {
    std::vector<int> floors;
    std::stringstream ss(input);
    std::string floor;

    while (getline(ss, floor, ',')) {
        floor.erase(std::remove_if(floor.begin(), floor.end(), ::isspace), floor.end());

        floors.push_back(stoi(floor));
    }

    return floors;
}

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        std::cerr << "Usage: " << argv[0] << " <startingFloorN>, <floor1>, <floor2>, ..., <floorN>" << std::endl;
        return 1;
    }

    // Parse CL args to get the floors
    std::vector<int> floorsToVisit = parseFloors(argv[1]);

    if (floorsToVisit.size() < 1) {
        std::cerr << "Invalid input. At least one floor is required." << std::endl;
    }

    DirectElevator elevator(floorsToVisit[0], 32);

    std::cout << "Elevator is starting on floor: " << elevator.getCurrentFloor() << std::endl;

    double travelTime = 0.0f;

    // Sim some floor requests
    for (size_t i = 1; i < floorsToVisit.size(); ++i) {
        elevator.requestFloor(floorsToVisit[i]);
        while(elevator.getCurrentFloor() != floorsToVisit[i]) {
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