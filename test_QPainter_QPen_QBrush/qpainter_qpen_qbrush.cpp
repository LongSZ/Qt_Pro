#include "qpainter_qpen_qbrush.h"
#include "ui_qpainter_qpen_qbrush.h"

#include <QPainter>

QPainter_QPen_QBrush::QPainter_QPen_QBrush(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QPainter_QPen_QBrush)
{
    ui->setupUi(this);
}

QPainter_QPen_QBrush::~QPainter_QPen_QBrush()
{
    delete ui;
}

void QPainter_QPen_QBrush::paintEvent(QPaintEvent *event)
{
    QPainter p(this);                                           //画家把本this窗体作为画布。
    p.setRenderHints(QPainter::HighQualityAntialiasing
                     | QPainter::Antialiasing
                     | QPainter::TextAntialiasing, true);       //抗锯齿以平滑
    int xLen = width();                                         //画布大小
    int yLen = height();
    
    //step 1：绘制绿色渐变背景
    //QRadialGradient(圆形渐变区域中心，渐变区域半径，聚焦点坐标)
    QRadialGradient gradient(QPointF(250, 250), 250, QPointF(250,250));
    gradient.setColorAt(0.5, QColor(170, 255, 127, 255));       //浅绿色不透明
    gradient.setColorAt(1.0, QColor(170, 255, 127, 0));         //浅绿色全透明
    p.setPen(QColor(170, 255, 127, 150));                       //绿色半透明边框
    p.setBrush(QBrush(gradient));                               //渐变画刷
    p.drawRect(this->rect());
    
    //step 2:绘制横竖两条中心线
    p.setPen(QColor(255, 0, 0, 255));
    p.setBrush(QColor(255, 0, 0, 255));
    p.drawLine(QPoint(xLen / 2, 0), QPoint(xLen / 2, yLen));
    p.drawLine(QPoint(0, xLen/2), QPoint(yLen, xLen/2));
    
    //step 3:绘制3个圆
    p.save();                                                   //移动或旋转坐标系之前，先备份当前坐标系的设置
    p.translate(xLen/2, yLen/2);                                //平移坐标系原点至
    p.setPen(QColor(255, 0, 0, 80));
    p.setBrush(QColor(255, 0, 0, 0));
    p.drawEllipse(QRect(-xLen/2, -yLen/2, xLen, yLen));         //绘制
    p.drawEllipse(QRect(-xLen/4, -yLen/4, xLen/2, yLen/2));
    p.drawEllipse(QRect(-xLen/8, -yLen/8, xLen/4, yLen/4));
    
    //step 4：用多边形绘制飞机
    QPoint uavPixPos;
    qreal uavYaw = 90;                                          //旋转 90 度
    qreal uavSize = 150;                                         //飞机大小
    
    p.setPen(QColor(255, 0, 0, 255));
    p.setBrush(QColor(255, 0, 0, 100));
    p.translate(uavPixPos.x(), -uavPixPos.y());
    p.rotate(uavYaw);
    QPoint points[4] = {QPoint(0, -uavSize), QPoint(-uavSize/1.5, uavSize/1.5), QPoint(0,0), QPoint( uavSize/1.5, uavSize/1.5)};
    p.drawPolygon(points, 4);
    p.setPen(QColor(255, 0, 0, 255));
    p.setBrush(QColor(255, 0, 0, 255));
    p.drawEllipse(QRect(-3, -3, 6, 6));
    p.restore();
    
    //step 5：绘制文字
    p.setPen(QColor(255, 0, 0, 150));
    p.setBrush(QColor(255, 0, 0, 150));
    p.drawText(5, yLen/2, "2m");
    
    p.setPen(QColor(255, 0, 0, 150));
    p.setBrush(QColor(255, 0, 0, 150));
    p.drawText(xLen/4+ 5, yLen/2, "1m");
    
    QWidget::paintEvent(event);
}

