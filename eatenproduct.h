#ifndef EATENPRODUCT_H
#define EATENPRODUCT_H
#include "product.h";
#include <chrono>

inline bool operator==(std::optional<std::chrono::hh_mm_ss< std::chrono::minutes>> time1, std::optional<std::chrono::hh_mm_ss< std::chrono::minutes>> time2)
{
    if(!time1.has_value() && !time1.has_value())
        return true;

    if(time1.value().hours() != time2.value().hours())
        return false;

    if(time1.value().minutes() != time2.value().minutes())
        return false;

    return true;
}

class EatenProduct
{
    Product _product;
    std::optional<size_unc> _eaten_quantity;
    std::optional<std::chrono::year_month_day> _day;
    std::optional<std::chrono::hh_mm_ss< std::chrono::minutes>> _time;
    void IsReady() const;
public:
    EatenProduct() = default;
    EatenProduct(Product product);
    EatenProduct(Product product, size_unc eaten_quantity);
    void SetQuantity(std::optional<size_unc> eaten_quantity);
    void SetQuantityAsDefault();
    void SetDate(int year, int month, int day);
    void SetTime(int hour, int minute=0);
    void SetDate(std::optional<std::chrono::year_month_day> date);
    void SetTime(std::optional<std::chrono::hh_mm_ss<std::chrono::minutes>> time);
    void SetProduct(Product product);

    size_unc GetProteins() const;
    size_unc GetKcalories() const;
    size_unc GetFats() const;
    size_unc GetCarbons() const;

    Product GetProduct() const;
    std::optional<std::chrono::year_month_day> GetDate() const;
    std::optional<std::chrono::hh_mm_ss< std::chrono::minutes>> GetTime() const;
    std::optional<size_unc> GetQuantity() const;
    bool operator==(const EatenProduct& other) const = default;

    friend std::ostream& operator<<(std::ostream& ostr, const EatenProduct& obj);
};

#endif // EATENPRODUCT_H
