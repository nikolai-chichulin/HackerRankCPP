#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

#include "IntegerAsVectors.h"

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

/// <summary>
/// Returns multiplication of two integers represented as vectors of int.
/// </summary>
/// <param name="a">The first integer.</param>
/// <param name="b">The second integer.</param>
/// <returns></returns>
vector<int> multuply(vector<int> a, vector<int> b) {

    vector<int> ret;
    for (int i = 0; i < b.size(); i++) {

        // Current vector
        vector<int> retCurr;

        // Add leading zeroes
        for (int j = 0; j < i; j++) {
            retCurr.push_back(0);
        }

        // Multiplication
        int mm = b[i];
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
    }

    return ret;
}

vector<int> power(vector<int> v, int n) {

    if (n == 0 || n == 1) {
        return v;
    }

    if (n == 2) {
        return multuply(v, v);
    }

    int n2 = (int)(log(n) / log(2.));
    int rem = n % ((int)pow(2, n2));

    vector<int> ret = multuply(v, v);
    for (int i = 1; i < n2; i++) {
        ret = multuply(ret, ret);
    }

    for (int i = 0; i < rem; i++) {
        ret = multuply(ret, v);
    }

    return ret;
}

vector<int> powers[1000][500];

vector<int> power(vector<int> v, int i, int n) {

    if (!powers[i][n].empty()) {
        return powers[i][n];
    }

    if (n == 0 || n == 1) {
        powers[i][n] = v;
        return powers[i][n];
    }

    if (n == 2) {
        powers[i][n] = multuply(v, v);
        return powers[i][n];
    }

    int n2 = (int)(log(n) / log(2.));
    int rem = n % ((int)pow(2, n2));

    vector<int> ret = multuply(v, v);
    for (int i = 1; i < n2; i++) {
        ret = multuply(ret, ret);
    }

    for (int i = 0; i < rem; i++) {
        ret = multuply(ret, v);
    }

    return ret;
}

/// <summary>
/// Returns factorial as a vector of ints.
/// </summary>
/// <param name="a">The values to caculate factorial.</param>
/// <returns></returns>
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
