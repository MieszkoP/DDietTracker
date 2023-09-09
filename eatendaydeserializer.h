#ifndef EATENDAYDESERIALIZER_H
#define EATENDAYDESERIALIZER_H
#include "abstract_deserializer.h"
#include "eatenday.h"

class EatenDayDeserializer : public AbstractDeserializer
{
public:
    EatenDayDeserializer(Json::Value& root);
    void RootToObject(EatenDay& eatenDay);
};

#endif // EATENDAYDESERIALIZER_H
