#ifndef ABSTRACT_SERIALIZER_H
#define ABSTRACT_SERIALIZER_H
#include <jsoncpp/json/json.h>
#include <fstream>

class AbstractSerializer
{
protected:
    Json::Value* _root; //encapsulation will be implemented in future
public:
    explicit AbstractSerializer(Json::Value& root);
    void RootToFile(const std::string_view& filename) const;
    void RootToFile(std::ofstream& file) const;
    Json::Value& GetRoot();
};

#endif // ABSTRACT_SERIALIZER_H
