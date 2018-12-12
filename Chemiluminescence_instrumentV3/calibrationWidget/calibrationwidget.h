/**
  *  @brief    校准/质控品
  *  @file     calibrationwidget.h
  *  @author   谢飞
  *  @version  1.0(版本号)
  *  @date     2017-09-12
  */
#ifndef CALIBRATIONWIDGET_H
#define CALIBRATIONWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QStackedWidget>
#include "calibrationWidget/calibration_onewidget.h"
#include "calibrationWidget/calibration_twowidget.h"
#include "calibrationWidget/calibration_calionewidget.h"
#include "calibrationWidget/calibration_qualityonewidget.h"
#include "Serial_port/serialport.h"

class calibrationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit calibrationWidget(QWidget *parent = 0);

public:

    void WidgetInit();
    void connectInit();
public:
    QStackedWidget *stack; /**< 界面堆栈 */
public:

    calibration_oneWidget *oneWidget; /**< 校准第一个窗口界面 */
    calibration_caliOneWidget *caliOneWidget; /**< 校准品界面结果*/
    calibration_qualityOneWidget *qualityOneWidget; /**< 质控第一个界面*/
    calibration_twoWidget *twoWidget; /**< 质控品窗口第一个界面 */

private:
    /**
     * @brief 设置space_num行试剂船信息内容
     * @param space_num 行
     * @param data 数据
     * @param length 数据长度
     */
    void setModel_ReagentInfo(int space_num, QByteArray &data, int interf);
    /**
     * @brief 试剂船拔出处理函数
     * @param postion
     */
    void reagentPopup_CMDHandle(int postion, int num);

    /**
     * @brief 试剂船进度处理函数
     * @param postion
     * @num 1:校准品 2：质控品
     */
    void returnProgress_InfoHandle(QByteArray &data, int interf);
    /**
     * @brief 试剂船错误处理函数
     * @param err
     */
    void returnRegent_ErrHandle(QByteArray &err);
    /**
     * @brief 测试结果处理函数
     * @param data
     */
    void testResultHandle(int interf,QByteArray &data);

signals:

public slots:
    void changeWindow(int num); //切换界面
    void calibration_cmdSignSlot(QString str); //校准品处理接收到的命令信号槽
    void quality_cmdSignSlot(QString str);  //质控品处理接收到的命令信号槽
};

#endif // CALIBRATIONWIDGET_H
