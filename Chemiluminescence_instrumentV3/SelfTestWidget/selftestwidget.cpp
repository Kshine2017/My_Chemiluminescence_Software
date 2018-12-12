#include "selftestwidget.h"
#include <QStringList>
#include <QSpinBox>
#include <QHeaderView>
#include "serical_thread/serial_thread.h"
#include "Serial_port/serialport.h"
#include "QMessageBox"
selfTestWidget::selfTestWidget(QWidget *parent)
    : QWidget(parent)
{
    init();
    connectInit();
    sendCMDToPC(); //进入自检模式
}

//布局初始化
void selfTestWidget::init()
{
    setWindowState(Qt::WindowMaximized);//全屏
    //setWindowState(Qt::WindowFullScreen);

    mainLayout = new QVBoxLayout;

    widget = new QWidget(this);
    widget->setGeometry(0,0,1687,1080);

    label_title = new QLabel(widget); //放背景
    label_title->setPixmap(QPixmap(":/picture/selfTest/title.png"));
    label_title->setGeometry(0,0,1687,69);

    label_titleName = new QLabel(label_title); //放文字
    label_titleName->setText(QString(tr("自检结果")));

//------------- 圆形进度条 ----------------------------------
    RoundPB = new QRoundProgressBar(this);
    RoundPB->setGeometry(855,360,100,100); //坐标，尺寸
    RoundPB->setBarStyle(QRoundProgressBar::StyleDonut); //风格设置
    RoundPB->setRange(0,100);

    QPalette palette1;
    // palette1.setBrush(QPalette::Window,Qt::NoBrush);
    palette1.setBrush(QPalette::Base,Qt::NoBrush);

    //palette1.setBrush(QPalette::AlternateBase,Qt::NoBrush);//中心字体的背景色
    palette1.setBrush(QPalette::AlternateBase,Qt::gray);

    palette1.setBrush(QPalette::Highlight,QBrush(QColor(0,255,0)));//进度条颜色

    palette1.setColor(QPalette::Text,QColor(0,0,0));

    RoundPB->setPalette(palette1);

//------------------------------------------------------
    QPalette pal;//按键字体颜色设置
    pal.setColor(QPalette::WindowText, QColor(255, 255, 255, 255));
    label_titleName->setPalette(pal);
    label_titleName->setFont(QFont("windowTitle",16));
    label_titleName->setGeometry(84,13,100,40);

    questionBtn = new QPushButton(label_title); //问号按钮
    questionBtn->setIconSize(QSize(46,45));
    questionBtn->setIcon(QIcon(":/picture/standardPrograme/？btn.png"));
    questionBtn->setFlat(true);
    questionBtn->setGeometry(1600,1,45,45);

    lab_textEdit_bg = new QLabel(widget);
    lab_textEdit_bg->setGeometry(0,72,1685,280);
    lab_textEdit_bg->setPixmap(QPixmap(":/picture/selfTest/bg_textedit2.png"));

    textEdit_content = new QTextEdit(lab_textEdit_bg); //显示自检进度
    textEdit_content->setFont(QFont("宋体",13));//设置字体大小。
    textEdit_content->setStyleSheet("color: white;background-color: transparent;"); //设置透明背景
    textEdit_content->setFixedSize(1685,280);

//    textEdit_content->setStyleSheet("background-image:url(:/picture/selfTest/bg_textedit.png)");
    textEdit_content->setDisabled(false);


    /*
     *按钮区域
     */
    btn_start = new QPushButton(widget);     //启动按钮
    btn_pause = new QPushButton(widget);     //暂停、继续按钮
    btn_stop = new QPushButton(widget);      //停止按钮
    btn_reset = new QPushButton(widget);     //报警复位按钮

    btn_start->setStyleSheet("QPushButton{border-image: url(:/picture/selfTest/start-up.png);}"
                               "QPushButton:hover{border-image: url(:/picture/selfTest/start-up.png);}"
                               "QPushButton:pressed{border-image: url(:/picture/selfTest/start-down.png);}");

    btn_pause->setStyleSheet("QPushButton{border-image: url(:/picture/selfTest/pause-up.png);}"
                               "QPushButton:hover{border-image: url(:/picture/selfTest/pause-up.png);}"
                               "QPushButton:pressed{border-image: url(:/picture/selfTest/pause-down.png);}");

    btn_stop->setStyleSheet("QPushButton{border-image: url(:/picture/selfTest/stop-up.png);}"
                               "QPushButton:hover{border-image: url(:/picture/selfTest/stop-up.png);}"
                               "QPushButton:pressed{border-image: url(:/picture/selfTest/stop-down.png);}");

    btn_reset->setStyleSheet("QPushButton{border-image: url(:/picture/selfTest/reset-up.png);}"
                               "QPushButton:hover{border-image: url(:/picture/selfTest/reset-up.png);}"
                               "QPushButton:pressed{border-image: url(:/picture/selfTest/reset-down.png);}");

    btn_start->setFlat(true);               //按钮去边框
    btn_pause->setFlat(true);
    btn_stop->setFlat(true);
    btn_reset->setFlat(true);

    btn_start->setFont(QFont("宋体",18));     //设置按钮字体大小
    btn_pause->setFont(QFont("宋体",18));
    btn_stop->setFont(QFont("宋体",18));
    btn_reset->setFont(QFont("宋体",18));

    btn_start->setGeometry(40,380,100,40);
    btn_pause->setGeometry(240,380,100,40);
    btn_stop->setGeometry(440,380,100,40);
    btn_reset->setGeometry(640,380,100,40);

    /*
     *操作步骤区域
     */
    widget_content = new QWidget(widget); //放置步骤的边框背景
//    widget_content->setFixedSize(1687,606);
    widget_content->setGeometry(0,430,1670,605);
    widget_content->setAutoFillBackground(true);

    QPalette palette;
    QPixmap pixmap(":/picture/selfTest/content.png");
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    widget_content->setPalette(palette);    //放置背景图片

    label_contentName = new QLabel(widget_content);  //放置文字标签--具体步骤
    label_contentName->setText(QString(tr("具体步骤")));
    QPalette pal2;//标签字体颜色设置
    pal2.setColor(QPalette::WindowText, QColor(255, 255, 255, 255));
    label_contentName->setPalette(pal2);
    label_contentName->setFont(QFont("windowTitle",16));
    label_contentName->setGeometry(84,13,100,40);



    //表格窗口
    tableWidget = new QTableWidget(widget_content);
    tableWidget->setColumnCount(6);
    tableWidget->setRowCount(8);
    tableWidget->setFont(QFont("windowTitle",20)); //设置表格内容字体

    MyHeaderView *myHeader = new MyHeaderView(0, Qt::Horizontal,tableWidget);

    tableWidget->setHorizontalHeader(myHeader);     //设置自定义表头，在表头放一个复选框
    connect(myHeader,SIGNAL(checkStausChange(bool)),this,SLOT(setAllCheckStatus(bool)));//复选框点击事件
    tableWidget->setGeometry(0,30,1660,559);
    //表头
    QStringList header;
    header<<""<<"检验项目"<<"次数"<<"拓展项"<<"单项执行"<<"结果";
    tableWidget->setHorizontalHeaderLabels(header);
    //设置水平表头的高度。
    tableWidget->horizontalHeader()->setFixedHeight(62);
    //设置垂直表头的高度。
    tableWidget->verticalHeader()->setFixedWidth(62);
    //设置水平表头内文字的字体、颜色和大小。
    tableWidget->horizontalHeader()->setStyleSheet
            ("QHeaderView::section{font:20pt 'windowTitle';color: black;};");
    //设置每一列的宽度
    tableWidget->setColumnWidth(0, 60); //勾选 checkbox
    tableWidget->setColumnWidth(1, 450);//检验项目
    tableWidget->setColumnWidth(2, 250);//次数
    tableWidget->setColumnWidth(3, 320);//拓展项
    tableWidget->setColumnWidth(4, 280);//单项执行
    tableWidget->setColumnWidth(5, 230);//结果

    //设置每一行的高度
    tableWidget->setRowHeight(0,60);
    tableWidget->setRowHeight(1,60);
    tableWidget->setRowHeight(2,60);
    tableWidget->setRowHeight(3,60);
    tableWidget->setRowHeight(4,60);
    tableWidget->setRowHeight(5,60);
    tableWidget->setRowHeight(6,60);
    tableWidget->setRowHeight(7,60);
    tableWidget->setRowHeight(8,60);

    tableWidget->setGeometry(7,62,1655,590);//设置表格的大小和位置
    tableWidget->setMaximumSize(1655,590);

    //设置水平表头不可操作
    //tableWidget->horizontalHeader()->setDisabled(true);
    //设置垂直表头不可操作
    //tableWidget->verticalHeader()->setDisabled(true);

    //设置水平表头不可拖动
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    //设置垂直表头不可拖动
    tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    //实例化每一个步骤（每一行）
    step1 = new SelfTestStep(1,QString(tr("x轴移动")));
    step2 = new SelfTestStep(2,QString(tr("y轴移动")));
    step3 = new SelfTestStep(3,QString(tr("z轴移动")));
    step4 = new SelfTestStep(4,QString(tr("底噪测量")));

    //把每个步骤的内容添加到表格中
    SetStep(step1);
    SetStep(step2);
    SetStep(step3);
    SetStep(step4);


    WorkQueue = new Queue;  //申请一个工作队列
    InquiryTimer = new QTimer(this); //定时器
    InquiryTimer->setInterval(INQUIRY_TIME);
    InquiryTimer->setSingleShot(false); //设置为循环定时器



    pauseBtnState = false; //暂停按钮处于暂停状态
    self_state = SELF_STOP ;//自检设备运行状态

    //把所有控件添加到主布局中
//    mainLayout->addWidget(label_title);
//    mainLayout->addWidget(textEdit_content);
//    mainLayout->addLayout(layout_btn);
//    mainLayout->addWidget(widget_content);
//    setAutoFillBackground(true);
//    setLayout(mainLayout);
}

//设置某一行
void selfTestWidget::SetStep(SelfTestStep *step)
{
    int i = step->number; //i是序号，也是每一行的行号
    tableWidget->setCellWidget(i-1,0,step->checkBox);
    tableWidget->setCellWidget(i-1,1,step->label);
    tableWidget->setCellWidget(i-1,2,step->spinBox);
    tableWidget->setCellWidget(i-1,3,step->label_expand);
    tableWidget->setCellWidget(i-1,4,step->btn);
    tableWidget->setCellWidget(i-1,5,step->label_result);


}
//设置所有复选框状态（全选、全部选）
void selfTestWidget::setAllCheckStatus(bool b)
{
    step1->checkBox->setChecked(b);
    step2->checkBox->setChecked(b);
    step3->checkBox->setChecked(b);
    step4->checkBox->setChecked(b);
}

/****单步运行按钮信号槽********************/
void selfTestWidget::runSignalStepSlot(int num, int count)
{
    QString cmdStr ;
    if( self_state != SELF_STOP ){
        QMessageBox::critical(this,tr("提示！"),tr("上一次单步运行还没有完成,请稍后操作!"));
        return;  //如果暂停按钮在继续状态下，提示退出。
    }
    if( !count ){
        QMessageBox::critical(this,tr("提示！"),tr("次数不能选择为0!"));
        return;  //如果选择的次数为0，提示退出
    }
    switch(num){            //根据num来确定当前点击的是哪个步骤，目前分为以下6步
    case 1:
        cmdStr = "00,03,ff,ff,00,01," + QString::number(count,16);   //自检x轴
        WorkQueue->enqueue(cmdStr); //将任务加入工作队列
        step1->spinBox->setValue(0);
        break;
    case 2:
        cmdStr = "00,04,ff,ff,00,01," + QString::number(count,16);   //自检y轴
        WorkQueue->enqueue(cmdStr); //将任务加入工作队列
        step2->spinBox->setValue(0);
        break;
    case 3:
        cmdStr = "00,05,ff,ff,00,01,"  + QString::number(count,16);   //自检z轴
        WorkQueue->enqueue(cmdStr); //将任务加入工作队列
        step3->spinBox->setValue(0);
        break;
    case 4:
        cmdStr = "00,06,ff,ff,00,01,"  + QString::number(count,16);   //底噪测量
        WorkQueue->enqueue(cmdStr); //将任务加入工作队列
        step4->spinBox->setValue(0);
        break;
    }
    serialPort::mySend_Data("00,02,ff,ff,00,00"); //发送是否空闲询问命令
    self_state = SELF_STEP_RUN;  //启动状态
    InquiryTimer->start();  //启动定时器
}


/**********询问是否空闲定时器超时槽***********************************************/
void selfTestWidget::InquiryTimerOverSlot()
{
    if( !WorkQueue->isEmpty()){
        serialPort::mySend_Data("00,02,ff,ff,00,00"); //发送是否空闲询问命令
        qDebug() << "<<<<<<<<<<发送一次询问空闲命令";
    }
}

/**
 * @brief 处理自检界面命令信号槽
 * @param 自检界面下，下位机发过来的命令
 */
void selfTestWidget::self_Test_CMDSlot(QString str)
{
    QByteArray Receive_array = 0;
    qDebug() << "自检收到一条命令" << str;
    Receive_array = serialPort::HEXStringToArr(str);
    uint16_t dataLength = (uint16_t)(((Receive_array.at(4)&0xffff)<< 8)|(Receive_array.at(5)&0xff));//数据长度
    unsigned char cmd = (Receive_array.at(1) & 0xff); //命令
    unsigned int noise_value = 0;  //底噪数值临时定义
    if( ( Receive_array.at(0) & 0xff) & 0x40 ){   //MCU返回码命令解析
        switch(cmd){
        case SELF_WHETHER_FREE_RETURN_CMD:
            if( dataLength != 1){
                qDebug() << "自检空闲MUC返回码没有数据长度不对";
                return;
            }
            qDebug() << "自检空闲命令";
            if( !Receive_array.at(6) & 0xff ){ //判断是否空闲
                qDebug() << "是空闲命令";

                if( !WorkQueue->isEmpty()){
                    QString str;
                    WorkQueue->dequeue(str);
                    qDebug() << "队列字符串"<< str;
                    RoundPB->setValue(0);    //将自检进度设置为0.
                    emit serialPort::ReceiveThread.sendDataSign(str);

                }
            }else qDebug() << "是忙命令";

            break;
        }
        return;
    }
    switch(cmd){
    case SELF_PROGRESS_CMD:
        RoundPB->setValue(Receive_array.at(6) & 0xff);    //设置原型进度条进度值
        break;
    case SELF_X_INFOR_CMD:
        if( !Receive_array.at(6) & 0xff ){
            textEdit_content->append(QString(tr("X轴自检成功\n")));
        }else {
            textEdit_content->append(QString(tr("X轴自检失败\n")));
        }

        if( self_state ==  SELF_STEP_RUN ){         //对暂停按钮和单步或者全速进行处理
            self_state = SELF_STOP;
            if( pauseBtnState ){ //如果暂停/继续按钮处于继续时，将按钮变成暂停
                pauseBtnState = false;
                btn_pause->setStyleSheet("QPushButton{border-image: url(:/picture/selfTest/pause-up.png);}"
                                         "QPushButton:hover{border-image: url(:/picture/selfTest/pause-up.png);}"
                                         "QPushButton:pressed{border-image: url(:/picture/selfTest/pause-down.png);}");
            }
        }else if( self_state ==  SELF_FULL_START ){
            if ( WorkQueue->isEmpty() ){
                self_state = SELF_STOP;
                if( pauseBtnState ){ //如果暂停/继续按钮处于继续时，将按钮变成暂停
                    pauseBtnState = false;
                    btn_pause->setStyleSheet("QPushButton{border-image: url(:/picture/selfTest/pause-up.png);}"
                                             "QPushButton:hover{border-image: url(:/picture/selfTest/pause-up.png);}"
                                             "QPushButton:pressed{border-image: url(:/picture/selfTest/pause-down.png);}");
                }
            }
        }

        break;
    case SELF_Y_INFOR_CMD:
        if( !Receive_array.at(6) & 0xff ){
            textEdit_content->append(QString(tr("Y轴自检成功\n")));
        }else {
            textEdit_content->append(QString(tr("Y轴自检失败\n")));
        }

        if( self_state ==  SELF_STEP_RUN ){         //对暂停按钮和单步或者全速进行处理
            self_state = SELF_STOP;
            InquiryTimer->stop();  //停止询问定时器
            if( pauseBtnState ){ //如果暂停/继续按钮处于继续时，将按钮变成暂停
                pauseBtnState = false;
                btn_pause->setStyleSheet("QPushButton{border-image: url(:/picture/selfTest/pause-up.png);}"
                                         "QPushButton:hover{border-image: url(:/picture/selfTest/pause-up.png);}"
                                         "QPushButton:pressed{border-image: url(:/picture/selfTest/pause-down.png);}");
            }
        }else if( self_state ==  SELF_FULL_START ){
            if ( WorkQueue->isEmpty() ){
                InquiryTimer->stop();  //停止询问定时器
                self_state = SELF_STOP;
                if( pauseBtnState ){ //如果暂停/继续按钮处于继续时，将按钮变成暂停
                    pauseBtnState = false;
                    btn_pause->setStyleSheet("QPushButton{border-image: url(:/picture/selfTest/pause-up.png);}"
                                             "QPushButton:hover{border-image: url(:/picture/selfTest/pause-up.png);}"
                                             "QPushButton:pressed{border-image: url(:/picture/selfTest/pause-down.png);}");
                }
            }
        }

        break;
    case SELF_Z_INFOR_CMD:
        if( !Receive_array.at(6) & 0xff ){
            textEdit_content->append(QString(tr("Z轴自检成功\n")));
        }else {
            textEdit_content->append(QString(tr("Z轴自检失败\n")));
        }

        if( self_state ==  SELF_STEP_RUN ){         //对暂停按钮和单步或者全速进行处理
            self_state = SELF_STOP;
            InquiryTimer->stop();  //停止询问定时器
            if( pauseBtnState ){ //如果暂停/继续按钮处于继续时，将按钮变成暂停
                pauseBtnState = false;
                btn_pause->setStyleSheet("QPushButton{border-image: url(:/picture/selfTest/pause-up.png);}"
                                         "QPushButton:hover{border-image: url(:/picture/selfTest/pause-up.png);}"
                                         "QPushButton:pressed{border-image: url(:/picture/selfTest/pause-down.png);}");
            }
        }else if( self_state ==  SELF_FULL_START ){
            if ( WorkQueue->isEmpty() ){
                self_state = SELF_STOP;
                InquiryTimer->stop();  //停止询问定时器
                if( pauseBtnState ){ //如果暂停/继续按钮处于继续时，将按钮变成暂停
                    pauseBtnState = false;
                    btn_pause->setStyleSheet("QPushButton{border-image: url(:/picture/selfTest/pause-up.png);}"
                                             "QPushButton:hover{border-image: url(:/picture/selfTest/pause-up.png);}"
                                             "QPushButton:pressed{border-image: url(:/picture/selfTest/pause-down.png);}");
                }
            }
        }

        break;
     case SELF_RETURN_GROUND_NOISE_CMD:

            noise_value |= ( ( (Receive_array.at(6)&0xff) << 24 ) | ( (Receive_array.at(7)&0xff) << 16 )
                                          | ( (Receive_array.at(8)&0xff) << 8 ) |  (Receive_array.at(9)&0xff ) );
            textEdit_content->append(QString(tr("当前光子计数器底噪值： ")) + QString::number(noise_value,10)+ "\n");

            if( self_state ==  SELF_STEP_RUN ){         //对暂停按钮和单步或者全速进行处理
                InquiryTimer->stop();  //停止询问定时器
                self_state = SELF_STOP;
                if( pauseBtnState ){ //如果暂停/继续按钮处于继续时，将按钮变成暂停
                    pauseBtnState = false;
                    btn_pause->setStyleSheet("QPushButton{border-image: url(:/picture/selfTest/pause-up.png);}"
                                             "QPushButton:hover{border-image: url(:/picture/selfTest/pause-up.png);}"
                                             "QPushButton:pressed{border-image: url(:/picture/selfTest/pause-down.png);}");
                }
            }else if( self_state ==  SELF_FULL_START ){
                if ( WorkQueue->isEmpty() ){
                    self_state = SELF_STOP;
                    if( pauseBtnState ){ //如果暂停/继续按钮处于继续时，将按钮变成暂停
                        pauseBtnState = false;
                        btn_pause->setStyleSheet("QPushButton{border-image: url(:/picture/selfTest/pause-up.png);}"
                                                 "QPushButton:hover{border-image: url(:/picture/selfTest/pause-up.png);}"
                                                 "QPushButton:pressed{border-image: url(:/picture/selfTest/pause-down.png);}");
                    }
                }
            }

        break;
    }
}

/**
 * @brief 启动按钮信号槽
 */
void selfTestWidget::startBtnSlot()
{
    QString cmdStr;
/****先判断自检的是否没有选择***************/
    if( !step1->checkBox->isChecked() || !step2->checkBox->isChecked() || !step3->checkBox->isChecked() || !step4->checkBox->isChecked()){
        QMessageBox::critical(this,tr("提示！"),tr("没有选择任何自检步骤"));
        return;
    }
/****对各项步骤选择进行判断**********************************/
    if(step1->checkBox->isChecked()){
        if( ! step1->spinBox->value()){
            QMessageBox::critical(this,tr("提示！"),tr("自检X轴次数选型不能为0"));
            return;
        }
        cmdStr = "00,03,ff,ff,00,01," + QString::number(step1->spinBox->value(),16);   //自检x轴
        WorkQueue->enqueue(cmdStr); //将任务加入工作队列
    }
    if(step2->checkBox->isChecked()){
        if( ! step2->spinBox->value()){
            QMessageBox::critical(this,tr("提示！"),tr("自检Y轴次数选型不能为0"));
            return;
        }
        cmdStr = "00,04,ff,ff,00,01,"  + QString::number(step2->spinBox->value(),16);   //自检Y轴
        WorkQueue->enqueue(cmdStr); //将任务加入工作队列
    }
    if(step3->checkBox->isChecked()){
        if( ! step3->spinBox->value()){
            QMessageBox::critical(this,tr("提示！"),tr("自检Z轴次数选型不能为0"));
            return;
        }
        cmdStr = "00,05,ff,ff,00,01,"  + QString::number(step3->spinBox->value(),16);   //自检Z轴
        WorkQueue->enqueue(cmdStr); //将任务加入工作队列
    }
    if(step4->checkBox->isChecked()){
        if( ! step4->spinBox->value()){
            QMessageBox::critical(this,tr("提示！"),tr("底噪测量次数选型不能为0"));
            return;
        }
        cmdStr = "00,06,ff,ff,00,01,"  + QString::number(step4->spinBox->value(),16);   //底噪
        WorkQueue->enqueue(cmdStr); //将任务加入工作队列
    }
    serialPort::mySend_Data("00,02,ff,ff,00,00"); //发送是否空闲询问命令
    self_state = SELF_FULL_START;  //启动状态
    InquiryTimer->start();  //启动询问定时器
}

/**
 * @brief 停止按钮信号槽
 */
void selfTestWidget::stopBtnSlot()
{
    RoundPB->setValue(0);    //恢复进度条值
    serialPort::mySend_Data("00,0E,ff,ff,00,00");  //发送停止命令
    if( pauseBtnState ){ //如果暂停/继续按钮处于继续时，将按钮变成暂停
        pauseBtnState = false;
        btn_pause->setStyleSheet("QPushButton{border-image: url(:/picture/selfTest/pause-up.png);}"
                                 "QPushButton:hover{border-image: url(:/picture/selfTest/pause-up.png);}"
                                 "QPushButton:pressed{border-image: url(:/picture/selfTest/pause-down.png);}");
    }
    WorkQueue->makeEmpty();
    self_state = SELF_STOP;
    InquiryTimer->stop();  //停止询问定时器
}

/**
 * @brief 暂停按钮信号槽
 */
void selfTestWidget::pauseBtnSlot()
{
    if ( self_state == SELF_FULL_START || self_state == SELF_STEP_RUN ){
        if( !pauseBtnState){  //按钮处于暂停
            serialPort::mySend_Data("00,0C,ff,ff,00,00");  //发送暂停命令
            pauseBtnState = true;

            btn_pause->setStyleSheet("QPushButton{border-image: url(:/picture/selfTest/continue-up.png);}"
                                     "QPushButton:hover{border-image: url(:/picture/selfTest/continue-up.png);}"
                                     "QPushButton:pressed{border-image: url(:/picture/selfTest/continue-down.png);}");
            InquiryTimer->stop();  //停止询问定时器
        }else{
            serialPort::mySend_Data("00,0D,ff,ff,00,00");  //发送继续命令
            pauseBtnState = false;

            btn_pause->setStyleSheet("QPushButton{border-image: url(:/picture/selfTest/pause-up.png);}"
                                     "QPushButton:hover{border-image: url(:/picture/selfTest/pause-up.png);}"
                                     "QPushButton:pressed{border-image: url(:/picture/selfTest/pause-down.png);}");
            InquiryTimer->start();  //停止询问定时器
        }
    }else {
        QMessageBox::critical(this,tr("提示！"),tr("当前没有正在运行的项目！"));
        return;
    }
}
/**
 * @brief 复位按钮信号槽
 */
void selfTestWidget::resetBtnSlot()
{
    serialPort::mySend_Data("00,0f,ff,ff,00,00");  //发送复位命令
}





//获取单步的数据（选中状态和操作次数）
QString selfTestWidget::getStepData(SelfTestStep *step){
    QString s = "";
    bool isCheck = step->checkBox->isChecked();//当前checkBox选中状态
    QString times = step->spinBox->text();//当前次数

    if(isCheck){
        s = "true--------"+times;
    }else{
        s = "false-------"+times;
    }
    return s;
}

//获取所有数据并显示在textEdit中。
void selfTestWidget::getStepDatas()
{
    QString str = "";
    str = str+"步骤一：----"+getStepData(step1)+"\n"
            +"步骤二：----"+getStepData(step2)+"\n"
            +"步骤三：----"+getStepData(step3)+"\n"
            +"步骤四：----"+getStepData(step4)+"\n";
    textEdit_content->setText(str);
}

/*******发送当前时间命令*******/
void selfTestWidget::sendCMDToPC()
{
    QString data_time = "00,01,ff,ff,00,00"; //告知下位机进入自检界面
    serialPort::mySend_Data(data_time);
}


/**************信号和槽绑定****************************/
void selfTestWidget::connectInit()
{
    connect(btn_start,SIGNAL(clicked()),this,SLOT(startBtnSlot())); // 启动按钮
    connect(btn_stop,SIGNAL(clicked()),this,SLOT(stopBtnSlot()));// 停止按钮
    connect(btn_pause,SIGNAL(clicked()),this,SLOT(pauseBtnSlot()));// 暂停按钮
    connect(btn_reset,SIGNAL(clicked()),this,SLOT(resetBtnSlot()));// 复位按钮
    /********单步绑定信号槽*****************************************************************/
    connect(step1,SIGNAL(sendData(int,int)),this,SLOT(runSignalStepSlot(int ,int)));
    connect(step2,SIGNAL(sendData(int,int)),this,SLOT(runSignalStepSlot(int ,int)));
    connect(step3,SIGNAL(sendData(int,int)),this,SLOT(runSignalStepSlot(int ,int)));
    connect(step4,SIGNAL(sendData(int,int)),this,SLOT(runSignalStepSlot(int ,int)));
    connect(InquiryTimer,SIGNAL(timeout()),this,SLOT(InquiryTimerOverSlot()));
    connect(&serialPort::ReceiveThread,SIGNAL(self_test_cmdSign(QString)),this,SLOT(self_Test_CMDSlot(QString)),Qt::DirectConnection);
}





