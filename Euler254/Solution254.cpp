#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ls;
typedef vector<ls> vl;

// factorial   0 1 2 3 4  5   6   7    8     9
ls facts[] = { 1,1,2,6,24,120,720,5040,40320,362880 };
vl factsv[] = { {1},{1},{2},{6},{24},{120},{720},{5040},{40320},{362880} };

// Pre-calculated g in direct record
// g(i)              1   2   3   4     5     6   7     8     9   10    11    12    13      14      15    16      17      18    19
vl gv[] = { {1},{2},{5},{1,5},{2,5},{3},{1,3},{2,3},{6},{1,6},{2,6},{4,4},{1,4,4},{2,5,6},{3,6},{1,3,6},{2,3,6},{6,7},{1,6,7},
//   20                                                                        30
    {2,6,7},{3,4,9},{1,3,4,9},{2,3,4,9},{4,9},{1,4,9},{2,4,9},{9},{1,9},{2,9},{1,2,9},{2,2,9},{1,2,2,9},{3,9},{1,3,9},{2,3,9},{1,2,3,9},
    //                                     40
        {1,3,3,3,9},{2,3,5,9,9},{4,4,7,9},{1,4,4,7,9},{2,3,5,5,6,7,9},{3,4,4,4,7,9},{1,3,4,4,4,7,9},{2,3,7,8,8,8,9},{1,2,3,7,8,8,8,9},
    //                                                                                               50
        {1,3,3,3,7,8,8,8,9},{2,3,5,6,8,8,8,8,9,9},{1,2,3,5,6,8,8,8,8,9,9},{1,3,3,3,5,6,8,8,8,8,9,9},{1,2,2,4,5,6,7,7,8,8,8,8,9,9},
    //   51                            52                              53                                  54
        {3,4,4,4,6,6,6,6,8,8,8,8,9,9},{1,3,4,4,4,6,6,6,6,8,8,8,8,9,9},{1,2,2,4,5,5,7,8,8,9,9,9,9,9,9,9,9},{1,2,3,3,4,5,5,7,8,8,9,9,9,9,9,9,9,9},
    //   55                                      56
        {1,3,3,3,6,6,6,7,9,9,9,9,9,9,9,9,9,9,9},{1,2,2,4,5,5,5,6,6,6,6,7,9,9,9,9,9,9,9,9,9,9,9} };

/// <summary>
/// Inverses the given vector.
/// </summary>
/// <param name="v">The vector.</param>
/// <returns></returns>
vl inverse(vl v) {
    vl ret(v.size());
    for (ls i = 0; i < (ls)v.size(); i++) {
        ret[i] = v[v.size() - 1 - i];
    }
    return ret;
}

/// <summary>
/// Prints a vector to output console.
/// </summary>
/// <param name="v">The vector.</param>
void out(vl v) {
    for (ls v : v) {
        cout << v;
    }
    // cout << " " << endl;
}

/// <summary>
/// Converts an integer to the vector form with a given base.
/// </summary>
/// <param name="n">The integer.</param>
/// <param name="base">The base.</param>
/// <returns></returns>
vl convertToVector(ls n, ls base) {

    vl ret;
    ls m = n;
    while (m != 0) {

        ls rem = m % base;
        ret.push_back(rem);
        m /= base;
    }

    return ret;
}

/// <summary>
/// Checks if two vectrs are equal.
/// </summary>
/// <param name="v1">The first vector.</param>
/// <param name="v2">The second vector.</param>
/// <returns></returns>
bool equal(vl v1, vl v2) {

    if (v1.size() != v2.size()) {
        return false;
    }

    for (ls i = 0; i < (ls)v1.size(); i++) {
        if (v1[i] != v2[i]) {
            return false;
        }
    }
    return true;
}

/// <summary>
/// Compares two vectors. Returns true if the first is less than the second.
/// </summary>
/// <param name="v1">The first vector.</param>
/// <param name="v2">The second vector.</param>
/// <returns></returns>
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
        ls minuend = i < (ls)a.size() ? a[i] - c : -c;
        ls subtrahend = i < (ls)b.size() ? b[i] : 0;
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
    for (ls i = 0; i < (ls)b.size(); i++) {

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
    } while (lessthan(subtrahend, minuend) || equal(subtrahend, minuend));
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

        if (done) {
            break;
        }

        // Find the next digit
        do {
            m++;
            subtrahendPrev = subtrahend;
            subtrahend = sum(v2, subtrahend);
        } while (lessthan(subtrahend, minuend) || equal(subtrahend, minuend));
        ret.first.insert(ret.first.begin(), --m);
        minuend = subtr(minuend, subtrahendPrev);
        subtrahend = v2;
    }

    ret.second = minuend;
    return ret;
}

vector<vl> comp(ls v, ls nmax) {

    vector<vl> ret;

    if (v == 0) {
        ret.push_back({});
    }
    else if (v == 1) {
        ret.push_back({ 1 });
    }
    else if (v == 2) {
        ret.push_back({ 1,1 });
        ret.push_back({ 2 });
    }
    else {
        ls ie = v < 10 ? v : 9;
        for (ls i = 1; i <= ie; i++) {
            vector<vl> vv = comp(v - i, nmax - 1);
            for (vl c : vv) {
                if ((ls)c.size() < nmax) {
                    vl tmp(c);
                    tmp.emplace(tmp.begin(), i);
                    ret.push_back(tmp);
                }
            }
        }
    }
    return ret;
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
/// Decomposition of integer in factorials of 1-9.
/// </summary>
/// <param name="v">The integer.</param>
/// <returns></returns>
ls decomp(ls v) {

    vl ret;
    ls sum = 0;

    ls vv = v;
    for (ls i = 9; i >= 1; i--) {
        ls res = vv / facts[i];
        if (res > 0)
            ret.push_back(res);
        vv = vv % facts[i];
        sum += res;
    }

    return sum;
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

ls sumOfDigits(vl v) {

    ls s = 0;
    for (ls i : v)
    {
        s += i;
    }
    return s;
}

/// <summary>
/// Sum of factorials of digits of the given number.
/// f(abc) = a!+b!+c!
/// </summary>
/// <param name="v">The number.</param>
/// <returns></returns>
vl f(vl v) {

    vl ret;
    for (ls i : v)
    {
        ret = sum(ret, factorial(i));
    }
    return ret;
}

// Bruteforce
void solveBF(ls n) {

    ls g[500]{};
    ls sfmax = 0;
    ls step = 1;
    for (ls i = 1; i <= 5000000000000000000; i += step) {
        vl nv = convertToVector(i, 10);
        ls f = 0;
        for (ls i : nv) {
            f += facts[i];
        }
        ls sf = sumOfDigits(convertToVector(f, 10));
        if (g[sf] == 0) {
            g[sf] = i;
            if (sf > sfmax) {
                sfmax = sf;
            }
            cout << "n = " << i << " f(n) = " << f << " sf(n) = " << sf << " : g(" << sf << ") = " << i << endl;
            if (sf == 32) {
                step = 10;
            }
            else if (sf == 47) {
                step = 100;
            }
            else if (sf == 53) {
                step = 100000000;
            }
        }
        else {
            // cout << "n = " << n << " f(n) = " << f << " sf(n) = " << sf << " repeat" << endl;
        }
    }
    cout << endl;

    //cout << "g values:" << endl;
    //for (ls i = 0; i <= n; i++) {
    //    cout << i << " " << g[i] << endl;
    //}
    //cout << endl;

    //cout << "sg values:" << endl;
    //ls s = 0;
    //for (ls i = 0; i <= n; i++) {
    //    s += sumOfDigits(convertToVector(g[i], 10));
    //    cout << i << " " << s << endl;
    //}
    //cout << "S(" << n << ") = " << s << endl;
    // cout << "Done. sfmax = " << sfmax << endl;
}

void solve() {

    ls g[1000]{};
    ls sfmax = 0;
    ls ftemp[] = { 1,1,2,6,24,120,720,5040,40320,362880 }; // 0!, 1!,... 9!
    ls iadd = 1;
    for (ls ten = 0; ten <= 100; ten++) {
        for (ls i = 0; i < 10; i++) {

            ls n = i + 10 * ten;
            vl f = convertToVector(ftemp[i], 10);
            ls sf = sumOfDigits(f);
            if (g[sf] == 0) {
                g[sf] = n;
                if (sf > sfmax) {
                    sfmax = sf;
                }
                cout << "n = " << n << " f(n) = " << ftemp[i] << " sf(n) = " << sf << " g(sf) = " << n << endl;
            }
            else {
                // cout << "n = " << n << " f(n) = " << f << " sf(n) = " << sf << " repeat" << endl;
            }
            ftemp[i] = facts[iadd] + facts[i];
        }
        iadd++;
    }

    cout << "Done. sfmax = " << sfmax << endl;
}

int main() {

    // solveBF(50);
    // solve();

    //ls dc = decomp(379999);
    //dc = decomp(488899);

    //vector<vl> ret = comp(20, 3);

    //cout << "Size: " << ret.size() << endl;
    //for (vl v : ret) {
    //    out(v);
    //}

    //int i = 1;
    //ls sg = 0;
    //for (vl g : gv) {
    //    ls sum = sumOfDigits(g);
    //    vl fs = f(g);
    //    sg += sum;
    //    cout << i << " sg = " << sum << " S = " << sg << endl;
    //    i++;
    //}

    vl basis[] = { {0,8,8,2,6,3},{0,2,3,0,4},{0,4,0,5},{0,2,7},{0,2,1},{4,2},{6},{2},{1} };
    ls n = 9;

    vl v{ 3,9,9,9,9,8,9 };
    out(v);
    cout << " : sum of digits = " << sumOfDigits(v) << endl;

    vl* act = decomp(inverse(v), basis, n);

    vl digits;
    for (int i = 0; i < n; i++) {
        out(inverse(act[i]));
        cout << " ";
        digits = sum(digits, act[i]);
    }
    cout << " Number of digits in g: ";
    out(inverse(digits));
    cout << endl;

    return 0;
}
