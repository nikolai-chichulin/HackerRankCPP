#include "typedefs.h"

#include "IntegerAsVectors.h"
#include "Util.h"
#include "CompDecompTests.h"

bool compTest(vl basis[], vl terms[], ls n, vl exp)
{
    vl act = comp(basis, terms, n);

    if (!equalto(act, exp)) {
        return false;
    }

    return true;
}

bool compTests()
{
    vl basis[] = { {0,8,8,2,6,3},{0,2,3,0,4},{0,4,0,5},{0,2,7},{0,2,1},{4,2},{6},{2},{1} };
    ls n = 9;

    vl terms[] = { {1},{2},{4},{5},{3},{2},{6},{2},{4} };
    vl exp = { 2,3,7,7,6,4 }; // 467732

    if (!compTest(basis, terms, n, exp)) {
        return false;
    }

    return true;
}

bool decompTest(vl v, vl basis[], ls n, vl exp[])
{
    vl* act = decomp(v, basis, n);

    for (ls i = 0; i < n; i++) {
        if (!equalto(act[i], exp[i])) {
            return false;
        }
    }

    return true;
}

bool decompTests()
{
    vl basis[] = { {0,8,8,2,6,3},{0,2,3,0,4},{0,4,0,5},{0,2,7},{0,2,1},{4,2},{6},{2},{1} };
    ls n = 9;

    vl v1{ 6,2,1,2,5,2,1 };
    vl exp1[]{ {3},{4},{0},{3},{0},{1},{3},{2},{0} };
    if (!decompTest(v1, basis, n, exp1)) {
        return false;
    }

    vl v2{ 7,3,1,4,8,9,5,3,4,2,1,5,4,8,9,1,7 };
    vl exp2[]{ {8,3,8,8,1,0,0,7,3,8,9,1},{1},{2},{0},{2},{2},{1},{1},{1} };
    if (!decompTest(v2, basis, n, exp2)) {
        return false;
    }

    //vl v3{ 4,8,9,9,9,9,9 };
    //v3 = inverse(v3);
    //vl exp3[]{ {8,3,8,8,1,0,0,7,3,8,9,1},{1},{2},{0},{2},{2},{1},{1},{1} };
    //if (!decompTest(v3, basis, n, exp3)) {
    //    return false;
    //}

    return true;
}
