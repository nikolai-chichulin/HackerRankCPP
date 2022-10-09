#include "Util.h"

vl inverse(vl v) {

    vl ret(v.size());
    for (ls i = 0; i < v.size(); i++) {
        ret[i] = v[v.size() - 1 - i];
    }
    return ret;
}

bool isprime(int n) {

    if (n == 2 || n == 3)
        return true;

    if (n <= 1 || n % 2 == 0 || n % 3 == 0)
        return false;

    for (int i = 5; i * i <= n; i += 6)
    {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }

    return true;
}
