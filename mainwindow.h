#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "customtree.h"
#include <QMainWindow>
#include <QFileSystemModel>
#include <QTreeView>
#include <QFileInfoList>
#include <QDebug>
#include <QSplitter>
#include <QModelIndex>
#include <windows.h>
#include <QKeyEvent>
#include <QDrag>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QDirModel>
#include <QTimer>
#include <QKeyEvent>
#include <QWidget>

namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    bool event(QEvent *event);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool empty = true;             // is "Clipboard" empty or not
    bool cutted = false;
    int selectedCount;
    QModelIndex selectedIndex;

private slots:
    void debug()
    {   qDebug() << "DEBUG";    }

private:
    Ui::MainWindow *ui;

    QList<QString> * vec = new QList<QString>; // actually it's list,
                                               // but this name already
                                               // exists :3 (vector)
    QFileInfoList list = QDir::drives();
    int count = list.count();

    QTreeView * tree = new QTreeView[count + count];
    CustomTree * arr = new CustomTree[count + count];
    QTimer timer;

};

#endif // MAINWINDOW_H
















