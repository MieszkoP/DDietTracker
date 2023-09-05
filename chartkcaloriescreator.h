#ifndef CHARTKCALORIESCREATOR_H
#define CHARTKCALORIESCREATOR_H
#include <QtCharts>

class ChartKcaloriesCreator
{
private:
    QChart* _chart = nullptr;
public:
    ChartKcaloriesCreator();
    QChart* createExempleAreaChart();

};

#endif // CHARTKCALORIESCREATOR_H
