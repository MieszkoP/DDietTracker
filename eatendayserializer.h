#ifndef EATENDAYSERIALIZER_H
#define EATENDAYSERIALIZER_H
#include "abstract_serializer.h"
#include "eatenday.h"

class EatenDaySerializer : public AbstractSerializer
{
public:
    EatenDaySerializer(Json::Value& root);
    void ObjectToRoot(EatenDay& product);
};

#endif // EATENDAYSERIALIZER_H
