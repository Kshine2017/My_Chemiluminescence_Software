#ifndef SERIAL_THREAD_H
#define SERIAL_THREAD_H
#include <QThread>

class serial_thread : public QThread
{
    Q_OBJECT
public:
    serial_thread();
private:
    bool IsReturnCode(QByteArray &array); /**< 是不是返回码*/
    bool IsOkReturnCode(QByteArray &array); /**< 返回码是否正确*/
    void return_okCode(const QByteArray &array);/**< 发送给MCU正确的返回码*/
    void dealData_Handle(QByteArray &array);  /**< 解析当前命令*/
protected:
    void run();

signals:
    void okAnswering_Sign(QString str); //正确应答信号
    void ErrAnswering_Sign(QString str);//错误应答
    void communicationComplete_Sign();  //接收完成处理信号
    void self_test_cmdSign(QString str);//自检状态命令
    void reagent_programe_cmdSign(QString str);//试剂船编辑
    void unkonow_cmdSign(QString str); //未知品操作命令
    void standard_cmdSign(QString str); //标准品操作命令
    void calibration_cmdSign(QString str); //校准品操作命令
    void other_cmdSign(QString str); // 其它操作命令，如温度
    void quality_cmdSign(QString str); //质控品操作命令
    void sendDataSign(QString str);   //通过串口发送数据信号
    void ErrDataSign(QString str);  //发送通讯信息错误信号
};

#endif // SERIAL_THREAD_H
