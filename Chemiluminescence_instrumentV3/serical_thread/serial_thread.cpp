#include "serial_thread.h"
#include "Serial_port/serialport.h"
#include "QMessgeBox/mymessgebox.h"
#include <QDebug>


serial_thread::serial_thread()
{


}

/**
 * @brief 串口接收到的数据是不是返回码
 * @return
 */
bool serial_thread::IsReturnCode(QByteArray &array)
{
    if( (array[4]&0xff) & 0x40 ){    //是MCU返回码
        if((array[5] & 0xff) & 0x02){  //自检带有空闲不空闲返回数据返回码
           IsOkReturnCode( array );
           return false;
        }else if( (array[5]&0xff) & 0x05){//未知品、质控品、校准品有空闲不空闲返回数据返回码
           IsOkReturnCode( array );
           return false;
        }else if((array[5]&0xff) & 0x06 ){
            IsOkReturnCode( array );
            return false;
        }
      qDebug() << "当前收到数据是MCU返回码";
      return true;
    }else return false;
}

/**
 * @brief MCU应答是否正确应答
 * @param 接收缓冲
 * @return
 */
bool serial_thread::IsOkReturnCode(QByteArray &array)
{
    if( ( ( (serialPort::send_shareMemery[4] & 0x0f) | 0x80 ) == (array[4] & 0xff))
            && (( serialPort::send_shareMemery[5] & 0xff) == (array[5] & 0xff ))){
        qDebug() << "这是一个正确的MCU返回码";
        emit communicationComplete_Sign();//通讯完成处理信号
        return true;
    } else {
        qDebug() << "这是一个校验正确但返回错误的MCU返回码";
        return false;
    }
}



/**
 * @brief 发送给MCU正确的返回码
 * @param array接收Buffer
 */
void serial_thread::return_okCode(const QByteArray &array)
{
    QString str = 0;
    unsigned char cmd = 0;
    if( (array[4]&0xff ) & 0x80 ){
        cmd = ( ( array[4] & 0xff ) & 0x0f ) | 0x20;  //返回码是0x2开头的
        str.append(QString::number(cmd,16));
        str.append(",");
        cmd = array[5] & 0xff;
        str.append(QString::number(cmd,16));
        emit okAnswering_Sign(str);
        qDebug() << "%%%%%%%%%%%%%%%%s是MCU命令";
    }
}

/**
 * @brief 解析当前命令
 */
void serial_thread::dealData_Handle(QByteArray &array)
{
    QString str = 0; //临时转发命令和数据字符串
    uint16_t dataLength =(uint16_t)(((array.at(8)&0xffff)<< 8)|(array.at(9)&0xff));
    int arrayLength = array.size();
    bool headData_flag = ((array.at(0)&0xff) == 0xD5) &&((array.at(1)&0xff) == 0xC8) && ((array.at(2)&0xff) == 0xD5) && ((array.at(3)&0xff) == 0xC8);
    bool rearData_flag = ((array.at(arrayLength-4)&0xff) == 0x13) && ((array.at(arrayLength-3)&0xff) == 0xAB )&& ((array.at(arrayLength-2)&0xff) == 0x13) && ((array.at(arrayLength-1)&0xff) == 0xAB );
    if(!(headData_flag && rearData_flag) ){
        qDebug() << "当前数据包，包头或包尾有错误" ;
        return;
    }else qDebug() << "当前数据包，包头或包尾正确"<<"数据长度为"<< dataLength;
    unsigned char State = (array.at(4) & 0xff);
    unsigned char cmd = (array.at(5) & 0xff);
    qDebug() << "监测数据 = "<< dataLength<<"信号线程号 = " << QThread::currentThreadId();
    switch( State){
    case SELF_TEST: //MCU主动发送的自检数据
        for(int i = 0;i< dataLength+6;i++){
            str.append(QString::number(array.at(4+i)&0xff,16));
            str.append(",");
        }
        str.chop(1);
        emit self_test_cmdSign(str);
        qDebug() << "当前接收到的数据长度 = "<< dataLength<<"信号线程号 = " << QThread::currentThreadId();
        break;
    case SELF_TEST_RETURN:
        for(int i = 0;i< dataLength+6;i++){
            str.append(QString::number(array.at(4+i)&0xff,16));
            str.append(",");
        }
        str.chop(1);
        emit self_test_cmdSign(str);
        break;
    case UNKNOWN:
        for(int i = 0;i< dataLength+6;i++){
            str.append(QString::number(array.at(4+i)&0xff,16));
            str.append(",");
        }
        str.chop(1);
        emit unkonow_cmdSign(str);
        qDebug() << "当前接收到的数据长度 = "<< dataLength<<"信号线程号 = " << QThread::currentThreadId();
        break;
    case UNKNOWN_RETURN_CMD:
        for(int i = 0;i< dataLength+6;i++){
            str.append(QString::number(array.at(4+i)&0xff,16));
            str.append(",");
        }
        str.chop(1);
        emit unkonow_cmdSign(str);
        break;

    case REAGENT_ALL_RUN:
        for(int i = 0;i< dataLength+6;i++){
            str.append(QString::number(array.at(4+i)&0xff,16));
            str.append(",");
        }
        str.chop(1);
        emit reagent_programe_cmdSign(str);
        break;

    case REAGENT_ALL_RETURN_RUN_CMD:
        for(int i = 0;i< dataLength+6;i++){
            str.append(QString::number(array.at(4+i)&0xff,16));
            str.append(",");
        }
        str.chop(1);
        emit reagent_programe_cmdSign(str);
        break;
    case STANDARD_OPRATION:
        for(int i = 0;i< dataLength+6;i++){
            str.append(QString::number(array.at(4+i)&0xff,16));
            str.append(",");
        }
        str.chop(1);
        emit standard_cmdSign(str);
        break;
    case STANDARD_OPRATION_RETURN_CMD:
        for(int i = 0;i< dataLength+6;i++){
            str.append(QString::number(array.at(4+i)&0xff,16));
            str.append(",");
        }
        str.chop(1);
        emit standard_cmdSign(str);
        break;
    case CALIBRATION:
        for(int i = 0;i< dataLength+6;i++){
            str.append(QString::number(array.at(4+i)&0xff,16));
            str.append(",");
        }
        str.chop(1);
        emit calibration_cmdSign(str);
        break;
    case CALIBRATION_RETURN_CMD:
        for(int i = 0;i< dataLength+6;i++){
            str.append(QString::number(array.at(4+i)&0xff,16));
            str.append(",");
        }
        str.chop(1);
        emit calibration_cmdSign(str);
        break;

    case QUALITY:
        for(int i = 0;i< dataLength+6;i++){
            str.append(QString::number(array.at(4+i)&0xff,16));
            str.append(",");
        }
        str.chop(1);
        emit quality_cmdSign(str);
        break;
    case QUALITY_RETURN_CMD:
        for(int i = 0;i< dataLength+6;i++){
            str.append(QString::number(array.at(4+i)&0xff,16));
            str.append(",");
        }
        str.chop(1);
        emit quality_cmdSign(str);
        break;
    case OTHER:
        for(int i = 0;i< dataLength+6;i++){
            str.append(QString::number(array.at(4+i)&0xff,16));
            str.append(",");
        }
        str.chop(1);
        emit other_cmdSign(str);
        break;
    }

    emit communicationComplete_Sign();
}

/**
 * @brief 线程主要工作任务
 */
void serial_thread::run()
{
    unsigned int calibData = 0; //校准码
    volatile unsigned char caliHight = 0; //校准码高字节
    volatile unsigned char calilow = 0;  //校准码低字节
    QByteArray err_array = 0;   //错误返回码
    QByteArray ok_array = 0;   //正确返回码
    int arrayLength ;   //数据包长度
    bool headData_flag; //包头正确否标志
    bool rearData_flag; //包尾正确否标志
    for(;;){
        serialPort::ReceiveMutex.lock(); //阻塞等待一个完整的数据包

        for(int j = 0;j <serialPort::Receive_shareMemery.size(); j++)
            qDebug("当前i:= %d,当前接收到:%x" ,j,serialPort::Receive_shareMemery.at(j)&0xff);

        if(serialPort::Receive_shareMemery.size() < 15){  //当前数据长度小于数据包最低长度
            goto Incomplete;
        }
        /**
       开始分析数据
        **/

        //包头和包尾分析
        arrayLength  = serialPort::Receive_shareMemery.size();
        headData_flag = ((serialPort::Receive_shareMemery.at(0)&0xff) == 0xD5) &&((serialPort::Receive_shareMemery.at(1)&0xff) == 0xC8) && ((serialPort::Receive_shareMemery.at(2)&0xff) == 0xD5) && ((serialPort::Receive_shareMemery.at(3)&0xff) == 0xC8);
        rearData_flag = ((serialPort::Receive_shareMemery.at(arrayLength-4)&0xff) == 0x13) && ((serialPort::Receive_shareMemery.at(arrayLength-3)&0xff) == 0xAB )&& ((serialPort::Receive_shareMemery.at(arrayLength-2)&0xff) == 0x13) && ((serialPort::Receive_shareMemery.at(arrayLength-1)&0xff) == 0xAB );
        if(!(headData_flag && rearData_flag) ){
            qDebug() << "当前数据包，包头或包尾有错误" ;
            emit ErrAnswering_Sign("通讯数据包头或包尾不正确");
            goto check_err;
        }
        //校验和分析
        calibData = serialPort::calibration_data(serialPort::Receive_shareMemery,serialPort::Receive_shareMemery.size());
        caliHight = (unsigned char)((calibData>>8)&0xff);
        calilow = (unsigned char)(calibData&0xff);
        qDebug( "收到数据的校验和= %x",calibData);
        if( !( caliHight == ( serialPort::Receive_shareMemery.at( serialPort::Receive_shareMemery.size()-6)&0xff ) && calilow ==
               ( serialPort::Receive_shareMemery.at(serialPort::Receive_shareMemery.size()-5)&0xff) ) ){
            qDebug("实际数值：高 = %x",serialPort::Receive_shareMemery.at( serialPort::Receive_shareMemery.size()-6)&0xff);
            qDebug("实际数值：低 = %x",serialPort::Receive_shareMemery.at( serialPort::Receive_shareMemery.size()-5)&0xff);
            goto check_err;
        }
        if( IsReturnCode(serialPort::Receive_shareMemery)){  //判断是不是正确的MCU返回码
            if( IsOkReturnCode( serialPort::Receive_shareMemery )){
                goto ok;
            }
        }
        return_okCode(serialPort::Receive_shareMemery); //如果是命令就发送正确接收码给MCU
        /***
         *开始正确的解析当前数据
         */
        dealData_Handle(serialPort::Receive_shareMemery);
        goto ok;

Incomplete:
        qDebug() << "不是一个完整的数据包";
check_err:
        qDebug() << "收到数据不正确";
ok:
        serialPort::Receive_shareMemery.clear();
    }
}

