#include "mydialogadd.h"
#include <QRegExpValidator>
#include <QMessageBox>
#include <QDebug>
MyDialogAdd::MyDialogAdd(QWidget *parent, WF_enum WinFlag) : QDialog(parent)
{
    setWindowModality(Qt::ApplicationModal);
    this->setWindowTitle(tr("新增用户"));
    this->setFixedSize(849,666);
    QPalette palette;
    QPixmap pixmap(":/picture/login/register_background.jpg");
    palette.setBrush(QPalette::Window,QBrush(pixmap));
    setPalette(palette);

    label_name = new QLabel ();
    label_pwd = new QLabel ();
    label_truename= new QLabel ();
    label_department = new QLabel ();
    label_hospital = new QLabel ();
    label_phoneNum = new QLabel ();
    label_email = new QLabel ();
    //给label添加背景
    label_name->setPixmap(QPixmap(":/picture/login/name_labal.png"));
    label_pwd->setPixmap(QPixmap(":/picture/login/password.png"));

    label_truename->setPixmap(QPixmap(":/picture/login/name.png"));
    label_department->setPixmap(QPixmap(":/picture/login/department.png"));
    label_hospital->setPixmap(QPixmap(":/picture/login/hospital.png"));

    label_phoneNum->setPixmap(QPixmap(":/picture/login/pthone.png"));
    label_email->setPixmap(QPixmap(":/picture/login/email.png"));

    le_name = new QLineEdit ();
    le_pwd = new QLineEdit ();

    le_truename = new QLineEdit ();
//    le_department = new QLineEdit ();;
//    le_hospital = new QLineEdit ();
    cbx_department = new QComboBox();
    cbx_hospital =new QComboBox();
    connect(cbx_hospital,SIGNAL(currentTextChanged(QString)),this,SLOT(slot_auto_fresh_department(QString)));

    le_phoneNum = new QLineEdit ();
    le_email = new QLineEdit ();

    QRegExp regExp("^[A-Za-z]{0,5}[0-9]{0,10}$"); //正则表达式
    le_name->setValidator(new QRegExpValidator(regExp,this));
    le_name->setPlaceholderText("用户账号");

    regExp.setPattern("^[A-Za-z 0-9]{6,}$");
    le_pwd->setValidator(new QRegExpValidator(regExp));
    le_pwd->setPlaceholderText("登录密码");

    le_truename->setPlaceholderText("姓名");
//    le_department->setPlaceholderText("科室");
//    le_hospital->setPlaceholderText("医院");

    regExp.setPattern("^((13[0-9])|(14[5|7])|(15([0-3]|[5-9]))|(18[0,5-9]))\\d{8}$");
    le_phoneNum->setValidator(new QRegExpValidator(regExp));
    le_phoneNum->setPlaceholderText("手机号码");

    regExp.setPattern("^([a-zA-Z0-9_-])+@([a-zA-Z0-9_-])+(([.][a-zA-Z0-9_-]{2,3}){1,2})$");
    le_email->setValidator(new QRegExpValidator(regExp));
    le_email->setPlaceholderText("电子邮箱");

    le_name->setFixedSize(500,40);
    le_pwd->setFixedSize(500,40);
    le_truename->setFixedSize(500,40);
    cbx_department->setFixedSize(500,40);
    cbx_hospital->setFixedSize(500,40);
    le_phoneNum->setFixedSize(500,40);
    le_email->setFixedSize(500,40);

    btn_sure = new QPushButton ();
    btn_sure->setFixedSize(110,43);
    btn_sure->setStyleSheet("QPushButton{border-image: url(:/picture/MessgeBox/sure-up.png);}"
                             "QPushButton:hover{border-image: url(:/picture/MessgeBox/sure-up.png);}"
                             "QPushButton:pressed{border-image: url(:/picture/MessgeBox/sure-down.png);}");

    btn_cancel = new QPushButton ();
    btn_cancel->setFixedSize(110,43);
    btn_cancel->setStyleSheet("QPushButton{border-image: url(:/picture/MessgeBox/cancel-up.png);}"
                                "QPushButton:hover{border-image: url(:/picture/MessgeBox/cancel-up.png);}"
                                "QPushButton:pressed{border-image: url(:/picture/MessgeBox/cancel-down.png);}");

    layout_name = new QHBoxLayout();
    layout_pwd = new QHBoxLayout();
    layout_truename= new QHBoxLayout();
    layout_department= new QHBoxLayout();
    layout_hospital= new QHBoxLayout();
    layout_phoneNum = new QHBoxLayout();
    layout_email = new QHBoxLayout();
    layout_btn = new QHBoxLayout();

    //=========================================================================
     //=========================================================================
     //=========================================================================
    mainLayout = new QVBoxLayout(this);

    layout_name->addSpacing(100);
    layout_name->addWidget(label_name);
    layout_name->addWidget(le_name);
    layout_name->addSpacing(100);

    layout_pwd->addSpacing(100);
    layout_pwd->addWidget(label_pwd);
    layout_pwd->addWidget(le_pwd);
    layout_pwd->addSpacing(100);

    layout_truename->addSpacing(100);
    layout_truename->addWidget(label_truename);
    layout_truename->addWidget(le_truename);
    layout_truename->addSpacing(100);

    layout_department->addSpacing(100);
    layout_department->addWidget(label_department);
    layout_department->addWidget(cbx_department);
    layout_department->addSpacing(100);

    layout_hospital->addSpacing(100);
    layout_hospital->addWidget(label_hospital);
    layout_hospital->addWidget(cbx_hospital);
    layout_hospital->addSpacing(100);

    layout_phoneNum->addSpacing(100);
    layout_phoneNum->addWidget(label_phoneNum);
    layout_phoneNum->addWidget(le_phoneNum);
    layout_phoneNum->addSpacing(100);

    layout_email->addSpacing(100);
    layout_email->addWidget(label_email);
    layout_email->addWidget(le_email);
    layout_email->addSpacing(100);

    layout_btn->addSpacing(100);
    layout_btn->addWidget(btn_sure);
    layout_btn->addWidget(btn_cancel);
    layout_btn->addSpacing(100);

    mainLayout->addSpacing(100);
    mainLayout->addLayout(layout_name);
    mainLayout->addLayout(layout_pwd);
    mainLayout->addLayout(layout_truename);
    mainLayout->addLayout(layout_hospital);
    mainLayout->addLayout(layout_department);

    mainLayout->addLayout(layout_phoneNum);
    mainLayout->addLayout(layout_email);
    mainLayout->addSpacing(100);
    mainLayout->addLayout(layout_btn);
    mainLayout->addSpacing(100);

    connect(btn_sure,SIGNAL(clicked()),this,SLOT(btn_addSlot()));
    connect(btn_cancel,SIGNAL(clicked()),this,SLOT(btn_cancelSlot()));


    //-----------------------
    Flag_Window=WinFlag;
    fresh_hospital_combobox();

}

void MyDialogAdd::fresh_hospital_combobox()
{
    cbx_hospital->clear();
    AddDelUpdSel op;
    QSqlQueryModel moddddel;
    op.selectData_ALL_hospital(moddddel);
    for(int i=0;i<moddddel.rowCount();i++)
    {
        QModelIndex index= moddddel.index(i,0);
       QString str= moddddel.data(index).toString();
        cbx_hospital->insertItem(i,str);
    }
}

void MyDialogAdd::fresh_department_combobox(QString text)
{
    cbx_department->clear();

    AddDelUpdSel op;
    QSqlQueryModel moddddel;
    qDebug()<<"医院名："<<text;
    op.selectData_department(text,moddddel);
    for(int i=0;i<moddddel.rowCount();i++)
    {
        QModelIndex index= moddddel.index(i,0);
        QString str= moddddel.data(index).toString();
        cbx_department->insertItem(i,str);
    }
}

void MyDialogAdd::btn_cancelSlot()
{
    this->close();
}

void MyDialogAdd::btn_addSlot()
{

    //--------------输入检测------------------
    if(le_name->text().isEmpty() || le_pwd->text().isEmpty() || le_phoneNum->text().isEmpty() || le_email->text().isEmpty()){
        QMessageBox::critical(this,QObject::tr("提示！"),QObject::tr("请输入完整信息！"));
        return;
    }
    QRegExp regExp("^((13[0-9])|(14[5|7])|(15([0-3]|[5-9]))|(18[0,5-9]))\\d{8}$");
    if(!regExp.exactMatch(le_phoneNum->text())){
        QMessageBox::critical(this,QObject::tr("提示！"),tr("请输入正确格式手机号码！"));
        return;
    }
    regExp.setPattern("^([a-zA-Z0-9_-])+@([a-zA-Z0-9_-])+(([.][a-zA-Z0-9_-]{2,3}){1,2})$");
    if(!regExp.exactMatch(le_email->text())){
        QMessageBox::critical(this,QObject::tr("提示！"),tr("请输入正确格式邮箱用户名！"));
        return;
    }

    //---------------数据查重------------------
    QString name = le_name->text();
    QString passward = le_pwd->text();
    QString truename = le_truename->text();
    QString department =cbx_department->currentText();
    QString hospital = cbx_hospital->currentText();
    QString phone_num = le_phoneNum->text();
    QString email = le_email->text();
    QSqlQuery query;
    query.exec("select usrname from usrinfo where usrname = ?;"); //账号
    query.bindValue(0,name,QSql::Out);
    query.exec();
    while(query.next()){
        QString msg="该用户名:"+name+" 已存在于【普通用户表】中，请重新命名。";
        QMessageBox::critical(this,QObject::tr("提示！"),msg);
        return;
    }
    QSqlQuery query1;
    query1.exec("select usrname from administator_usrinfo where usrname = ?;");
    query1.bindValue(0,name,QSql::Out);
    query1.exec();
    while(query1.next()){
        QString msg="该用户名:"+name+" 已存在于【管理员用户表】中，请重新命名。";
        QMessageBox::critical(this,QObject::tr("提示！"),msg);
        return;
    }

    //--------------执行新增------------------
    AddDelUpdSel op;
    bool b ;
    if(Flag_Window==ORDINARYUSER)
    {
        b= op.insertData_OrdinaryUser(name,passward,truename,department,hospital,phone_num,email);
    }
    if(Flag_Window==ADMINUSER)
    {
        b= op.insertData_AdminUser(name,passward,truename,department,hospital,phone_num,email);
    }

    if(b)
    {
        emit siganl_please_fresh_table(); //发送刷新表格信号

    }
    this->close();

}

void MyDialogAdd::slot_auto_fresh_department(QString text)
{
    qDebug()<<"根据医院名，罗列科室！";
    fresh_department_combobox(text);
}



