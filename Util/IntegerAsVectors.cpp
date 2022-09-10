#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>

#include "IntegerAsVectors.h"

using namespace std;

/// Compares two vectors. Returns true if the first is less than the second.
bool lessthan(vector<int> v1, vector<int> v2)
{
    if (v1.size() < v2.size()) {
        return true;
    }
    if (v1.size() > v2.size()) {
        return false;
    }
    for (int i = v1.size() - 1; i >= 0; i--) {
        if (v1[i] < v2[i]) {
            return true;
        }
        else if (v1[i] > v2[i]) {
            return false;
        }
    }
    return false;
}

/// Compares two vectors. Returns true if the first is equal to the second.
bool equalto(vector<int> v1, vector<int> v2)
{
    if (v1.size() != v2.size()) {
        return false;
    }
    for (int i = v1.size() - 1; i >= 0; i--) {
        if (v1[i] != v2[i]) {
            return false;
        }
    }
    return true;
}

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
/// Subtracts a lesser (second) integer from a greater (first) one. Both are represented as vectors.
/// The first value must be greater or equal to the second one.
/// The result is NOT guaranteed otherwise.
/// </summary>
/// <param name="a">The first integer as a vector.</param>
/// <param name="b">The second integer as a vector.</param>
/// <returns></returns>
vector<int> subtr(vector<int> a, vector<int> b) {

    vector<int> ret;
    int la = static_cast<int>(a.size());
    int lb = static_cast<int>(b.size());
    int lmax = max(la, lb);
    int c = 0;
    for (int i = 0; i < lmax; i++) {
        int minuend = i < a.size() ? a[i] - c : -c;
        int subtrahend = i < b.size() ? b[i] : 0;
        c = 0;
        if (minuend < subtrahend) {
            minuend += 10;
            c = 1;
        }
        int res = minuend - subtrahend;
        ret.push_back(res);
    }

    // Erase the leading zeros
    while (ret.size() > 1 && ret[ret.size() - 1] == 0) {
        ret.erase(ret.end() - 1);
    }

    return ret;
}

/// <summary>
/// Returns multiplication of two integers, one of which is represented as a vector.
/// </summary>
/// <param name="a">The first integer as a vector.</param>
/// <param name="b">The second integer.</param>
/// <returns></returns>
vector<int> multiply(vector<int> a, int b) {

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
vector<int> multiply(vector<int> a, vector<int> b) {

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

/// <summary>
/// Division of one vector by another. Returns integer part of the result.
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
pair<vector<int>, vector<int>> divide(vector<int> v1, vector<int> v2) {

    pair<vector<int>, vector<int>> ret;

    if (lessthan(v1, v2)) {
        ret.first.push_back(0);
        return ret; // the first is less than the secons, return { 0 }
    }

    // Create a subvector
    // "minuend" - "subtrahend"
    auto first = v1.end() - v2.size();
    auto last = v1.end();
    vector<int> minuend = { first, last };
    vector<int> subtrahend(v2);

    while (lessthan(minuend, subtrahend)) {
        first--;
        minuend = { first, last };
    }

    // The first subtraction
    int m = 1; // the maximal multiplicator
    vector<int> subtrahendPrev;
    do {
        m++;
        subtrahendPrev = subtrahend;
        subtrahend = sum(v2, subtrahend);
    } while (lessthan(subtrahend, minuend) || equalto(subtrahend, minuend));
    ret.first.insert(ret.first.begin(), --m);
    minuend = subtr(minuend, subtrahendPrev);
    subtrahend = v2;

    // The following subtractions to the begining of v1
    while (first != v1.begin()) {
        m = 1;
        minuend.insert(minuend.begin(), *(--first));

        // Erase the leading zeros
        while (minuend.size() > 1 && minuend[minuend.size() - 1] == 0) {
            minuend.erase(minuend.end() - 1);
        }

        // Move futher if less than the divisor
        while (lessthan(minuend, subtrahend)) {
            minuend.insert(minuend.begin(), *(--first));
            ret.first.insert(ret.first.begin(), 0);
        }

        do {
            m++;
            subtrahendPrev = subtrahend;
            subtrahend = sum(v2, subtrahend);
        } while (lessthan(subtrahend, minuend) || equalto(subtrahend, minuend));
        ret.first.insert(ret.first.begin(), --m);
        minuend = subtr(minuend, subtrahendPrev);
        subtrahend = v2;
    }

    ret.second = minuend;
    return ret;
}

vector<int> power(vector<int> v, int n) {

    if (n == 0 || n == 1) {
        return v;
    }

    if (n == 2) {
        return multiply(v, v);
    }

    int n2 = (int)(log(n) / log(2.));
    int rem = n % ((int)pow(2, n2));

    vector<int> ret = multiply(v, v);
    for (int i = 1; i < n2; i++) {
        ret = multiply(ret, ret);
    }

    for (int i = 0; i < rem; i++) {
        ret = multiply(ret, v);
    }

    return ret;
}

vector<int> powers[1300][500];

vector<int> power(vector<int> v, int iv, int n) {

    if (!powers[iv][n].empty()) {
        return powers[iv][n];
    }

    if (n == 0 || n == 1) {
        powers[iv][n] = v;
        return powers[iv][n];
    }

    if (n == 2) {
        powers[iv][n] = multiply(v, v);
        return powers[iv][n];
    }

    int n2 = (int)(log(n) / log(2.));
    int rem = n % ((int)pow(2, n2));

    vector<int> ret = power(v, iv, 2); // multuply(v, v);
    int p = 2; // power of 2

    for (int i = 1; i < n2; i++) {
        p *= 2;
        ret = multiply(ret, ret);
        powers[iv][p] = ret;
    }

    for (int i = 0; i < rem; i++) {
        p += 1;
        ret = multiply(ret, v);
        powers[iv][p] = ret;
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
        ret = multiply(factorial(a - 1), a);
    }
    return ret;
}

vector<int> facts[1000];

/// <summary>
/// Returns factorial as a vector of ints. Variant with memorization.
/// </summary>
/// <param name="a">The values to caculate factorial.</param>
/// <returns></returns>
vector<int> factorialM(int a) {

    if (!facts[a].empty()) {
        return facts[a];
    }

    if (a == 0 || a == 1) {
        facts[a].push_back(1);
    }
    else {
        facts[a] = multiply(factorial(a - 1), a);
    }
    return facts[a];
}
