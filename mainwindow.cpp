#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtCharts>
#include "chartkcaloriescreator.h"
#include <QAbstractTableModel>
#include "allproductstable.h"
#include "addeatenproductwindow.h"
#include "addtobasewindow.h"
#include <json/json.h>
#include "apbaseserializer.h"

typedef QPair<QPointF, QString> Data;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _chartKcaloriesCreator = ChartKcaloriesCreator();

    _dayTable = new DayTable();
    _eatenDay = _dayTable->GetEatenDay();
    _dayTable->LoadEatenDay(_eatenDay);
    _dayTable->ToView(ui->tableView);
    _chartView = new QChartView(_chartKcaloriesCreator.createKcalChart(_eatenDay));
    _chartView->hide();
    ui->gridLayout_2->layout()->addWidget(_chartView);

    _allProductsTable = new AllProductsTable();
    _allProductsTable->ToView(ui->tableView_2);
    connect(ui->tableView->selectionModel(), &QItemSelectionModel::selectionChanged, [&, this](const QItemSelection &selected, const QItemSelection &deselected)
    {
        if(selected.empty())
        {
            ui->DeleteButton->setEnabled(false);
        }
        else
        {
            ui->DeleteButton->setEnabled(true);
            idSelectedInEaten = selected.indexes().at(0).row();
        }

    }
            );

    connect(ui->tableView_2->selectionModel(), &QItemSelectionModel::selectionChanged, [&, this](const QItemSelection &selected, const QItemSelection &deselected)
    {
        if(selected.empty())
        {
            ui->DeleteButton_2->setEnabled(false);
        }
        else
        {
            ui->DeleteButton_2->setEnabled(true);
            idSelectedInBase = selected.indexes().at(0).row();
        }

    }
            );

    connect(_dayTable, &AbstractTable::isUpdated, [&, this]
    {
        size_unc proteins = _dayTable->GetEatenDay()->SumProteins();
        ui->proteins_value->setText(QString::fromStdString(
            std::to_string(proteins.GetValue()) + "+/-" + std::to_string(proteins.GetUncertainty())

            ));

        size_unc kcalories = _dayTable->GetEatenDay()->SumCalories();
        ui->kcalories_value->setText(QString::fromStdString(
            std::to_string(kcalories.GetValue()) + "+/-" + std::to_string(kcalories.GetUncertainty())

            ));

        _dayTable->GetEatenDay()->SumCalories();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_2_clicked()
{
    _chartViewShowed = !_chartViewShowed;
    if(!_chartViewShowed)
    {
        _chartView->close();
        ui->pushButton_2->setText("Show Chart");
    }
    else
    {
        ui->pushButton_2->setText("Hide Chart");
        _eatenDay->SortByTime();
        _dayTable->Reload();
        _chartView->setChart((_chartKcaloriesCreator.createKcalChart(_eatenDay)));
        _chartView->show();
    }
    ui->DeleteButton->setEnabled(false);
}


void MainWindow::on_pushButton_3_released()
{
    auto eatenProductWindow = new AddEatenProductWindow(this);
    eatenProductWindow->SetEatenDay(_eatenDay);
    eatenProductWindow->show();
    auto eatenDay = _eatenDay;
    auto chartView = _chartView;

    connect(eatenProductWindow, &AddEatenProductWindow::SendSignal, [&,this, eatenDay, chartView]() {
        _dayTable->Reload();
        if(_chartViewShowed)
        {
            eatenDay->SortByTime();
            chartView->setChart((_chartKcaloriesCreator.createKcalChart(_eatenDay)));
            chartView->show();
        }
    });
    ui->DeleteButton->setEnabled(false);
}


void MainWindow::on_pushButton_5_clicked()
{
    _eatenDay->Clean();
    _dayTable->Reload();
    ui->DeleteButton->setEnabled(false);

}


void MainWindow::on_pushButton_4_released()
{
    auto addToBaseWindow = new AddToBaseWindow(this);
    addToBaseWindow->show();

    //connect(eatenProductWindow, &AddEatenProductWindow::SendSignal, _dayTable, &DayTable::Reload);
    connect(addToBaseWindow, &AddToBaseWindow::SendSignal, [&]() {
        _allProductsTable->Reload();
    });
    ui->DeleteButton_2->setEnabled(false);
}


void MainWindow::on_DeleteButton_2_pressed()
{
    auto products = AllProductsBase::GetInstance();
    auto index = ui->tableView_2->model()->index(idSelectedInBase, 1);
    std::string product = ui->tableView_2->model()->data(index).toString().toStdString();
    products->DeleteProduct(product);
    _allProductsTable->Reload();
    ui->DeleteButton_2->setEnabled(false);
}


void MainWindow::on_DeleteButton_pressed()
{

    _eatenDay->RemoveEatenProduct(idSelectedInEaten);
    if(_chartViewShowed)
    {
        _eatenDay->SortByTime();
        _chartView->setChart((_chartKcaloriesCreator.createKcalChart(_eatenDay)));
        _chartView->show();
    }
    _dayTable->Reload();
    ui->DeleteButton->setEnabled(false);
}


void MainWindow::on_SaveButton_clicked()
{
    auto products = AllProductsBase::GetInstance();
    Json::Value root;
    APBaseSerializer apbkserializer(root);
    apbkserializer.ObjectToRoot(products);
    std::ofstream file("product_base.json");
    file << root;
    file.close();
    QMessageBox::information(this, "Base of Products Updated!", "Base of Products Updated!");
}

