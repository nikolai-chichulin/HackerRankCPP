#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>

#include "BigInteger.h"

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

    for (char c : s) {
        if (c - '0' >= 0 && c - '0' < 10) {
            this->v.insert(v.begin(), c - '0');
        }
    }
}

bi::~bi()
{
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

bool bi::isNegative() const
{
    return negative;
}

bool bi::isZero() const
{
    return (v.size() == 1 && v[0] == 0) || v.size() == 0;
}

size_t bi::size() const
{
    return v.size();
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

std::ostream& operator<< (std::ostream& os, const bi& rhs) {

    if (rhs.isZero()) {
        os << 0;
    }
    else {
        if (rhs.isNegative()) {
            os << '-';
        }
        for (int i = 0; i < rhs.size(); i++) {
            os << rhs[rhs.size() - i - 1];
        }
    }

    return os;
}
