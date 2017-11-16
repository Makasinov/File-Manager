#ifndef CUSTOMTREE_H
#define CUSTOMTREE_H

#include "prop.h"
#include <windows.h>
#include <QTreeView>
#include <QStandardItem>
#include <QDesktopServices>
#include <QTableWidget>
#include <QLineEdit>
#include <QString>
#include <QObject>
#include <QMouseEvent>
#include <QDebug>
#include <QMenu>
#include <QAction>
#include <QSplitter>
#include <QFileInfo>
#include <QMessageBox>
#include <QDirModel>
#include <QInputDialog>
#include <QList>
#include <QKeyEvent>
class Model : public QDirModel
{
  Q_OBJECT
public:
      void beginInserting(QModelIndex &parent, int first, int last)
    {   beginInsertRows(parent,first,last);  }
    void endInserting()
   {   endInsertRows();  }
   // Model(QDirModel &model)
   // { this = model; }
//private:
    //QDirModel * model;
};


class CustomTree : public QObject
{
    Q_OBJECT

public:
    CustomTree(QObject *parent = nullptr);
    void addPath(QLineEdit * LineEdit)      {this->adressLine = LineEdit;}
    void addFileName(QLineEdit * LineEdit)  {this->fileNameLine = LineEdit;}
    void addTab(QTabWidget * tab) {this->tab = tab;}
    void addTree(QTreeView * tree);
    bool eraseDir(QModelIndex index);
    void addModel(Model * model) { this->model = model; }
    void addBool(bool &EMPTY) {this->empty = &EMPTY;}
    void addCut(bool &CUT) {this->cutted = &CUT;}
    void addClipboard(QModelIndex &SI) {this->selectedIndex = &SI;}
    void addCount(qint32 &SC) {this->selectedCount = &SC;}
    void addVec(QList<QString> &L) {this->strVec = &L;}
    void addVec2(QList<QModelIndex> &L) {this->mdlVec = &L;}

public slots:
    void keyPressEvent(QKeyEvent * event);
    void drawPath();
    void openItem();
    void popUp();
    void popupCopy();
    void popupCut();
    void popupPaste();
    void popupErase();
    void popupRename();
    void popupProp();
    void popupMkdir();
    void debug() {  qDebug() << "DEBUUUUG"; }

private:
    bool * empty;
    bool * cutted;                  // Cut action
    int  * selectedCount;
    QModelIndex * selectedIndex;

    QMenu * menu = new QMenu;       // popUp menu with 5 fields
    QAction * paste  ;
    QAction * copy   ;
    QAction * erase  ;              // not "delete", becase it's engaged
    QAction * cut    ;
    QAction * rename ;
    QAction * mkdir  ;
    QAction * prop   ;

    QList<QString> * strVec;
    QList<QModelIndex> * mdlVec;
    int itemsSelected;
    Prop * propUi;
    QTreeView  * tree;
    Model * model;

    QTabWidget * tab;
    QLineEdit  * adressLine;         // absolute path to file
    QLineEdit  * fileNameLine;
};

#endif // CUSTOMTREE_H
