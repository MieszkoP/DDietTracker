#ifndef EATENDAY_H
#define EATENDAY_H
#include "eatenproduct.h"
#include <vector>

class EatenDay
{
    std::vector<EatenProduct> _eatenProducts;
    static bool CompareByTime(const EatenProduct& a, const EatenProduct& b);
public:
    EatenDay() = default;
    size_t Size() const;
    void AddEatenProduct(const EatenProduct& eatenProduct);
    void RemoveEatenProduct(size_t index);
    EatenProduct& ReturnEatenProduct(size_t index);

    size_unc SumCalories() const;
    size_unc SumProteins() const;
    void Clean();

    //size_unc SumCaloriesBefore();
    //size_unc SumProteinsBefore(); //Wil be implemented in future

    void SortByTime();
    bool operator==(const EatenDay& other) const = default;
    friend std::ostream& operator<<(std::ostream& os, const EatenDay& other);
};

#endif // EATENDAY_H
