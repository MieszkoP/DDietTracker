#include "apbasedeserializer.h"
#include "productdeserializer.h"

APBaseDeserializer::APBaseDeserializer(Json::Value& root) : AbstractDeserializer(root)
{

}

void APBaseDeserializer::RootToObject(AllProductsBase* allProductBase)
{
    allProductBase->ClearBase();
    for(auto& projectRoot : *_root)
    {
        Product product;
        ProductDeserializer productDeserializer(projectRoot);
        productDeserializer.RootToObject(product);
        allProductBase->AddProduct(product);
    }
}

