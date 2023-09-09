#include "chartkcaloriescreator.h"
#include "ddt.h"

ChartKcaloriesCreator::ChartKcaloriesCreator()
{
    _chart = new QChart();
    _axisX->setTickCount(10);
    _axisX->setFormat("h:m, d.M");
    _axisX->setTitleText("Date");
    _chart->addAxis(_axisX.get(), Qt::AlignBottom);

    _axisY->setLabelFormat("%i");
    _axisY->setTitleText("Sunspots count");
    _chart->addAxis(_axisY.get(), Qt::AlignLeft);
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

QChart* ChartKcaloriesCreator::createKcalChart(std::shared_ptr<EatenDay> eatenDay)
{
    _eatenDay = eatenDay;
    _chart->removeAllSeries();
    _chart->setTitle("Kcalories chart");
    QtCharts::QLineSeries *series = new QtCharts::QLineSeries();

    qint64 minX = QDateTime(QDateTime::currentDateTime()).toMSecsSinceEpoch() + 86000000;
    qint64 maxX = QDateTime(QDateTime::currentDateTime()).toMSecsSinceEpoch() - 86000000;
    float maxY = 0;
    float kcalories = 0;

    for(int i = 0; i<eatenDay->Size(); i++)
    {
        auto product = _eatenDay->ReturnEatenProduct(i);
        auto added_kcalories = product.GetKcalories().GetValue()+kcalories;
        auto uncertainty = product.GetKcalories().GetUncertainty();
        QDateTime momentInTime;
        if(product.GetDate().has_value())
        {
            auto year = int(product.GetDate().value().year());
            auto month = unsigned(product.GetDate().value().month());
            auto day = unsigned(product.GetDate().value().day());

            auto hours = product.GetTime().value().hours().count();
            auto minutes = product.GetTime().value().minutes().count();

            momentInTime.setDate(QDate(year, month, day));
            momentInTime.setTime(QTime(hours, minutes));
        }
        else
        {
            QDateTime dateTime = QDateTime::currentDateTime();
            auto year = dateTime.date().year();
            auto month = dateTime.date().month();
            auto day = dateTime.date().day();

            momentInTime.setDate(QDate(year, month, day));
            momentInTime.setTime(QTime(6, 0));
        }
        product.GetKcalories();

        series->append(momentInTime.toMSecsSinceEpoch()-5, kcalories);
        series->append(momentInTime.toMSecsSinceEpoch(),added_kcalories);

        if (minX>momentInTime.toMSecsSinceEpoch())
        {
            minX = momentInTime.toMSecsSinceEpoch();
        }

        if (maxX<momentInTime.toMSecsSinceEpoch())
        {
            maxX = momentInTime.toMSecsSinceEpoch();
        }

        if(maxY<added_kcalories)
        {
            maxY = added_kcalories;
        }

        kcalories = added_kcalories;
    }

    _chart->addSeries(series);

    _axisY->setRange(0, maxY+100);
    _axisX->setRange(QDateTime::fromMSecsSinceEpoch(minX-40000), QDateTime::fromMSecsSinceEpoch(maxX+400000));

    series->attachAxis(_axisX.get());
    series->attachAxis(_axisY.get());

    return _chart;
}
