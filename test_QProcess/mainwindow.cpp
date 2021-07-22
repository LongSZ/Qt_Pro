#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    process = new QProcess();
    connect(process, SIGNAL(started()), SLOT(started()));
    connect(process, SIGNAL(stateChanged(QProcess::ProcessState)), SLOT(stateChanged(QProcess::ProcessState )));
    connect(process, SIGNAL(finished(int, QProcess::ExitStatus)), SLOT(finished(int, QProcess::ExitStatus)));
    connect(process, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadStandardOutput()));
    
    QString program = "adb shell ls /sdcard/";
    process->start(program);
    cout << "program = " << program.toStdString() << endl;
    if(process->waitForStarted()) {
        qDebug() << "Sucess!";
        if (process->waitForFinished()) {
            qDebug() << "Finished!";
        }
    }
    else {
        qDebug() << "Failure!";
    }
    //process->startDetached(QString("cmd"), list);
}

void MainWindow::started()
{
    qDebug() << "Started!";
}

void MainWindow::stateChanged(QProcess::ProcessState state)
{
    qDebug() << "show state:";
    switch(state) {
        case QProcess::NotRunning:
            qDebug()<<"Not Running";
            break;
        case QProcess::Starting:
            qDebug()<<"Starting";
            break;
        case QProcess::Running:
            qDebug()<<"Running";
            break;
        default:
            qDebug()<<"otherState";
            break;
    }
}

void MainWindow::finished(int exitCode, QProcess::ExitStatus exitStatus)
{
    qDebug()<<"finished";
    qDebug() << exitCode;// 被调用程序的main返回的int
    qDebug() << exitStatus;// QProcess::ExitStatus(NormalExit)
    qDebug() << "finished-output-readAll:";
    qDebug() << QString::fromLocal8Bit(process->readAll());
    qDebug() << "finished-output-readAllStandardOutput:";
    qDebug() << QString::fromLocal8Bit(process->readAllStandardOutput());
 
}

void MainWindow::readyRead()
{
    qDebug() << "readyRead-readAll:";
    qDebug() << QString::fromLocal8Bit(process->readAll());// "hello it is ok!"
    qDebug() << "readyRead-readAllStandardOutput:";
    qDebug() << QString::fromLocal8Bit(process->readAllStandardOutput());// ""
}

void MainWindow::readyReadStandardOutput()
{
    qDebug() << "readyReadStandardOutput-readAll:";
    qDebug() << QString::fromLocal8Bit(process->readAll());// ""
    qDebug() << "readyReadStandardOutput-readAllStandardOutput:";
    qDebug() << QString::fromLocal8Bit(process->readAllStandardOutput());// ""
}

MainWindow::~MainWindow()
{
    delete ui;
}



