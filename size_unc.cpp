#include "size_unc.h"

size_unc operator+(const size_unc &n1, const size_unc &n2)
{
    return size_unc(n1._size+n2._size, std::hypot(n1._unc, n2._unc));
};

size_unc operator-(const size_unc &n1, const size_unc &n2)
{
    return size_unc(n1._size-n2._size, std::hypot(n1._unc, n2._unc));
};

size_unc operator*(const size_unc &n1, const size_unc &n2)
{
    float z = n1._size*n2._size;
    return size_unc(z, z*std::hypot(n1._unc/n1._size, n2._unc/n2._size));
};

size_unc operator/(const size_unc &n1, const size_unc &n2)
{
    return size_unc(n1._size/n2._size, std::sqrt(n1._unc/n2._unc-n1._size/(n2._size*n2._size)*n2._unc));
};

float size_unc::GetUpperBound() const
{
    return _size-_unc;
};

float size_unc::GetLowerBound() const
{
    return _size+_unc;
};

std::ostream& operator<<(std::ostream& ostr, const size_unc& obj)
{
    return ostr<<obj._size<<" unc.: "<<obj._unc;
};

/*
std::istream &operator>>(std::istream& istr, const size_unc& obj)
{
    return istr>>obj._size;
};
*/

bool size_unc::operator==(const size_unc& other) const
{
    return _size<=other.GetUpperBound() && _size>=other.GetLowerBound();
};

bool size_unc::operator>(const size_unc& other) const
{
    return _size>other.GetUpperBound();
};

bool size_unc::operator<(const size_unc& other) const
{
    return _size<other.GetLowerBound();
};

bool size_unc::operator>=(const size_unc& other) const
{
    return _size>=other.GetUpperBound();
};

bool size_unc::operator<=(const size_unc& other) const
{
    return _size<=other.GetLowerBound();
};

bool size_unc::operator!=(const size_unc& other) const
{
    return !(*this==other);
};

float size_unc::GetValue() const
{
    return _size;
}
