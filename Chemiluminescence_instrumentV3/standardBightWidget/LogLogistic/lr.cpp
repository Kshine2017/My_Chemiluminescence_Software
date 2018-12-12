#include "lr.h"
#include <QDebug>
#include <QtCore/qmath.h>

LR::LR(double *x_val, double *y_val, int count_val)
{
    coeff = new double[3];  //logistic拟合曲线只有三个参数
    best_coeff = new double[3];  //logistic拟合曲线只有三个参数

    count = count_val;
    x = new double[count];
    y = new double[count];
    for(int i=0;i<count;i++)
    {
        x[i] = x_val[i];
        y[i] = y_val[i];
        y_ += y[i];
    }
    y_ = y_/count;          //y值的平均值

    //将参数赋初值
    coeff[0] = K = y[count-1]+1;
    coeff[1] = P = y[0];

    //画点500个点的浓度值、光子值
    my_x = new double [500];
    my_y = new double [500];
    maxX = x[count-1];      //浓度最大值

    qDebug()<<"doFit前";
    doFit();
    qDebug()<<"doFit后";

    double *temp_c = getcoeff();
    for(int i = 0;i<500;i++)
    {
        my_x[i] = maxX *1.1*i/500;
        my_y[i] = temp_c[0]/(1+(temp_c[0]/temp_c[1]-1)*exp(-temp_c[2]*my_x[i]));
    }
    qDebug()<<"循环后";
}
/**
 * @brief LR::get_K_value
 * @param K_value
 * @param P_value
 * @param r_value
 * @param mag   数量级
 * @return
 */

double LR::get_K_value(double K_value, double P_value, double r_value, int mag)
{
    double st_K = K_value - pow(10,mag+1);
    double end_K = K_value + pow(10,mag+1);
    double temp_value = 0;
    if(st_K < 0) st_K = 0;
    coeff[1] = P_value;
    coeff[2] = r_value;
    for(K = st_K;K < end_K;K += pow(10,mag))
    {
        coeff[0] = K;
        double temp = getR(coeff);
        qDebug()<<num<<"---get_K---拟合优度："<<temp<<"--------------"<<K;
        if(temp > 1 && temp < minR)
        {
            minR = temp;
            temp_value = coeff[0];
        }

        if(temp<1 && temp > maxR)
        {
            maxR = temp;
            temp_value = coeff[0];
            best_coeff[0] = K;
            best_coeff[1] = P;
            best_coeff[2] = r;
        }
        all_R[num] = temp;
        all_coeff[num][0] = K;
        all_coeff[num][1] = P;
        all_coeff[num][2] = r;
        num++;
        if(num > cru_count-5){
            break;
        }
        qDebug()<<"all_coeff[num][0]-------"<<all_coeff[3][0]<<"---K-------"<<K;
    }
    if(temp_value == 0)temp_value = K_value;
    qDebug()<<"-----K----"<<"minR:"<<minR<<"temp_value:"<<temp_value;
    qDebug()<<"-----K----"<<"manR:"<<maxR<<"temp_value:"<<temp_value;
    return temp_value;
}

double LR::get_P_value(double K_value, double P_value, double r_value, int mag)
{
    double st_P = P - pow(10,mag+1);
    double end_P = P + pow(10,mag+1);
    double temp_value = 0;
    if(st_P < 0) st_P = 0;
    coeff[0] = K_value;
    coeff[2] = r_value;
    for(P = st_P;P < end_P;P += pow(10,mag))
    {

        coeff[1] = P;
        double temp = getR(coeff);
        qDebug()<<num<<"---get_P---"<<temp<<"--------------"<<P;
        if(temp > maxR)
        {
            maxR = temp;
            temp_value = coeff[1];
        }
        all_R[num] = temp;
        all_coeff[num][0] = K;
        all_coeff[num][1] = P;
        all_coeff[num][2] = r;
        num++;
        if(num > cru_count-5){
            break;
        }
    }
    if(temp_value == 0) temp_value = P_value;
    qDebug()<<"-----P----"<<"maxR:"<<maxR<<"temp_value:"<<temp_value;

    return temp_value;
}

double LR::get_r_value(double K_value, double P_value, double r_value, int mag)
{
    double st_r = r_value - pow(10,mag+1);
    double end_r = r_value + pow(10,mag+1);
    if(st_r < 0) st_r = 0;
    double temp_value = 0;
    coeff[0] = K_value;
    coeff[1] = P_value;
    for(r = st_r;r < end_r;r += pow(10,mag))
    {
//        num++;
        coeff[2] = r;
        double temp = getR(coeff);
        qDebug()<<num<<"---get_r---"<<temp<<"--------------"<<r;
        if(temp > 1 && temp <= minR)
        {
            minR = temp;
            temp_value = coeff[2];
        }
        if(temp<1 && temp > maxR)
        {
            maxR = temp;
            temp_value = coeff[2];
            best_coeff[0] = K;
            best_coeff[1] = P;
            best_coeff[2] = r;
        }
        all_R[num] = temp;
        all_coeff[num][0] = K;
        all_coeff[num][1] = P;
        all_coeff[num][2] = r;
        num++;
        if(num > cru_count-5){
            break;
        }
    }
    if(temp_value == 0) temp_value = r_value;
    qDebug()<<"-----r----"<<"minR:"<<minR<<"temp_value:"<<temp_value;
    qDebug()<<"-----r----"<<"maxR:"<<maxR<<"temp_value:"<<temp_value;
    return temp_value;
}

/**
 * @brief LR::getR
 * @param coe   参数解
 * @return  当前参数解时，返回当前拟合优度
 */
double LR::getR(double*coe)
{
    double fenzi = 0;
    double fenmu = 0;
    double r_temp = 0;

    for(int i = 0;i<count;i++)
    {
        fenzi += pow((coe[0]/(1+(coe[0]/coe[1]-1)*exp(-coe[2]*x[i]))) - y[i],2);
        fenmu += pow(y[i]-y_,2);
    }
    r_temp = 1-fenzi/fenmu;

//    if(r_temp < 0)
//    {
//        for(int i = 0;i<count;i++)
//        {
//            fenzi += pow((coe[0]/(1+(coe[0]/coe[1]-1)*exp(-coe[2]*x[i]))) - y_,2);
//            fenmu += pow(y[i]-y_,2);
//        }
//        r_temp = fenzi/fenmu;
//    }
    return r_temp;

}
/**
 * @brief LR::getcoeff
 * 获取最优拟合优度时，此时参数解
 */
double* LR::getcoeff()
{
    double * temp = new double[3];
    temp[0] = all_coeff[best_R_index][0];
    temp[1] = all_coeff[best_R_index][1];
    temp[2] = all_coeff[best_R_index][2];
    return temp;
}
/**
 * @brief LR::getMagnitude
 * @param value 数值
 * @return 该数值的数量级
 */
int LR::getMagnitude(double value)
{
    value = qAbs(value);
    int mag = 0;
    if(value > 1)
    {
        while(value >= 1)
        {
            value = value/10;
            mag++;
        }
        mag = mag-1;
    }
    else if(value <1)
    {
        while(value < 1)
        {
            value = value*10;
            mag--;
        }
    }
    return mag;
}

void LR::doFit()
{
    double temp_K;
    double temp_P;
    double temp_r;
    double temp_R;

    //求r的初始值
    for(int i = 0 ;i<count;i++)
    {
        double tempX = x[i];
        double tempY = y[i];
        coeff[2] = (qLn((K/tempY-1)/(K/P-1)))/(-tempX);
        temp_R = getR(coeff);

        qDebug()<<"r="<<coeff[2]<<"  R="<<temp_R;
        if(temp_R > 1)  //如果求得曲线决定系数大于1，则找出最小的曲线决定系数
        {
            if(temp_R < minR)
            {
                minR = temp_R;      //找到最小的决定系数
                r = coeff[2];         //并记下当前的r参数
            }
        }
        else if(temp_R < 1)//如果求得曲线决定系数小于1，则找出最大的曲线决定系数
        {
            if(temp_R > maxR)
            {
                maxR = temp_R;      //找到最大的决定系数
                r = coeff[2];         //并记下当前的r参数
            }
        }
    }
    qDebug()<<"r参数初始值："<<r;
    for(int i = 0;;i++)
    {
        r = get_r_value(K,P,r,getMagnitude(r)-i);
        qDebug()<<"---K----"<<K<<"---P----"<<P<<"-----r-----"<<r;
        K = get_K_value(K,P,r,getMagnitude(K)-i);
        qDebug()<<"---K----"<<K<<"---P----"<<P<<"-----r-----"<<r;
        P = get_P_value(K,P,r,getMagnitude(P)-i);
        qDebug()<<"---K----"<<K<<"---P----"<<P<<"-----r-----"<<r;

        if(maxR >0.99)
        {
            break;
        }

        if(num > cru_count-5){
            break;
        }
    }

    qDebug()<<"循环次数"<<num;

    for(int i = 0;i<num;i++)
    {
//        qDebug()<<"循环：R："<<all_R[i]<<"参数"<<all_coeff[i][0]<<all_coeff[i][1]<<all_coeff[i][2];
        if(all_R[i]<1&&all_R[i] > best_R)
        {
            best_R = all_R[i];
            best_coeff[0] = all_coeff[i][0];
            best_coeff[1] = all_coeff[i][1];
            best_coeff[2] = all_coeff[i][2];
            best_R_index = i;
        }
    }

    double RR = getBestR();
    double *cc = getcoeff();

    qDebug()<<"R:"<<RR<<"参数："<<cc[0]<<"--"<<cc[1]<<"--"<<cc[2]<<"--";
}

/**
 * @brief LR::getBestR
 * @return 获取最优拟合优度
 */
double LR::getBestR()
{
    return best_R;
}
/**
 * @brief LR::getX
 * @return  画图所需点的横坐标
 */
double *LR::getX()
{
    return my_x;
}

/**
 * @brief LR::getY
 * @return  画图所需点的纵坐标
 */
double *LR::getY()
{
    return my_y;
}
