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
#include "shortestElevator.h"
#include "scanElevator.h"

/**
 * @brief Function to parse the comma-separated list of floors from input string.
 *
 * @param a The command line argument passed to the function.
 * @return The vector of floors to visit.
 */
std::vector<int> parseFloors(const std::string& input) {
    std::vector<int> floors;
    std::stringstream ss(input);
    std::string floor;
    
    while (getline(ss, floor, ',')) {
        // Remove any whitespace from the extracted floor string
        floor.erase(std::remove_if(floor.begin(), floor.end(), ::isspace), floor.end());

        // Convert the floor string to integer and add to the floors vector
        floors.push_back(stoi(floor));
    }

    return floors;
}

int main(int argc, char* argv[]) {
    // Check if enough command line arguments are provided
    if (argc <= 1) {
        std::cerr << "Usage: " << argv[0] << "\"<startingFloorN>, <floor1>, <floor2>, ..., <floorN>\"" << std::endl;
        return 1;
    }

    // Parse CL args to get the floors
    std::vector<int> floorsToVisit = parseFloors(argv[1]);

    // Ensure there's at least one floor in the list
    if (floorsToVisit.size() < 1) {
        std::cerr << "Invalid input. At least one floor is required." << std::endl;
    }

    // This is inaccurate, but without a priori knowledge of the building, this is a
    // nice way to make sure I don't Charlie and the Glass Elevator out of the top.
    int highestFloor = *std::max_element(floorsToVisit.begin(), floorsToVisit.end());

    // Instantiate the SCAN algorithm elevator with the starting and highest floors.
    ScanElevator elevator(floorsToVisit[0], highestFloor, 10.0, 0.0, 0.0);

    std::cout << "Elevator is starting on floor: " << elevator.getCurrentFloor() << std::endl;

    // Sim some floor requests
    for (size_t i = 1; i < floorsToVisit.size(); ++i) {
        elevator.requestFloor(floorsToVisit[i]);
    }
    
    // Drive the elevator simulation until it reaches the IDLE state
    do {
        elevator.tick();
        elevator.updateTotalTravelTime();
        std::cout << "Elevator is currently at floor: " << elevator.getCurrentFloor()
                    << " and is " << toString(elevator.getStatus()) << " at " << elevator.getTotalTravelTime() << std::endl;

        // Sleep for one second between each simulation tick
        std::this_thread::sleep_for(std::chrono::seconds(1));
    } while(elevator.getStatus() != ElevatorStatus::IDLE);

    std::cout << "Elevator is now on floor: " << elevator.getCurrentFloor()
              << " and took " << elevator.getTotalTravelTime() << " to get there " << std::endl;

    // Generate and display detailed results of the elevator simulation
    elevator.outputResults();

    return 0;
}