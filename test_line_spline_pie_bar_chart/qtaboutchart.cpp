#include "qtaboutchart.h"
//#include <QDebug>

QtAboutChart::QtAboutChart()
{
    
}

QtAboutChart::QtAboutChart(QWidget *parent)
    : QWidget(parent)
{
    m_Mychart = new MyQChartBar;
    m_Mychart1 = new MyQChartLine;
    m_Mychart2 = new MyQChartPie;
    m_Mychart3 = new MyQChartSpline;

    InitLayout();

    m_Mychart->InitAx();
    m_Mychart1->InitAx();
    m_Mychart2->InitAx();
    m_Mychart3->InitAx();

    SetTimer(1000);
}
void QtAboutChart::SetTimer(const int mdelay)
{
    timer = NULL;
    timer = new QTimer();
    timer->setInterval(mdelay);
    connect(timer, SIGNAL(timeout()), this, SLOT(slotsTimerDeal()));
    timer->start();
}

void QtAboutChart::InitLayout()
{
    //指针置空
    m_layout = NULL;

    m_layout = new QVBoxLayout();
    m_hlayout1 = new QHBoxLayout();
    m_hlayout2 = new QHBoxLayout();

    m_Mychart->setTitlrText(QString("test1"));
    m_Mychart1->setTitlrText(QString("test2"));
    m_Mychart2->setTitlrText(QString("test3"));
    m_Mychart3->setTitlrText(QString("test4"));

    m_hlayout1->addWidget(m_Mychart->getView());
    m_hlayout1->addWidget(m_Mychart1->getView());
    m_hlayout2->addWidget(m_Mychart2->getView());
    m_hlayout2->addWidget(m_Mychart3->getView());

    m_layout->addLayout(m_hlayout1);
    m_layout->addLayout(m_hlayout2);


    //m_layout->addWidget(m_Mychart->getView());

    setLayout(m_layout);
}

void QtAboutChart::slotsTimerDeal()
{
    //qDebug() << i <<"up date!!";
    
    m_Mychart1->refreshAx();                        //曲线图刷新
    m_Mychart->refreshAx();                            //柱状图刷新
    m_Mychart2->refreshAx();                        //饼状图刷新
    m_Mychart3->refreshAx();


    //m_Mychart->m_axisX->setRange(0, i);
    //m_Mychart->m_axisY->setRange(0, i);
}
