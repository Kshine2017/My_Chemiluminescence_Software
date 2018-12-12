#ifndef DUOXIANGSHI_H
#define DUOXIANGSHI_H

//#include <QWidget>
//#include <QPaintEvent>
//#include <QPainter>
//#include <QLabel>
#include <QString>

class DuoXiangShi
{
//    Q_OBJECT

public:
    explicit DuoXiangShi(double *x = NULL, double *y = NULL, int count = 0,int coefficientCount = 4);
    ~DuoXiangShi();

    int p;  //系数的个数
    int p_count; //点的个数
    double *coefficient;

//    QLabel *lable_curve; //曲线的名字-放置曲线方程
    QString name;

    double *my_x;       //画图所需点的X坐标
    double *my_y;       //画图所需点的Y坐标
    double maxX;        //浓度最大值

    double *point_x;
    double *point_y;
    double r;

    void setCoefficient(double *point_x,double *point_y,int pointCount,int coeCount);
    void calculatePoints(double *cof);          //计算各点---画图所需点的坐标

    double* getX();         //画图所需点的X坐标
    double* getY();         //画图所需点的Y坐标

    double getR();      //获取相关系数
    double getYValue(double xValue);//根据X值求y值（拟合曲线）
    double* getCoefficient();        //获取函数系数数组


    void LinearSolve(double **A,double *B,double *x,int n);
    void linear(double **x,double *y,double *beta,int n,int p);
    void polyfit(double *x,double *y,double *beta,int n,int p);

    QString toString(double b);
    QString toString(int i);
    QString toString(float f);

};

#endif // DUOXIANGSHI_H
