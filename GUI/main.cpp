#include "mainwindow.h"

#include <QApplication>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(600, 400);
    w.show();
    return a.exec();
    }

