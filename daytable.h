#ifndef DAYTABLE_H
#define DAYTABLE_H
#include <QTableView>
#include "eatenday.h"
 #include <QStandardItemModel>
#include <QHeaderView>>

#include <memory>

class DayTable
{
    QStandardItemModel* _model = nullptr;
    EatenDay* _eatenDay = nullptr;
    static QList<QStandardItem*> EatenProductToRow(const EatenProduct& eatenProduct);
    static void AddElementToRow(QList<QStandardItem*>& list, const std::optional<size_unc>& thing);
    static void AddElementToRow(QList<QStandardItem*>& list, const std::string& thing);
    static void AddElementToRow(QList<QStandardItem*>& list, const std::optional<std::chrono::year_month_day>& thing);
    static void AddElementToRow(QList<QStandardItem*>& list, const std::optional<std::chrono::hh_mm_ss< std::chrono::minutes>>& thing);
    static void AddElementToRow(QList<QStandardItem*>& list, const QuantityType& thing);

public:
    DayTable();
    void LoadEatenDay(EatenDay& eatenDay);
    void addProduct(EatenProduct& eatenProduct);
    QTableView* ToView(QTableView* table);
    void Reload();
};

#endif // DAYTABLE_H
