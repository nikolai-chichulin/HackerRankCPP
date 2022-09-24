#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <set>
#include <chrono>
using namespace std;

typedef long long li;

bool ispandigital(li i, li maxdigit) {

    int d[] = { 0,0,0,0,0,0,0,0,0,0 };
    while (i > 0)
    {
        int rem = i % 10;
        if (rem == 0 || rem > maxdigit || d[rem] == 1) {
            return false;
        }
        d[rem] = 1;
        i /= 10;
    }

    return true;
}

bool ispandigitalmult(li i1, li i2, li i3, li maxdigit) {

    int d[] = { 0,0,0,0,0,0,0,0,0,0 };
    while (i1 > 0)
    {
        int rem = i1 % 10;
        if (rem == 0 || rem > maxdigit || d[rem] == 1) {
            return false;
        }
        d[rem] = 1;
        i1 /= 10;
    }
    while (i2 > 0)
    {
        int rem = i2 % 10;
        if (rem == 0 || rem > maxdigit || d[rem] == 1) {
            return false;
        }
        d[rem] = 1;
        i2 /= 10;
    }
    while (i3 > 0)
    {
        int rem = i3 % 10;
        if (rem == 0 || rem > maxdigit || d[rem] == 1) {
            return false;
        }
        d[rem] = 1;
        i3 /= 10;
    }
    for (int k = 1; k <= maxdigit; k++) {
        if (d[k] == 0) {
            return false;
        }
    }
    return true;
}

void solve(li n, li maxdigit) {

    li k = 0;
    li sum = 0;
    for (li i1 = 1; i1 < n; i1++) {
        if (ispandigital(i1, maxdigit)) {
            for (li i2 = i1 + 1; i2 < n; i2++) {
                if (ispandigital(i2, maxdigit)) {
                    li i3 = i1 * i2;
                    if (ispandigitalmult(i1, i2, i3, maxdigit)) {
                        k++;
                        sum += i3;
                        cout << i1 << " * " << i2 << " = " << i3 << " " << k << endl;
                    }
                }
            }
        }
    }
    cout << "sum = " << sum << endl;
}

int main() {
    solve(20000, 9);
    return 0;
}
