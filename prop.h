#ifndef PROP_H
#define PROP_H

#include <QWidget>

namespace Ui {
class Prop;
}

class Prop : public QWidget
{
    Q_OBJECT

public:
    explicit Prop(QString name = "Title",QWidget *parent = 0);
    ~Prop();
    void setNameEdit(QString name);
    void setSizeEdit(QString name);
    void setPathEdit(QString name);

private slots:
    void on_closeButton_clicked();
    void closeButtonPress();
    void closeButtonRelease();

private:
    Ui::Prop *ui;
};

#endif // PROP_H
