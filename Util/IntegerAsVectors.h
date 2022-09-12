#ifndef INTEGER_AS_VECTORS_H
#define INTEGER_AS_VECTORS_H

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

#include "typedefs.h"

using namespace std;

bool lessthan(vl v1, vl v2);
bool equalto(vl v1, vl v2);

vl sum(vl a, vl b);
vl subtr(vl a, vl b);
vl multiply(vl a, ls b);
vl multiply(vl a, vl b);
vl power(vl v, ls n);
vl power(vl v, ls i, ls n);
pair<vl, vl> divide(vl v1, vl v2);
vl factorial(ls a);
vl factorialM(ls a);
vl comp(vl basis[], vl terms[], ls n); // composition of a number from the given basis
vl* decomp(vl v, vl basis[], ls n); // decomposition of a number in the given basis

#endif // !INTEGER_AS_VECTORS_H
