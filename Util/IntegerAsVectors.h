#ifndef INTEGER_AS_VECTORS_H
#define INTEGER_AS_VECTORS_H

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

bool lessthan(vector<int> v1, vector<int> v2);
bool equalto(vector<int> v1, vector<int> v2);

vector<int> sum(vector<int> a, vector<int> b);
vector<int> subtr(vector<int> a, vector<int> b);
vector<int> multiply(vector<int> a, int b);
vector<int> multiply(vector<int> a, vector<int> b);
vector<int> power(vector<int> v, int n);
vector<int> power(vector<int> v, int i, int n);
pair<vector<int>, vector<int>> divide(vector<int> v1, vector<int> v2);
vector<int> factorial(int a);
vector<int> factorialM(int a);
vector<int> comp(vector<int> basis[], vector<int> terms[], int n); // composition of a number from the given basis
vector<int>* decomp(vector<int> v, vector<int> basis[], int n); // decomposition of a number in the given basis

#endif // !INTEGER_AS_VECTORS_H
