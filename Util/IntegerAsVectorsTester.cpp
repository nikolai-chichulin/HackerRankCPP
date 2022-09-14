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

    long long i = 123456789777777;
    bi i1(i);
    cout << i1 << endl;
    int j = 12345;
    bi i2(j);
    cout << i2 << endl;

    return 0;
}
