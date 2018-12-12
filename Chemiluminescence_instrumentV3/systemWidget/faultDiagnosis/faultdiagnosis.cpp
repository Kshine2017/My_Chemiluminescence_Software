#include "faultdiagnosis.h"

FaultDiagnosis::FaultDiagnosis(QWidget *parent) : QWidget(parent)
{
    init();
}

void FaultDiagnosis::init()
{
    widget = new QWidget(this);           //主窗口
    widget->setFixedSize(1671,1008);
    widget->setAutoFillBackground(true);

    QPalette palette;
    QPixmap pixmap(":/picture/System/faultDiagnosis/fault_bg.png");
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    widget->setPalette(palette);    //放置背景图片

    tabWidget = new QTabWidget(widget);           //
//    tabWidget->setFixedSize(1600,1000);
    tabWidget->setGeometry(15,5,1640,950);
    tableView_History = new QTableView();           //历史状态信息查询
    tableView_Fault = new QTableView();           //故障状态信息查询

    tabWidget->addTab(tableView_History,tr("历史状态信息查询"));
    tabWidget->addTab(tableView_Fault,tr("故障状态信息查询"));
}
