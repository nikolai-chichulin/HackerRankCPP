#ifndef UTIL_H
#define UTIL_H

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <set>

using namespace std;

typedef long long li;

li sqroot(li i);
li ldiv(li n);
vector<li> makeprimeswithsieve(li nmax);
void divisors(const li pol[], li nmax);
bool fermat(li a, li n);
li powli(li base, li exp);
li mul(li a, li b, li m);
li pows(li a, li b, li m);
li gcd(li a, li b);
bool ferma(li x);
li index(li a, li b, li c, li i);
void indextest(li a, li b, li c, li nmax);

#endif // !UTIL_H
