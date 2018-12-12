/**
  *  @brief    串口设置
  *  @file     serialport.h
  *  @author   谢飞
  *  @version  1.0(版本号)
  *  @date     2017-10-19
  */
#ifndef SERIALPORT_H
#define SERIALPORT_H
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QWidget>
#include <QTimer>
#include <QDebug>
#include <QMutex>
#include "serical_thread/serial_thread.h"
#include "queue/queue.h"
/**自定义的宏**/
#define OVER_TIME 300 //通讯超时判定时间设置
#define COMMUNICATION_COUNT 3  //通讯重发次数
#define RECVE_OVER_TIME 100 //二个数据包之间间隔时间ms

//操作界面
#define SELF_TEST 0X80 //自检
#define SELF_TEST_RETURN 0X40 //自检MCU返回应答,试剂船编辑

#define OTHER 0X86 //其它


#define UNKNOWN 0X81 //未知品
#define UNKNOWN_RETURN_CMD 0X41 //未知品MCU返回应答

#define REAGENT_ALL_RUN 0X82//试剂船全速运行和试剂船编辑
#define REAGENT_ALL_RETURN_RUN_CMD 0X42 //试剂船全速运行MCU应答

#define STANDARD_OPRATION 0X83 //标准品操作
#define STANDARD_OPRATION_RETURN_CMD 0X43 //标准品MCU应答

#define CALIBRATION 0X84   //校准品操作
#define CALIBRATION_RETURN_CMD 0X44   //校准品操作MCU返回码

#define QUALITY 0X85 //质控品操作
#define QUALITY_RETURN_CMD 045 //质控品操作


//命令第二个字节

//自检
#define SELF_WHETHER_FREE_RETURN_CMD 0X02   //是否空闲
#define SELF_PROGRESS_CMD 0X10  //自检进度
#define SELF_SUCESS_CMD 0X11   //自检成功
#define SELF_ERR_CMD 0X12      //自检故障
#define SELF_X_INFOR_CMD 0X13      //自检x轴信息
#define SELF_Y_INFOR_CMD 0X14      //自检y轴信息
#define SELF_Z_INFOR_CMD 0X15      //自检z轴信息
#define SELF_RETURN_GROUND_NOISE_CMD  0X16 //返回底噪


//其它
#define OTHER_TRMPERATURE_CMD 0X50  //返回温度信息


//未知品
#define UNKONOW_PULL_SHIP_CMD 0X10  //试剂船退出
#define UNKONOW_NEW_SHIP_INFOR_CMD   0X11 //新试剂船信息
#define UNKONOE_ALL_TEST_PROGRESS_CMD  0x12 //所有试剂槽进度
#define UNKONOE_ERR_INFOR_CMD  0X13     //返回错误
#define UNKONOE_ONE_TEST_DATA_CMD  0X14     //返回某个测试试剂槽的发光值
#define UNKONOE_WHETHER_FREE_RETURN_CMD 0x05 //MCU返回空闲是否
#define UNKONOE_WHEHTER_SCHED_RETURN_CMD 0X06  //MCY返回是否可以调度命令


//试剂船编辑
#define REAGENT_STEP_PROGRESS_CMD 0X30 //单步进度
#define REAGENT_STEP_FINISH_CMD 0X31 //单步结束信息

#define REA_ALL_RUN_PULL_SHIP_CMD  0X10 //试剂船拔出
#define REA_ALL_RUN_NEW_SHIP_INFOR_CMD 0X11 //新试剂船信息
#define REA_ALL_RUN_ALL_TEST_PROGRESS_CMD 0X12 //所有试剂船进度
#define REA_ALL_RUN_ERR_CMD 0X13               //所有错误信息
#define REA_ALL_RUN_ONE_TEST_DATA_CMD 0X14 //返回某个测试试剂槽的发光值
#define REA_ALL_WHETHER_FREE_RETURN_CMD 0x05  //试剂船全速运行MCU返回是否空闲
#define REA_ALL_WHEHTER_SCHED_RETURN_CMD 0x06  //试剂船全速运行MCU返回是否可以调度

//标准品编辑
#define STANDARD_PULL_SHIP_CMD 0X10 //试剂船拔出
#define STANDARD_NEW_SHIP_INFOR_CMD 0X11 //新试剂船信息
#define STANDARD_ALL_TEST_PROGRESS_CMD 0X12 //所有试剂船进度
#define STANDARD_ERR_CMD 0X13 //返回错误
#define STANDARD_ONE_TEST_DATA_CMD 0X14 //返回某个测试槽信息
#define STANDARD_WHETHER_FREE_RETURN_CMD 0x05  //标准品测试全速运行MCU返回是否空闲
#define STANDARD_WHEHTER_SCHED_RETURN_CMD 0x06  //标准品测试全速运行MCU返回是否可以调度


//校准品
#define CALIBRATION_PULL_SHIP_CMD 0X10 //试剂船拔出
#define CALIBRATION_NEW_SHIP_INFOR_CMD 0X11//新试剂船信息
#define CALIBRATION_ALL_TEST_PROGRESS 0X12//所有试剂船进度
#define CALIBRATION_ERR_CMD 0X13//返回错误
#define CALIBRATION_ONE_TEST_DATA_CMD 0X14//返回某个测试槽信息
#define CALIBRATION_WHETHER_FREE_RETURN_CMD 0x05  //校准品全速运行MCU返回是否空闲
#define CALIBRATION_WHEHTER_SCHED_RETURN_CMD 0x06  //校准品全速运行MCU返回是否可以调度


//质控品
#define QUALITY_PULL_SHIP_CMD 0X10 //试剂船拔出
#define QUALITY_NEW_SHIP_INFOR_CMD 0X11//新试剂船信息
#define QUALITY_ALL_TEST_PROGRESS 0X12//所有试剂船进度
#define QUALITY_ERR_CMD 0X13//返回错误
#define QUALITY_ONE_TEST_DATA_CMD 0X14//返回某个测试槽信息
#define QUALITY_WHETHER_FREE_RETURN_CMD 0x05  //校准品全速运行MCU返回是否空闲
#define QUALITY_WHEHTER_SCHED_RETURN_CMD 0x06  //校准品全速运行MCU返回是否可以调度

class serialPort:public QWidget
{
    Q_OBJECT
public:
    explicit serialPort(QWidget *parent = 0);
    static uint16_t calibration_data(const QByteArray &src, int num);/**<校验数据和*/
    static void mySend_Data(const QString &string); /**<发送数据函数 */

    static QByteArray HEXStringToArr(QString hexstr);
    static QSerialPort mySerialPort; /**< 串口*/

    static QByteArray send_shareMemery;  /**< 串口发送buffer*/
    static QByteArray Receive_shareMemery; /**< 串口接收buffer*/
    static QByteArray Temp_Receive_shareMemery; /**< 串口接收临时buffer*/

    static QMutex SendMutex;               /**< 串口发送互斥锁*/
    static QMutex ReceiveMutex;     /**< 串口接收互斥锁*/
    static int communication_num  ;  //连续发送次数
    static QTimer Serical_SendTimer; //串口发送超时定时器
    static bool returnOkflag;    //MCU已经正确应答命令标志
    //工作队列
    Queue *WorkQueue;  //工作队列
    QTimer *queryTimer; //工作队列询问定时器

    static serial_thread ReceiveThread; //处理数据线程
public:

    void getSerialPortID();//得到串口ID
    void setSerialPort();   //设置串口

private:
    void connectInit();//信号槽绑定函数初始化

private:
    QSerialPortInfo *mySerialInfo;
    QList <QSerialPortInfo> serialInfoList; //扫描的串口号列表

    QTimer *Serical_ReceiveTimer;//串口接收超时定时器



public slots:
    void mySerialRead();    //读取缓冲区里面的数据
    void SendOvertime_dealFuction();//发送应答超时处理函数
    void ReceiveOvertime_dealFuction();//接收超时处理
    void okAnswering_SignSlot(QString string); //正确应答信号槽
    void ErrAnswering_SignSlot(QString string); //错误应答信号槽
    void ErrDataSignSlot(QString str); //MCU错误数据处理
    void communicationComplete_SignSlot(); //接收完成处理信号槽

    void queryTimerSlot(); //发送队列查询定时器
    /**
     * @brief 在处理函数里面发送数据到MCU
     * @param str
     */
    void sendDataSignSlot(QString str);
};

#endif // SERIALPORT_H
