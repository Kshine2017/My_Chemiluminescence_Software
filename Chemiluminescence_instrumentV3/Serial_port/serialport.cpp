#include "serialport.h"
#include <QMessageBox>



QByteArray serialPort::send_shareMemery;  /**< 串口发送buffer*/
QByteArray serialPort::Receive_shareMemery; /**< 串口接收buffer*/
QByteArray serialPort::Temp_Receive_shareMemery; /** <串口接收临时 */
QMutex serialPort::SendMutex;               /**< 串口发送互斥锁*/
QMutex serialPort::ReceiveMutex;     /**< 串口接收互斥锁*/
int serialPort::communication_num = 1;  //必须是1，不然不发送数据
QTimer serialPort::Serical_SendTimer; //串口发送超时定时器
serial_thread serialPort::ReceiveThread; //处理数据线程
QSerialPort serialPort::mySerialPort; /**< 串口*/
bool serialPort::returnOkflag = true; //MCU已经正确应答命令标志
/**
 * @brief 校准和（累加和）
 * @param s
 * @param num
 * @return
 */
uint16_t serialPort::calibration_data(const QByteArray &src, int num)
{
    uint16_t temp = 0;
    QByteArray array = src;
    for(int i = 0;i<num-6;i++){
        temp += array.at(i)&0xff;
    }
    return temp;
}

/**
 * @brief 字符串转成1进制数组
 * @param hexstr
 * @return
 */
QByteArray serialPort::HEXStringToArr(QString hexstr)
{
    QByteArray qrst;
    hexstr=hexstr.trimmed(); //去除空白空格
    QStringList sl=hexstr.split(","); //遍历hexstr字符串容器
    foreach(QString str,sl)
    {
        if(!str.isEmpty())
            qrst.append((str.toInt(Q_NULLPTR,16)&0xFF));
    }
    return qrst;
}
/**
 * @brief 串口构造函数
 */
serialPort::serialPort(QWidget *parent):QWidget(parent)
{
    mySerialInfo = new QSerialPortInfo();
    Serical_ReceiveTimer = new QTimer(this);

    queryTimer = new QTimer; //工作队列询问定时器
    WorkQueue = new Queue; //工作队列
    serialPort::ReceiveMutex.lock();     /**< 串口接收互斥锁*/
    serialPort::ReceiveThread.start(QThread::TimeCriticalPriority); //尽可能多安排时间
    connectInit();
}

/**
 * @brief 发送串口数据
 * @return
 */
void serialPort::mySend_Data( const QString &string)
{
    if( serialPort::returnOkflag ){ //防止上次命令还没有正确应答
        serialPort::returnOkflag = false;
        serialPort::SendMutex.lock(); //上锁
        QString str = string;
        uint16_t  data_length = 0; //数据长度
        str.insert(0,"D5,C8,D5,C8,"); //包头
        str.append(",00,00,13,AB,13,AB");//校验加包尾
        serialPort::send_shareMemery = HEXStringToArr(str);

        data_length = (uint16_t)serialPort::send_shareMemery.size()-16; //16是除去数据的格式
        serialPort::send_shareMemery[8] =  ((data_length >> 8)&0xff);  //更改数据长度
        serialPort::send_shareMemery[9] =  (data_length&0xff);

        uint16_t calibData = (uint16_t)calibration_data(serialPort::send_shareMemery,serialPort::send_shareMemery.size());
        unsigned char caliHight = (unsigned char)(calibData>>8);
        unsigned char calilow = (unsigned char)calibData;

        serialPort::send_shareMemery[serialPort::send_shareMemery.size()-6] = (caliHight&0xff);     //更改数据校准
        serialPort::send_shareMemery[serialPort::send_shareMemery.size()-5] = (calilow&0xff);
        qDebug() << "当前发送" << serialPort::send_shareMemery;
        serialPort::mySerialPort.write(serialPort::send_shareMemery);//写入数据进串口
        qDebug() << "当前发送定时器启动";
        serialPort::Serical_SendTimer.start(OVER_TIME); //启动发送倒计时

        serialPort::SendMutex.unlock();//解锁
    }
}



/**
 * @brief 扫描串口
 */
void serialPort::getSerialPortID()
{
    serialInfoList =  mySerialInfo->availablePorts(); //可以用的串口号
    int nSerialnum = serialInfoList.length(); //列表长度
    for(int i = 0;i<nSerialnum;i++){
         QString serialdesp = serialInfoList[i].description();
         QString serialName = serialInfoList[i].portName();
         qDebug() << serialdesp <<  serialName;
    }
}

//设置串口参数  波特率：57600 偶校验  数据位：8 停止位：1 流控：无
void serialPort::setSerialPort()
{
//串口的序列号，这个号码一般来说是唯一的。串口名称可能会随时被更改
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        if( info.portName() == ("COM2")){  //如果串口号是1，就绑定
            *mySerialInfo = info;
            break;
        }
    }
    serialPort::mySerialPort.setPort(*mySerialInfo);
    if(serialPort::mySerialPort.open(QIODevice::ReadWrite)){
        qDebug() << "serialPort::mySerialPort.open(QIODevice::ReadWrite)";
        serialPort::mySerialPort.setBaudRate(QSerialPort::Baud57600);
        serialPort::mySerialPort.setParity(QSerialPort::EvenParity); //偶校验证
        serialPort::mySerialPort.setDataBits(QSerialPort::Data8);
        serialPort::mySerialPort.setStopBits(QSerialPort::OneStop);
        serialPort::mySerialPort.setFlowControl(QSerialPort::NoFlowControl);
        serialPort::mySerialPort.clearError();  //将串口错误状态代码清空
        serialPort::mySerialPort.clear();       //清空串口缓冲数据
        serialPort::mySerialPort.setReadBufferSize(1000);

    }
}

/**
 * @brief 信号槽绑定函数初始化
 */
void serialPort::connectInit()
{
    connect(&serialPort::mySerialPort,SIGNAL(readyRead()),this,SLOT(mySerialRead()));//绑定串口有数据需要读的信号槽
    connect(&serialPort::Serical_SendTimer,SIGNAL(timeout()),this,SLOT(SendOvertime_dealFuction()));
    connect(Serical_ReceiveTimer,SIGNAL(timeout()),this,SLOT(ReceiveOvertime_dealFuction()));
    connect(&serialPort::ReceiveThread,SIGNAL(okAnswering_Sign(QString)),this,SLOT(okAnswering_SignSlot(QString)));
    connect(&serialPort::ReceiveThread,SIGNAL(ErrAnswering_Sign(QString)),this,SLOT(ErrAnswering_SignSlot(QString)));
    connect(&serialPort::ReceiveThread,SIGNAL(communicationComplete_Sign()),this,SLOT(communicationComplete_SignSlot()));
    connect(&serialPort::ReceiveThread,SIGNAL(ErrDataSign(QString)),this,SLOT(ErrDataSignSlot(QString)));
    connect(&serialPort::ReceiveThread,SIGNAL(sendDataSign(QString)),this,SLOT(sendDataSignSlot(QString))); //发送数据信号槽
    connect(queryTimer,SIGNAL(timeout()),this,SLOT(queryTimerSlot()));
}

//信号槽 读取缓冲区串口数据
void serialPort::mySerialRead()
{   QByteArray temp;
    temp = serialPort::serialPort::mySerialPort.readAll();
    serialPort::Temp_Receive_shareMemery.append(temp);
    Serical_ReceiveTimer->start( RECVE_OVER_TIME ); //超时时间设置为10ms
}

/**
 * @brief 发送应答超时处理
 */
void serialPort::SendOvertime_dealFuction()
{
    communication_num++;
    if(serialPort::communication_num> COMMUNICATION_COUNT){
       serialPort::Serical_SendTimer.stop();
       serialPort::send_shareMemery.clear();
       qDebug() << "发送定时器超时3次";
       if( QMessageBox::critical(this,tr("错误代码E0001"),tr("错误代码E0001:当前通讯异常!")) == QMessageBox::Ok){
          serialPort::communication_num = 1;
          serialPort::returnOkflag = true;
          WorkQueue->makeEmpty(); //清空待发送数据命令
          queryTimer->stop();
       }

    }
    if(  communication_num > 1 ){
        serialPort::SendMutex.lock();//上锁
        qDebug() << "发送超时*****************";
        serialPort::mySerialPort.write(serialPort::send_shareMemery);
        serialPort::SendMutex.unlock();//解锁
        serialPort::Serical_SendTimer.start(OVER_TIME); //100ms秒没有反应
    }
}

/**
 * @brief 接收应答超时处理,应答超时代表当前一个数据包传输完成
 */
void serialPort::ReceiveOvertime_dealFuction()
{
        Serical_ReceiveTimer->stop();
        serialPort::serialPort::mySerialPort.clear(QSerialPort::Input);
        serialPort::serialPort::Receive_shareMemery = serialPort::serialPort::Temp_Receive_shareMemery;
        serialPort::serialPort::Temp_Receive_shareMemery.clear();
        serialPort::ReceiveMutex.unlock();//解锁
}


void serialPort::okAnswering_SignSlot(QString string)
{
    QString sendString = "D5,C8,D5,C8,00,00,FF,FF,00,00,00,00,13,AB,13,AB";
    QString tempStr = string;
    QByteArray send_array = 0; //待发送数组
    qDebug() <<"接收到命令返回码" <<tempStr;
    sendString.replace(12,5,tempStr);
    send_array = HEXStringToArr(sendString);
    uint16_t calibData = calibration_data(send_array,send_array.size());
    unsigned char caliHight = (unsigned char)(calibData>>8);
    unsigned char calilow = (unsigned char)calibData;

    send_array[send_array.size()-6] = (caliHight&0xff);     //更改数据校准
    send_array[send_array.size()-5] = (calilow&0xff);

    serialPort::SendMutex.lock();//上锁
    serialPort::serialPort::mySerialPort.write(send_array);
    serialPort::SendMutex.unlock();//上锁
    qDebug() << sendString;

}

/***错误应答信号处理函数*/
void serialPort::ErrAnswering_SignSlot(QString string)
{
    if(string == "通讯数据包头或包尾不正确"){
        QMessageBox::critical(this,tr("错误代码E0001"),tr("错误代码E0001:通讯数据包头或包尾不正确!"));
    }
}

/**
 * @brief MCU错误信号数据处理信号槽
 * @param str
 */
void serialPort::ErrDataSignSlot(QString str)
{
    qDebug() << "处理错误信号线程号 = " << QThread::currentThreadId();
    if(str == "数据长度不对"){
       QMessageBox::critical(this,tr("错误代码E0001"),tr("错误代码E0001:MCU通讯数据长度不对!"));
    }else if( str == "无此试剂方案"){
       QMessageBox::critical(this,tr("错误代码E0020"),tr("错误代码E0020:无此试剂方案!"));
    }else if( str == "试剂船全速运行只能插入一个试剂船"){
       QMessageBox::critical(this,tr("错误代码E0021"),tr("错误代码E0021:试剂船全速运行只能插入一个试剂船!"));
    }else if( str == "扫码枪数据不对"){
       QMessageBox::critical(this,tr("错误代码E0022"),tr("错误代码E0022:扫码枪数据不对!"));
    }else if( str == "此条码编码异常"){
        QMessageBox::critical(this,tr("此条码编码异常E0023"),tr("错误代码E0023:此条码编码异常!"));
    }else if( str == "此试剂已过期"){
        QMessageBox::critical(this,tr("错误代码E0024"),tr("错误代码E0024:此试剂已过期!"));
    }else if( str == "当前试剂船正在运行,被强制拔出"){
        QMessageBox::critical(this,tr("错误代码E0005"),tr("错误代码E0005:当前试剂船正在运行,被强制拔出!"));
    }else if( str == "温度模块出现故障"){
        QMessageBox::critical(this,tr("错误代码E0025"),tr("错误代码E0025:温度模块出现故障!"));
    }
}

/**
 * @brief serialPort::通讯完成处理信号槽
 */
void serialPort::communicationComplete_SignSlot()
{
    /****清理串口数据和设置发送条件*******/
      serialPort::Serical_SendTimer.stop();
      serialPort::communication_num = 1;
      serialPort::returnOkflag = true;
      serialPort::Receive_shareMemery.clear();//清除应答接收数据
      serialPort::send_shareMemery.clear();
}

/**发送队列查询超时信号槽**/
void serialPort::queryTimerSlot()
{
    QString sendString ;
    if( WorkQueue->isEmpty()){
        queryTimer->stop();
    }else {
        if( serialPort::returnOkflag ){
            WorkQueue->dequeue(sendString);
            qDebug() << "即将发送数据" <<sendString << "线程号" << QThread::currentThreadId();
            serialPort::mySend_Data(sendString);
        }else qDebug() << "当前待发送数据包里面有消息等待发送，但发送条件不成立";
    }
}

/**
 * @brief 在处理函数里面发送数据到MCU
 * @param str
 */
void serialPort::sendDataSignSlot(QString str)
{
    QString sendString = str;
//    if( serialPort::returnOkflag ){
//        serialPort::mySend_Data(sendString);
//    }
//    else {
        WorkQueue->enqueue(str);
        queryTimer->start(500);
//    }
}


