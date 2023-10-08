#ifndef ABSTRACTTABLE_H
#define ABSTRACTTABLE_H
#include <QStandardItemModel>
#include <QTableView>
#include "eatenday.h"

class AbstractTable : public QObject
{
    Q_OBJECT
protected:
    QStandardItemModel* _model = nullptr; //Will be encapsulated in the future
    static QList<QStandardItem*> EatenProductToRow(const EatenProduct& eatenProduct);
    static void AddElementToRow(QList<QStandardItem*>& list, const std::optional<size_unc>& size_uncElement);
    static void AddElementToRow(QList<QStandardItem*>& list, const std::string& stringElement);
    static void AddElementToRow(QList<QStandardItem*>& list, const std::optional<std::chrono::year_month_day>& dateElement);
    static void AddElementToRow(QList<QStandardItem*>& list, const std::optional<std::chrono::hh_mm_ss< std::chrono::minutes>>& timeElement);
    static void AddElementToRow(QList<QStandardItem*>& list, const QuantityType& quantityElement);
signals:
    void isUpdated();

public:
    AbstractTable();
    QTableView* ToView(QTableView* table);
    ~AbstractTable() override;

};

#endif // ABSTRACTTABLE_H
