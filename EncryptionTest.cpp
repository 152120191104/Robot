#include "Encryption.h"
#include <iostream>
#include "FestoRobotAPI.h"
using namespace std;

void testEncryption() {
    cout << "Testing Encryption class\n";
    Encryption enc;

    int encrypted = enc.encrypt(1234);
    cout << "Encrypted: " << encrypted << endl;

    int decrypted = enc.decrypt(encrypted);
    cout << "Decrypted: " << decrypted << endl;

    cout << "Encryption class tests completed\n";
}

int main() {
    FestoRobotAPI* robotino;
    robotino = new FestoRobotAPI();
    robotino->connect();
    testEncryption();
    robotino->disconnect();
    delete robotino;
    
    return 0;
}
