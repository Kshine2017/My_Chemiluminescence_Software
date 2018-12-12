
#include "login.h"
#include <QDebug>
#include <QIcon>
#include "Serial_port/serialport.h"
#include "data/configfile.h"
Login::Login(QWidget *parent)
    : QDialog(parent)
{
   setWindowState(Qt::WindowMaximized);//全屏
//    setWindowFlags(Qt::Dialog);
//    showFullScreen();
/*设置界面的窗口背景*/
    setAutoFillBackground(true);
    QPalette palette;
    QPixmap pixmap(":/picture/login/WindowBackground.jpg");
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    setPalette(palette);

//透明背景
    center_window = new QWidget(this);
    center_window->setAutoFillBackground(true);
    QPalette center_palette;
    QPixmap center_pixmap(":/picture/login/login_background.png");
    center_palette.setBrush(QPalette::Window,QBrush(center_pixmap));
    center_window->setPalette(center_palette);
    center_window->setGeometry(533,320,853,531);

    mainLayout = new QVBoxLayout(center_window);
//用户
    layout_user = new QVBoxLayout();
    layout_user->setMargin(0);
    layout_name = new QHBoxLayout();
    layout_name->setMargin(0);

//用户名
    lab_name = new QLabel;
    lab_name->setPixmap(QPixmap(":/picture/login/name_labal.png"));
    le_name = new QLineEdit;
    le_name->setFixedSize(530,88);
    le_name->setFont(QFont("le_name",30));
    le_name->setFocus();  //设置鼠标聚焦于此控件
    QRegExp regExp("[A-Za-z]{0,5}[0-9]{0,10}"); //正则表达式
    le_name->setValidator(new QRegExpValidator(regExp,this));

    layout_name->addSpacing(90);
    layout_name->addWidget(lab_name);
    layout_name->addWidget(le_name);
    layout_name->addSpacing(240);

//密码
    layout_pwd = new QHBoxLayout();
    layout_pwd->setMargin(0);
    lab_pwd = new QLabel;
    lab_pwd->setPixmap(QPixmap(":/picture/login/password.png"));
    le_pwd = new QLineEdit();
    le_pwd->setFont(QFont("le_pwd",30));
    le_pwd->setEchoMode(QLineEdit::Password);  //设置输入为密码模式
    le_pwd->setFixedSize(530,88);
    regExp.setPattern("^[A-Za-z 0-9]{6,}$");
    le_pwd->setValidator(new QRegExpValidator(regExp));

    layout_pwd->addSpacing(90);
    layout_pwd->addWidget(lab_pwd);
    layout_pwd->addWidget(le_pwd);
    layout_pwd->addSpacing(240);

//按钮水平布局
    layout_login = new QHBoxLayout();

//登陆案钮
    btn_login = new QPushButton;
    btn_login->setFixedSize(297,87);
    btn_login->setStyleSheet("QPushButton{border-image: url(:/picture/login/login-up.png);}"
                               "QPushButton:hover{border-image: url(:/picture/login/login-up.png);}"
                               "QPushButton:pressed{border-image: url(:/picture/login/login-down.png);}");
    btn_login->setFlat(true);
    btn_login->setShortcut(Qt::Key_Return);
//取消按钮
    btn_exist = new QPushButton;
    btn_exist->setFixedSize(297,87);
    btn_exist->setStyleSheet("QPushButton{border-image: url(:/picture/login/cancel-up.png);}"
                              "QPushButton:hover{border-image: url(:/picture/login/cancel-up.png);}"
                              "QPushButton:pressed{border-image: url(:/picture/login/cancel-down.png);}");
    btn_exist->setFlat(true);



    layout_login->addSpacing(140);
    layout_login->addWidget(btn_login);
    layout_login->addSpacing(80);
    layout_login->addWidget(btn_exist);
    layout_login->addSpacing(180);


    layout_user->addLayout(layout_name);
    layout_user->addSpacing(40);
    layout_user->addLayout(layout_pwd);

//注册
    btn_register = new QPushButton;
    btn_register->setIconSize(QSize(153,44));
    btn_register->setIcon(QIcon(":/picture/login/register.png"));
    btn_register->setFlat(true);

    layout_register = new QHBoxLayout;
    layout_register->addSpacing(82);
    layout_register->addWidget(btn_register);
    layout_register->addSpacing(595);


//主布局
    mainLayout->addSpacing(20);
    mainLayout->addLayout(layout_user);
    mainLayout->addSpacing(40);
    mainLayout->addLayout(layout_register);
    mainLayout->addLayout(layout_login);
    mainLayout->addSpacing(20);

    showFullScreen();   //全屏显示
    connect(btn_login,SIGNAL(clicked()),this,SLOT(user_login()));
    connect(btn_exist,SIGNAL(clicked()),this,SLOT(cancel()));
    connect(btn_register,SIGNAL(clicked()),this,SLOT(user_register()));

}

/**
 * @brief 登录按钮信号槽
 */
void Login::user_login()
{
    QString nnnname,department,hospital;int status;
    if(le_name->text().isEmpty() || le_pwd->text().isEmpty()){
        if(le_name->text().isEmpty()){
            QMessageBox::information(this,tr("请输入用户名"),tr("请先输入用户名再登录！"),QMessageBox::Ok);
            le_name->setFocus();
        }else{
            QMessageBox::information(this,tr("请输入密码"),tr("请先输入密码再登录！"),QMessageBox::Ok);
            le_pwd->setFocus();
        }
    }else{
        QSqlQuery query;
        query.exec("select usrname,pwd,name,department,hospital from usrinfo"); //普通用户
        while(query.next()){
            if(query.value(0).toString() == le_name->text()){
                if( query.value(1).toString() == le_pwd->text())
                {
                    QDialog::accept();
                    nnnname=query.value(2).toString();
                    status=0;
                    department=query.value(3).toString();
                    hospital  =query.value(4).toString();
                    goto Ok;
                }else{
                    QMessageBox::warning(this,tr("提示"),tr("请输入正确的密码！"),QMessageBox::Ok);
                    le_pwd->clear();
                    le_pwd->setFocus();
                    goto password_err;
                }
            }
        }

        query.exec("select usrname,pwd,name,department,hospital from administator_usrinfo");//管理员用户
        while(query.next()){
            if(query.value(0).toString() == le_name->text()){
                if(query.value(1).toString() == le_pwd->text()){
                    QDialog::accept();
                    nnnname=query.value(2).toString();
                    status=1;
                    department=query.value(3).toString();
                    hospital  =query.value(4).toString();
                    goto Ok;
                }else{
                    QMessageBox::warning(this,tr("提示"),tr("请输入正确的密码！"),QMessageBox::Ok);
                    le_pwd->clear();
                    le_pwd->setFocus();
                    goto password_err;
                }
            }
        }

        QMessageBox::warning(this,tr("提示"),tr("你输入的用户名不存在！"),QMessageBox::Ok);
        le_name->clear();
        le_pwd->clear();
        le_name->setFocus();
        password_err:return;
        Ok:
          qInfo() << le_name->text() << "登录成功";
          ConfigFile cp;
          cp.saveCurrentUser(le_name->text(),le_pwd->text(),nnnname,status,department,hospital);
          serialPort::mySend_Data("01,00,ff,ff,00,00");
          qDebug() << "发送进入未知品阶段命令一次";
        return;
    }
}
/**
 * @brief 注册新用户按钮
 */
void Login::user_register()
{
    register_Dialog = new  Register;
    if(register_Dialog->exec() == QDialog::Accepted){   //模式对话框

    }

}
void Login::cancel()
{
    QDialog::reject();

}

Login::~Login()
{

}
