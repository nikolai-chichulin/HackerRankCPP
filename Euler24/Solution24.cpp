#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

typedef long long li;

const li fact[] = { 1,1,2,6,24,120,720,5040,40320,362880,3628800,39916800,479001600 };

li firstletter(li n, li i) {

    li ind = -1;
    for (li k = 0; k <= n - 1; k++) {
        if (i > (k * fact[n - 1]) && i <= (k + 1) * fact[n - 1]) {
            ind = k;
            break;
        }
    }
    return ind;
}

string solve(const string s, li i) {

    string ret;
    string tmp = s;
    while (tmp.length() > 0) {

        li first = firstletter(tmp.length(), i);
        ret.push_back(tmp[first]);

        tmp.erase(tmp.begin() + first);
        i -= first * fact[tmp.length()];
    }
    return ret;
}

int main() {

    //char c = firstletter("abcdefg", 3456);
    //char c = firstletter("abcdfg", 576);
    //char c = firstletter("abcdg", 96);
    //char c = firstletter("abcg", 24);
    //char c = firstletter("ab", 2);

    string ret = solve("abcdefghijklm", 2);
    cout << ret << endl;

    return 0;
}
