#include "IntegerAsVectors.h"
#include "SumTests.h"
#include "MultTests.h"

int main() {

    cout << (multTestsI() ? "Passed" : "Failed") << endl;
    cout << (multTestsV() ? "Passed" : "Failed") << endl;
    cout << (sumTests() ? "Passed" : "Failed") << endl;
    return 0;
}
