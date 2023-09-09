#ifndef ALLPRODUCTSTABLE_H
#define ALLPRODUCTSTABLE_H
#include "abstracttable.h"
#include "allproductsbase.h"

class AllProductsTable : public AbstractTable
{
    AllProductsBase* _allProducstBase = nullptr;
    static QList<QStandardItem*> ProductToRow(const Product& Product);
public:
    AllProductsTable();
    void Reload();
    ~AllProductsTable();
};

#endif // ALLPRODUCTSTABLE_H
