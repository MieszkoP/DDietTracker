#ifndef CHARTKCALORIESCREATOR_H
#define CHARTKCALORIESCREATOR_H
#include <QtCharts>
#include "eatenday.h"

class ChartKcaloriesCreator
{
private:
    QChart* _chart = new QChart();
    std::shared_ptr<EatenDay> _eatenDay = std::make_shared<EatenDay>();
    std::shared_ptr<QDateTimeAxis> _axisX = std::make_shared<QDateTimeAxis>();
    std::shared_ptr<QValueAxis> _axisY = std::make_shared<QValueAxis>();

public:
    ChartKcaloriesCreator();
    QChart* createExempleAreaChart();
    QChart* createKcalChart(std::shared_ptr<EatenDay> eatenDay);

};

#endif // CHARTKCALORIESCREATOR_H
