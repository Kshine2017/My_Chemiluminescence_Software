#ifndef CRUVEGENERATION_H
#define CRUVEGENERATION_H

#include <QWidget>
#include "qcustomplot.h"
#include <QString>
#include <QDebug>
#include "polynomial/duoxiangshi.h"
#include "fourParameterLogistic/logistic.h"
#include "LogLinearFit/linnear_fit.h"
#include "LogLogistic/lr.h"
#include "data/util.h"

class CruveGeneration : public QWidget
{
    Q_OBJECT
public:
    explicit CruveGeneration(QWidget *parent = 0, double *x = NULL, double *y = NULL, int Pointcount = 0, int coefficientCount = 4, int type = -1);

    QCustomPlot *customPlot;        //画图的控件
    DuoXiangShi *duoxiangshi;       //多项式拟合
    Logistic *logistic;             //logistic-四参数拟合
    Linnear_Fit *linear_fit;        //对数线性拟合
    LR *lr;                         //Log-Logistic拟合
private:
    int pointCount;           //参与拟合的点数
    int coefficient_count;   //系数个数，最高次数+1

    double *point_x;        //传入点x坐标
    double *point_y;        //传入点y坐标

    double R_duoxiangshi;       //多项式相关系数
    double R_logistic;       //四参数相关系数

    double *coefficient_duoxiangshi;        //多项式函数 系数数组
    double *coefficient_logistic;           //四参数函数 系数数组

    void addCruve_Duoxiangshi();            //添加多项式曲线
    void addCruve_Logistic();               //添加Logistic-四参数曲线
    void addCruve_LogLinearFit();           //添加曲线对数线性拟合
    void addCruve_LogLogistic();            //添加Log-Logistic曲线


    void init();            //初始化曲线
public:
    void setCruveVisible_Duoxiangshi(bool b);       //设置多项式曲线是否可视
    void setCruveVisible_Logistic(bool b);       //设置Logistic-四参数曲线是否可视
    void setCruveVisible_Log_Logist(bool b);       //设置Log_Logist曲线是否可视
    void setCruveVisible_Ln(bool b);       //设置Ln曲线是否可视
    void setCruveVisible_LogLinearFit(bool b);      //设置对数线性拟合曲线是否可视
    void setCruveSize(int i,int size);         //设置曲线粗细



signals:

public slots:
};

#endif // CRUVEGENERATION_H
