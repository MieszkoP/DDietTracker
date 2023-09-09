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

template <>
struct std::hash<ProductCategory>
{
    std::size_t operator()(const ProductCategory& category) const
    {
        return ((hash<std::string>()(category._name)));
    }
};

#endif // PRODUCTCATEGORY_H
