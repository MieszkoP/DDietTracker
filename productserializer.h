#ifndef PRODUCTSERIALIZER_H
#define PRODUCTSERIALIZER_H
#include <jsoncpp/json/json.h>
#include "product.h"
#include <fstream>
#include "abstract_serializer.h"

//Serialization here works like this: object -> json::value -> file

class ProductSerializer : public AbstractSerializer
{
public:
    ProductSerializer(Json::Value& root);
    void ObjectToRoot(const Product& product);
};

#endif // PRODUCTSERIALIZER_H
