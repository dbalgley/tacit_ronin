#include "elevatorStatus.h"

const char* toString(ElevatorStatus status) {
    switch (status) {
        case ElevatorStatus::MOVING_UP: return "Moving Up";
        case ElevatorStatus::MOVING_DOWN: return "Moving Down";
        case ElevatorStatus::IDLE: return "Idle";
        case ElevatorStatus::DOORS_OPEN: return "Doors Opening";
        case ElevatorStatus::DOORS_CLOSE: return "Doors Closing";
        case ElevatorStatus::LOADING: return "Loading";
        case ElevatorStatus::LOCKED_OUT: return "Locked Out";
    }
}