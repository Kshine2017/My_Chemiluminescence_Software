/**
  *  @brief    自定义校准和质控
  *  @file     Calibration.h
  *  @author   谢飞
  *  @version  1.0(版本号)
  *  @date     2017-10-10
  */
#ifndef CALIBRATION_ONEWIDGET_H
#define CALIBRATION_ONEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include "unknownWidget/statuswidget.h"
#include <QStandardItemModel>
#include <QTableView>
#include "calibrationWidget/calibration_progressbardelegate.h"
#include "calibrationWidget/calibration_qcomboxdelegate.h"
#include "calibrationWidget/calibration_okbtndelegate.h"
#include "queue/queue.h"
#include "Serial_port/serialport.h"
#include "standardBightWidget/qcustomplot.h"

#define CALIBRATION_QUERY_FREE_TIME 2000   //校准品查询是否空闲定时器定时时间

class calibration_oneWidget : public QWidget
{
    Q_OBJECT
public:
    explicit calibration_oneWidget(QWidget *parent = 0);

public:
    /**
     * @brief 标题初始化
     */
    void titleInit();
    /**
     * @brief 模型视图初始化
     */
    void tableViewInit();
    /**
     * @brief 操作按钮初始化
     */
    void PushBtnInit();
    /**
     * @brief QCustomplotInit
     * 画图板初始化
     */
    void QCustomplotInit();

    /**
     * @brief 得到运行步骤数据
     * @param 条码
     * @return 当前试剂运行数据
     */
    QString getRunInfo(QString &serical);
public:
    QPushButton *returnBtn;      //返回按钮
    QPushButton *questionBtn; //问号按钮
    //工作队列
    Queue*  Calibration_WorkQueue;  //工作队列

    StatusWidget *statusWidget; //试剂仓状态显示窗口

    //模型视图
    QStandardItemModel *model;
    QTableView *tableView;

    QMap<int ,QString > *RunData; //储存插入试剂船运行数据
    QMap<int,QString> *SerialNumber; //储存各试剂船序列号，第二位到第七位条码用于查询标准曲线
     //视图代理
    calibration_okBtnDelegate * okBtn;
private:
    /**
     * @brief 标题头资源
     */
    QLabel *titleIconLab;   //头图标
    QLabel *titleTextLab; //标题文字
    QPushButton *finishPlaceBtn; //结束放置按钮
    QPushButton *nextBtn; //下一步按钮

    QCustomPlot *customPlot; //画图板
    //视图代理
    calibration_ProgressBarDelegate * progressBarDelegate;
    calibration_QComboxDelegate *comBoxDelegate;


private:
    QVBoxLayout *mainLayout;/**< 主布局器 */
    QHBoxLayout *btnLayout; /**< 按钮水平布局器*/
private:

    QTimer *queryTimer; //工作队列询问定时器




signals:
    void measurementFinshSignal(int num); //完成界面跳转信号
public slots:
    void finishPlaceBtnSlot();
    void nextBtnSlot();
    void Display_btnSlot(const QModelIndex&);
    void calibration_queryTimerOverSlot();  //工作队列询问是否空闲超时定时器

};

#endif // CALIBRATION_ONEWIDGET_H
