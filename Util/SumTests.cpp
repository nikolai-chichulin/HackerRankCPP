#include "IntegerAsVectors.h"

bool sumTest(vector<int> v1, vector<int> v2, vector<int> exp) {

    vector<int> act = sum(v1, v2);

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

bool sumTests() {

    vector<int> v1 = { 4, 5, 7, 8, 3 };
    vector<int> v2 = { 5, 2, 3, 2, 9, 1 };
    vector<int> exp = { 9, 7, 0, 1, 3, 2 };
    if (!sumTest(v1, v2, exp)) {
        return false;
    }

    v1 = { 5, 2, 3, 2, 9, 1 };
    v2 = { 4, 5, 7, 8, 3 };
    exp = { 9, 7, 0, 1, 3, 2 };
    if (!sumTest(v1, v2, exp)) {
        return false;
    }

    v1 = { 1 };
    v2 = { 5, 7, 8, 3 };
    exp = { 6, 7, 8, 3 };
    if (!sumTest(v1, v2, exp)) {
        return false;
    }

    v1 = { 5, 7, 8, 3 };
    v2 = { 1 };
    exp = { 6, 7, 8, 3 };
    if (!sumTest(v1, v2, exp)) {
        return false;
    }

    v1 = { 0 };
    v2 = { 5, 7, 8, 3 };
    exp = { 5, 7, 8, 3 };
    if (!sumTest(v1, v2, exp)) {
        return false;
    }

    v1 = { 5, 7, 8, 3 };
    v2 = { 0 };
    exp = { 5, 7, 8, 3 };
    if (!sumTest(v1, v2, exp)) {
        return false;
    }

    v1 = { 9, 0, 9, 0, 9 };
    v2 = { 9, 0, 9, 0, 9, 0, 9 };
    exp = { 8, 1, 8, 1, 8, 1, 9 };
    if (!sumTest(v1, v2, exp)) {
        return false;
    }

    v1 = { 9, 0, 9, 0, 9, 0, 9 };
    v2 = { 9, 0, 9, 0, 9 };
    exp = { 8, 1, 8, 1, 8, 1, 9 };
    if (!sumTest(v1, v2, exp)) {
        return false;
    }

    return true;
}
