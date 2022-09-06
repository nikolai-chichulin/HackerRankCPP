#include "IntegerAsVectors.h"
#include "SumTests.h"
#include "MultTests.h"
#include "PowerTests.h"

int main() {

    cout << (multTestsI() ? "Passed" : "Failed") << endl;
    cout << (multTestsV() ? "Passed" : "Failed") << endl;
    cout << (sumTests() ? "Passed" : "Failed") << endl;
    cout << (powerTests() ? "Passed" : "Failed") << endl;
    cout << (powerTestsI() ? "Passed" : "Failed") << endl;
    return 0;
}
