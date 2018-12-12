#include "mainwindow.h"
#include <QDebug>
#include "unknownWidget\unkownwidget.h"
#include <QFont>
#include "QMessgeBox/mymessgebox.h"
#include "Serial_port/serialport.h"
#include "standardBightWidget/qcustomplot.h"
#include "stndog.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
  //主窗口设置
    setFixedSize(1920,1080);
    setWindowFlags(Qt::FramelessWindowHint);


  //菜单栏停靠窗口设置
    menuDockWidget = new QDockWidget(this);
    menuDockWidget->setAutoFillBackground(true);
    menuDockWidget->setWindowFlags(Qt::FramelessWindowHint);
    menuDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);            //不可移动

    menuWidget = new QWidget();

    menuWidget->setAutoFillBackground(true);
    menuWidget->setWindowFlags(Qt::FramelessWindowHint);


    QPalette menuWidget_palette;
    QPixmap menuWidget_pixmap(":/picture/mainwindow/toolwidgetBackground.png");
    menuWidget->setFixedSize(234,1080);
    menuWidget_palette.setBrush(QPalette::Window,QBrush(menuWidget_pixmap));
    menuWidget->setPalette(menuWidget_palette);
    menuDockWidget->setWidget(menuWidget);

////去掉停靠窗口自定义标题栏
    QWidget *tempWidget = new QWidget;
    menuDockWidget->setTitleBarWidget(tempWidget);

//添加一个停靠窗口
    addDockWidget(Qt::LeftDockWidgetArea,menuDockWidget);
    disTemperatureWidgetInit(); //温度显示和温度曲线显示

//中心窗口
    unknow_Widget = new UnkownWidget(this);
    calibration_Widget = NULL;
    selfTest_Widget = NULL;
    query_Widget = NULL;
    standardBight_Widget = NULL;
    standardPragrame_Widget = NULL;
    standardTest_Widget = NULL;
    system_Widget = NULL;
    manul_Widget = NULL;


    setCentralWidget(unknow_Widget);



/**
 *  状态栏设置
 */
    statu1Label = new QLabel;
    statu1Label->setFixedSize(60,40);
    statu1Label->setText(tr("PLC:"));
    statu1Label->setFrameShape(QFrame::WinPanel); //设置标签形
    statu1Label->setFrameShadow(QFrame::Sunken); //设置标签阴影

    statu2Label = new QLabel;
    statu2Label->setFixedSize(60,40);
    statu2Label->setPixmap(QPixmap(30,30));
    statu2Label->setFrameShape(QFrame::WinPanel); //设置标签形
    statu2Label->setFrameShadow(QFrame::Sunken); //设置标签阴影
    setTimer();
    showTimeLabel->setFont(QFont("timeFont",30));
//    statusLayout = new QHBoxLayout;

    statusBar()->setAutoFillBackground(true);
    statusBar()->setFixedSize(1920,40);
    statusBar()->setPalette(QPalette(QColor(160, 160, 164)));
 //showMessage：定时显示。
 // addPermanentWidget：添加现实永久信息。//最右侧
    statusBar()->addPermanentWidget(statu1Label);
    statusBar()->addPermanentWidget(statu2Label);
    statusBar()->addPermanentWidget(showTimeLabel);


//菜单窗口
    createMenus();

//信号槽绑定函数
    connectInit();

    qDebug() << "当前主线程ID = " << QThread::currentThreadId();
}

MainWindow::~MainWindow()
{
 qDebug() <<"sssssdwsdss";

}
/**
 * @brief 更新当前温度值
 * @param 下位机上传的温度值
 */
void MainWindow::UpdateTemperatureValue(unsigned short temp)
{
    double temperature = 0;
    if( temp & 0x8000){
        temperature = (~temp + 1) *0.1;
        temperatureNum->setText(tr("-") + QString::number(temperature,3,1) + tr("℃"));
    }else{
        temperature = temp *0.1;
        temperatureNum->setText(QString::number(temperature,3,1) + tr("℃"));
        disTemperatureWidget->insertData(temperature);
    }
}

/**
 * @brief 创建菜单栏
 */
void MainWindow::createMenus()
{
    QPalette   pal;//按键字体颜色设置
    pal.setColor(QPalette::ButtonText, QColor(255, 255, 255, 255));

    UnknownBtn = new QPushButton; //未知品测试
    UnknownBtn->setFont(QFont("menu",15));
    UnknownBtn->setPalette(pal);
    UnknownBtn->setText(tr(" 未知品测试"));
    UnknownBtn->setFixedSize(234,40);
    UnknownBtn->setIconSize(QSize(17,17));
    UnknownBtn->setIcon(QIcon(":/picture/mainwindow/unknownBtn.png"));
    UnknownBtn->setStatusTip(QString(tr("进行样本测试"))); //按键功能显示
    UnknownBtn->setFlat(true);
    UnknownBtn->setStyleSheet("text-align: left;");//设置按钮文字显示位置-左对齐;
    connect(UnknownBtn,SIGNAL(clicked()),this,SLOT(create_UnknownWindow()));

    CalibrationBtn = new QPushButton; //校准/质控品
    CalibrationBtn->setFont(QFont("menu",15));
    CalibrationBtn->setText(tr(" 校/质品测试"));
    CalibrationBtn->setPalette(pal);
    CalibrationBtn->setFixedSize(234,40);
    CalibrationBtn->setIconSize(QSize(17,17));
    CalibrationBtn->setIcon(QIcon(":/picture/menu/xiaozhunzhikong_icon.png"));
    CalibrationBtn->setStatusTip(QString(tr("进行校准品或者质控品测试"))); //按键功能显示
    CalibrationBtn->setStyleSheet("text-align: left;");//设置按钮文字显示位置-左对齐;
    CalibrationBtn->setFlat(true);
    connect(CalibrationBtn,SIGNAL(clicked()),this,SLOT(create_CalibrationWindow()));

    SelfTestBtn = new QPushButton; //自检
    SelfTestBtn->setFont(QFont("menu",15));
    SelfTestBtn->setPalette(pal);
    SelfTestBtn->setText(tr(" 自 检"));
    SelfTestBtn->setFixedSize(234,40);
    SelfTestBtn->setIconSize(QSize(17,17));
    SelfTestBtn->setIcon(QIcon(":/picture/menu/zijian_icon.png"));
    SelfTestBtn->setStatusTip(QString(tr("进行自检"))); //按键功能显示
    SelfTestBtn->setStyleSheet("text-align: left;");//设置按钮文字显示位置-左对齐;
    SelfTestBtn->setFlat(true);
    connect(SelfTestBtn,SIGNAL(clicked()),this,SLOT(create_SelfTestWindow()));

    QueryBtn = new QPushButton;    //查询
    QueryBtn->setFont(QFont("menu",15));
    QueryBtn->setText(tr(" 查 询"));
    QueryBtn->setPalette(pal);
    QueryBtn->setFixedSize(234,40);
    QueryBtn->setIconSize(QSize(17,17));
    QueryBtn->setIcon(QIcon(":/picture/menu/chaxun.png"));
    QueryBtn->setStatusTip(QString(tr("进入查询"))); //按键功能显示
    QueryBtn->setStyleSheet("text-align: left;");//设置按钮文字显示位置-左对齐;
    QueryBtn->setFlat(true);
    connect(QueryBtn,SIGNAL(clicked()),this,SLOT(create_QueryWindow()));

    SystemBtn = new QPushButton;  //系统
    SystemBtn->setFont(QFont("menu",15));
    SystemBtn->setPalette(pal);
    SystemBtn->setText(tr(" 系 统"));
    SystemBtn->setFixedSize(234,40);
    SystemBtn->setIconSize(QSize(17,17));
    SystemBtn->setIcon(QIcon(":/picture/menu/xitong_icon.png"));
    SystemBtn->setStatusTip(QString(tr("进入系统设置"))); //按键功能显示
    SystemBtn->setStyleSheet("text-align: left;");//设置按钮文字显示位置-左对齐;
    SystemBtn->setFlat(true);
    connect(SystemBtn,SIGNAL(clicked()),this,SLOT(create_SystemWindow()));

    StandardPragrameBtn = new QPushButton; //标准品试剂船编辑
    StandardPragrameBtn->setFont(QFont("menu",15));
    StandardPragrameBtn->setPalette(pal);
    StandardPragrameBtn->setText(tr(" 标准品试剂船编辑"));
    StandardPragrameBtn->setFixedSize(234,40);
    StandardPragrameBtn->setIconSize(QSize(17,17));
    StandardPragrameBtn->setIcon(QIcon(":/picture/menu/biaozhunbianji_icon.png"));
    StandardPragrameBtn->setStatusTip(QString(tr("进入标准品试剂船编辑界面"))); //按键功能显示
    StandardPragrameBtn->setStyleSheet("text-align: left;");//设置按钮文字显示位置-左对齐;
    StandardPragrameBtn->setFlat(true);
    connect(StandardPragrameBtn,SIGNAL(clicked()),this,SLOT(create_StandardPragrameWindow()));

    StandardTestBtn = new QPushButton;     //标准品测试
    StandardTestBtn->setFont(QFont("menu",15));
    StandardTestBtn->setPalette(pal);
    StandardTestBtn->setText(tr(" 标准品测试"));
    StandardTestBtn->setFixedSize(234,40);
    StandardTestBtn->setIconSize(QSize(17,17));
    StandardTestBtn->setIcon(QIcon(":/picture/menu/biaozhun_icon.png"));
    StandardTestBtn->setStatusTip(QString(tr("进入标准品测试界面"))); //按键功能显示
    StandardTestBtn->setStyleSheet("text-align: left;");//设置按钮文字显示位置-左对齐;
    StandardTestBtn->setFlat(true);
    connect(StandardTestBtn,SIGNAL(clicked()),this,SLOT(create_StandardTestWindow()));

    StandardBightBtn = new QPushButton;   //标准曲线生成
    StandardBightBtn->setFont(QFont("menu",15));
    StandardBightBtn->setPalette(pal);
    StandardBightBtn->setText(tr(" 标准曲线生成"));
    StandardBightBtn->setFixedSize(234,40);
    StandardBightBtn->setIconSize(QSize(17,17));
    StandardBightBtn->setIcon(QIcon(":/picture/menu/biaozhunquxian_icon.png"));
    StandardBightBtn->setStatusTip(QString(tr("进行标准品曲线生成"))); //按键功能显示
    StandardBightBtn->setStyleSheet("text-align: left;");//设置按钮文字显示位置-左对齐;
    StandardBightBtn->setFlat(true);
    connect(StandardBightBtn,SIGNAL(clicked()),this,SLOT(create_StandardBightWindow()));

    CancelBtn =new QPushButton;
    CancelBtn->setFont(QFont("menu",15));
    CancelBtn->setPalette(pal);
    CancelBtn->setText(QString(tr(" 退出软件")));
    CancelBtn->setFixedSize(234,40);
    CancelBtn->setIconSize(QSize(17,17));
    CancelBtn->setIcon(QIcon(":/picture/mainwindow/unknownBtn.png"));
    CancelBtn->setStatusTip(QString(tr("强制退出软件"))); //按键功能显示
    CancelBtn->setStyleSheet("text-align: left;");//设置按钮文字显示位置-左对齐;
    CancelBtn->setFlat(true);
    connect(CancelBtn,SIGNAL(clicked()),this,SLOT(CancelBtnSlot()));

    toolbarLab1 = new QLabel;
    toolbarLab1->setPixmap(QPixmap(":/picture/menu/tool_bar.png"));
    toolbarLab2 = new QLabel;
    toolbarLab2->setPixmap(QPixmap(":/picture/menu/tool_bar.png"));
    toolbarLab3 = new QLabel;
    toolbarLab3->setPixmap(QPixmap(":/picture/menu/tool_bar.png"));
    toolbarLab4 = new QLabel;
    toolbarLab4->setPixmap(QPixmap(":/picture/menu/tool_bar.png"));
    toolbarLab5 = new QLabel;
    toolbarLab5->setPixmap(QPixmap(":/picture/menu/tool_bar.png"));
    toolbarLab6 = new QLabel;
    toolbarLab6->setPixmap(QPixmap(":/picture/menu/tool_bar.png"));
    toolbarLab7 = new QLabel;
    toolbarLab7->setPixmap(QPixmap(":/picture/menu/tool_bar.png"));
    toolbarLab8 = new QLabel;
    toolbarLab8->setPixmap(QPixmap(":/picture/menu/tool_bar.png"));
    toolbarLab9 = new QLabel;
    toolbarLab9->setPixmap(QPixmap(":/picture/menu/tool_bar.png"));
 //布局管理器
    menuLayout  = new QVBoxLayout;
    menuLayout->setMargin(0); //设置边距
    menuLayout->addStretch(60);
    menuLayout->addWidget(UnknownBtn);
    menuLayout->addWidget(toolbarLab1);
    menuLayout->addWidget(CalibrationBtn);
    menuLayout->addWidget(toolbarLab2);
    menuLayout->addWidget(SelfTestBtn);
    menuLayout->addWidget(toolbarLab3);
    menuLayout->addWidget(QueryBtn);
    menuLayout->addWidget(toolbarLab4);
    menuLayout->addWidget(SystemBtn);
    menuLayout->addWidget(toolbarLab5);

    StnDog *stnDog = new StnDog();
    stnDog->status=HASP_STATUS_OK;//20181213 不使用加密狗
    if(stnDog->status == 0)
    {
        menuLayout->addWidget(StandardPragrameBtn);
        menuLayout->addWidget(toolbarLab6);
        menuLayout->addWidget(StandardTestBtn);
        menuLayout->addWidget(toolbarLab7);
        menuLayout->addWidget(StandardBightBtn);
        menuLayout->addWidget(toolbarLab8);
    }
    menuLayout->addWidget(CancelBtn);
    menuLayout->addWidget(toolbarLab9);

    if(stnDog->status != 0){
        menuLayout->addStretch(100);
    }

    menuLayout->addSpacing(55);//165
    menuLayout->addWidget(disTemperatureWidget);
    menuLayout->addStretch(15);




    menuWidget->setLayout(menuLayout);
}

/**
 * @brief 设置当前系统时间
 */
void MainWindow::setTimer()
{
    showTimeLabel = new QLabel(this);     //显示当前时间
    timer = new QTimer(this);           //时间计时器
    timer->start(500);
    connect(timer,SIGNAL(timeout()),this,SLOT(showTime()));
    showTime();
    showDot = true;
}

/**
 * @brief 信号槽绑定函数初始化
 */
void MainWindow::connectInit()
{
    connect(unknow_Widget->questionBtn,SIGNAL(clicked()),this,SLOT(questionBtnSlot()));
    connect(&serialPort::ReceiveThread,SIGNAL(other_cmdSign(QString)),this,SLOT(other_cmdSignSlot(QString)),(Qt::ConnectionType)(Qt::UniqueConnection|Qt::QueuedConnection));
}

/**
 * @brief 显示温度和温度曲线界面
 */
void MainWindow::disTemperatureWidgetInit()
{

    disTemperatureWidget = new TemperaturePlot(this);


    //disTemperatureWidget = new QWidget; //显示温度和温度曲线界面
      disTemperatureWidget->setAutoFillBackground(true);
      disTemperatureWidget->setFixedSize(230,380);
    //disTemperatureWidget->setStyleSheet("background-color:rgb(91,160,175);");
    //disTemperatureWidget->setAttribute(Qt::WA_TranslucentBackground);//透明

    QPalette disTempet_palette;
    QPixmap disTempet_pixmap(":/picture/mainwindow/temperatureBackGround.png");
    disTempet_palette.setBrush(QPalette::Window,QBrush(disTempet_pixmap));
    disTemperatureWidget->setPalette(disTempet_palette);

//    temperatureIcon = new QLabel(disTemperatureWidget); //温度图标
//    temperatureIcon->setPixmap(QPixmap(":/picture/mainwindow/temperatureIcon.png"));



    temperatureNum = new QLabel(disTemperatureWidget); //显示当前温度数值
    QPalette   pal;//按键字体颜色设置
    pal.setColor(QPalette::WindowText, QColor(255, 255, 255, 255));

    temperatureName = new  QLabel(disTemperatureWidget); //温度名称
    temperatureName->setPalette(pal);
    temperatureName->setText(tr("当前温度:"));
    temperatureName->setFont(QFont("tempetFont",20,QFont::Bold));

    temperatureNum = new  QLabel(disTemperatureWidget); //显示当前温度数值
    temperatureNum->setPalette(pal);
    temperatureNum->setFont(QFont("tempetFont",20,QFont::Bold));
    temperatureNum->setText(tr("00.0℃"));

    CycleIcon = new QLabel(disTemperatureWidget);//温度循环图标
    CycleIcon->setPixmap(QPixmap(":/picture/mainwindow/temperatureCycleIcon.png"));


    SystemStateLabel = new QLabel(disTemperatureWidget); //系统状态
    SystemStateLabel->setPalette(pal);
    SystemStateLabel->setFont(QFont("systemStateFont",20,QFont::Bold));
    SystemStateLabel->setText(tr("系统已运行!"));


    //temperatureIcon->setGeometry(10,10,36,31);
    temperatureName->setGeometry(10,10,130,25);
    temperatureNum->setGeometry(140,10,100,25);
    CycleIcon->setGeometry(10,285,67,48);//200
    SystemStateLabel->setGeometry(77,295,153,25);//210

}



/**
 * @brief 创建未知品窗口
 */
void MainWindow::create_UnknownWindow()
{
    myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_QUESTION,tr("提示"),tr("是否退出当前界面！"),this);
    if(messge->exec() == QDialog::Accepted){   //模式对话框
        unknow_Widget = new UnkownWidget(this);
        unknow_Widget->setWindowFlags(Qt::FramelessWindowHint);
        setCentralWidget(unknow_Widget);
        connect(unknow_Widget->questionBtn,SIGNAL(clicked()),this,SLOT(questionBtnSlot()));
        serialPort::mySend_Data("01,00,ff,ff,00,00");
        qDebug() << "*************发送一次";

    }

//    CalibrationBtn->setEnabled(false); //校准/质控品
//    SelfTestBtn->setEnabled(false); //自检
//    QueryBtn->setEnabled(false);
//    SystemBtn->setEnabled(false);  //系统
//    StandardPragrameBtn->setEnabled(false); //标准品试剂船编辑
//    StandardTestBtn->setEnabled(false);     //标准品测试
//    StandardBightBtn->setEnabled(false);   //标准曲线生成;
}

/**
 * @brief 创建校准/质控品窗口
 */
void MainWindow::create_CalibrationWindow()
{
    myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_QUESTION,tr("提示"),tr("是否退出当前界面！"),this);
    if(messge->exec() == QDialog::Accepted){   //模式对话框
        calibration_Widget = new calibrationWidget(this);
        calibration_Widget->setWindowFlags(Qt::FramelessWindowHint);
        setCentralWidget(calibration_Widget);
        connect(calibration_Widget->oneWidget->questionBtn,SIGNAL(clicked()),this,SLOT(questionBtnSlot()));
        connect(calibration_Widget->caliOneWidget->questionBtn,SIGNAL(clicked()),this,SLOT(questionBtnSlot()));
        connect(calibration_Widget->twoWidget->questionBtn,SIGNAL(clicked()),this,SLOT(questionBtnSlot()));
        connect(calibration_Widget->qualityOneWidget->questionBtn,SIGNAL(clicked()),this,SLOT(questionBtnSlot()));


        //返回按钮
        connect(calibration_Widget->oneWidget->returnBtn,SIGNAL(clicked()),this,SLOT(returnBtnSlot()));
        connect(calibration_Widget->twoWidget->returnBtn,SIGNAL(clicked()),this,SLOT(returnBtnSlot()));

        myCheckmessageBox *message = new myCheckmessageBox(myCheckmessageBox::MY_CALIBRATION,tr("选择!"),tr("请选择校准还是质控!"),this);
        if(message->exec() == QDialog::Accepted){
            calibration_Widget->stack->setCurrentIndex(0);

            serialPort::mySend_Data("04,00,ff,ff,00,00");
            qDebug() << "发送进入校准品阶段命令一次";

            myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_INFORMATION,tr("提示"),tr("请插入校准品！"),this);
            if(messge->exec() == QDialog::Accepted){   //模式对话框

            }
        }else{
            calibration_Widget->stack->setCurrentIndex(1);

            serialPort::mySend_Data("05,00,ff,ff,00,00");
            qDebug() << "发送进入质控品阶段命令一次";
            myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_INFORMATION,tr("提示"),tr("请插入质控品！"),this);
            if(messge->exec() == QDialog::Accepted){   //模式对话框

            }
         }
    }
}
/**
 * @brief 创建自检窗口
 */
void MainWindow::create_SelfTestWindow()
{
    myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_QUESTION,tr("提示"),tr("是否退出当前界面！"),this);
    if(messge->exec() == QDialog::Accepted){   //模式对话框
        selfTest_Widget = new selfTestWidget(this);
        selfTest_Widget->setWindowFlags(Qt::FramelessWindowHint);
        setCentralWidget(selfTest_Widget);
        connect(selfTest_Widget->questionBtn,SIGNAL(clicked()),this,SLOT(questionBtnSlot())); //绑定问号按钮信号槽
    }
}
/**
 * @brief 创建查询窗口
 */
void MainWindow::create_QueryWindow()
{
    myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_QUESTION,tr("提示"),tr("是否退出当前界面！"),this);
    if(messge->exec() == QDialog::Accepted){   //模式对话框
        query_Widget = new queryWidget(this);
        query_Widget->setWindowFlags(Qt::FramelessWindowHint);
        setCentralWidget(query_Widget);
        connect(query_Widget->questionBtn,SIGNAL(clicked()),this,SLOT(questionBtnSlot())); //绑定问号按钮信号槽
    }

}

/**
 * @brief 创建系统窗口
 */
void MainWindow::create_SystemWindow()
{
    myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_QUESTION,tr("提示"),tr("是否退出当前界面！"),this);
    if(messge->exec() == QDialog::Accepted){   //模式对话框
        system_Widget = new systemWidget(this);
        system_Widget->setWindowFlags(Qt::FramelessWindowHint);
        setCentralWidget(system_Widget);
        connect(system_Widget->questionBtn,SIGNAL(clicked()),this,SLOT(questionBtnSlot())); //绑定问号按钮信号槽
    }
}

/**
 * @brief 创建标准品编辑窗口
 */
void MainWindow::create_StandardPragrameWindow()
{
    myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_QUESTION,tr("提示"),tr("是否退出当前界面！"),this);
    if(messge->exec() == QDialog::Accepted){   //模式对话框
        standardPragrame_Widget = new standardPragrameWidget(this);
        standardPragrame_Widget->setWindowFlags(Qt::FramelessWindowHint);
        setCentralWidget(standardPragrame_Widget);
        connect(standardPragrame_Widget->questionBtn,SIGNAL(clicked()),this,SLOT(questionBtnSlot()));
        serialPort::mySend_Data("02,00,ff,ff,00,00");
        qDebug() << "发送进入试剂船编辑阶段命令一次";
    }
}

/**
 * @brief 创建标准品测试窗口
 */
void MainWindow::create_StandardTestWindow()
{
    myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_QUESTION,tr("提示"),tr("是否退出当前界面！"),this);
    if(messge->exec() == QDialog::Accepted){   //模式对话框
        standardTest_Widget = new standardTestWidget(this);
        standardTest_Widget->setWindowFlags(Qt::FramelessWindowHint);
        setCentralWidget(standardTest_Widget);
        connect(standardTest_Widget->oneWidget->questionBtn,SIGNAL(clicked()),this,SLOT(questionBtnSlot()));
        connect(standardTest_Widget->twoWidget->questionBtn,SIGNAL(clicked()),this,SLOT(questionBtnSlot()));

        connect(standardTest_Widget->oneWidget->returnBtn,SIGNAL(clicked()),this,SLOT(returnBtnSlot()));
        serialPort::mySend_Data("03,00,ff,ff,00,00");
        qDebug() << "发送进入标准品测试阶段命令一次";
        myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_INFORMATION,tr("提示"),tr("请插入标准品试剂船！"),this);
        if(messge->exec() == QDialog::Accepted){   //模式对话框

        }

    }
}

/**
 * @brief 创建标准品曲线窗口
 */
void MainWindow::create_StandardBightWindow()
{
    myMessgeBox *messge;
    if(standardBightWidget::CurveDisplayFlag){
        messge = new myMessgeBox(myMessgeBox::MY_MESSAGE_QUESTION,tr("提示"),tr("当前参数没有保存，是否退出界面"),this);
        if(messge->exec() == QDialog::Accepted){   //模式对话框
            standardBight_Widget = new standardBightWidget(this);
            standardBight_Widget->setWindowFlags(Qt::FramelessWindowHint);
            setCentralWidget(standardBight_Widget);
            connect(standardBight_Widget->questionBtn,SIGNAL(clicked()),this,SLOT(questionBtnSlot()));
            connect(standardBight_Widget,SIGNAL(quitOkSign()),this,SLOT(returnBtnSlot()));
            standardBightWidget::CurveDisplayFlag = false;
        }
    }else{
        standardBight_Widget = new standardBightWidget(this);
        standardBight_Widget->setWindowFlags(Qt::FramelessWindowHint);
        setCentralWidget(standardBight_Widget);
        connect(standardBight_Widget->questionBtn,SIGNAL(clicked()),this,SLOT(questionBtnSlot()));
        connect(standardBight_Widget,SIGNAL(quitOkSign()),this,SLOT(returnBtnSlot()));
    }

//    UnknownBtn->setEnabled(false);
//    CalibrationBtn->setEnabled(false); //校准/质控品
//    SelfTestBtn->setEnabled(false); //自检
//    QueryBtn->setEnabled(false);
//    SystemBtn->setEnabled(false);  //系统
//    StandardPragrameBtn->setEnabled(false); //标准品试剂船编辑
    //    StandardTestBtn->setEnabled(false);     //标准品测试
}

/**
 * @brief 退出软件信号槽
 */
void MainWindow::CancelBtnSlot()
{
    myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_QUESTION,tr("提示"),tr("是否退出软件！"),this);
    if(messge->exec() == QDialog::Accepted){   //模式对话框
        this->close();
    }
}

/**
 * @brief 其它命令处理函数
 * @param str
 */
void MainWindow::other_cmdSignSlot(const QString &str)
{
    QByteArray Receive_array = 0;
    QString returnCMD = "";
    qDebug()<<"处理信号槽线程ID = " <<QThread::currentThreadId();
    qDebug() << "其它命令收到一条命令" << str;
    Receive_array = serialPort::HEXStringToArr(str);
    uint16_t dataLength = (uint16_t)(((Receive_array.at(4)&0xffff)<< 8)|(Receive_array.at(5)&0xff));//数据长度
    unsigned char cmd = (Receive_array.at(1) & 0xff); //命令

    if( ( Receive_array.at(0) & 0xff) & 0x40 ){   //MCU返回码命令解析
        return;
    }
    /***MCU主动发送的命令解析************************************************/
    switch(cmd){
    case OTHER_TRMPERATURE_CMD:
        qDebug()<< "其它收到MCU有温度返回命令";
        if( dataLength != 3){
            //插入错误数据表
            qDebug() << "其它温度命令数据长度不对";
             emit serialPort::ReceiveThread.ErrDataSign("数据长度不对");
            return;
        }
        unsigned char state = Receive_array.at(6)&0xff;//位置
        if( state ){
            emit serialPort::ReceiveThread.ErrDataSign("温度模块出现故障");
            return;
        }else{
            unsigned short int temp = ( Receive_array.at(7)&0xff )<< 8 | Receive_array.at(8)&0xff;
            UpdateTemperatureValue(temp);
        }
        break;
    }
}

/**
 * @brief MainWindow::显示当前系统时间
 */
void MainWindow::showTime()
{
    QTime time = QTime::currentTime();
    QString timeString = time.toString("hh:mm");
    if(showDot){
        timeString[2] = ':';
        showDot = false;
    }
    else
    {
        timeString[2]=' ';
        showDot = true;
    }
    showTimeLabel->setText(timeString);
}

/**
 * @brief MainWindow::问号按钮信号槽
 */
void MainWindow::questionBtnSlot()
{
    qDebug() << "questionBtn press";
    manul_Widget = new manul_bookWidget(this);
    if(manul_Widget->exec() == QDialog::Accepted){

    }
}

/**
 * @brief 各个界面返回主界面
 */
void MainWindow::returnBtnSlot()
{
    create_UnknownWindow();
}
