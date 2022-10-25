#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>

#include "Util.h"
#include "Solution.h"

using namespace std;

typedef long long li;

bool primeP[11000000];
bool chained[11000000];
li dv[11000000]; // least divisors != 1
li pol[11000000];
size_t idivBF = 0;

bool isprime(li n) {

    if (n == 2 || n == 3) {
        return true;
    }

    idivBF++;
    if (n <= 1 || n % 2 == 0 || n % 3 == 0) {
        return false;
    }

    for (li i = 5; i * i <= n; i += 6)
    {
        idivBF++;
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }

    return true;
}

bool isprimen(vector<li> primes, li n) {

    if (n == 0 || n == 1) {
        return false;
    }

    if (n == 2 || n == 3 || n == 5 || n == 7) {
        return true;
    }

    for (size_t i = 0; i < primes.size(); i++) {
        li prime = primes[i];
        if (n % prime == 0) {
            return false;
        }
    }

    return true;
}

/// <summary>
/// Least divisor.
/// </summary>
/// <param name="n"></param>
/// <returns></returns>
li ldiv(li n) {

    if (n == 2 || n == 3) {
        return n;
    }
    else {
        if (n % 2 == 0) {
            return 2;
        }
        if (n % 3 == 0) {
            return 3;
        }

        for (li i = 5; i * i <= n; i += 6)
        {
            if (n % i == 0) {
                return i;
            }
            if (n % (i + 2) == 0) {
                return i + 2;
            }
        }
    }

    return n;
}

/// <summary>
/// Returns a vector of prime factors of n without dubbing.
/// </summary>
/// <param name="n"></param>
/// <returns></returns>
vector<li> ldivv(li n) {

    vector<li> ret;
    if (n == 2 || n == 3) {
        ret.push_back(n);
    }
    else if (n > 1) {
        li m = n;
        if (n % 2 == 0) {
            ret.push_back(2);
            while (m % 2 == 0)
            {
                m /= 2;
            }
        }
        else if (n % 3 == 0) {
            ret.push_back(3);
            while (m % 3 == 0)
            {
                m /= 3;
            }
        }
        for (li i = 5; i * i <= n; i += 6)
        {
            if (n % i == 0) {
                ret.push_back(i);
                while (m % i == 0)
                {
                    m /= i;
                }
            }
            else if (n % (i + 2) == 0) {
                ret.push_back(i + 2);
                while (m % (i + 2) == 0)
                {
                    m /= i + 2;
                }
            }
        }
        if (m > 1)
        {
            ret.push_back(m);
        }
    }
    return ret;
}

li p(li a, li b, li c, li n) {
    return a * n * n + b * n + c;
}

li sieve(li nmax) {

    dv[0] = 1;

    li imax = static_cast<li>(sqrt(nmax));
    for (li i = 2; i <= imax; i++) {
        if (dv[i] == i) {
            li jst = i * i;
            for (li j = jst; j <= nmax; j += i) {
                dv[j] = i; // least divisor
            }
        }
    }

    li s = 0;
    for (li i = 0; i <= nmax; i++) {
        if (dv[i] == i) {
            //cout << p(a, b, c, i) << endl;
            s++;
        }
    }
    return s;
}

/// <summary>
/// Chain to cross out non-primes.
/// </summary>
/// <param name="n">Starting index</param>
/// <param name="k">Step</param>
/// <param name="nmax">Maximal index</param>
/// <param name="prime">A boolean array with prime/non-prime flags</param>
void chain(li n, li k, li nmax, bool prime[]) {

    //cout << "chain " << n << " : " << k << endl;

    // the chain starts with (n+k) term
    for (li i = n + k; i <= nmax; i += k) {
        if (prime[i]) {
            //  cross out i-th term
            prime[i] = false;
        }
    }
}

void prerun(li a, li b, li c, li nmax) {

    bool output = false;
    vector<li> primes = makeprimeswithsieve(2 * nmax);

    li npt = 0;
    for (li iprime = primes.size() - 1; iprime >= primes.size() - 10000; iprime--) {
        li prime = primes[iprime];
        for (li n = 0; n <= nmax; n++) {
            if (primeP[n]) {
                if (pol[n] % prime == 0) {
                    if (output) {
                        cout << "n=" << n << " P(n)=" << pol[n] << " is divisible by " << prime << endl;
                        cout << "mark all i starting with " << n + prime << " with step " << prime << " as non-primes" << endl;
                    }
                    li np = 0;
                    for (li j = n + prime; j <= nmax; j += prime) {
                        if (primeP[j]) {
                            primeP[j] = false;
                            np++;
                        }
                    }
                    npt += np;
                    if (output) {
                        cout << "non-primes marked =       " << np << endl;
                    }
                    //
                    li d2 = pol[n] / prime;
                    if (d2 > 1 && d2 != prime) {
                        if (output) {
                            cout << "n=" << n << " P(n)=" << pol[n] << " is divisible by " << d2 << endl;
                            cout << "mark all i starting with " << n + d2 << " with step " << d2 << " as non-primes" << endl;
                        }
                        np = 0;
                        for (li j = n + d2; j <= nmax; j += d2) {
                            if (primeP[j]) {
                                primeP[j] = false;
                                np++;
                            }
                        }
                        npt += np;
                        if (output) {
                            cout << "non-primes marked =       " << np << endl;
                        }
                    }
                    if (output) {
                        cout << "----------" << endl;
                    }
                }
            }
        }
    }
    if (output) {
        cout << "total non-primes marked = " << npt << endl;
    }

    //
    li nprime = 0;
    li nnprime = 0;
    for (li n = 0; n <= nmax; n++) {
        if (primeP[n]) {
            nprime++;
        }
        else {
            nnprime++;
        }
    }
    cout << nprime << " potential primes" << endl;
    cout << nnprime << " non-primes" << endl;
    cout << nprime + nnprime << " total" << endl;
}

li solve3(li a, li b, li c, li nmax) {

    li s = 0;
    li icalc = 0;
    li pmax = 0;
    li ncalcmax = 0;
    for (li n = 0; n <= nmax; n++) {
        if (primeP[n]) {

            li ldv = ldiv(pol[n]); // least divisor but 1

            // count calculations
            icalc++;
            //cout << "Least divisor calculation for n = " << n << " Pn = " << pol[n] << " i = " << icalc << endl;

            if (pol[n] > pmax) {
                pmax = pol[n];
                ncalcmax = n;
            }

            // 1 is not a prime
            if (ldv == 1) {
                primeP[n] = false;
                continue;
            }
            else if (ldv < pol[n]) {
                primeP[n] = false;
            }
            cout << "pmax  = " << pmax << " n = " << ncalcmax << " ldv = " << ldv << " icalc = " << icalc << endl;

            // run a chain for crossing non-primes out
            chain(n, ldv, nmax, primeP);
        }
        if (primeP[n]) {
            s++;
        }
        //if (n % 10000 == 0) {
        //    cout << n << endl;
        //}
    }
    cout << "icalc = " << icalc << endl;
    return s;
}

li solve2(li a, li b, li c, li nmax) {

    li s = 0;
    li icalc = 0;
    for (li n = 0; n <= nmax; n++) {
        vector<li> dv = ldivv(pol[n]);
        icalc++;
        if (dv.empty()) {
            primeP[n] = false;
            continue;
        }
        //cout << "Least divisors calculation for n = " << n << " Pn = " << pol[n] << " i = " << icalc << endl;
        for (li d : dv) {
            cout << " --->" << n << " " << d << endl;
            if (d < pol[n]) {
                primeP[n] = false;
            }
            for (li j = n + d; j <= nmax; j += d) {
                primeP[j] = false;
            }
        }
        if (primeP[n]) {
            s++;
        }
        if (n % 10000 == 0) {
            cout << n << endl;
        }
    }
    cout << "icalc = " << icalc << endl;
    return s;
}

li solve1(li a, li b, li c, li nmax) {
    li scomp1 = 0;
    li scomp2 = 0;
    li sprime = 0;
    for (li n = 0; n <= nmax; n++) {
        bool maybeprime = true;
        // Loop over primes <= sqrt(n)
        li mmax = static_cast<li>(sqrt(n));
        for (li m = 2; m <= mmax && (dv[m] == m); m++) {
            li r = n % m;
            li rem = pol[r];
            if (rem % m == 0) {
                // P is definitely not a prime
                scomp1++;
                //cout << n << " is compound " << scomp1 << " by " << m << endl;
                maybeprime = false;
                break;
            }
        }
        if (maybeprime) {
            if (isprime(pol[n])) {
                sprime++;
                //cout << n << " is prime " << sprime << endl;
            }
            else {
                scomp2++;
                //cout << n << " is secondary compound " << scomp2 << endl;
            }
        }
    }
    cout << "Compound 1 = " << scomp1 << " Compound 2 = " << scomp2 << " Prime = " << sprime << endl;
    return sprime;
}

li solveBFDivisors(li a, li b, li c, li nmax) {

    //ofstream outf("Euler216-divisorsbut3_11_17_19.txt");
    li ldmax = 0;
    li s = 0;
    for (li n = 0; n <= nmax; n++) {
        if (primeP[n]) {
            li p = pol[n];
            vector<li> ld = ldivv(p);
            if (ld.size() == 0) {}
            else if (ld[0] == p) {
                //outf << "prime     " << n << " " << p << endl;
                s++;
            }
            else {
                //outf << "non-prime " << n << " " << p << " divisors:";
                //for (li dv : ld) {
                //    outf << " " << dv;
                //}
                //outf << endl;
                if (ld[0] > ldmax)
                    ldmax = ld[0];
            }
        }
        if (n % 1000 == 0) {
            cout << "n=" << n << " done" << endl;
        }
    }
    //outf << "Maximal least divisor = " << ldmax << endl;
    //outf.close();
    return s;
}

li solveBF(li a, li b, li c, li nmax) {
    auto start = std::chrono::high_resolution_clock::now();
    cout << "BF solution started" << endl;
    cout << "nmax = " << nmax << endl;
    li nn = 0;
    li np = 0;
    for (li n = 0; n <= nmax; n++) {
        nn++;
        li p = pol[n];
        if (isprime(p)) {
            np++;
        }
        //if (n % 10000 == 0) {
        //    cout << " solveBF: ---> " << n << " " << p << endl;
        //}
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << "BF done. " << endl;
    cout << "n divisions     = " << idivBF << endl;
    cout << "primes found    = " << np << endl;
    cout << "execution time  = " << t << " s" << endl;
    cout << "execution time per division = " << t / np << " s" << endl;
    cout << "--------------------" << endl;
    return np;
}

void test(li nmax) {

    li maybeprime = 0;
    for (li n = 0; n <= nmax; n++) {
        li p = pol[n];
        if (ferma(p)) {
            maybeprime++;
        }
    }
    cout << maybeprime << endl;
}

int main() {

    int a = 2;
    int b = 0;
    int c = 1;
    size_t n = 10000;
    //vector<li> primes = makeprimeswithsieve(2 * n);

    //auto start = std::chrono::high_resolution_clock::now();

    for (li i = 0; i <= n; i++) {
        primeP[i] = true;
        dv[i] = i;
        pol[i] = p(a, b, c, i);
    }
    cout << "Data done for n = " << n << endl;
    cout << "--------------------" << endl;

    //indextest(a, b, c, n);
    //test(n);
    //divisors(pol, n);

    //auto stop = std::chrono::high_resolution_clock::now();
    //auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    //double t = duration.count() / 1E6;
    //cout << " time = " << t << " s" << endl;

    //li res1 = sieve(n);
    //cout << "Sieve done:         " << res1 << endl;
    //auto stop = std::chrono::high_resolution_clock::now();
    //auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    //double t = duration.count() / 1E6;
    //cout << " time = " << t << " s" << endl;

    //start = std::chrono::high_resolution_clock::now();
    //prerun(a, b, c, n);
    //cout << "Prerun done. " << endl;
    //stop = std::chrono::high_resolution_clock::now();
    //duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    //t = duration.count() / 1E6;
    //cout << " time = " << t << " s" << endl;

    //start = std::chrono::high_resolution_clock::now();
    //li res1 = solveBFDivisors(a, b, c, n);
    //cout << "solveBFDivisors done: " << res1 << endl;
    //stop = std::chrono::high_resolution_clock::now();
    //duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    //t = duration.count() / 1E6;
    //cout << " time = " << t << " s" << endl;

    //start = std::chrono::high_resolution_clock::now();
    //li res = solve2(a, b, c, n);
    //cout << "solve 2 done: " << res << endl;
    //stop = std::chrono::high_resolution_clock::now();
    //duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    //t = duration.count() / 1E6;
    //cout << " time = " << t << " s" << endl;

    li res1 = solveBF(a, b, c, n);
    li res2 = run(a, b, c, n, true);

    return 0;
}
