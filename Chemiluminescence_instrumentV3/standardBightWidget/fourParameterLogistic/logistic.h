#ifndef LOGISTIC_H
#define LOGISTIC_H

#include <QWidget>
#include <QLabel>
#include "CouveFitter.h"

class Logistic : public QWidget
{
    Q_OBJECT

public:
    Logistic(QWidget *parent = 0, double *point_x = NULL, double *point_y = NULL, int count = 0);
    ~Logistic();

    CurveFitter *Curve;

    double *my_x;       //画图所需点的x坐标
    double *my_y;       //画图所需点的y坐标

    double *pVal;       //未知数

    double maxX;        //浓度最大值

    double* getX();         //画图所需点的X坐标
    double* getY();         //画图所需点的X坐标

    double getR();      //获取相关系数
    double* getCoefficient();        //获取函数系数数组

    void CalculatePoints();         //计算各点
    QString toString(double b);         //转成QString
    QString toString(int i);
    QString toString(float f);

    QLabel *label;
};

#endif // LOGISTIC_H
