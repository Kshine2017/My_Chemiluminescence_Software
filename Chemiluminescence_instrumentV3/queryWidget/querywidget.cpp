#include "querywidget.h"
#include <QString>

queryWidget::queryWidget(QWidget *parent)
    : QWidget(parent)
{
    init();
}

void queryWidget::init()
{
    widget = new QWidget(this);
    widget->setFixedSize(1685,1080);

    QPalette palette;
    QPixmap pixmap(":/System/userManage/user_bg.png");
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    widget->setPalette(palette);    //放置背景图片

    tabWidget = new QTabWidget(widget);
    tabWidget->setGeometry(6,5,1660,1070);

    questionBtn = new QPushButton(widget); //问号按钮
    questionBtn->setIconSize(QSize(46,45));
    questionBtn->setIcon(QIcon(":/picture/standardPrograme/？btn.png"));
    questionBtn->setFlat(true);
    questionBtn->setGeometry(1600,1,45,45);

    history = new HistorySearch();
    qualityData = new QualityDataQuery();
    QIcon icon1(":/picture/query/historyQuery/historyQuery.png");
    QIcon icon2(":/picture/query/qualityDataQuery/qualityDataQuery.png");

    tabWidget->addTab(history,icon1,QString(tr("历史查询")));
    tabWidget->addTab(qualityData,icon2,QString(tr("质控数据查询")));
    /*
     * 样式表
     * "QHeaderView::section{background-color:rgb(40,143,218);font:13pt '宋体';color: white;};"
     */
    QString tabBarStyle = "QTabBar::tab {min-width:140px;\
            min-height:22px;\
        color: white;\
        font:14pt '宋体';\
        background-color:qlineargradient(x1:0, y1:0, x2:0, y2:1, stop: 0 #00a0a0, stop: 1 DarkTurquoise);\
        border: 2px solid;\
        border-top-left-radius: 8px;\
        border-top-right-radius: 8px;\
        padding:8px;}\
    QTabBar::tab:!selected {margin-top: 11px;} \
    QTabBar::tab:selected {color: black;}";
    tabWidget->setStyleSheet(tabBarStyle);

//    setAutoFillBackground(true);
//    showFullScreen();   //全屏显示

}



