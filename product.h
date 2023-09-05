#ifndef PRODUCT_H
#define PRODUCT_H
#include "size_unc.h"
#include "productcategory.h"
#include <optional>

enum class QuantityType {velocity, mass};

//The Product class is a data entity that describes a registered product. It is not a unit of product consumed.
class Product
{
public:
    Product() = default;
    Product(std::string name);
    QuantityType _quantityType = QuantityType::mass;
    ProductCategory _productCategory;
    std::optional<size_unc> _kcalories;
    std::optional<size_unc> _proteins;
    std::optional<size_unc> _carbons;
    std::optional<size_unc> _fats;
    std::optional<size_unc> _quantity = 100; // Used for macronutrient calculations [g\ml]
    std::optional<size_unc> _standard_quantity; // Estimation of the standard amount consumed [g\ml]
    std::string _name = "None";
    bool operator==(const Product& other) const = default;
    friend std::ostream& operator<<(std::ostream& os, const Product prod);
};

#endif // PRODUCT_H
