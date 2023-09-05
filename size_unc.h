#ifndef SIZE_UNC_H
#define SIZE_UNC_H

#include <iostream>
#include <cmath>
#include <optional>

class size_unc
{
private:
    float _size;
    float _unc;

public:

    template <typename T1, typename T2> size_unc(T1 size, T2 unc): _size{static_cast<float>(size)}, _unc{static_cast<float>(unc)}
    {
        if(std::numeric_limits<float>::max()<size || std::numeric_limits<float>::lowest()>size)
            throw(std::invalid_argument("The value is outside the range of possible values for the type."));

        if(std::numeric_limits<float>::max()<unc || std::numeric_limits<float>::lowest()>unc)
            throw(std::invalid_argument("The uncertainty is outside the range of possible values for the type: "+std::to_string(unc)));

    };

    template <typename T1> size_unc(T1 size): _size{static_cast<float>(size)}, _unc{static_cast<float>(0)}
    {
        if(std::numeric_limits<float>::max()<size || std::numeric_limits<float>::lowest()>size)
            throw(std::invalid_argument("The value is outside the range of possible values for the type."));

    };

    size_unc& operator=(std::initializer_list<float> input)
    {
        _size = *(input.begin());
        _unc = *(input.begin()+1);
        return *this;
    };

    size_unc(std::initializer_list<float> input)
    {
        _size = *(input.begin());
        _unc = *(input.begin()+1);
    };

    friend std::ostream& operator<<(std::ostream& ostr, const size_unc& obj);
    friend std::istream &operator>>(std::istream& istr, const size_unc& obj);

    friend size_unc operator+(const size_unc &n1, const size_unc &n2);
    friend size_unc operator-(const size_unc &n1, const size_unc &n2);
    friend size_unc operator*(const size_unc &n1, const size_unc &n2);
    friend size_unc operator/(const size_unc &n1, const size_unc &n2);

    float GetUpperBound() const;
    float GetLowerBound() const;

    void operator++() = delete;
    void operator--() = delete;
    bool operator==(const size_unc& other) const;
    bool operator>(const size_unc& other) const;
    bool operator<(const size_unc& other) const;
    bool operator<=(const size_unc& other) const;
    bool operator>=(const size_unc& other) const;
    bool operator!=(const size_unc& other) const;

    float GetValue() const;
    float GetUncertainty() const;


};

#endif // SIZE_UNC_H
