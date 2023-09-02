#include "abstract_serializer.h"

AbstractSerializer::AbstractSerializer(Json::Value& root) : _root{&root} {};

void AbstractSerializer::RootToFile(const std::string_view& filename)
{
    std::ofstream file(filename.data());
    file << (*_root);
    file.close();
}

void AbstractSerializer::RootToFile(std::ofstream& file)
{
    if(file.is_open())
    {
        file << (*_root);
    }
    else
    {
        throw(std::invalid_argument("File is already closed."));
    }
}

Json::Value& AbstractSerializer::GetRoot()
{
    return (*_root);
}
