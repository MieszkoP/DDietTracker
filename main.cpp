#include "mainwindow.h"

#include <QApplication>
#include <jsoncpp/json/json.h>
#include <fstream>

class Product
{
public:
    Product() = default;

    int _kcalories = 0;
    int _proteins = 0;
    int _carbons = 0;
    int _fats = 0;
    int _mass = 0;
};

void ParseProduct(const Product& product, std::ofstream& file)
{
    Json::Value root;
    root["carbons"] = product._carbons;
    root["kcalories"] = product._kcalories;
    root["proteins"] = product._carbons;
    root["fats"] = product._fats;
    root["mass"] = product._mass;
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
