#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>

using namespace std;

typedef long long li;

int ispr[10000000];

int power10i(int n) {
    int ret = 1;
    for (int i = 1; i <= n; i++) {
        ret *= 10;
    }
    return ret;
}

int tonumber(vector<int> v) {
    int ret = 0;
    int tens = 1;
    for (int i : v) {
        ret += tens * i;
        tens *= 10;
    }
    return ret;
}

vector<int> tovector(int n) {
    vector<int> ret;
    while (n > 0) {
        int rem = n % 10;
        ret.push_back(rem);
        n /= 10;
    }
    return ret;
}

vector<int> rotations(int n) {

    vector<int> ret;
    vector<int> digits = tovector(n);
    for (int k = 0; k < digits.size() - 1; k++) {

        int first = digits.back();
        digits.pop_back();
        digits.insert(digits.begin(), first);
        ret.push_back(tonumber(digits));
    }
    return ret;
}

bool isprime(int n) {

    if (ispr[n] != 0) {
        return (ispr[n] == 2);
    }

    if (n == 2 || n == 3) {
        ispr[n] = 2;
        return true;
    }

    if (n <= 1 || n % 2 == 0 || n % 3 == 0) {
        ispr[n] = 1;
        return false;
    }

    for (int i = 5; i * i <= n; i += 6)
    {
        if (n % i == 0 || n % (i + 2) == 0) {
            ispr[n] = 1;
            return false;
        }
    }

    ispr[n] = 2;
    return true;
}

void test1() {
    long long s = 0;
    for (int i = 1; i <= 1000000; i++) {
        if (isprime(i)) {
            s += i;
        }
        if (i % 100000 == 0) {
            cout << i << endl;
        }
    }
    cout << s << endl;
}

void test2() {
    vector<int> res = rotations(104080);
}

li solve(int n) {
    li ret = 0;
    li num = 0;
    for (int i = 2; i < n; i++) {
        if (isprime(i)) {
            bool iscircularprime = true;
            vector<int> rotsi = rotations(i);
            for (int roti : rotsi) {
                if (!isprime(roti)) {
                    iscircularprime = false;
                    break;
                }
            }
            if (iscircularprime) {
                ret += i;
                num++;
            }
        }
    }
    return ret;
}

int main() {

    //test2();

    auto start = std::chrono::high_resolution_clock::now();
    long long res = solve(1000000);
    cout << res << endl;
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << " time = " << t << " s" << endl;

    return 0;
}
