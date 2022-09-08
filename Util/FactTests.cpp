#include "IntegerAsVectors.h"

bool factTest(int a, vector<int> exp) {

    vector<int> act = factorial(a);

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

bool factTests() {

    int a = 0;
    vector<int> exp = { 1 };
    if (!factTest(a, exp)) {
        return false;
    }

    a = 1;
    exp = { 1 };
    if (!factTest(a, exp)) {
        return false;
    }

    a = 2;
    exp = { 2 };
    if (!factTest(a, exp)) {
        return false;
    }

    a = 20;
    exp = { 0,0,0,0,4,6,6,7,1,8,0,0,2,0,9,2,3,4,2 };
    if (!factTest(a, exp)) {
        return false;
    }

    return true;
}
