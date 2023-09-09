#ifndef ADDTOBASEWINDOW_H
#define ADDTOBASEWINDOW_H

#include <QDialog>
#include "allproductsbase.h"

namespace Ui {
class AddToBaseWindow;
}

class AddToBaseWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddToBaseWindow(QWidget *parent = nullptr);
    ~AddToBaseWindow();

private slots:
    void on_comboBoxCategory_currentIndexChanged(int index);

    void on_comboBox_2_activated(int index);
    void UpdateLabels();

    void on_BaseQuantityValue_valueChanged(double arg1);
    void on_buttonBox_accepted();
signals:
    void SendSignal();

private:
    AllProductsBase* _products = nullptr;
    Ui::AddToBaseWindow *ui;
    std::string _perQuantityString;
    std::string _quantityString;
    std::string _perQuantityStringKcal;
};

#endif // ADDTOBASEWINDOW_H
