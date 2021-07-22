#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     
//    ui->dockWidget->setTitleBarWidget(NULL);
//    ui->dockWidget->setWindowFlags(Qt::FramelessWindowHint);
    
    //移除titlebar
//    QWidget* lTitleBar = ui->dockWidget->titleBarWidget();
//    QWidget* lEmptyWidget = new QWidget();
//    ui->dockWidget->setTitleBarWidget(lEmptyWidget);
//    delete lTitleBar;
    
    //移除中间widget
    
}

MainWindow::~MainWindow()
{
    delete ui;
}

