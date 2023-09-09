#ifndef DDT_H
#define DDT_H
#include <iostream>
#include <optional>
#include "size_unc.h"
#include <chrono>

class DDT
{
protected:
    DDT() = default;
    static DDT* _ddt;
public:
    static DDT* GetInstace();
    DDT(DDT &other) = delete;
    void operator=(DDT &other) = delete;
    static std::string OptionToValueAsString(std::optional<size_unc> option);
    static std::string OptionToUncertaintyAsString(std::optional<size_unc> option);
    static std::optional<size_unc> StringToProductOption(std::string value, std::string uncertainty);
    template<typename T> static bool OptionalHasValue(std::optional<T> opt)
    {
        return opt.has_value();
    }
    static std::optional<std::chrono::hh_mm_ss< std::chrono::minutes>> StringToTimeOption(std::string time);
    static std::optional<std::chrono::year_month_day> StringToDateOption(std::string date);
    static std::string DateOptionAsString(std::optional<std::chrono::year_month_day> date);
    static std::string TimeOptionAsString(std::optional<std::chrono::hh_mm_ss< std::chrono::minutes>> time);
    static void LoadProductBase();
    static void UpdateProductBase();
};

#endif // DDT_H
