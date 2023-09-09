#include "mainwindow.h"

#include <QApplication>
#include <jsoncpp/json/json.h>
#include <fstream>
#include "size_unc.h"
#include <QString>
#include "ddt.h"

int main(int argc, char *argv[])
{
    DDT::LoadProductBase();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
