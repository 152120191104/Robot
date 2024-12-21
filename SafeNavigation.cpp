#include <iostream>
#include "SafeNavigation.h"
#include "IRSensor.h"
#include "RobotControler.h"
#include "FestoRobotAPI.h"

int main() {
    IRSensor irSensor;
    FestoRobotAPI api;
    RobotControler controller(&api);
    SafeNavigation navigator(&irSensor, &controller);

    if (controller.connectRobot()) {
        std::cout << "Robot connected successfully.\n";

        std::cout << "Attempting safe forward navigation:\n";
        navigator.moveForwardSafe();

        std::cout << "Attempting safe backward navigation:\n";
        navigator.moveBackwardSafe();

        controller.disconnectRobot();
    }
    else {
        std::cerr << "Error: Could not connect to the robot.\n";
    }

    return 0;
}