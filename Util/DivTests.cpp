#include <utility>

#include "typedefs.h"

#include "IntegerAsVectors.h"
#include "Util.h"
#include "DivTests.h"

bool divTest(vl v1, vl v2, pair<vl, vl> exp)
{
    pair<vl, vl> act = divide(v1, v2);

    if (exp.first.size() != act.first.size() || exp.second.size() != act.second.size()) {
        return false;
    }

    for (ls i = 0; i < exp.first.size(); i++) {
        if (exp.first[i] != act.first[i]) {
            return false;
        }
    }

    for (ls i = 0; i < exp.second.size(); i++) {
        if (exp.second[i] != act.second[i]) {
            return false;
        }
    }

    return true;
}

bool divTests()
{
    vl v1 = { 9,8,2,6,4 };
    vl v2 = { 4,5,6 };
    pair<vl, vl> exp({ 0,7 }, { 9,0,5 });
    if (!divTest(v1, v2, exp)) {
        return false;
    }

    v1 = { 4,5,2,7,4,1 };
    v2 = { 3,2 };
    exp = pair<vl, vl>({ 2,0,4,6 }, { 8 });
    if (!divTest(v1, v2, exp)) {
        return false;
    }

    v1 = { 9,8,2,6,4 };
    v2 = { 4,5,6 };
    exp = pair<vl, vl>({ 0,7 }, { 9,0,5 });
    if (!divTest(v1, v2, exp)) {
        return false;
    }

    v1 = { 4,5,2 };
    v2 = { 1 };
    exp = pair<vl, vl>({ 4,5,2 }, { 0 });
    if (!divTest(v1, v2, exp)) {
        return false;
    }

    v1 = { 1 };
    v2 = { 4,5,2 };
    exp = pair<vl, vl>({ 0 }, { 1 });
    if (!divTest(v1, v2, exp)) {
        return false;
    }

    v1 = { 5,5,5,5,5,5,5,5,5,5 };
    v2 = { 1,1,1,1,1,1,1 };
    exp = pair<vl, vl>({ 0,0,0,5 }, { 5,5,5 });
    if (!divTest(v1, v2, exp)) {
        return false;
    }

    v1 = { 9,9,9,9,9,9,9,9,9,9 };
    v2 = { 2,1,2,1,2,1,2 };
    exp = pair<vl, vl>({ 4,1,7,4 }, { 1,3,6,6,0,6 });
    if (!divTest(v1, v2, exp)) {
        return false;
    }

    v1 = { 0,0,0,9,9,9,9,9 };
    v2 = { 0,0,7,7,0,7,7 };
    exp = pair<vl, vl>({ 2,1 }, { 0,0,6,6,0,5,7 });
    if (!divTest(v1, v2, exp)) {
        return false;
    }

    v1 = { 0,0,0,9,9,9,9,9,0,0,0 };
    v2 = { 0,0,7,7,0,7,7,0,0 };
    exp = pair<vl, vl>({ 2,1 }, { 0,0,6,6,0,5,7 });
    if (!divTest(v1, v2, exp)) {
        return false;
    }

    v1 = { 1,1,0,0,0,0 };
    v2 = { 0,0,0,0,0,0,0,0,0,0 };
    exp = pair<vl, vl>({  }, {  });
    if (!divTest(v1, v2, exp)) {
        return false;
    }

    // 31536601576561183883451*59520366631203959071+920666176026519=1877070088139126456906464448883776014260540
    v1 = { 1,8,7,7,0,7,0,0,8,8,1,3,9,1,2,6,4,5,6,9,0,6,4,6,4,4,4,8,8,8,3,7,7,6,0,1,4,2,6,0,5,4,0 };
    v1 = inverse(v1);
    v2 = { 3,1,5,3,6,6,0,1,5,7,6,5,6,1,1,8,3,8,8,3,4,5,1 };
    v2 = inverse(v2);
    exp = pair<vl, vl>({ 1,7,0,9,5,9,3,0,2,1,3,6,6,6,3,0,2,5,9,5 }, { 9,1,5,6,2,0,6,7,1,6,6,6,0,2,9 });
    if (!divTest(v1, v2, exp)) {
        return false;
    }

    return true;
}
