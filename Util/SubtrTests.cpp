#include "IntegerAsVectors.h"
#include "Util.h"
#include "SubtrTests.h"

bool subtrTest(vector<int> v1, vector<int> v2, vector<int> exp)
{
    vector<int> act = subtr(v1, v2);

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

bool subtrTests()
{
    vector<int> v1 = { 1 };
    vector<int> v2 = { 1 };
    vector<int> exp = { 0 };
    if (!subtrTest(v1, v2, exp)) {
        return false;
    }

    v1 = { 2 };
    v2 = { 1 };
    exp = { 1 };
    if (!subtrTest(v1, v2, exp)) {
        return false;
    }

    v1 = { 1,0,1,1 };
    v2 = { 3,2,1 };
    exp = { 8,7,9 };
    if (!subtrTest(v1, v2, exp)) {
        return false;
    }

    v1 = { 1,0,1,1 };
    v2 = { 0 };
    exp = { 1,0,1,1 };
    if (!subtrTest(v1, v2, exp)) {
        return false;
    }

    v1 = { 1,1,1,1 };
    v2 = { 9,9,9 };
    exp = { 2,1,1 };
    if (!subtrTest(v1, v2, exp)) {
        return false;
    }

    v1 = { 1,0,1,1 };
    v2 = { 1 };
    exp = { 0,0,1,1 };
    if (!subtrTest(v1, v2, exp)) {
        return false;
    }

    v1 = { 1,0,1,1 };
    v2 = { 2 };
    exp = { 9,9,0,1 };
    if (!subtrTest(v1, v2, exp)) {
        return false;
    }

    v1 = { 2,1,6,3,1,7,9 };
    v2 = { 7,3,1,8,4,5 };
    exp = { 5,7,4,5,6,1,9 };
    if (!subtrTest(v1, v2, exp)) {
        return false;
    }



    return true;
}
