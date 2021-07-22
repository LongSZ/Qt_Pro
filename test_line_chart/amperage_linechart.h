#ifndef AMPERAGE_LINECHART_H
#define AMPERAGE_LINECHART_H

#include <QWidget>
#include <QTimer>
#include <QTime>
#include <QVector>
#include <QHBoxLayout>
#include <QtMath>

#include <QChartView>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QtCharts/QSplineSeries>
QT_CHARTS_USE_NAMESPACE

#include "myqchartview.h"

#include <iostream>
#include <vector>
#include <random>
using namespace std;

namespace Ui {
class Amperage_LineChart;
}

class Amperage_LineChart : public QWidget
{
    Q_OBJECT
    
public:
    explicit Amperage_LineChart(QWidget *parent = nullptr);
    ~Amperage_LineChart();
    
public slots:
    void timer1Slot();
    
private:
    Ui::Amperage_LineChart *ui;
    
    QSplineSeries *spY1;
    QSplineSeries *spY2;
    
    QVector<QPointF> vecKv;
    QVector<QPointF> vecVacc;
};

#endif // AMPERAGE_LINECHART_H
