#include "myqchartline.h"

MyQChartLine::MyQChartLine()
{
    series = new QLineSeries();
}


MyQChartLine::~MyQChartLine()
{
    delete series;
}

void MyQChartLine::InitAx()
{
    MyQChart::InitAx();
    m_chartView->chart()->addSeries(series);
    m_chart->setAxisX(m_axisX, series);
    m_chart->setAxisY(m_axisY, series);
}
void MyQChartLine::InitDate()
{
    i = 0;
}

void MyQChartLine::refreshDate()
{
    i++;
}
void MyQChartLine::refreshAx()
{
    refreshDate();
    addDate<int, float>(i, float(i) / 2);    //曲线图刷新
    if (i <= 20) {
        MyQChart::refrshAx(0, 0, i, (i + 1) / 2);
    }
    else {
        MyQChart::refrshAx(i - 20, ((i + 1) / 2) - 10, i, (i + 1) / 2);
    }
}

template <typename A_Val, typename B_Val>
void MyQChartLine::addDate(A_Val valX, B_Val valY)
{
    series->append(valX, valY);
    m_chartView->chart()->update();
}
