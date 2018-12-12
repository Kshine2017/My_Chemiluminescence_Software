#ifndef WORKPROGRESSAREA_H
#define WORKPROGRESSAREA_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "SelfTestWidget/QRoundProgressBar.h"
#include <QTimer>
class WorkProgressArea : public QWidget
{
    Q_OBJECT
public:
    explicit WorkProgressArea(QWidget *parent = nullptr);
    QWidget* Area_widget;
    QLabel* Label_background_pic;//背景图片

    QLabel* label_current_work_stage;//当前工作阶段：
    QLabel* label_workprogress_bar; //工作进度条：//暂时不用
    QLabel* label_start_time;//开始时间：
    QLabel* label_end_time;//结束时间

    QLabel* Lvalue_stage; //存放状态情况
    QLabel* Lvalue_start_time;//开始时间存放时间值
    QLabel* Lvalue_end_time;//结束时间存放时间值

    QHBoxLayout* All_layout;//全

    QVBoxLayout *current_work_all_layout;   //当前工作阶段整体布局
    QHBoxLayout *current_work_layout;   //当前工作阶段布局
    QHBoxLayout *start_time_layout;     //开始时间布局
    QHBoxLayout *end_time_layout;       //结束时间布局

    QRoundProgressBar* RoundPB;//圆形进度条

    int counter;

signals:

public slots:


};

#endif // WORKPROGRESSAREA_H
