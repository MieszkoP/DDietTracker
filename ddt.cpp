#include "ddt.h"

DDT::DDT()
{

}

//DDT* DDT::GetInstace()
//{
//    if(DDT::_ddt==nullptr)
//    {
//        DDT::_ddt= new DDT();
//    }
//    return DDT::_ddt;;
//}

std::string DDT::OptionToValueAsString(std::optional<size_unc> option)
{
    if (option.has_value())
    {
        return std::to_string(option.value().GetValue());
    }
    else
    {
        return "None";
    }
}

std::string DDT::OptionToUncertaintyAsString(std::optional<size_unc> option)
{
    if (option.has_value())
    {
        return std::to_string(option.value().GetUncertainty());
    }
    else
    {
        return "None";
    }
}

std::optional<size_unc> DDT::StringToProductOption(std::string value, std::string uncertainty)
{
    std::optional<size_unc> output;
    try
    {
        output  = size_unc(std::stof(value), std::stof(uncertainty));
    }
    catch(const std::invalid_argument& e)
    {

    }
    return output;
}
