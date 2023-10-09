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
#include "eatendayserializer.h"
#include "eatendaydeserializer.h"
#include <filesystem>


using Data = QPair<QPointF, QString>;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _eatenDay = _dayTable->GetEatenDay();
    _dayTable->LoadEatenDay(_eatenDay);
    _dayTable->ToView(ui->tableView);
    _chartView = new QChartView(_chartKcaloriesCreator.createKcalChart(_eatenDay, _axisXType, _axisYType));
    _chartView->setRubberBand(QChartView::RectangleRubberBand);
    ui->gridLayout_2->layout()->addWidget(_chartView);
    _setXAxis = new QComboBox(this);
    _setYAxis = new QComboBox(this);
    _setOrangePointsVisible = new QComboBox(this);

    _setXAxis->addItems({"Time", "Proteins", "Carbons", "Fats", "Kcals"});
    _setYAxis->addItems({"Time", "Proteins", "Carbons", "Fats", "Kcals"});
    _setOrangePointsVisible->addItems({"Hidden", "Visible"});

    _setXAxis->setCurrentIndex(0);
    _setYAxis->setCurrentIndex(4);
    _setOrangePointsVisible->setCurrentIndex(1);

    _chartParametersLayout = new QHBoxLayout();
    ui->gridLayout_2->addLayout(_chartParametersLayout, 2, 0);
    _labelAxisX = new QLabel(this);
    _labelAxisY = new QLabel(this);
    _labelPointsVisible = new QLabel(this);

    _labelAxisX->setText("X axis: ");
    _labelAxisY->setText("Y axis: ");
    _labelPointsVisible->setText("Orange points: ");
    _chartParametersLayout->addItem(new QSpacerItem(4000, 0, QSizePolicy::Maximum, QSizePolicy::Maximum));
    _chartParametersLayout->addWidget(_labelPointsVisible);
    _chartParametersLayout->addWidget(_setOrangePointsVisible);
    _chartParametersLayout->addWidget(_labelAxisX);
    _chartParametersLayout->addWidget(_setXAxis);
    _chartParametersLayout->addWidget(_labelAxisY);
    _chartParametersLayout->addWidget(_setYAxis);

    showChart(false);

    connect(this->_setXAxis, QOverload<int>::of(&QComboBox::currentIndexChanged), [this](int index)
    {
        _axisXType = static_cast<AxisType>(index);
        _chartView->setChart(_chartKcaloriesCreator.createKcalChart(_eatenDay, _axisXType, _axisYType));
        _chartView->show();
    });

    connect(this->_setYAxis, QOverload<int>::of(&QComboBox::currentIndexChanged), [this](int index)
    {
        _axisYType = static_cast<AxisType>(index);
        _chartView->setChart(_chartKcaloriesCreator.createKcalChart(_eatenDay, _axisXType, _axisYType));
        _chartView->show();
    });

    connect(this->_setOrangePointsVisible, QOverload<int>::of(&QComboBox::currentIndexChanged), [this](int index)
            {
                _pointsVisible = static_cast<bool>(index);
                _chartKcaloriesCreator.setOrangePointsVisible(_pointsVisible);
                _chartView->setChart(_chartKcaloriesCreator.createKcalChart(_eatenDay, _axisXType, _axisYType));
                _chartView->show();
            });

    _allProductsTable = new AllProductsTable();
    _allProductsTable->ToView(ui->tableView_2);
    connect(ui->tableView->selectionModel(), &QItemSelectionModel::selectionChanged, [this] (const QItemSelection &selected,  [[maybe_unused]] const QItemSelection &deselected)
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

    connect(ui->tableView_2->selectionModel(), &QItemSelectionModel::selectionChanged, [this] (const QItemSelection &selected, [[maybe_unused]] const QItemSelection &deselected)
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

    connect(_dayTable, &AbstractTable::isUpdated, [this]
    {
        size_unc proteins = _dayTable->GetEatenDay()->SumProteins();
        ui->proteins_value->setText(QString::fromStdString(
            std::to_string(proteins.GetValue()) + "+/-" + std::to_string(proteins.GetUncertainty())

            ));

        size_unc kcalories = _dayTable->GetEatenDay()->SumCalories();
        ui->kcalories_value->setText(QString::fromStdString(
            std::to_string(kcalories.GetValue()) + "+/-" + std::to_string(kcalories.GetUncertainty())

            ));

        if(_chartViewShowed)
        {
            _eatenDay->SortByTime();
            _chartView->setChart(_chartKcaloriesCreator.createKcalChart(_eatenDay, _axisXType, _axisYType));
            _chartView->show();
        }
    });

}

MainWindow::~MainWindow()
{
    delete ui;
    delete _dayTable;
    delete _allProductsTable;
}



void MainWindow::on_pushButton_2_clicked()
{
    _chartViewShowed = !_chartViewShowed;
    if(!_chartViewShowed)
    {
        ui->pushButton_2->setText("Show Chart");
        showChart(false);
    }
    else
    {
        ui->pushButton_2->setText("Hide Chart");
        _eatenDay->SortByTime();
        _dayTable->Reload();
        _chartView->setChart(_chartKcaloriesCreator.createKcalChart(_eatenDay, _axisXType, _axisYType));
        showChart(true);
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

    connect(eatenProductWindow, &AddEatenProductWindow::SendSignal, [this, eatenDay, chartView]() {
        _dayTable->Reload();
    });
    ui->DeleteButton->setEnabled(false);
}

//Show chart button
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

    connect(addToBaseWindow, &AddToBaseWindow::SendSignal, [this]() {
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

void MainWindow::showChart(bool show)
{
    if(show)
    {
        _chartView->show();
        _setXAxis->show();
        _setYAxis->show();
        _setOrangePointsVisible->show();

        _labelAxisX->show();
        _labelAxisY->show();
        _labelPointsVisible->show();
    }
    else
    {
        _chartView->hide();
        _setXAxis->hide();
        _setYAxis->hide();
        _setOrangePointsVisible->hide();

        _labelAxisX->hide();
        _labelAxisY->hide();
        _labelPointsVisible->hide();
    }
}


void MainWindow::on_SaveDayButton_released()
{
    QFileDialog* qfiledialog = new QFileDialog();
    qfiledialog->setDefaultSuffix("json");
    auto eatenDaySavedName = qfiledialog->getSaveFileName(this, "Save the eaten day", std::filesystem::current_path().append("days").string().data(), tr("*.json"));
    if(eatenDaySavedName.isNull())
        return;
    if (!eatenDaySavedName.endsWith(".json", Qt::CaseInsensitive)) {
        eatenDaySavedName += ".json";
    }
    qDebug() << qfiledialog->defaultSuffix().toStdString().data();
    qDebug() <<"\n";
    Json::Value root;
    EatenDaySerializer eatenDaySerializer(root);
    eatenDaySerializer.ObjectToRoot(*_eatenDay);
    std::ofstream file(eatenDaySavedName.toStdString());
    qDebug()<<eatenDaySavedName;
    file << root;
    file.close();
}


void MainWindow::on_LoadDayButton_released()
{
    auto eatenDaySavedName = QFileDialog::getOpenFileName(this, "Load the eaten day", std::filesystem::current_path().append("days").string().data(), tr("*.json"));
    if(eatenDaySavedName.isNull())
        return;
    EatenDay eatenDay;
    std::ifstream file(eatenDaySavedName.toStdString());
    Json::Value root;
    EatenDayDeserializer deserializer(root);
    deserializer.FileToRoot(file);
    _eatenDay->Clean();
    deserializer.RootToObject(*_eatenDay);
    _dayTable->Reload();
    file.close();
}

