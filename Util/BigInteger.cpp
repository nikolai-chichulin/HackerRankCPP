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

bi bi::operator+(const bi& rhs)
{
    bi ret;

    // equal signs, use summation
    if ((!negative && !rhs.negative) || (negative && rhs.negative)) {

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

        // negation if needed
        ret.negative = negative && rhs.negative;
    }
    else { // different signs

        if (!negative && rhs.negative) {
            ret = operator-(rhs);
        }
    }

    return ret;
}

bi bi::operator-(const bi& rhs)
{
    bi ret;
    int la = static_cast<int>(v.size());
    int lb = static_cast<int>(rhs.v.size());
    int lmax = max(la, lb);
    int c = 0;
    for (int i = 0; i < lmax; i++) {
        int minuend = i < v.size() ? v[i] - c : -c;
        int subtrahend = i < rhs.v.size() ? rhs.v[i] : 0;
        c = 0;
        if (minuend < subtrahend) {
            minuend += 10;
            c = 1;
        }
        int res = minuend - subtrahend;
        ret.v.push_back(res);
    }

    // Erase the leading zeros
    while (ret.v.size() > 1 && ret.v[ret.v.size() - 1] == 0) {
        ret.v.erase(ret.v.end() - 1);
    }

    return ret;
}

bool bi::operator==(const bi& rhs)
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

bool bi::operator!=(const bi& rhs)
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
    int j = static_cast<int>(v.size()) - static_cast<int>(i) - 1;
    int ret = j >= 0 ? v[j] : v[0];
    return ret;
}

bool bi::isNegative() const
{
    return negative;
}

bool bi::isZero() const
{
    return (v.size() == 1 && v[0] == 0) || v.size() == 0;
}

long long bi::size() const
{
    return static_cast<long long> (v.size());
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
            os << rhs[i];
        }
    }

    return os;
}
