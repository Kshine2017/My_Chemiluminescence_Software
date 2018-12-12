/**
  *  @brief    未知品操作界面的患者信息输入栏
  *  @file     infowidget.h
  *  @author   谢飞
  *  @version  1.0(版本号)
  *  @date     2017-09-12
  */
#ifndef INFOWIDGET_H
#define INFOWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QScrollBar>
#include <QScrollArea>
#include <QComboBox>
#include "systemWidget/userManage/adddelupdsel.h"
class InfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InfoWidget(QWidget *parent = 0);

public:
    /**
     * @brief 患者信息窗口初始化
     */
    void InfoWidget_Init();
    /**
     * @brief 信号槽绑定函数初始化
     */
    void connectInit();

public:
    QLabel *PositionLab; /**<试剂船位置编号*/

public:
    //病人信息表
    QMap<int,QStringList> patientInfo;  //储存12个试剂船病人信息
    QPushButton *okBtn;     /**<确定按钮*/
private:

    QWidget *infoWidget; /**<显示窗口*/
    QScrollArea *scrArea;/**<滚动窗口*/

    QLabel *IDLab; /**<患者ID*/
    QLabel *nameLab;/**<患者姓名标签*/
    QLabel *sexLab;/**<患者性别标签*/
    QLabel *ageLab;/**<患者年龄标签*/
    QLabel *telphoneLab;/**<患者手机号码标签*/
    QLabel *administrativeLab;/**<科室标签*/


    QLineEdit *nameLEidt;/**<患者姓名输入框*/
    QLineEdit *IDEidt;   /**<ID输入框*/
    QComboBox *sexCom;/**<患者性别输入框*/
    QLineEdit *ageLEdit;/**<患者年龄输入框*/
    QLineEdit *telphoneLEdit;/**<患者手机号码输入框*/
    QComboBox *administrativeCBox;/**<科室输入框*/


    QGridLayout *infoLayout; /**<主布局器*/
    QHBoxLayout *HBoxLayout; /**<水平布局*/
    QHBoxLayout *okBtnLayout; /**<按钮和位号标签布局 */
    QVBoxLayout *mainLayout;

signals:
    void OKBtnPress(int num);
public slots:
    /**
     * @brief 确定按钮信号槽
     */
    void okBtnSlot();
    /**
     * @brief 接收来自UnkownWidget.h的信号槽
     * @param num
     */
    void selectRowSignSlot(int num);

    /**
     * @brief fresh_TestItemCBox
     * 刷新检测项目下拉列表选项
     */
    void fresh_TestItemCBox();
    /**
     * @brief fresh_TestItemCBox
     * 刷新科室下拉列表选项
     */
    void fresh_administrativeCBox();
};

#endif // INFOWIDGET_H
