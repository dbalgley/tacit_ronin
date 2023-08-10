// elevatorStatus.h
#pragma once

enum class ElevatorStatus {
    MOVING_UP,
    MOVING_DOWN,
    IDLE,
    DOORS_OPEN,
    DOORS_CLOSE,
    LOADING,
    LOCKED_OUT
};

// Function to convert status to string for human readability
const char* toString(ElevatorStatus status);