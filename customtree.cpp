#include "customtree.h"

void CustomTree::popupCut()
{
    this->popupCopy();
    *cutted = true;
}
void CustomTree::eventHandle(QKeyEvent *event)
{
    this->popupErase();
}
void CustomTree::popupCopy()
{
    if ( itemsSelected != 0)
    {
        *selectedIndex = this->tree->selectionModel()->selectedRows().at(0);
        *selectedCount = this->tree->selectionModel()->selectedRows().length();
        *empty = false; *cutted = false; vec->clear();
        QFileInfo info;
        for (int i = 0; i < *selectedCount ; i++)
        {
            info = this->model->fileInfo(
                        this->tree->selectionModel()->selectedRows().at(i));
            vec->push_front(info.fileName());
            vec->push_front(info.absoluteFilePath());
        }
    }
        else
    {
        vec->clear();
        *empty = true;
    }
}
void CustomTree::popupPaste()
{
    if ( !vec->isEmpty() )
    {
        *empty = true;
        auto index = this->tree->currentIndex();

        QFileInfo info = this->model->fileInfo(index);

        auto it = vec->begin();
        while ( it != vec->end() )
        {
            QString oldFile = *(it++);
            QString newFile = info.absoluteFilePath();
            newFile += "/";
            newFile += *(it++);


            std::wstring wstr1 = oldFile.toStdWString();
            LPCWSTR path1 = wstr1.c_str();

            std::wstring wstr2 = newFile.toStdWString();
            LPCWSTR path2 = wstr2.c_str();

            WINBOOL errorFounded;

            if ( *cutted && !MoveFile(path1,path2) )
                QMessageBox::warning(this->tree, tr("Упс..."),tr("При перемещении произошла ошибка"));
            else
            {
                CopyFile(path1,path2,errorFounded);
                if ( !errorFounded )
                    QMessageBox::warning(this->tree, tr("Упс.."),tr("При копировании произошла ошибка"));
            }
            qDebug() << oldFile << " -> " << newFile;
            this->model->refresh();
        }
    }
}

////////////////////////////// OTHER CODE /////////////////////////////////
CustomTree::CustomTree(QObject *parent) : QObject(parent)
{
        copy   = new QAction(QString::fromUtf8("Копировать")   ,this);
        cut    = new QAction(QString::fromUtf8("Вырезать")     ,this);
        paste  = new QAction(QString::fromUtf8("Вставить")     ,this);
        paste->setEnabled(false);
        erase  = new QAction(QString::fromUtf8("Удалить")      ,this);
        rename = new QAction(QString::fromUtf8("Переименовать"),this);
        mkdir  = new QAction(QString::fromUtf8("Создать")      ,this);
        prop   = new QAction(QString::fromUtf8("Свойства")     ,this);

        this->menu->setStyleSheet("border-style: outset;"
                                  "border-width: 1px;"
                                  "border-radius: 5px;"
                                  "border-color: beige;"
                                  "min-width: 10em;"
                                  "padding: 2px;"
                                  "border-color: black;");
        this->menu->addAction(copy) ;
        this->menu->addAction(cut)  ;
        this->menu->addAction(paste);
        this->menu->addAction(erase);
        this->menu->addAction(rename);
        this->menu->addAction(prop) ;
        this->menu->addAction(mkdir);

            QObject::connect(this->prop,SIGNAL(triggered(bool)),
                             this,SLOT(popupProp()));

            QObject::connect(this->copy,SIGNAL(triggered(bool)),
                             this,SLOT(popupCopy()));

            QObject::connect(this->cut,SIGNAL(triggered(bool)),
                             this,SLOT(popupCut()));

            QObject::connect(this->rename,SIGNAL(triggered(bool)),
                             this,SLOT(popupRename()));

            QObject::connect(this->erase,SIGNAL(triggered(bool)),
                             this,SLOT(popupErase()));

            QObject::connect(this->paste,SIGNAL(triggered(bool)),
                             this,SLOT(popupPaste()));

            QObject::connect(this->mkdir,SIGNAL(triggered(bool)),
                             this,SLOT(popupMkdir()));

}
void CustomTree::drawPath()
{
    auto index = tree->currentIndex();

    auto index2 = index;
    QString str =
     tree->model()->sibling(index2.row(),0,index2).data().toString();
    index2 = index2.parent();

    while ( index2.parent().data().toString() != NULL )
    {
        str = index2.data().toString() + "/" + str;
        index2 = index2.parent();
    }
    str.insert(0,tab->tabText(tab->currentIndex()));

    adressLine->setText(str);
    fileNameLine->setText(index.sibling(index.row(),0).data().toString());
}
void CustomTree::openItem()
{
    if ( adressLine->text() != NULL )
    {
        QString str = "file:///";
        str.append(adressLine->text());
        QDesktopServices::openUrl(
         QUrl(str,
         QUrl::TolerantMode));
    }
}
void CustomTree::popUp()
{
    //itemsSelected = this->tree->selectionModel()->selectedRows().length();
    //qDebug() << "rows - " << itemsSelected;
        if ( itemsSelected != 0 )
        {
            if (!*empty) paste->setEnabled(true);
                else paste->setEnabled(false);

            this->copy->setEnabled(true);
            this->cut->setEnabled(true);
            this->rename->setEnabled(true);
            this->erase->setEnabled(true);
        } else {
            if (!*empty) paste->setEnabled(true);
                else paste->setEnabled(false);
            this->copy->setEnabled(false);
            this->cut->setEnabled(false);
            this->rename->setEnabled(false);
            this->erase->setEnabled(false);
        }
        if (this->tree->currentIndex().isValid()
                &&
            !model->isDir(this->tree->currentIndex())
           ) this->mkdir->setEnabled(false);
             else this->mkdir->setEnabled(true);
        menu->popup(QCursor::pos());
}

void CustomTree::popupErase()
{
    if ( itemsSelected != 0 )
    {
        for (int i = 0; i < itemsSelected; i++)
        {
            auto index = this->tree->selectionModel()->selectedRows(0).at(0);
            //qDebug() << index.data().toString();
            bool ok = this->model->remove(index);
            if ( ok ) continue;
            else {
                QMessageBox::warning(this->tree, tr("Ошибка"),
                                     tr("Ошибка удаления %1").arg(
                                         model->fileName(index))); continue;
            }
        }
    }
}
void CustomTree::popupRename()
{
    auto index = this->tree->currentIndex();
    if ( itemsSelected != 0 ) this->tree->edit(
                tree->model()->sibling(index.row(),0,index));

}
void CustomTree::popupMkdir()
{
    QModelIndex index;
    if ( itemsSelected != 0 )
        index = this->tree->currentIndex();
    else
        index = this->tree->rootIndex();

    QString name = QInputDialog::getText(tree, tr("Создать папку "), tr("Имя папки "));
    if ( !name.isEmpty() )
    {
        if ( !model->isDir(index) ) {
            index = model->parent(index);
        }
        if ( !model->mkdir(index, name).isValid() ) {
            QMessageBox::information(tree, tr("Ошибка создания папки..."), tr("Ошибка во время создания директории"));
        }
    }
}
void CustomTree::popupProp()
{
    auto info = this->model->fileInfo(this->tree->currentIndex());
    QString name = info.fileName();
    name += " - ";
    name += QString::number(info.size()) ;
    name += tr(" байт");

    propUi = new Prop(name);
    propUi->setNameEdit(info.fileName());
    propUi->setSizeEdit(QString::number(info.size()));
    propUi->setPathEdit(info.absoluteFilePath());
    propUi->show();
}
void CustomTree::addTree(QTreeView *tree)
{
    this->tree = tree;
    this->tree->setDragEnabled(true);
    this->tree->setAcceptDrops(true);
    this->tree->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->tree->setSelectionMode(QTreeView::ContiguousSelection);
    this->tree->setContextMenuPolicy(Qt::CustomContextMenu);
    this->tree->setColumnWidth(0,200);
    this->tree->setColumnWidth(1,70);
    this->tree->setColumnWidth(2,60);
    this->tree->setSortingEnabled(true);

        QObject::connect(this->tree,SIGNAL(clicked(QModelIndex)),
                         this,SLOT(drawPath()));

        QObject::connect(this->tree,SIGNAL(doubleClicked(QModelIndex)),
                         this,SLOT(openItem()));

        QObject::connect(this->tree,SIGNAL(customContextMenuRequested(QPoint)),
                         this,SLOT(drawPath()));

        QObject::connect(this->tree,SIGNAL(customContextMenuRequested(QPoint)),
                         this,SLOT(popUp()   ));
}

















