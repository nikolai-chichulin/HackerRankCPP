#ifndef DECOMP_TESTS_H
#define DECOMP_TESTS_H

#include "IntegerAsVectors.h"

bool compTest(vector<int> basis[], vector<int> terms[], int n, vector<int> exp);
bool compTests();
bool decompTest(vector<int> v, vector<int> basis[], int n, vector<int> exp[]);
bool decompTests();

#endif // !DECOMP_TESTS_H
