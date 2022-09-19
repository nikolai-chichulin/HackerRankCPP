#ifndef BIG_INTEGER_AS_STRING_H
#define BIG_INTEGER_AS_STRING_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class bi
{
public:
    bi();
    bi(int i);
    bi(long long i);
    bi(const std::string&);
    bi(vector<int>& v);

    ~bi();

    static bi zero();
    static bi unity();

    bool isZero() const;

    bi operator+(const bi& rhs) const;
    bi operator-(const bi& rhs) const;
    bi operator-() const;
    bi operator*(const bi& rhs) const;
    pair<bi, bi> operator/(const bi& rhs) const;

    bool operator==(const bi& rhs) const;
    bool operator!=(const bi& rhs) const;
    bool operator<(const bi& rhs) const;
    bool operator<=(const bi& rhs) const;
    bool operator>(const bi& rhs) const;
    bool operator>=(const bi& rhs) const;

    bi operator+=(const bi& rhs);

    int operator[](size_t i) const;

    size_t size() const;
    bi s() const; // sum of digits
    bi f() const; // sum of the digits factorials

    string tostring() const;

    void decomp(bi dcp[], const bi basis[], int n) const;
    static bi comp(bi dcp[], int n);

    static bi factorial(int);

private:

    static const char GROUP_SEPARATOR;

    vector<int> v;
    bool negative = false;

    bool isUnity() const;

    static bi sum(const bi& a, const bi& b); // summation of two positive bi
    static bi subtr(const bi& a, const bi& b); // subtraction of two positive bi, the minued must be greater

    // Vector utilities
    static bool lessthan(vector<int> v1, vector<int> v2);
    static bool equalto(vector<int> v1, vector<int> v2);
    static vector<int> sum(vector<int> v1, vector<int> v2);
    static vector<int> subtr(vector<int> v1, vector<int> v2);

};

std::ostream& operator<< (std::ostream& os, const bi& rhs);

#endif // !BIG_INTEGER_AS_STRING_H
