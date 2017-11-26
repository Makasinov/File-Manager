#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFocusPolicy(Qt::StrongFocus);

    setAcceptDrops(true);

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
    timer.start(500);

    for (int i = 0; i < count; ++i)
    {
        tree[i].setModel(model);
        tree[i].setRootIndex(model->index(list.at(i).path()));

        QObject::connect(&timer,SIGNAL(timeout()),
                         &arr[i],SLOT(refreshTree()));

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

        QObject::connect(&timer,SIGNAL(timeout()),
                         &arr[l],SLOT(refreshTree()));

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
bool MainWindow::event(QEvent * event)
{
    const auto CtrlPlusC = "\u0003";
    if ( event->type() == QEvent::KeyPress){
        QKeyEvent * keyEvent = static_cast<QKeyEvent *>(event);
        //qDebug() << keyEvent->text();
        for ( int i = 0; i < (count + count); i++ )
            if (tree[i].hasFocus() )
            {
                //if ( keyEvent->text()[5] == '3' );
          //          qDebug() << keyEvent->text() << " event!";
                //else if ( ) qDebug() << "Delete event!"
                break;
            }
    };
    QMainWindow::event(event);
}
MainWindow::~MainWindow()
{ delete ui; }




