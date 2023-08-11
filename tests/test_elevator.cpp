#include <gtest/gtest.h>
#include "elevator.h"
#include "directElevator.h"
#include "elevatorMode.h"
#include "elevatorStatus.h"

class ElevatorTest : public ::testing::Test {
protected:
    DirectElevator directElevatorInstance;

    ElevatorTest() : directElevatorInstance(1, 5) {}
};

TEST_F(ElevatorTest, TestStartFloor) {
    ASSERT_EQ(directElevatorInstance.getCurrentFloor(), 1);
}

TEST_F(ElevatorTest, TestMoveUp) {
    directElevatorInstance.moveUp();
    ASSERT_EQ(directElevatorInstance.getCurrentFloor(), 2);
    ASSERT_EQ(directElevatorInstance.getStatus(), ElevatorStatus::MOVING_UP);
}

TEST_F(ElevatorTest, TestMoveDown) {
    directElevatorInstance.moveDown();
    ASSERT_EQ(directElevatorInstance.getCurrentFloor(), 1);
    // Should remain IDLE since it's at the bottom floor.
    ASSERT_EQ(directElevatorInstance.getStatus(), ElevatorStatus::IDLE);
}

TEST_F(ElevatorTest, TestRequestValidFloor) {
    directElevatorInstance.requestFloor(3);
    directElevatorInstance.tick();
    ASSERT_EQ(directElevatorInstance.getStatus(), ElevatorStatus::MOVING_UP);
}

TEST_F(ElevatorTest, TestRequestSameFloor) {
    directElevatorInstance.requestFloor(1);
    // Requesting the current floor should not change the status.
    ASSERT_EQ(directElevatorInstance.getStatus(), ElevatorStatus::IDLE);
}

TEST_F(ElevatorTest, TestRequestInvalidFloor) {
    directElevatorInstance.requestFloor(6);  // Assuming 5 floors.
    ASSERT_EQ(directElevatorInstance.getStatus(), ElevatorStatus::IDLE);
}

TEST_F(ElevatorTest, TestTickDoorsOpen) {
    directElevatorInstance.requestFloor(3);
    directElevatorInstance.tick();  // Moving up
    directElevatorInstance.tick();  // Moving up
    directElevatorInstance.tick();  // Now at floor 3
    ASSERT_EQ(directElevatorInstance.getStatus(), ElevatorStatus::DOORS_OPEN);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}