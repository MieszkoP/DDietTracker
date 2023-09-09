#include "productcreator.h"
#include <vector>
#include "ddt.h"


ProductCreator::ProductCreator(std::string name)
{
    _product._name = name;
}

ProductCreator::ProductCreator(std::string name, size_unc quantity)
{
    _product._name = name;
    _product._quantity = quantity;
}

void ProductCreator::SetQuantityType(QuantityType quantity_type)
{
    _product._quantityType = quantity_type;
}

void ProductCreator::SetQuantity(size_unc quantity)
{
    _product._quantity = quantity;
}

void ProductCreator::SetName(std::string name)
{
    _product._name = name;
}

void ProductCreator::SetKcaloriesPerQuantity(size_unc kcalories)
{
    _product._kcalories = kcalories;
}

void ProductCreator::SetProteinsPerQuantity(size_unc proteins)
{
    _product._proteins = proteins;
}

void ProductCreator::SetCarbonsPerQuantity(size_unc carbons)
{
    _product._carbons = carbons;
}

void ProductCreator::SetFatsPerQuantity(size_unc fats)
{
    _product._fats = fats;
}

void ProductCreator::SetStandardQuantity(size_unc standard_quantity)
{
    _product._standard_quantity = standard_quantity;
}

void ProductCreator::SetThreeMacros(size_unc fats, size_unc carbons, size_unc proteins)
{
    SetFatsPerQuantity(fats);
    SetCarbonsPerQuantity(carbons);
    SetProteinsPerQuantity(proteins);
    CalculateMissing();
}

void ProductCreator::CalculateMissing()
{
    if(!_product._kcalories.has_value())
    {

        _product._kcalories = 4*(_product._carbons.value()+_product._proteins.value())+8*_product._fats.value();

    }
}

Product ProductCreator::Result()
{
    bool checker = true;
    std::vector<std::optional<size_unc>> important_values = {_product._kcalories, _product._proteins, _product._carbons, _product._fats, _product._quantity};
    std::vector<bool> bools;
    bools.resize(important_values.size());
    std::transform(important_values.begin(), important_values.end(), bools.begin(), DDT::OptionalHasValue<size_unc>);
    std::for_each(bools.begin(), bools.end(), [&checker](bool b){checker=checker&&b;});
    if(checker)
        return _product;
    else
        throw("Product is not ready yet");
}
