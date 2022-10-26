#include "Solution.h"

// polynom
const sz lim = 20000000; // max possible number of the polynom terms
li polynom[lim]; // polynom values p(n) = an^2 + bn + c
bool possibleprime[lim]; // is term P(n) prime or not, n = [0; lim-1]

// primes
const sz limprimes = 2000000; // number of primes below 20 000 000
sz primes[limprimes]; // primes
sz nprimes = 0; // actual number of primes
bool primedisabled[limprimes]; // flags to enable/disable the primes
sz primecount[limprimes];
sz idiv[limprimes]; // number of divisions by primes
sz idivtot = 0;
sz primetests = 0;
sz positivept = 0;
sz negativept = 0;

const sz limfact = 20000;
sz factors[limfact]; // prime factors
sz nfact = 0; // number of different prime factors
sz firstactiveprime = 0;

ofstream outf;
bool output;

/// <summary>
/// Construct the polynom to nmax inclusive.
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <param name="c"></param>
/// <param name="nmax"></param>
void constructpolynom(int a, int b, int c, sz nmax) {
    for (sz n = 0; n <= nmax; n++) {
        polynom[n] = a * n * n + b * n + c;
    }
}

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
/// Initialization of the input data.
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <param name="c"></param>
/// <param name="nmax"></param>
void init1(int a, int b, int c, sz nmax) {

    // construct the polynom
    constructpolynom(a, b, c, nmax);

    // construct primes
    constructprimes(sz(1.5 * sqrt(polynom[nmax])));

    for (sz i = 0; i <= nmax; i++) {
        possibleprime[i] = true;
    }
}

/// <summary>
/// Factorization. Makes all prime factors of p, including p itself if it is a prime.
/// </summary>
/// <param name="p">The polynom</param>
/// <param name="ind">Index of the polynom p</param>
/// <returns></returns>
bool primetest(li p, sz ind) {

    primetests++;
    nfact = 0;
    sz iprime = 0;
    bool ret = false;
    if (p == 2) {
        ret = true;
        factors[nfact++] = 2;
        primecount[0]++;
    }
    else if (p == 3) {
        ret = true;
        factors[nfact++] = 3;
        primecount[1]++;
    }
    else if (p > 1) {
        for (iprime = 0; iprime < nprimes; iprime++) { // loop for small primes (<= sqrt(p))
            if (primedisabled[iprime]) { // test only active primes
                continue;
            }
            sz prime = primes[iprime];
            if (prime * prime > p) {
                break;
            }
            idiv[iprime]++;
            if (p % prime == 0)
            {
                factors[nfact++] = prime;
                primecount[iprime]++;
                if (primecount[iprime] == 2) { // disable prime if it's encountered twice
                    primedisabled[iprime] = true;
                }
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
        positivept++;
        //outf << "P(" << ind << ")=" << p << " - prime; depth - " << iprime << endl;
    }
    else {
        negativept++;
        //outf << "P(" << ind << ")=" << p << " - composite; depth - " << iprime << endl;
    }

    return ret;
}

/// <summary>
/// Crosses out all prime starting with s with the given step.
/// </summary>
/// <param name="s"></param>
/// <param name="nmax"></param>
/// <param name="step"></param>
void crossout(sz s, sz nmax, li step) {
    if (output)
        outf << "  * cross out starting with " << s << " with step=" << step << endl;
    for (sz ind = s; ind <= nmax; ind += step) {
        possibleprime[ind] = false;
    }
}

/// <summary>
/// The main loop. The simple version.
/// </summary>
/// <param name="nmax"></param>
void mainloop1(sz nmax) {

    if (output)
        outf = ofstream("Euler216-part1.txt");

    // for each prime "Pr" it makes sense to do trial division only in the range of indexes [0; Pr-1]
    // after this range, all division results are repeatable with step Pr so that we can cross out
    // the composite numbers with the step Pr. 
    // After that, if we have crossed "distant" non-primes,
    // for each ind we need test only primes in the range [ind; sqrt(P(n))]

    // P(0) = c
    // P(1) = a+b+c

    li pmax = polynom[nmax];
    // loop over the polynom terms
    for (sz ind = 0; ind <= nmax; ind++) {
        if (possibleprime[ind]) {
            if (polynom[ind] == 1) {
                possibleprime[ind] = false;
            }
            else {
                bool thisisaprime = primetest(polynom[ind], ind);
                if (output)
                    outf << "Testing P(" << ind << ")=" << polynom[ind] << " " << thisisaprime << endl;
                for (sz ifact = 0; ifact < nfact; ifact++) {
                    if (output)
                        outf << " * factor " << ifact + 1 << " = " << factors[ifact] << endl;
                    sz indst = thisisaprime ? ind + factors[ifact] : ind;
                    crossout(indst, nmax, factors[ifact]);
                }
            }
        }
    }
    if (output)
        outf.close();
}

/// <summary>
/// This is slightly upgraded BF version. It works with 1.5 s / n = 100 000 performance.
/// Base BF version takes 4 s / 100 000.
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <param name="c"></param>
/// <param name="nmax"></param>
/// <param name="out"></param>
/// <returns></returns>
ul run1(int a, int b, int c, sz nmax, bool out) {
    auto start = std::chrono::high_resolution_clock::now();
    cout << "New solution started" << endl;
    cout << "nmax = " << nmax << endl;

    output = out;

    // init data
    init1(a, b, c, nmax);

    // the main loop
    mainloop1(nmax);

    ul ret = 0;
    for (sz i = 0; i <= nmax; i++) {
        if (possibleprime[i]) {
            ret++;
        }
    }

    if (output)
        outf = ofstream("Euler216-part2.txt");
    sz idivtot = 0;
    sz divmax = 0;
    sz ind = 0;
    for (sz i = 0; i < nprimes; i++) {
        idivtot += idiv[i];
        if (i > divmax) {
            divmax = i;
        }
        if (idiv[i] > 0) {
            ind++;
            if (output)
                outf << ind << " : " << primes[i] << " : " << idiv[i] << " : " << idivtot << endl;
        }
    }
    if (output)
        outf << idivtot << endl;
    if (output)
        outf.close();

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << "New solution done. " << endl;
    cout << "n prime tests   = " << primetests << endl;
    cout << "n divisions     = " << idivtot << endl;
    cout << "primes found    = " << ret << endl;
    cout << "execution time  = " << t << " s" << endl;
    cout << "execution time per division = " << t / ret << " s" << endl;
    cout << "--------------------" << endl;

    return ret;
}

void constructcycle(sz a, sz b, sz c, sz i, sz p, sz factor, sz nmax) {

    p = p / factor;
    idivtot++;
    sz a2 = 2 * a;
    sz b2 = b - a * factor;
    for (sz j = i + factor; j <= nmax; j += factor) {
        p += a2 * j + b2;
        polynom[j] = p;
        possibleprime[j] = false;
        constructcycle(a, b, c, j, p * factor, p, nmax);
    }
}

void mainloop2(sz a, sz b, sz c, sz nmax) {

    for (sz i = 0; i <= nmax; i++) {
        if (possibleprime[i]) { // test only possible primes
            li p = a * i * i + b * i + c;
            if (p == 1) {
                possibleprime[i] = false;
                continue;
            }
            polynom[i] = p;
            if (!primetest(p, i)) { // composite numbers
                possibleprime[i] = false;
                constructcycle(a, b, c, i, p, p, nmax);
            }
            for (sz ifact = 0; ifact < nfact; ifact++) {
                sz factor = factors[ifact];
                constructcycle(a, b, c, i, p, factor, nmax);
            }
        }
    }
}

ul run2(int a, int b, int c, sz nmax, bool out) {
    auto start = std::chrono::high_resolution_clock::now();
    cout << "New solution started" << endl;
    cout << "nmax = " << nmax << endl;

    output = out;

    // construct primes
    constructprimes(50 + sz(sqrt(a * nmax * nmax + b * nmax + c)));

    for (sz i = 0; i <= nmax; i++) {
        possibleprime[i] = true;
    }

    // the main loop
    //outf = ofstream("Euler216-primetest.txt");
    mainloop2(a, b, c, nmax);
    //outf.close();

    ul ret = 0;
    for (sz i = 0; i <= nmax; i++) {
        if (possibleprime[i]) {
            ret++;
        }
    }

    if (output)
        outf = ofstream("Euler216-part2.txt");
    sz divmax = 0;
    sz ind = 0;
    for (sz i = 0; i < nprimes; i++) {
        idivtot += idiv[i];
        if (i > divmax) {
            divmax = i;
        }
        if (idiv[i] > 0) {
            ind++;
            if (output)
                outf << ind << " : " << primes[i] << " : " << idiv[i] << " : " << idivtot << endl;
        }
    }
    if (output)
        outf << idivtot << endl;
    if (output)
        outf.close();

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << "New solution done. " << endl;
    cout << "n prime tests   = " << primetests << endl;
    cout << "positive tests  = " << positivept << endl;
    cout << "negative tests  = " << negativept << endl;
    cout << "n divisions     = " << idivtot << endl;
    cout << "primes found    = " << ret << endl;
    cout << "execution time  = " << t << " s" << endl;
    cout << "execution time per division = " << t / ret << " s" << endl;
    cout << "--------------------" << endl;

    return ret;
}
