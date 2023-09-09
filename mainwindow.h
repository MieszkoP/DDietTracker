#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include "daytable.h"
#include "allproductstable.h"
#include "chartkcaloriescreator.h"
#include <QMessageBox>
#include "ddt.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_released();

    void on_pushButton_5_clicked();

    void on_pushButton_4_released();

    void on_DeleteButton_2_pressed();

    void on_DeleteButton_pressed();

    void on_SaveButton_clicked();

private:
    Ui::MainWindow *ui;
    DayTable* _dayTable = nullptr;
    AllProductsTable* _allProductsTable = nullptr;
    std::shared_ptr<EatenDay> _eatenDay = std::make_shared<EatenDay>();
    QChartView *_chartView = nullptr;
    bool _chartViewShowed = false;
    ChartKcaloriesCreator _chartKcaloriesCreator;
    size_t idSelectedInBase = -1;
    size_t idSelectedInEaten = -1;
};
#endif // MAINWINDOW_H
