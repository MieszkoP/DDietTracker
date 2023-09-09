#ifndef PRODUCTSERIALIZER_H
#define PRODUCTSERIALIZER_H
#include <jsoncpp/json/json.h>
#include "abstract_serializer.h"
#include <fstream>
#include "product.h"

//Serialization here works like this: object -> json::value -> file

class ProductSerializer : public AbstractSerializer
{
public:
    ProductSerializer(Json::Value& root);
    void ObjectToRoot(const Product& product);
};

#endif // PRODUCTSERIALIZER_H
