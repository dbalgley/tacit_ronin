#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <thread>
#include <chrono>

#include "elevator.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        std::cerr << "Usage: " << argv[0] << " <floor1> <floor2> ... <floorN>" << std::endl;
        return 1;
    }

    // Parse CL args to get the floors
    std::vector<int> floorsToVisit;
    for (int i = 1; i < argc; ++i) {
        int floor = std::atoi(argv[i]);
        floorsToVisit.push_back(floor);
    }

    Elevator elevator(32);

    // Sim some floor requests
    for (int floor : floorsToVisit) {
        elevator.requestFloor(floor);
        while(elevator.getCurrentFloor() != floor) {
            elevator.tick();
            std::cout << "Elevator is currently at floor: " << elevator.getCurrentFloor()
                      << " and is " << elevator.getStatus() << std::endl;

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    std::cout << "Elevator is now on floor: " << elevator.getCurrentFloor() << std::endl;

    return 0;
}