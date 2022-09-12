#ifndef DECOMP_TESTS_H
#define DECOMP_TESTS_H

#include "typedefs.h"

#include "IntegerAsVectors.h"

bool compTest(vl basis[], vl terms[], ls n, vl exp);
bool compTests();
bool decompTest(vl v, vl basis[], ls n, vl exp[]);
bool decompTests();

#endif // !DECOMP_TESTS_H
