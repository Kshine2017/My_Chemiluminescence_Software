#ifndef CALIBRATION_TWOWIDGET_H
#define CALIBRATION_TWOWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include "unknownWidget/statuswidget.h"
#include <QStandardItemModel>
#include <QTableView>
#include <QTableWidget>
#include "calibrationWidget/calibration_progressbardelegate.h"
#include "calibrationWidget/calibration_qcomboxdelegate.h"
#include "calibrationWidget/calibration_okbtndelegate.h"
#include "queue/queue.h"
#include "Serial_port/serialport.h"
#include "standardBightWidget/qcustomplot.h"
#include "data/util.h"

#define CALIBRATION_QUERY_FREE_TIME 2000   //质控品查询是否空闲定时器定时时间

class calibration_twoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit calibration_twoWidget(QWidget *parent = 0);
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

    QString getRunInfo(QString &serical);

public:
    QPushButton *returnBtn;      //返回按钮
    QPushButton *questionBtn; //问号按钮

    //工作队列
    Queue* queue_WorkQueue;  //工作队列

    StatusWidget *statusWidget; //试剂仓状态显示窗口

    QMap<int ,QString > *RunData; //储存插入试剂船运行数据
    QMap<int,QString> *SerialNumber; //储存各试剂船序列号，第二位到第七位条码用于查询标准曲线
    //模型视图
    QStandardItemModel *model;
    QTableView *tableView;
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



    calibration_ProgressBarDelegate * progressBarDelegate;
    calibration_QComboxDelegate *comBoxDelegate;
private:
    QVBoxLayout *mainLayout;/**< 主布局器 */
    QHBoxLayout *btnLayout; /**< 按钮水平布局器*/
private:


    QTimer *queryTimer; //工作队列询问定时器

signals:
    void measurementFinshSignal(int num); //测量完成信号
public slots:
    void finishPlaceBtnSlot();
    void returnBtnSlot();
    void nextBtnSlot();
    void questionBtnSlot();
    void Display_btnSlot(const QModelIndex&);
    void queue_queryTimerOverSlot();  //工作队列询问是否空闲超时定时器
};

#endif // CALIBRATION_TWOWIDGET_H
