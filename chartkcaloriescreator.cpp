#include "chartkcaloriescreator.h"

ChartKcaloriesCreator::ChartKcaloriesCreator()
{

}

void ChartKcaloriesCreator::setOrangePointsVisible(bool isVisible)
{
    _orangePointsVisible = isVisible;
}

std::array<std::list<qreal>, 3> ChartKcaloriesCreator::CreateMacrosOrKcaloriesList(std::shared_ptr<EatenDay> eatenDay, macrosOrKcalories moc)
{
    float macroOrKcals = 0.0;
    float macroOrKcalsMin = 0.0;
    float macroOrKcalsMax = 0.0;

    std::list<qreal> macroOrKcalsList;
    std::list<qreal> macroOrKcalsListMin;
    std::list<qreal> macroOrKcalsListMax;

    for(int i = 0; i<eatenDay->Size(); i++)
    {
        auto product = eatenDay->ReturnEatenProduct(i);
        float added_macroOrKcals;
        float added_macroOrKcalsMin;
        float added_macroOrKcalsMax;

        switch (moc)
        {
        case macrosOrKcalories::Kcalories:
        added_macroOrKcals = product.GetKcalories().GetValue()+macroOrKcals;
        added_macroOrKcalsMin = product.GetKcalories().GetLowerBound()+macroOrKcalsMin;
        added_macroOrKcalsMax = product.GetKcalories().GetUpperBound()+macroOrKcalsMax;

        break;
        case macrosOrKcalories::Proteins:
        added_macroOrKcals = product.GetProteins().GetValue()+macroOrKcals;
        added_macroOrKcalsMin = product.GetProteins().GetLowerBound()+macroOrKcalsMin;
        added_macroOrKcalsMax = product.GetProteins().GetUpperBound()+macroOrKcalsMax;

        break;
        case macrosOrKcalories::Carbons:
        added_macroOrKcals = product.GetCarbons().GetValue()+macroOrKcals;
        added_macroOrKcalsMin = product.GetCarbons().GetLowerBound()+macroOrKcalsMin;
        added_macroOrKcalsMax = product.GetCarbons().GetUpperBound()+macroOrKcalsMax;

        break;
        case macrosOrKcalories::Fats:
        added_macroOrKcals = product.GetFats().GetValue()+macroOrKcals;
        added_macroOrKcalsMin = product.GetFats().GetLowerBound()+macroOrKcalsMin;
        added_macroOrKcalsMax = product.GetFats().GetUpperBound()+macroOrKcalsMax;

        break;
        }

        //auto uncertainty = product.GetKcalories().GetUncertainty(); //uncertainty in chart will be implemented in future

        macroOrKcalsList.push_back(macroOrKcals);
        macroOrKcalsList.push_back(added_macroOrKcals);

        macroOrKcalsListMin.push_back(macroOrKcalsMin);
        macroOrKcalsListMin.push_back(added_macroOrKcalsMin);

        macroOrKcalsListMax.push_back(macroOrKcalsMax);
        macroOrKcalsListMax.push_back(added_macroOrKcalsMax);

        macroOrKcals = added_macroOrKcals;
        macroOrKcalsMin = added_macroOrKcalsMin;
        macroOrKcalsMax = added_macroOrKcalsMax;
    }

    return {macroOrKcalsList, macroOrKcalsListMin, macroOrKcalsListMax};
}

std::list<qreal> ChartKcaloriesCreator::CreateTimeList(std::shared_ptr<EatenDay> eatenDay)
{
    std::list<qreal> timeList;
    for(int i = 0; i<eatenDay->Size(); i++)
    {
        auto product = eatenDay->ReturnEatenProduct(i);
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
        timeList.push_back(momentInTime.toMSecsSinceEpoch());
        timeList.push_back(momentInTime.toMSecsSinceEpoch());
    }
    return timeList;
}

QChart* ChartKcaloriesCreator::createKcalChart(std::shared_ptr<EatenDay> eatenDay, AxisType xAxisType, AxisType yAxisType)
{

    std::list<qreal> xAxis;
    std::list<qreal> yAxis;
    std::list<qreal> yAxisMin;
    std::list<qreal> yAxisMax;

    switch(xAxisType)
    {

    case AxisType::Carbons:
    xAxis = CreateMacrosOrKcaloriesList(eatenDay, macrosOrKcalories::Carbons).at(0);
    _axisX = std::make_shared<QValueAxis>();
    std::dynamic_pointer_cast<QValueAxis>(_axisX)->setLabelFormat("%i");
    _axisX->setTitleText("Carbons [g]");
    break;

    case AxisType::Fats:
    xAxis = CreateMacrosOrKcaloriesList(eatenDay, macrosOrKcalories::Fats).at(0);
    _axisX = std::make_shared<QValueAxis>();
    std::dynamic_pointer_cast<QValueAxis>(_axisX)->setLabelFormat("%i");
    _axisX->setTitleText("Fats [g]");
    break;

    case AxisType::Proteins:
    xAxis = CreateMacrosOrKcaloriesList(eatenDay, macrosOrKcalories::Proteins).at(0);
    _axisX = std::make_shared<QValueAxis>();
    std::dynamic_pointer_cast<QValueAxis>(_axisX)->setLabelFormat("%i");
    _axisX->setTitleText("Proteins [g]");
    break;

    case AxisType::Kcals:
    xAxis = CreateMacrosOrKcaloriesList(eatenDay, macrosOrKcalories::Kcalories).at(0);
    _axisX = std::make_shared<QValueAxis>();
    std::dynamic_pointer_cast<QValueAxis>(_axisX)->setLabelFormat("%i");
    _axisX->setTitleText("Kcalories");
    break;

    case AxisType::Time:
    xAxis = CreateTimeList(eatenDay);
    _axisX = std::make_shared<QDateTimeAxis>();
    std::dynamic_pointer_cast<QDateTimeAxis>(_axisX)->setFormat("hh:mm, dd.MM");
    _axisX->setTitleText("Time");
    break;

    }

    switch(yAxisType)
    {

    case AxisType::Carbons:
    yAxis = ChartKcaloriesCreator::CreateMacrosOrKcaloriesList(eatenDay, macrosOrKcalories::Carbons).at(0);
    yAxisMin = ChartKcaloriesCreator::CreateMacrosOrKcaloriesList(eatenDay, macrosOrKcalories::Carbons).at(1);
    yAxisMax = ChartKcaloriesCreator::CreateMacrosOrKcaloriesList(eatenDay, macrosOrKcalories::Carbons).at(2);

    _axisY = std::make_shared<QValueAxis>();
    std::dynamic_pointer_cast<QValueAxis>(_axisY)->setLabelFormat("%i");
    _axisY->setTitleText("Carbons [g]");
    break;

    case AxisType::Fats:
    yAxis = ChartKcaloriesCreator::CreateMacrosOrKcaloriesList(eatenDay, macrosOrKcalories::Fats).at(0);
    yAxisMin = ChartKcaloriesCreator::CreateMacrosOrKcaloriesList(eatenDay, macrosOrKcalories::Fats).at(1);
    yAxisMax = ChartKcaloriesCreator::CreateMacrosOrKcaloriesList(eatenDay, macrosOrKcalories::Fats).at(2);

    _axisY = std::make_shared<QValueAxis>();
    std::dynamic_pointer_cast<QValueAxis>(_axisY)->setLabelFormat("%i");
    _axisY->setTitleText("Fats [g]");
    break;

    case AxisType::Proteins:
    yAxis = ChartKcaloriesCreator::CreateMacrosOrKcaloriesList(eatenDay, macrosOrKcalories::Proteins).at(0);
    yAxisMin = ChartKcaloriesCreator::CreateMacrosOrKcaloriesList(eatenDay, macrosOrKcalories::Proteins).at(1);
    yAxisMax = ChartKcaloriesCreator::CreateMacrosOrKcaloriesList(eatenDay, macrosOrKcalories::Proteins).at(2);

    _axisY = std::make_shared<QValueAxis>();
    std::dynamic_pointer_cast<QValueAxis>(_axisY)->setLabelFormat("%i");
    _axisY->setTitleText("Proteins [g]");
    break;

    case AxisType::Kcals:
    yAxis = ChartKcaloriesCreator::CreateMacrosOrKcaloriesList(eatenDay, macrosOrKcalories::Kcalories).at(0);
    yAxisMin = ChartKcaloriesCreator::CreateMacrosOrKcaloriesList(eatenDay, macrosOrKcalories::Kcalories).at(1);
    yAxisMax = ChartKcaloriesCreator::CreateMacrosOrKcaloriesList(eatenDay, macrosOrKcalories::Kcalories).at(2);

    _axisY = std::make_shared<QValueAxis>();
    std::dynamic_pointer_cast<QValueAxis>(_axisY)->setLabelFormat("%i");
    _axisY->setTitleText("Kcalories");
    break;

    case AxisType::Time:
    yAxis = ChartKcaloriesCreator::CreateTimeList(eatenDay);
    _axisY = std::make_shared<QDateTimeAxis>();
    std::dynamic_pointer_cast<QDateTimeAxis>(_axisY)->setFormat("hh:mm, dd.MM");
    _axisY->setTitleText("Time");
    break;

    }

    _chart->addAxis(_axisX.get(), Qt::AlignBottom);
    _chart->addAxis(_axisY.get(), Qt::AlignLeft);


    //x vs y wykres
    _eatenDay = eatenDay;
    _chart->removeAllSeries();
    auto *series = new QtCharts::QLineSeries();
    auto *points = new QtCharts::QScatterSeries();
    auto *lowerSeries = new QtCharts::QLineSeries();
    auto *upperSeries = new QtCharts::QLineSeries();

    for(auto xPoint = xAxis.begin(), yPoint=yAxis.begin(); xPoint!=xAxis.end(); xPoint++, yPoint++)
    {
        series->append(*xPoint, *yPoint);
        if(_orangePointsVisible)
            points->append(*xPoint, *yPoint);
    }

    for(auto xPoint = xAxis.begin(), yPointMin=yAxisMin.begin(), yPointMax=yAxisMax.begin(); xPoint!=xAxis.end(); xPoint++, yPointMin++, yPointMax++)
    {
        lowerSeries->append(*xPoint, *yPointMin);
        upperSeries->append(*xPoint, *yPointMax);
    }

    if(xAxisType == AxisType::Time)
    {
        lowerSeries->append(xAxis.back()+600000, yAxisMin.back());
        upperSeries->append(xAxis.back()+600000, yAxisMax.back());
    }
    else
    {
        lowerSeries->append(xAxis.back()+1, yAxisMin.back());
        upperSeries->append(xAxis.back()+1, yAxisMax.back());
    }

    QAreaSeries *area = new QAreaSeries(upperSeries, lowerSeries);
    _chart->addSeries(area);
    _chart->addSeries(series);
    _chart->addSeries(points);

    if(xAxisType == AxisType::Time)
    {
        _axisX->setRange(QDateTime::fromMSecsSinceEpoch(xAxis.front()-40000), QDateTime::fromMSecsSinceEpoch(xAxis.back()+1000000));
    }
    else
    {
        _axisX->setRange(0, xAxis.back()+10);
    }

    if(yAxisType == AxisType::Time)
    {
        _axisY->setRange(QDateTime::fromMSecsSinceEpoch(yAxis.front()-40000), QDateTime::fromMSecsSinceEpoch(yAxis.back()+1000000));
    }
    else
    {
        _axisY->setRange(0, yAxisMax.back()+10);
    }

    series->attachAxis(_axisX.get());
    series->attachAxis(_axisY.get());

    points->attachAxis(_axisX.get());
    points->attachAxis(_axisY.get());

    area->attachAxis(_axisX.get());
    area->attachAxis(_axisY.get());

    _chart->legend()->setVisible(false);

    return _chart;
}
