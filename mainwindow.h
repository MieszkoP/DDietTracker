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
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() final;

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
    DayTable* _dayTable = new DayTable();
    AllProductsTable* _allProductsTable = nullptr;
    std::shared_ptr<EatenDay> _eatenDay = std::make_shared<EatenDay>();
    QChartView *_chartView = nullptr;
    bool _chartViewShowed = false;
    ChartKcaloriesCreator _chartKcaloriesCreator = ChartKcaloriesCreator();
    size_t idSelectedInBase = -1;
    size_t idSelectedInEaten = -1;

    QComboBox* _setXAxis = nullptr;
    QComboBox* _setYAxis = nullptr;
    QHBoxLayout* _chartParametersLayout = nullptr;
    QLabel* _labelAxisX = nullptr;
    QLabel* _labelAxisY = nullptr;
    void showChart(bool show);
    AxisType _axisXType = AxisType::Time;
    AxisType _axisYType = AxisType::Kcals;

};
#endif // MAINWINDOW_H
