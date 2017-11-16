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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool empty = true;             // is "Clipboard" empty or not
    bool cutted = false;
    int selectedCount;
    QModelIndex selectedIndex;

signals:
    virtual void keyPressEvent(QKeyEvent* event);

private slots:
    void debug()
    {   qDebug() << "DEBUG";    }
    void dragEnterEventSlot(QDragEnterEvent *event)
    {qDebug() << event;}
    void dropEventSlot(QDropEvent *event)
    {qDebug() << event;}

private:
    Ui::MainWindow *ui;

    QList<QString> * vec = new QList<QString>; // actually it's list,
                                               // but this name already
                                               // exists :3 (vector)
    QList<QModelIndex> *vec2 = new QList<QModelIndex>;
    QFileInfoList list = QDir::drives();
    int count = list.count();
};

#endif // MAINWINDOW_H
