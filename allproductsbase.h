#ifndef ALLPRODUCTSBASE_H
#define ALLPRODUCTSBASE_H
#include "product.h"
#include <unordered_map>

class AllProductsBase
{
protected:
    using map_of_products_type =  std::unordered_map<std::string, Product>;
    map_of_products_type* _base;;
    static AllProductsBase* _allProductsBase;
    AllProductsBase();
public:
    AllProductsBase(AllProductsBase &other) = delete;
    AllProductsBase& operator=(AllProductsBase &other) = delete;
    static AllProductsBase* GetInstance();
    map_of_products_type* GetBase();
    bool AddProduct(Product product);
    Product& GetProduct(std::string name);
    bool IsProduct(std::string name);
    void DeleteProduct(const std::string& name);
    void DeleteProduct(Product& product);
    void ChangeProduct(Product& product);
    void ClearBase();
};

#endif // ALLPRODUCTSBASE_H
