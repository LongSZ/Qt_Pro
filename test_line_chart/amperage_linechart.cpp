#include "amperage_linechart.h"
#include "ui_amperage_linechart.h"

const int MaxSample = 20;

Amperage_LineChart::Amperage_LineChart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Amperage_LineChart)
{
    ui->setupUi(this);
    
    QValueAxis *vaX = new QValueAxis();
    vaX->setRange(0, MaxSample);
    vaX->setTickCount(10);
    vaX->setLabelsColor(QColor(0, 255, 0));
    vaX->setTitleText("Sample-Points");
    
    QValueAxis *vaY1 = new QValueAxis();
    vaY1->setRange(0, 200);
    vaY1->setTickCount(5);
    vaY1->setLabelsColor(QColor(255,0, 0));
    vaY1->setTitleText("Voltage-Kv");
    
    QValueAxis *vaY2 = new QValueAxis();
    vaY2->setRange(0, 10);
    vaY2->setTickCount(5);
    vaY2->setLabelsColor(QColor(0, 0, 255));
    vaY2->setTitleText("Penning-V");
    
    spY1 = new QSplineSeries();
    spY2 = new QSplineSeries();
    
    MyQChartView *mChart = new MyQChartView(this);
    mChart->setEnabled(true);
    mChart->chart()->setTitle("Kv-Vacuum");
    mChart->chart()->legend()->hide();
    mChart->chart()->setTheme(QtCharts::QChart::ChartTheme::ChartThemeDark);
    mChart->chart()->addAxis(vaX, Qt::AlignBottom);
    mChart->chart()->addAxis(vaY1, Qt::AlignLeft);
    mChart->chart()->addAxis(vaY2, Qt::AlignRight);
    mChart->chart()->addSeries(spY1);
    mChart->chart()->addSeries(spY2);
    
    spY1->attachAxis(vaX);
    spY1->attachAxis(vaY1);
    spY1->setColor(QColor(255, 0, 0));
    spY1->setUseOpenGL();               // 开启openGL加速
    
    spY2->attachAxis(vaX);
    spY2->attachAxis(vaY2);
    spY2->setColor(QColor(0, 0, 255));
    spY2->setUseOpenGL();
    
    ui->gridLayout->addWidget(mChart);
    
    QTimer* timer1 = new QTimer(this);
    timer1->setInterval(1000);
    connect(timer1, SIGNAL(timeout()), this, SLOT(timer1Slot()));
    timer1->start();
}

Amperage_LineChart::~Amperage_LineChart()
{
    delete ui;
}

void Amperage_LineChart::timer1Slot()
{
    static int cnt = 0;
    if (cnt <= MaxSample) {
        float tmp = 85.0 + 85 * sin(cnt * 4 * M_PI / MaxSample);
        vecKv.push_back(QPointF(cnt, tmp));
        tmp = 5 + 5 * cos(cnt * 4 * M_PI / MaxSample);
        vecVacc.push_back(QPointF(cnt, tmp));
    }
    else {
        for (int i = 1; i < MaxSample; ++i) {
            vecKv[i - 1] = QPointF(vecKv[i - 1].x(), vecKv[i].y());
            vecVacc[i - 1] = QPointF(vecVacc[i - 1].x(), vecVacc[i].y());
        }
        float tmp = 85.0 + 85 * sin(cnt * 4 * M_PI / MaxSample);
        vecKv[MaxSample-1] = QPointF(vecKv[MaxSample-1].x(), tmp);
        tmp = 5 + 5 * cos(cnt * 4 * M_PI / MaxSample);
        vecVacc[MaxSample-1] = QPointF(vecVacc[MaxSample-1].x(), tmp);
        
//        if (cnt >= 3 * MaxSample) {// 计数器复位
//            cnt = 0;
//            vecKv.clear();
//            vecVacc.clear();
//        }
    }
    cnt++;
    
    spY1->replace(vecKv);
    spY2->replace(vecVacc);
}
