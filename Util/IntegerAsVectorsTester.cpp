#include "IntegerAsVectors.h"
#include "SumTests.h"
#include "SubtrTests.h"
#include "MultTests.h"
#include "PowerTests.h"
#include "DivTests.h"
#include "CompDecompTests.h"
#include "BigIntegerTests.h"

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
    cout << (biTests() ? "Passed" : "Failed") << endl;

    //bi i1;
    //bi i2(100);
    //cout << i1 << " + " << i2 << " = " << i1 + i2 << endl;
    //cout << i1 << " - " << i2 << " = " << i1 - i2 << endl;
    //cout << i2 << " + " << i1 << " = " << i2 + i1 << endl;
    //cout << i2 << " - " << i1 << " = " << i2 - i1 << endl;

    return 0;
}
