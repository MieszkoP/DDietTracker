#ifndef EATENPRODUCTSERIALIZER_H
#define EATENPRODUCTSERIALIZER_H
#include "abstract_serializer.h"
#include "eatenproduct.h"

class EatenProductSerializer : public AbstractSerializer
{
public:
    EatenProductSerializer(Json::Value& root);
    void ObjectToRoot(const EatenProduct& eatenProduct);
};

#endif // EATENPRODUCTSERIALIZER_H
