#include "abstracttable.h"
#include "ddt.h"
#include <QHeaderView>

AbstractTable::AbstractTable() : _model(new QStandardItemModel()) {}

void AbstractTable::AddElementToRow(QList<QStandardItem*>& list, const std::optional<size_unc>& size_uncElement)
{
    QString size_uncString;
    if(size_uncElement.has_value())
        size_uncString = QString::number(size_uncElement.value().GetValue())+" +/- "+QString::number(size_uncElement.value().GetUncertainty());
    else
        size_uncString = QString("No value");

    list.push_back(new QStandardItem(size_uncString));
}

void AbstractTable::AddElementToRow(QList<QStandardItem*>& list, const std::string& stringElement)
{
    QString QtstringString;
    QtstringString = QString::fromStdString(stringElement);
    list.push_back(new QStandardItem(QtstringString));
}

void AbstractTable::AddElementToRow(QList<QStandardItem*>& list, const std::optional<std::chrono::year_month_day>& dateElement)
{
    QString dateString;
    dateString = QString::fromStdString(DDT::DateOptionAsString(dateElement));
    list.push_back(new QStandardItem(dateString));
}

void AbstractTable::AddElementToRow(QList<QStandardItem*>& list, const std::optional<std::chrono::hh_mm_ss< std::chrono::minutes>>& timeElement)
{
    QString timeString;
    timeString = QString::fromStdString(DDT::TimeOptionAsString(timeElement));
    list.push_back(new QStandardItem(timeString));
}

void AbstractTable::AddElementToRow(QList<QStandardItem*>& list, const QuantityType& quantityElement)
{
    QString quantityString;
    if(quantityElement == QuantityType::mass)
    {
        quantityString = "Mass";
    }
    else
    {
        quantityString = "Volume";
    }
    list.push_back(new QStandardItem(quantityString));
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
