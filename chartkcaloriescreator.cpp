#include "chartkcaloriescreator.h"

ChartKcaloriesCreator::ChartKcaloriesCreator()
{
    _chart = new QChart();
}

QChart* ChartKcaloriesCreator::createExempleAreaChart()
{
    _chart->setTitle("Area chart");

    // The lower series initialized to zero values
    QLineSeries *lowerSeries = 0;
    QString name("Series ");
    int nameIndex = 0;
    _chart->setAnimationDuration(2000);
    QtCharts::QLineSeries *series = new QtCharts::QLineSeries();
    for (double x = 0; x <= 2 * M_PI; x += 0.1) {
        double y = sin(x);
        series->append(x, y);
    }

    _chart->addSeries(series);
    return _chart;
}
