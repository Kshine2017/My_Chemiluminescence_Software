#include "linnear_fit.h"
#include <QDebug>

/**
 * @brief Linnear_Fit::Linnear_Fit
 * 对数线性拟合
 */

Linnear_Fit::Linnear_Fit(double *x_val,double *y_val,double num)
{
    //将浓度值与发光值进行求对数，再进行线性拟合
    newCount = num - 1;
    newX = new double[newCount];
    newY = new double[newCount];
    for(int i = 0;i < newCount ;i++)
    {
        newX[i] = qLn(x_val[i+1])/qLn(10);
        newY[i] = qLn(y_val[i+1] - y_val[0])/qLn(10);
    }

    //原始数据，转换后求得线性拟合方程，再进行转换，可得
    count = num;
    x = new double[count];
    y = new double[count];
    for(int i=0;i<count;i++)
    {
        x[i] = x_val[i];
        y[i] = y_val[i];
        y_ += y[i];
    }
    y_ = y_/count;          //y值的平均值

    F0 = y_val[0];          //底噪光子值
    //获取浓度对数值，发光值去底对数值数组后，进行多项式线性拟合
    dxs = new DuoXiangShi(newX,newY,newCount,2);
    coef = dxs->getCoefficient();   //转换后线性方程的参数数组

    //画点500个点的浓度值、光子值
    my_x = new double [500];
    my_y = new double [500];
//    maxX = x[count-1];      //浓度最大值
    maxX = newX[newCount-1];        //转换后浓度最大值
//    double *t_coef = getcoef();
    for(int i=0;i<500;i++)
    {
        my_x[i] = maxX * i * 1.1/500;
//        my_y[i] = t_coef[0] * pow(my_x[i],t_coef[1]) + t_coef[2];
        my_y[i] = coef[0] + coef[1] * my_x[i];
    }
}
/**
 * @brief Linnear_Fit::getR
 * @return 返回对数线性拟合优度
 */
double Linnear_Fit::getR()
{
//    double *coeff = getcoef();

//    double fenzi = 0;
//    double fenmu = 0;
//    double r_temp = 0;

//    for(int i = 0;i<count;i++)
//    {
//        fenzi += pow((coeff[0]*pow(x[i],coeff[1])+coeff[2]) - y[i],2);
//        fenmu += pow(y[i]-y_,2);
//    }

//    qDebug()<<"fenzi______"<<fenzi;
//    qDebug()<<"fenmu______"<<fenmu;
//    r_temp = 1-fenzi/fenmu;

//    return r_temp;

    return dxs->getR();

}
/**
 * @brief Linnear_Fit::getcoef
 * @return 返回对数线性拟合函数参数数组，数组的第三个数为底噪
 */
double* Linnear_Fit::getcoef()
{
    double *coeff = new double[3];
    coeff[0] = qPow(10,coef[0]);
    coeff[1] = coef[1];
    coeff[2] = F0;
//    return coeff;
    return coef;
}

/**
 * @brief Linnear_Fit::getX
 * @return 返回拟合所需点的浓度值对数数组
 */
double *Linnear_Fit::getX()
{
    return my_x;

}

/**
 * @brief Linnear_Fit::getY
 * @return 返回拟合所需点的发光值去底对数数组
 */
double *Linnear_Fit::getY()
{
    return my_y;
}
