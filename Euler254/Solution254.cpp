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

vl multiply(vl a, ls b) {

    vl ret;

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
            vl retCurr;

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

vl inverse(vl v) {
    vl ret(v.size());
    for (int i = 0; i < v.size(); i++) {
        ret[i] = v[v.size() - 1 - i];
    }
    return ret;
}

void out(vl v) {
    for (ls v : v) {
        cout << v;
    }
    cout << " " << endl;
}

bool equal(vl v1, vl v2) {

    if (v1.size() != v2.size()) {
        return false;
    }

    for (int i = 0; i < v1.size(); i++) {
        if (v1[i] != v2[i]) {
            return false;
        }
    }
    return true;
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
                if (c.size() < nmax) {
                    vl tmp(c);
                    tmp.emplace(tmp.begin(), i);
                    ret.push_back(tmp);
                }
            }
        }
    }
    return ret;
}

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

    int i = 1;
    ls sg = 0;
    for (vl g : gv) {
        ls sum = sumOfDigits(g);
        vl fs = f(g);
        sg += sum;
        cout << i << " sg = " << sum << " S = " << sg << endl;
        i++;
    }

    return 0;
}
