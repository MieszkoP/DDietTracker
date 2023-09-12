#include "abstracttable.h"
#include "ddt.h"
#include <QHeaderView>

AbstractTable::AbstractTable()
{
    _model = new QStandardItemModel();
}

void AbstractTable::AddElementToRow(QList<QStandardItem*>& list, const std::optional<size_unc>& thing)
{
    QString string;
    if(thing.has_value())
        string = QString::number(thing.value().GetValue())+" +/- "+QString::number(thing.value().GetUncertainty());
    else
        string = QString("No value");

    list.push_back(new QStandardItem(string));
}

void AbstractTable::AddElementToRow(QList<QStandardItem*>& list, const std::string& thing)
{
    QString string;
    string = QString::fromStdString(thing);
    list.push_back(new QStandardItem(string));
}

void AbstractTable::AddElementToRow(QList<QStandardItem*>& list, const std::optional<std::chrono::year_month_day>& thing)
{
    QString string;
    string = QString::fromStdString(DDT::DateOptionAsString(thing));
    list.push_back(new QStandardItem(string));
}

void AbstractTable::AddElementToRow(QList<QStandardItem*>& list, const std::optional<std::chrono::hh_mm_ss< std::chrono::minutes>>& thing)
{
    QString string;
    string = QString::fromStdString(DDT::TimeOptionAsString(thing));
    list.push_back(new QStandardItem(string));
}

void AbstractTable::AddElementToRow(QList<QStandardItem*>& list, const QuantityType& thing)
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

QTableView* AbstractTable::ToView(QTableView* tableView)
{
    tableView->setModel(_model);

    tableView->resizeColumnsToContents();
    tableView->horizontalHeader()->setStretchLastSection(true);

    return tableView;
}

AbstractTable::~AbstractTable()
{
    delete _model;
}
