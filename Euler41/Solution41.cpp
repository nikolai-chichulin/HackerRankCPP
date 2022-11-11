#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <fstream>

using namespace std;

int good[10000];
int ngood;

int number(string s) {
    int ret = 0;
    int tens = 1;
    for (int i = 0; i < s.size(); i++) {
        ret += tens * int((s[s.size() - i - 1] - '0'));
        tens *= 10;
    }
    return ret;
}

bool isgood(string s) {

    int n = number(s);

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

int subloop(string s) {
    //cout << "----------" << endl;
    //std::cout << " String:       " << s << endl;
    std::sort(s.begin(), s.end());
    int ind = 0;
    do {
        if (isgood(s)) {
            good[ngood] = number(s);
            //std::cout << good[ngood] << " - prime " << endl;
            ngood++;
            ind++;
        }
    } while (std::next_permutation(s.begin(), s.end()));
    //std::cout << " Primes:       " << ind << endl;
    //std::cout << " Total primes: " << ngood << endl;
    //cout << "----------" << endl;
    return ind;
}

int mainloop(int nmax) {
    string s = "1";
    int ind = subloop(s);
    s = "12";
    ind += subloop(s);
    s = "123";
    ind += subloop(s);
    s = "1234";
    ind += subloop(s);
    s = "12345";
    ind += subloop(s);
    s = "123456";
    ind += subloop(s);
    s = "1234567";
    ind += subloop(s);
    s = "12345678";
    ind += subloop(s);
    s = "123456789";
    ind += subloop(s);

    int ret = -1;
    for (int i = 0; i < ngood; i++) {
        if (good[i] <= nmax && good[i] > ret) {
            ret = good[i];
        }
    }

    return ret;
}

int solve(int nmax) {
    auto start = std::chrono::high_resolution_clock::now();
    int ret = mainloop(nmax);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    //cout << "Execution time    = " << t << " s" << endl;
    return ret;
}

int main() {
    int nmax = 100000000;
    int res = solve(nmax);
    cout << res << endl;
}
