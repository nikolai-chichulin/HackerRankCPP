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

void commontests() {

    cout << "Multiplication with integer: " << (multTestsI() ? "passed" : "failed") << endl;
    cout << "Multiplication with vector:  " << (multTestsV() ? "passed" : "failed") << endl;
    cout << "Summation:                   " << (sumTests() ? "passed" : "failed") << endl;
    cout << "Raising to a power:          " << (powerTests() ? "passed" : "failed") << endl;
    cout << "Raising to a power integer:  " << (powerTestsI() ? "passed" : "failed") << endl;
    cout << "Subtration:                  " << (subtrTests() ? "passed" : "failed") << endl;
    cout << "Division:                    " << (divTests() ? "passed" : "failed") << endl;
    cout << "Compose:                     " << (compTests() ? "passed" : "failed") << endl;
    cout << "Decompose:                   " << (decompTests() ? "passed" : "failed") << endl;
    cout << "Big Integers:                " << (biTests() ? "passed" : "failed") << endl;
}

int main() {

    commontests();

    //bi i1 = bi::factorial(10);
    //bi i2 = i1.s();
    //bi i3 = i1.f();
    //cout << i1 << endl;
    //cout << i2 << endl;
    //cout << i3 << endl;

    //pair<bi, bi>res = i1 / i2;
    //cout << i1 << " / " << i2 << " = " << res.first << " : " << res.second << endl;
    //cout << i1 << " + " << i2 << " = " << i1 + i2 << endl;
    //cout << i1 << " - " << i2 << " = " << i1 - i2 << endl;
    //cout << i2 << " + " << i1 << " = " << i2 + i1 << endl;
    //cout << i2 << " - " << i1 << " = " << i2 - i1 << endl;

    return 0;
}
