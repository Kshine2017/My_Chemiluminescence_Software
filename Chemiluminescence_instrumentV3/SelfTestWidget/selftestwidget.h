#ifndef SELFTESTWIDGET_H
#define SELFTESTWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QComboBox>
#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <SelfTestWidget/selfteststep.h>
#include <QWidget>
#include <SelfTestWidget/myheaderview.h>
#include "queue/queue.h"
#include "QRoundProgressBar.h"

#define INQUIRY_TIME 2000   //询问是否空闲间隔时间
class selfTestWidget : public QWidget
{
    Q_OBJECT

public:
    enum SelfModeState {    //自检界面下设备状态枚举
        SELF_STEP_RUN = 0,
        SELF_FULL_START,
        SELF_STOP,
        SELF_PAUSE,
        SELF_CONTINUE
    };

    enum SelfModeState self_state ;  //自检界面下自检状态

    int Test_counter;
    selfTestWidget(QWidget *parent = 0);
    int stateFree = 2; //下位机空闲状态 2：未应答 ，1：不空闲 ，0：空闲

    QVBoxLayout *mainLayout; //主界面

    QLabel *label_title; //放背景

    QLabel* label_gif;
    QLabel* label_tip;
    QRoundProgressBar* RoundPB;



    QWidget *widget;//放背景
    QLabel *label_titleName; //放文字

    QPushButton *questionBtn; //问好按钮

    QTextEdit *textEdit_content; //显示自检进度--编辑框
    QLabel *lab_textEdit_bg;

    QPushButton *btn_start;     //启动按钮
    QPushButton *btn_pause;     //暂停、继续按钮
    QPushButton *btn_stop;      //停止按钮
    QPushButton *btn_reset;      //报警复位按钮

    QHBoxLayout *layout_btn;//放置按钮布局

    QWidget *widget_content; //放置内容背景
    QLabel *label_contentName;  //放置--具体步骤

    QTableWidget *tableWidget; //表格窗口

    SelfTestStep *step1;//自检步骤1
    SelfTestStep *step2;//自检步骤2
    SelfTestStep *step3;//自检步骤3
    SelfTestStep *step4;//自检步骤4


    void init();

    void SetStep(SelfTestStep *step);
    QString getStepData(SelfTestStep * step);

    void sendCMDToPC();

private:
    bool pauseBtnState; //记录当前暂停和继续按钮状态，是暂停还是继续
    Queue* WorkQueue;  //工作队列
    QTimer *InquiryTimer; //定时器
private:
    void connectInit(void);
signals:
public slots:
    void getStepDatas();
    void setAllCheckStatus(bool); //全选、全不选
    void runSignalStepSlot(int num, int count); //单选运行按钮的槽
    void InquiryTimerOverSlot();  //超时定时器
    void self_Test_CMDSlot(QString str);  //处理自检界面命令信号槽
    void startBtnSlot();   //启动按钮信号槽
    void stopBtnSlot();    //停止按钮信号槽
    void pauseBtnSlot();    //暂停继续按钮信号槽
    void resetBtnSlot();     //报警复位按钮信号槽
};


#endif // SELFTESTWIDGET_H
