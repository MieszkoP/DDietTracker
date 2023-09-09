#ifndef PRODUCTDESERIALIZER_H
#define PRODUCTDESERIALIZER_H
#include "abstract_deserializer.h"
#include <jsoncpp/json/json.h>
#include "product.h"
#include <fstream>

//Deserialization here works like this: file -> json::value -> object

class ProductDeserializer : public AbstractDeserializer
{
public:
    ProductDeserializer(Json::Value& root);
    void RootToObject(Product& product);
};

#endif // PRODUCTDESERIALIZER_H
