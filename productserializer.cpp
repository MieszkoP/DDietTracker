#include "productserializer.h"
#include "ddt.h"

ProductSerializer::ProductSerializer(Json::Value& root) : AbstractSerializer(root)
{

}

void ProductSerializer::ObjectToRoot(const Product& product)
{
    typedef std::string(*opt2_type)(std::optional<size_unc>);
    opt2_type opttval = DDT::OptionToValueAsString;
    opt2_type opttunc = DDT::OptionToUncertaintyAsString;

    (*_root)["name"] = product._name;
    (*_root)["carbons"]["value"] = opttval(product._carbons);
    (*_root)["kcalories"]["value"] = opttval(product._kcalories);
    (*_root)["proteins"]["value"] = opttval(product._proteins);
    (*_root)["fats"]["value"] = opttval(product._fats);
    (*_root)["quantity"]["value"] = opttval(product._quantity);
    (*_root)["standard_quantity"]["value"] = opttval(product._standard_quantity);

    (*_root)["quantity_type"] = int(product._quantityType);
    (*_root)["product_category"] = product._productCategory._name;

    (*_root)["carbons"]["uncertainty"] = opttunc(product._carbons);
    (*_root)["kcalories"]["uncertainty"] = opttunc(product._kcalories);
    (*_root)["proteins"]["uncertainty"] = opttunc(product._proteins);
    (*_root)["fats"]["uncertainty"] = opttunc(product._fats);
    (*_root)["quantity"]["uncertainty"] = opttunc(product._quantity);
    (*_root)["standard_quantity"]["uncertainty"] = opttunc(product._standard_quantity);
}
