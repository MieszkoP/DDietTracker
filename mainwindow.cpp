#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtCharts>
#include "chartkcaloriescreator.h"
#include <QAbstractTableModel>
#include "daytable.h"

typedef QPair<QPointF, QString> Data;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto chartKcaloriesCreator = ChartKcaloriesCreator();
    _chartView = new QChartView(chartKcaloriesCreator.createExempleAreaChart());
    ui->gridLayout_2->layout()->addWidget(_chartView);

    auto* dayTable = new DayTable();
    dayTable->ToView(ui->tableView);

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_2_clicked()
{
    if(!_chartViewShowed)
    {
        _chartView->close();
        ui->pushButton_2->setText("Show Chart");
    }
    else
    {
        _chartView->show();
        ui->pushButton_2->setText("Hide Chart");
    }
    _chartViewShowed = !_chartViewShowed;
}

