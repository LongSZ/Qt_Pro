#ifndef CURLDUANDIANXUCHUAN_H
#define CURLDUANDIANXUCHUAN_H

#include <QWidget>
#include <QThread>
#include <QFileInfo>
#include <curl.h>
#include <iostream>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class CurlDuanDianXuChuan; }
QT_END_NAMESPACE

class CurlDuanDianXuChuan;

class DownloadThread : public QThread
{
    Q_OBJECT
public:
    DownloadThread();
    
    CurlDuanDianXuChuan *getCurlDuanDianXuChuan() const;
    void setCurlDuanDianXuChuan(CurlDuanDianXuChuan *value);
    
protected:
    void run() override;
    
private:
    CurlDuanDianXuChuan *curlDuanDianXuChuan;
};

class CurlDuanDianXuChuan : public QWidget
{
    Q_OBJECT
    
public:
    CurlDuanDianXuChuan(QWidget *parent = nullptr);
    ~CurlDuanDianXuChuan();
    
    void UpdateProgressBar(int value);
    
signals:
    void sigUpdateProgressBar(int value);
    
private slots:
    void on_pushButton_clicked();
    void sltUpdateProgressBar(int value);
    
private:
    Ui::CurlDuanDianXuChuan *ui;
};
#endif // CURLDUANDIANXUCHUAN_H
