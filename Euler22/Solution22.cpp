#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <set>

using namespace std;

int main() {

    std::set<std::string> names;

    names.insert("ALEX");
    names.insert("LUIS");
    names.insert("JAMES");
    names.insert("BRIAN");
    names.insert("PaMELA");

    string name = "PaMELA";
    auto it = names.find(name);

    int s = 0;
    for (char c : *it) {
        int add = c - 'a' + 1;
        if (add < 0) {
            add += 32;
        }
        s += add;
    }
    s *= std::distance(names.begin(), it) + 1;

    cout << s << endl;

}
