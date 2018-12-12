#ifndef SYSTEMWIDGET_H
#define SYSTEMWIDGET_H

#include <QMainWindow>
#include <QTabWidget>
#include <systemWidget/userManage/usermanagement.h>
#include <systemWidget/clinicalDiagnosis/clinicaldiagnosis.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <systemWidget/systemMaintenance/systemmaintenance.h>
#include <systemWidget/faultDiagnosis/faultdiagnosis.h>
#include "reagentNumber/reagentnumber.h"

class systemWidget : public QWidget
{
    Q_OBJECT

public:
    systemWidget(QWidget *parent = 0);
    QPushButton *questionBtn;   //问号按钮
    QTabWidget *tabWidget;      //表格
private:

    QVBoxLayout *mainLayout; //主界面
    QWidget *widget;
    QLabel *lab_bg;          //放置背景图片 
    UserManagement *userManage;     //用户管理
    ClinicalDiagnosis *clinicalDiagnosis;       //科室与临床诊断
    reagentNumber *reagentNumberWidget;         //试剂编号编辑界面
    SystemMaintenance *systemMaintenance;       //系统维护
    FaultDiagnosis *faultDiagnosis;             //故障诊断

};


#endif // SYSTEMWIDGET_H
