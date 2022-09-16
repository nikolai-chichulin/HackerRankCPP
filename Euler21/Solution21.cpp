#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

ofstream outf;

const int amn[] = { 220, 284, 1184, 1210, 2620, 2924, 5020, 5564, 6232, 6368, 10744, 10856, 12285, 14595, 17296, 18416, 63020,
    66928, 66992, 67095, 69615, 71145, 76084, 79750, 87633, 88730 };

int sumofdiv(int n) {
    int sum = 0;
    for (int i = 1; i < n / 2 + 1; i++) {
        if (n % i == 0) {
            sum += i;
        }
    }
    return sum;
}

vector<int> amnumbers(int n) {
    vector<int> ret;
    for (int n = 1; n <= 100000; n++) {
        int sum = sumofdiv(n);
        int sum2 = sumofdiv(sum);
        if (sum2 == n && n != sum) {

            cout << n << " : " << sum << endl;

            bool added1 = false;
            bool added2 = false;
            for (int i = 0; i < ret.size(); i++) {
                if (n == ret[i]) {
                    added1 = true;
                }
                if (sum == ret[i]) {
                    added2 = true;
                }
                if (added1 && added2) {
                    break;
                }
            }
            if (!added1) {
                ret.push_back(n);
            }
            if (!added2) {
                ret.push_back(sum);
            }
        }
    }
    sort(ret.begin(), ret.end());
    return ret;
}

int solve(int n) {

    int ret = 0;
    for (int i = 0; i < 26; i++) {
        if (amn[i] < n) {
            ret += amn[i];
        }
    }
    return ret;
}

int main() {

    //outf.open("Euler21.txt");
    //vector<int> amnRecalculated = amnumbers(100000);
    //for (int i = 0; i < amnRecalculated.size(); i++) {
    //    outf << amnRecalculated[i] << " ";
    //}
    //outf.close();

    int n = 300;
    cout << solve(n) << endl;

    return 0;
}
