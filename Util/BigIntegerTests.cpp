#include "BigInteger.h"
#include "BigIntegerTests.h"

bool biTests()
{

    int imin = -10000;
    int imax = 10000;
    for (int t = 0; t < 100000; t++)
    {
        int i = rand() % (imax - imin + 1) + imin;
        int j = rand() % (imax - imin + 1) + imin;
        bi a(i);
        bi b(j);
        bi expSubtr(i - j);
        bi actSubtr = a - b;
        bi expSumm(i + j);
        bi actSumm = a + b;
        bi expMult(i * j);
        bi actMult = a * b;
        if (actSubtr != expSubtr) {
            cout << a << " - " << b << " = " << actSubtr << endl;
            return false;
        }
        else if (actSumm != expSumm) {
            cout << a << " + " << b << " = " << actSumm << endl;
            return false;
        }
        else if (actMult != expMult) {
            cout << a << " * " << b << " = " << actMult << endl;
            return false;
        }
    }

    return true;
}
