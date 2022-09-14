#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>

#include "typedefs.h"

#include "IntegerAsVectors.h"

using namespace std;

/// Compares two vectors. Returns true if the first is less than the second.
bool lessthan(vl v1, vl v2)
{
    if (v1.size() < v2.size()) {
        return true;
    }
    if (v1.size() > v2.size()) {
        return false;
    }
    for (ls i = (ls)v1.size() - 1; i >= 0; i--) {
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
bool equalto(vl v1, vl v2)
{
    if (v1.size() != v2.size()) {
        return false;
    }
    for (ls i = (ls)v1.size() - 1; i >= 0; i--) {
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
vl sum(vl a, vl b) {

    vl ret;
    ls la = static_cast<ls>(a.size());
    ls lb = static_cast<ls>(b.size());
    ls lmin = min(la, lb);
    ls lmax = max(la, lb);
    ls c = 0;
    for (ls i = 0; i < lmin; i++) {
        ls res = a[i] + b[i] + c;
        ls rem = res % 10;
        c = res / 10;
        ret.push_back(rem);
    }

    if (la != lb) {
        bool aig = la >= lb;
        for (ls i = lmin; i < lmax; i++) {
            ls res = (aig ? a[i] : b[i]) + c;
            ls rem = res % 10;
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
vl subtr(vl a, vl b) {

    vl ret;
    ls la = static_cast<ls>(a.size());
    ls lb = static_cast<ls>(b.size());
    ls lmax = max(la, lb);
    ls c = 0;
    for (ls i = 0; i < lmax; i++) {
        ls minuend = i < a.size() ? a[i] - c : -c;
        ls subtrahend = i < b.size() ? b[i] : 0;
        c = 0;
        if (minuend < subtrahend) {
            minuend += 10;
            c = 1;
        }
        ls res = minuend - subtrahend;
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
vl multiply(vl a, ls b) {

    vl ret;

    ls o = (ls)log10(b) + 1; // number of orders

    if (b == 0) {
        ret.push_back(0);
    }
    else if (b == 1) {
        ret = a;
    }
    else {
        ls m = b;
        for (ls io = 0; io < o; io++) {

            // Current vector
            vl retCurr;

            // Add leading zeroes
            for (ls j = 0; j < io; j++) {
                retCurr.push_back(0);
            }

            // Multiplication
            ls mm = m % 10;
            ls c = 0;
            for (ls ai : a) {

                ls res = ai * mm + c;
                ls rem = res % 10;
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
/// Returns multiplication of two integers represented as vectors of ls.
/// </summary>
/// <param name="a">The first integer.</param>
/// <param name="b">The second integer.</param>
/// <returns></returns>
vl multiply(vl a, vl b) {

    vl ret;
    for (ls i = 0; i < b.size(); i++) {

        // Current vector
        vl retCurr;

        // Add leading zeroes
        for (ls j = 0; j < i; j++) {
            retCurr.push_back(0);
        }

        // Multiplication
        ls mm = b[i];
        ls c = 0;
        for (ls ai : a) {

            ls res = ai * mm + c;
            ls rem = res % 10;
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
/// Division of one vector by another. Returns integer part of the result and the remainder.
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
pair<vl, vl> divide(vl v1, vl v2) {

    pair<vl, vl> ret;

    // Erase the leading zeros
    while (v1.size() > 0 && v1[v1.size() - 1] == 0) {
        v1.erase(v1.end() - 1);
    }
    while (v2.size() > 0 && v2[v2.size() - 1] == 0) {
        v2.erase(v2.end() - 1);
    }

    // Zero divident, return zero
    if (v1.size() == 0) {
        ret.first.push_back(0);
        ret.second = v1;
        return ret;
    }

    // Zero divider, return empty pair
    if (v2.size() == 0) {
        return ret;
    }

    // Divident is lesser than the divider, return {{0},{v1}}
    if (lessthan(v1, v2)) {
        ret.first.push_back(0);
        ret.second = v1;
        return ret;
    }

    // The divider is equal to 1
    if (v2.size() == 1 && v2[0] == 1) {
        ret.first = v1;
        ret.second.push_back({ 0 });
        return ret;
    }

    // Create a subvector
    // "minuend" - "subtrahend"
    auto first = v1.end() - v2.size();
    auto last = v1.end();
    vl minuend = { first, last };
    vl subtrahend(v2);

    // If the subvector is less than the divider, add the next digit
    while (first != v1.begin() && lessthan(minuend, subtrahend)) {
        first--;
        minuend = { first, last };
    }

    // The first subtraction
    ls m = 1; // the maximal multiplicator
    vl subtrahendPrev;
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
        while (minuend.size() > 0 && minuend[minuend.size() - 1] == 0) {
            minuend.erase(minuend.end() - 1);
        }

        bool done = false;
        // If the divident is less than the divider:
        while (lessthan(minuend, subtrahend)) {
            if (first == v1.begin()) { // if we reached the bigining, add 0 and stop
                ret.first.insert(ret.first.begin(), 0);
                done = true;
                break;
            }
            else { // move futher otherwise
                minuend.insert(minuend.begin(), *(--first));
                ret.first.insert(ret.first.begin(), 0);
            }
        }

        // Erase the leading zeros
        while (minuend.size() > 0 && minuend[minuend.size() - 1] == 0) {
            minuend.erase(minuend.end() - 1);
        }

        if (done) {
            break;
        }

        // Find the next digit
        while (lessthan(subtrahend, minuend) || equalto(subtrahend, minuend)) {
            m++;
            subtrahendPrev = subtrahend;
            subtrahend = sum(v2, subtrahend);
        }
        ret.first.insert(ret.first.begin(), --m);
        minuend = subtr(minuend, subtrahendPrev);
        subtrahend = v2;
    }

    ret.second = minuend;
    return ret;
}

vl power(vl v, ls n) {

    if (n == 0 || n == 1) {
        return v;
    }

    if (n == 2) {
        return multiply(v, v);
    }

    ls n2 = (ls)(log(n) / log(2.));
    ls rem = n % ((ls)pow(2, n2));

    vl ret = multiply(v, v);
    for (ls i = 1; i < n2; i++) {
        ret = multiply(ret, ret);
    }

    for (ls i = 0; i < rem; i++) {
        ret = multiply(ret, v);
    }

    return ret;
}

vl powers[1300][500];

vl power(vl v, ls iv, ls n) {

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

    ls n2 = (ls)(log(n) / log(2.));
    ls rem = n % ((ls)pow(2, n2));

    vl ret = power(v, iv, 2); // multuply(v, v);
    ls p = 2; // power of 2

    for (ls i = 1; i < n2; i++) {
        p *= 2;
        ret = multiply(ret, ret);
        powers[iv][p] = ret;
    }

    for (ls i = 0; i < rem; i++) {
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
vl factorial(ls a) {

    vl ret;
    if (a == 0 || a == 1) {
        ret.push_back(1);
    }
    else {
        ret = multiply(factorial(a - 1), a);
    }
    return ret;
}

vl facts[1000];

/// <summary>
/// Returns factorial as a vector of ints. Variant with memorization.
/// </summary>
/// <param name="a">The values to caculate factorial.</param>
/// <returns></returns>
vl factorialM(ls a) {

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

/// <summary>
/// Composition of integer from the given basis.
/// </summary>
/// <param name="basis">The basis as an array of vectors.</param>
/// <param name="terms">The terms to compose.</param>
/// <param name="n">Number of basic numbers.</param>
/// <returns></returns>
vl comp(vl basis[], vl terms[], ls n)
{
    vl ret;
    for (ls i = 0; i < n; i++) {
        ret = sum(ret, multiply(terms[i], basis[i]));
    }
    return ret;
}

/// <summary>
/// Decomposition of a big integer in a basis.
/// </summary>
/// <param name="v">The integer.</param>
/// <param name="basis">The basis as an array of vectors.</param>
/// <param name="n">Number of basic numbers.</param>
/// <returns></returns>
vl* decomp(vl v, vl basis[], ls n)
{
    vl* ret = new vl[n];
    vl rem = v;

    // Assume the terms are in descending order: {99, 71, 33, 17...}
    for (ls i = 0; i < n; i++) {
        pair<vl, vl> res = divide(rem, basis[i]);
        ret[i] = res.first;
        rem = res.second;
    }

    return ret;
}
