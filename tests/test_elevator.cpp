#include <gtest/gtest.h>
#include "elevator.h"
#include "elevatorMode.h"
#include "elevatorStatus.h"

class ElevatorTest : public ::testing::Test {
protected:
    Elevator elevator;

    ElevatorTest() : elevator(1, 5, ElevatorMode::DIRECT) {}
};

TEST_F(ElevatorTest, TestStartFloor) {
    ASSERT_EQ(elevator.getCurrentFloor(), 1);
}

TEST_F(ElevatorTest, TestMoveUp) {
    elevator.moveUp();
    ASSERT_EQ(elevator.getCurrentFloor(), 2);
    ASSERT_EQ(elevator.getStatus(), ElevatorStatus::MOVING_UP);
}

TEST_F(ElevatorTest, TestMoveDown) {
    elevator.moveDown();
    ASSERT_EQ(elevator.getCurrentFloor(), 1);
    // Should remain IDLE since it's at the bottom floor.
    ASSERT_EQ(elevator.getStatus(), ElevatorStatus::IDLE);
}

TEST_F(ElevatorTest, TestRequestValidFloor) {
    elevator.requestFloor(3);
    elevator.tick();
    ASSERT_EQ(elevator.getStatus(), ElevatorStatus::MOVING_UP);
}

TEST_F(ElevatorTest, TestRequestSameFloor) {
    elevator.requestFloor(1);
    // Requesting the current floor should not change the status.
    ASSERT_EQ(elevator.getStatus(), ElevatorStatus::IDLE);
}

TEST_F(ElevatorTest, TestRequestInvalidFloor) {
    elevator.requestFloor(6);  // Assuming 5 floors.
    ASSERT_EQ(elevator.getStatus(), ElevatorStatus::IDLE);
}

TEST_F(ElevatorTest, TestTickDoorsOpen) {
    elevator.requestFloor(3);
    elevator.tick();  // Moving up
    elevator.tick();  // Moving up
    elevator.tick();  // Now at floor 3
    ASSERT_EQ(elevator.getStatus(), ElevatorStatus::DOORS_OPEN);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}