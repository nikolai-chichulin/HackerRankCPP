#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <random>

using namespace std;

ofstream outf;

int sumofdiv(int n) {
    int sum = 0;
    for (int i = 1; i < n / 2 + 1; i++) {
        if (n % i == 0) {
            sum += i;
        }
    }
    return sum;
}

bool isabn(int i) {
    return sumofdiv(i) > i;
}

vector<int> abnumbers(int n) {
    vector<int> ret;
    for (int i = 1; i <= n; i++) {
        int sum = sumofdiv(i);
        if (sum > i) {
            ret.push_back(i);
        }
    }
    return ret;
}

bool solve(int n) {

    outf << n << " ";

    if (n < 24) {
        return false;
    }
    if (n > 20161) {
        return true;
    }

    for (int i = 12; i < n / 2 + 1; i++) {
        if (isabn(i) && isabn(n - i)) {
            //cout << n << " = " << i << " + " << n - i << endl;
            return true;
        }
    }
    return false;
}

int main() {

    outf.open("Euler23.txt");

    for (int it = 20000; it <= 22000; it++) {

        int n = it; // rand();
        cout << n << endl;
        bool ret = solve(n);
        outf << (ret ? "YES" : "NO") << endl;
    }

    outf.close();
    return 0;
}
