#ifndef QTABOUTCHART_H
#define QTABOUTCHART_H

#include <QWidget>
#include <QtCharts/QLineSeries>
#include <QVBoxlayout>
#include <QHBoxlayout>
#include <QtCharts/QValueAxis>
#include <QTimer>
#include <QString>
QT_CHARTS_USE_NAMESPACE

#include "MyQChartSpline.h"
#include "MyQChartLine.h"
#include "MyQChartBar.h"
#include "MyQChartPie.h"

class QtAboutChart : public QWidget
{
    Q_OBJECT
public:
    QtAboutChart();
    QtAboutChart(QWidget *parent = Q_NULLPTR);
    
    void InitLayout();
    void SetTimer(const int mdelay);    //设置定时时间（ms）

    //template <typename A_Val> void refreshDate(A_Val valX, A_Val valY, A_Val incrementX, const int num);

public slots:
    void slotsTimerDeal();

private:
    //QChart *m_chart;
    //QChartView *m_chartView;
    
    MyQChartBar *m_Mychart;
    MyQChartLine *m_Mychart1;
    MyQChartPie *m_Mychart2;
    MyQChartSpline *m_Mychart3;

    QLineSeries *series;
    QVBoxLayout *m_layout;
    QHBoxLayout *m_hlayout1;
    QHBoxLayout *m_hlayout2;

    QValueAxis *m_axisX;
    QValueAxis *m_axisY;

    QTimer *timer;
};

#endif // QTABOUTCHART_H
