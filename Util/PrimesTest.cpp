#include "PrimesTest.h"
#include "Util.h"

bool primetest()
{
    int n = 2;
    if (!isprime(n)) {
        return false;
    }
    n = 3;
    if (!isprime(n)) {
        return false;
    }
    n = 11;
    if (!isprime(n)) {
        return false;
    }
    n = 3701;
    if (!isprime(n)) {
        return false;
    }
    n = 9883;
    if (!isprime(n)) {
        return false;
    }

    return true;
}
