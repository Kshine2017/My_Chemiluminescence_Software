/**
  *  @brief    试剂船编辑和工作编辑
  *  @file     reagentprowidget.h
  *  @author   谢飞
  *  @version  1.0(版本号)
  *  @date     2017-09-12
  */
#ifndef REAGENTPROWIDGET_H
#define REAGENTPROWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QGridLayout>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>
#include "standardProgrameWidget/standardprograme_actionpro.h"
#include "Serial_port/serialport.h"
#include "queue/queue.h"


#define REAGRNT_PRAGRAME_INQUIRY_TIME 2000 //试剂船全速运行界面询问是否空闲超时时间间隔
class reagentProWidget : public QWidget
{
    Q_OBJECT
public:
    explicit reagentProWidget(QWidget *parent = 0);
    enum STANDARD_PRO_ModeState {    //自检界面下设备状态枚举
        PRO_STEP_RUN = 0,
        PRO_FULL_START,
        PRO_STOP,
        PRO_PAUSE,
        PRO_CONTINUE
    };
    enum STANDARD_PRO_ModeState standardPrograme_mode ; //试剂船全速运行设备状态
private:
//    /**
//     * @brief 试剂船项目名称表格初始化
//     */
//    void tableProjectWidgetInit();
    /**
     * @brief 试剂船工作进度表格初始化
     */
    void tableWorkWidgetInit();
    /**
     * @brief 工具栏初始化
     */
    void workToolBarInit();
    /**
     * @brief 信号槽绑定初始化
     */
    void connectInit();
public:
//    /**
//     * @brief 试剂船信息是否有为空
//     * @return 空true ,非空false
//     */
//    bool ProjectInfoIsEmpty();


public:
    /**
     * @brief 试剂船动作名称编辑项目表格
     */
   // QTableWidget *tableProjectWidget;
    standardPrograme_actionPro *actionProTabelView;

    //工作队列
    Queue* WorkQueue;  //工作队列
    QTableWidget *tableWorkWidget;
private:

    QLabel *titleLab;   /**< 试剂船编辑标签 */
    /**
     * @brief 试剂船工作进度表格
     */
    //QTableWidget *tableWorkWidget;
    QProgressBar *WorkProgBar;  /**< 试剂船工作进度条 */
    /**
     * @brief 试剂船工具条
     */
    QWidget *workToolWidget;
    QPushButton *startBtn;/**< 开始 */
    QPushButton *pauseContinuBtn;/**< 暂停/继续 */
    QPushButton *stopBtn;/**< 停止 */
    QPushButton *saveBtn;/**< 保存 */
    QPushButton *openBtn; /**< 打开*/
    QPushButton *importBtn;/**< 导入*/
    QPushButton *exportBtn;/**< 导出*/
    QHBoxLayout *toolLayout;
    /**
     * @brief 试剂船编辑方案
     */


    QTimer *InquiryTimer; //工作队列询问定时器

    bool pauseContinuBtnState; //暂停/继续按钮当前状态


signals:
     void SaveBtnPress_Sign();
     void OpenBtnSignal();      //打开按钮信号，需要将信号发送到试剂船编辑主界面
     void startBtnSignal();   //启动全速运行按钮信号，需要将信号发送到试剂船编辑主界面
public slots:
    void saveBtnSlot();
    void openBtnSlot();
    void startBtnSlot();
    void pauseContinuBtnSlot();
    void stopBtnSlot();
    void importBtnSlot();
    void exportBtnSlot();

    void reagentpro_InquiryTimerOverSlot();  //工作队列询问是否空闲超时定时器

};

#endif // REAGENTPROWIDGET_H
