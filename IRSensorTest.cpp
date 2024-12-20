#include "IRSensor.h"
#include <iostream>
using namespace std;

void testIRSensor() {
    cout << "Testing IRSensor class\n";
    IRSensor ir;

    ir.update();
    for (int i = 0; i < 9; ++i) {
        cout << "Sensor " << i << " range: " << ir.getRange(i) << endl;
    }

    cout << "IRSensor class tests completed\n";
}

int main() {
    FestoRobotAPI* robotino;
    robotino = new FestoRobotAPI();
    robotino->connect();
    testIRSensor();
    robotino->disconnect();
    delete robotino;

    return 0;
}
