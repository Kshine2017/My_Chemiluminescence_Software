#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QToolButton>
#include <QSplitter>
#include <QLayout>
#include <QPushButton>
#include <QDockWidget>
#include <QStatusBar>
#include <QLabel>
#include <QTime>
#include <QTimer>
#include "calibrationWidget/calibrationwidget.h"
#include "queryWidget/querywidget.h"
#include "SelfTestWidget/selftestwidget.h"
#include "standardBightWidget/standardbightwidget.h"
#include "standardProgrameWidget/standardpragramewidget.h"
#include "standardTestWidget/standardtestwidget.h"
#include "unknownWidget/unkownwidget.h"
#include "systemWidget/systemwidget.h"
#include "manul_book/manul_bookwidget.h"
#include "QMessgeBox/mycheckmessagebox.h"
#include "Serial_port/serialport.h"
#include "menu/temperatureplot.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public:
    /**
     * @brief 更新当前温度值
     * @param 下位机上传的温度值
     */
    void UpdateTemperatureValue(unsigned short int temp);
private:
    void createMenus();
    /**
     * @brief 当前系统时间初始化
     */
    void setTimer();

    /**
     * @brief 信号槽绑定初始化函数
     */
    void connectInit();
    /**
     * @brief 显示温度和温度曲线界面
     */
    void disTemperatureWidgetInit();
private:
  //主控菜单界面按钮
    QPushButton *CancelBtn; //退出主界面
    QPushButton *UnknownBtn; //未知品测试
    QPushButton *CalibrationBtn; //校准/质控品
    QPushButton *SelfTestBtn; //自检
    QPushButton *QueryBtn;    //查询
    QPushButton *SystemBtn;  //系统
    QPushButton *StandardPragrameBtn; //标准品试剂船编辑
    QPushButton *StandardTestBtn;     //标准品测试
    QPushButton *StandardBightBtn;   //标准曲线生成


//    serialPort *myserial_Port;

 //工具栏横线
    QLabel *toolbarLab1;
    QLabel *toolbarLab2;
    QLabel *toolbarLab3;
    QLabel *toolbarLab4;
    QLabel *toolbarLab5;
    QLabel *toolbarLab6;
    QLabel *toolbarLab7;
    QLabel *toolbarLab8;
    QLabel *toolbarLab9;

//温度显示曲线界面
    //QWidget *disTemperatureWidget; //显示温度和温度曲线界面
    TemperaturePlot *disTemperatureWidget;


    QLabel *temperatureIcon; //温度图标
    QLabel *temperatureName; //温度名称
    QLabel *temperatureNum; //显示当前温度数值
    QLabel *CycleIcon;//温度循环图标
    QLabel *SystemStateLabel; //系统状态

//窗口
    QDockWidget * menuDockWidget;
    QWidget *menuWidget;//停靠窗口里面的窗口

    UnkownWidget * unknow_Widget;
    calibrationWidget *calibration_Widget;
    selfTestWidget *selfTest_Widget;
    queryWidget *query_Widget;
    standardBightWidget *standardBight_Widget;
    standardPragrameWidget *standardPragrame_Widget;
    standardTestWidget *standardTest_Widget;
    systemWidget *system_Widget;
    manul_bookWidget *manul_Widget;

//状态栏信息
    QLabel *statu1Label;
    QLabel *statu2Label;
    QLabel *statupix1Label;
    QLabel *statupix2Label;
//状态栏显示当前时间
    QLabel *showTimeLabel;
    QTimer *timer;           //时间计时器
    bool showDot;           //用于是否显示":"

//布局管理器
    QVBoxLayout *menuLayout; //菜单布局器
signals:

public slots:
//创建各功能界面槽函数
    void create_UnknownWindow();
    void create_CalibrationWindow();
    void create_SelfTestWindow();
    void create_QueryWindow();
    void create_SystemWindow();
    void create_StandardPragrameWindow();
    void create_StandardTestWindow();
    void create_StandardBightWindow();
    void CancelBtnSlot();
    void other_cmdSignSlot(const QString &str); //其它命令处理函数

    //显示时间信号槽
    void showTime();
    /**
     * @brief 问号按钮信号槽
     */
    void questionBtnSlot();
    /**
     * @brief 返回按钮信号操
     */
    void returnBtnSlot();
};

#endif // MAINWINDOW_H
