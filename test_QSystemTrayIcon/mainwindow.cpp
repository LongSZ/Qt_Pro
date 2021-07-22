#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    system_tray_icon = new QSystemTrayIcon;
    QIcon icon = QIcon(":/LJTools.ico");
    system_tray_icon->setIcon(icon);
    system_tray_icon->setToolTip("A QSystemTrayIcon Example\nCreated by LiuHongWei\nFor Fuck!");
    QString titlec = tr("Hello");
    QString textc = QString::fromLocal8Bit("Hello QT?");
    system_tray_icon->showMessage(titlec, textc, QSystemTrayIcon::Information, 5000);
    
    //给QSystemTrayIcon添加槽函数
    connect(system_tray_icon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(activate_system_tray_icon(QSystemTrayIcon::ActivationReason)));
    
    // 初始化托盘菜单及功能
    QMenu *menu = new QMenu;                                                            //初始化菜单
    
    QAction *show_normal = new QAction;                                                 //初始化恢复窗口
    show_normal->setText(QStringLiteral("显示窗口"));
    QObject::connect(show_normal, SIGNAL(triggered()), this, SLOT(show()));             //菜单中的显示窗口，单击连接显示窗口
    menu->addAction(show_normal);
    
    QAction *quit = new QAction;                                                        //初始化退出程序
    quit->setText(QStringLiteral("退出程序"));
    //qApp，是Qt自带的demo中的知识点，查了一下文档，qApp是Qt中所有app的指针，关闭它就可以关闭当前的程序
    //之所以不用this->close()，是由于软件要求关闭改为最小化到托盘，所以close()的功能已经不再是关闭窗口的功能，所以要另寻方法
    QObject::connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));                    //菜单中的退出程序，单击连接退出
    //connect(quit, SIGNAL(triggered()), this, SLOT(close()));
    menu->addAction(quit);
    
    //***将定义好的菜单加入托盘的菜单模块中***
    system_tray_icon->setContextMenu(menu);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (ui->checkBox_min_to_systemtray->isChecked()) {              //如果是要退出到系统托盘
        hide();                             //隐藏窗口
        event->ignore();                    //忽略关闭事件
        system_tray_icon->show();
    }
}

void MainWindow::activate_system_tray_icon(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason){
        case QSystemTrayIcon::Trigger:                          //单击托盘图标
            //show();
            break;
        case QSystemTrayIcon::DoubleClick:                      //双击托盘图标,后显示主程序窗口
            show();
            break;
    case QSystemTrayIcon::Context:                              //右键、等同于显示右键菜单
            //show();
            break;
        default:
            break;
    }
}
