#include "workprogressarea.h"

WorkProgressArea::WorkProgressArea(QWidget *parent) : QWidget(parent)
{
    //0)创建承载窗口（也可以不要）
    Area_widget = new QWidget(this);
    Area_widget->setFixedSize(650,220);
    Area_widget->setFont(QFont("楷体",16));
    //  Area_widget->setStyleSheet("background-color:white;");

    //1)在窗口中，创建标签名：
    label_current_work_stage= new QLabel(Area_widget);
    label_start_time =new QLabel(Area_widget);
    label_end_time =new QLabel(Area_widget);

    // label_current_work_stage->setFont(QFont());
    label_current_work_stage->setText("当前工作阶段：");
    label_start_time->setText("开始时间：");
    label_end_time->setText("结束时间：");
    // 标签凸起或凹下
    label_current_work_stage->setFrameShadow(QFrame::Raised);
    label_start_time->setFrameShadow(QFrame::Raised);
    label_end_time->setFrameShadow(QFrame::Raised);




    //  name_layout->setGeometry(QRect(0,0,120,200));

    //2)创建数值(公开接口)
    Lvalue_stage        =new QLabel(Area_widget);
    Lvalue_start_time   =new QLabel(Area_widget);
    Lvalue_end_time     =new QLabel(Area_widget);
    Lvalue_stage->setFixedSize(200,20);
    Lvalue_start_time->setFixedSize(250,25);
    Lvalue_end_time->setFixedSize(300,30);

  /**
    *   测试数据：
    *   Lvalue_stage->setText("**********");
    *   Lvalue_start_time->setText("2014/03/12 12:12:12");
    *   Lvalue_end_time->setText("2014/03/12 12:12:12");
    *
    */

    //整体布局
    current_work_layout = new QHBoxLayout;   //当前工作阶段布局
    current_work_layout->addWidget(label_current_work_stage);
    current_work_layout->addWidget(Lvalue_stage);

    start_time_layout = new QHBoxLayout;     //开始时间布局
    start_time_layout->addWidget(label_start_time);
    start_time_layout->addWidget(Lvalue_start_time);

    end_time_layout = new QHBoxLayout;       //结束时间布局
    end_time_layout->addWidget(label_end_time);
    end_time_layout->addWidget(Lvalue_end_time);

    current_work_all_layout = new QVBoxLayout;
    current_work_all_layout->addLayout(current_work_layout);
    current_work_all_layout->addLayout(start_time_layout);
    current_work_all_layout->addLayout(end_time_layout);



    //  value_layout->setGeometry(QRect(120,0,200,200));


    //3)创建圆形进度条
    RoundPB = new QRoundProgressBar(Area_widget);
    //RoundPB->setGeometry(20,20,50,50); //坐标，尺寸
    RoundPB->setFixedSize(180,180);
    RoundPB->setBarStyle(QRoundProgressBar::StyleDonut); //风格设置
    RoundPB->setRange(0,100);
//    RoundPB->setOutlinePenWidth(0);
//    RoundPB->setDataPenWidth(0);
    QPalette palette1;

    palette1.setBrush(QPalette::Base,QColor(243,243,243)); //(进度条的底色)未填充的部分，如果需要透明需要设置为 Qt::NoBrush

    QLinearGradient plotGradient(QPointF(0, 0), QPointF(0, 180));
    plotGradient.setColorAt(0,QColor(254,254,254));
    plotGradient.setColorAt(0.5,QColor(250,250,250));
    plotGradient.setColorAt(1,QColor(238,238,238));
    palette1.setBrush(QPalette::Window,plotGradient); //（外边缘颜色）widget的背景色一般设置为Qt::NoBrush

    //palette1.setBrush(QPalette::Shadow,Qt::NoBrush); // 未填充的前景色
    //palette1.setBrush(QPalette::AlternateBase,Qt::NoBrush);//中心字体的背景色
    palette1.setBrush(QPalette::AlternateBase,QColor(243,243,243));

    palette1.setBrush(QPalette::Highlight,QBrush(QColor(0,80,255)));//进度条颜色

    palette1.setColor(QPalette::Text,QColor(0,0,0));

    RoundPB->setPalette(palette1);


    //4)横向布局
    All_layout =new QHBoxLayout(Area_widget);


    All_layout->addWidget(RoundPB);
    All_layout->addSpacing(20);
    All_layout->addLayout(current_work_all_layout);
    All_layout->addSpacing(100);

    All_layout->setGeometry(QRect(0,0,340,220));


}

