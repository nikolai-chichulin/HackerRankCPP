#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int facts[] = { 1,1,2,6,24,120,720,5040,40320,362880 };

bool isCurious(int n) {

    if (n < 10) {
        return false;
    }

    int m = n;
    int s = 0;
    while (m != 0) {

        int rem = m % 10;
        s += facts[rem];
        m /= 10;
    }

    return s % n == 0;
}

int solve(int n) {

    int ret = 0;
    for (int i = 10; i < n; i++) {
        if (isCurious(i)) {
            ret += i;
        }
    }

    return ret;
}


int main() {

    int n = 100000;
    cout << solve(n) << endl;

    return 0;
}
