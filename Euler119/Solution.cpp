#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

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
        powers[iv][n] = multuply(v, v);
        return powers[iv][n];
    }

    int n2 = (int)(log(n) / log(2.));
    int rem = n % ((int)pow(2, n2));

    int p = 2; // power
    vector<int> ret = power(v, iv, p);

    for (int i = 1; i < n2; i++) {

        int vl = iv * iv;
        ret = power(ret, vl, 2);
        p *= 2;
        powers[iv][p] = ret;

        // fill out the right triangle of the powers
        // decomposition of the power p: 4=2*2, 8=2*4=4*2, 16=2*8=4*4=8*2
        int pl = p / 2;
        while (pl > 1)
        {
            powers[vl][pl] = ret;
            vl *= vl;
            pl /= 2;
        }
    }

    for (int i = 0; i < rem; i++) {
        p += 1;
        ret = multuply(ret, v);
        powers[iv][p] = ret;
    }

    return ret;
}

vector<int> power11(vector<int> v, int iv, int n) {

    if (powers[iv][n].empty()) {
        if (n == 0 || n == 1) {
            powers[iv][n] = v;
        }
        else if (n == 2) {
            powers[iv][n] = multuply(v, v);
        }
        else {
            powers[iv][n] = multuply(power(v, iv, n - 1), v);
        }
    }
    return powers[iv][n];
}

vector<int> convertToVector(int n, int base) {

    vector<int> ret;
    int m = n;
    while (m != 0) {

        int rem = m % base;
        ret.push_back(rem);
        m /= base;
    }

    return ret;
}

int sumOfDigits(int n, int base) {

    if (n < base) {
        return n;
    }

    int m = n;
    int s = 0;
    while (m != 0) {

        int rem = m % base;
        s += rem;
        m /= base;
    }

    return s;
}

int sumOfDigits(vector<int> v) {

    int s = 0;
    for (int i : v)
    {
        s += i;
    }
    return s;
}

/// <summary>
/// Solve the problem for the given order and base.
/// </summary>
/// <param name="n">The order.</param>
/// <param name="base">The base.</param>
void solve(int n, int base) {

    // Min and max numbers for {n, base}
    long long nmin = (int)pow(base, n);
    long long nmax = (int)pow(base, n + 1) - 1;

    // Min and max sum of digits for the order n
    int smin = 2; // always 1, 100 for base=10, n=2
    int smax = (base - 1) * (n + 1); // 999 for base=10, n=2

    // Loop over the potential sums of digits
    cout << n << " : ";
    for (int s = smin; s <= smax; s++) {
        // Loop over the powers
        for (int m = 2; m < 300; m++) {
            int sp = (int)pow(s, m);
            if (sp < nmin) {
                continue;
            }
            if (sp > nmax) {
                break;
            }
            int sact = sumOfDigits(sp, base);
            if (sact == s) {
                cout << sp << " ";
            }
        }
    }
    cout << endl;
}

void solveN(int base) {

    vector<int> v;

    // Max order (100 for base = 10)
    int nmax = static_cast<int>(10. / log10(base));

    // Min and max sum of digits for the order n
    int smin = 2; // always 1, 100 for base=10, n=2
    int smax = (base - 1) * nmax; // 999 for base=10, n=2

    // Loop over the potential sums of digits
    for (int s = smin; s <= smax; s++) {
        // Loop over the powers
        for (int m = 2; m < nmax; m++) {
            int sp = (int)pow(s, m);
            int sact = sumOfDigits(sp, base);
            if (sact == s) {
                cout << sp << " ";
                v.push_back(sp);
            }
        }
    }
    cout << endl;
}

void solveV(int base) {

    //vector<vector<int>> v;

    // Max order (100 for base = 10)
    int nmax = static_cast<int>(100. / log10(base));

    // Min and max sum of digits for the order n
    int sMin = 2; // always 1, 100 for base=10, n=2
    int sMax = (base - 1) * nmax; // 999 for base=10, n=2

    // Loop over the potential sums of digits
    int ret = 0;
    for (int sExp = sMin; sExp <= sMax; sExp++) {
        vector<int> sExpV = convertToVector(sExp, base);
        int mmax = static_cast<int>(100. / log10(sExp));
        // Loop over the powers
        // cout << "sExp " << sExp << ": ";
        for (int m = 2; m <= mmax; m++) {
            // cout << m << " ";
            vector<int> sExpR = power11(sExpV, sExp, m); // power(sExpV, m);
            int sAct = sumOfDigits(sExpR);
            if (sAct == sExp) {
                ret++;
                // cout << sp << " ";
                // v.push_back(sp);
                cout << ret << ": " << sExp << " " << m << endl;
            }
        }
        // cout << endl;
    }
    cout << endl;
}

void solve(int base) {

    for (int n = 1; n < 100; n++) {
        solve(n, base);
    }
}

int main() {

    solveV(10);
    return 0;
}
