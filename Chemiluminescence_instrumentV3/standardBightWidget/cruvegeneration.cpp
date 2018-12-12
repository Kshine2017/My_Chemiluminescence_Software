#include "cruvegeneration.h"
#include <stdio.h>



CruveGeneration::CruveGeneration(QWidget *parent, double *x, double *y, int Pointcount, int coefficientCount,int type):QWidget(parent)
{
    point_x = new  double[Pointcount];  //{0,50,200,500,2000,5000};
    point_y = new  double[Pointcount];

    pointCount = Pointcount;
    coefficient_count =  coefficientCount;

    memcpy(point_x,x,sizeof(double)*Pointcount);         //传入 画图所需点的X坐标
    memcpy(point_y,y,sizeof(double)*Pointcount);         //传入 画图所需点的Y坐标



    if(type == LOGLOGISTIC)
    {
        init();             //初始化坐标轴以及点的坐标
        addCruve_LogLogistic();            //增加LOG-Logistic拟合曲线
    }
    else if(type == DUOXIANGSHI)
    {

        init();             //初始化坐标轴以及点的坐标
        addCruve_Duoxiangshi();         //增加多项式拟合曲线
    }
    else if(type == LOGISTIC)
    {
        init();             //初始化坐标轴以及点的坐标
        addCruve_Logistic();            //增加Logistic-四参数拟合曲线
    }
    else if(type == LOGLINEARFIT)
    {
        qDebug()<<"------------------------------"<<1;
        customPlot = new QCustomPlot(this);
        qDebug()<<"------------------------------"<<2;
        customPlot->setFixedSize(1200,800);
        qDebug()<<"------------------------------"<<3;
        //设置完数据后可以对x，y轴进行设置
        customPlot->xAxis->setLabel("浓度对数值");
        customPlot->yAxis->setLabel("发光值去底对数值");
        qDebug()<<"------------------------------"<<4;

        addCruve_LogLinearFit();        //增加对数线性拟合拟合曲线
        qDebug()<<"------------------------------"<<5;

        //或者设置x，y轴的范围
        customPlot->xAxis->setRange(0,linear_fit->newX[linear_fit->newCount-1]*1.2);
        customPlot->yAxis->setRange(0,linear_fit->newY[linear_fit->newCount-1]*1.2);
        qDebug()<<"------------------------------"<<6;

        //在第一张图上描点
        QVector <double> key_x(linear_fit->newCount);
        QVector <double> value_y(linear_fit->newCount);
        qDebug()<<"------------------------------"<<7;

        for(int i=0;i<linear_fit->newCount;i++)
        {
            key_x[i] = linear_fit->newX[i];
            value_y[i] = linear_fit->newY[i];
        }
        qDebug()<<"------------------------------"<<8;


        customPlot->addGraph();
        customPlot->graph(1)->setData(key_x,value_y);//添加数据
        customPlot->graph(1)->setPen(QColor(50, 50, 50, 255));
        customPlot->graph(1)->setLineStyle(QCPGraph::lsNone);
        customPlot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 6));
        customPlot->graph(1)->setName("点的位置");
        qDebug()<<"------------------------------"<<9;

    }

//    setCruveVisible_Duoxiangshi(false);
//    setCruveVisible_Logistic(false);
//    setCruveVisible_LogLinearFit(false);
//    setCruveVisible_Log_Logist(false);

}


void CruveGeneration::init()
{
    qDebug()<<"CruveGeneration::init()";
    customPlot = new QCustomPlot(this);
    customPlot->setFixedSize(1200,800);
    customPlot->addGraph();
    //设置完数据后可以对x，y轴进行设置
    customPlot->xAxis->setLabel("浓度");
    customPlot->yAxis->setLabel("发光值");
    //或者设置x，y轴的范围
    customPlot->xAxis->setRange(0,point_x[pointCount-1]*1.2);
    customPlot->yAxis->setRange(0,point_y[pointCount-1]*1.2);

    //在第一张图上描点
    QVector <double> key_x(pointCount);
    QVector <double> value_y(pointCount);

    for(int i=0;i<pointCount;i++)
    {
        key_x[i] = point_x[i];
        value_y[i] = point_y[i];
    }

    customPlot->graph(0)->setData(key_x,value_y);//添加数据
    customPlot->graph(0)->setPen(QColor(50, 50, 50, 255));
    customPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
    customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 6));
    customPlot->graph(0)->setName("点的位置");
}
void CruveGeneration::addCruve_Duoxiangshi()//添加多项式曲线
{
    duoxiangshi = new DuoXiangShi(point_x,point_y,pointCount,coefficient_count);
    double *x = duoxiangshi->getX();     //获取多项式函数计算出的500个点X坐标
    double *y = duoxiangshi->getY();     //获取多项式函数计算出的500个点Y坐标

    QVector <double> key_dxs(500);                  //将点的坐标从double型转为QVector
    QVector <double> value_dxs(500);
    for(int i = 0;i < 500;i++)
    {
        key_dxs[i] = x[i];
        value_dxs[i] = y[i];
    }

    customPlot->addGraph();
    customPlot->graph(1)->setData(key_dxs,value_dxs);//添加数据
    customPlot->graph(1)->setPen(QColor("cyan"));
    customPlot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDiamond, 1));
}
void CruveGeneration::addCruve_Logistic()               //添加Logistic-四参数曲线
{
    logistic = new Logistic(this,point_x,point_y,pointCount);
    double *x = logistic->getX();     //获取Logistic-四参数函数计算出的500个点X坐标
    double *y = logistic->getY();     //获取Logistic-四参数函数计算出的500个点Y坐标

    QVector <double> key_logistic(500);                  //将点的坐标从double型转为QVector
    QVector <double> value_logistic(500);
    for(int i = 0;i < 500;i++)
    {
        key_logistic[i] = x[i];
        value_logistic[i] = y[i];
    }

    customPlot->addGraph();
    customPlot->graph(1)->setData(key_logistic,value_logistic);//添加数据
    customPlot->graph(1)->setPen(QColor("darkBlue"));
    //    customPlot->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDiamond, 1));
}

/**
 * @brief CruveGeneration::addCruve_LogLinearFit
 *  对数线性拟合
 */
void CruveGeneration::addCruve_LogLinearFit()
{
    linear_fit = new Linnear_Fit(point_x,point_y,pointCount);
    double *x = linear_fit->getX();     //获取对数线性拟合函数计算出的500个点X坐标
    double *y = linear_fit->getY();     //获取对数线性拟合函数计算出的500个点Y坐标

    QVector <double> key_linear_fit(500);                  //将点的坐标从double型转为QVector
    QVector <double> value_linear_fit(500);
    for(int i = 0;i < 500;i++)
    {
        key_linear_fit[i] = x[i];
        value_linear_fit[i] = y[i];
    }

    customPlot->addGraph();
    customPlot->graph(0)->setData(key_linear_fit,value_linear_fit);//添加数据
    customPlot->graph(0)->setPen(QColor("darkCyan"));
}

void CruveGeneration::addCruve_LogLogistic()
{
    lr = new LR(point_x,point_y,pointCount);
    double *x = lr->getX();     //获取对数线性拟合函数计算出的500个点X坐标
    double *y = lr->getY();     //获取对数线性拟合函数计算出的500个点Y坐标

    QVector <double> key_lr(500);                  //将点的坐标从double型转为QVector
    QVector <double> value_lr(500);
    for(int i = 0;i < 500;i++)
    {
        key_lr[i] = x[i];
        value_lr[i] = y[i];
    }

    customPlot->addGraph();
    customPlot->graph(1)->setData(key_lr,value_lr);//添加数据
    customPlot->graph(1)->setPen(QColor("red"));
}

void CruveGeneration::setCruveVisible_Duoxiangshi(bool b)       //设置多项式曲线是否可视
{
    qDebug()<<"多项式曲线--------"<<b;
    customPlot->graph(1)->setVisible(b);

}
void CruveGeneration::setCruveVisible_Logistic(bool b)      //设置Logistic-四参数曲线是否可视
{
    qDebug()<<"Logistic-四参数曲线--------"<<b;
    customPlot->graph(2)->setVisible(b);
}


void CruveGeneration::setCruveVisible_Log_Logist(bool b)       //设置Log_Logist曲线是否可视
{
    qDebug()<<"Log_Logist曲线--------"<<b;
    customPlot->graph(4)->setVisible(b);

}
void CruveGeneration::setCruveVisible_Ln(bool b)       //设置Ln曲线是否可视
{

}

void CruveGeneration::setCruveVisible_LogLinearFit(bool b)  //设置对数线性拟合曲线是否可视
{
    qDebug()<<"对数线性拟合曲线--------"<<b;
    customPlot->graph(3)->setVisible(b);
}
/**
 * @brief setCruveToBold
 * @param i     曲线的坐标
 * @param size  设置的尺寸
 */
void CruveGeneration::setCruveSize(int i,int size)         //设置曲线粗细
{
    customPlot->graph(i)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDiamond, size));
}
