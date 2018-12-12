#ifndef UTIL_H
#define UTIL_H

#include <QString>
#include <QSqlQuery>
#include <QDebug>
#include <QtCore/qmath.h>
#include <QMessageBox>
/**
 * @brief The cruve_generation_type enum 曲线拟合类型
 */
enum cruve_generation_type
{
    DUOXIANGSHI, //多项式
    LOGISTIC,    //四参数
    LOGLINEARFIT,//线性回归拟合
    LOGLOGISTIC  //logstatic方程
};

class Util
{

public:
    Util();
    /**
     * @brief getX 根据测试项目 和光子数（y）的值求浓度（X）的值
     * @param type  试剂整体前七位编码
     * @param yValue    光子数（即y值）
     * @return  返回浓度值
     */
    static double getX(QString type,double yValue)
    {
        double x = 0;
        QSqlQuery query;

        int generation_type;    //拟合方式
        double *para = new double[6]; //函数系数数组
        QString queryStr = "select GENERATION_TYPE,PARAMETER_ONE,PARAMETER_TWO,PARAMETER_THREE,"
                           "PARAMETER_FOUR,PARAMETER_FIVE,PARAMETER_SIX "
                           "from cruve_parameter "
                           "where REAGENT_CODE = '" + type + "' and DEL_FLAG = 0";

        query.exec(queryStr) ;
        qDebug()<<"getX()------query.exec";

        while(query.next()){
//            qDebug() << QString("PARAMETER_ONE: %1, PARAMETER_TWO: %2, PARAMETER_THREE: %3,"
//                                "PARAMETER_FOUR: %4, PARAMETER_FIVE: %5, PARAMETER_SIX: %6,GENERATION_TYPE: %7")
//                                .arg(query.value("PARAMETER_ONE").toString())
//                                .arg(query.value("PARAMETER_TWO").toString())
//                                .arg(query.value("PARAMETER_THREE").toString())
//                                .arg(query.value("PARAMETER_FOUR").toString())
//                                .arg(query.value("PARAMETER_FIVE").toString())
//                                .arg(query.value("PARAMETER_SIX").toDouble())
//                                .arg(query.value("GENERATION_TYPE").toInt());

            generation_type = query.value("GENERATION_TYPE").toInt();//取出数据库中存储的函数系数
            qDebug()<<generation_type;
            para[0] = query.value("PARAMETER_ONE").toDouble();
            qDebug()<<para[0];
            para[1] = query.value("PARAMETER_TWO").toDouble();
            para[2] = query.value("PARAMETER_THREE").toDouble();
            para[3] = query.value("PARAMETER_FOUR").toDouble();
            para[4] = query.value("PARAMETER_FIVE").toDouble();
            para[5] = query.value("PARAMETER_SIX").toDouble();
        }
        qDebug()<<"getXValue";
        x = getXValue(generation_type,yValue,para);
        qDebug()<<"光子值："<<yValue<<"浓度值："<<x;
        return x;
    }

private:
    /**
     * @brief getX      根据曲线拟合方式和光子数（y）的值求浓度（X）的值
     * @param type      曲线拟合方式(cruve_generation_type)
     * @param yValue    光子数（即y值）
     * @param para[]    函数系数数组
     * @return  返回浓度值
     */
    static double getXValue(int type,double yValue ,double *para)
    {
        double a = para[3];
        double b = para[2];
        double c = para[1];
        double d = para[0];

        qDebug()<<"a---getXValue"<<a;
        qDebug()<<"b---getXValue"<<b;
        qDebug()<<"c---getXValue"<<c;
        qDebug()<<"d---getXValue"<<d;
        double x = 0;
        if(type == DUOXIANGSHI){    //3次方多项式求根
            double A = b*b - 3*a*c;
            double B = b*c - 9*a*(d-yValue);
            double C = c*c - 3*b*(d-yValue);

            double deta = B*B - 4*A*C;
            qDebug()<<"deta---getXValue"<<deta;
            if(deta >=0){
                double Y1 = A*b +1.5*a*(-B+pow(deta,0.5));
                double Y2 = A*b +1.5*a*(-B-pow(deta,0.5));

                double Y1_sqrt3,Y2_sqrt3;

                if(Y1>=0)
                    Y1_sqrt3 = pow(Y1,1.0/3.0);
                else
                    Y1_sqrt3 = -pow(-Y1,1.0/3.0);

                if(Y2>=0)
                    Y2_sqrt3 = pow(Y2,1.0/3.0);
                else
                    Y2_sqrt3 = -pow(-Y2,1.0/3.0);
                x = (-b-Y1_sqrt3-Y2_sqrt3)/(3*a);
            }
        }else if(type == LOGISTIC){     //四参数求根 y = (d-a)/(1+x/b)^c+a;
            x = b*pow((d-a)/(yValue-a)-1,1.0/c);
        }
        else if(type == LOGLINEARFIT)   //对数线性拟合求根
        {
            x = pow(10,(qLn(yValue - para[2])/qLn(10) - para[0])/para[1]);
        }
        else if(type == LOGLOGISTIC)    //LogLogistic拟合函数求解
        {
            x = qLn((para[0]/yValue-1)*para[1]/(para[0] - para[1]))/(-para[2]);
        }
        else{
            x = -1;
        }
        return x;
    }
public:
    /*
     * 画曲线时，所根据浓度求发光值
     */
    static double getYValue(int type,double x ,double *para)
    {
        double a = para[0];
        double b = para[1];
        double c = para[2];
        double d = para[3];
        double y = 0 ;

        if(type == DUOXIANGSHI)
        {
            y = a + b * x + c * x * x + d * x * x * x;
        }
        else if(type == LOGISTIC)
        {
            y = (a-d)/(1+ pow(x/c , b)) + d;
        }
        else if(type == LOGLOGISTIC)
        {
            y = pow(10,para[0]+para[1]*qLn(x)/qLn(10))+para[2];
        }
        else if(type == LOGLINEARFIT)
        {
            y = para[0] + para[1] * x;
        }
        else
        {
            y = -1;
        }
        return y;
    }
};

#endif // UTIL_H
