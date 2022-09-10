#include "IntegerAsVectors.h"
#include "Util.h"
#include "MultTests.h"

bool multTest(vector<int> v, int a, vector<int> exp) {

    vector<int> act = multiply(v, a);

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

bool multTestsI() {

    vector<int> v = { 1 };
    int a = 0;
    vector<int> exp = { 0 };
    if (!multTest(v, a, exp)) {
        return false;
    }

    v = { 3, 2, 1 };
    a = 2;
    exp = { 6, 4, 2 };
    if (!multTest(v, a, exp)) {
        return false;
    }

    v = { 9, 0, 8, 0, 7, 0, 6, 0, 4, 0, 3, 0, 2, 0, 1 };
    a = 919;
    exp = { 1, 7, 4, 3, 7, 0, 9, 7, 1, 3, 4, 9, 5, 6, 7, 3, 9 };
    if (!multTest(v, a, exp)) {
        return false;
    }

    v = { 9, 0, 8, 0, 7, 0, 6, 0, 4, 0, 3, 0, 2, 0, 1 };
    a = 11111;
    exp = { 9, 9, 7, 8, 5, 7, 2, 5, 8, 1, 4, 8, 9, 5, 6, 3, 3, 1, 1 };
    if (!multTest(v, a, exp)) {
        return false;
    }

    return true;
}

bool multTest(vector<int> v1, vector<int> v2, vector<int> exp) {

    vector<int> act = multiply(v1, v2);

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

bool multTestsV() {

    vector<int> v1 = { 0 };
    vector<int> v2 = { 5, 2, 3, 2, 9, 1 };
    vector<int> exp = { 0, 0, 0, 0, 0, 0 };
    if (!multTest(v1, v2, exp)) {
        return false;
    }

    v1 = { 1 };
    v2 = { 5, 7, 8, 3 };
    exp = { 5, 7, 8, 3 };
    if (!multTest(v1, v2, exp)) {
        return false;
    }

    v1 = { 5, 7, 8, 3 };
    v2 = { 1 };
    exp = { 5, 7, 8, 3 };
    if (!multTest(v1, v2, exp)) {
        return false;
    }

    v1 = { 2 };
    v2 = { 5, 7, 8, 3 };
    exp = { 0, 5, 7, 7 };
    if (!multTest(v1, v2, exp)) {
        return false;
    }

    v1 = { 5, 7, 8, 3 };
    v2 = { 2 };
    exp = { 0, 5, 7, 7 };
    if (!multTest(v1, v2, exp)) {
        return false;
    }

    v1 = { 3 };
    v2 = { 5, 7, 8, 3 };
    exp = { 5, 2, 6, 1, 1 };
    if (!multTest(v1, v2, exp)) {
        return false;
    }

    v1 = { 5, 7, 8, 3 };
    v2 = { 3 };
    exp = { 5, 2, 6, 1, 1 };
    if (!multTest(v1, v2, exp)) {
        return false;
    }

    v1 = { 5, 2, 3, 2, 9, 1 };
    v2 = { 4, 5, 7, 8, 3 };
    exp = { 0, 5, 0, 3, 6, 3, 3, 5, 4, 7 };
    if (!multTest(v1, v2, exp)) {
        return false;
    }

    v1 = { 4, 5, 7, 8, 3 };
    v2 = { 5, 2, 3, 2, 9, 1 };
    exp = { 0, 5, 0, 3, 6, 3, 3, 5, 4, 7 };
    if (!multTest(v1, v2, exp)) {
        return false;
    }

    v1 = { 1, 1, 1, 1, 1 };
    v2 = { 2, 2, 2, 2, 2, 2, 2, 2, 2 };
    exp = { 2, 4, 6, 8, 0, 1, 1, 1, 1, 9, 6, 4, 2 };
    if (!multTest(v1, v2, exp)) {
        return false;
    }

    v1 = { 2, 2, 2, 2, 2, 2, 2, 2, 2 };
    v2 = { 1, 1, 1, 1, 1 };
    exp = { 2, 4, 6, 8, 0, 1, 1, 1, 1, 9, 6, 4, 2 };
    if (!multTest(v1, v2, exp)) {
        return false;
    }

    return true;
}
