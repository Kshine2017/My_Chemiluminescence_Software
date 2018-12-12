#include "operation_step.h"

Operation_step::Operation_step(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QHBoxLayout(this);
    layout_btn = new QVBoxLayout();
    btn_add = new QPushButton();//加
//    QIcon *icon_add = new QIcon(":/new/prefix1/picture/add.png");//按钮加的图标
//    btn_add->setIcon(*icon_add);

    btn_minus = new QPushButton();//减
//    QIcon *icon_minus = new QIcon(":/new/prefix1/picture/minus.png");
//    btn_minus->setIcon(*icon_minus);
    btn_singleStep = new QPushButton(QString(tr("单步运行")));//单步运行
    //设置按钮去边框
    btn_add->setFlat(true);
    btn_minus->setFlat(true);

    btn_add->setFixedHeight(20);
    btn_minus->setFixedHeight(20);

    label_step = new QLabel(QString(tr("步骤1:")));
    label_startPosition = new QLabel(QString(tr("起始位置:")));
    label_endPosition = new QLabel(QString(tr("放入位置:")));
    label_time = new QLabel(QString(tr("时间:")));
    label_preOrderMixingTimes = new QLabel(QString(tr("前序混匀次数:")));//前序混匀次数
    label_ordinalMixingTimes = new QLabel(QString(tr("前序混匀次数:")));//前序混匀次数

//    label_startPosition->setFrameStyle(6);
//    label_endPosition->setFrameStyle(6);
//    label_time->setFrameStyle(6);
//    label_preOrderMixingTimes->setFrameStyle(6);
//    label_ordinalMixingTimes->setFrameStyle(6);

    combo_step = new QComboBox();//步骤
    combo_startPosition = new QComboBox();//起始位置
    combo_endPosition = new QComboBox();//放入位置
    combo_time = new QComboBox();//时间
    combo_preOrderMixingTimes = new QComboBox();//前序混匀次数
    combo_ordinalMixingTimes = new QComboBox();//前序混匀次数



    layout_btn->addWidget(btn_add);
    layout_btn->addWidget(btn_minus);

    mainLayout->addLayout(layout_btn);
    mainLayout->addWidget(label_step);
    mainLayout->addWidget(combo_step);
    mainLayout->addWidget(label_startPosition);
    mainLayout->addWidget(combo_startPosition);
    mainLayout->addWidget(label_endPosition);
    mainLayout->addWidget(combo_endPosition);
    mainLayout->addWidget(label_time);

    mainLayout->addWidget(combo_time);
    mainLayout->addWidget(label_preOrderMixingTimes);
    mainLayout->addWidget(combo_preOrderMixingTimes);
    mainLayout->addWidget(label_ordinalMixingTimes);
    mainLayout->addWidget(combo_ordinalMixingTimes);

    mainLayout->addWidget(btn_singleStep);



}
