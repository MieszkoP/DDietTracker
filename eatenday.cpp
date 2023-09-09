#include "eatenday.h"

EatenDay::EatenDay()
{

}

void EatenDay::AddEatenProduct(EatenProduct eatenProduct)
{
    _eatenProducts.push_back(eatenProduct);
}

void EatenDay::RemoveEatenProduct(size_t index)
{
    _eatenProducts.erase(_eatenProducts.begin()+index);
}

EatenProduct& EatenDay::ReturnEatenProduct(size_t index)
{
    *(_eatenProducts.begin()+index);
}

size_t EatenDay::Size() const
{
    _eatenProducts.size();
}

size_unc EatenDay::SumCalories()
{
    size_unc sum = 0;
    for(auto x : _eatenProducts)
    {
        sum=x.GetKcalories()+sum;
    }
    return sum;
}

size_unc EatenDay::SumProteins()
{
    size_unc sum = 0;
    for(auto x : _eatenProducts)
    {
        sum=x.GetProteins()+sum;
    }
}

bool EatenDay::CompareByTime(const EatenProduct& a, const EatenProduct& b)
{
    if(a.GetDate()<b.GetDate())
        return true;

    if(a.GetDate()>b.GetDate())
        return false;

    if(a.GetTime()->hours()<b.GetTime()->hours())
        return true;

    if(a.GetTime()->hours()>b.GetTime()->hours())
        return false;

    if(a.GetTime()->minutes()<b.GetTime()->minutes())
        return true;

    if(a.GetTime()->minutes()>b.GetTime()->minutes())
        return false;

    if(a.GetTime()->minutes()==b.GetTime()->minutes())
        return true;
    return true;
}

void EatenDay::SortByTime()
{
    //returns ​true if the first argument is less than (i.e. is ordered before) the second.
    std::sort(_eatenProducts.begin(), _eatenProducts.end(), EatenDay::CompareByTime);
}

std::ostream& operator<<(std::ostream& os, const EatenDay& other)
{
    os<<"EatenProduct with "<<other.Size()<<" elements.";
}

void EatenDay::Clean()
{
    _eatenProducts.clear();
}
