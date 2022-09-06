#include "IntegerAsVectors.h"
#include "PowerTests.h"

vector<int> inverse(vector<int> v) {

    vector<int> ret(v.size());
    for (int i = 0; i < v.size(); i++) {
        ret[i] = v[v.size() - 1 - i];
    }
    return ret;
}

bool powerTest(vector<int> v, int n, vector<int> exp)
{
    vector<int> act = power(v, n);

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

bool powerTests()
{
    // 1^0 = 1
    vector<int> v = { 1 };
    int a = 0;
    vector<int> exp = { 1 };
    if (!powerTest(v, a, exp)) {
        return false;
    }

    // 123^2 = 15129
    v = { 3,2,1 };
    a = 2;
    exp = { 9,2,1,5,1 };
    if (!powerTest(v, a, exp)) {
        return false;
    }

    // 1234^7 = 4 357 186 184 021 382 204 544
    v = { 4,3,2,1 };
    a = 7;
    exp = { 4,4,5,4,0,2,2,8,3,1,2,0,4,8,1,6,8,1,7,5,3,4 };
    if (!powerTest(v, a, exp)) {
        return false;
    }

    // 25^17 = 582 076 609 134 674 072 265 625
    v = { 5,2 };
    a = 17;
    exp = { 5,2,6,5,6,2,2,7,0,4,7,6,4,3,1,9,0,6,6,7,0,2,8,5 };
    if (!powerTest(v, a, exp)) {
        return false;
    }

    // 217^11 = 50 240 860 866 158 912 890 695 433
    v = { 7,1,2 };
    a = 11;
    exp = { 3,3,4,5,9,6,0,9,8,2,1,9,8,5,1,6,6,8,0,6,8,0,4,2,0,5 };
    if (!powerTest(v, a, exp)) {
        return false;
    }

    // 17^26 = 98 100 666 009 922 840 441 972 689 847 969
    v = { 7,1 };
    a = 26;
    exp = { 9,6,9,7,4,8,9,8,6,2,7,9,1,4,4,0,4,8,2,2,9,9,0,0,6,6,6,0,0,1,8,9 };
    if (!powerTest(v, a, exp)) {
        return false;
    }

    // 65^97 = 71 218 954 573 795 351 700 899 981 963 691 181 259 771 
    //            475 102 992 340 699 093 465 331 630 164 995 551 101 
    //            108 655 735 790 113 915 200 962 497 731 221 985 669 
    //            268 979 472 109 324 692 363 774 289 560 751 640 237 
    //            867 832 183 837 890 625
    v = { 5,6 };
    a = 97;
    exp = { 7,1, 2,1,8, 9,5,4, 5,7,3, 7,9,5, 3,5,1, 7,0,0, 8,9,9, 9,8,1, 9,6,3, 6,9,1, 1,8,1, 2,5,9, 7,7,1,
                    4,7,5, 1,0,2, 9,9,2, 3,4,0, 6,9,9, 0,9,3, 4,6,5, 3,3,1, 6,3,0, 1,6,4, 9,9,5, 5,5,1, 1,0,1,
                    1,0,8, 6,5,5, 7,3,5, 7,9,0, 1,1,3, 9,1,5, 2,0,0, 9,6,2, 4,9,7, 7,3,1, 2,2,1, 9,8,5, 6,6,9,
                    2,6,8, 9,7,9, 4,7,2, 1,0,9, 3,2,4, 6,9,2, 3,6,3, 7,7,4, 2,8,9, 5,6,0, 7,5,1, 6,4,0, 2,3,7,
                    8,6,7, 8,3,2, 1,8,3, 8,3,7, 8,9,0, 6,2,5 };
    exp = inverse(exp);
    if (!powerTest(v, a, exp)) {
        return false;
    }

    return true;
}
