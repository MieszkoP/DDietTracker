#ifndef ADDEATENPRODUCTWINDOW_H
#define ADDEATENPRODUCTWINDOW_H

#include <QDialog>
#include "productcategory.h"
#include "allproductsbase.h"
#include "eatenday.h"

namespace Ui {
class AddEatenProductWindow;
}

class AddEatenProductWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddEatenProductWindow(QWidget *parent = nullptr);
    ~AddEatenProductWindow();
    void SetEatenDay(std::shared_ptr<EatenDay> eatenDay);

private slots:
    void on_NameBox_activated(int index);

    void on_CategoryBox_currentIndexChanged(int index);

    void on_buttonBox_accepted();

    void on_checkBox_stateChanged(int arg1);

signals:
    void SendSignal();
private:
    bool _IsDate = true;
    Ui::AddEatenProductWindow *ui;
    std::unique_ptr<ProductCategory> _choosenCategory = std::make_unique<ProductCategory>();
    AllProductsBase* _products = nullptr;
    std::shared_ptr<EatenDay> _eatenDay = std::make_shared<EatenDay>();
};

#endif // ADDEATENPRODUCTWINDOW_H
