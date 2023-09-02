#ifndef PRODUCTCREATOR_H
#define PRODUCTCREATOR_H
#include "product.h"
#include "ddt.h"

class ProductCreator
{
    Product _product;
public:
    ProductCreator() = default;
    ProductCreator(std::string name);
    ProductCreator(std::string name, size_unc quantity);
    void SetQuantityType(QuantityType quantity_type);
    void SetQuantity(size_unc quantity);
    void SetName(std::string name);
    void SetKcaloriesPerQuantity(size_unc kcalories);
    void SetProteinsPerQuantity(size_unc proteins);
    void SetCarbonsPerQuantity(size_unc carbons);
    void SetFatsPerQuantity(size_unc fats);
    void SetStandardQuantity(size_unc standard_quantity);
    void SetThreeMacros(size_unc fats, size_unc carbons, size_unc proteins);
    void CalculateMissing();
    Product Result();
};

#endif // PRODUCTCREATOR_H
