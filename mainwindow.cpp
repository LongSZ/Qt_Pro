#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QComboBox>
#include <QCompleter>
#include <iostream>
using namespace std;

#include "combobox.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    ComboBox *cb = new ComboBox(this);
    cb->addItem(QStringLiteral("三星"));
    cb->addItem(QStringLiteral("三星你"));
    cb->addItem(QStringLiteral("三星你一"));
    cb->addItem(QStringLiteral("三星你一的在"));
    cb->addItem(QStringLiteral("三星你好"));
    cb->addItem(QStringLiteral("三星你好吗我不好"));
    cb->addItem(QStringLiteral("三星你好吗"));
    cb->addItem(QStringLiteral("联想"));
    cb->addItem(QStringLiteral("联想你"));
    cb->addItem(QStringLiteral("联想你好不"));
    cb->addItem(QStringLiteral("联想你好"));
    cb->addItem(QStringLiteral("戴尔"));
    cb->addItem(QStringLiteral("苹果"));
    ui->verticalLayout->addWidget(cb);
    
    //当前
    QStringList word_list1;
    for (int i = 0; i < ui->comboBox->count(); i++) {
        QString txt = ui->comboBox->itemText(i);
        cout << i << " --> " << txt.toLocal8Bit().toStdString() << endl;
        word_list1 << txt;
    }
    QCompleter *completer1 = new QCompleter(word_list1, this);
    ui->comboBox->setCompleter(completer1); 
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_comboBox_editTextChanged(const QString &arg1)
{
//    QStringList word_list;
//    for (int i = 0; i < ui->comboBox->count(); i++) {
//        QString txt = ui->comboBox->itemText(i);
//        cout << i << " --> " << txt.toLocal8Bit().toStdString() << endl;
//        word_list << txt;
//    }
//    QCompleter *completer = new QCompleter(word_list, this);
//    ui->comboBox->setCompleter(completer); 
    cout << "current index" << ui->comboBox->currentIndex() << endl;
}
