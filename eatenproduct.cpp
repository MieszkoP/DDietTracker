#include "eatenproduct.h"

EatenProduct::EatenProduct(const Product& product) : _product{product}
{

}

EatenProduct::EatenProduct(const Product& product, size_unc eaten_quantity)
    : _product{product},
    _eaten_quantity{eaten_quantity}
{

}

void EatenProduct::SetQuantity(std::optional<size_unc> eaten_quantity)
{
    _eaten_quantity = eaten_quantity;
}

void EatenProduct::SetQuantityAsDefault()
{
    if(_product._name!="None")
    {
        _eaten_quantity = _product._standard_quantity;
    }
    else
    {
    throw std::invalid_argument("No product!");
    }
}

size_unc EatenProduct::GetProteins() const
{
    IsReady();
    return _product._proteins.value()*_eaten_quantity.value()/_product._quantity.value();
}

size_unc EatenProduct::GetKcalories() const
{
    IsReady();
    return _product._kcalories.value()*_eaten_quantity.value()/_product._quantity.value();
}

size_unc EatenProduct::GetFats() const
{
    IsReady();
    return _product._fats.value()*_eaten_quantity.value()/_product._quantity.value();
}

size_unc EatenProduct::GetCarbons() const
{
    IsReady();
    return _product._carbons.value()*_eaten_quantity.value()/_product._quantity.value();
}

void EatenProduct::IsReady() const
{
    if (_eaten_quantity.has_value() && _product._name!="None")
    {
    return;
    }
    else
    {
    throw std::logic_error("No product or eaten quantity!");
    }
}

void EatenProduct::SetDate(int year, int month, int day)
{
    _day = std::chrono::year_month_day(
        std::chrono::year(year),
        std::chrono::month(month),
        std::chrono::day(day)
        );
}

void EatenProduct::SetTime(int hour, int minute)
{
    std::chrono::hours h(hour);
    std::chrono::minutes m(minute);
    _time = std::chrono::hh_mm_ss<std::chrono::minutes>(h+m);
}

void EatenProduct::SetDate(const std::optional<std::chrono::year_month_day>& date)
{
    _day = date;
}

void EatenProduct::SetTime(const std::optional<std::chrono::hh_mm_ss<std::chrono::minutes>>& time)
{
    _time = time;
}

Product EatenProduct::GetProduct() const
{
    return _product;
}

std::optional<std::chrono::year_month_day> EatenProduct::GetDate() const
{
    return _day;
}

std::optional<std::chrono::hh_mm_ss< std::chrono::minutes>> EatenProduct::GetTime() const
{
    return _time;
}

std::optional<size_unc> EatenProduct::GetQuantity() const
{
    return _eaten_quantity;
}

void EatenProduct::SetProduct(const Product& product)
{
    _product = product;
}

std::ostream& operator<<(std::ostream& ostr, const EatenProduct& obj)
{
    if (obj.GetQuantity().has_value())
        return ostr<<"ProductName: "<<obj.GetProduct()._name<<"EatenQuantity: "<<obj.GetQuantity().value().GetValue();
    return ostr<<"ProductName: "<<obj.GetProduct()._name<<"No eaten quantity precised";
}
