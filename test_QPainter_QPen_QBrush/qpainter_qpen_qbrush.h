#ifndef QPAINTER_QPEN_QBRUSH_H
#define QPAINTER_QPEN_QBRUSH_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class QPainter_QPen_QBrush; }
QT_END_NAMESPACE

class QPainter_QPen_QBrush : public QWidget
{
    Q_OBJECT
    
public:
    QPainter_QPen_QBrush(QWidget *parent = nullptr);
    ~QPainter_QPen_QBrush();
    
protected:
    virtual void paintEvent(QPaintEvent *event);
    
private:
    Ui::QPainter_QPen_QBrush *ui;
};
#endif // QPAINTER_QPEN_QBRUSH_H
