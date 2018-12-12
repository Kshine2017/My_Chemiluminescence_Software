#include "itemwidget.h"

itemWidget::itemWidget(QWidget *parent) : QWidget(parent)
{
   checkNameLab = new QLabel;          //检测名称
   bachNumberLab = new QLabel;         //批号
   currentWorkLab = new QLabel;        //当前工作阶段
   startTimerLab = new QLabel;         //开始时间
   endTimerLab = new QLabel;           //结束时间
   measurePhotonLab = new QLabel;       //测量光子
   measureConcentrationLab = new QLabel;  //测量浓度
   testProgressBar = new QProgressBar;    //测试进度
   startBtn = new QPushButton;          //开始按钮
   OkBtn = new QPushButton;            //结束按钮

   mainlayout = new QHBoxLayout;

   mainlayout->addWidget(checkNameLab);
   mainlayout->addWidget(bachNumberLab);
   mainlayout->addWidget(startBtn);
   mainlayout->addWidget(currentWorkLab);
   mainlayout->addWidget(testProgressBar);
   mainlayout->addWidget(startTimerLab);
   mainlayout->addWidget(endTimerLab);
   mainlayout->addWidget(measurePhotonLab);
   mainlayout->addWidget(measureConcentrationLab);
   setLayout(mainlayout);
}

void itemWidget::setTestProgressBar(int)
{

}
