#include "eatendayserializer.h"
#include "eatenproductserializer.h"

EatenDaySerializer::EatenDaySerializer(Json::Value& root) : AbstractSerializer(root)
{

}

void EatenDaySerializer::ObjectToRoot(EatenDay& eatenDay)
{
    int i = 0;
    for(int i= 0 ; i< eatenDay.Size(); i++)
    {
        Json::Value root;
        EatenProductSerializer eatenProductSerializer(root);
        auto eatenProduct = eatenDay.ReturnEatenProduct(i);
        eatenProductSerializer.ObjectToRoot(eatenProduct);
        _root->append(root);
    }

}
