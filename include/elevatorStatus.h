// elevatorStatus.h
#pragma once

/**
 * @brief Enum class representing the status of an elevator.
 */
enum class ElevatorStatus {
    MOVING_UP,    ///< Elevator is moving upwards.
    MOVING_DOWN,  ///< Elevator is moving downwards.
    IDLE,         ///< Elevator is not in motion and doors are closed.
    DOORS_OPEN,   ///< Elevator's doors are currently open.
    DOORS_CLOSE,  ///< Elevator's doors are currently closing or closed.
    LOADING,      ///< Elevator is in the process of loading or unloading passengers.
    LOCKED_OUT    ///< Elevator is not operational.
};

/**
 * @brief Convert an ElevatorStatus value to a human-readable string.
 * 
 * @param status ElevatorStatus value to be converted.
 * @return const char* Corresponding string representation.
 */
const char* toString(ElevatorStatus status);