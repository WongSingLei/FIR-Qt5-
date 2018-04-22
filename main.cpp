#include "mainwindow.h"
#include <QApplication>

/*
 * Qt五子棋单机游戏
 * 功能：双人对战
 *
*/



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
