#ifndef MYDIALOGADD_H
#define MYDIALOGADD_H

#include <QWidget>
#include <QDialog>

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "../qmysqlquerymodel.h"
#include "adddelupdsel.h"
#include <QComboBox>
class MyDialogAdd : public QDialog
{
    Q_OBJECT
public:
    explicit MyDialogAdd(QWidget *parent = 0,WF_enum WinFlag=NOUSER);
    WF_enum Flag_Window;
    QVBoxLayout *mainLayout;

    QLabel *label_name;
    QLabel *label_pwd;
    //--------------------
    QLabel *label_truename;
    QLabel *label_department;
    QLabel *label_hospital;
    //--------------------
    QLabel *label_phoneNum;
    QLabel *label_email;

    QLineEdit *le_name;
    QLineEdit *le_pwd;
    //---------------------
    QLineEdit *le_truename;

    QComboBox* cbx_department;
    QComboBox* cbx_hospital;
    //--------------------
    QLineEdit *le_phoneNum;
    QLineEdit *le_email;
    QMySQlQueryModel model;
    QHBoxLayout *layout_name;
    QHBoxLayout *layout_pwd;
    QHBoxLayout *layout_truename;
    QHBoxLayout *layout_department;
    QHBoxLayout *layout_hospital;
    QHBoxLayout *layout_phoneNum;
    QHBoxLayout *layout_email;
    QHBoxLayout *layout_btn;

    QPushButton *btn_sure;
    QPushButton *btn_cancel;


    void fresh_hospital_combobox();
    void fresh_department_combobox(QString text);

signals:
    void siganl_please_fresh_table();
public slots:

    void btn_cancelSlot();
    void btn_addSlot();
    void slot_auto_fresh_department(QString text);

};

#endif // MYDIALOGADD_H
