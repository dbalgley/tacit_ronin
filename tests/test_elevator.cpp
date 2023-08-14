#include <gtest/gtest.h>
#include "elevator.h"
#include "directElevator.h"
#include "scanElevator.h"
#include "elevatorStatus.h"

/**
 * @brief Test fixture class for Elevator-related tests.
 * 
 * Contains instances of DirectElevator and ScanElevator for testing purposes.
 */
class ElevatorTest : public ::testing::Test {
protected:
    DirectElevator directElevatorInstance;
    ScanElevator scanElevatorInstance;

    // Default constructor initializing elevator instances.
    ElevatorTest() : directElevatorInstance(1, 5, 10, 0, 0),
                     scanElevatorInstance(1, 5, 10, 0, 0) {}
};

/**
 * @brief Test the starting floor of the elevator instances.
 */
TEST_F(ElevatorTest, TestStartFloor) {
    ASSERT_EQ(directElevatorInstance.getCurrentFloor(), 1);
    ASSERT_EQ(scanElevatorInstance.getCurrentFloor(), 1);
}

/**
 * @brief Test the moveUp function of the elevator instances.
 */
TEST_F(ElevatorTest, TestMoveUp) {
    directElevatorInstance.moveUp();
    ASSERT_EQ(directElevatorInstance.getCurrentFloor(), 2);
    ASSERT_EQ(directElevatorInstance.getStatus(), ElevatorStatus::MOVING_UP);

    scanElevatorInstance.moveUp();
    ASSERT_EQ(scanElevatorInstance.getCurrentFloor(), 2);
    ASSERT_EQ(scanElevatorInstance.getStatus(), ElevatorStatus::MOVING_UP);
}

/**
 * @brief Test the moveDown function of the elevator instances.
 */
TEST_F(ElevatorTest, TestMoveDown) {
    directElevatorInstance.moveDown();
    ASSERT_EQ(directElevatorInstance.getCurrentFloor(), 1);
    // Should remain IDLE since it's at the bottom floor.
    ASSERT_EQ(directElevatorInstance.getStatus(), ElevatorStatus::IDLE);

    scanElevatorInstance.moveDown();
    ASSERT_EQ(scanElevatorInstance.getCurrentFloor(), 1);
    // Should remain IDLE since it's at the bottom floor.
    ASSERT_EQ(scanElevatorInstance.getStatus(), ElevatorStatus::IDLE);
}

/**
 * @brief Test the behavior when requesting a valid floor.
 */
TEST_F(ElevatorTest, TestRequestValidFloor) {
    directElevatorInstance.requestFloor(3);
    directElevatorInstance.tick();
    ASSERT_EQ(directElevatorInstance.getStatus(), ElevatorStatus::MOVING_UP);
    
    scanElevatorInstance.requestFloor(3);
    scanElevatorInstance.tick();
    ASSERT_EQ(scanElevatorInstance.getStatus(), ElevatorStatus::MOVING_UP);
}

/**
 * @brief Test the behavior when requesting the same floor the elevator is currently on.
 */
TEST_F(ElevatorTest, TestRequestSameFloor) {
    directElevatorInstance.requestFloor(1);
    // Requesting the current floor should not change the status.
    ASSERT_EQ(directElevatorInstance.getStatus(), ElevatorStatus::IDLE);
    
    scanElevatorInstance.requestFloor(1);
    // Requesting the current floor should not change the status.
    ASSERT_EQ(scanElevatorInstance.getStatus(), ElevatorStatus::IDLE);
}

/**
 * @brief Test the behavior when requesting an invalid floor.
 */
TEST_F(ElevatorTest, TestRequestInvalidFloor) {
    directElevatorInstance.requestFloor(6);  // Assuming 5 floors.
    ASSERT_EQ(directElevatorInstance.getStatus(), ElevatorStatus::IDLE);
    
    scanElevatorInstance.requestFloor(6);  // Assuming 5 floors.
    ASSERT_EQ(scanElevatorInstance.getStatus(), ElevatorStatus::IDLE);
}

/**
 * @brief Test the tick function behavior when the elevator doors are open.
 */
TEST_F(ElevatorTest, TestTickDoorsOpen) {
    directElevatorInstance.requestFloor(3);
    directElevatorInstance.tick();  // Moving up
    directElevatorInstance.tick();  // Now at floor 3
    ASSERT_EQ(directElevatorInstance.getStatus(), ElevatorStatus::DOORS_OPEN);
    
    scanElevatorInstance.requestFloor(3);
    scanElevatorInstance.tick();  // Moving up
    scanElevatorInstance.tick();  // Now at floor 3
    ASSERT_EQ(scanElevatorInstance.getStatus(), ElevatorStatus::DOORS_OPEN);
}

/**
 * @brief Test the tick function behavior during the loading phase.
 */
TEST_F(ElevatorTest, TestTickLoading) {
    directElevatorInstance.requestFloor(3);
    directElevatorInstance.tick();  // Moving up
    directElevatorInstance.tick();  // Now at floor 3
    directElevatorInstance.tick();  // Doors Opening
    ASSERT_EQ(directElevatorInstance.getStatus(), ElevatorStatus::LOADING);
    
    scanElevatorInstance.requestFloor(3);
    scanElevatorInstance.tick();  // Moving up
    scanElevatorInstance.tick();  // Now at floor 3
    scanElevatorInstance.tick();  // Doors Opening
    ASSERT_EQ(scanElevatorInstance.getStatus(), ElevatorStatus::LOADING);
}

/**
 * @brief Test the tick function behavior when the elevator doors are closing.
 */
TEST_F(ElevatorTest, TestTickDoorsClose) {
    directElevatorInstance.requestFloor(3);
    directElevatorInstance.tick();  // Moving up
    directElevatorInstance.tick();  // Now at floor 3
    directElevatorInstance.tick();  // Doors Opening
    directElevatorInstance.tick();  // Attempting a Load
    ASSERT_EQ(directElevatorInstance.getStatus(), ElevatorStatus::DOORS_CLOSE);
    
    scanElevatorInstance.requestFloor(3);
    scanElevatorInstance.tick();  // Moving up
    scanElevatorInstance.tick();  // Now at floor 3
    scanElevatorInstance.tick();  // Doors Opening
    scanElevatorInstance.tick();  // Attempting a Load
    ASSERT_EQ(scanElevatorInstance.getStatus(), ElevatorStatus::DOORS_CLOSE);
}

/**
 * @brief Comprehensive test for the elevator's overall functionality.
 */
TEST_F(ElevatorTest, TestFunctionality) {
    scanElevatorInstance.requestFloor(3);
    scanElevatorInstance.requestFloor(2);
    scanElevatorInstance.requestFloor(5);
    scanElevatorInstance.requestFloor(4);
    do {
        scanElevatorInstance.tick();
    } while (scanElevatorInstance.getStatus() != ElevatorStatus::IDLE);
    ASSERT_EQ(scanElevatorInstance.getCurrentFloor(), 5);
    ASSERT_EQ(scanElevatorInstance.getTotalTravelTime(), 40);
}

// Test for moveDown() at bottom
// Test for mnoveUp() at top

/**
 * @brief Entry point for the test execution.
 * 
 * @param argc Argument count.
 * @param argv Argument values.
 * @return int Test result status.
 */
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}