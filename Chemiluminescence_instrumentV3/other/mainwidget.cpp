#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    //设置窗口标题
    this->setWindowTitle("伯纳公司化学发光仪");
    setWindowState(Qt::WindowMaximized);//全屏
    QFont *font = new QFont("AcadEref",20,20);//设置字体
    mainLayout = new QHBoxLayout(this);//主界面
    this->setFont(*font);
    layout_operation = new QVBoxLayout();//操作界面

    stack = new QStackedWidget(); //堆栈界面

    btn_unknowProduct = new QPushButton(QString(tr("未知品操作")));//未知品操作
    btn_qualityControl= new QPushButton(QString(tr("校准、质控品")));//校准、质控品
    btn_standard = new QPushButton(QString(tr("标准品")));//标准品
    btn_selfCheck = new QPushButton(QString(tr("自检")));//自检
    btn_lookUp = new QPushButton(QString(tr("查询")));//查询
    btn_system = new QPushButton(QString(tr("系统")));//系统
    btn_reagentVesselEditor = new QPushButton(QString(tr("标准品试剂船编辑")));//试剂船编辑
    btn_standardCurveGeneration = new QPushButton(QString(tr("标准曲线生成")));//标准曲线生成

    pit_temp = new QPixmap();//温度图片
    label_temp = new QLabel(QString(tr("温育台:40℃")));//显示温度
    label_temp->setFixedSize(250,50);
    pit_selfCheck = new QPixmap();//自检图片
    label_selfCheck = new QLabel(QString(tr("系统未自检！")));//显示自检

    //堆栈界面
    stack = new QStackedWidget();

    //操作界面
    layout_operation->addWidget(btn_unknowProduct);
    layout_operation->addWidget(btn_qualityControl);
    layout_operation->addWidget(btn_selfCheck);
    layout_operation->addWidget(btn_lookUp);
    layout_operation->addWidget(btn_system);
    layout_operation->addWidget(btn_reagentVesselEditor);
    layout_operation->addWidget(btn_standard);
    layout_operation->addWidget(btn_standardCurveGeneration);
    //layout_operation->addWidget(*pit_temp);
    layout_operation->addStretch();
    layout_operation->addWidget(label_temp);
//    layout_operation->addWidget(*pit_selfCheck);
    layout_operation->addWidget(label_selfCheck,0,Qt::AlignBottom);

    //堆栈界面
    window_editor = new ReagentVesselEditor();
    stack->addWidget(window_editor);
    //主界面
    mainLayout->addLayout(layout_operation);
    mainLayout->addWidget(stack,0,Qt::AlignTop);

    mainLayout->setMargin(5);
    mainLayout->setSpacing(5);
    mainLayout->setStretchFactor(layout_operation,1);
    mainLayout->setStretchFactor(stack,9);

    connect(btn_reagentVesselEditor,SIGNAL(clicked()),this,SLOT(setCurrentIndex(int)));
}




