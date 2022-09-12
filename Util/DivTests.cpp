#include <utility>

#include "IntegerAsVectors.h"
#include "Util.h"
#include "DivTests.h"

bool divTest(vector<int> v1, vector<int> v2, pair<vector<int>, vector<int>> exp)
{
    pair<vector<int>, vector<int>> act = divide(v1, v2);

    if (exp.first.size() != act.first.size() || exp.second.size() != act.second.size()) {
        return false;
    }

    for (int i = 0; i < exp.first.size(); i++) {
        if (exp.first[i] != act.first[i]) {
            return false;
        }
    }

    for (int i = 0; i < exp.second.size(); i++) {
        if (exp.second[i] != act.second[i]) {
            return false;
        }
    }

    return true;
}

bool divTests()
{
    vector<int> v1 = { 9,8,2,6,4 };
    vector<int> v2 = { 4,5,6 };
    pair<vector<int>, vector<int>> exp({ 0,7 }, { 9,0,5 });
    if (!divTest(v1, v2, exp)) {
        return false;
    }

    v1 = { 4,5,2,7,4,1 };
    v2 = { 3,2 };
    exp = pair<vector<int>, vector<int>>({ 2,0,4,6 }, { 8 });
    if (!divTest(v1, v2, exp)) {
        return false;
    }

    v1 = { 9,8,2,6,4 };
    v2 = { 4,5,6 };
    exp = pair<vector<int>, vector<int>>({ 0,7 }, { 9,0,5 });
    if (!divTest(v1, v2, exp)) {
        return false;
    }

    v1 = { 4,5,2 };
    v2 = { 1 };
    exp = pair<vector<int>, vector<int>>({ 4,5,2 }, { 0 });
    if (!divTest(v1, v2, exp)) {
        return false;
    }

    v1 = { 1 };
    v2 = { 4,5,2 };
    exp = pair<vector<int>, vector<int>>({ 0 }, { 1 });
    if (!divTest(v1, v2, exp)) {
        return false;
    }

    v1 = { 5,5,5,5,5,5,5,5,5,5 };
    v2 = { 1,1,1,1,1,1,1 };
    exp = pair<vector<int>, vector<int>>({ 0,0,0,5 }, { 5,5,5 });
    if (!divTest(v1, v2, exp)) {
        return false;
    }

    v1 = { 9,9,9,9,9,9,9,9,9,9 };
    v2 = { 2,1,2,1,2,1,2 };
    exp = pair<vector<int>, vector<int>>({ 4,1,7,4 }, { 1,3,6,6,0,6 });
    if (!divTest(v1, v2, exp)) {
        return false;
    }

    v1 = { 0,0,0,9,9,9,9,9 };
    v2 = { 0,0,7,7,0,7,7 };
    exp = pair<vector<int>, vector<int>>({ 2,1 }, { 0,0,6,6,0,5,7 });
    if (!divTest(v1, v2, exp)) {
        return false;
    }

    v1 = { 0,0,0,9,9,9,9,9,0,0,0 };
    v2 = { 0,0,7,7,0,7,7,0,0 };
    exp = pair<vector<int>, vector<int>>({ 2,1 }, { 0,0,6,6,0,5,7 });
    if (!divTest(v1, v2, exp)) {
        return false;
    }

    v1 = { 1,1,0,0,0,0 };
    v2 = { 0,0,0,0,0,0,0,0,0,0 };
    exp = pair<vector<int>, vector<int>>({  }, {  });
    if (!divTest(v1, v2, exp)) {
        return false;
    }

    return true;
}
