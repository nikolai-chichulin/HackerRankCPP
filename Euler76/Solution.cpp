#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

long long d[1001][1001]{};

long long solve(long long n, long long k) {

    if (n >= 0 && k >= 0 && d[n][k] > 0) return d[n][k];
    if (n < 0) return 0;
    if (n <= 1 || k == 1) return 1;
    d[n][k] = (solve(n, k - 1) + solve(n - k, k)) % static_cast<long long>(7 + 1000000000);
    return d[n][k];
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */

    int t = 100;
    for (int tt = 0; tt <= t; tt++) {
        long long n = 1000;

        // Init the array
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                d[i][j] = -1;
            }
        }
        cout << n << " : " << solve(n, n) - 1 << endl;
    }

    return 0;
}
