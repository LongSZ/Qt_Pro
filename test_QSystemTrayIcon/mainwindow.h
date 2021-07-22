#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
protected:
    void closeEvent(QCloseEvent *event);                        //由于要关闭窗口变为隐藏至托盘图标，所以要重写close事件
    
private slots:
    void activate_system_tray_icon(QSystemTrayIcon::ActivationReason reason);
    
private:
    Ui::MainWindow *ui;
    
    QSystemTrayIcon *system_tray_icon;
};
#endif // MAINWINDOW_H
