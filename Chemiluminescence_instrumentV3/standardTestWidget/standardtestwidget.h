/**
  *  @brief    标准品测试主类
  *  @file     standardtestWidget.h
  *  @author   谢飞
  *  @version  1.0(版本号)
  *  @date     2017-09-12
  */
#ifndef STANDARDTESTWIDGET_H
#define STANDARDTESTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QStackedWidget>
#include "standardTestWidget/standardtest_onewidget.h"
#include "standardTestWidget/standardtest_twowidget.h"
#include "Serial_port/serialport.h"

class standardTestWidget : public QWidget
{
    Q_OBJECT
public:
    explicit standardTestWidget(QWidget *parent = 0);
    /**
     * @brief 试剂船拔出处理函数
     * @param postion ：试剂船位置
     * @param num  : 1校准品，2质控品
     */
    void reagentPopup_CMDHandle(int postion,int num);
    /**
     * @brief 试剂船错误处理函数
     * @param err
     */
    void returnRegent_ErrHandle(QByteArray &err);
    /**
     * @brief 试剂船返回值数据处理
     * @param data
     * @param interf
     */
    void returnProgress_InfoHandle(QByteArray &data,int interf);
    /**
     * @brief 设置space_num行试剂船信息内容
     * @param space_num 行
     * @param data 数据
     * @param length 数据长度
     */
    void setModel_ReagentInfo(int space_num, QByteArray &data, int length);

    /**
     * @brief 测试结果处理函数
     * @param data
     */
    void testResultHandle(QByteArray &data);
private:
    void WidgetInit();
    void connectInit();
public:
    QStackedWidget *stack; /**< 界面堆栈 */
public:
    standardTest_OneWidget *oneWidget; /**< 第一个窗口界面 */
    standardTest_TwoWidget *twoWidget; /**< 第二个窗口界面 */

signals:

public slots:
    /**
         * @brief 第一界面下一步按钮
         */
        void twoReturnBtnSlot();
        /**
         * @brief 保存标准品数据槽
         */
        void SaveBtnPressSlot();
        /**
         * @brief 下一步或者当前工作完成之后发送的信号的槽
         */
        void nextBtnPressSlot();

        void standardTest_cmdSignSlot(QString str); //标准品处理接收到的命令信号槽


};

#endif // STANDARDTESTWIDGET_H
