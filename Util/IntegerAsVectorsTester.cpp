#include "IntegerAsVectors.h"
#include "SumTests.h"
#include "SubtrTests.h"
#include "MultTests.h"
#include "PowerTests.h"
#include "DivTests.h"
#include "CompDecompTests.h"

#include "BigInteger.h"

using namespace std;

int main() {

    //cout << (multTestsI() ? "Passed" : "Failed") << endl;
    //cout << (multTestsV() ? "Passed" : "Failed") << endl;
    //cout << (sumTests() ? "Passed" : "Failed") << endl;
    //cout << (powerTests() ? "Passed" : "Failed") << endl;
    //cout << (powerTestsI() ? "Passed" : "Failed") << endl;
    //cout << (subtrTests() ? "Passed" : "Failed") << endl;
    //cout << (divTests() ? "Passed" : "Failed") << endl;
    //cout << (compTests() ? "Passed" : "Failed") << endl;
    //cout << (decompTests() ? "Passed" : "Failed") << endl;

    bi i1(-123456789777777L); // long long
    bi i2(-123); // int
    bi i3("-12345"); // string
    cout << i1 << endl;
    cout << i2 << endl;
    cout << i3 << endl;

    cout << i1[0] << endl;

    return 0;
}
