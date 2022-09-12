#include "CompDecompTests.h"

bool compTest(vector<int> basis[], vector<int> terms[], int n, vector<int> exp)
{
    vector<int> act = comp(basis, terms, n);

    if (!equalto(act, exp)) {
        return false;
    }

    return true;
}

bool compTests()
{
    vector<int> basis[] = { {0,8,8,2,6,3},{0,2,3,0,4},{0,4,0,5},{0,2,7},{0,2,1},{4,2},{6},{2},{1} };
    int n = 9;

    vector<int> terms[] = { {1},{2},{4},{5},{3},{2},{6},{2},{4} };
    vector<int> exp = { 2,3,7,7,6,4 }; // 467732

    if (!compTest(basis, terms, n, exp)) {
        return false;
    }

    return true;
}

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

    vector<int> v1{ 6,2,1,2,5,2,1 };
    vector<int> exp1[]{ {3},{4},{0},{3},{0},{1},{3},{2},{0} };
    if (!decompTest(v1, basis, n, exp1)) {
        return false;
    }

    vector<int> v2{ 7,3,1,4,8,9,5,3,4,2,1,5,4,8,9,1,7 };
    vector<int> exp2[]{ {8,3,8,8,1,0,0,7,3,8,9,1},{1},{2},{0},{2},{2},{1},{1},{1} };
    if (!decompTest(v2, basis, n, exp2)) {
        return false;
    }

    return true;
}
