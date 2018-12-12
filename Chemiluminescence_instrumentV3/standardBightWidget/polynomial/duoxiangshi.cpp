#include "duoxiangshi.h"
#include <math.h>
#include <QDebug>
#include <QVector>

DuoXiangShi::DuoXiangShi(double*x, double*y, int count, int coefficientCount)

{
    int n= count;           //点的个数
    p = coefficientCount;
    point_x = new  double[n];  //{0,50,200,500,2000,5000};
    point_y = new  double[n];

    memcpy(point_x,x,sizeof(double)*n);
    memcpy(point_y,y,sizeof(double)*n);
    setCoefficient(point_x,point_y,n,p);//将求解出来的未知系数存入coeffcient数组

    my_x = new double [500];
    my_y = new double [500];
    maxX = point_x[n-1];
    calculatePoints(coefficient);   //计算各个点的坐标
//    QCustomPlot *customPlot = new QCustomPlot(this);
//    customPlot->setFixedSize(1000,800);
//    customPlot->addGraph();
//    customPlot->graph(0)->setData(key,value);//添加数据
//    customPlot->graph(0)->setName("多项式拟合");

//    //设置完数据后可以对x，y轴进行设置
//    customPlot->xAxis->setLabel("浓度");
//    customPlot->yAxis->setLabel("发光值");
//    //或者设置x，y轴的范围
//    customPlot->xAxis->setRange(0,5000);
//    customPlot->yAxis->setRange(0,2500000);

//    double avg_y = (17974+58055+173265+524707+1117376+2352413)/6;

//    double he_pingfang = pow((my_y[0]-avg_y),2)+pow((my_y[4]-avg_y),2)+pow((my_y[19]-avg_y),2)
//            +pow((my_y[49]-avg_y),2)+pow((my_y[199]-avg_y),2)+pow((my_y[499]-avg_y),2);

//    double pingfang_he = pow((17974-avg_y),2)+pow((58055-avg_y),2)+pow((173265-avg_y),2)
//            +pow((524707-avg_y),2)+pow((1117376-avg_y),2)+pow((2352413-avg_y),2);


//    qDebug()<<"R²-----";
//    qDebug() << "he" << QString::number(he_pingfang,10,6);
//    qDebug() << "ping" << QString::number(pingfang_he,10,6);
//    r = he_pingfang/pingfang_he;
//    qDebug()<<QString::number(r,10,6);

//    lable_curve = new QLabel(customPlot); //曲线的名字

//    lable_curve->setText(name+"\n"+"R² = "+toString(r));


//    lable_curve->setFont(QFont("宋体",12));

//    lable_curve->setGeometry(340,470,800,40);

//    setAutoFillBackground(true);

}

//获取画图所需点X坐标数组
double* DuoXiangShi::getX()
{
    double *temp;
    temp = my_x;
    return temp;
}
//获取画图所需点Y坐标数组
double* DuoXiangShi::getY()
{
    double *temp;
    temp = my_y;
    return temp;
}

double DuoXiangShi::getR()     //获取相关系数
{
    double avg_y = 0;
    double fenzi = 0;
    double fenmu = 0;
    for (int i = 0;i<p_count;i++) //求Y的平均值
    {
        avg_y += point_y[i]/p_count;
    }
    for(int i = 0;i<p_count;i++)
    {
        fenzi = fenzi+(pow((getYValue(point_x[i])-avg_y),2));
        fenmu = fenmu+(pow((point_y[i]-avg_y),2));
    }
    r = fenzi/fenmu;
    qDebug() << "duoxiangshi rr = " << r << "fenzi = " << fenzi << "fenmu = " << fenmu << "avg = " << avg_y;
    return r;
}


double DuoXiangShi::getYValue(double xValue)         //通过X值求Y值
{
    double Y_Value = 0;
    for(int j = 0;j<p;j++)
    {
        Y_Value = Y_Value + coefficient[j]*pow(xValue,j);
    }
    return Y_Value;

}

double* DuoXiangShi::getCoefficient()        //获取函数系数数组
{
    return coefficient;
}
//根据函数系数数组  计算各点---画图所需点的坐标
void DuoXiangShi::calculatePoints(double * cof)
{
    int len = sizeof(my_x)/sizeof(double);
    qDebug() << "%%%%%%%%%%%%%%%%%%%%%%%"<<len;
    for(int i=0;i<500;i++)
    {
        my_x[i] = i*maxX*1.1/500;
        my_y[i] = 0;
        for(int j = 0;j<p;j++)
        {
            my_y[i] =my_y[i]+cof[j]*pow(my_x[i],j);
        }
    }
}

//void DuoXiangShi::paintEvent(QPaintEvent *)
//{

//    setCoefficient();//将求解出来的未知系数存入coeffcient数组

//    my_x = new double [500];
//    my_y = new double [500];
//    paintPict(coefficient);
//    // 画一条直线
//    QPainter painter(this);             // 创建QPainter一个对象
//    QPen pen;

//    QBrush bruch(Qt::FDiagPattern);     // 画刷
//    painter.setBrush(bruch);            // 设置画刷

//    // 画一个多点线
//    pen.setColor(Qt::black);
//    painter.setPen(pen);
//    bruch.setStyle(Qt::NoBrush);        // 将画刷设置成null//fow what
//    painter.setBrush(bruch);
//    QPointF pointf[500];
//    for (int i=0; i<500; i++)
//    {
//        pointf[i].setX(my_x[i]/10);
//        pointf[i].setY(500-my_y[i]/5000);
//        qDebug()<<toString(my_x[i]);
//        qDebug()<<toString(my_y[i]);
//    }
//    painter.drawPolyline(pointf, 500);
//}

/**
 * 将求解出来的未知系数存入coeffcient数组
 * 第一个参数：    已知点X坐标数组
 * 第二个参数：    已知点X坐标数组
 * 第三个参数：    点的个数
 * 第四个参数：    函数系数的个数  即为最高次方+1
 *
 */
void DuoXiangShi::setCoefficient(double *point_x,double *point_y,int pointCount,int coeCount)
{
    //多项式拟合：输入点坐标(x,y),输出多项式参数beta
    //n为点数,p为多项式系数个数
    int n= pointCount;           //点的个数
    double *x = new  double[n];  //{0,50,200,500,2000,5000};
    double *y = new  double[n];

    p = coeCount;       //系数的个数
    p_count = pointCount; //点的个数
    memcpy(x,point_x,sizeof(double)*n);
    memcpy(y,point_y,sizeof(double)*n);

    double *beta = new double[p];//未知系数中转数组
    coefficient = new double[p];//未知系数数组

    polyfit(x,y,beta,n,p);//求解方程；

    QString str = "";
//    qDebug()<<"beta--------";
//    for(int i=0;i<p;i++){qDebug<<beta[i];}
    qDebug()<<"coefficient--------";
    for(int i=0;i<p;i++)
    {
        qDebug()<<toString(coefficient[i]);
        if(i== 0)
        {
            str.append("y = "+toString(coefficient[i]));
        }else if(i== p-1)
        {
            if(coefficient[i]<0){str.append(toString(coefficient[i])+"x^"+toString(i));}
            else if(coefficient[i]>0){str.append("+"+toString(coefficient[i])+"x^"+toString(i));}
            else{str.append("");}

        }else
        {
            if(coefficient[i]<0){str.append(toString(coefficient[i])+"x^"+toString(i));}
            else if(coefficient[i]>0){str.append("+"+toString(coefficient[i])+"x^"+toString(i));}
            else{str.append("");}
        }
    }

    name = str;

    qDebug()<<str << "duoxiangshi";

}


//求解线性方程组 A*x=B (n为矩阵维数)
void DuoXiangShi::LinearSolve(double **A,double *B,double *beta,int n)
{
    int i,j,k,ik;
    double mik,temp;

    double **a,*b;
    a=new double*[n];
    for(i=0;i<n;i++) a[i]=new double[n];

    b=new double[n];

    for(i=0;i<n;i++)
    {
        b[i]=B[i];
        for(j=0;j<n;j++) a[i][j]=A[i][j];
    }

    for(k=0;k<n;k++)
    {
        mik=-1;
        for(i=k;i<n;i++)
            if(qAbs(a[i][k])>mik)
            {
                mik=qAbs(a[i][k]);
                ik=i;
            }

        for(j=k;j<n;j++)
            qSwap(a[ik][j],a[k][j]);

        qSwap(b[k],b[ik]);
        b[k]/=a[k][k];
        for(i=n-1;i>=k;i--)
            a[k][i]/=a[k][k];

        for(i=k+1;i<n;i++)
        {
            b[i]-=a[i][k]*b[k];
            for(j=n-1;j>=k;j--)
                a[i][j]-=a[i][k]*a[k][j];
        }
    }
    for(i=n-1;i>=0;i--)
    {
        beta[i]=b[i];
        for(j=i+1;j<n;j++)
            beta[i]-=a[i][j]*beta[j];
    }

    for(i=0;i<p;i++){coefficient[i]=beta[i];}

    //删除内存
    delete b;
    for(i=0;i<n;i++) delete a[i];
}

//一般线性方程组拟合。n为参数个数,p为点数。
void DuoXiangShi::linear(double **x,double *y,double *beta,int n,int p)
{
    double **a,*b;
    int i,j,k;

    //a:分配内存
    a=new double*[p];
    for(i=0;i<p;i++)
        a[i]=new double[p];

    //a:p*p矩阵
    for(i=0;i<p;i++)
        for(j=0;j<p;j++)
        {
            a[i][j]=0;
            for(k=0;k<n;k++)
                a[i][j]+=x[k][i]*x[k][j];    //计算内积
        }

    //b:1*p矩阵
    b=new double[p];
    for(i=0;i<p;i++)
    {
        b[i]=0;
        for(j=0;j<n;j++)
            b[i]+=x[j][i]*y[j];
    }

    LinearSolve(a,b,beta,p);    //求解beta

    //a:删除内存
    for(i=0;i<p;i++) delete a[i];

    delete b;
}

//多项式拟合：输入点坐标(x,y),输出多项式参数beta
//n为点数,p为多项式系数个数
void DuoXiangShi::polyfit(double *x,double *y,double *beta,int n,int p)
{
    int i,j;
    double **xx=new double*[n];

    for(i=0;i<n;i++)
    {
        //多次拟合
        xx[i]=new double[p];
        for(j=0;j<p;j++)
        {
            if(0==j)
                xx[i][j]=1;
            else
                xx[i][j]=pow(x[i],j);    //连续函数
        }
    }

    linear(xx,y,beta,n,p);

    for(i=0;i<n;i++) delete xx[i];

    delete xx;
}

QString DuoXiangShi::toString(double b){return QString::number(b,10,6);}
QString DuoXiangShi::toString(int i){return QString::number(i, 10);}
QString DuoXiangShi::toString(float f){return QString::number(f, 10,6);}

DuoXiangShi::~DuoXiangShi()
{

}
