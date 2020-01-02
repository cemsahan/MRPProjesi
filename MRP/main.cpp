#include "MainWindow.h"
#include <QApplication>

#include <QDesktopWidget>
#include<Qt>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowFlags(Qt::CustomizeWindowHint);

    w.show();

    return a.exec();
}
