#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>

typedef long long li;

using namespace std;

const li dv = 1000000007L;

li solve(li n) {

    li s = 0;
    li s1 = 0;
    li s2 = 0;
    if (n < 100000) { // int version
        s = 1 + 4 * n * (n - 1) * (n - 2) / 6 + 5 * (n - 1) * (n + 1) / 2;
    }
    else { // long version
        s1 = 0;

        // Convert S1 from 4 N (N-1) (N-2) / 6 to 4 * N1 * N2 * N3 to be able to use mod correctly
        li n1 = n;
        li n2 = (n - 1) / 2;
        li n3 = n - 2;
        if (n1 % 3 == 0) {
            n1 /= 3;
            n1 = n1 % dv;

            n2 = n2 % dv;
            n3 = n3 % dv;
        }
        else if (n2 % 3 == 0) {
            n2 /= 3;
            n2 = n2 % dv;

            n1 = n1 % dv;
            n3 = n3 % dv;
        }
        else if (n3 % 3 == 0) {
            n3 /= 3;
            n3 = n3 % dv;

            n1 = n1 % dv;
            n2 = n2 % dv;
        }

        s1 = n1 * n2;
        s1 = s1 % dv;
        s1 *= n3;
        s1 = s1 % dv;
        s1 *= 4;
        s1 = s1 % dv;

        // S2 => 5 * N4 * N5
        li n4 = (n - 1) / 2;
        n4 = n4 % dv;
        li n5 = n + 1;
        n5 = n5 % dv;
        s2 = n4 * n5;
        s2 = s2 % dv;
        s2 *= 5;
        s2 = s2 % dv;

        s = 1 + s1 + s2;
    }
    s = s % dv;

    return s;
}

int main() {

    li n = 7777; // 2000000000899999999; //2111199;
    cout << solve(n) << endl;

    return 0;
}
