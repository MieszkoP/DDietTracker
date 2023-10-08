#ifndef CHARTKCALORIESCREATOR_H
#define CHARTKCALORIESCREATOR_H
#include <QtCharts>
#include "eatenday.h"
#include "ddt.h"

enum macrosOrKcalories {Kcalories = 0, Proteins = 1, Fats =3, Carbons = 4};

class ChartKcaloriesCreator
{
private:
    QChart* _chart = new QChart();
    std::shared_ptr<EatenDay> _eatenDay = std::make_shared<EatenDay>();
    std::shared_ptr<QAbstractAxis> _axisX = nullptr;
    std::shared_ptr<QAbstractAxis> _axisY = nullptr;
    bool _orangePointsVisible = true;

    static std::array<std::list<qreal>, 3>CreateMacrosOrKcaloriesList(std::shared_ptr<EatenDay> eatenDay, macrosOrKcalories moc);
    static std::list<qreal> CreateTimeList(std::shared_ptr<EatenDay> eatenDay);

public:
    ChartKcaloriesCreator();
    void setOrangePointsVisible(bool isVisible);
    QChart* createKcalChart(std::shared_ptr<EatenDay> eatenDay, AxisType xAxisType, AxisType yAxisType);
};

#endif // CHARTKCALORIESCREATOR_H
