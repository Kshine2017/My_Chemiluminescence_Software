/**
  *  @brief    试剂船编辑窗口
  *  @file     standardpragramewidget.h
  *  @author   谢飞
  *  @version  1.0(版本号)
  *  @date     2017-09-12
  */
#ifndef STANDARDPRAGRAMEWIDGET_H
#define STANDARDPRAGRAMEWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include "standardProgrameWidget/reagentprowidget.h"
#include "standardProgrameWidget/reagentdisplay.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QDateEdit>
#include "Serial_port/serialport.h"



class standardPragrameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit standardPragrameWidget(QWidget *parent = 0);

public:
    /**
     * @brief 获取当前船位置位置的数据
     * @param 试剂船位置信息
     * @return 试剂船当前位置
     */
    QString getX_Y_Value(unsigned char postion);
    /**
     * @brief 获取当前船位置位置的容量
     * @param 试剂船位置信息
     * @return 试剂船当前位置的容量
     */
    QString getC_Value(unsigned char postion);
    /**
     * @brief 获取当前试剂船运动全部实际发送数据
     * @return 当前试剂船项目试剂数据字符串
     */
    QString getProAllInfo();

    bool tableWidgetIsEmpty(); //试剂内容是否为空
    bool ProjectInfoIsEmpty();
    bool TabelView_CheckBoxnum_IsLessThanNumber(int num);//勾选少于
private:
    /**
     * @brief 标题初始化
     */
    void titleInit();
    /**
     * @brief 试剂船编辑表格
     */
    void tableInit();
    /**
     * @brief connectInit
     */
    void connectInit();
    /**
     * @brief 设置reagentdisplay.h里面的workPA信息
     * @param startTime:开始时间
     * @param endTime:结束时间
     * @param stage:当前阶段
     * @param progressValue:进度值
     */
    void setWorkPaINFO(const QString& startTime,const QString& endTime, const QString& stage, int progressValue);
    /**
     * @brief 全速运行时当前进度和时间返回码
     * @param 命令字符串
     */
    void allRunProgressHandle(QByteArray &data);
    /**
     * @brief 单步运行时间返回码
     * @param 命令字符串
     */
    void stepRunTimeHandle(QByteArray &data);

public:
    QPushButton *questionBtn; //问号按钮

    QDateEdit *dateEdit_start_time;
    QDateEdit *dateEdit_end_time;
    QComboBox* cmbx_type;//品类数值
    QComboBox* cmbx_fileName;//项目名称
    QComboBox* cmbx_fileSN;//文件名简写short name //项目试剂
    QComboBox* cmbx_numberPH;//批号PiHao
    QComboBox* cmbx_POV;//有效期 period of validity
    QTableWidgetItem *itemName13;
    QTableWidgetItem *itemName15;//这个在槽中被多次使用。最好只创建一次，所以放到类的成员中

private:
    /**
     * @brief 标题头资源
     */
    QLabel *titleIconLab;   //头图标
    QLabel *titleTextLab; //标题文字

    /**
     * @brief试剂船编辑显示
     */
    reagentDisplay *reagentdisplay;
    /**
     * @brief 试剂船编辑表格
     */
     QTableWidget *tableWidget;

    //新移入的表格--------------------------------
    QTableWidget *tableProjectWidget; //项目信息

    void tableProjectWidgetInit();


    /**
     * @brief 试剂船项目显示编辑视图
     */
    reagentProWidget *reagentPromWidget;





signals:
    void signal_refreshNumber();//刷新条码
public slots:
    void StartBtnSignalSlot(); //试剂船全速运行时信号槽，用于发送数据去下位机
    void SaveBtnPressSlot();  //保存按钮按下信号槽
    void OpenBtnSlot();     //打开按钮信号槽
    void DataToWindow(QString& ACTION_CODE);
    void reagent_programe_cmdSignSlot(QString str); //全速运行试剂船编辑命令信号槽

    void stepRunBtnSignalSlot(int step);  //单步运行按钮

    void slot_RefreshComoBox_FileName_And_SN(QString text);//刷新项目名称和试剂类别
    void slot_RefreshComoBox__SN(QString text);

    void slot_autoGenerateNumer();//自动生成条码
    void slot_send_signal_autoGenerateNumer(QDate date);//转发信号，用于告知生成条码
    void slot_send_signal_autoGenerateNumer(QString text);//转发信号，用于告知生成条码
};

#endif // STANDARDPRAGRAMEWIDGET_H
