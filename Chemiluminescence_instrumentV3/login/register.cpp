#include "register.h"
#include <QDebug>
#include <QSqlError>
#include <QRegExpValidator>
Register::Register(QWidget *parent) : QDialog(parent)
{
    mainLayout = new QVBoxLayout(this);
    layout_register = new QVBoxLayout();
    setAutoFillBackground(true);
    QPalette palette;
    QPixmap pixmap(":/picture/login/register_background.jpg");
    palette.setBrush(QPalette::Window,QBrush(pixmap));
    setPalette(palette);
    setFixedSize(pixmap.size());

    lab_name = new QLabel;
    lab_name->setPixmap(QPixmap(":/picture/login/name_labal.png"));
    lab_pwd = new QLabel;
    lab_pwd->setPixmap(QPixmap(":/picture/login/password.png"));

    lab_truename = new QLabel;          //真实姓名
    lab_truename->setPixmap(QPixmap(":/picture/login/name.png"));
    lab_department = new QLabel;
    lab_department->setPixmap(QPixmap(":/picture/login/department.png"));
    lab_hospital= new QLabel;
    lab_hospital->setPixmap(QPixmap(":/picture/login/hospital.png"));


    lab_number = new QLabel;
    lab_number->setPixmap(QPixmap(":/picture/login/pthone.png"));
    lab_email = new QLabel;
    lab_email->setPixmap(QPixmap(":/picture/login/email.png"));


    QRegExp regExp("^[A-Za-z]{0,5}[0-9]{0,10}$"); //正则表达式
    le_name = new QLineEdit();
    le_name->setFixedSize(530,40);
    le_name->setFont(QFont("le_name",16));
    le_name->setValidator(new QRegExpValidator(regExp,this));
    le_name->setFocus();

    le_pwd = new QLineEdit();
    le_pwd->setFixedSize(530,40);
    le_pwd->setFont(QFont("le_name",16));
    regExp.setPattern("^[A-Za-z 0-9]{6,}$");
    le_pwd->setValidator(new QRegExpValidator(regExp));

    le_truename = new QLineEdit();
    le_truename->setFixedSize(530,40);
    le_truename->setFont(QFont("le_name",16));
    com_department= new QComboBox();
    com_department->setFixedSize(530,40);
    com_department->setFont(QFont("le_name",16));
    com_hospital = new QComboBox();
    com_hospital->setFixedSize(530,40);
    com_hospital->setFont(QFont("le_name",16));

    connect(com_hospital,SIGNAL(currentTextChanged(QString)),this,SLOT(slot_auto_fresh_department(QString)));
    fresh_hospital_combobox();

    le_number = new QLineEdit();
    le_number->setFixedSize(530,40);
    le_number->setFont(QFont("le_name",16));
    regExp.setPattern("^((13[0-9])|(14[5|7])|(15([0-3]|[5-9]))|(18[0,5-9]))\\d{8}$");
    le_number->setValidator(new QRegExpValidator(regExp));

    le_email = new QLineEdit();
    le_email->setFixedSize(530,40);
    le_email->setFont(QFont("le_name",16));
    regExp.setPattern("^([a-zA-Z0-9_-])+@([a-zA-Z0-9_-])+(([.][a-zA-Z0-9_-]{2,3}){1,2})$");
    le_email->setValidator(new QRegExpValidator(regExp));

    le_name->setPlaceholderText("用户账号");
    le_pwd->setPlaceholderText("登录密码");
    le_truename->setPlaceholderText("姓名");
    le_number->setPlaceholderText("手机号码");
    le_email->setPlaceholderText("电子邮箱");

    layout_name = new QHBoxLayout();
    layout_pwd = new QHBoxLayout();
    layout_truename = new QHBoxLayout();
    layout_department = new QHBoxLayout();
    layout_hospital = new QHBoxLayout();
    layout_number = new QHBoxLayout();
    layout_email = new QHBoxLayout();
    layout_btn = new QHBoxLayout();

    layout_name->addSpacing(100);
    layout_name->addWidget(lab_name);
    layout_name->addWidget(le_name);
    layout_name->addSpacing(169);

    layout_pwd->addSpacing(100);
    layout_pwd->addWidget(lab_pwd);
    layout_pwd->addWidget(le_pwd);
    layout_pwd->addSpacing(169);

    layout_truename->addSpacing(100);
    layout_truename->addWidget(lab_truename);
    layout_truename->addWidget(le_truename);
    layout_truename->addSpacing(169);

    layout_department->addSpacing(100);
    layout_department->addWidget(lab_department);
    layout_department->addWidget(com_department);
    layout_department->addSpacing(169);

    layout_hospital->addSpacing(100);
    layout_hospital->addWidget(lab_hospital);
    layout_hospital->addWidget(com_hospital);
    layout_hospital->addSpacing(169);

    layout_number->addSpacing(100);
    layout_number->addWidget(lab_number);
    layout_number->addWidget(le_number);
    layout_number->addSpacing(169);

    layout_email->addSpacing(100);
    layout_email->addWidget(lab_email);
    layout_email->addWidget(le_email);
    layout_email->addSpacing(169);


    btn_register = new QPushButton;
    btn_register->setFixedSize(297,87);
    btn_register->setStyleSheet("QPushButton{border-image: url(:/picture/login/register-up.png);}"
                              "QPushButton:hover{border-image: url(:/picture/login/register-up.png);}"
                              "QPushButton:pressed{border-image: url(:/picture/login/register-down.png);}");
    btn_register->setFlat(true);

    btn_cancel = new QPushButton;
    btn_cancel->setFixedSize(297,87);
    btn_cancel->setStyleSheet("QPushButton{border-image: url(:/picture/login/cancel-up.png);}"
                              "QPushButton:hover{border-image: url(:/picture/login/cancel-up.png);}"
                              "QPushButton:pressed{border-image: url(:/picture/login/cancel-down.png);}");
    btn_cancel->setFlat(true);
    layout_btn->addSpacing(140);
    layout_btn->addWidget(btn_register);
    layout_btn->addSpacing(80);
    layout_btn->addWidget(btn_cancel);
    layout_btn->addSpacing(180);



    layout_register->addSpacing(100);
    layout_register->addLayout(layout_name);
    layout_register->addLayout(layout_pwd);
    layout_register->addLayout(layout_truename);
    layout_register->addLayout(layout_hospital);
    layout_register->addLayout(layout_department);
    layout_register->addLayout(layout_number);
    layout_register->addLayout(layout_email);
    layout_register->addSpacing(100);
    layout_register->addLayout(layout_btn);
    layout_register->addSpacing(100);
    mainLayout->addLayout(layout_register);

    //去掉窗口图标
    this->setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint);
    setWindowTitle("注册界面");
    resize(960,540);

    connect(btn_cancel,SIGNAL(clicked()),this,SLOT(cancel()));
    connect(btn_register,SIGNAL(clicked()),this,SLOT(user_register()));
}

Register::~Register()
{
    delete mainLayout;
    delete layout_register;
    delete layout_name;
    delete layout_pwd;
    delete layout_number;
    delete layout_email;
    delete layout_btn;

    delete lab_name;
    delete lab_pwd;
    delete lab_number;
    delete lab_email;

    delete le_title;
    delete le_name;
    delete le_pwd;
    delete le_number;
    delete le_email;

    delete btn_register;
    delete btn_cancel;


}

/**
 * @brief 点击注册新用户按钮信号槽
 */
void Register::user_register()
{
    QSqlQuery query;
    QRegExp regExp("^((13[0-9])|(14[5|7])|(15([0-3]|[5-9]))|(18[0,5-9]))\\d{8}$");
    if(!regExp.exactMatch(le_number->text())){
        QMessageBox::critical(this,QObject::tr("提示！"),tr("请输入正确格式手机号码！"));
        return;
    }
    regExp.setPattern("^([a-zA-Z0-9_-])+@([a-zA-Z0-9_-])+(([.][a-zA-Z0-9_-]{2,3}){1,2})$");
    if(!regExp.exactMatch(le_email->text())){
        QMessageBox::critical(this,QObject::tr("提示！"),tr("请输入正确格式邮箱用户名！"));
        return;
    }
    if(le_name->text().isEmpty() || le_pwd->text().isEmpty() || le_number->text().isEmpty() || le_email->text().isEmpty()){
        QMessageBox::critical(this,QObject::tr("错误代码:E0017"),QObject::tr("请输入完整信息！"));
        return;
    }
    QString name = le_name->text();
    QString passward = le_pwd->text();
    QString truename = le_truename->text();
    QString department =com_department->currentText();
    QString hospital = com_hospital->currentText();
    QString phone_num = le_number->text();
    QString email = le_email->text();
    query.exec("select usrname from usrinfo where usrname = ?");
    query.bindValue(0,name,QSql::Out);
    query.exec();
    while(query.next()){
        QMessageBox::critical(this,QObject::tr("提示！"),tr("注册用户名已存在，请重新命名。"));
        return;
    }

    query.exec("select usrname from administator_usrinfo where usrname = ?");

    query.bindValue(0,name,QSql::Out);
    query.exec();
    while(query.next()){
        QMessageBox::critical(this,QObject::tr("提示！"),tr("注册用户名已存在，请重新命名。"));
        return;
    }
    query.exec("insert into usrinfo values(?,?,?,?,?,?,?,?,?,?,?,?)");
    query.bindValue(0,name);
    query.bindValue(1,passward);
    query.bindValue(2,phone_num);
    query.bindValue(3,email);
    query.bindValue(4,truename);
    query.bindValue(5,department);
    query.bindValue(6,hospital);
    query.bindValue(7,0);
    query.bindValue(8,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    query.bindValue(9,0);
    query.bindValue(10,0);
    query.bindValue(11,0);
    if(!query.exec())
    {
        QMessageBox::critical(this,QObject::tr("错误代码:E0016"),query.lastError().text());
    }
    QDialog::accept();
}

/**
 * @brief 取消按钮信号槽
 */
void Register::cancel()
{
//如果取消 "取消按钮"
    if(!le_name->text().isEmpty() && !le_pwd->text().isEmpty() && !le_number->text().isEmpty() && !le_email->text().isEmpty()){
        if(QMessageBox::warning(this,QString(tr("提示！")),QString(tr("注册用户名没有保存！")),QMessageBox::Ok,QMessageBox::Cancel) == QMessageBox::Cancel)
        {


        }else QDialog::accept();
    }else QDialog::accept();
}

void Register::slot_auto_fresh_department(QString text)
{
    qDebug()<<"根据医院名，罗列科室！";
    fresh_department_combobox(text);
}

void Register::fresh_hospital_combobox()
{
    com_hospital->clear();
    AddDelUpdSel op;
    QSqlQueryModel moddddel;
    op.selectData_ALL_hospital(moddddel);
    for(int i=0;i<moddddel.rowCount();i++)
    {
        QModelIndex index= moddddel.index(i,0);
        QString str= moddddel.data(index).toString();
        com_hospital->insertItem(i,str);
    }
}

void Register::fresh_department_combobox(QString text)
{
    com_department->clear();

    AddDelUpdSel op;
    QSqlQueryModel moddddel;
    qDebug()<<"医院名："<<text;
    op.selectData_department(text,moddddel);
    for(int i=0;i<moddddel.rowCount();i++)
    {
        QModelIndex index= moddddel.index(i,0);
        QString str= moddddel.data(index).toString();
        com_department->insertItem(i,str);
    }
}
