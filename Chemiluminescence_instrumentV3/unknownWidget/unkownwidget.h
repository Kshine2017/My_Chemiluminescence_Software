/**
  *  @brief    未知品操作界面
  *  @file     unkownwidget.h
  *  @author   谢飞
  *  @version  1.0(版本号)
  *  @date     2017-09-12
  */
#ifndef UNKOWNWIDGET_H
#define UNKOWNWIDGET_H
#include "QLabel"
#include <QWidget>
#include <QStandardItemModel>
#include <QTableView>
#include <QGridLayout>
#include <QHeaderView>
#include <QItemSelectionModel>
#include "unknownWidget/infowidget.h"
#include "unknownWidget/statuswidget.h"
#include "unknownWidget/check_namedelegate.h"
#include "unknownWidget/serial_numdelegate.h"
#include "unknownWidget/progress_bardelegate.h"
#include "unknownWidget/start_pushbuttondelegate.h"
#include "unknownWidget/okbtn_delegate.h"
#include "Serial_port/serialport.h"
#include "queue/queue.h"

#define UNKNOW_INQUIRY_TIME 2000 //未知品界面下询问当前设备是否空闲超时时间间隔
class UnkownWidget : public QWidget
{
    Q_OBJECT
public:
    explicit UnkownWidget(QWidget *parent = 0);
public:
    enum BtnState{  //按钮状态
      NO_CLICKED,
      CLICKED,
    };

    QLabel* label_backpic;

private:
    /**
     * @brief 窗口标题初始化
     */
    void titleInit();

    /**
     * @brief 模型视图初始化
     */
    void tableModel_Init();
    /**
     * @brief 信号和槽绑定函数初始化
     */

    /**
     * @brief 设置space_num行试剂船信息内容
     * @param space_num 行
     * @param data 数据
     * @param length 数据长度
     */
    void setModel_ReagentInfo(int space_num,QByteArray &data,int length);
    /**
     * @brief 试剂船拔出处理函数
     * @param postion
     */
    QString reagentPopup_CMDHandle(int postion);

    /**
     * @brief 试剂船进度处理函数
     * @param postion
     */
    void returnProgress_InfoHandle(QByteArray &data);
    /**
     * @brief 试剂船错误处理函数
     * @param err
     */
    void returnRegent_ErrHandle(QByteArray &err);
    /**
     * @brief 测试结果处理函数
     * @param data
     */
    void testResultHandle(QByteArray &data);
    /**
     * @brief 信号槽绑定
     */
    void connectInit();
    /**
     * @brief 得到运行步骤数据
     * @param 条码
     * @return 当前试剂运行数据
     */
    QString getRunInfo(QString & serical);

public:
    //串口对象
//    serialPort *myserial_port;
    QPushButton *questionBtn;  /**< 问号按钮图标 */
private:
    QVBoxLayout *mainlayout;    //主布局器
    QHBoxLayout *infolayout;    //状态和信息布局管理器
//窗口标签
    QLabel *WindowTile;
//显示状态
    QLabel *statusTitleLab;     //试剂船信息头
    QLabel *patientTitleLab;   //患者信息头



//试剂船状态显示窗口
    StatusWidget *statusWidget; //试剂仓状态显示窗口
    InfoWidget *infoWidget;   //信息录入窗口
    QWidget * underWidget;   //界面下部显示窗口( 12个信息槽表 )

//模型视图
    QStandardItemModel *model;
    QTableView *tableView;
    QItemSelectionModel *selectModel; //选择模型
//代理
    check_nameDelegate *checkNameDelegate;
    serial_numDelegate *serialNumDelegate;
    progress_BarDelegate *progessBarDelegate;
    start_PushButtonDelegate *startPushButtonDelegate;
    okbtn_Delegate * okbtnDelegate;

//按钮状态
    BtnState OkBtnState[12]; //确定按钮状态
    BtnState StartBtnState[12]; //开始按钮状态
    QMap<int ,QString > *RunData; //储存插入试剂船运行数据 
    QMap<int,QString> *SerialNumber; //储存各试剂船序列号，第二位到第七位条码用于查询标准曲线
//工作队列
    Queue* WorkQueue;  //工作队列
    QTimer *queryTimer; //工作队列询问定时器

signals:
    void selectRowSign(int num);

public slots:
    void OkBtnSlot(const QModelIndex&);
    void startBtnSlot(const QModelIndex&);
    void selectionIndexesSlot(QItemSelection newSelect, QItemSelection delSelect);
    void infoWidgetOkBtnSlot(int num);

    void unkonow_cmdSignSlot(QString str); //位置品处理接收到的命令

    void Unknow_queryTimerOverSlot();  //工作队列询问是否空闲超时定时器


};

#endif // UNKOWNWIDGET_H
