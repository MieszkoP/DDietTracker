#include "allproductsbase.h"
#include <QDebug>
#include <sstream>
#include <iostream>
AllProductsBase* AllProductsBase::_allProductsBase = nullptr;

AllProductsBase* AllProductsBase::GetInstance()
{
    if(!_allProductsBase)
        _allProductsBase = new AllProductsBase();

    return _allProductsBase;
}

AllProductsBase::AllProductsBase()
{
    _base = new map_of_products_type();
    _categoriesMap = new map_of_categories_type();
}

void AllProductsBase::UpdateCategoriesMap()
{
    _categoriesMap->clear();
    for(auto& product : *_base)
    {
        (*_categoriesMap)[product.second._productCategory].push_back(&product.second);
    }
}

AllProductsBase::map_of_categories_type* AllProductsBase::GetCategoriesMap()
{
    return _categoriesMap;
}

AllProductsBase::map_of_products_type* AllProductsBase::GetBase()
{
    return _base;
}

bool AllProductsBase::IsProduct(std::string name)
{
    return _base->find(name)!=_base->end();
}

bool AllProductsBase::AddProduct(Product product)
{
    std::stringstream string_stream;
    string_stream << &product;

    if(!IsProduct(product._name))
    {
        _base->insert({product._name, product});
        auto* pointer = &(_base->at(product._name));
        (*_categoriesMap)[product._productCategory].push_back(pointer);
    }
   else
    {
        throw std::invalid_argument("This product already exists!");
    }

    return true;
}

Product& AllProductsBase::GetProduct(std::string name)
{
    return _base->at(name);
}

void AllProductsBase::DeleteProduct(const std::string& name)
{
    _base->erase(name);
    UpdateCategoriesMap();

}

void AllProductsBase::DeleteProduct(Product& product)
{
    _base->erase(product._name);
    UpdateCategoriesMap();
}

void AllProductsBase::ChangeProduct(Product& product)
{
    _base->insert_or_assign(product._name, product);
    UpdateCategoriesMap();
}

void AllProductsBase::ClearBase()
{
    _base->clear();
}
