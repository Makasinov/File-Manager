#include "prop.h"
#include "ui_prop.h"

Prop::Prop(QString name,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Prop)
{
    ui->setupUi(this);

    this->setWindowTitle(name);

    QObject::connect(this->ui->closeButton,SIGNAL(pressed()),
                     this,SLOT(closeButtonPress()));
    QObject::connect(this->ui->closeButton,SIGNAL(released()),
                     this,SLOT(closeButtonRelease()));
}

Prop::~Prop()
{
    delete ui;
}
void Prop::setNameEdit(QString name)
{
    this->ui->nameEdit->setText(name);
}
void Prop::setSizeEdit(QString name)
{
    this->ui->sizeEdit->setText(name);
}
void Prop::setPathEdit(QString name)
{
    this->ui->pathEdit->setText(name);
}
void Prop::closeButtonPress()
{
    this->ui->closeButton->setStyleSheet(
                "border-style:  outset;"
                "border-width:  1px;"
                "border-radius: 5px;"
                "border-color:  beige;"
                "min-width:     7em;"
                "padding:       1px;"
                "border-color:  blue;");
}
void Prop::closeButtonRelease()
{
    this->ui->closeButton->setStyleSheet(
                "border-style: outset;"
                "border-width: 1px;"
                "border-radius: 5px;"
                "border-color: beige;"
                "min-width: 7em;"
                "padding: 1px;"
                "border-color: grey;");
}
void Prop::on_closeButton_clicked()
{
    this->close();
}
