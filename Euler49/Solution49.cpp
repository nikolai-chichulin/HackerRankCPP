#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <set>
#include <string>

using namespace std;

typedef long long li;
typedef size_t sz;

const int lim = 10000000;
bool isprime[lim];
int inf[lim]; // numbers with the givem number of factors
int res[lim]; // resulting indexes

string comb[lim];
int ncomb = 0;
int perm[20000][20];

vector<vector<int>> ap;
int pind = 0; // count of the progressions

/// <summary>
/// Finding arithmetic sequence pattern.
/// </summary>
void findaspattern(int maxval, int maxlen, int arr[], int narr) {
    if (narr < 0) {
        return;
    }
    //
    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx - the array
    //  ^      ^         ^
    //  i      j         k
    // 
    // Scan i from 0 to n-3, j - from i+1 to n-2, k - from j+1 to n-1
    // so that the difference between ni and nj is equal to the difference between nj and nk
    //
    for (int i = 0; i < narr; i++) {
        if (arr[i] > maxval) // the first term must be <= maxval
            continue;
        for (int j = i + 1; j < narr; j++) {
            bool found = false;
            int d = arr[j] - arr[i];
            if (d != 0) {
                for (int k = j + 1; k < narr; k++) {
                    if (arr[k] - arr[j] == d) {
                        if (maxlen == 3) {
                            vector<int> tmp = { arr[i], arr[j], arr[k] };
                            ap.push_back(tmp);
                            pind++;
                            found = true;
                        }
                        else {
                            for (int l = k + 1; l < narr; l++) {
                                if (arr[l] - arr[k] == d) {
                                    vector<int> tmp = { arr[i], arr[j], arr[k],arr[l] };
                                    ap.push_back(tmp);
                                    pind++;
                                    found = true;
                                }
                            }
                        }
                    }
                    if (found)
                        break; // if progression found, got to the next j
                }
            }
        }
    }
}

int tonumber(const string& s) {
    int ret = 0;
    int tens = 1;
    for (int i = 0; i < s.size(); i++) {
        ret += tens * (s[s.size() - i - 1] - '0');
        tens *= 10;
    }
    return ret;
}

// Combinations utility
void subcomb(string s1, string s2, int r) {
    if (s1.size() == 0 || s2.size() == 0) {
        return;
    }
    for (sz i = 0; i < s2.size(); i++) {
        string s3(s1);
        s3.append(1, s2[i]);
        if (s3.size() == r) {
            comb[ncomb++] = s3;
        }
        else {
            string s4 = s2.substr(i, s2.size());
            subcomb(s3, s4, r);
        }
    }
}

// Combinations with repetitions
void getcombinations(string s, int r) {
    for (sz i = 0; i < s.size(); i++) {
        string s1(1, s[i]);
        string s2 = s.substr(i, s.size());
        subcomb(s1, s2, r);
    }
}

void getprimepermutations(int maxval, int maxlen) {

    ofstream outf("resfull.dat");
    outf << "Combinations with prime numbers: " << endl;
    for (sz i = 0; i < ncomb; i++) {
        std::sort(comb[i].begin(), comb[i].end());
        outf << "Combination " << i << " = " << comb[i] << endl;
        int nperm = 0;
        int numprev = -1;
        do {
            if (comb[i][0] == '0') {
                continue;
            }
            int num = tonumber(comb[i]);
            if (isprime[num]) { // prime
                perm[i][nperm] = num;
                if (nperm == 0) {
                    outf << num << " ";
                }
                else {
                    outf << num << " (" << num - numprev << ")" << " ";
                }
                numprev = num;
                nperm++;
            }
        } while (std::next_permutation(std::begin(comb[i]), std::end(comb[i])));

        // now we have an array perm[i] of primes created from the i-th combination
        if (nperm > 0) {
            findaspattern(maxval, maxlen, perm[i], nperm);
        }
        outf << "Nperm = " << nperm << endl;
        outf << endl;
    }
    outf.close();
}

void output(int k) {
    ofstream outf("resshort.dat");
    for (int i = 0; i < pind; i++) {
        for (int j = 0; j < k; j++) {
            outf << ap[i][j];
        }
        if (i > 0 && ap[i][0] == ap[i - 1][0]) {
            outf << " double";
        }
        outf << endl;
    }
    outf.close();
}

struct {
    bool operator()(const int* a, const int* b) const {
        bool ret = a[0] == b[0] ? a[1] < b[1] : a[0] < b[0];
        return ret;
    }
} customless;

void solve(int n, int k) {

    // Get primes
    for (sz i = 2; i < lim; i++) {
        isprime[i] = true;
    }
    for (sz i = 2; i < lim; i++) {
        if (isprime[i]) {
            sz jst = i * i;
            for (sz j = jst; j < lim; j += i) {
                isprime[j] = false;
            }
        }
    }

    // Get all needed partial permutations
    std::string digits = "0123456789";
    getcombinations(digits, 4); // 1000-9999
    getcombinations(digits, 5); // 10000-99999
    getcombinations(digits, 6); // 100000-999999
    cout << "N combinations = " << ncomb << endl;
    getprimepermutations(n, k);
    std::sort(ap.begin(), ap.end());
    output(k);
}

void test(int n, int k) {
    int arr[] = { 100,150,175,200,225,250,275,300,325,350,375,400,425,450,475,500 };
    //int arr[] = { 100,100,100,106,116,126,136 };
    //int arr[] = { 1237, 1327, 1723, 2137, 2371, 2713, 2731, 3217, 3271, 7213, 7321 };
    findaspattern(n, k, arr, 16);
    for (int i = 0; i < pind; i++) {
        for (int j = 0; j < k; j++) {
            cout << ap[i][j];
        }
        cout << endl;
    }
}

int main() {

    int n = 578000;
    int k = 3;

    auto start = std::chrono::high_resolution_clock::now();
    //
    //test(1000, 3);
    solve(n, k);
    //
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << "Execution time    = " << t << " s" << endl;

    return 0;
}
