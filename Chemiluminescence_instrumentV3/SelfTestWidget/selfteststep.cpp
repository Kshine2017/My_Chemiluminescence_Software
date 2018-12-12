#include "selfteststep.h"
#include <QDebug>
#include "Serial_port/serialport.h"

SelfTestStep::SelfTestStep(QWidget *parent)
{
    checkBox = new QCheckBox();
    label = new QLabel();
    label_expand = new QLabel;
    label_result = new QLabel;
    btn = new QPushButton();
    spinBox = new QSpinBox();
}

SelfTestStep::SelfTestStep(int num, QString name)
{
    number = num;
    checkBox = new QCheckBox();
    checkBox->setChecked(false);
    //checkBox->resize(100,100);
    //checkBox->setGeometry(15,15,30,30);
    //checkBox->rect().adjusted(15,15,30,30);
    //checkBox->setStyleSheet("QCheckBox {spacing: 10px;}");
  //  checkBox->setStyleSheet("QCheckBox::indicator {width:56px; height: 50px;}");

    checkBox->setStyleSheet("QCheckBox::indicator{ width: 30px;  height: 30px; left: 15px;}QCheckBox::indicator:checked{image:url(:/picture/selfTest/Checked_png.png);}"
                              "QCheckBox::indicator:unchecked{image:url(:/picture/selfTest/UnChecked_png.png); } "
                              "QCheckBox::indicator:checked:disabled{image:url(:/picture/selfTest/UnChecked_png.png);}"
                              );

    label = new QLabel;
    label->setText(name);
    //设置文本居中
    label->setAlignment(Qt::AlignCenter);
    label_expand = new QLabel;label_expand->setAlignment(Qt::AlignCenter);
    label_result = new QLabel;label_result->setAlignment(Qt::AlignCenter);


    btn = new QPushButton();
    btn->setFixedSize(275,58); //个字的大小

    btn->setStyleSheet("QPushButton{border-image: url(:/picture/selfTest/stepstart-up.png);}"
                         "QPushButton:hover{border-image: url(:/picture/selfTest/stepstart-up.png);}"
                         "QPushButton:pressed{border-image: url(:/picture/selfTest/stepstart-down.png);}");

    btn->setFlat(true);

    spinBox = new QSpinBox();
    spinBox->setMinimum(1);
    spinBox->setMaximum(20);

    connectInit();
}

/**信号槽初始化***/
void SelfTestStep::connectInit()
{
    connect(btn,SIGNAL(clicked()),this,SLOT(btnSlot()));

}

void SelfTestStep::btnSlot()
{
    int count = spinBox->text().toInt();
    emit sendData(number , count);
}


