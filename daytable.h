#ifndef DAYTABLE_H
#define DAYTABLE_H
#include <QTableView>
#include "eatenday.h"
 #include <QStandardItemModel>
#include <QHeaderView>
#include "abstracttable.h"

#include <memory>

class DayTable : public AbstractTable
{
    std::shared_ptr<EatenDay> _eatenDay = std::make_shared<EatenDay>();
    static QList<QStandardItem*> EatenProductToRow(const EatenProduct& eatenProduct);

public:
    DayTable();
    void LoadEatenDay(std::shared_ptr<EatenDay> eatenDay);
    std::shared_ptr<EatenDay> GetEatenDay();
    void Reload();
};

#endif // DAYTABLE_H
