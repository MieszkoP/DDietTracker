#ifndef DDT_H
#define DDT_H
#include <iostream>
#include <optional>
#include "size_unc.h"

class DDT
{
protected:
    DDT();
    //static DDT* _ddt;
public:
    //static DDT* GetInstace();
    DDT(DDT &other) = delete;
    void operator=(DDT &other) = delete;
    static std::string OptionToValueAsString(std::optional<size_unc> option);
    static std::string OptionToUncertaintyAsString(std::optional<size_unc> option);
    static std::optional<size_unc> StringToProductOption(std::string value, std::string uncertainty);
    template<typename T> static bool OptionalHasValue(std::optional<T> opt)
    {
        return opt.has_value();
    }
};

#endif // DDT_H
