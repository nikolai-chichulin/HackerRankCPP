#include "typedefs.h"

#include "IntegerAsVectors.h"
#include "Util.h"
#include "FactTests.h"

bool factTest(ls a, vl exp) {

    vl act = factorial(a);

    if (exp.size() != act.size()) {
        return false;
    }

    for (ls i = 0; i < exp.size(); i++) {
        if (exp[i] != act[i]) {
            return false;
        }
    }

    return true;
}

bool factTests() {

    ls a = 0;
    vl exp = { 1 };
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
