#include "logistic.h"
#include <QDebug>
#include <QString>

Logistic::Logistic(QWidget *parent, double *point_x, double *point_y, int count)
    : QWidget(parent)
{
    qDebug()<<"Logistic";
    int n = count;
    double x[n],y[n];
    for(int i= 0;i<n;i++)
    {
        x[i] = point_x[i];
        y[i] = point_y[i];
    }

    maxX = x[n-1];

    Curve = new CurveFitter(x,y,n);
    Curve->doFit();      //计算得出各个系数
    Curve->print();
    qDebug()<<"Curve";
    pVal = Curve->getCoeff();   //系数数组
    qDebug()<<"pVal";
    my_x = new double [500];
    my_y = new double [500];
    CalculatePoints();          //计算画图所需各点的坐标
//    QVector <double> key(500);
//    QVector <double> value(500);

//    for(int i=0;i<500;i++){
//        key[i]=my_x[i];
//        value[i]=my_y[i];
//    }

//    double r = Curve.getRSquared();

//    QCustomPlot *customPlot = new QCustomPlot(this);
//    customPlot->setFixedSize(1000,800);
//    customPlot->addGraph();
//    customPlot->graph(0)->setData(key,value);//添加数据
//    customPlot->graph(0)->setName("多项式拟合");

//    //设置完数据后可以对x，y轴进行设置
//    customPlot->xAxis->setLabel("浓度");
//    customPlot->yAxis->setLabel("发光值");
//    //或者设置x，y轴的范围
//    customPlot->xAxis->setRange(0,5000);
//    customPlot->yAxis->setRange(0,2500000);

//    //在第二张图上描点
//    QVector <double> key_x(6);
//    QVector <double> value_y(6);

//    for(int i=0;i<6;i++){
//        key_x[i]=x[i];
//        value_y[i]=y[i];
//    }

//    //添加 点
//    customPlot->addGraph();
//    customPlot->graph(1)->setPen(QColor(50, 50, 50, 255));
//    customPlot->graph(1)->setLineStyle(QCPGraph::lsNone);
//    customPlot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
//    customPlot->graph(1)->setName("Some random data around\na quadratic function");

//    customPlot->graph(1)->setData(key_x,value_y);


////  setSubGridVisible(true);//设置是否显示自网格线   在qcustomplot.cpp 中修改，默认为false 已改为true；

//    label = new QLabel(customPlot);
//    QString name;
//    QString str = "(%1-%2)/(1+(x/%3)^%4)+%5";
//    name = str.arg(toString(pVal[0]),toString(pVal[3]),toString(pVal[2]),toString(pVal[1]),toString(pVal[3]));

//    qDebug()<<toString(pVal[0]);
//    qDebug()<<toString(pVal[1]);
//    qDebug()<<toString(pVal[2]);
//    qDebug()<<toString(pVal[3]);

//    label->setText(name+"\n"+"R² = "+toString(r));
//    label->setFont(QFont("宋体",12));         //设置字体
//    label->setGeometry(340,470,800,40);     //调整位置

}

double* Logistic::getX()         //画图所需点的X坐标
{
    return my_x;
}
double* Logistic::getY()         //画图所需点的X坐标
{
    return my_y;
}

double Logistic::getR()      //获取相关系数
{
    return Curve->getR();
}
double* Logistic::getCoefficient()        //获取函数系数数组
{
    return Curve->getCoeff();
}

void Logistic::CalculatePoints()
{
    for(int i=0;i<500;i++){
        my_x[i]=i*maxX*1.1/500;
        my_y[i]=(pVal[0]-pVal[3])/(1+pow(my_x[i]/pVal[2],pVal[1]))+pVal[3];
    }
}

QString Logistic::toString(double b){return QString::number(b,10,6);}
QString Logistic::toString(int i){return QString::number(i, 10);}
QString Logistic::toString(float f){return QString::number(f, 10,6);}

Logistic::~Logistic()
{

}
