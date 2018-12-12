#ifndef LR_H
#define LR_H

/**
 * @brief The LR class
 * @author huangzhijie
 * @version 1.0
 *  logistic 曲线拟合
 *
 * y = K/(1+(K/P-1)*e^(-r*x));
 *
 * K-----------最终值
 * P-----------起始值
 * r-----------曲线变化斜率
 *
 */
class LR
{
public:
    LR(double *x_val, double *y_val, int count_val);

private:
    double *x;  //拟合所需标准品浓度数组
    double *y;  //拟合所需标准品发光值数组
    int count;  //拟合所需标准品数量

    const static int cru_count = 500;       //曲线拟合最大次数

    double y_ = 0;  //y值的平均值

    double K;   //曲线最终值
    double P;   //曲线初始值
    double r;   //衡量曲线变化快慢
    double R;   //曲线拟合优度最优解

    double maxX;    //曲线最大浓度值；
    double *my_x;   //曲线画点所需浓度值数组
    double *my_y;   //曲线画点所需发光值数组


    double maxR = 0;
    double minR = 100;

    int num = 0;

    double *coeff;  //曲线参数数组最优解
    double *best_coeff;

    double all_R[cru_count];    //所有拟合优度
    double all_coeff[cru_count][3];         //所有参数解
    double best_R = 0;
    int best_R_index = 0;

public:
    double *getcoeff();
    double getBestR();
    double *getX();
    double *getY();

private:

    //获得当前参数K的最优解
    double get_K_value(double K_value,double P_value,double r_value,int mag);
    //获得当前参数P的最优解
    double get_P_value(double K_value,double P_value,double r_value,int mag);
    //获得当前参数r的最优解
    double get_r_value(double K_value,double P_value,double r_value,int mag);

    double getR(double *coe);
    int getMagnitude(double value);

    //开始拟合
    void doFit();


};

#endif // LR_H
