#include "ddt.h"
#include <chrono>
#include <regex>
#include <filesystem>
#include "allproductsbase.h"
#include <json/json.h>
#include "apbaseserializer.h"
#include "apbasedeserializer.h"
#include <QDebug>

DDT* DDT::_ddt = nullptr;

DDT* DDT::GetInstace()
{
    if(!_ddt)
    {
        _ddt= new DDT();
    }
    return DDT::_ddt;;
}

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

std::optional<std::chrono::hh_mm_ss< std::chrono::minutes>> DDT::StringToTimeOption(std::string time)
{
    std::regex pat {R"((\d+)\:(\d+))"};

    std::smatch m;

    if(std::regex_match(time, pat))
    {
        std::regex_search(time, m, pat);
        auto hour = m[1].str();
        auto minute = m[2].str();

        std::chrono::hours h(std::stoi(hour));
        std::chrono::minutes m(std::stoi(minute));
        return std::chrono::hh_mm_ss<std::chrono::minutes>(h+m);

    }
    else
    {
        return std::nullopt;
    }

}

std::optional<std::chrono::year_month_day> DDT::StringToDateOption(std::string date)
{
    std::regex pat {R"((\d+)\.(\d+)\.(\d+))"};

    std::smatch m;

    if(std::regex_match(date, pat))
    {
        std::regex_search(date, m, pat);
        auto day = m[1].str();
        auto month = m[2].str();
        auto year = m[3].str();

        return std::chrono::year_month_day(
            std::chrono::year(std::stoi(year)),
            std::chrono::month(std::stoi(month)),
            std::chrono::day(std::stoi(day))
            );
    }
    else
    {
        return std::nullopt;
    }
}




std::string DDT::DateOptionAsString(std::optional<std::chrono::year_month_day> date)
{
    if (date.has_value())
    {
        std::string day = std::to_string(unsigned(date.value().day()));
        std::string month = std::to_string(unsigned(date.value().month()));
        std::string year = std::to_string(int(date.value().year()));

        return day+"."+month+"."+year;
    }
    else
    {
        return "None";
    }
}

std::string DDT::TimeOptionAsString(std::optional<std::chrono::hh_mm_ss< std::chrono::minutes>> time)
{
    if (time.has_value())
    {
        std::string hour = std::to_string(time.value().hours().count());
        std::string minute = std::to_string(time.value().minutes().count());
        return hour+":"+minute;
    }
    else
    {
        return "None";
    }
}

void DDT::LoadProductBase()
{
    auto products = AllProductsBase::GetInstance();
    products->ClearBase();

    if(!std::filesystem::exists("product_base.json"))
    {
        Product product1("Onion");
        Product product2("Carrot");
        Product product3("Water");

        auto products = AllProductsBase::GetInstance();

        product1._kcalories = {39, 1};
        product1._productCategory._name = "Vegetable";
        product1._carbons={9, 1};
        product1._proteins={1.1, 0.1};
        product1._fats={0.1, 0};
        product1._standard_quantity = 100;

        product2._kcalories = {41, 1};
        product2._productCategory._name = "Vegetable";
        product2._carbons={10, 1};
        product2._proteins={1, 1};
        product2._fats={0, 0};
        product2._standard_quantity = 100;

        product3._kcalories = {0, 0};
        product3._productCategory._name = "Drink";
        product3._carbons={0, 0};
        product3._proteins={0, 0};
        product3._fats={0, 0};
        product3._standard_quantity = 100;

        products->AddProduct(product1);
        products->AddProduct(product2);
        products->AddProduct(product3);

        Json::Value root;
        APBaseSerializer apbkserializer(root);
        apbkserializer.ObjectToRoot(products);
        std::ofstream file("product_base.json");
        file << root;
        file.close();
    }
    products->ClearBase();
    std::ifstream file2("product_base.json");
    Json::Value root2;
    APBaseDeserializer deserializer(root2);
    deserializer.FileToRoot(file2);
    deserializer.RootToObject(products);
    file2.close();

    if(!std::filesystem::is_directory("days"))
        std::filesystem::create_directory("days");
}

void DDT::UpdateProductBase()
{
    auto products = AllProductsBase::GetInstance();
    Json::Value root;
    APBaseSerializer apbkserializer(root);
    apbkserializer.ObjectToRoot(products);
    std::ofstream file("product_base.json");
    file << root;
    file.close();
}
