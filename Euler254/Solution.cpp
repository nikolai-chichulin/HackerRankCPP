#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int facts[] = { 1,1,2,6,24,120,720,5040,40320,362880 };

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

bool factTest(int a, vector<int> exp) {

    vector<int> act = factorial(a);

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

bool factTests() {

    int a = 0;
    vector<int> exp = { 1 };
    if (!factTest(a, exp)) {
        return false;
    }

    a = 1;
    exp = { 1 };
    if (!factTest(a, exp)) {
        return false;
    }

    a = 2;
    exp = { 2 };
    if (!factTest(a, exp)) {
        return false;
    }

    a = 20;
    exp = { 0,0,0,0,4,6,6,7,1,8,0,0,2,0,9,2,3,4,2 };
    if (!factTest(a, exp)) {
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

    string ns = "873920297998364837";
    //string ns = "345";
    vector<int> n(20);
    int size = (int)ns.size();
    for (int i = 0; i < size; i++) {
        char c = ns[i];
        int ci = c - '0';
        cout << ci << endl;
        n[i] = ci;
    }

    int f = 0;
    for (int i = 0; i < size; i++) {
        f += facts[n[i]];
    }
    cout << f << endl;

    return 0;
}
