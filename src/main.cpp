#include <iostream>
#include <vector>
#include <string>

#include "elevator.h"

using namespace std;

int main()
{
    // vector<string> msg {"Hello", "C++", "World", "from", "VS Code", "and the C++ Extension!"};

    // for (const string& word : msg)
    // {
    //     cout << word << " ";
    // }
    // cout << endl;

    Elevator myElevator(10);

    // Sim some floor requests
    myElevator.requestFloor(3);
    myElevator.requestFloor(7);
    myElevator.requestFloor(5);

    std::cout << "Elevator is now on floor: " << myElevator.getCurrentFloor() << std::endl;

    return 0;
}