#include "daytable.h"

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

DayTable::DayTable() : AbstractTable()
{
    _model = new QStandardItemModel();

    Reload();

}

void DayTable::LoadEatenDay(std::shared_ptr<EatenDay> eatenDay)
{
    _eatenDay = eatenDay;
}

void DayTable::Reload()
{
    _model->clear();

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

    for(int i = 0; i<(*_eatenDay).Size(); i++)
    {
        QList<QStandardItem*> row = EatenProductToRow(_eatenDay->ReturnEatenProduct(i));
        _model->appendRow(row);
    }
    isUpdated();
}

std::shared_ptr<EatenDay> DayTable::GetEatenDay()
{
    return _eatenDay;
}
