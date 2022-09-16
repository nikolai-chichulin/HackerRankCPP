#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>

#include "BigInteger.h"

using namespace std;

ofstream outf;

bi fib[100000];

int bounds[11] = { 0,1,7,12,17,21,26,31,36,40,45 };

void fibonacciResearch();
bi fibonacci(int n);
bi fibonacciAlt(int n);
double fibonacciAlt2Log(int n);
int solve(int n);

int main() {

    //fibonacciResearch();

    for (int n = 1; n <= 5000; n++) {
        cout << n << " " << solve(n) << endl;
    }
    cout << "Done." << endl;

    return 0;
}

int solve(int n) {

    if (n <= 10) {
        return bounds[n];
    }

    double fi = log10(0.5 * (1 + sqrt(5.)));
    int ret = static_cast<int>((n - 1 + log10(sqrt(5.))) / fi) + 1;
    return ret;
}

void fibonacciResearch() {

    outf.open("Euler25.txt");

    int sz_ = -1;
    int sz = -1;
    for (int n = 1; n <= 2000; n++) {
        bi v = fibonacciAlt(n);
        double vlog = fibonacciAlt2Log(n);
        int ivlog = static_cast<int>(vlog);
        cout << n << endl;

        sz_ = sz;
        sz = v.size();

        if (sz != ivlog + 1) {
            outf << n << " " << sz << " " << vlog << " error!" << endl;
        }
        else {
            if (sz != sz_) {
                outf << n << " " << sz << " " << vlog << endl;
            }
        }

        //outf << v << endl;
    }
    outf.close();
}

/// n > 0
bi fibonacci(int n) {

    if (n == 0) {
        return bi();
    }

    if (n == 1 || n == 2) {
        return bi(1);
    }

    if (fib[n - 1].isZero()) {
        fib[n - 1] = fibonacci(n - 1);
    }
    if (fib[n - 2].isZero()) {
        fib[n - 2] = fibonacci(n - 2);
    }

    return fib[n - 1] + fib[n - 2];
}

/// n > 0
bi fibonacciAlt(int n) {

    fib[0] = bi();
    fib[1] = bi(1);
    fib[2] = bi(1);
    for (int i = 3; i <= n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    return fib[n];
}

double fibonacciAlt2Log(int n) {

    double a = n * log10(0.5 * (1 + sqrt(5.))) - log10(sqrt(5.));
    return a;
}
