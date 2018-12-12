#include "displaycruve.h"
#include <QSqlQuery>
#include "data/util.h"
#include <QDebug>

DisplayCruve::DisplayCruve(QWidget *parent) : QDialog(parent)
{
    setWindowModality(Qt::ApplicationModal);
    init();
}
/**
 * @brief paint_cruve 画曲线
 * @param name  项目名
 * @param x     浓度 数组
 * @param y     发光值数组
 * @param n     点的个数
 * 浓度与发光值位置需一一对应
 */
void DisplayCruve::paint_cruve(QString name, double *x, double *y, int n)
{
    int count = n;

    /**************根据项目名称获得曲线拟合方式和曲线拟合参数数组***********************/
    QSqlQuery query;
    int generation_type;    //拟合方式
    double *para = new double[6]; //函数参数数组
    QString queryStr = "select GENERATION_TYPE,PARAMETER_ONE,PARAMETER_TWO,PARAMETER_THREE,"
                       "PARAMETER_FOUR,PARAMETER_FIVE,PARAMETER_SIX "
                       "from cruve_parameter "
                       "where REAGENT_CODE = '" + name.mid(1,6) + "' and DEL_FLAG = 0";
    if( !query.exec(queryStr) ){
        QMessageBox::critical(this,tr("错误代码E0027"),tr("错误代码E0027:当前试剂没有做标准曲线定标!"));
        return;
    }
    while(query.next())
    {
        generation_type = query.value("GENERATION_TYPE").toInt();//取出数据库中存储的函数系数
        para[0] = query.value("PARAMETER_ONE").toDouble();
        para[1] = query.value("PARAMETER_TWO").toDouble();
        para[2] = query.value("PARAMETER_THREE").toDouble();
        para[3] = query.value("PARAMETER_FOUR").toDouble();
        para[4] = query.value("PARAMETER_FIVE").toDouble();
        para[5] = query.value("PARAMETER_SIX").toDouble();
    }
    /**********************************************/

    /**********************画点*****************/
    QVector <double> key_x(count);                  //将点的坐标存入QVector
    QVector <double> value_y(count);
    maxX = 0;    //浓度最大值
    maxY = 0;    //发光值最大值
    for(int i = 0;i < count;i++)
    {
        key_x[i] = x[i];
        value_y[i] = y[i];
        if(maxX < x[i])
        {
            maxX = x[i];
        }
        if(maxY < y[i])
        {
            maxY = y[i];
        }
    }
    customPlot->addGraph();
    customPlot->graph(0)->setData(key_x,value_y);//添加数据
    customPlot->graph(0)->setPen(QColor(255,0,0));
    customPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
    customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 6));
    customPlot->graph(0)->setName("点的位置");

    /***************************************/

    /*****************画曲线**********************/
    QVector <double> key(500);                  //将点的坐标存入QVector
    QVector <double> value(500);
    if(generation_type == LOGLINEARFIT)         //对数线性拟合
    {
        for(int i = 0;i < 500;i++)
        {
            maxX = qLn(maxX)/qLn(10);
            key[i] = maxX * 1.2 * i /500;
            value[i] = Util::getYValue(generation_type ,key[i],para); //根据浓度、拟合方式和拟合参数数组求光子值
        }
    }else{
        for(int i = 0;i < 500;i++)
        {
            key[i] = maxX * 1.2 * i /500;
            value[i] = Util::getYValue(generation_type ,key[i],para); //根据浓度、拟合方式和拟合参数数组求光子值
        }
    }

    if(generation_type == LOGLINEARFIT)
    {
        customPlot->xAxis->setLabel("浓度对数值");
        customPlot->yAxis->setLabel("发光值对数值");
    }else{
        customPlot->xAxis->setLabel("浓度");
        customPlot->yAxis->setLabel("发光值");
    }

    customPlot->addGraph();
    customPlot->graph(1)->setData(key,value);//添加数据
    customPlot->graph(1)->setPen(QColor("cyan"));

    /**********************************************/

    customPlot->replot();
}

void DisplayCruve::init()
{
    this->setWindowTitle("标准曲线");
    customPlot = new QCustomPlot(this);
    customPlot->setGeometry(0,0,960,640);
    //设置完数据后可以对x，y轴进行设置
    customPlot->xAxis->setLabel("浓度");
    customPlot->yAxis->setLabel("发光值");
    //或者设置x，y轴的范围
    customPlot->xAxis->setRange(0,maxX*1.3);
    customPlot->yAxis->setRange(0,maxY*1.3);

}
