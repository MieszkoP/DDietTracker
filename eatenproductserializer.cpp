#include "eatenproductserializer.h"
#include "ddt.h"
#include "productserializer.h"

EatenProductSerializer::EatenProductSerializer(Json::Value& root) : AbstractSerializer(root)
{

}

void EatenProductSerializer::ObjectToRoot(const EatenProduct& eatenProduct)
{
    typedef std::string(*opt2_type)(std::optional<size_unc>);
    opt2_type opttval = DDT::OptionToValueAsString;
    opt2_type opttunc = DDT::OptionToUncertaintyAsString;

    (*_root)["quantity"]["value"] = opttval(eatenProduct.GetQuantity());
    (*_root)["quantity"]["uncertainty"] = opttunc(eatenProduct.GetQuantity());
    Product product = eatenProduct.GetProduct();

    Json::Value rootProduct;
    ProductSerializer productserializer(rootProduct);
    productserializer.ObjectToRoot(product);

    (*_root)["Product"] =rootProduct;
    (*_root)["Day"] = DDT::DateOptionAsString(eatenProduct.GetDate());
    (*_root)["Time"] = DDT::TimeOptionAsString(eatenProduct.GetTime());
}
