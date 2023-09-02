#ifndef PRODUCTCATEGORY_H
#define PRODUCTCATEGORY_H
#include <ostream>

class ProductCategory
{
public:
    std::string _name;
    ProductCategory(std::string name = "None");
    bool operator==(const ProductCategory& other) const = default;
};

#endif // PRODUCTCATEGORY_H
