#ifndef APBASEDESERIALIZER_H
#define APBASEDESERIALIZER_H

#include "abstract_deserializer.h"
#include "allproductsbase.h"

class APBaseDeserializer : public AbstractDeserializer
{
public:
    APBaseDeserializer(Json::Value& root);
    void RootToObject(AllProductsBase* allProductBase);
};

#endif // APBASEDESERIALIZER_H
