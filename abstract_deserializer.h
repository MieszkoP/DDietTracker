#ifndef ABSTRACT_DESERIALIZER_H
#define ABSTRACT_DESERIALIZER_H
#include <jsoncpp/json/json.h>
#include <fstream>


class AbstractDeserializer
{
protected:
    Json::Value* _root; //Will be encapsulated in the future
public:
    explicit AbstractDeserializer(Json::Value& root);
    void FileToRoot(const std::string_view& filename);
    void FileToRoot(std::ifstream& file);
    Json::Value& GetRoot();
};


#endif // ABSTRACT_DESERIALIZER_H
