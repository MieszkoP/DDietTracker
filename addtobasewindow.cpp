#include "addtobasewindow.h"
#include "ui_addtobasewindow.h"
#include <QMessageBox>

AddToBaseWindow::AddToBaseWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddToBaseWindow)
{
    ui->setupUi(this);

    _products = AllProductsBase::GetInstance();
    int i = 0;
    for(auto const& [category, products] : *(_products->GetCategoriesMap()))
    {
        ui->comboBoxCategory->addItem(QString::fromStdString(category._name), i);
        i+=1;
    }
    ui->comboBoxCategory->addItem("Add new category", i);
    ui->comboBox_2->addItem("Mass", static_cast<int>(QuantityType::mass));
    ui->comboBox_2->addItem("Volume", static_cast<int>(QuantityType::volume));
    ui->BaseQuantityValue->setValue(100);
    ui->BaseQuantityUncertainty->setValue(1);

    _quantityString = "g";
    _perQuantityString = "[g/100"+_quantityString+"]";
    _perQuantityStringKcal = "[kcal/100"+_quantityString+"]";

    //connect(ui->comboBox_2, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &AddToBaseWindow::UpdateLabels);

}

AddToBaseWindow::~AddToBaseWindow()
{
    delete ui;
}

void AddToBaseWindow::on_comboBoxCategory_currentIndexChanged(int)
{

    if("Add new category" == ui->comboBoxCategory->currentText())
    {
        ui->EditCategory->setEnabled(true);
    }
    else
    {
        ui->EditCategory->setEnabled(false);
    }
}

void AddToBaseWindow::UpdateLabels()
{
    if(
        auto quantityType = static_cast<QuantityType>(ui->comboBox_2->itemData(ui->comboBox_2->currentIndex()).toInt()); 
        quantityType == QuantityType::volume)
    {
        _quantityString = "ml";
    }
    else
    {
        _quantityString = "g";
    }

    _perQuantityString = "[g/"+std::to_string(int(ui->BaseQuantityValue->value()))+_quantityString+"]";
    _perQuantityStringKcal = "[kcal/"+std::to_string(int(ui->BaseQuantityValue->value()))+_quantityString+"]";

    ui->BaseQuantityType->setText(QString::fromStdString(_quantityString));
    ui->DefaultQuantityType->setText(QString::fromStdString(_quantityString));


    ui->KcaloriesQuantity->setText(QString::fromStdString(_perQuantityStringKcal));
    ui->ProteinsQuantity->setText(QString::fromStdString(_perQuantityString));
    ui->CarbonsQuantity->setText(QString::fromStdString(_perQuantityString));
    ui->FatsQuantity->setText(QString::fromStdString(_perQuantityString));
}


[[maybe_unused]] void AddToBaseWindow::on_comboBox_2_activated(int)
{
    UpdateLabels();
}


[[maybe_unused]] void AddToBaseWindow::on_BaseQuantityValue_valueChanged(double)
{
    UpdateLabels();
}

void AddToBaseWindow::on_buttonBox_accepted()
{
    Product product;
    product._quantityType = static_cast<QuantityType>(ui->comboBox_2->itemData(ui->comboBox_2->currentIndex()).toInt());
    if(ui->comboBoxCategory->currentText()=="Add new category")
    {
        product._productCategory = ui->EditCategory->text().toStdString();
    }
    else
    {
        product._productCategory = ui->comboBoxCategory->currentText().toStdString();
    }
    product._name = ui->EditName->text().toStdString();
    if(product._name.empty() || product._name=="None")
    {
        QMessageBox::warning(this, "You must specify name!", "You must specify name!");
        return;
    }
    if(_products->IsProduct(product._name))
    {
        QMessageBox::warning(this, "Product already exist!", "Product already exist!");
        return;
    }
    product._carbons = size_unc(ui->CarbonsValue->value(), ui->CarbonsUncertainty->value());
    product._kcalories = size_unc(ui->KcaloriesValue->value(), ui->KcaloriesUncertainty->value());
    product._proteins = size_unc(ui->ProteinsValue->value(), ui->ProteinsUncertainty->value());
    product._fats = size_unc(ui->FatsValue->value(), ui->FatsUncertainty->value());
    product._quantity = size_unc(ui->BaseQuantityValue->value(), ui->BaseQuantityUncertainty->value());
    product._standard_quantity = size_unc(ui->DefaultQuantityValue->value(), ui->DefaultQuantityUncertainty->value());
    _products->AddProduct(product);

    SendSignal();
}

