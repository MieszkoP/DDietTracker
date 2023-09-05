#include "daytable.h"
#include "ddt.h"

void DayTable::AddElementToRow(QList<QStandardItem*>& list, const std::optional<size_unc>& thing)
{
    QString string;
    if(thing.has_value())
        string = QString::number(thing.value().GetValue())+" +/- "+QString::number(thing.value().GetUncertainty());
    else
        string = QString("No value");

    list.push_back(new QStandardItem(string));
}

void DayTable::AddElementToRow(QList<QStandardItem*>& list, const std::string& thing)
{
    QString string;
    string = QString::fromStdString(thing);
    list.push_back(new QStandardItem(string));
}

void DayTable::AddElementToRow(QList<QStandardItem*>& list, const std::optional<std::chrono::year_month_day>& thing)
{
    QString string;
    string = QString::fromStdString(DDT::DateOptionAsString(thing));
    list.push_back(new QStandardItem(string));
}

void DayTable::AddElementToRow(QList<QStandardItem*>& list, const std::optional<std::chrono::hh_mm_ss< std::chrono::minutes>>& thing)
{
    QString string;
    string = QString::fromStdString(DDT::TimeOptionAsString(thing));
    list.push_back(new QStandardItem(string));
}

void DayTable::AddElementToRow(QList<QStandardItem*>& list, const QuantityType& thing)
{
    QString string;
    if(thing == QuantityType::mass)
    {
        string = "Mass";
    }
    else
    {
        string = "Volume";
    }
    list.push_back(new QStandardItem(string));
}

QList<QStandardItem*> DayTable::EatenProductToRow(const EatenProduct& eatenProduct)
{
    QList<QStandardItem*> list;

    AddElementToRow(list, eatenProduct.GetProduct()._productCategory._name);
    AddElementToRow(list, eatenProduct.GetProduct()._name);
    AddElementToRow(list, eatenProduct.GetQuantity());
    AddElementToRow(list, eatenProduct.GetKcalories());
    AddElementToRow(list, eatenProduct.GetProteins());
    AddElementToRow(list, eatenProduct.GetFats());
    AddElementToRow(list, eatenProduct.GetCarbons());
    AddElementToRow(list, eatenProduct.GetDate());
    AddElementToRow(list, eatenProduct.GetTime());
    AddElementToRow(list, eatenProduct.GetProduct()._quantityType);

    return list;
}

DayTable::DayTable()
{
    _model = new QStandardItemModel();
    _eatenDay = new EatenDay();
    _model->setColumnCount(10);
    _model->setHorizontalHeaderItem(0, new QStandardItem("Category"));
    _model->setHorizontalHeaderItem(1, new QStandardItem("Name"));
    _model->setHorizontalHeaderItem(2, new QStandardItem("Quantity"));
    _model->setHorizontalHeaderItem(3, new QStandardItem("Kcals"));
    _model->setHorizontalHeaderItem(4, new QStandardItem("Proteins"));
    _model->setHorizontalHeaderItem(5, new QStandardItem("Fats"));
    _model->setHorizontalHeaderItem(6, new QStandardItem("Carbons"));
    _model->setHorizontalHeaderItem(7, new QStandardItem("Day"));
    _model->setHorizontalHeaderItem(8, new QStandardItem("Time"));
    _model->setHorizontalHeaderItem(9, new QStandardItem("Type"));

    //FOR TEST
    EatenDay day;
    (*_eatenDay) =  day;
    Product product1("Marmolada");

    product1._kcalories={500.09000008, 20};
    product1._proteins={5300, 20};
    product1._fats={9, 2};
    product1._carbons={9, 2};

    EatenProduct eaten1 = EatenProduct(product1, 400);

    _eatenDay->AddEatenProduct(eaten1);
    _eatenDay->AddEatenProduct(eaten1);
    _eatenDay->AddEatenProduct(eaten1);

    Reload();

}

void DayTable::LoadEatenDay(EatenDay& eatenDay)
{
    (*_eatenDay) = eatenDay;
}

void DayTable::Reload()
{
    for(int i = 0; i<(*_eatenDay).Size(); i++)
    {
        QList<QStandardItem*> row = EatenProductToRow(_eatenDay->ReturnEatenProduct(i));
        _model->appendRow(row);
    }
}

void DayTable::addProduct(EatenProduct& eatenProduct)
{
    _eatenDay->AddEatenProduct(eatenProduct);
}

QTableView* DayTable::ToView(QTableView* tableView)
{
    tableView->setModel(_model);

    tableView->resizeColumnsToContents();
    tableView->horizontalHeader()->setStretchLastSection(true);

    return tableView;
}
