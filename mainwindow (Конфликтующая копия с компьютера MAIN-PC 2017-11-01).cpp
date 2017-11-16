#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setAcceptDrops(true);
    /*QObject::connect(this,SIGNAL(dragEnterEvent(QDragEnterEvent*)),
                     this,SLOT(dragEnterEventSlot(QDragEnterEvent*)));
    QObject::connect(this,SIGNAL(dropEvent(QDropEvent*)),
                     this,SLOT(dropEventSlot(QDropEvent*)));*/
    QTreeView * tree = new QTreeView[count + count];
    CustomTree * arr = new CustomTree[count + count];

    ui->tabWidget  ->removeTab(0);
    ui->tabWidget  ->removeTab(0);
    ui->tabWidget_2->removeTab(0);
    ui->tabWidget_2->removeTab(0);

    QDirModel *model = new QDirModel;
    //QFileSystemModel *model = new QFileSystemModel;

    model->setFilter(QDir::Files|QDir::Dirs|QDir::NoDotAndDotDot); // Hide dots
    //model->setRootPath("/");
    QDir::setCurrent(QDir::rootPath());
    model->setReadOnly(false);

    for (int i = 0; i < count; ++i)
    {
        tree[i].setModel(model);
        tree[i].setRootIndex(model->index(list.at(i).path()));

        QObject::connect(tree[i].header(),SIGNAL(sectionPressed(int)),
                         &arr[i],SLOT(changeSortOrder()));
        /*QObject::connect(this,SIGNAL(keyPressEvent(QKeyEvent*)),
                         &arr[i],SLOT(keyPressEvent(QKeyEvent*)));*/

        arr[i].addVec(*vec);
        arr[i].addModel(model);
        arr[i].addTree(&tree[i]);
        arr[i].addPath(ui->adressEdit);
        arr[i].addFileName(ui->itemNameEdit);
        arr[i].addTab(ui->tabWidget);
        arr[i].addClipboard(this->selectedIndex);
        arr[i].addCount(this->selectedCount);
        arr[i].addBool(this->empty);
        arr[i].addCut(this->cutted);

        ui->tabWidget->addTab(&tree[i],list.at(i).path());
    }

    for (int i = 0,l = count; l < count + count; ++i,++l)
    {
        tree[l].setModel(model);
        tree[l].setRootIndex(model->index(list.at(i).path()));

        QObject::connect(tree[l].header(),SIGNAL(sectionPressed(int)),
                         &arr[l],SLOT(changeSortOrder()));
        /*QObject::connect(this,SIGNAL(keyPressEvent(QKeyEvent*)),
                         &arr[l],SLOT(keyPressEvent(QKeyEvent*)));*/

        arr[l].addVec(*vec);
        arr[l].addModel(model);
        arr[l].addTree(&tree[l]);
        arr[l].addPath(ui->adressEdit2);
        arr[l].addFileName(ui->itemNameEdit2);
        arr[l].addTab(ui->tabWidget_2);
        arr[l].addClipboard(this->selectedIndex);
        arr[l].addCount(this->selectedCount);
        arr[l].addBool(this->empty);
        arr[l].addCut(this->cutted);

        ui->tabWidget_2->addTab(&tree[l],list.at(i).path());
    }
}

MainWindow::~MainWindow()
{ delete ui; }




