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

li pcv3[] = { 153,370,371,407 };
li pcv4[] = { 1634,8208,9474 };
li pcv5[] = { 4150,4151,54748,92727,93084,194979 };
li pcv6[] = { 548834 };

ofstream outf;

li ipow(li b, li exp) {
    li ret = 1;
    for (li i = 0; i < exp; i++) {
        ret *= b;
    }
    return ret;
}

void solve(int n) {

    // 2
    li xmin = 11;
    li xmax = 99;
    for (li x = xmin; x <= xmax; x++) {
        li d2 = x / 10;
        li d1 = (x - d2 * 10);
        li r = ipow(d2, n) + ipow(d1, n);
        if (x == r) {
            cout << x << endl;
        }
    }
    // 3
    xmin = 111;
    xmax = 999;
    for (li x = xmin; x <= xmax; x++) {
        li d3 = x / 100;
        li d2 = (x - d3 * 100) / 10;
        li d1 = (x - d3 * 100 - d2 * 10);
        li r = ipow(d3, n) + ipow(d2, n) + ipow(d1, n);
        if (x == r) {
            cout << x << endl;
        }
    }
    // 4
    xmin = 1111;
    xmax = 9999;
    for (li x = xmin; x <= xmax; x++) {
        li d4 = x / 1000;
        li d3 = (x - d4 * 1000) / 100;
        li d2 = (x - d4 * 1000 - d3 * 100) / 10;
        li d1 = (x - d4 * 1000 - d3 * 100 - d2 * 10);
        li r = ipow(d4, n) + ipow(d3, n) + ipow(d2, n) + ipow(d1, n);
        if (x == r) {
            cout << x << endl;
        }
    }
    // 5
    xmin = 11111;
    xmax = 99999;
    for (li x = xmin; x <= xmax; x++) {
        li d5 = x / 10000;
        li d4 = (x - d5 * 10000) / 1000;
        li d3 = (x - d5 * 10000 - d4 * 1000) / 100;
        li d2 = (x - d5 * 10000 - d4 * 1000 - d3 * 100) / 10;
        li d1 = (x - d5 * 10000 - d4 * 1000 - d3 * 100 - d2 * 10);
        li r = ipow(d5, n) + ipow(d4, n) + ipow(d3, n) + ipow(d2, n) + ipow(d1, n);
        if (x == r) {
            cout << x << endl;
        }
    }
    // 6
    xmin = 111111;
    xmax = 999999;
    for (li x = xmin; x <= xmax; x++) {
        li d6 = x / 100000;
        li d5 = (x - d6 * 100000) / 10000;
        li d4 = (x - d6 * 100000 - d5 * 10000) / 1000;
        li d3 = (x - d6 * 100000 - d5 * 10000 - d4 * 1000) / 100;
        li d2 = (x - d6 * 100000 - d5 * 10000 - d4 * 1000 - d3 * 100) / 10;
        li d1 = (x - d6 * 100000 - d5 * 10000 - d4 * 1000 - d3 * 100 - d2 * 10);
        li r = ipow(d6, n) + ipow(d5, n) + ipow(d4, n) + ipow(d3, n) + ipow(d2, n) + ipow(d1, n);
        if (x == r) {
            cout << x << endl;
        }
    }
    // 7
    xmin = 1111111;
    xmax = 9999999;
    for (li x = xmin; x <= xmax; x++) {
        li d7 = x / 1000000;
        li d6 = (x - d7 * 1000000) / 100000;
        li d5 = (x - d7 * 1000000 - d6 * 100000) / 10000;
        li d4 = (x - d7 * 1000000 - d6 * 100000 - d5 * 10000) / 1000;
        li d3 = (x - d7 * 1000000 - d6 * 100000 - d5 * 10000 - d4 * 1000) / 100;
        li d2 = (x - d7 * 1000000 - d6 * 100000 - d5 * 10000 - d4 * 1000 - d3 * 100) / 10;
        li d1 = (x - d7 * 1000000 - d6 * 100000 - d5 * 10000 - d4 * 1000 - d3 * 100 - d2 * 10);
        li r = ipow(d7, n) + ipow(d6, n) + ipow(d5, n) + ipow(d4, n) + ipow(d3, n) + ipow(d2, n) + ipow(d1, n);
        if (x == r) {
            cout << x << endl;
        }
    }
}

li solvePC(li n) {
    li ret = 0;
    if (n == 3) {
        for (li i : pcv3) {
            ret += i;
        }
    }
    else if (n == 4) {
        for (li i : pcv4) {
            ret += i;
        }
    }
    else if (n == 5) {
        for (li i : pcv5) {
            ret += i;
        }
    }
    else if (n == 6) {
        for (li i : pcv6) {
            ret += i;
        }
    }
    return ret;
}

int main() {
    cout << solvePC(3) << endl;
    return 0;
}
