#include "IntegerAsVectors.h"
#include "Util.h"
#include "DivTests.h"

bool divTest(vector<int> v1, vector<int> v2, vector<int> exp)
{
    vector<int> act = divide(v1, v2);

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

bool divTests()
{
    vector<int> v1 = { 7,1,3,5,0,2,4,5 };
    vector<int> v2 = { 2,4,7,1,3 };
    vector<int> exp = { 7,0,7,1 };
    if (!divTest(v1, v2, exp)) {
        return false;
    }

    v1 = { 1 };
    v2 = { 1 };
    exp = { 1 };
    if (!divTest(v1, v2, exp)) {
        return false;
    }

    //v1 = { 2,4,7,1,3 };
    //v2 = { 7,1,3,5,0,2,4,5 };
    //exp = { 7,0,7,1 };
    //if (!divTest(v1, v2, exp)) {
    //    return false;
    //}

    return true;
}
