#include "chartkcaloriescreator.h"

ChartKcaloriesCreator::ChartKcaloriesCreator()
{

}

std::list<qreal> ChartKcaloriesCreator::CreateMacrosOrKcaloriesList(std::shared_ptr<EatenDay> eatenDay, macrosOrKcalories moc)
{
    float macroOrKcals = 0.0;
    std::list<qreal> macroOrKcalsList;
    for(int i = 0; i<eatenDay->Size(); i++)
    {
        auto product = eatenDay->ReturnEatenProduct(i);
        float added_macroOrKcals;
        switch (moc)
        {
        case macrosOrKcalories::Kcalories: added_macroOrKcals = product.GetKcalories().GetValue()+macroOrKcals;
        break;
        case macrosOrKcalories::Proteins: added_macroOrKcals = product.GetProteins().GetValue()+macroOrKcals;
        break;
        case macrosOrKcalories::Carbons: added_macroOrKcals = product.GetCarbons().GetValue()+macroOrKcals;
        break;
        case macrosOrKcalories::Fats: added_macroOrKcals = product.GetFats().GetValue()+macroOrKcals;
        break;
        }

        //auto uncertainty = product.GetKcalories().GetUncertainty(); //uncertainty in chart will be implemented in future

        macroOrKcalsList.push_back(macroOrKcals);
        macroOrKcalsList.push_back(added_macroOrKcals);

        macroOrKcals = added_macroOrKcals;
    }

    return macroOrKcalsList;
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

    switch(xAxisType)
    {

    case AxisType::Carbons: xAxis = CreateMacrosOrKcaloriesList(eatenDay, macrosOrKcalories::Carbons);
    _axisX = std::make_shared<QValueAxis>();
    std::dynamic_pointer_cast<QValueAxis>(_axisX)->setLabelFormat("%i");
    _axisX->setTitleText("Carbons");
    break;

    case AxisType::Fats: xAxis = CreateMacrosOrKcaloriesList(eatenDay, macrosOrKcalories::Fats);
    _axisX = std::make_shared<QValueAxis>();
    std::dynamic_pointer_cast<QValueAxis>(_axisX)->setLabelFormat("%i");
    _axisX->setTitleText("Fats");
    break;

    case AxisType::Proteins: xAxis = CreateMacrosOrKcaloriesList(eatenDay, macrosOrKcalories::Proteins);
    _axisX = std::make_shared<QValueAxis>();
    std::dynamic_pointer_cast<QValueAxis>(_axisX)->setLabelFormat("%i");
    _axisX->setTitleText("Proteins");
    break;

    case AxisType::Kcals: xAxis = CreateMacrosOrKcaloriesList(eatenDay, macrosOrKcalories::Kcalories);
    _axisX = std::make_shared<QValueAxis>();
    std::dynamic_pointer_cast<QValueAxis>(_axisX)->setLabelFormat("%i");
    _axisX->setTitleText("Kcalories");
    break;

    case AxisType::Time: xAxis = CreateTimeList(eatenDay);
    _axisX = std::make_shared<QDateTimeAxis>();
    std::dynamic_pointer_cast<QDateTimeAxis>(_axisX)->setFormat("hh:mm, dd.MM");
    _axisX->setTitleText("Time");
    break;

    }

    switch(yAxisType)
    {

    case AxisType::Carbons: yAxis = ChartKcaloriesCreator::CreateMacrosOrKcaloriesList(eatenDay, macrosOrKcalories::Carbons);
    _axisY = std::make_shared<QValueAxis>();
    std::dynamic_pointer_cast<QValueAxis>(_axisY)->setLabelFormat("%i");
    _axisY->setTitleText("Carbons");
    break;

    case AxisType::Fats: yAxis = ChartKcaloriesCreator::CreateMacrosOrKcaloriesList(eatenDay, macrosOrKcalories::Fats);
    _axisY = std::make_shared<QValueAxis>();
    std::dynamic_pointer_cast<QValueAxis>(_axisY)->setLabelFormat("%i");
    _axisY->setTitleText("Fats");
    break;

    case AxisType::Proteins: yAxis = ChartKcaloriesCreator::CreateMacrosOrKcaloriesList(eatenDay, macrosOrKcalories::Proteins);
    _axisY = std::make_shared<QValueAxis>();
    std::dynamic_pointer_cast<QValueAxis>(_axisY)->setLabelFormat("%i");
    _axisY->setTitleText("Proteins");
    break;

    case AxisType::Kcals: yAxis = ChartKcaloriesCreator::CreateMacrosOrKcaloriesList(eatenDay, macrosOrKcalories::Kcalories);
    _axisY = std::make_shared<QValueAxis>();
    std::dynamic_pointer_cast<QValueAxis>(_axisY)->setLabelFormat("%i");
    _axisY->setTitleText("Kcalories");
    break;

    case AxisType::Time: yAxis = ChartKcaloriesCreator::CreateTimeList(eatenDay);
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

    qreal endX;
    qreal endY;
    for(auto xPoint = xAxis.begin(), yPoint=yAxis.begin(); xPoint!=xAxis.end(); xPoint++, yPoint++)
    {
        series->append(*xPoint, *yPoint);
    }

    _chart->addSeries(series);

    if(xAxisType == AxisType::Time)
    {
        _axisX->setRange(QDateTime::fromMSecsSinceEpoch(xAxis.front()-40000), QDateTime::fromMSecsSinceEpoch(xAxis.back()+40000));
    }
    else
    {
        _axisX->setRange(xAxis.front()-3, xAxis.back()+3);
    }

    if(yAxisType == AxisType::Time)
    {
        _axisY->setRange(QDateTime::fromMSecsSinceEpoch(yAxis.front()-40000), QDateTime::fromMSecsSinceEpoch(yAxis.back()+40000));
    }
    else
    {
        _axisY->setRange(yAxis.front()-3, yAxis.back()+3);
    }

    series->attachAxis(_axisX.get());
    series->attachAxis(_axisY.get());

    _chart->legend()->setVisible(false);

    return _chart;
}
