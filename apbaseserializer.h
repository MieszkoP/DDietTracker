#ifndef APBASESERIALIZER_H
#define APBASESERIALIZER_H

#include "abstract_serializer.h"
#include "allproductsbase.h"
#include <jsoncpp/json/json.h>

class APBaseSerializer : public AbstractSerializer
{
public:
    APBaseSerializer(Json::Value& root);
    void ObjectToRoot(const AllProductsBase* productBase);
};

#endif // APBASESERIALIZER_H
