#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <set>
#include <chrono>
using namespace std;

ofstream outf;

typedef long long li;
typedef vector<int> vi;

vector<int> tovector(li n) {
    vector<int> ret;
    while (n > 0) {
        int rem = n % 10;
        ret.push_back(rem);
        n /= 10;
    }
    return ret;
}

li tonumber(vi v) {
    li ret = 0;
    li tens = 1;
    for (li i : v) {
        ret += tens * i;
        tens *= 10;
    }
    return ret;
}

bool containszeroes(li n) {
    if (n == 0) {
        return true;
    }
    while (n > 0) {
        int rem = n % 10;
        if (rem == 0) {
            return true;
        }
        n /= 10;
    }
    return false;
}

/// <summary>
/// Given two numbers: short and long so that all digits of the short are in the digits of the long one.
/// Checks if the order of the short's digits are the same as in the long.
/// </summary>
/// <param name="shortnumber">the short number as a vector of digits</param>
/// <param name="longnumber">the long number as a vector of digits</param>
/// <returns></returns>
bool isorderconserved(vi shortnumber, vi longnumber) {

    vector<int> tmp; // indexes of short's digits in the long number

    // { 4,5 };
    // { 5,4,2,5,1,7 };

    // Loop over the short number digits
    int ip = 0;
    for (int is = 0; is < shortnumber.size(); is++) {
        // Find the digit in the long number
        for (int il = ip; il < longnumber.size(); il++) {
            if (longnumber[il] == shortnumber[is]) {
                tmp.push_back(il);
                ip = il + 1;
                break;
            }
        }
    }

    // Now make sure tmp is in ascending order. Return false otherwise.
    for (int i = 1; i < tmp.size(); i++) {
        if (tmp[i] <= tmp[i - 1]) {
            return false;
        }
    }

    return tmp.size() == shortnumber.size();
}

vector<vi> permutations(vi v) {
    vector<vi> ret;
    std::sort(v.begin(), v.end());
    do {
        //std::cout << v[0] << " " << v[1] << " " << v[2] << " " << v[3] << '\n';
        ret.push_back(v);
    } while (std::next_permutation(v.begin(), v.end()));
    return ret;
}

// inserts i into v starting with the index start
vector<vi> mixing(int i, vi v, int start) {

    vector<vi> ret;
    for (int j = start; j < v.size() + 1; j++) { // where to insert v2[0]
        vi tmp = v;
        tmp.insert(tmp.begin() + j, i);
        ret.push_back(tmp);
    }
    return ret;
}

// inserts v1 into v2 without any permutations of v1 and v2
vector<vi> mixing(vi v1, vi v2) {

    vector<vi> ret;
    for (int i = 0; i < v1.size(); i++) {
        for (int j = 0; j < v1.size(); j++) {
            //vector<vi> tmp = mixing(v1[i], v2);
        }
    }
    return ret;
}

set<pair<li, li>> passed;
void solve() {

    for (li denb = 11; denb < 99; denb++) { // loop over base denominator (2-digit)
        //cout << "base denominator:" << denb << endl;
        vi denbv = tovector(denb);
        for (li numb = 11; numb < denb; numb++) { // loop over base numerator (2-digit)
            //cout << " base numerator:" << numb << endl;
            vi numbv = tovector(numb);
            for (li remb = 11; remb < 99; remb++) { // loop over the removable part (2-digit)

                // Exclude numbers with zeroes
                if (remb % 10 == 0) {
                    continue;
                }

                //cout << "  removable part:" << remb << endl;
                vi rembv = tovector(remb);

                vi numv(numbv);
                numv.insert(numv.end(), rembv.begin(), rembv.end()); // the full numerator
                vi denv(denbv);
                denv.insert(denv.end(), rembv.begin(), rembv.end()); // the ful denominator

                vector<vi> numperm = permutations(numv); // permutations of the full numerator
                vector<vi> denperm = permutations(denv); // permutations of the full denominator

                // Loop over permutations of the numerator and denominator
                for (vi numtmp : numperm) {
                    for (vi dentmp : denperm) {

                        // 1. Check the main condition: numtmp/dentmp == numbv/denbv
                        //    or: numtmp*denbv = numbv*dentmp
                        // 2. Memorization in the set
                        li numfull = tonumber(numtmp);
                        li denfull = tonumber(dentmp);
                        bool good = denb * numfull == numb * denfull;
                        if (good && passed.find(pair<li, li>(numfull, denfull)) == passed.end()) {

                            // Check if the order of the base part is conserved in the full numerator/denominator
                            bool numordergood = isorderconserved(numbv, numtmp);
                            bool denordergood = isorderconserved(denbv, dentmp);
                            if (numordergood && denordergood) {
                                outf << numfull << "/" << denfull << " = " << numb << "/" << denb << " removed: " << remb << endl;
                                cout << numfull << "/" << denfull << " = " << numb << "/" << denb << " removed: " << remb << endl;
                            }
                            else {
                                cout << numfull << "/" << denfull << " = " << numb << "/" << denb << " removed: " << remb << " - bad order, excluded" << endl;
                            }
                            passed.insert(pair<li, li>(numfull, denfull));
                        }
                    }
                }
            }
        }
    }
}

void testImpl(vi s, vi l, bool exp) {
    if (isorderconserved(s, l) != exp) {
        cout << "Failed" << endl;
    }
    else {
        cout << "Passed" << endl;
    }
}

void test1() {

    vi s = { 4,5 };
    vi l = { 1,2,3,4,5 };
    testImpl(s, l, true);

    s = { 4,5 };
    l = { 1,4,3,2,5 };
    testImpl(s, l, true);

    s = { 4,5 };
    l = { 5,4,2,3,1 };
    testImpl(s, l, false);

    s = { 4,5 };
    l = { 5,4,2,5,1,7 };
    testImpl(s, l, true);

    s = { 4,5 };
    l = { 5,4,2,5,1,4 };
    testImpl(s, l, true);

    s = { 5,1 };
    l = { 5,4,5,1 };
    testImpl(s, l, true);

    s = { 1,1 };
    l = { 0,1,2,1 };
    testImpl(s, l, true);
}

void test2() {

    int n = 52891618;
    if (containszeroes(n)) {
        cout << "Failed" << endl;
    }
    else {
        cout << "Passed" << endl;
    }

    n = 1;
    if (containszeroes(n)) {
        cout << "Failed" << endl;
    }
    else {
        cout << "Passed" << endl;
    }

    n = 0;
    if (!containszeroes(n)) {
        cout << "Failed" << endl;
    }
    else {
        cout << "Passed" << endl;
    }

    n = 10;
    if (!containszeroes(n)) {
        cout << "Failed" << endl;
    }
    else {
        cout << "Passed" << endl;
    }

    n = 290618;
    if (!containszeroes(n)) {
        cout << "Failed" << endl;
    }
    else {
        cout << "Passed" << endl;
    }

    n = 1906180;
    if (!containszeroes(n)) {
        cout << "Failed" << endl;
    }
    else {
        cout << "Passed" << endl;
    }

}

int main() {

    //vi v = { 1,2,3,4 };
    //vector<vi> res = mixing(9, v, 3);

    test1();
    test2();

    //outf.open("euler33.txt");
    //auto start = std::chrono::high_resolution_clock::now();
    //solve();
    //auto stop = std::chrono::high_resolution_clock::now();
    //auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    //double t = duration.count() / 1E6;
    //cout << " time = " << t << " s" << endl;
    //outf.close();
    return 0;
}
