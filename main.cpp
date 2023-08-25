#include "mainwindow.h"

#include <QApplication>
#include <jsoncpp/json/json.h>
#include <fstream>
#include "size_unc.h"

class Product
{
public:
    Product() = default;

    size_unc _kcalories = 0;
    size_unc _proteins = 0;
    size_unc _carbons = 0;
    size_unc _fats = 0;
    size_unc _mass = 0;
};

void ParseProduct(const Product& product, std::ofstream& file)
{
    Json::Value root;
    root["carbons"] = product._carbons.GetValue();
    root["kcalories"] = product._kcalories.GetValue();
    root["proteins"] = product._carbons.GetValue();
    root["fats"] = product._fats.GetValue();
    root["mass"] = product._mass.GetValue();
    file << root;
}

int main(int argc, char *argv[])
{
    Json::Value root;
    std::ofstream file;
    file.open("File.json");
    Product product;
    ::ParseProduct(product, file);
    file.close();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
