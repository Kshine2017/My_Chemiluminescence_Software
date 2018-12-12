#include "systemwidget.h"
#include <QString>

systemWidget::systemWidget(QWidget *parent)
    : QWidget(parent)
{

    widget = new QWidget(this);        //主窗口
    widget->setFixedSize(1686,1080);

    QPalette palette;
    QPixmap pixmap(":/picture/System/system_bg.png");
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    widget->setPalette(palette);    //放置背景图片

    tabWidget  = new QTabWidget(widget);
    userManage = new UserManagement();          //用户管理
    clinicalDiagnosis = new ClinicalDiagnosis();        //  科室与临床诊断
    reagentNumberWidget = new reagentNumber();          //试剂编号编辑界面
    systemMaintenance = new SystemMaintenance();       //系统维护
    faultDiagnosis = new FaultDiagnosis();             //故障诊断

    QIcon icon1(":/picture/System/userManage/user.png");
    QIcon icon2(":/picture/System/clinicalDiagnosis/bed.png");
    QIcon icon3(":/picture/System/systemMaintenance/system.png");
    QIcon icon4(":/picture/System/faultDiagnosis/diagnosis.png");
    tabWidget->addTab(userManage,icon1,tr("用户管理"));
    tabWidget->addTab(clinicalDiagnosis,icon2,tr("科室与临床诊断管理"));
    tabWidget->addTab(reagentNumberWidget,icon2,tr("试剂编号管理"));
    tabWidget->addTab(systemMaintenance,icon3,tr("系统维护"));
    tabWidget->addTab(faultDiagnosis,icon4,tr("故障诊断"));
    tabWidget->setFixedSize(1686,1080);
    /*
     * 样式表
     *min-width:110px;max-width:320px;min-height:22px;\
     * "QHeaderView::section{background-color:rgb(40,143,218);font:13pt '宋体';color: white;};"
     */
    QString tabBarStyle = "QTabBar::tab {\
        color: white;\
        font:12pt '宋体';\
        background-color:qlineargradient(x1:0, y1:0, x2:0, y2:1, stop: 0 #00a0a0, stop: 1 DarkTurquoise);\
        border: 2px solid;\
        border-top-left-radius: 8px;\
        border-top-right-radius: 8px;\
        padding:8px;}\
    QTabBar::tab:!selected {margin-top: 11px;} \
    QTabBar::tab:selected {color: black;}";
    tabWidget->setStyleSheet(tabBarStyle);

    questionBtn = new QPushButton(widget); //问号按钮
    questionBtn->setIconSize(QSize(46,45));
    questionBtn->setIcon(QIcon(":/picture/standardPrograme/？btn.png"));
    questionBtn->setFlat(true);
    questionBtn->setGeometry(1600,1,45,45);



}


