#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <fstream>

using namespace std;

const int lim = 3000000;
int nf[lim]; // number of factors
int inf[lim]; // numbers with the givem number of factors
int res[lim]; // resulting indexes
ofstream outf;

void solve(int n, int k) {

    int nsupermax = 2100000;
    for (int i = 2; i <= nsupermax; i++) {
        if (nf[i] == 0) {
            for (int j = 2 * i; j <= nsupermax; j += i) {
                nf[j]++;
            }
        }
    }

    // separate the numbers with k factors
    int ninf = 0;
    for (int i = 2; i <= nsupermax; i++) {
        if (nf[i] == k) {
            inf[ninf++] = i;
        }
    }

    //outf.open("Euler47.txt");

    int ret = 0;
    if (k == 2) {
        for (int i = 0; i < ninf - 1; i++) {
            if (inf[i] <= n) {
                // pairs
                if (inf[i + 1] == inf[i] + 1) {
                    res[ret++] = inf[i];
                    cout << inf[i] << endl;
                    //outf << inf[i] << endl;
                    //outf << inf[i + 1] << endl;
                    //outf << "-----" << endl;
                }
            }
        }
    }
    else if (k == 3) {
        for (int i = 0; i < ninf - 2; i++) {
            if (inf[i] <= n) {
                // triples
                if (inf[i + 1] == inf[i] + 1
                    && inf[i + 2] == inf[i] + 2) {
                    res[ret++] = inf[i];
                    cout << inf[i] << endl;
                    //outf << inf[i] << endl;
                    //outf << inf[i + 1] << endl;
                    //outf << inf[i + 2] << endl;
                    //outf << "-----" << endl;
                    i += 2;
                }
            }
        }
    }
    else if (k == 4) {
        for (int i = 0; i < ninf - 3; i++) {
            if (inf[i] <= n) {
                // fours
                if (inf[i + 1] == inf[i] + 1
                    && inf[i + 2] == inf[i] + 2
                    && inf[i + 3] == inf[i] + 3) {
                    res[ret++] = inf[i];
                    cout << inf[i] << endl;
                    //outf << inf[i] << endl;
                    //outf << inf[i + 1] << endl;
                    //outf << inf[i + 2] << endl;
                    //outf << inf[i + 3] << endl;
                    //outf << "-----" << endl;
                }
            }
        }
    }

    //outf.close();
}

int main() {

    int n = 20;
    int k = 2;

    auto start = std::chrono::high_resolution_clock::now();
    //
    solve(n, k);
    //
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << "Execution time    = " << t << " s" << endl;

    return 0;
}
