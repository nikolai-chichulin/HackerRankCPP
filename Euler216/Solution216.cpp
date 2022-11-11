#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <fstream>

using namespace std;

typedef long long li;
typedef size_t sz;

// polynom
const int lim = 60000000; // max possible number of the polynom terms
li polynom[lim]; // polynom values p(n) = an^2 + bn + c
bool possibleprime[lim]; // is term P(n) prime or not, n = [0; lim-1]

li ndiv = 0;

const sz limfact = 20000;
sz factors[limfact]; // prime factors
sz nfact = 0; // number of different prime factors

// primes
const sz limprimes = 2000000; // number of primes below 20 000 000
sz primes[limprimes]; // primes
sz nprimes = 0; // actual number of primes

// Output to a file
li output(int nmax) {
    li ret = 0;
    int i = 0;
    ofstream outf("Euler216.txt");
    for (int n = 0; n < nmax; n++) {
        if (possibleprime[n]) {
            i++;
            outf << i << " P(" << n << ") = " << polynom[n] << endl;
            ret++;
        }
    }
    outf.close();
    return ret;
}

// Constructs the polynom.
void constructpolynom(int a, int b, int c, li nmax) {
    for (int n = 0; n <= nmax; n++) {
        polynom[n] = li(a) * n * n + li(b) * n + c;
    }
}

// Constructs primes up to nmax with Erato sieve.
void constructprimes(sz nmax) {

    // Basics
    bool* ispr = new bool[nmax + 1];
    ispr[0] = false;
    ispr[1] = false;
    for (sz i = 2; i <= nmax; i++) {
        ispr[i] = true;
    }

    // Main loop
    for (sz i = 2; i <= nmax; i++) {
        if (ispr[i]) {
            sz jst = i * i;
            for (sz j = jst; j <= nmax; j += i) {
                ispr[j] = false;
            }
        }
    }

    sz nnonprimes = 0;
    for (sz i = 0; i <= nmax; i++) {
        if (ispr[i]) {
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

    delete[] ispr;
}

// Prime factorizations of the given number.
bool primetest(li p) {

    nfact = 0;
    sz iprime = 0;
    bool ret = false;
    if (p == 2) {
        ret = true;
        factors[nfact++] = 2;
    }
    else if (p == 3) {
        ret = true;
        factors[nfact++] = 3;
    }
    else if (p > 1) {
        li ptmp = p;
        for (iprime = 0; iprime < nprimes; iprime++) { // loop for small primes (<= sqrt(p))
            sz prime = primes[iprime];
            if (prime * prime > p) {
                break;
            }
            while (ptmp % prime == 0)
            {
                ptmp /= prime;
                factors[nfact++] = prime;
            }
        }
        if (nfact == 0) { // if no small primes - this is a prime, add the number itself
            ret = true;
            factors[nfact++] = ptmp;
        }
        else if (ptmp != 1) {
            factors[nfact++] = ptmp;
        }
    }

    if (ret)
    {
        //outf << "P(" << ind << ")=" << p << " - prime; depth - " << iprime << endl;
    }
    else {
        //outf << "P(" << ind << ")=" << p << " - composite; depth - " << iprime << endl;
    }

    return ret;
}

// Returns the second base index if any given the first one.
li getn2(int a, int b, int c, li n1, li divisor) {

    li ret = 0;
    if (b == 0) {
        ret = n1 > divisor ? n1 - divisor : divisor - n1;
    }
    else {

    }
    return ret;
}

// Cross out each polynom term with the given step. 
// Divides each term by the given divisor until the remainer is zero.
void crossout(int a, int b, int c, li n0, li nmax, li divisor) {
    for (li n = n0; n <= nmax; n += divisor) {
        possibleprime[n] = false;
        polynom[n] = polynom[n] == 0 ? (li(a) * n * n + li(b) * n + c) / divisor : polynom[n] / divisor;
        while (polynom[n] % divisor == 0) {
            polynom[n] /= divisor;
            ndiv += 2;
        }
        ndiv += 2;
    }
}

// Cross out each polynom term with the given step. 
// Divides each term by the given divisor only once.
void crossoutsimple(int a, int b, int c, li n0, li nmax, li divisor) {
    for (li n = n0; n <= nmax; n += divisor) {
        possibleprime[n] = false;
        polynom[n] /= divisor;
        while (polynom[n] % divisor == 0) {
            polynom[n] /= divisor;
            ndiv += 2;
        }
        ndiv += 2;
    }
}

// Simple variant for 2n^2 + 1
void mainloopcomplicated(int a, int b, int c, li nmax, bool out) {

    bool isprime0 = primetest(polynom[0]);
    bool isprime1 = primetest(polynom[1]);

    for (int ifact = 0; ifact < nfact; ifact++) {
        if (ifact == 0 || (ifact > 0 && factors[ifact] > factors[ifact - 1])) {
            crossoutsimple(a, b, c, 1, nmax, factors[ifact]);
        }
    }
}

// Simple variant for 2n^2 + 1
void mainloopsimple(int a, int b, int c, li nmax, bool out) {
    for (li n = 0; n <= nmax; n++) {
        if (polynom[n] == 0) { // the term is not yet handled
            polynom[n] = li(a) * n * n + li(b) * n + c;
        }
        // start with the first term > 1
        if (polynom[n] == 1) { // was equal to 1 OR completely reduced to 1
            possibleprime[n] = false;
        }
        else if (polynom[n] > 1) { // not yet handled, let's do it
            // start two cycles with crossing out
            // one starts with n1, the second - with n2,
            // where n1 and n2 - two base indexes for the divisor
            li n1 = n;
            crossout(a, b, c, n1 + polynom[n1], nmax, polynom[n1]);

            // n2 > n1
            li n2 = getn2(a, b, c, n, polynom[n]);
            if (n2 <= nmax) {
                if (polynom[n2] == 0) {
                    polynom[n2] = li(a) * n2 * n2 + li(b) * n2 + c;
                }
                crossout(a, b, c, n2, nmax, polynom[n]);
            }
        }
    }
}

// Brute force variant for R&D
void mainloopBF(int a, int b, int c, int nmax, bool out) {
    ofstream outf;
    if (out)
        outf.open("Euler216-factorization-step2.txt");
    li s = 0;
    for (int n = 0; n <= nmax; n++) {
        //polynom[n] = li(a) * n * n + li(b) * n + c;
        li p = polynom[n];
        if (p == 1) {
            if (out) {
                outf << "P(" << n << ") = " << p << endl;
            }
        }
        else if (primetest(p)) {
            s++;
            if (out) {
                outf << "P(" << n << ") = " << p << " - prime" << endl;
            }
        }
        else {
            if (out) {
                outf << "P(" << n << ") = " << p << " = ";
                for (int i = 0; i < nfact; i++) {
                    outf << factors[i];
                    if (i < nfact - 1) {
                        outf << " * ";
                    }
                }
                outf << endl;
            }
        }
    }
    if (out) {
        outf << "Primes: " << s << endl;
        outf.close();
    }
    cout << "BF done for nmax  = " << nmax << endl;
    cout << "Primes count      = " << s << endl;
}

// More complicated variant for an^2 + bn + c
void runcomplicated(int a, int b, int c, int nmax, bool out)
{
    auto start = std::chrono::high_resolution_clock::now();
    constructprimes(nmax);
    constructpolynom(a, b, c, nmax);
    for (int i = 0; i <= nmax; i++) {
        possibleprime[i] = true;
    }
    mainloopcomplicated(a, b, c, nmax, out);
    mainloopBF(a, b, c, nmax, true);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;

    cout << "Done for nmax   = " << nmax << endl;
    cout << "Primes count    = " << output(nmax) << endl;
    cout << "Divisions count = " << ndiv << endl;
    cout << "Execution time  = " << t << " s" << endl;
}

// Simple variant for 2n^2 + 1
void runsimple(int a, int b, int c, int nmax, bool out)
{
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i <= nmax; i++) {
        possibleprime[i] = true;
    }
    mainloopsimple(a, b, c, nmax, out);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;

    cout << "SV done for nmax = " << nmax << endl;
    cout << "Primes count     = " << output(nmax) << endl;
    cout << "Divisions count  = " << ndiv << endl;
    cout << "Execution time   = " << t << " s" << endl;
}

// Brute force variant for R&D
void runBF(int a, int b, int c, int nmax, bool out) {
    auto start = std::chrono::high_resolution_clock::now();
    constructprimes(nmax);
    mainloopBF(a, b, c, nmax, out);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << "Execution time    = " << t << " s" << endl;
}

int main() {

    int a = 2;
    int b = 0;
    int c = -1;
    int nmax = 50000100;
    bool out = false;

    runsimple(a, b, c, nmax, true);
}
