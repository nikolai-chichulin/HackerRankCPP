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

const li n = 8;
li v[n] = { 1,2,5,10,20,50,100,200 }; // set of coins
li d[n][100001];
li dv = 1000000007;

/// <summary>
/// Number of combinations given the sum of coins.
/// Iterative version with memorization.
/// </summary>
/// <param name="s">Sum of all coins.</param>
/// <returns></returns>
li fiter(li s) {

    li ret = 0;
    for (li i = 1; i < n; i++) {
        d[i][0] = 1;
        for (li j = 1; j <= s; j++) {
            d[0][j] = 1;
            d[i][j] = d[i - 1][j];
            if (j >= v[i]) {
                d[i][j] = (d[i][j] + d[i][j - v[i]]) % dv;
            }
        }
    }
    ret = d[n - 1][s];

    return ret;
}

/// <summary>
/// Number of combinations given the highest coin index and the sum of coins.
/// Recursive version.
/// </summary>
/// <param name="i">Index of the highest used coin.</param>
/// <param name="s">Sum of all coins.</param>
/// <returns></returns>
li frec(li i, li s) {

    li ret = 0;
    if (i == 0 || s == 0) {
        ret = 1;
    }
    else if (s < 0) {
        ret = 0;
    }
    else
    {
        li inew = i - 1;
        li jnew = s - v[i];
        ret = frec(inew, s) + frec(i, jnew);
    }

    //cout << "i=" << i << " j=" << s << " ret=" << ret << endl;
    return ret;
}

void test() {

    for (li s = 1; s <= 100; s++) {

        // Recursive
        auto start = std::chrono::high_resolution_clock::now();
        li resRec = frec(n - 1, s);
        auto stop = std::chrono::high_resolution_clock::now();
        auto durationRec = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

        // Iterative
        start = std::chrono::high_resolution_clock::now();
        li resIter = fiter(s);
        stop = std::chrono::high_resolution_clock::now();
        auto durationIter = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

        double timeRec = durationRec.count() / 1E6;
        double timeIter = durationIter.count() / 1E6;

        cout << " s = " << s << endl;
        cout << " Recursive version = " << resRec << " time = " << timeRec << endl;
        cout << " Iterative version = " << resIter << " time = " << timeIter << endl;
        //cout << " Iterative version = " << resIter << endl;
        cout << endl;

        if (resRec != resIter) {
            break;
        }
    }
}

int main() {

    //test();

    auto start = std::chrono::high_resolution_clock::now();
    for (li i = 0; i < 100; i++) {
        li resIter = fiter(100000 - i);
        //if (i % 100 == 0)
        //    cout << " s = " << 100000 - i << " res = " << resIter << endl;
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << " time = " << t << " s" << endl;

    return 0;
}
