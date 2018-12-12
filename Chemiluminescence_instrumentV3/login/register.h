#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFont>
#include <QPalette>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QtSql>
#include <systemWidget/userManage/adddelupdsel.h>
class Register : public QDialog
{
    Q_OBJECT
public:
    explicit Register(QWidget *parent = 0);
    ~Register();
private:
    QVBoxLayout *mainLayout;
    QVBoxLayout *layout_register;
    QHBoxLayout *layout_name;
    QHBoxLayout *layout_pwd;
    QHBoxLayout *layout_number;
    QHBoxLayout *layout_email;

    QHBoxLayout *layout_btn;

    QLabel *lab_name;
    QLabel *lab_pwd;
    QLabel *lab_number;
    QLabel *lab_email;

    QLineEdit *le_title;
    QLineEdit *le_name;
    QLineEdit *le_pwd;
    QLineEdit *le_number;
    QLineEdit *le_email;

    QPushButton * btn_register;
    QPushButton *btn_cancel;

    QPalette *palette;
    QFont *font_title;


    //--------------------
    QLabel *lab_truename;
    QLabel *lab_department;
    QLabel *lab_hospital;
    //--------------------
    //---------------------
    QLineEdit *le_truename;
    QComboBox *com_department;
    QComboBox *com_hospital;
    //--------------------
    QHBoxLayout *layout_truename;
    QHBoxLayout *layout_department;
    QHBoxLayout *layout_hospital;

    void fresh_hospital_combobox();
    void fresh_department_combobox(QString text);


signals:

public slots:
    void user_register();
    void cancel();
    void slot_auto_fresh_department(QString text);
};

#endif // REGISTER_H
