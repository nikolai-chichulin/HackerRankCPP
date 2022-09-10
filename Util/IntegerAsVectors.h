#ifndef INTEGER_AS_VECTORS_H
#define INTEGER_AS_VECTORS_H

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<int> sum(vector<int> a, vector<int> b);
vector<int> subtr(vector<int> a, vector<int> b);
vector<int> multiply(vector<int> a, int b);
vector<int> multiply(vector<int> a, vector<int> b);
vector<int> power(vector<int> v, int n);
vector<int> power(vector<int> v, int i, int n);
pair<vector<int>, vector<int>> divide(vector<int> v1, vector<int> v2);
vector<int> factorial(int a);
vector<int> factorialM(int a);

#endif // !INTEGER_AS_VECTORS_H
