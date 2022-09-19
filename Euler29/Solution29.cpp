#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <set>

#include "BigInteger.h"

using namespace std;

typedef long long li;

ofstream outf;

bool passed[100001];

li pcv[] = { 0,0,
    1,4,8,15,23,34,44,54,69,88,106,129,152,177,195,226,256,291,324,361,399,442,483,519,564,600,648,703,755,814,856,915,976,1039,1085,
    1156,1224,1295,1365,1444,1519,1602,1681,1762,1846,1937,2023,2095,2184,2279,2373,2476,2574,2677,2779,2886,2993,3108,3216,3335,3450,
    3569,3648,3771,3890,4021,4147,4277,4406,4545,4676,4819,4957,5098,5240,5391,5534,5689,5838,5946,6099,6262,6416,6579,6740,6906,7070,
    7245,7412,7591,7763,7941,8118,8301,8479,8670,8855,9045,9183,9382,9572,9775,9970,10171,10371,10582,10783,10998,11205,11419,11630,11853,
    12067,12290,12509,12735,12959,13194,13419,13599,13830,14068,14302,14484,14720,14971,15154,15402,15648,15907,16154,16411,16666,16925,
    17183,17454,17714,17989,18252,18524,18795,19078,19278,19561,19839,20120,20401,20696,20979,21278,21567,21863,22154,22457,22751,23062,
    23364,23672,23976,24289,24596,24919,25232,25551,25869,26200,26517,26769,27093,27425,27753,28096,28426,28767,29103,29447,29788,30143,
    30484,30843,31189,31545,31897,32260,32614,32985,33345,33710,34074,34453,34818,35201,35574,35953,36229,36620,36997,37392,37774,38166,
    38554,38951,39339,39742,40138,40542,40941,41356,41756,42175,42582,42998,43410,43833,44138,44563,44983,45409,45831 };

li solve(li n) {

    li s = 0;
    for (li i = 2; i <= n; i++) {
        li base = i;
        if (!passed[base]) { // not yet calculated
            s += n - 1; // powers of i
            passed[base] = true;
            // account for the powers of powers of i: i^j
            for (li j = 2; j < 1000000; j++) {
                base *= i;
                if (base > n) {
                    break;
                }
                for (li k = 2; k <= n; k++) {
                    if (j * k > n) {
                        s++;
                    }
                }
                passed[base] = true;
            }
        }
    }
    return s;
}

li solveII(li n) {

    li s = 0;
    for (li base = 2; base <= n; base++) {
        set<li> v; // store the base raised to the powers
        li start = base;
        if (!passed[start]) { // this row wasn't calculated yet

            s += n - 1; // powers of i
            for (li k = 2; k <= n; k++) {
                if (v.find(k) == v.end()) {
                    v.insert(k);
                }
            }
            passed[start] = true; // the base was calculated

            // account for the next powers of the base: base^k = (i^p)^k = i^(pk), p >= 2
            for (li p = 2; p < 1000000; p++) {
                start *= base;
                if (start > n) {
                    break;
                }
                if (!passed[start]) { // base-th row wasn't calculated yet
                    for (li k = 2; k <= n; k++) {
                        li tp = p * k; // total power of the base, not the starting number
                        if (v.find(tp) == v.end()) {
                            s++;
                            v.insert(tp);
                        }
                    }
                    passed[start] = true; // the base was calculated
                }
            }
        }
    }
    return s;
}

int main() {

    li res = solveII(99999);

    //outf.open("Euler29rnd.txt");
    //for (int n = 2; n <= 200; n++) {

    //    for (int i = 0; i < 100001; i++) {
    //        passed[i] = false;
    //    }

    //    li resExp = pcv[n];
    //    li res = solveII(n);
    //    if (res != resExp) {
    //        cout << "Alarm!" << endl;
    //        break;
    //    }
    //    outf << n << " " << res << endl;
    //    if (n % 1 == 0) {
    //        cout << n << " " << res << endl;
    //    }
    //}
    //outf.close();
    return 0;
}
