#include "elevator.h"

#include "elevatorMode.h"
#include "elevatorStatus.h"

/**
 * @brief Construct a new Elevator object.
 * 
 * @param startFloor Initial floor the elevator starts from.
 * @param floors Total number of floors the elevator can visit.
 * @param travelTime Time taken to travel between two floors.
 * @param actuateTime Time taken for the elevator doors to actuate.
 * @param loadTime Time taken for passengers to load or unload.
 */
Elevator::Elevator(int startFloor, int floors, double travelTime, double actuateTime, double loadTime) 
    : currentFloor(startFloor),
      totalFloors(floors),
      floorTravelTime(travelTime),
      doorsTime(actuateTime),
      loadingTime(loadTime),
      status(ElevatorStatus::IDLE),
      totalTravelTime(0),
      floorsVisited() 
{}

/**
 * @brief Move the elevator one floor up.
 */
void Elevator::moveUp() {
    if(currentFloor < totalFloors) {
        currentFloor++;
        status = ElevatorStatus::MOVING_UP;
        totalTravelTime += floorTravelTime;
    } else {
        status = ElevatorStatus::IDLE;
    }
}

/**
 * @brief Move the elevator one floor down.
 */
void Elevator::moveDown() {
    if(currentFloor > 1) {
        currentFloor--;
        status = ElevatorStatus::MOVING_DOWN;
        totalTravelTime += floorTravelTime;
    } else {
        status = ElevatorStatus::IDLE;
    }
}

/**
 * @brief Get the current floor of the elevator.
 * 
 * @return int The current floor.
 */
int Elevator::getCurrentFloor() const {
    return currentFloor;
}

/**
 * @brief Get the current status of the elevator.
 * 
 * @return ElevatorStatus The current status.
 */
ElevatorStatus Elevator::getStatus() const {
    return status;
}

/**
 * @brief Get the time taken to travel between floors.
 * 
 * @return double Time in seconds.
 */
double Elevator::getFloorTravelTime() const {
    return floorTravelTime;
}

/**
 * @brief Get the time taken for the elevator doors to actuate.
 * 
 * @return double Time in seconds.
 */
double Elevator::getDoorsTime() const {
    return doorsTime;
}


/**
 * @brief Get the time taken for passengers to load or unload.
 * 
 * @return double Time in seconds.
 */
double Elevator::getLoadingTime() const {
    return loadingTime;
}

/**
 * @brief Update the total travel time depending on the current status.
 */
void Elevator::updateTotalTravelTime() {
    if (status == ElevatorStatus::DOORS_OPEN || status == ElevatorStatus::DOORS_CLOSE) {
        totalTravelTime += doorsTime;
    } else if (status == ElevatorStatus::LOADING) {
        floorsVisited.push_back(currentFloor);
        totalTravelTime += loadingTime;
    }
}

/**
 * @brief Get the total accumulated travel time of the elevator.
 * 
 * @return double Total time in seconds.
 */
double Elevator::getTotalTravelTime() const {
    return totalTravelTime;
}

/**
 * @brief Print the total travel time and the floors visited by the elevator.
 */
void Elevator::outputResults() {
    std::cout << totalTravelTime << " ";
    for (size_t i=0; i < floorsVisited.size(); ++i) {
        std::cout << floorsVisited[i];
        if (i < floorsVisited.size() -1 ) {
            std::cout << ",";
        }
    }
    std::cout << std::endl;
}