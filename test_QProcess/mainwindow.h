#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QDebug>

#include <iostream>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
public slots:
    void started();
    void finished(int exitCode, QProcess::ExitStatus exitStatus);
    void stateChanged(QProcess::ProcessState state);
    void readyRead();
    void readyReadStandardOutput();
    
private:
    Ui::MainWindow *ui;
    
    QProcess *process;
};
#endif // MAINWINDOW_H
