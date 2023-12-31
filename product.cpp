#include "product.h"

Product::Product(const std::string& name) : _name(name) {};

std::ostream& operator<<(std::ostream& ostr, const Product& prod)
{
    return ostr<<prod._name;
};
