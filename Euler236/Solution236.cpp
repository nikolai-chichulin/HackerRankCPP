#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>

using namespace std;

typedef long long li;

struct Fraction
{
    Fraction(li numerator, li denominator) {
        num = numerator;
        den = denominator;
        numsqrt = -1;
        densqrt = -1;
    }

    Fraction operator+(Fraction other) {

        // n1   n2   n1 c2 + n2 c1
        // -- + -- = -------------
        // d1   d2     lcd c1 c2
        li lcd = Fraction::gcd(den, other.denominator());

        li c1 = den / lcd;
        li c2 = other.denominator() / lcd;

        li n3 = num * c2 + other.numerator() * c1;
        li d3 = lcd * c1 * c2;

        Fraction ret(n3, d3);
        //ret.reduce();
        return ret;
    }

    void reduce() {
        li gcd = Fraction::gcd(num, den);
        num /= gcd;
        den /= gcd;
    }

    bool isinteger() const {
        return num % den == 0;
    }

    bool issquared() {
        numsqrt = sqroot(num);
        densqrt = sqroot(den);
        return numsqrt > -1 && densqrt > -1;
    }

    li numerator() const {
        return num;
    }

    li denominator() const {
        return den;
    }

    li numeratorsqrt() const {
        return numsqrt;
    }

    li denominatorsqrt() const {
        return densqrt;
    }

    static li gcd(li d1, li d2) {

        li a = d1 > d2 ? d1 : d2; // max
        li b = (a == d1) ? d2 : d1; // min
        while (b != 0) {
            li t = b;
            b = a % b;
            a = t;
        }
        return a;
    }

private:

    li num;
    li den;
    li numsqrt;
    li densqrt;

    static li sqroot(li i) {
        if (i < 0) {
            return -1;
        }
        if (i == 0) {
            return 0;
        }
        li s = (li)sqrt((double)i) - 1;
        li e = s + 2;
        for (li cand = s; cand <= e; cand++) {
            if (cand * cand == i) {
                return cand;
            }
        }
        return -1;
    }
};

Fraction solve3(li a[], li b[]) {

    li sa = a[0] + a[1] + a[2];
    li sb = b[0] + b[1] + b[2];
    li sabd = a[0] * a[1] * a[2];

    for (li as1 = 1; as1 < a[0]; as1++) {
        li sabn1 = as1 * b[0] * a[1] * a[2];
        for (li as2 = 1; as2 < a[1]; as2++) {
            li sabn2 = a[0] * as2 * b[1] * a[2];
            for (li as3 = 1; as3 < a[2]; as3++) {
                li sabn3 = a[0] * a[1] * as3 * b[2];

                li sas = as1 + as2 + as3;
                li sabn = sabn1 + sabn2 + sabn3;

                // m^2 = m2n/m2d
                li m2n = sb * sas * sabd;
                li m2d = sa * sabn;

                if (m2n > m2d) {

                    Fraction mf(m2n, m2d);
                    mf.reduce();
                    if (mf.issquared()) {
                        // test if bsi are integers
                        li bs1n = b[0] * mf.numeratorsqrt() * as1;
                        li bs1d = a[0] * mf.denominatorsqrt();
                        Fraction bs1(bs1n, bs1d);
                        if (bs1n % bs1d != 0) {
                            break;
                        }

                        li bs2n = b[1] * mf.numeratorsqrt() * as2;
                        li bs2d = a[1] * mf.denominatorsqrt();
                        if (bs2n % bs2d != 0) {
                            break;
                        }

                        li bs3n = b[2] * mf.numeratorsqrt() * as3;
                        li bs3d = a[2] * mf.denominatorsqrt();
                        if (bs3n % bs3d != 0) {
                            break;
                        }

                        cout << " as: " << as1 << " " << as2 << " " << as3 << endl;
                        cout << m2n << " / " << m2d << " = " << mf.numerator() << " / " << mf.denominator() << endl;
                        return Fraction(mf.numeratorsqrt(), mf.denominatorsqrt());
                    }
                }
            }
        }
    }
    return Fraction(0, 0);
}

Fraction solve4(li a[], li b[]) {

    li sa = a[0] + a[1] + a[2] + a[3];
    li sb = b[0] + b[1] + b[2] + b[3];
    li sabd = a[0] * a[1] * a[2] * a[3];

    for (li as1 = 1; as1 < a[0]; as1++) {
        li sabn1 = as1 * b[0] * a[1] * a[2] * a[3];
        for (li as2 = 1; as2 < a[1]; as2++) {
            li sabn2 = a[0] * as2 * b[1] * a[2] * a[3];
            for (li as3 = 1; as3 < a[2]; as3++) {
                li sabn3 = a[0] * a[1] * as3 * b[2] * a[3];
                for (li as4 = 1; as4 < a[3]; as4++) {
                    li sabn4 = a[0] * a[1] * a[2] * as4 * b[3];

                    li sas = as1 + as2 + as3 + as4;
                    li sabn = sabn1 + sabn2 + sabn3 + sabn4;

                    // m^2 = m2n/m2d
                    li m2n = sb * sas * sabd;
                    li m2d = sa * sabn;

                    if (m2n > m2d) {

                        Fraction mf(m2n, m2d);
                        mf.reduce();
                        if (mf.issquared()) {
                            // test if bsi are integers
                            li bs1n = b[0] * mf.numeratorsqrt() * as1;
                            li bs1d = a[0] * mf.denominatorsqrt();
                            Fraction bs1(bs1n, bs1d);
                            if (bs1n % bs1d != 0) {
                                break;
                            }

                            li bs2n = b[1] * mf.numeratorsqrt() * as2;
                            li bs2d = a[1] * mf.denominatorsqrt();
                            if (bs2n % bs2d != 0) {
                                break;
                            }

                            li bs3n = b[2] * mf.numeratorsqrt() * as3;
                            li bs3d = a[2] * mf.denominatorsqrt();
                            if (bs3n % bs3d != 0) {
                                break;
                            }

                            li bs4n = b[3] * mf.numeratorsqrt() * as4;
                            li bs4d = a[3] * mf.denominatorsqrt();
                            if (bs4n % bs4d != 0) {
                                break;
                            }

                            cout << " as: " << as1 << " " << as2 << " " << as3 << " " << as4 << endl;
                            cout << m2n << " / " << m2d << " = " << mf.numerator() << " / " << mf.denominator() << endl;
                            return Fraction(mf.numeratorsqrt(), mf.denominatorsqrt());
                        }
                    }
                }
            }
        }
    }
    return Fraction(0, 0);
}

Fraction solve5(li a[], li b[]) {

    li sa = a[0] + a[1] + a[2] + a[3] + a[4];
    li sb = b[0] + b[1] + b[2] + b[3] + b[4];
    li sabd = a[0] * a[1] * a[2] * a[3] * a[4];

    for (li as1 = 1; as1 < a[0]; as1++) {
        li sabn1 = as1 * b[0] * a[1] * a[2] * a[3] * a[4];
        for (li as2 = 1; as2 < a[1]; as2++) {
            li sabn2 = a[0] * as2 * b[1] * a[2] * a[3] * a[4];
            for (li as3 = 1; as3 < a[2]; as3++) {
                li sabn3 = a[0] * a[1] * as3 * b[2] * a[3] * a[4];
                for (li as4 = 1; as4 < a[3]; as4++) {
                    li sabn4 = a[0] * a[1] * a[2] * as4 * b[3] * a[4];
                    for (li as5 = 1; as5 < a[4]; as5++) {
                        li sabn5 = a[0] * a[1] * a[2] * a[3] * as5 * b[4];

                        li sas = as1 + as2 + as3 + as4 + as5;
                        li sabn = sabn1 + sabn2 + sabn3 + sabn4 + sabn5;

                        // m^2 = m2n/m2d
                        li m2n = sb * sas * sabd;
                        li m2d = sa * sabn;

                        if (m2n > m2d) {

                            Fraction mf(m2n, m2d);
                            mf.reduce();
                            if (mf.issquared()) {
                                // test if bsi are integers
                                li bs1n = b[0] * mf.numeratorsqrt() * as1;
                                li bs1d = a[0] * mf.denominatorsqrt();
                                Fraction bs1(bs1n, bs1d);
                                if (bs1n % bs1d != 0) {
                                    break;
                                }

                                li bs2n = b[1] * mf.numeratorsqrt() * as2;
                                li bs2d = a[1] * mf.denominatorsqrt();
                                if (bs2n % bs2d != 0) {
                                    break;
                                }

                                li bs3n = b[2] * mf.numeratorsqrt() * as3;
                                li bs3d = a[2] * mf.denominatorsqrt();
                                if (bs3n % bs3d != 0) {
                                    break;
                                }

                                li bs4n = b[3] * mf.numeratorsqrt() * as4;
                                li bs4d = a[3] * mf.denominatorsqrt();
                                if (bs4n % bs4d != 0) {
                                    break;
                                }

                                li bs5n = b[4] * mf.numeratorsqrt() * as5;
                                li bs5d = a[4] * mf.denominatorsqrt();
                                if (bs5n % bs5d != 0) {
                                    break;
                                }

                                cout << " as: " << as1 << " " << as2 << " " << as3 << " " << as4 << " " << as5 << endl;
                                cout << m2n << " / " << m2d << " = " << mf.numerator() << " / " << mf.denominator() << endl;
                                return Fraction(mf.numeratorsqrt(), mf.denominatorsqrt());
                            }
                        }
                    }
                }
            }
        }
    }
    return Fraction(0, 0);
}

void testReduce() {

    li n1 = static_cast<li>(2 * 3 * 7 * 11);
    li d1 = static_cast<li>(2 * 3 * 11 * 13);
    Fraction f(n1, d1);
    f.reduce();
    if (f.numerator() != 7 && f.denominator() != 13) {
        cout << "Failed!" << endl;
    }

    n1 = static_cast<li>(2789 * 2 * 3 * 3 * 7 * 7) * static_cast<li>(11 * 11 * 11 * 13);
    d1 = static_cast<li>(2789 * 2 * 3 * 3 * 7 * 7) * static_cast<li>(11 * 11 * 11 * 17);
    f = Fraction(n1, d1);
    f.reduce();
    if (f.numerator() != 13 && f.denominator() != 17) {
        cout << "Failed!" << endl;
    }

    n1 = static_cast<li>(729587262763827);
    d1 = static_cast<li>(945267351435381);
    f = Fraction(n1, d1);
    f.reduce();
    if (f.numerator() != 729587262763827 / 39 && f.denominator() != 945267351435381 / 39) {
        cout << "Failed!" << endl;
    }
}

void testFractionSum() {

    Fraction a1(11, 100);
    Fraction a2(12, 120);
    Fraction a3 = a1 + a2;
}

void testGCD() {

    li n = static_cast<li>(4723 * 4729 * 3 * 2);
    li d = static_cast<li>(4723 * 4889 * 3 * 2);
    li act = Fraction::gcd(n, d);
    li exp = static_cast<li>(4723 * 3 * 2);
    if (act != exp) {
        cout << "Failed!" << endl;
    }

    n = static_cast<li>(9883 * 4729 * 3 * 2);
    d = static_cast<li>(9883 * 4889 * 3 * 2);
    act = Fraction::gcd(n, d);
    exp = static_cast<li>(9883 * 3 * 2);
    if (act != exp) {
        cout << "Failed!" << endl;
    }

    n = static_cast<li>(729587262763827);
    d = static_cast<li>(945267351435381);
    act = Fraction::gcd(n, d);
    exp = static_cast<li>(39);
    if (act != exp) {
        cout << "Failed!" << endl;
    }
}

int main() {

    //testReduce();
    //testGCD();
    //auto start = std::chrono::high_resolution_clock::now();
    //for (int i = 0; i < 100000; i++) {
    //    testGCD();
    //}
    //cout << "Done" << endl;
    //auto stop = std::chrono::high_resolution_clock::now();
    //auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    //double t = duration.count() / 1E6;
    //cout << " time = " << t << " s" << endl;

    //Fraction f(144 * 2 * 7 * 11, 109 * 2 * 7 * 11);
    //f.reduce();
    //bool squared = f.issquared();

    li a[] = { 10,8,6 };
    li b[] = { 2,9,9 };

    //li a[] = { 30,19,2,27,16 };
    //li b[] = { 29,18,17,26,5 };

    auto start = std::chrono::high_resolution_clock::now();
    Fraction res = solve3(a, b);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << res.numerator() << "/" << res.denominator() << endl;
    cout << " time = " << t << " s" << endl;

    return 0;
}
