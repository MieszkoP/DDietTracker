#include "apbaseserializer.h"
#include "productserializer.h"

APBaseSerializer::APBaseSerializer(Json::Value& root) : AbstractSerializer(root)
{

}

void APBaseSerializer::ObjectToRoot(const AllProductsBase* productBase)
{
    auto base = productBase->GetInstance()->GetBase();

    for(auto& x : *base)
    {
        Json::Value productRoot;
        ProductSerializer productSerializer = ProductSerializer(productRoot);
        productSerializer.ObjectToRoot(x.second);
        (*_root)[x.first] = productSerializer.GetRoot();
    }
}
