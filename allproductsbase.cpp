#include "allproductsbase.h"

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
    if(!IsProduct(product._name))
    {
        _base->insert({product._name, product});
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
}

void AllProductsBase::DeleteProduct(Product& product)
{
    _base->erase(product._name);
}

void AllProductsBase::ChangeProduct(Product& product)
{
    _base->insert_or_assign(product._name, product);
}

void AllProductsBase::ClearBase()
{
    _base->clear();
}
