#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <set>
#include <chrono>
using namespace std;

ofstream outf1;
ofstream outf2;

typedef long long li;
typedef vector<int> vi;

vector<int> tovector(li n, li l) {
    vector<int> ret;
    while (n > 0) {
        int rem = n % 10;
        ret.push_back(rem);
        n /= 10;
    }
    while ((li)ret.size() < l) {
        ret.push_back(0);
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

void solve(li n, li k) {

    set<pair<li, li>> passed;

    li denbmax = 9;
    if (n - k == 2) {
        denbmax = 99;
    }
    else if (n - k == 3) {
        denbmax = 999;
    }

    li rembmin = 1;
    li rembmax = 9;
    if (k == 2) {
        rembmin = 10;
        rembmax = 99;
    }
    else if (k == 3) {
        rembmin = 100;
        rembmax = 999;
    }

    li sumnum = 0;
    li sumden = 0;
    for (li denb = 1; denb <= denbmax; denb++) { // loop over base denominator (2-digit)
        cout << "<---------- base denominator:" << denb << " ---------->" << endl;
        vi denbv = tovector(denb, n - k);
        for (li numb = 1; numb < denb; numb++) { // loop over base numerator (2-digit)
            //cout << " base numerator:" << numb << endl;
            vi numbv = tovector(numb, n - k);
            for (li remb = rembmin; remb <= rembmax; remb++) { // loop over the removable part (2-digit)

                // Exclude numbers with zeroes
                if (containszeroes(remb)) {
                    continue;
                }

                //cout << "  removable part:" << remb << endl;
                vi rembv = tovector(remb, k);

                vi numv(numbv);
                numv.insert(numv.end(), rembv.begin(), rembv.end()); // the full numerator
                vi denv(denbv);
                denv.insert(denv.end(), rembv.begin(), rembv.end()); // the ful denominator

                vector<vi> numperm = permutations(numv); // permutations of the full numerator
                vector<vi> denperm = permutations(denv); // permutations of the full denominator

                // Loop over permutations of the numerator and denominator
                for (vi numtmp : numperm) {

                    // Skip numbers starting with zeroes
                    if (numtmp[numtmp.size() - 1] == 0) {
                        continue;
                    }
                    for (vi dentmp : denperm) {

                        // Skip numbers starting with zeroes
                        if (dentmp[dentmp.size() - 1] == 0) {
                            continue;
                        }

                        // 1. Check the main condition: numtmp/dentmp == numbv/denbv
                        //    or: numtmp*denbv = numbv*dentmp
                        // 2. Memorization in the set
                        li numfull = tonumber(numtmp);
                        li denfull = tonumber(dentmp);
                        bool good = denb * numfull == numb * denfull;
                        if (good && passed.find(pair<li, li>(denfull, numfull)) == passed.end()) {

                            // Check if the order of the base part is conserved in the full numerator/denominator
                            bool numordergood = isorderconserved(numbv, numtmp);
                            bool denordergood = isorderconserved(denbv, dentmp);
                            if (numordergood && denordergood) {
                                outf1 << numfull << "/" << denfull << " = " << numb << "/" << denb << " removed: " << remb << endl;
                                cout << numfull << "/" << denfull << " = " << numb << "/" << denb << " removed: " << remb << endl;
                                sumnum += numfull;
                                sumden += denfull;
                                passed.insert(pair<li, li>(denfull, numfull));
                            }
                            else {
                                cout << numfull << "/" << denfull << " = " << numb << "/" << denb << " removed: " << remb << " - bad order, excluded" << endl;
                            }
                        }
                    }
                }
            }
        }
    }

    for (auto p : passed) {
        outf2 << p.first << " " << p.second << endl;
    }

    outf1 << "sumnum: " << sumnum << endl;
    outf1 << "sumden: " << sumden << endl;
    outf2 << "sumnum: " << sumnum << endl;
    outf2 << "sumden: " << sumden << endl;
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

    //test1();
    //test2();

    outf1.open("euler33_1.txt");
    outf2.open("euler33_2.txt");
    auto start = std::chrono::high_resolution_clock::now();
    solve(2, 1);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << " time = " << t << " s" << endl;
    outf1.close();
    outf2.close();
    return 0;
}
