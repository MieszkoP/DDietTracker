#include "addeatenproductwindow.h"
#include "ui_addeatenproductwindow.h"

AddEatenProductWindow::AddEatenProductWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEatenProductWindow)
{
    ui->setupUi(this);
    _products = AllProductsBase::GetInstance();
    int i = 0;
    for (const auto& [category, productList]: *(_products->GetCategoriesMap()))
    {
        ui->CategoryBox->addItem(QString::fromStdString(category._name), i);
        i+=1;
    }
    QDateTime dateTime = QDateTime::currentDateTime();
    ui->dateTimeEdit->setDateTime(dateTime);
}

AddEatenProductWindow::~AddEatenProductWindow()
{
    delete ui;
}

void AddEatenProductWindow::on_NameBox_activated(int)
{
    const Product& chosenProduct = _products->GetProduct(ui->NameBox->currentText().toStdString());
    if( chosenProduct._quantityType == QuantityType::mass)
    {
        ui->quantity_type->setText("[g]");
    }
    else
    {
        ui->quantity_type->setText("[ml]");
    }
}

void AddEatenProductWindow::SetEatenDay(std::shared_ptr<EatenDay> eatenDay)
{
    _eatenDay = eatenDay;
}

void AddEatenProductWindow::on_CategoryBox_currentIndexChanged(int index)
{
    ui->NameBox->clear();
    auto begin = _products->GetCategoriesMap()->begin();
    int variant = ui->CategoryBox->itemData(index).toInt();
    for(int i = 0; i < variant; i++)
    {
        ++begin;
    }

    *_choosenCategory = begin->first;

    auto categories_map = (*(_products->GetCategoriesMap()))[*_choosenCategory];

    int i = 0;
    for (auto product : categories_map)
    {
        ui->NameBox->addItem(QString::fromStdString(product->_name), i);
        i+=1;
    }
}

void AddEatenProductWindow::on_buttonBox_accepted()
{
    if(ui->NameBox->currentText().isNull())
    {
        return;
    }

    Product chosenProduct = _products->GetProduct(ui->NameBox->currentText().toStdString());
    auto quantity = size_unc(ui->valueBox->value(), ui->uncertaintyBox->value());
    EatenProduct eatenProduct(chosenProduct, quantity);

    if(_IsDate)
    {
        int day = ui->dateTimeEdit->dateTime().date().day();
        int month = ui->dateTimeEdit->dateTime().date().month();
        int year = ui->dateTimeEdit->dateTime().date().year();

        int hour = ui->dateTimeEdit->dateTime().time().hour();
        int minute = ui->dateTimeEdit->dateTime().time().minute();
        eatenProduct.SetTime(hour, minute);
        eatenProduct.SetDate(year, month, day);

    }
    _eatenDay->AddEatenProduct(eatenProduct);
    SendSignal();
}

void AddEatenProductWindow::on_checkBox_stateChanged([[maybe_unused]] int arg1)
{
    _IsDate = ! _IsDate;
    ui->dateTimeEdit->setEnabled(_IsDate);
}

