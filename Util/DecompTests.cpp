#include "DecompTests.h"

bool decompTest(vector<int> v, vector<int> basis[], int n, vector<int> exp[])
{
    vector<int>* act = decomp(v, basis, n);

    for (int i = 0; i < n; i++) {
        if (!equalto(act[i], exp[i])) {
            return false;
        }
    }

    return true;
}

bool decompTests()
{
    vector<int> basis[] = { {0,8,8,2,6,3},{0,2,3,0,4},{0,4,0,5},{0,2,7},{0,2,1},{4,2},{6},{2},{1} };
    int n = 9;
    vector<int> v{ 6,2,1,2,5,2,1 };
    vector<int> exp[] = { {3},{4},{0},{3},{0},{1},{3},{2},{0} };
    if (!decompTest(v, basis, 9, exp)) {
        return false;
    }

    return true;
}
