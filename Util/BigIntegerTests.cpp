#include "BigInteger.h"
#include "BigIntegerTests.h"

bool biTests()
{

    int imin = -200;
    int imax = 500;
    for (int t = 0; t < 10000; t++)
    {
        int i = rand() % (imax - imin + 1) + imin;
        int j = rand() % (imax - imin + 1) + imin;
        bi a(i);
        bi b(j);
        bi expSumm(i + j);
        bi actSumm = a + b;
        bi expSubtr(i - j);
        bi actSubtr = a - b;
        bi expMult(i * j);
        bi actMult = a * b;
        bi expDiv1;
        bi expDiv2;
        if (j != 0) {
            expDiv1 = bi(i / j);
            expDiv2 = bi(i % j);
        }
        pair<bi, bi> actDiv = a / b;
        if (actSumm != expSumm) {
            cout << a << " + " << b << " = " << actSumm << endl;
            return false;
        }
        else if (actSubtr != expSubtr) {
            cout << a << " - " << b << " = " << actSubtr << endl;
            return false;
        }
        else if (actMult != expMult) {
            cout << a << " * " << b << " = " << actMult << endl;
            return false;
        }
        else if (actDiv.first != expDiv1 || actDiv.second != expDiv2) {
            cout << a << " / " << b << " = " << actDiv.first << " : " << actDiv.second << endl;
            return false;
        }
    }

    bi act = bi::factorial(0);
    bi exp(1);
    if (act != exp) {
        return false;
    }

    act = bi::factorial(1);
    exp = bi(1);
    if (act != exp) {
        return false;
    }

    act = bi::factorial(10);
    exp = bi(3628800);
    if (act != exp) {
        return false;
    }

    act = bi(123456789).s();
    exp = bi(45);
    if (act != exp) {
        return false;
    }

    return true;
}
