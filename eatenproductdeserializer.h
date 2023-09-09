#ifndef EATENPRODUCTDESERIALIZER_H
#define EATENPRODUCTDESERIALIZER_H
#include "abstract_deserializer.h"
#include <jsoncpp/json/json.h>
#include "eatenproduct.h"
#include <fstream>

class EatenProductDeserializer : public AbstractDeserializer
{
public:
    EatenProductDeserializer(Json::Value& root);
    void RootToObject(EatenProduct& eatenProduct);
};

#endif // EATENPRODUCTDESERIALIZER_H
