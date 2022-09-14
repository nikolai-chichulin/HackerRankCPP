#ifndef BIG_INTEGER_AS_STRING_H
#define BIG_INTEGER_AS_STRING_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class bi
{
public:
    bi();
    bi(int i);
    bi(long long i);
    bi(const std::string&);

    ~bi();

    bi operator+(const bi& rhs);
    bi operator-(const bi& rhs);

    bool operator==(const bi& rhs);
    bool operator!=(const bi& rhs);

    bi operator+=(const bi& rhs);

    vector<int> digits() const;
    bool isNegative() const;

private:

    vector<int> v;
    bool negative = false;

};

std::ostream& operator<< (std::ostream& os, const bi& rhs);

#endif // !BIG_INTEGER_AS_STRING_H
