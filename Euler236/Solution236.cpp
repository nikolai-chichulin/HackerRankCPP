#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <chrono>

using namespace std;

typedef long long li;

ofstream outf;

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

    bool operator==(const Fraction& other) {
        return num == other.num && den == other.den;
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
        cout << "as1 = " << as1 << endl;
        li sabn1 = as1 * b[0] * a[1] * a[2] * a[3] * a[4];
        for (li as2 = 1; as2 < a[1]; as2++) {
            cout << "as2 = " << as2 << endl;
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
                                //return Fraction(mf.numeratorsqrt(), mf.denominatorsqrt());
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

void selection(li a[], li b[]);

int main() {

    outf.open("output.dat");

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

    //li a[] = { 10,8,6 };
    //li b[] = { 2,9,9 };

    //li a[] = { 30,19,2,17 };
    //li b[] = { 29,18,17,26 };

    //li a[] = { 30,19,2,27,16 };
    //li b[] = { 29,18,17,26,5 };

    //li a[] = { 164,41,82,180,123 };
    //li b[] = { 20,59,118,118,177 };

    li a[] = { 5248,1312,2624,5760,3936 };
    li b[] = { 640,1888,3776,3776,5664 };

    auto start = std::chrono::high_resolution_clock::now();
    //Fraction res = solve5(a, b);
    selection(a, b);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    //cout << res.numerator() << "/" << res.denominator() << endl;
    std::cout << " time = " << t << " s" << endl;

    outf.close();
    return 0;
}

// original PE 236 problem has been solved at April 14, 2024
// maximal m = 123/59 = 2.08475
// as = 413,1,1,30,10
// bs = 105,3,3,41,30
// astot = 455
// bstot = 182

void selection(li a[], li b[]) {

    const int n = 5;
    li as[n] = {};
    li bs[n] = {};
    li atot = 0;
    li btot = 0;

    // sums
    for (int i = 0; i < n; i++) {
        atot += a[i];
        btot += b[i];
    }

    std::cout << "atot = " << atot << " btot = " << btot << endl;

    // loop over the possible m for i = 0 as m = (bsi/bi) / (asi/ai) = (bsi*ai)  / (asi*bi)
    li numcomb = 0;
    li numcombtot = a[0] * b[0];
    for (as[0] = 1062; as[0] <= a[0]; as[0]++) {
        li bs_start = as[0] == 1062 ? 360 : b[0];
        for (bs[0] = bs_start; bs[0] > 0; bs[0]--) {
            numcomb++;
            outf << "as[0] = " << as[0] << " bs[0] = " << bs[0] << " combination " << numcomb << " from " << numcombtot << endl;
            // find m, it must be > 1
            Fraction m(a[0] * bs[0], b[0] * as[0]);
            if (m.numerator() <= m.denominator()) {
                outf << "m = " << m.numerator() << " / " << m.denominator() << " <= 1, continue!" << endl;
                continue;
            }
            double mdouble = double(m.numerator()) / double(m.denominator());
            if (mdouble < 2.08475) {
                continue;
            }
            m.reduce();
            bool found = false;
            // the expected value of the astot/bstot ratio: 
            // since m = (astot/atot) / (bstot/btot) => astot/bstot = m*atot/btot
            Fraction ratio_exp(m.numerator() * atot, m.denominator() * btot);
            ratio_exp.reduce();
            // find the base values of as and bs for i=1,2,3,4 as bsi = m_num*bi, asi = n_den*ai
            for (int i = 1; i < n; i++) {
                Fraction tmp(m.numerator() * b[i], m.denominator() * a[i]);
                tmp.reduce();
                as[i] = tmp.denominator();
                bs[i] = tmp.numerator();
            }
            // pick up coefficients for i=1...4
            li imax[n] = {};
            for (int i = 1; i < n; i++) {
                imax[i] = min(btot / bs[i], atot / as[i]);
            }
            int num = 0;
            li astot0 = as[0];
            li bstot0 = bs[0];
            outf << "start i-looping: m = " << m.numerator() << " / " << m.denominator() << " = " << mdouble << endl;
            for (int i1 = 1; i1 < imax[1]; i1++) {
                //std::cout << " i1 = " << i1 << " from " << imax[1] << endl;
                li astot1 = i1 * as[1];
                if ((astot0 + astot1) > atot) {
                    break;
                }
                li bstot1 = i1 * bs[1];
                if ((bstot0 + bstot1) > btot) {
                    break;
                }
                for (int i2 = 1; i2 < imax[2]; i2++) {
                    //std::cout << " i2 = " << i2 << " from " << imax[2] << endl;
                    li astot2 = i2 * as[2];
                    if ((astot0 + astot1 + astot2) > atot) {
                        break;
                    }
                    li bstot2 = i2 * bs[2];
                    if ((bstot0 + bstot1 + bstot2) > btot) {
                        break;
                    }
                    for (int i3 = 1; i3 < imax[3]; i3++) {
                        li astot3 = i3 * as[3];
                        if ((astot0 + astot1 + astot2 + astot3) > atot) {
                            break;
                        }
                        li bstot3 = i3 * bs[3];
                        if ((bstot0 + bstot1 + bstot2 + bstot3) > btot) {
                            break;
                        }
                        for (int i4 = 1; i4 < imax[4]; i4++) {
                            li astot4 = i4 * as[4];
                            li astot = astot0 + astot1 + astot2 + astot3 + astot4;
                            if (astot > atot) {
                                break;
                            }
                            li bstot4 = i4 * bs[4];
                            li bstot = bstot0 + bstot1 + bstot2 + bstot3 + bstot4;
                            if (bstot > btot) {
                                break;
                            }
                            if (bstot > astot) {
                                break;
                            }
                            // compare with the expected value: m = (astot/atot) / (bstot/btot) => astot/bstot = m*atot/btot
                            Fraction ratio = Fraction(astot, bstot);
                            ratio.reduce();
                            //cout << ratio.numerator() << "/" << ratio.denominator() << endl;
                            if (ratio == ratio_exp) {
                                num++;
                                std::cout << "---------- num " << num << endl;
                                std::cout << i1 << " " << i2 << " " << i3 << " " << i4 << endl;
                                std::cout << "as: " << as[0] << " " << i1 * as[1] << " " << i2 * as[2] << " " << i3 * as[3] << " " << i4 * as[4] << endl;
                                std::cout << "bs: " << bs[0] << " " << i1 * bs[1] << " " << i2 * bs[2] << " " << i3 * bs[3] << " " << i4 * bs[4] << endl;
                                std::cout << "astot = " << astot << " bstot = " << bstot << endl;
                                std::cout << "reduced form: " << ratio.numerator() << "/" << ratio.denominator() << endl;
                                outf << "---------- found num " << num << endl;
                                outf << "i1 = " << i1 << " i2 = " << i2 << " i3 = " << i3 << " i4 = " << i4 << endl;
                                outf << "as: " << as[0] << " " << i1 * as[1] << " " << i2 * as[2] << " " << i3 * as[3] << " " << i4 * as[4] << endl;
                                outf << "bs: " << bs[0] << " " << i1 * bs[1] << " " << i2 * bs[2] << " " << i3 * bs[3] << " " << i4 * bs[4] << endl;
                                outf << "astot = " << astot << " bstot = " << bstot << endl;
                                outf << "reduced form: " << ratio.numerator() << "/" << ratio.denominator() << endl;
                                // actual m
                                Fraction aratetot(astot, atot);
                                Fraction bratetot(bstot, btot);
                                Fraction m_act(astot * btot, bstot * atot);
                                m_act.reduce();
                                cout << "m actual = " << m_act.numerator() << "/" << m_act.denominator() << endl;
                                outf << "m actual = " << m_act.numerator() << "/" << m_act.denominator() << endl;
                                outf.flush();
                                found = true;
                            }
                            if (found) {
                                break;
                            }
                        }
                        if (found) {
                            break;
                        }
                    }
                    if (found) {
                        break;
                    }
                }
                if (found) {
                    break;
                }
            }
        }
    }
}
