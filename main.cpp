#include "mainwindow.h"
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("File Manager 1.1.3");

    w.show();

    return a.exec();
}
