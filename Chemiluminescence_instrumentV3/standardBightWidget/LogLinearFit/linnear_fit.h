#ifndef LINNEAR_FIT_H
#define LINNEAR_FIT_H
#include <QtCore/qmath.h>
#include "standardBightWidget/polynomial/duoxiangshi.h"

class Linnear_Fit
{
public:
    Linnear_Fit(double *x_val,double *y_val,double num);

private:

    double *x;  //拟合所需标准品浓度数组
    double *y;  //拟合所需标准品发光值数组
    int count;  //拟合所需标准品数量

    double y_;      //y值的平均值

    double *my_x;       //画图所需点的X坐标
    double *my_y;       //画图所需点的Y坐标
    double maxX;        //浓度最大值

public:
    DuoXiangShi *dxs;   //

    double *newX;   //拟合所需标准品浓度数组----转换后
    double *newY;   //拟合所需标准品发光值数组----转换后
    int newCount;  //拟合所需标准品数量----转换后

    double F0;      //底噪，浓度为0时的发光值
    double *coef;   //曲线拟合参数数组


public:
    double getR();
    double *getcoef();
    double* getX();         //画图所需点的X坐标
    double* getY();         //画图所需点的Y坐标
};

#endif // LINNEAR_FIT_H
