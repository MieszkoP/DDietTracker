#include "eatendaydeserializer.h"
#include "eatenproductdeserializer.h"

EatenDayDeserializer::EatenDayDeserializer(Json::Value& root) : AbstractDeserializer(root)
{

}

void EatenDayDeserializer::RootToObject(EatenDay& eatenDay)
{
    for(auto& eatenDayRoot : (*_root))
    {
        EatenProduct eatenProduct;
        EatenProductDeserializer eatenProductDeserializer(eatenDayRoot);
        eatenProductDeserializer.RootToObject(eatenProduct);
        eatenDay.AddEatenProduct(eatenProduct);
    }
}
