#include "mydialogupdate.h"
#include <QRegExpValidator>



MyDialogUpdate::MyDialogUpdate(QWidget *parent, const QString name,const QString password,const QString truename,const QString department,const QString hospital,const QString telephone, const QString mail, WF_enum WinFlag): QDialog(parent)
{
    setWindowModality(Qt::ApplicationModal);
    this->setWindowTitle(tr("更改用户信息"));
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
    le_department = new QLineEdit ();;
    le_hospital = new QLineEdit ();
    le_phoneNum = new QLineEdit ();
    le_email = new QLineEdit ();





    QRegExp regExp("^[A-Za-z]{0,5}[0-9]{0,10}$"); //正则表达式
    le_name->setValidator(new QRegExpValidator(regExp,this));
    le_name->setPlaceholderText("用户账号");

    regExp.setPattern("^[A-Za-z 0-9]{6,}$");
    le_pwd->setValidator(new QRegExpValidator(regExp));
    le_pwd->setPlaceholderText("登录密码");

    le_truename->setPlaceholderText("姓名");
    le_department->setPlaceholderText("科室");
    le_hospital->setPlaceholderText("医院");

    regExp.setPattern("^((13[0-9])|(14[5|7])|(15([0-3]|[5-9]))|(18[0,5-9]))\\d{8}$");
    le_phoneNum->setValidator(new QRegExpValidator(regExp));
    le_phoneNum->setPlaceholderText("手机号码");

    regExp.setPattern("^([a-zA-Z0-9_-])+@([a-zA-Z0-9_-])+(([.][a-zA-Z0-9_-]{2,3}){1,2})$");
    le_email->setValidator(new QRegExpValidator(regExp));
    le_email->setPlaceholderText("电子邮箱");

    le_name->setFixedSize(500,40);
    le_pwd->setFixedSize(500,40);
    le_truename->setFixedSize(500,40);
    le_department->setFixedSize(500,40);
    le_hospital->setFixedSize(500,40);
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
    layout_department->addWidget(le_department);
    layout_department->addSpacing(100);

    layout_hospital->addSpacing(100);
    layout_hospital->addWidget(label_hospital);
    layout_hospital->addWidget(le_hospital);
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
    mainLayout->addLayout(layout_department);
    mainLayout->addLayout(layout_hospital);
    mainLayout->addLayout(layout_phoneNum);
    mainLayout->addLayout(layout_email);
    mainLayout->addSpacing(100);
    mainLayout->addLayout(layout_btn);
    mainLayout->addSpacing(100);

    connect(btn_sure,SIGNAL(clicked()),this,SLOT(btn_addSlot()));
    connect(btn_cancel,SIGNAL(clicked()),this,SLOT(btn_cancelSlot()));


    //-------------------------
    le_name ->setText(name);
    le_pwd ->setText(password);
    le_truename ->setText(truename);
    le_department ->setText(department);
    le_hospital ->setText(hospital);
    le_phoneNum ->setText(telephone);
    le_email ->setText(mail);
    Flag_Window=WinFlag;
    //-------------------------
    le_name->setEnabled(false);
}

void MyDialogUpdate::btn_cancelSlot()
{
    this->close();
}

void MyDialogUpdate::btn_addSlot()
{

    QString name = le_name->text();
    QString passward = le_pwd->text();
    QString truename = le_truename->text();
    QString department =le_department->text();
    QString hospital = le_hospital->text();
    QString phone_num = le_phoneNum->text();
    QString email = le_email->text();

    AddDelUpdSel op;
    bool b ;
    if(Flag_Window==ORDINARYUSER)
        b= op.updateData_OrdinaryUser(name,passward,truename,department,hospital,phone_num,email);
    if(Flag_Window==ADMINUSER)
        b=op.updateData_AdminUser(name,passward,truename,department,hospital,phone_num,email);
    if(b)
    {
        emit siganl_please_fresh_table();

    }
    this->close();

}
