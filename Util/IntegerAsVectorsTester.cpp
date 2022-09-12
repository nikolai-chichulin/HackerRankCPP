#include "IntegerAsVectors.h"
#include "SumTests.h"
#include "SubtrTests.h"
#include "MultTests.h"
#include "PowerTests.h"
#include "DivTests.h"
#include "DecompTests.h"

int main() {

    cout << (multTestsI() ? "Passed" : "Failed") << endl;
    cout << (multTestsV() ? "Passed" : "Failed") << endl;
    cout << (sumTests() ? "Passed" : "Failed") << endl;
    cout << (powerTests() ? "Passed" : "Failed") << endl;
    cout << (powerTestsI() ? "Passed" : "Failed") << endl;
    cout << (subtrTests() ? "Passed" : "Failed") << endl;
    cout << (divTests() ? "Passed" : "Failed") << endl;
    cout << (decompTests() ? "Passed" : "Failed") << endl;
    return 0;
}
