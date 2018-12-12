#include "dialogadddepartment.h"
#include <QString>
#include <QDebug>
#include <QMessageBox>

DialogAddDepartment::DialogAddDepartment(QDialog *parent) : QDialog(parent)
{
    init();
    connect(btn_saveAdd,SIGNAL(clicked()),this,SLOT(saveAdd()));
    connect(btn_saveClose,SIGNAL(clicked()),this,SLOT(saveClose()));
    connect(btn_cancel,SIGNAL(clicked()),this,SLOT(cancel()));
}

//保存新增
void DialogAddDepartment::saveAdd()
{
//    lineEdit_hospital->clear();

    data_hospital = lineEdit_hospital->text();
    data_DeDepartment = lineEdit_DeDepartment->text();

    if(data_hospital == "" || data_DeDepartment == "")
    {
        QMessageBox::information(this,tr("提示"),tr("请完善当前信息！"));
    }else
    {
        QSqlQuery query;
        query.exec("select DEPATMENT_NAME from hospital_info where DEPATMENT_NAME = '" + data_DeDepartment + "';");
        while(query.next())
        {
            QMessageBox::information(this,tr("提示"),tr("已存在该科室！"));
            return;
        }

        query.exec(("insert into hospital_info(HOSPITAL_NAME,DEPATMENT_NAME,CREATOR_ID,CREATE_TIME,MODIFIER_ID,MODIFY_TIME,DEL_FLAG) values('" + data_hospital + "','" + data_DeDepartment + "',0,0,0,0,0)"));

        emit signal_saveAdd();

        lineEdit_DeDepartment->clear();
    }

}
//保存关闭
void DialogAddDepartment::saveClose()
{
    data_hospital = lineEdit_hospital->text();
    data_DeDepartment = lineEdit_DeDepartment->text();
    if(data_hospital == "" || data_DeDepartment == "")
    {
        QMessageBox::information(this,tr("提示"),tr("请完善当前信息！"));
    }else
    {
        QSqlQuery query;
        query.exec("select DEPATMENT_NAME from hospital_info where DEPATMENT_NAME = '" + data_DeDepartment + "';");
        while(query.next())
        {
            QMessageBox::information(this,tr("提示"),tr("已存在该科室！"));
            return;
        }

        query.exec(("insert into hospital_info(HOSPITAL_NAME,DEPATMENT_NAME,CREATOR_ID,CREATE_TIME,MODIFIER_ID,MODIFY_TIME,DEL_FLAG) values('" + data_hospital + "','" + data_DeDepartment + "',0,0,0,0,0)"));

        emit signal_saveClose();
        this->close();
    }
}

//取消
void DialogAddDepartment::cancel()
{
    this->close();
}

//获取弹窗所填的信息
QString DialogAddDepartment::getData()
{
    data_hospital = lineEdit_hospital->text();
    data_DeDepartment = lineEdit_DeDepartment->text();
    QString s = "%1,%2";
    data = s.arg(data_hospital).arg(data_DeDepartment);
    qDebug()<<"------"+data;
    lineEdit_hospital->clear();
    lineEdit_DeDepartment->clear();
    return data;
}

//初始化界面
void DialogAddDepartment::init()
{
    widget_content = new QWidget(this); //放置背景图片的的
    widget_content->setFixedSize(450,300);
    widget_content->setAutoFillBackground(true);

    setWindowModality(Qt::ApplicationModal);

    mainLayout = new QVBoxLayout(widget_content);
    this->setWindowTitle(QString(tr("新增科室")));
    resize(450,300);
    this->setFont(QFont("宋体",16));

    QPalette palette;
    QPixmap pixmap(":/picture/System/clinicalDiagnosis/dialog/dialog_bg.png");
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    widget_content->setPalette(palette);    //放置背景图片


    layout_hospital = new QHBoxLayout();
    layout_Department = new QHBoxLayout();
    layout_btn = new QHBoxLayout();

    label_hospital = new QLabel(QString(tr("医院:")));
    label_hospital->setFixedSize(55,26);
    label_hospital->setAlignment(Qt::AlignRight);        //设置右对齐
    label_DeDepartment = new QLabel(QString(tr("科室:")));
    label_DeDepartment->setFixedSize(55,26);
    label_hospital->setAlignment(Qt::AlignRight);

    lineEdit_hospital = new QLineEdit();
    lineEdit_hospital->setFixedSize(280,26);

    lineEdit_DeDepartment = new QLineEdit();
    lineEdit_DeDepartment->setFixedSize(280,26);

    btn_saveAdd = new QPushButton(QString(tr("保存新增")));
    QIcon icon1(":/picture/System/clinicalDiagnosis/dialog/saveAdd.png");
    btn_saveAdd->setIcon(icon1);
    btn_saveAdd->setFlat(true);
    btn_saveAdd->setFixedSize(130,36);
    btn_saveAdd->setIconSize(QSize(26,30));

    btn_saveClose = new QPushButton(QString(tr("保存关闭")));
    QIcon icon2(":/picture/System/clinicalDiagnosis/dialog/saveClose.png");
    btn_saveClose->setIcon(icon2);
    btn_saveClose->setFixedSize(130,36);
    btn_saveClose->setFlat(true);
    btn_saveClose->setIconSize(QSize(26,26));

    btn_cancel = new QPushButton(QString(tr("取消")));
    QIcon icon3(":/picture/System/clinicalDiagnosis/dialog/cancel.png");
    btn_cancel->setIcon(icon3);
    btn_cancel->setFlat(true);
    btn_cancel->setFixedSize(130,36);
    btn_cancel->setIconSize(QSize(26,26));

    //layout_num->addSpacing(10);
    layout_hospital->addStretch();
    layout_hospital->addWidget(label_hospital);
    layout_hospital->addWidget(lineEdit_hospital);
    layout_hospital->addStretch();

    layout_Department->addStretch();
    layout_Department->addWidget(label_DeDepartment);
    layout_Department->addWidget(lineEdit_DeDepartment);
    layout_Department->addStretch();

    layout_btn->addWidget(btn_saveAdd);
    layout_btn->addWidget(btn_saveClose);
    layout_btn->addWidget(btn_cancel);

    mainLayout->addStretch(4);
    mainLayout->addLayout(layout_hospital);
    mainLayout->addStretch(2);
    mainLayout->addLayout(layout_Department);
    mainLayout->addStretch(5);
    mainLayout->addLayout(layout_btn);
    mainLayout->addStretch(1);


}
