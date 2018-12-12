#ifndef MYDIALOGUPDATE_H
#define MYDIALOGUPDATE_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "adddelupdsel.h"

class MyDialogUpdate : public QDialog
{
    Q_OBJECT
public:
    //explicit MyDialogUpdate(QDialog *parent = 0);
    explicit MyDialogUpdate(QWidget *parent = 0, const QString name=NULL, const QString password=NULL, const QString truename=NULL, const QString department=NULL, const QString hospital=NULL, const QString telephone=NULL, const QString mail=NULL, WF_enum WinFlag=NOUSER);
    QVBoxLayout *mainLayout;
    WF_enum Flag_Window;

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
    QLineEdit *le_department;
    QLineEdit *le_hospital;
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

signals:
    void siganl_please_fresh_table();
public slots:
    void btn_cancelSlot();
    void btn_addSlot();
};

#endif // MYDIALOGUPDATE_H
