#include "usermanagement.h"
#include <systemWidget/userManage/ordinaryusermanagement.h>

#include "adminitratormanagement.h"

UserManagement::UserManagement(QWidget *parent) : QWidget(parent)
{
    widget = new QWidget(this);         //主窗口
    widget->setFixedSize(1671,1010);
    widget->setAutoFillBackground(true);
    QPalette palette;
    QPixmap pixmap(":/picture/System/userManage/user_bg.png");
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    widget->setPalette(palette);    //放置背景图片

    tabWidget = new QTabWidget(widget);
    tabWidget->setFixedSize(1671,1010);

    OrdinaryUserManagement *ordinaryUserMana = new OrdinaryUserManagement();
    AdminitratorManagement *ordinaryUserMana2 = new AdminitratorManagement();

    tabWidget->addTab(ordinaryUserMana,tr("普通用户管理"));
    tabWidget->addTab(ordinaryUserMana2,tr("管理员管理"));

}
