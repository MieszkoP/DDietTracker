#ifndef ABSTRACTTABLE_H
#define ABSTRACTTABLE_H
#include <QStandardItemModel>
#include <QTableView>
#include "eatenday.h"

class AbstractTable : public QObject
{
    Q_OBJECT
protected:
    QStandardItemModel* _model = nullptr;
    static QList<QStandardItem*> EatenProductToRow(const EatenProduct& eatenProduct);
    static void AddElementToRow(QList<QStandardItem*>& list, const std::optional<size_unc>& thing);
    static void AddElementToRow(QList<QStandardItem*>& list, const std::string& thing);
    static void AddElementToRow(QList<QStandardItem*>& list, const std::optional<std::chrono::year_month_day>& thing);
    static void AddElementToRow(QList<QStandardItem*>& list, const std::optional<std::chrono::hh_mm_ss< std::chrono::minutes>>& thing);
    static void AddElementToRow(QList<QStandardItem*>& list, const QuantityType& thing);

public:
    AbstractTable();
    QTableView* ToView(QTableView* table);
};

#endif // ABSTRACTTABLE_H