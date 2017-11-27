#ifndef CUSTOMTREE_H
#define CUSTOMTREE_H

#include "prop.h"
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
#include <QTimer>
#include <boost/filesystem.hpp>
#include <iostream>
#include <string.h>

class CustomTree : public QObject
{
    Q_OBJECT

public:
    CustomTree(QObject *parent = nullptr);
    void addPath(QLineEdit * LineEdit)      {this->adressLine = LineEdit;}   //
    void addOtherPath(QLineEdit * LineEdit) {this->adressLine_2 = LineEdit;} //
    void addFileName(QLineEdit * LineEdit)  {this->fileNameLine = LineEdit;} //
    void addTab(QTabWidget * tab) {this->tab = tab;}                         //
    void addTree(QTreeView * tree);                                          //
    bool eraseDir(QModelIndex index);                                        //
    void addModel(QDirModel * model) { this->model = model; }                //
    void addBool(bool &EMPTY) {this->empty = &EMPTY;}                        //
    void addCut(bool &CUT) {this->cutted = &CUT;}                            //
    void addClipboard(QModelIndex &SI) {this->selectedIndex = &SI;}          //
    void addCount(qint32 &SC) {this->selectedCount = &SC;}                   //
    void addVec(QList<QString> &L) {this->vec = &L;}                         //
    void eventHandle(QKeyEvent *event);                                      //
    bool scanDir(std::wstring oldFile, std::wstring newFile, boost::system::error_code error_code);
    static const char slash = '/';                                           //
    static const char nonSlash = '\\';                                       //

public slots:
    void checkSelected();
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
    void refreshTree() {   this->model->refresh();   }
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

    QList<QString> * vec;
    int itemsSelected;
    Prop * propUi;
    QTreeView  * tree;
    QDirModel * model;

    QTabWidget * tab;
    QLineEdit  * adressLine;         // absolute path to file
    QLineEdit  * adressLine_2;       // second one
    QLineEdit  * fileNameLine;

};


#endif // CUSTOMTREE_H
