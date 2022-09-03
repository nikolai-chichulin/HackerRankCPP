#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/// <summary>
/// Returns sum of two integers represented as vectors.
/// </summary>
/// <param name="a">The first integer as a vector.</param>
/// <param name="b">The second integer as a vector.</param>
/// <returns></returns>
vector<int> sum(vector<int> a, vector<int> b) {

    vector<int> ret;
    int la = static_cast<int>(a.size());
    int lb = static_cast<int>(b.size());
    int lmin = min(la, lb);
    int lmax = max(la, lb);
    int c = 0;
    for (int i = 0; i < lmin; i++) {
        int res = a[i] + b[i] + c;
        int rem = res % 10;
        c = res / 10;
        ret.push_back(rem);
    }

    if (la != lb) {
        bool aig = la >= lb;
        for (int i = lmin; i < lmax; i++) {
            int res = (aig ? a[i] : b[i]) + c;
            int rem = res % 10;
            c = res / 10;
            ret.push_back(rem);
        }
    }
    if (c > 0) {
        ret.push_back(c);
    }

    return ret;
}

/// <summary>
/// Returns multiplication of two integers, one of which is represented as a vector.
/// </summary>
/// <param name="a">The first integer as a vector.</param>
/// <param name="b">The second integer.</param>
/// <returns></returns>
vector<int> multuply(vector<int> a, int b) {

    vector<int> ret;

    int o = (int)log10(b) + 1; // number of orders

    if (b == 0) {
        ret.push_back(0);
    }
    else if (b == 1) {
        ret = a;
    }
    else {
        int m = b;
        for (int io = 0; io < o; io++) {

            // Current vector
            vector<int> retCurr;

            // Add leading zeroes
            for (int j = 0; j < io; j++) {
                retCurr.push_back(0);
            }

            // Multiplication
            int mm = m % 10;
            int c = 0;
            for (int ai : a) {

                int res = ai * mm + c;
                int rem = res % 10;
                c = res / 10;
                retCurr.push_back(rem);
            }
            if (c > 0) {
                retCurr.push_back(c);
            }

            // Adding to the main result
            ret = sum(ret, retCurr);

            // Go to the next order
            m /= 10;
        }
    }

    return ret;
}

vector<int> factorial(int a) {

    vector<int> ret;
    if (a == 0 || a == 1) {
        ret.push_back(1);
    }
    else {
        ret = multuply(factorial(a - 1), a);
    }
    return ret;
}

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

bool multTest(vector<int> v, int a, vector<int> exp) {

    vector<int> act = multuply(v, a);

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

bool multTests() {

    vector<int> v = { 1 };
    int a = 0;
    vector<int> exp = { 0 };
    if (!multTest(v, a, exp)) {
        return false;
    }

    v = { 3, 2, 1 };
    a = 2;
    exp = { 6, 4, 2 };
    if (!multTest(v, a, exp)) {
        return false;
    }

    v = { 9, 0, 8, 0, 7, 0, 6, 0, 4, 0, 3, 0, 2, 0, 1 };
    a = 919;
    exp = { 1, 7, 4, 3, 7, 0, 9, 7, 1, 3, 4, 9, 5, 6, 7, 3, 9 };
    if (!multTest(v, a, exp)) {
        return false;
    }

    v = { 9, 0, 8, 0, 7, 0, 6, 0, 4, 0, 3, 0, 2, 0, 1 };
    a = 11111;
    exp = { 9, 9, 7, 8, 5, 7, 2, 5, 8, 1, 4, 8, 9, 5, 6, 3, 3, 1, 1 };
    if (!multTest(v, a, exp)) {
        return false;
    }

    return true;
}

int solve(int n) {

    vector<int> v = factorial(n);

    int ret = 0;
    for (int d : v) {
        ret += d;
    }

    return ret;
}

int main() {

    //vector<int> v = { 7, 8, 3, 2 };
    //vector<int> res = multuply(v, 13);

    //for (int i : res) {
    //    cout << i << " ";
    //}
    //cout << endl;

    // vector<int> res = factorial(100);

    for (int n = 0; n <= 1000; n++) {
        cout << n << " : " << solve(n) << endl;
    }

    // cout << (sumTests() ? "Passed" : "Failed") << endl;
    // cout << (multTests() ? "Passed" : "Failed") << endl;

    return 0;
}
