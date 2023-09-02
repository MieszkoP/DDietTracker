#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtCharts>
typedef QPair<QPointF, QString> Data;

QChart* createAreaChart()
{
    QChart *chart = new QChart();
    chart->setTitle("Area chart");

    // The lower series initialized to zero values
    QLineSeries *lowerSeries = 0;
    QString name("Series ");
    int nameIndex = 0;
    chart->setAnimationDuration(2000);
    QtCharts::QLineSeries *series = new QtCharts::QLineSeries();
    for (double x = 0; x <= 2 * M_PI; x += 0.1) {
        double y = sin(x);
        series->append(x, y);
    }

    QLinearGradient backgroundGradient;
    backgroundGradient.setStart(QPointF(0, 0));
    backgroundGradient.setFinalStop(QPointF(0, 1));
    backgroundGradient.setColorAt(0.0, QRgb(0xd2d0d1));
    backgroundGradient.setColorAt(1.0, QColor("red"));
    backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    chart->setBackgroundBrush(backgroundGradient);
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::AllAnimations);
    return chart;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QChartView *chartView;
    QStandardItemModel *model = new QStandardItemModel(4,4);
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int column = 0; column < model->columnCount(); ++column) {
            QStandardItem *item = new QStandardItem(QString("row %0, column %1").arg(row).arg(column));
            model->setItem(row, column, item);
        }
    }

    chartView = new QChartView(createAreaChart());
    ui->centralwidget->layout()->addWidget(chartView);
    ui->tableView->setModel(model);
    ui->tableView->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}



