#include "IntegerAsVectors.h"
#include "PowerTests.h"

bool powerTest(vector<int> v, int n, vector<int> exp)
{
    vector<int> act = power(v, n);

    if (exp.size() != act.size()) {
        return false;
    }

    for (int i = 0; i < exp.size(); i++) {
        if (exp[i] != act[i]) {
            return false;
        }
    }

    return true;
}

bool powerTests()
{
    vector<int> v = { 1 };
    int a = 0;
    vector<int> exp = { 1 };
    if (!powerTest(v, a, exp)) {
        return false;
    }

    v = { 3,2,1 };
    a = 2;
    exp = { 9,2,1,5,1 }; // 15 129
    if (!powerTest(v, a, exp)) {
        return false;
    }

    v = { 4,3,2,1 };
    a = 7;
    exp = { 4,4,5,4,0,2,2,8,3,1,2,0,4,8,1,6,8,1,7,5,3,4 }; // 4 357 186 184 021 382 204 544
    if (!powerTest(v, a, exp)) {
        return false;
    }

    v = { 7,1,2 };
    a = 11;
    exp = { 3,3,4,5,9,6,0,9,8,2,1,9,8,5,1,6,6,8,0,6,8,0,4,2,0,5 }; // 50 240 860 866 158 912 890 695 433
    if (!powerTest(v, a, exp)) {
        return false;
    }

    return true;
}
