#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>

#include "BigInteger.h"

const char bi::GROUP_SEPARATOR = ' ';

bi::bi()
{
}

bi::bi(int i) :bi((long long)i)
{
}

bi::bi(long long i)
{
    negative = i < 0 ? true : false;

    long long res = abs(i);
    int rem = 1;
    int div = 10;
    while (res > 0) {
        rem = res % div;
        v.push_back(rem);
        res /= 10;
    }
}

bi::bi(const std::string& s)
{
    if (s[0] == '-') {
        negative = true;
    }

    bool zeroallowed = false;
    for (char c : s) {
        if (((zeroallowed && c - '0' >= 0) || (!zeroallowed && c - '0' > 0)) && c - '0' < 10) {
            this->v.insert(v.begin(), c - '0');
            zeroallowed = true;
        }
    }
}

/// <summary>
/// Constructor from the given vector.
/// </summary>
/// <param name="v">Vector of ints in reversed order.</param>
bi::bi(vector<int>& v)
{
    // Erase the leading zeros
    while (v.size() > 1 && v[v.size() - 1] == 0) {
        v.erase(v.end() - 1);
    }

    this->v = v;
    this->negative = false;
}

bi::~bi()
{
}

bi bi::zero()
{
    return bi();
}

bi bi::unity()
{
    return bi(1);
}

bi bi::operator+(const bi& rhs) const
{
    bi ret;

    // equal signs, use summation
    if ((!negative && !rhs.negative) || (negative && rhs.negative)) {

        ret = sum(*this, rhs);
        ret.negative = negative && rhs.negative;
    }
    else { // different signs, use subtraction

        if (*this > rhs) {
            ret = subtr(*this, rhs);
            ret.negative = negative;
        }
        else if (*this < rhs) {
            ret = subtr(rhs, *this);
            ret.negative = rhs.negative;
        }
    }

    return ret;
}

bi bi::operator-(const bi& rhs) const
{
    bi ret;

    // equal signs, use subtraction
    if ((!negative && !rhs.negative) || (negative && rhs.negative)) {

        if (*this > rhs) {
            ret = subtr(*this, rhs);
            ret.negative = negative;
        }
        else if (*this < rhs) {
            ret = subtr(rhs, *this);
            ret.negative = !negative;
        }
    }
    else { // different signs, use summation

        ret = sum(*this, rhs);
        ret.negative = negative;
    }

    return ret;
}

bi bi::operator-() const
{
    bi ret = *this;
    ret.negative = !negative;
    return ret;
}

bi bi::operator*(const bi& rhs) const
{
    bi ret;

    if (isZero() || rhs.isZero()) {
        return ret;
    }

    for (int i = 0; i < rhs.size(); i++) {

        // Current vector
        bi retCurr;

        // Add leading zeroes
        for (int j = 0; j < i; j++) {
            retCurr.v.push_back(0);
        }

        // Multiplication
        int mm = rhs[i];
        int c = 0;
        for (int ai : v) {

            int res = ai * mm + c;
            int rem = res % 10;
            c = res / 10;
            retCurr.v.push_back(rem);
        }
        if (c > 0) {
            retCurr.v.push_back(c);
        }

        // Adding to the main result
        ret = sum(ret, retCurr);
    }

    ret.negative = negative ^ rhs.negative;
    return ret;
}

pair<bi, bi> bi::operator/(const bi& rhs) const
{
    pair<bi, bi> ret;

    vector<int> v1 = v;
    vector<int> v2 = rhs.v;

    // Zero divident/divider, return a pair {empty, empty}
    if (isZero() || rhs.isZero()) {
        return ret;
    }

    // Divident is lesser than the divider, return {empty, v}
    if (lessthan(v1, v2)) {
        ret.second = v1;
        return ret;
    }

    // The divider is equal to 1, return {v, empty}
    if (v2.size() == 1 && v2[0] == 1) {
        ret.first = v1;
        return ret;
    }

    // Create a subvector
    // "minuend" - "subtrahend"
    auto first = v1.end() - v2.size();
    auto last = v1.end();
    vector<int> minuend = { first, last };
    vector<int> subtrahend(v2);

    // If the subvector is less than the divider, add the next digit
    while (first != v1.begin() && lessthan(minuend, subtrahend)) {
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
    ret.first.v.insert(ret.first.v.begin(), --m);
    minuend = subtr(minuend, subtrahendPrev);
    subtrahend = v2;

    // The following subtractions to the begining of v
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
                ret.first.v.insert(ret.first.v.begin(), 0);
                done = true;
                break;
            }
            else { // move futher otherwise
                minuend.insert(minuend.begin(), *(--first));
                ret.first.v.insert(ret.first.v.begin(), 0);
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
        ret.first.v.insert(ret.first.v.begin(), --m);
        minuend = subtr(minuend, subtrahendPrev);
        subtrahend = v2;
    }

    ret.second = minuend;
    return ret;
}

bool bi::operator==(const bi& rhs) const
{
    if (v.size() != rhs.v.size()) {
        return false;
    }

    for (int i = 0; i < v.size(); i++) {
        if (v[i] != rhs.v[i]) {
            return false;
        }
    }
    return true;
}

bool bi::operator!=(const bi& rhs) const
{
    if (v.size() != rhs.v.size()) {
        return true;
    }

    for (int i = 0; i < v.size(); i++) {
        if (v[i] != rhs.v[i]) {
            return true;
        }
    }
    return false;
}

bool bi::operator<(const bi& rhs) const
{
    if (v.size() < rhs.size()) {
        return true;
    }
    if (v.size() > rhs.size()) {
        return false;
    }
    for (int i = (int)v.size() - 1; i >= 0; i--) {
        if (v[i] < rhs.v[i]) {
            return true;
        }
        else if (v[i] > rhs.v[i]) {
            return false;
        }
    }
    return false;
}

bool bi::operator<=(const bi& rhs) const
{
    return (*this < rhs) || (*this == rhs);
}

bool bi::operator>(const bi& rhs) const
{
    return !(*this < rhs) && !(*this == rhs);
}

bool bi::operator>=(const bi& rhs) const
{
    return !(*this < rhs);
}

bi bi::operator+=(const bi& rhs)
{
    bi ret;
    int la = static_cast<int>(v.size());
    int lb = static_cast<int>(rhs.v.size());
    int lmin = min(la, lb);
    int lmax = max(la, lb);
    int c = 0;
    for (int i = 0; i < lmin; i++) {
        int res = v[i] + rhs.v[i] + c;
        int rem = res % 10;
        c = res / 10;
        ret.v.push_back(rem);
    }

    if (la != lb) {
        bool aig = la >= lb;
        for (int i = lmin; i < lmax; i++) {
            int res = (aig ? v[i] : rhs.v[i]) + c;
            int rem = res % 10;
            c = res / 10;
            ret.v.push_back(rem);
        }
    }
    if (c > 0) {
        ret.v.push_back(c);
    }

    return ret;
}

int bi::operator[](size_t i) const
{
    return v[i];
}

bool bi::isZero() const
{
    return (v.size() == 1 && v[0] == 0) || v.size() == 0;
}

bool bi::isUnity() const
{
    return (v.size() == 1 && v[0] == 1);
}

size_t bi::size() const
{
    return v.size();
}

bi bi::s() const
{
    bi ret;
    for (int i : v) {
        ret = ret + bi(i);
    }
    return ret;
}

bi bi::f() const
{
    bi ret;
    for (int i : v) {
        ret = ret + bi::factorial(i);
    }
    return ret;
}

string bi::tostring() const
{
    string ret;

    if (isZero()) {
        ret.push_back('0');
    }
    else {
        for (int i = 0; i < v.size(); i++) {
            ret.insert(ret.begin(), v[i] + '0');
            if ((i + 1) % 3 == 0 && i != v.size() - 1) {
                ret.insert(ret.begin(), GROUP_SEPARATOR);
            }
        }
        if (negative) {
            ret.insert(ret.begin(), '-');
        }
    }
    return ret;
}

/// <summary>
/// Decomposition of a big integer in a basis.
/// </summary>
/// <param name="ret">Deomposition array (output).</param>
/// <param name="v">The integer to decompose (input).</param>
/// <param name="basis">The basis as an array of vectors (input).</param>
/// <param name="n">Number of basic numbers (input).</param>
/// <returns></returns>
void bi::decomp(bi ret[], const bi basis[], int n) const
{
    // Assume the basis is in descending order: {99, 71, 33, 17...}
    bi rem = *this;
    for (int i = 0; i < n; i++) {
        pair<bi, bi> res = rem / basis[i];
        ret[i] = res.first;
        rem = res.second;
    }
}

bi bi::comp(bi dcp[], int n)
{
    vector<int> ret;
    for (int i = 0; i < n; i++) {
        bi tmp = dcp[i];
        while (!tmp.isZero())
        {
            ret.push_back(n - i);
            tmp = tmp - bi(1);
        }
    }
    return bi(ret);
}

bi bi::factorial(int n)
{
    bi ret = bi::unity();
    if (n == 0 || n == 1) {
        return ret;
    }
    return bi(n) * bi::factorial(n - 1);
}

bi bi::sum(const bi& a, const bi& b)
{
    bi ret;
    int la = static_cast<int>(a.v.size());
    int lb = static_cast<int>(b.v.size());
    int lmin = min(la, lb);
    int lmax = max(la, lb);
    int c = 0;
    for (int i = 0; i < lmin; i++) {
        int res = a.v[i] + b.v[i] + c;
        int rem = res % 10;
        c = res / 10;
        ret.v.push_back(rem);
    }

    if (la != lb) {
        bool aig = la >= lb;
        for (int i = lmin; i < lmax; i++) {
            int res = (aig ? a.v[i] : b.v[i]) + c;
            int rem = res % 10;
            c = res / 10;
            ret.v.push_back(rem);
        }
    }
    if (c > 0) {
        ret.v.push_back(c);
    }

    return ret;
}

bi bi::subtr(const bi& a, const bi& b)
{
    bi ret;
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
        ret.v.push_back(res);
    }

    // Erase the leading zeros
    while (ret.size() > 1 && ret[ret.size() - 1] == 0) {
        ret.v.erase(ret.v.end() - 1);
    }

    return ret;
}

bool bi::lessthan(vector<int> v1, vector<int> v2)
{
    if (v1.size() < v2.size()) {
        return true;
    }
    if (v1.size() > v2.size()) {
        return false;
    }
    for (int i = (int)v1.size() - 1; i >= 0; i--) {
        if (v1[i] < v2[i]) {
            return true;
        }
        else if (v1[i] > v2[i]) {
            return false;
        }
    }
    return false;
}

bool bi::equalto(vector<int> v1, vector<int> v2)
{
    if (v1.size() != v2.size()) {
        return false;
    }
    for (int i = (int)v1.size() - 1; i >= 0; i--) {
        if (v1[i] != v2[i]) {
            return false;
        }
    }
    return true;
}

vector<int> bi::sum(vector<int> a, vector<int> b)
{
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

vector<int> bi::subtr(vector<int> a, vector<int> b)
{
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
    while (ret.size() > 0 && ret[ret.size() - 1] == 0) {
        ret.erase(ret.end() - 1);
    }

    return ret;
}

std::ostream& operator<< (std::ostream& os, const bi& rhs) {

    os << rhs.tostring();

    //if (rhs.isZero()) {
    //    os << 0;
    //}
    //else {
    //    if (rhs.isNegative()) {
    //        os << '-';
    //    }
    //    for (int i = 0; i < rhs.size(); i++) {
    //        os << rhs[rhs.size() - i - 1];
    //    }
    //}

    return os;
}
