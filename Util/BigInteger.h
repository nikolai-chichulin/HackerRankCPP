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

    ~bi();

    bi operator+(const bi& rhs) const;
    bi operator-(const bi& rhs) const;
    bi operator*(const bi& rhs) const;

    bool operator==(const bi& rhs) const;
    bool operator!=(const bi& rhs) const;
    bool operator<(const bi& rhs) const;
    bool operator<=(const bi& rhs) const;
    bool operator>(const bi& rhs) const;
    bool operator>=(const bi& rhs) const;

    bi operator+=(const bi& rhs);

    int operator[](size_t i) const;

    bool isNegative() const;
    bool isZero() const;
    size_t size() const;

private:

    vector<int> v;
    bool negative = false;

    static bi sum(const bi& a, const bi& b); // summation of two positive bi
    static bi subtr(const bi& a, const bi& b); // subtraction of two positive bi, the minued must be greater

};

std::ostream& operator<< (std::ostream& os, const bi& rhs);

#endif // !BIG_INTEGER_AS_STRING_H
