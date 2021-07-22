#ifndef MYQCHARTVIEW_H
#define MYQCHARTVIEW_H

#include <QObject>

#include <QChartView>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QtCharts/QSplineSeries>
QT_CHARTS_USE_NAMESPACE

#include <iostream>
#include <vector>
#include <random>
using namespace std;

class MyQChartView : public QChartView
{
    Q_OBJECT
public:
    MyQChartView();
    explicit MyQChartView(QWidget *parent = 0);
    
    void saveAxisRange();                           //保存原始位置
    
protected:
    void MyQChartView::keyPressEvent(QKeyEvent *event);
    void MyQChartView::keyReleaseEvent(QKeyEvent *event);
    
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    
    void wheelEvent(QWheelEvent *event);
    
    bool m_isPress;
    QGraphicsSimpleTextItem *m_coordItem;
    qreal m_xMin, m_xMax;
    qreal m_yMin, m_yMax;
    QPoint m_lastPoint;
    bool m_ctrlPress;
    bool m_alreadySaveRange;
};

#endif // MYQCHARTVIEW_H
