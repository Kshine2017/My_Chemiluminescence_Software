#include "systemmaintenance.h"

SystemMaintenance::SystemMaintenance(QWidget *parent) : QWidget(parent)
{
    init();

    connect(btn_AutomaticDay,SIGNAL(clicked()),this,SLOT(automaticDayMaintain()));
    connect(btn_AutomaticWeek,SIGNAL(clicked()),this,SLOT(automaticWeekMaintain()));

    connect(btn_Instrument,SIGNAL(clicked()),this,SLOT(initInstrument()));
    connect(btn_PMT,SIGNAL(clicked()),this,SLOT(testPMT()));



    connect(btn_start,SIGNAL(clicked()),this,SLOT(startMaintain()));
    connect(btn_pause,SIGNAL(clicked()),this,SLOT(pauseMaintain()));
    connect(btn_continue,SIGNAL(clicked()),this,SLOT(continueMaintain()));

    connect(btn_InstrumentStart,SIGNAL(clicked()),this,SLOT(startInstrument()));
    connect(btn_InstrumentStop,SIGNAL(clicked()),this,SLOT(stopInstrument()));
}
//自动日维护
void SystemMaintenance::automaticDayMaintain(){}
//自动周维护
void SystemMaintenance::automaticWeekMaintain(){}
//仪器初始化及运行待机状态
void SystemMaintenance::initInstrument(){}
//PMT背景检测
void SystemMaintenance::testPMT(){}

//开始每日维护
void SystemMaintenance::startMaintain(){}
//暂停每日维护
void SystemMaintenance::pauseMaintain(){}
//继续每日维护
void SystemMaintenance::continueMaintain(){}

//开始仪器初始化
void SystemMaintenance::startInstrument(){}
//结束仪器初始化
void SystemMaintenance::stopInstrument(){}

//初始化界面
void SystemMaintenance::init()
{
    mainLayout = new QVBoxLayout();
    widget = new QWidget(this);         //主窗口
    widget->setFixedSize(1671,1000);
    widget->setAutoFillBackground(true);

    QPalette palette;
    QPixmap pixmap(":/picture/System/systemMaintenance/sysbg.png");
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    widget->setPalette(palette);    //放置背景图片
    layout_la = new QHBoxLayout(widget);      //放置两个layout
    layout_RoutineMaintain = new QVBoxLayout();         //日常维护


    layout_SingleMaintain = new QVBoxLayout();          //仪器维护单项操作
    layout_btn_routine = new QHBoxLayout();             //日常维护按钮
    layout_btn_single = new QHBoxLayout();              //仪器维护单项操作按钮

    layout_btn_AutomaticDay = new QHBoxLayout();        //调整按钮btn_AutomaticDay的位置
    layout_btn_AutomaticWeek = new QHBoxLayout();        //调整按钮btn_AutomaticWeek的位置
    layout_btn_Instrument = new QHBoxLayout();        //调整按钮btn_Instrument的位置
    layout_btn_PMT = new QHBoxLayout();        //调整按钮btn_PMT的位置


    label_RoutineMaintain = new QLabel(QString(tr("仅日常维护")));               //标签日常维护
    label_RoutineMaintain->setFont(QFont("宋体",20));
    label_RoutineMaintain->setFixedSize(720,36);





    btn_AutomaticDay = new QPushButton(QString(tr("自动日维护")));         //自动日维护
    btn_AutomaticDay->setFont(QFont("宋体",20));
    btn_AutomaticDay->setFixedSize(200,45);
    btn_AutomaticDay->setFlat(true);
    QIcon icon5(":/picture/System/systemMaintenance/checked.png");
    btn_AutomaticDay->setIcon(icon5);
    btn_AutomaticDay->setIconSize(QSize(36,36));

    btn_AutomaticWeek = new QPushButton(QString(tr("自动周维护")));         //自动周维护
    btn_AutomaticWeek->setFont(QFont("宋体",20));
    btn_AutomaticWeek->setFixedSize(200,45);
//    label_AutomaticWeek->setText("<img src ='://System/systemMaintenance/week.png'/>自动周维护");
    btn_AutomaticWeek->setFlat(true);
    QIcon icon6(":/picture/System/systemMaintenance/unchecked.png");
    btn_AutomaticWeek->setIcon(icon6);
    btn_AutomaticWeek->setIconSize(QSize(36,36));




    tableView_RoutineMaintain = new QTableView();         //日常维护表
    tableView_RoutineMaintain->setFixedSize(650,520);
    tableView_SingleMaintain = new QTableView();         //仪器维护单项操作表
    tableView_SingleMaintain->setFixedSize(650,520);




    //    btn_start = new QPushButton(QString(tr("开始日常维护")));         //开始日常维护
    //    btn_start->setFont(QFont("宋体",20));
    //    btn_start->setFlat(true);
    //    QIcon icon1(":/picture/System/systemMaintenance/start.png");
    //    btn_start->setIcon(icon1);
    //    btn_start->setIconSize(QSize(26,26));
    //    btn_start->setFixedHeight(32);

        btn_start = new QPushButton();
        btn_start->setFlat(true);
        btn_start->setFocusPolicy(Qt::TabFocus);
        btn_start->setFixedSize(133,47);//图片的固定大小
        btn_start->setStyleSheet("QPushButton{border-image: url(:/picture/System/systemMaintenance/start_dayMT-up.png);}"
                               "QPushButton:hover{border-image: url(:/picture/System/systemMaintenance/start_dayMT-up.png);}"
                               "QPushButton:pressed{border-image: url(:/picture/System/systemMaintenance/start_dayMT-down.png);}");


    //    btn_pause = new QPushButton(QString(tr("暂停日常维护")));         //暂停日常维护
    //    btn_pause->setFont(QFont("宋体",20));
    //    btn_pause->setFlat(true);
    //    QIcon icon2(":/picture/System/systemMaintenance/pause.png");
    //    btn_pause->setIcon(icon2);
    //    btn_pause->setIconSize(QSize(30,30));
    //    btn_pause->setFixedHeight(32);
        btn_pause = new QPushButton();
        btn_pause->setFlat(true);
        btn_pause->setFocusPolicy(Qt::TabFocus);
        btn_pause->setFixedSize(133,47);//图片的固定大小
        btn_pause->setStyleSheet("QPushButton{border-image: url(:/picture/System/systemMaintenance/pause_dayMT-up.png);}"
                               "QPushButton:hover{border-image: url(:/picture/System/systemMaintenance/pause_dayMT-up.png);}"
                               "QPushButton:pressed{border-image: url(:/picture/System/systemMaintenance/pause_dayMT-down.png);}");


    //    btn_continue = new QPushButton(QString(tr("继续日常维护")));         //继续日常维护
    //    btn_continue->setFont(QFont("宋体",20));
    //    btn_continue->setFlat(true);
    //    QIcon icon3(":/picture/System/systemMaintenance/continue.png");
    //    btn_continue->setIcon(icon3);
    //    btn_continue->setIconSize(QSize(26,26));
    //    btn_continue->setFixedHeight(32);
        btn_continue = new QPushButton();
        btn_continue->setFlat(true);
        btn_continue->setFocusPolicy(Qt::TabFocus);
        btn_continue->setFixedSize(133,47);//图片的固定大小
        btn_continue->setStyleSheet("QPushButton{border-image: url(:/picture/System/systemMaintenance/continue_dayMT-up.png);}"
                               "QPushButton:hover{border-image: url(:/picture/System/systemMaintenance/continue_dayMT-up.png);}"
                               "QPushButton:pressed{border-image: url(:/picture/System/systemMaintenance/continue_dayMT-down.png);}");







    label_SingleMaintain = new QLabel(QString(tr("仪器维护单项操作")));         //仪器维护单项操作
    label_SingleMaintain->setFont(QFont("宋体",20));
    label_SingleMaintain->setFixedSize(720,36);

    btn_Instrument = new QPushButton(QString(tr("仪器初始化及运行待机状态")));         //仪器初始化及运行待机状态
    btn_Instrument->setFont(QFont("宋体",20));
    btn_Instrument->setFixedSize(395,40);
    btn_Instrument->setFlat(true);
//    QIcon icon6("://System/systemMaintenance/week.png");
    btn_Instrument->setIcon(icon6);
    btn_Instrument->setIconSize(QSize(36,36));

    btn_PMT = new QPushButton(QString(tr("PMT背景检测")));         //PMT背景检测
    btn_PMT->setFont(QFont("宋体",20));
    btn_PMT->setFixedSize(220,40);
    btn_PMT->setIcon(icon5);
    btn_PMT->setFlat(true);
    btn_PMT->setIconSize(QSize(36,36));




    //    btn_InstrumentStart = new QPushButton(QString(tr("开始仪器初始化")));         //开始仪器初始化
    //    btn_InstrumentStart->setFont(QFont("宋体",20));
    //    btn_InstrumentStart->setFlat(true);
    //    //QIcon icon4("://System/systemMaintenance/continue.png");
    //    btn_InstrumentStart->setIcon(icon1);
    //    btn_InstrumentStart->setIconSize(QSize(26,26));
    //    btn_InstrumentStart->setFixedHeight(32);
        btn_InstrumentStart = new QPushButton();
        btn_InstrumentStart->setFlat(true);
        btn_InstrumentStart->setFocusPolicy(Qt::TabFocus);
        btn_InstrumentStart->setFixedSize(173,42);//图片的固定大小
        btn_InstrumentStart->setStyleSheet("QPushButton{border-image: url(:/picture/System/systemMaintenance/start_init-up.png);}"
                               "QPushButton:hover{border-image: url(:/picture/System/systemMaintenance/start_init-up.png);}"
                               "QPushButton:pressed{border-image: url(:/picture/System/systemMaintenance/start_init-down.png);}");



    //    btn_InstrumentStop = new QPushButton(QString(tr("结束仪器初始化")));         //结束仪器初始化
    //    btn_InstrumentStop->setFont(QFont("宋体",20));
    //    btn_InstrumentStop->setFlat(true);
    //    QIcon icon4(":/picture/System/systemMaintenance/stop.png");
    //    btn_InstrumentStop->setIcon(icon4);
    //    btn_InstrumentStop->setIconSize(QSize(26,26));
    //    btn_InstrumentStop->setFixedHeight(32);

        btn_InstrumentStop = new QPushButton();
        btn_InstrumentStop->setFlat(true);
        btn_InstrumentStop->setFocusPolicy(Qt::TabFocus);
        btn_InstrumentStop->setFixedSize(173,42);//图片的固定大小
        btn_InstrumentStop->setStyleSheet("QPushButton{border-image: url(:/picture/System/systemMaintenance/stop_init-up.png);}"
                               "QPushButton:hover{border-image: url(:/picture/System/systemMaintenance/stop_init-up.png);}"
                               "QPushButton:pressed{border-image: url(:/picture/System/systemMaintenance/stop_init-down.png);}");



    /*
     * layout_RoutineMaintain 初始化
     */
    layout_btn_AutomaticDay->addStretch(1);
    layout_btn_AutomaticDay->addWidget(btn_AutomaticDay);
    layout_btn_AutomaticDay->addStretch(5);

    layout_btn_AutomaticWeek->addStretch(1);
    layout_btn_AutomaticWeek->addWidget(btn_AutomaticWeek);
    layout_btn_AutomaticWeek->addStretch(5);

    layout_btn_routine->addStretch(4);
    layout_btn_routine->addWidget(btn_start);
    layout_btn_routine->addStretch(1);
    layout_btn_routine->addWidget(btn_pause);
    layout_btn_routine->addStretch(1);
    layout_btn_routine->addWidget(btn_continue);
    layout_btn_routine->addStretch(4);

    layout_RoutineMaintain->addStretch(2);
    layout_RoutineMaintain->addWidget(label_RoutineMaintain);
    layout_RoutineMaintain->addStretch(2);
    layout_RoutineMaintain->addLayout(layout_btn_AutomaticDay);
    layout_RoutineMaintain->addLayout(layout_btn_AutomaticWeek);
    layout_RoutineMaintain->addStretch(1);
    layout_RoutineMaintain->addWidget(tableView_RoutineMaintain);
    layout_RoutineMaintain->addStretch(1);
    layout_RoutineMaintain->addLayout(layout_btn_routine);
    layout_RoutineMaintain->addStretch(6);

    layout_RoutineMaintain->setAlignment(tableView_RoutineMaintain,Qt::AlignHCenter);
    layout_RoutineMaintain->setAlignment(label_RoutineMaintain,Qt::AlignHCenter);

    /*
     * layout_SingleMaintain 初始化
     */
    layout_btn_single->addStretch();
    layout_btn_single->addWidget(btn_InstrumentStart);
    layout_btn_single->addStretch();
    layout_btn_single->addWidget(btn_InstrumentStop);
    layout_btn_single->addStretch();

    layout_btn_Instrument->addStretch(20);
    layout_btn_Instrument->addWidget(btn_Instrument);
    layout_btn_Instrument->addStretch(62);

    layout_btn_PMT->addStretch(5);
    layout_btn_PMT->addWidget(btn_PMT);
    layout_btn_PMT->addStretch(24);

//    layout_btn_Instrument->addWidget(btn_Instrument);
//    layout_btn_PMT->addWidget(btn_PMT);
//    layout_btn_Instrument->setAlignment(btn_Instrument,Qt::AlignLeft);
//    layout_btn_PMT->setAlignment(btn_PMT,Qt::AlignLeft);

    layout_SingleMaintain->addStretch(2);
    layout_SingleMaintain->addWidget(label_SingleMaintain);
    layout_SingleMaintain->addStretch(2);
    layout_SingleMaintain->addLayout(layout_btn_Instrument);
    layout_SingleMaintain->addLayout(layout_btn_PMT);
    layout_SingleMaintain->addStretch(1);
    layout_SingleMaintain->addWidget(tableView_SingleMaintain);
    layout_SingleMaintain->addStretch(1);
    layout_SingleMaintain->addLayout(layout_btn_single);
    layout_SingleMaintain->addStretch(6);

    layout_SingleMaintain->setAlignment(label_SingleMaintain,Qt::AlignHCenter);
    layout_SingleMaintain->setAlignment(tableView_SingleMaintain,Qt::AlignHCenter);

    layout_la->addLayout(layout_RoutineMaintain);
    layout_la->addLayout(layout_SingleMaintain);

//    mainLayout->addWidget(widget);
}
