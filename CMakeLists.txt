cmake_minimum_required(VERSION 3.14)

project(tacit_ronin)

# Specify the required c++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Compiler options
add_compile_options(-Wall)

# Include header files
include_directories(include)

# Add all source files to the project
file(GLOB SOURCES "src/*.cpp")

# Add all test files to the project
#file(GLOB TESTS "tests/*.cpp")

# Specify where to place the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Create an executable
add_executable(tacit_ronin ${SOURCES})

# Fetch gTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# # Define the test exe and link against gTest
# add_executable(ElevatorTests ${TESTS} ${SOURCES})
# target_link_libraries(ElevatorTests gtest_main)

enable_testing()

add_executable(tacit_ronin_test ./src/elevator.cpp ./src/scanElevator.cpp ./src/directElevator.cpp ./src/shortestElevator ./tests/test_elevator.cpp)
target_link_libraries(tacit_ronin_test GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tacit_ronin_test)
