#include "elevator.h"
#include <gtest/gtest.h>

TEST(hello_test, InitializationTest) {
    Elevator elevator;
    ASSERT_EQ(elevator.getCurrentFloor(), 1);
}