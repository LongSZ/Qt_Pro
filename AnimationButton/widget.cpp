#include "widget.h"
#include "ui_widget.h"
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->pushButton->setAnimationEnable(true);
    ui->pushButton->setContext("Wo ai ni ppp...");
    ui->pushButton->setAlignment(Qt::AlignCenter);
    
    ui->pushButton_2->setContext("Me to me too...");
    ui->pushButton_2->setAlignment(Qt::AlignHCenter|Qt::AlignBottom);
}

Widget::~Widget()
{
    delete ui;
}
