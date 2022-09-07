#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <chrono>

using namespace std;

vector<int> powers[1300][500];

vector<int> inverse(vector<int> v) {

    vector<int> ret(v.size());
    for (int i = 0; i < v.size(); i++) {
        ret[i] = v[v.size() - 1 - i];
    }
    return ret;
}

void out(vector<int> v) {
    for (int v : v) {
        cout << v << ":";
    }
    cout << " ";
}

/// <summary>
/// Returns sum of two integers represented as vectors.
/// </summary>
/// <param name="a">The first integer as a vector.</param>
/// <param name="b">The second integer as a vector.</param>
/// <param name="base">The base of the numeral system.</param>
/// <returns></returns>
vector<int> sum(vector<int> a, vector<int> b, int base) {

    vector<int> ret;
    int la = static_cast<int>(a.size());
    int lb = static_cast<int>(b.size());
    int lmin = min(la, lb);
    int lmax = max(la, lb);
    int c = 0;
    for (int i = 0; i < lmin; i++) {
        int res = a[i] + b[i] + c;
        int rem = res % base;
        c = res / base;
        ret.push_back(rem);
    }

    if (la != lb) {
        bool aig = la >= lb;
        for (int i = lmin; i < lmax; i++) {
            int res = (aig ? a[i] : b[i]) + c;
            int rem = res % base;
            c = res / base;
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
/// <param name="base">The base of the numeral system.</param>
/// <returns></returns>
vector<int> multiply(vector<int> a, vector<int> b, int base) {

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
            int rem = res % base;
            c = res / base;
            retCurr.push_back(rem);
        }
        if (c > 0) {
            retCurr.push_back(c);
        }

        // Adding to the main result
        ret = sum(ret, retCurr, base);
    }

    return ret;
}

vector<int> power1(vector<int> v, int n, int base) {

    if (n == 0 || n == 1) {
        return v;
    }

    if (n == 2) {
        return multiply(v, v, base);
    }

    int n2 = (int)(log(n) / log(2.));
    int rem = n % ((int)pow(2, n2));

    vector<int> ret = multiply(v, v, base);
    for (int i = 1; i < n2; i++) {
        ret = multiply(ret, ret, base);
    }

    for (int i = 0; i < rem; i++) {
        ret = multiply(ret, v, base);
    }

    return ret;
}

vector<int> power2(vector<int> v, int iv, int n, int base) {

    if (!powers[iv][n].empty()) {
        return powers[iv][n];
    }

    if (n == 0 || n == 1) {
        powers[iv][n] = v;
        return powers[iv][n];
    }

    if (n == 2) {
        powers[iv][n] = multiply(v, v, base);
        return powers[iv][n];
    }

    int n2 = (int)(log(n) / log(2.));
    int rem = n % ((int)pow(2, n2));

    int p = 2; // power
    vector<int> ret = power2(v, iv, p, base);

    for (int i = 1; i < n2; i++) {

        int vl = iv * iv;
        ret = power2(ret, vl, 2, base);
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
        ret = multiply(ret, v, base);
        powers[iv][p] = ret;
    }

    return ret;
}

/// <summary>
/// Recursive version with memorization.
/// It must be guaranteed that iv is equal to v!
/// </summary>
/// <param name="v">The value in vector form.</param>
/// <param name="iv">The value as an integer (must be equal to iv).</param>
/// <param name="n">The power.</param>
/// <param name="base">The base.</param>
/// <returns></returns>
vector<int> power3(vector<int> v, int iv, int n, int base) {

    if (powers[iv][n].empty()) {
        if (n == 0 || n == 1) {
            powers[iv][n] = v;
        }
        else if (n == 2) {
            powers[iv][n] = multiply(v, v, base);
        }
        else {
            powers[iv][n] = multiply(power3(v, iv, n - 1, base), v, base);
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
        s += sumOfDigits(i, 10);
    }
    return s;
}

/// <summary>
/// Variant with numbers.
/// </summary>
/// <param name="base">The base.</param>
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

/// <summary>
/// Variant with numbers as vectors.
/// </summary>
/// <param name="base">The base.</param>
void solveV(int base) {

    vector<vector<int>> v;

    // Max order (100 for base = 10)
    int nmax = static_cast<int>(100. / log10(base));

    // Min and max sum of digits for the order n
    int sMin = 2; // always 1, 100 for base=10, n=2
    int sBase = sumOfDigits(base - 1, 10);
    int sMax = sBase * nmax; // 999 for base=10, n=2

    // Loop over the potential sums of digits
    int ret = 0;
    for (int sExp = sMin; sExp <= sMax; sExp++) {
        vector<int> sExpV = convertToVector(sExp, base);
        int mmax = static_cast<int>(100. / log10(sExp));
        // Loop over the powers
        // cout << "sExp " << sExp << ": ";
        for (int m = 2; m <= mmax; m++) {
            // cout << m << " ";
            vector<int> sExpR = power3(sExpV, sExp, m, base);
            int sAct = sumOfDigits(sExpR);
            if (sAct == sExp) {
                ret++;
                //cout << sp << " ";
                //cout << ret << ": " << sExp << " ^ " << m << " : " << endl;
                //cout << "Base notation:    ";
                //out(inverse(sExpR));
                //cout << endl;
                //vector<int> sExpVDec = convertToVector(sExp, 10);
                //vector<int> sExpRDec = power1(sExpVDec, m, 10);
                //cout << "Decimal notation: ";
                //out(inverse(sExpRDec));
                //cout << endl;
                v.push_back(inverse(power1(convertToVector(sExp, 10), m, 10)));
            }
        }
        // cout << endl;
    }
    cout << endl;

    sort(v.begin(), v.end());
}

int main() {

    auto start = std::chrono::high_resolution_clock::now();

    for (int base = 2; base <= 1000; base++) {

        cout << endl << "---------- Base " << base << " ----------" << endl;

        auto start1 = std::chrono::high_resolution_clock::now();
        solveV(base);
        auto stop1 = std::chrono::high_resolution_clock::now();
        auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(stop1 - start1);

        cout << "Time: " << duration1.count() / 1E6 << " seconds" << endl;

        for (int i = 0; i < 1300; i++)
        {
            for (int j = 0; j < 500; j++)
            {
                powers[i][j].clear();
            }
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    cout << "Total time: " << duration.count() / 1E6 << " seconds" << endl;

    return 0;
}
