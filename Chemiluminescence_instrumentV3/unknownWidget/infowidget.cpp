#include "infowidget.h"
#include <QPalette>
#include <QDebug>
#include <QMessageBox>
InfoWidget::InfoWidget(QWidget *parent) : QWidget(parent)
{
    InfoWidget_Init(); //初始化函数
    connectInit(); //信号槽绑定初始化

    fresh_TestItemCBox();
    fresh_administrativeCBox();

}

/**
 * @brief 患者信息窗口初始化
 */
void InfoWidget::InfoWidget_Init()
{
    setFixedSize(448,300);


    infoWidget = new QWidget;
    infoWidget->setAutoFillBackground(true);
    infoWidget->setFixedSize(420,300);
    infoWidget->setFont(QFont("infoWidget",15));

 /**
  * 滚动窗口
  */
    scrArea = new QScrollArea(this);
    scrArea->setFrameShape(QFrame::NoFrame); //无边框
    scrArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrArea->setFixedSize(448,265);

    PositionLab = new QLabel; /**<试剂船位置编号*/
    PositionLab->setText(tr("    舱位 01"));/**<默认舱位号*/
    PositionLab->setFont(QFont("Microsoft YaHei", 20, 75));
    PositionLab->setFixedSize(247,51);
    //设置颜色
    QPalette pa;
    pa.setColor(QPalette::WindowText,QColor(70,156,171));
//    QPixmap pixmap(":/picture/unknowWidget/info_background.png");
//    pa.setBrush(QPalette::Window,QBrush(pixmap));
    PositionLab->setStyleSheet("background-image: url(:/picture/unknowWidget/info_background.png);border: 0px");
    PositionLab->setPalette(pa);
    IDLab = new QLabel; /**<ID标签*/
    IDLab->setText(tr("患 者ID："));
    nameLab = new QLabel;/**<患者姓名标签*/
    nameLab->setText(tr("姓   名："));
    sexLab = new QLabel;/**<患者性别标签*/
    sexLab->setText(tr("性   别："));
    ageLab = new QLabel;/**<患者年龄标签*/
    ageLab->setText(tr("年   龄："));
    telphoneLab = new QLabel;/**<患者手机号码标签*/
    telphoneLab->setText(tr("电   话："));
    administrativeLab = new QLabel;/**<科室标签*/
    administrativeLab->setText(tr("科    室："));

    IDEidt = new QLineEdit;
    nameLEidt = new QLineEdit;/**<患者姓名输入框*/
    sexCom = new QComboBox;/**<患者性别选择框*/
    sexCom->addItem(QString(tr("男")));
    sexCom->addItem(QString(tr("女")));
    ageLEdit = new QLineEdit;/**<患者年龄输入框*/
    telphoneLEdit = new QLineEdit;/**<患者手机号码输入框*/
    administrativeCBox = new QComboBox;/**<科室下拉框*/
//-------------------正则表达式限制--------------------------

    IDEidt->setValidator(new QRegExpValidator(QRegExp(tr("^(0|[1-9][0-9]*|-[1-9][0-9]*)$")),this));
    nameLEidt->setValidator(new QRegExpValidator(QRegExp(tr("^[\u4e00-\u9fa5_a-zA-Z]+$")),this));
    telphoneLEdit->setValidator(new QRegExpValidator(QRegExp(tr("^((13[0-9])|(14 [1,4,5-7])|(15([0-3]|[5-9]))|(166)|(17[4,5,7,8])|(18[0,5-9])|(19[8,9]))([0-9]{8})")),this));
    ageLEdit->setValidator(new QRegExpValidator(QRegExp(tr("^(?:[1-9][0-9]?|1[01][0-9]|120)$")),this));//

//------------------ 输入提示------------------------------
    telphoneLEdit->setPlaceholderText("请输入11位手机号码！");
    ageLEdit->setPlaceholderText("年龄范围1~120岁");
    IDEidt->setPlaceholderText("请录入患者ID！");
    nameLEidt->setPlaceholderText("请录入患者姓名！");

//--------------------------------------------------------
    okBtn = new QPushButton;     /**<确定按钮*/
    okBtn->setFixedSize(147,51);
    okBtn->setStyleSheet("QPushButton{border-image: url(:/picture/unknowWidget/informationOkBtn-up.png);}"
                               "QPushButton:hover{border-image: url(:/picture/unknowWidget/informationOkBtn-up.png);}"
                               "QPushButton:pressed{border-image: url(:/picture/unknowWidget/informationOkBtn-down.png);}");
    okBtn->setFlat(true);
    infoLayout = new QGridLayout; /**<主布局器*/
    infoLayout->setMargin(0);
    HBoxLayout  = new QHBoxLayout; /**<水平布局*/
    HBoxLayout->setMargin(0);
    HBoxLayout->setSpacing(0);

    okBtnLayout = new QHBoxLayout;
    okBtnLayout->addWidget(PositionLab);
    okBtnLayout->addWidget(okBtn);
    okBtnLayout->addSpacing(70);

    infoLayout->addWidget(IDLab,2,0);
    infoLayout->addWidget(nameLab,3,0);
    infoLayout->addWidget(sexLab,4,0);
    infoLayout->addWidget(ageLab,5,0);
    infoLayout->addWidget(telphoneLab,6,0);
    infoLayout->addWidget(administrativeLab,7,0);

    infoLayout->addWidget(IDEidt,2,1);
    infoLayout->addWidget(nameLEidt,3,1);
    infoLayout->addWidget(sexCom,4,1);
    infoLayout->addWidget(ageLEdit,5,1);
    infoLayout->addWidget(telphoneLEdit,6,1);
    infoLayout->addWidget(administrativeCBox,7,1);


    HBoxLayout->addSpacing(23);
    HBoxLayout->addLayout(infoLayout);
    infoWidget->setLayout(HBoxLayout);
    scrArea->setWidget(infoWidget);

    mainLayout = new QVBoxLayout;  //主布局管理器
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addLayout(okBtnLayout);
    mainLayout->addWidget(scrArea);
    setLayout(mainLayout);
}

/**
 * @brief 信号和槽绑定初始化函数
 */
void InfoWidget::connectInit()
{
    connect(okBtn,SIGNAL(clicked()),this,SLOT(okBtnSlot()));

}

/**
 * @brief InfoWidget::确定按钮信号槽
 */
void InfoWidget::okBtnSlot()
{
    if(IDEidt->text().isEmpty() || nameLEidt->text().isEmpty() || ageLEdit->text().isEmpty() ){
        QMessageBox::information(this,tr("提示！"),tr("检测必要信息不完整，请输入完整信息。"));
    }
    QString postionString =  PositionLab->text();
    qDebug() << "当前试剂船的位置" << postionString;
    QString numStr =  postionString.mid(7);//截断字符串
    qDebug() << "当前试剂船的位置" << numStr;
    QStringList stringList;
    stringList << IDEidt->text()<< nameLEidt->text() << sexCom->currentText() << ageLEdit->text() << telphoneLEdit->text()
                           <<administrativeCBox->currentText();
//将病人信息插入信息列表
    patientInfo.insert(numStr.toInt()-1,stringList);
    //清除病人信息框里面内容
    IDEidt->clear();
    nameLEidt->clear();
    ageLEdit->clear();
    telphoneLEdit->clear();
    emit OKBtnPress(numStr.toInt()-1);

}

/**
 * @brief InfoWidget::接收来unkownWidget的信号slot
 * @param num
 */
void InfoWidget::selectRowSignSlot(int num)
{
    QStringList stringList = patientInfo.value(num);
    if(stringList.isEmpty()){  //更换行之后清除信息显示窗口信息
      IDEidt->clear();
      nameLEidt->clear();
      ageLEdit->clear();
      telphoneLEdit->clear();
      //  administrativeCBox->clear();
      return;
    }
    IDEidt->setText(stringList.at(0));
    nameLEidt->setText(stringList.at(1));
    sexCom->setCurrentText(stringList.at(2));
    ageLEdit->setText(stringList.at(3));
    telphoneLEdit->setText(stringList.at(4));
    administrativeCBox->setCurrentText(stringList.at(5));
}

void InfoWidget::fresh_TestItemCBox()
{
    //  TestItemCBox->clear();
    AddDelUpdSel op;
    QSqlQueryModel moddddel;
    op.selectData_All_TestItem(moddddel);
    for(int i=0;i<moddddel.rowCount();i++)
    {
        QModelIndex index= moddddel.index(i,0);
        QString str= moddddel.data(index).toString();
    }
}

void InfoWidget::fresh_administrativeCBox()
{
    //  administrativeCBox->clear();
    AddDelUpdSel op;
    QSqlQueryModel moddddel;
    op.selectData_ALL_hospital(moddddel);
    QString text = "";
    if(moddddel.rowCount() > 0)
    {
        QModelIndex index= moddddel.index(0,0);
        text = moddddel.data(index).toString(); //得到医院名
        qDebug()<<"医院名："<<text;
    }

    op.selectData_department(text,moddddel);
    for(int i=0;i<moddddel.rowCount();i++)
    {
        QModelIndex index= moddddel.index(i,0);
        QString str= moddddel.data(index).toString();
        administrativeCBox->insertItem(i,str);
    }
}


