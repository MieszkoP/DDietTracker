#include "abstract_deserializer.h"

AbstractDeserializer::AbstractDeserializer(Json::Value& root):  _root{&root} {}

void AbstractDeserializer::FileToRoot(const std::string_view& filename)
{
    std::ifstream file(filename.data());
    file >> (*_root);
    file.close();
}

void AbstractDeserializer::FileToRoot(std::ifstream& file)
{
    if(file.is_open())
    {
        file >> (*_root);
    }
    else
    {
        throw(std::invalid_argument("File is already closed."));
    }
}

Json::Value& AbstractDeserializer::GetRoot()
{
    return (*_root);
}
