#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QFont>
#include <QTextEdit>
#include <QPalette>
#include <QDebug>
#include <QPixmap>
#include <QIcon>
#include <QMessageBox>
#include <QtSql>
#include <login/register.h>
class Login : public QDialog
{
    Q_OBJECT

public:
    Login(QWidget *parent = 0);
    ~Login();

    QVBoxLayout *mainLayout;//主布局
private:
    QWidget *center_window;

    QVBoxLayout *layout_user;//用户布局
    QHBoxLayout *layout_name;//用户名
    QHBoxLayout *layout_pwd;//密码

    QHBoxLayout *layout_login;//登录、注册
    QHBoxLayout *layout_register;

    QLabel *lab_name;
    QLabel *lab_pwd;
    QLineEdit *le_pwd;
    QLineEdit *le_name;

    QPushButton *btn_login;
    QPushButton *btn_register;
    QPushButton *btn_exist;

    Register *register_Dialog;

public slots:
    void cancel(void);
    void user_login(void);
    void user_register(void);
};

#endif // LOGIN_H
