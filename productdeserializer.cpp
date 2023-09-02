#include "productdeserializer.h"
#include "ddt.h"

ProductDeserializer::ProductDeserializer(Json::Value& root) : AbstractDeserializer(root)
{

}

void ProductDeserializer::RootToObject(Product& product)
{
    typedef std::optional<size_unc>(*type_conv)(std::string, std::string);
    type_conv stringtopt = DDT::StringToProductOption;

    product._carbons = stringtopt((*_root)["carbons"]["value"].asString(), (*_root)["carbons"]["uncertainty"].asString());
    product._kcalories = stringtopt((*_root)["kcalories"]["value"].asString(), (*_root)["kcalories"]["uncertainty"].asString());
    product._proteins = stringtopt((*_root)["proteins"]["value"].asString(), (*_root)["proteins"]["uncertainty"].asString());
    product._fats = stringtopt((*_root)["fats"]["value"].asString(), (*_root)["fats"]["uncertainty"].asString());
    product._quantity = stringtopt((*_root)["quantity"]["value"].asString(), (*_root)["quantity"]["uncertainty"].asString());
    product._standard_quantity = stringtopt((*_root)["standard_quantity"]["value"].asString(), (*_root)["standard_quantity"]["uncertainty"].asString());
    product._quantityType = static_cast<QuantityType>((*_root)["quantity_type"].asInt());
    product._productCategory = (*_root)["product_category"].asString();
}
