#ifndef ABSTRACT_SERIALIZER_H
#define ABSTRACT_SERIALIZER_H
#include <jsoncpp/json/json.h>
#include <fstream>

class AbstractSerializer
{
protected:
    Json::Value* _root;
public:
    AbstractSerializer(Json::Value& root);
    void RootToFile(const std::string_view& filename);
    void RootToFile(std::ofstream& file);
    Json::Value& GetRoot();
};

#endif // ABSTRACT_SERIALIZER_H
