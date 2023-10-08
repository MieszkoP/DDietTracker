#include "allproductstable.h"
#include "ddt.h"

QList<QStandardItem*> AllProductsTable::ProductToRow(const Product& product)
{
    QList<QStandardItem*> list;

    AddElementToRow(list, product._productCategory._name);
    AddElementToRow(list, product._name);
    AddElementToRow(list, product._quantity);
    AddElementToRow(list, product._standard_quantity);
    AddElementToRow(list, product._proteins);
    AddElementToRow(list, product._fats);
    AddElementToRow(list, product._carbons);
    AddElementToRow(list, product._kcalories);
    AddElementToRow(list, product._quantityType);

    return list;
}


AllProductsTable::AllProductsTable() : AbstractTable()
{
    _allProducstBase = AllProductsBase::GetInstance();

    Reload();
}

void AllProductsTable::Reload()
{
    _model->clear();
    _model->setColumnCount(9);

    _model->setHorizontalHeaderItem(0, new QStandardItem("Category"));
    _model->setHorizontalHeaderItem(1, new QStandardItem("Name"));
    _model->setHorizontalHeaderItem(2, new QStandardItem("Quantity"));
    _model->setHorizontalHeaderItem(3, new QStandardItem("Standard Quantity"));
    _model->setHorizontalHeaderItem(4, new QStandardItem("Proteins [g]"));
    _model->setHorizontalHeaderItem(5, new QStandardItem("Fats [g]"));
    _model->setHorizontalHeaderItem(6, new QStandardItem("Carbons [g]"));
    _model->setHorizontalHeaderItem(7, new QStandardItem("Kcals"));
    _model->setHorizontalHeaderItem(8, new QStandardItem("Quantity Type"));
    for(auto const &[productName, product] : *(_allProducstBase->GetBase()))
    { const
        QList<QStandardItem*> row = ProductToRow(product);
        _model->appendRow(row);
    }
}

