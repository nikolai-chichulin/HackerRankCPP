#include "IntegerAsVectors.h"
#include "SumTests.h"
#include "SubtrTests.h"
#include "MultTests.h"
#include "PowerTests.h"
#include "DivTests.h"
#include "CompDecompTests.h"
#include "BigIntegerTests.h"
#include "PrimesTest.h"

#include "BigInteger.h"

using namespace std;

ofstream outf;

void commontests() {

    cout << "Multiplication with integer: " << (multTestsI() ? "passed" : "failed") << endl;
    cout << "Multiplication with vector:  " << (multTestsV() ? "passed" : "failed") << endl;
    cout << "Summation:                   " << (sumTests() ? "passed" : "failed") << endl;
    cout << "Raising to a power:          " << (powerTests() ? "passed" : "failed") << endl;
    cout << "Raising to a power integer:  " << (powerTestsI() ? "passed" : "failed") << endl;
    cout << "Subtration:                  " << (subtrTests() ? "passed" : "failed") << endl;
    cout << "Division:                    " << (divTests() ? "passed" : "failed") << endl;
    cout << "Compose:                     " << (compTests() ? "passed" : "failed") << endl;
    cout << "Decompose:                   " << (decompTests() ? "passed" : "failed") << endl;
    cout << "Big Integers:                " << (biTests() ? "passed" : "failed") << endl;
}

void euler245() {

    const bi basis[] = { bi(362880),bi(40320),bi(5040),bi(720),bi(120),bi(24),bi(6),bi(2),bi(1) };
    bi dcp[9];

    const bi ssgnPC[] = { bi(1),  bi(3),  bi(8),  bi(14),  bi(21),  bi(24),  bi(28),  bi(33),  bi(39),  bi(46),  bi(54),  bi(62),  bi(71),
        bi(84),  bi(93),  bi(103),  bi(114),  bi(127),  bi(141),  bi(156),  bi(172),  bi(189),  bi(207),  bi(220),  bi(234),  bi(249),
        bi(258),  bi(268),  bi(279),  bi(291),  bi(304),  bi(318),  bi(330),  bi(343),  bi(357),  bi(372),  bi(391),  bi(419),  bi(443),
        bi(468),  bi(505),  bi(536),  bi(568),  bi(613),  bi(659),  bi(709),  bi(775),  bi(842),  bi(913),  bi(997),  bi(1086),  bi(1176),
        bi(1290),  bi(1408),  bi(1542),  bi(1696),  bi(1854),  bi(2053),  bi(2324),  bi(2570),  bi(2817),  bi(3175),  bi(3496),  bi(4041),
        bi(4884),  bi(5936),  bi(7275),  bi(8849),  bi(10695),  bi(12730) };

    bi ssgn = ssgnPC[61];
    for (long long n = 63; n <= 500; n++) {

        long long n9 = n / 9L;
        int n9f = n % 9L;
        int ndig = n9f > 0 ? n9 + 1 : n9;
        vector<int> v(ndig);
        for (int i = 0; i < n9; i++) {
            v[i] = 9;
        }
        if (n9f > 0) {
            v[n9] = n9f;
        }

        bi fgn(v);
        outf << "n = " << n << ": ";
        //outf << "fgn: " << fgn << endl;
        fgn.decomp(dcp, basis, 9);
        //outf << "decomp 6: ";
        //outf << dcp[0] << " | ";
        //for (int i = 0; i < 9; i++) {
        //    outf << 9 - i << ":" << dcp[i] << " ";
        //}
        //outf << endl;
        //bi gn = bi::comp(dcp, 9);
        //outf << "gn: " << gn << endl;
        bi sgn;
        for (int i = 0; i < 9; i++) {
            sgn = sgn + bi(9 - i) * dcp[i];
        }
        ssgn = ssgn + sgn;
        //outf << "sgn = " << sgn << endl;
        outf << sgn << " | " << ssgn << endl;
        //outf << endl;

        if (n % 100 == 0) {
            cout << n << endl;
        }
    }

}

int main() {

    if (!primetest()) {
        cout << "Failed." << endl;
    }
    else {
        cout << "Passed." << endl;
    }

    //commontests();

    //outf.open("output.txt");
    //euler245();
    //cout << "Done." << endl;

    //bi i1 = bi(1000);
    //bi i2 = bi(20);
    //pair<bi, bi>res = i1 / i2;

    //bi i3 = i1.f();
    //cout << i1 << endl;
    //cout << i2 << endl;
    //cout << i3 << endl;

    //cout << i1 << " / " << i2 << " = " << res.first << " : " << res.second << endl;
    //cout << i1 << " + " << i2 << " = " << i1 + i2 << endl;
    //cout << i1 << " - " << i2 << " = " << i1 - i2 << endl;
    //cout << i2 << " + " << i1 << " = " << i2 + i1 << endl;
    //cout << i2 << " - " << i1 << " = " << i2 - i1 << endl;

    //outf.close();

    return 0;
}
