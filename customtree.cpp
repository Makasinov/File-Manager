#include "customtree.h"

/*!
 * This function provides recursively copy the folder and files.
 * Эта функция позволяет рекурсивно делать копии папок и файлов.
 */
bool CustomTree::scanDir(std::wstring oldFile, std::wstring newFile, boost::system::error_code error_code)
{
    //qDebug() << "scanDir - " << oldFile.data() << "\t" << newFile.data();
    boost::filesystem::create_directory(newFile.data(),error_code);
    //if ( error_code )
    //boost::filesystem::copy_directory(oldFile.toStdWString(),newFile.toStdWString(),error_code);

    boost::filesystem::path path(oldFile.data());

    boost::filesystem::directory_iterator end_itr;
    //qDebug() << "Nu poehali - " << oldFile.data();
    for (boost::filesystem::directory_iterator itr(path); itr != end_itr; ++itr)
    {
        //if (boost::filesystem::is_regular_file(itr->path())) {
            std::wstring current_file = itr->path().wstring();
            std::wstring oldFile = newFile.data();
            oldFile += CustomTree::slash;
            std::wstring var = current_file.data();
            int position = var.length();
            //qDebug() << "-" << var.data();
            while ( var[position] != CustomTree::nonSlash) --position;
            var.erase(0,(position + 1));
            //qDebug() << "after - " << var.data() << "\t";
            oldFile += var;
            if ( boost::filesystem::is_directory(current_file.data()) )
                scanDir(current_file,oldFile,error_code);
            else boost::filesystem::copy_file(current_file.data(),oldFile.data(),error_code) ;
            //qDebug() << "\t" << current_file.data() << " | " << oldFile.data() ;
        //}
    }
}
/// Метод вставки выделенных файлов/каталогов.
void CustomTree::popupPaste()
{
    checkSelected();
    if ( !vec->isEmpty() )
    {
        *empty = true;
        auto index = this->tree->currentIndex();

        QFileInfo info;
        if ( index.isValid() )
         info = this->model->fileInfo(index);
        else info = this->model->fileInfo(this->tree->rootIndex());
        auto it = vec->begin();
        while ( it != vec->end() )
        {
            QString oldFile = *(it++);
            QString newFile = info.absoluteFilePath();
            newFile += "/";
            newFile += *(it++);

            boost::system::error_code error_code;
            if ( boost::filesystem::is_directory(oldFile.toStdWString(),error_code) )
            {
                //qDebug() << "directory - " << oldFile;
                scanDir(oldFile.toStdWString(),newFile.toStdWString(),error_code);
                if ( *cutted ) {
                    boost::filesystem::remove_all(oldFile.toStdWString());
                    QString text = adressLine_2->text();
                    while ( *(text.end() - 1) != slash )
                    {
                        text.remove(-1,text.length());
                        //qDebug() << *text.end() << "\t" << text;
                    }
                    adressLine_2->setText(text);
                }
            }   else    {
                //qDebug() << "file - " << oldFile;
                boost::filesystem::copy_file(oldFile.toStdWString(),newFile.toStdWString(),error_code);
            }
            if ( error_code )
                QMessageBox::warning(this->tree, tr("Упс.."),tr("При копировании произошла ошибка"));
            //qDebug() << oldFile << " -> " << newFile;
            }
            this->model->refresh();
    }
}
void CustomTree::popupCut()
{
    checkSelected();
    this->popupCopy();
    *cutted = true;
}
/// Пока не используется
/// TODO - Обработчик горячих клавиш.
void CustomTree::eventHandle(QKeyEvent *event)
{
    this->popupErase();
}
/*! \brief Метод, где все выделенные файлы загружаются в QList<QString>.
	Также используется и для вырезания, и для удаления, но немного иначе.
	\brief Если коротко, то здесь программа запоминает все выделенные файлы.
*/
void CustomTree::popupCopy()
{
    checkSelected();
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
    }   else    {
        vec->clear();
        *empty = true;
    }
}

/*! \brief Здесь налаживаются все связи между событиями.
*/
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
/// отрисовка пути до выделенного файла в UI.
void CustomTree::drawPath()
{
    auto index = tree->currentIndex();

    auto index2 = index;
    QString str =
     tree->model()->sibling(index2.row(),0,index2).data().toString();
    index2 = index2.parent();

    while ( index2.parent().data().toString() != NULL )
    {
        str = index2.data().toString() + slash + str;
        index2 = index2.parent();
    }
    str.insert(0,tab->tabText(tab->currentIndex()));

    adressLine->setText(str);
    fileNameLine->setText(index.sibling(index.row(),0).data().toString());
}
/// openItem - Конструкция, открывающая файл по нажатию двойного щелчка.
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
/// Метод происходит, когда выпадает контекствое меню.
/// Здесь включаются и выключаются необходимые кнопки.
void CustomTree::popUp()
{
    checkSelected();
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
/// метод удаления выделеных файлов/директорий
void CustomTree::popupErase()
{
    checkSelected();
    if ( itemsSelected != 0 )
    {
        popupCopy();
        auto it = vec->begin();
        //qDebug() << vec->begin().operator *();
        while (it != vec->end())
        {
            //auto index = this->tree->selectionModel()->selectedRows(0).at(0);
            //qDebug() << index.data().toString();
            //bool ok = this->model->remove(index);
            boost::system::error_code error_code;

            QString file = it.operator *();
//            if ( boost::filesystem::is_directory(file.toStdString(),error_code) )
//                boost::filesystem::remove_all()
            boost::filesystem::remove_all(file.toStdWString(),error_code );
            it += 2;

            if ( error_code )
            {
                QMessageBox::warning(this->tree, tr("Ошибка"),
                            tr("Ошибка удаления %1").arg(file)); continue;
            }
        }
        QString text = adressLine->text();
        while ( *(text.end() - 1) != slash )
        {
            text.remove(-1,text.length());
            //qDebug() << *text.end() << "\t" << text;
        }
        //text.remove(-1,text.length());
        adressLine->setText(text);
    }
}
void CustomTree::popupRename()
{
    checkSelected();
    auto index = this->tree->currentIndex();
    if ( itemsSelected != 0 ) this->tree->edit(
                tree->model()->sibling(index.row(),0,index));

}
void CustomTree::popupMkdir()
{
    auto index = this->tree->currentIndex();
    if ( ! index.isValid() ) index = this->tree->rootIndex();

        QString name = QInputDialog::getText(tree, tr("Создание директории "),
                                               tr("Имя папки "));
        if ( !name.isEmpty() )
        {
            //qDebug() << adressLine << " + " << name;
            QString newDir = adressLine->text() + slash + name ;
            if ( !boost::filesystem::create_directory(newDir.toStdWString()) )
            QMessageBox::information(tree, tr("Ошибка создания папки..."),
                                tr("Ошибка во время создания директории"));
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
/// Метод который проверяет количество выделеных файлов в рабочей области.
void CustomTree::checkSelected()
{
    itemsSelected = this->tree->selectionModel()->selectedRows().length();
}












