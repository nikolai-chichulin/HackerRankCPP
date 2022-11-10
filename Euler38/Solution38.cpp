#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <fstream>

using namespace std;

typedef size_t sz;

int good[10000];
int multipliers[10000];
int ngood;
int mult;

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

    bool ret = true;
    sz n = s.size();

    // d - length of the multiplier
    for (sz d = 1; d <= n / 2; d++) {
        ret = true;
        sz pos = 0;
        sz count = d;
        int dbase = -1;
        int dcurr = -1;
        int dnext = -1;
        int m = 1;
        while (pos + count <= s.size())
        {
            string ss = s.substr(pos, count);
            if (ss == "1") { // 1 is a trivial multiplier
                ret = false;
                break;
            }
            dcurr = number(ss);

            if (dbase == -1) { // first substring
                dbase = dcurr;
            }
            else { // next substrings
                if (dcurr % dbase != 0 || dcurr / dbase != m) {
                    ret = false;
                    break;
                }
            }

            // shift the pointer
            pos += count;

            // estimate the next step
            m++;
            dnext = m * dbase;
            count = sz(log10(dnext) + 1);
        }
        if (ret) {
            if (pos == n) {
                multipliers[mult++] = dbase;
                //cout << s << " d = " << d << endl;
                return ret;
            }
            else {
                ret = false;
            }
        }
    }
    return ret;
}

void makenumbers(string s) {
    std::sort(s.begin(), s.end());
    do {
        if (isgood(s)) {
            good[ngood] = number(s);
            ngood++;
        }
    } while (std::next_permutation(s.begin(), s.end()));
}

void solve(string s, int n) {
    auto start = std::chrono::high_resolution_clock::now();
    makenumbers(s);
    std::sort(std::begin(multipliers), std::end(multipliers));
    for (int mlt : multipliers) {
        if (mlt > 0 && mlt < n) {
            cout << mlt << endl;
        }
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << "Execution time    = " << t << " s" << endl;
}

int main() {
    int k = 9;
    int n = 100000;
    string s = (k == 8) ? "12345678" : "123456789";
    solve(s, n);
}
