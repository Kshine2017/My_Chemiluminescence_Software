#include "temperatureplot.h"
#define LENGTH_NUM 30
#define TEMP_H 50
#define TEMP_L 5

#define WEIDGET_W  200
#define WEIDGET_H  230
TemperaturePlot::TemperaturePlot(QWidget *parent) : QWidget(parent)
{

    //Widget_main =new QWidget(this);

    Storge =new double[LENGTH_NUM];
    memset(Storge,0,LENGTH_NUM);//清空

    temPIC = new QCustomPlot(this);
    //位置和尺寸
    temPIC->setGeometry(15,40,WEIDGET_W,WEIDGET_H); //
    //temPIC->setStyleSheet("background-color:rgb(91,160,175);");
    //背景图片（不使用背景图片，之间用渐变色去隐藏）
//    QPixmap pix;
//    pix.load(":/picture/mainwindow/temperatureBackGround.png");
//    temPIC->setBackground(pix,true);

    QLinearGradient plotGradient(QPointF(0, 0), QPointF(0, WEIDGET_H));
//93,155,167 //同一水平位置 画图板测量rgb（这里不要随便改）//102 ,164,176
    plotGradient.setColorAt(0,QColor(102 ,164,176));
//28,90,103 //39 101 114
    plotGradient.setColorAt(1,QColor(39,101,114));
    temPIC->setBackground(plotGradient);




    //X和Y轴
//  temPIC->xAxis->setLabel("时间/min");
//  temPIC->xAxis->setLabelColor(Qt::white);
    temPIC->xAxis->setRange(0,LENGTH_NUM);
    temPIC->xAxis->grid()->setSubGridVisible(false);
    temPIC->xAxis->setBasePen(QPen(QColor(255,255,255)));
    temPIC->xAxis->setTickLabelColor(QColor(255,255,255));
    temPIC->xAxis->setTickPen(QPen(QColor(255,255,255)));
    temPIC->xAxis->setSubTickPen(QPen(QColor(255,255,255)));

//    temPIC->yAxis->setLabel("温度/℃");
//    temPIC->yAxis->setLabelColor(Qt::white);
    temPIC->yAxis->setRange(TEMP_L,TEMP_H);
    temPIC->yAxis->grid()->setSubGridVisible(false);
    temPIC->yAxis->setBasePen(QPen(QColor(255,255,255)));
    temPIC->yAxis->setTickLabelColor(QColor(255,255,255));
    temPIC->yAxis->setTickPen(QPen(QColor(255,255,255)));
    temPIC->yAxis->setSubTickPen(QPen(QColor(255,255,255)));

    //设置可缩放，拖拽
    // temPIC->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |QCP::iSelectLegend | QCP::iSelectPlottables);



}

TemperaturePlot::~TemperaturePlot()
{
//析构
}

void TemperaturePlot::insertData(double tem)
{
    QVector<double> Xstorge(LENGTH_NUM);
    QVector<double> Ystorge(LENGTH_NUM);
    //更新数据（前插后弃）
    for(int i=0;i < LENGTH_NUM - 1 ;i++)
    {
        Storge[LENGTH_NUM-1-i]=Storge[LENGTH_NUM-2-i];

    }
    Storge[0]=tem;//放入最新的数据

    //装载数据
    for(int i=0;i<30;i++)
    {
        Xstorge[i]=i;
        Ystorge[i]=Storge[i];
    }

    //添加曲线
    if(temPIC->graphCount()<1)temPIC->addGraph();
    QPen pen;
    pen.setColor(QColor(255, 200, 20, 200));
    pen.setStyle(Qt::DashLine);//虚线
    pen.setWidthF(2.0);//2.5

    temPIC->graph(0)->setPen(pen);
    //temPIC->graph(0)->setLineStyle(QCPGraph::lsLine);


    // 设置渐变色
        QLinearGradient linear(QPointF(0, 234), QPointF(0, 0));
        linear.setColorAt(0, Qt::blue);
        linear.setColorAt(0.5,Qt::yellow);
        linear.setColorAt(1, Qt::red);
     temPIC->graph(0)->setBrush(QBrush(linear));
    //temPIC->graph(0)->setBrush(QBrush(QColor(255,200,20,160)));//填充 rgb+不透明度
    //temPIC->graph(0)->setScatterStyle(QCPScatterStyle(QPixmap(":/C:/Users/Administrator/Desktop/3.png")));
    temPIC->graph(0)->setData(Xstorge,Ystorge);
    temPIC->replot();
}
