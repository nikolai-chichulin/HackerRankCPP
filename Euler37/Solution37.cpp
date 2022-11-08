#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <fstream>

using namespace std;

typedef size_t sz;

// primes
const sz limprimes = 1000001; // number of primes below 20 000 000
sz primes[limprimes]; // primes
sz nprimes = 0; // actual number of primes
bool isprime[limprimes];
bool istruncatablelefttoright[limprimes];
bool istruncatablerighttoleft[limprimes];

// Constructs primes up to nmax with Erato sieve.
void constructprimes(sz nmax) {

    // Basics
    isprime[0] = false;
    isprime[1] = false;
    for (sz i = 2; i <= nmax; i++) {
        isprime[i] = true;
    }

    // Main loop
    for (sz i = 2; i <= nmax; i++) {
        if (isprime[i]) {
            sz jst = i * i;
            for (sz j = jst; j <= nmax; j += i) {
                isprime[j] = false;
            }
        }
    }

    sz nnonprimes = 0;
    for (sz i = 0; i <= nmax; i++) {
        if (isprime[i]) {
            primes[nprimes] = i;
            nprimes++;
        }
        else {
            nnonprimes++;
        }
    }
    //cout << "primes     = " << nprimes << endl;
    //cout << "non-primes = " << nnonprimes << endl;
    //cout << "total      = " << nprimes + nnonprimes << endl;
}

int addleft(int n, int digit) {
    int digits = int(log10(double(n))) + 1;
    int tens = int(pow(10, double(digits)));
    int m = n + digit * tens;
    return isprime[m] ? m : -1;
}

int addright(int n, int digit) {
    int m = n * 10 + digit;
    return isprime[m] ? m : -1;
}

/// <summary>
/// Right to left
/// </summary>
/// <param name="baseprime"></param>
void truncatablerighttoleft(int baseprime) {
    if (baseprime >= 100000) {
        //cout << "Stopped at " << baseprime << endl;
        return;
    }
    for (int add = 1; add < 10; add++) {
        int nextprime = addright(baseprime, add);
        if (nextprime > 0) {
            //cout << "Truncatable from right to left: " << nextprime << endl;
            istruncatablerighttoleft[nextprime] = true;
            truncatablerighttoleft(nextprime);
        }
    }
}

/// <summary>
/// Right to left
/// </summary>
/// <param name="baseprime"></param>
void truncatablelefttoright(int baseprime) {
    if (baseprime >= 100000) {
        //cout << "Stopped at " << baseprime << endl;
        return;
    }
    for (int add = 1; add < 10; add++) {
        int nextprime = addleft(baseprime, add);
        if (nextprime > 0) {
            //cout << "Truncatable from left to right: " << nextprime << endl;
            istruncatablelefttoright[nextprime] = true;
            truncatablelefttoright(nextprime);
        }
    }
}

int constructtruncatableprimes(int nmax) {

    int singles[] = { 2,3,5,7 };

    for (int sp : singles) {
        truncatablerighttoleft(sp);
        truncatablelefttoright(sp);
    }

    int ret = 0;
    for (sz prime : primes) {
        if (istruncatablelefttoright[prime] && istruncatablerighttoleft[prime]) {
            if (prime < nmax) {
                ret += prime;
            }
            cout << "Fully truncatable: " << prime << endl;
        }
    }
    return ret;
}

int solve(int nmax) {
    auto start = std::chrono::high_resolution_clock::now();
    constructprimes(nmax);
    int ret = constructtruncatableprimes(nmax);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << "Execution time    = " << t << " s" << endl;
    return ret;
}

int main() {

    int nmax = 1000000;
    int sum = solve(nmax);
    cout << sum << endl;
}
