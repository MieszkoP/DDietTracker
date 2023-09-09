#include "eatenproductdeserializer.h"
#include "productdeserializer.h"
#include "ddt.h"

EatenProductDeserializer::EatenProductDeserializer(Json::Value& root)
 : AbstractDeserializer(root)
{

}

void EatenProductDeserializer::RootToObject(EatenProduct& eatenProduct)
{
    Product product;
    ProductDeserializer productDeserializer((*_root)["Product"]);
    productDeserializer.RootToObject(product);
    eatenProduct.SetProduct(product);

    eatenProduct.SetTime(DDT::StringToTimeOption((*_root)["Time"].asString()));
    eatenProduct.SetDate(DDT::StringToDateOption((*_root)["Day"].asString()));

    auto quantity = DDT::StringToProductOption((*_root)["quantity"]["value"].asString() ,(*_root)["quantity"]["uncertainty"].asString());
    eatenProduct.SetQuantity(quantity);

}
