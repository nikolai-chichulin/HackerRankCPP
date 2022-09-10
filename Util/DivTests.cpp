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
    vector<int> v1 = { 4,5,2,7,4,1 };
    vector<int> v2 = { 3,2 };
    pair<vector<int>, vector<int>> exp({ 2,0,4,6 }, { 8 });
    if (!divTest(v1, v2, exp)) {
        return false;
    }

    return true;
}
