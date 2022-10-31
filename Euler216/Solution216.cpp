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
const int lim = 20000000; // max possible number of the polynom terms
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

/// <summary>
/// Construct primes up to nmax with Erato sieve.
/// </summary>
/// <param name="nmax"></param>
/// <returns></returns>
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

/// <summary>
/// Constructs prime factorizations of the given number.
/// </summary>
/// <param name="p">The number</param>
/// <returns></returns>
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
        for (iprime = 0; iprime < nprimes; iprime++) { // loop for small primes (<= sqrt(p))
            sz prime = primes[iprime];
            if (prime * prime > p) {
                break;
            }
            if (p % prime == 0)
            {
                factors[nfact++] = prime;
            }
        }
        if (nfact == 0) { // if no small primesa - this is a prime, add the number itself
            ret = true;
            factors[nfact++] = p;
        }
        else if (nfact == 1 && factors[nfact - 1] * factors[nfact - 1] != p) {
            factors[nfact++] = p / factors[nfact - 1];
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

li getn2(int a, int b, int c, li n1, li divisor) {

    li ret = 0;
    if (b == 0) {
        ret = n1 > divisor ? n1 - divisor : divisor - n1;
    }
    else {

    }
    return ret;
}

/// <summary>
/// Cross out each polynom term with the given step. 
/// Divides each term by the given divisor until the remainer is zero.
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <param name="c"></param>
/// <param name="n0"></param>
/// <param name="nmax"></param>
/// <param name="divisor"></param>
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

void mainloop(int a, int b, int c, li nmax, bool out) {
    for (li n = 0; n <= nmax; n++) {
        if (polynom[n] == 0) { // the term is not yet handled
            polynom[n] = li(a) * n * n + li(b) * n + c;
        }
        if (polynom[n] == 1) { // completely handled
            possibleprime[n] = false;
        }
        else if (polynom[n] > 1) { // incompletely handled

            // start with the first term > 1

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

void run(int a, int b, int c, int nmax, bool out)
{
    for (int i = 0; i <= nmax; i++) {
        possibleprime[i] = true;
    }

    mainloop(a, b, c, nmax, out);
}

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

int main() {

    int a = 2;
    int b = 0;
    int c = 1;
    int nmax = 10000000;
    bool out = false;

    auto start = std::chrono::high_resolution_clock::now();
    run(a, b, c, nmax, out);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;

    cout << "Done for nmax   = " << nmax << endl;
    cout << "Execution time  = " << t << " s" << endl;
    cout << "Primes count    = " << output(nmax) << endl;
    cout << "Divisions count = " << ndiv << endl;
}
