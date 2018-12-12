/**
  *  @brief    试剂船动作编辑界面
  *  @file     standardprograme_actionpro.h
  *  @author   谢飞
  *  @version  1.0(版本号)
  *  @date     2017-10-17
  */
#ifndef STANDARDPROGRAME_ACTIONPRO_H
#define STANDARDPROGRAME_ACTIONPRO_H

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QHeaderView>
#include "standardProgrameWidget/standardprograme_addbtndelegate.h"
#include "standardProgrameWidget/standardprograme_minusdelegate.h"
#include "standardProgrameWidget/standardprograme_actioncheckdelegate.h"
#include "standardProgrameWidget/standardprograme_startpostiondelegate.h"
#include "standardProgrameWidget/standardprograme_endpostiondelegate.h"
#include "standardProgrameWidget/standardprograme_beforecountdelegate.h"
#include "standardProgrameWidget/standardprograme_aftercountdelegate.h"
#include "standardProgrameWidget/standardpragrame_runbtndelegate.h"
#include <QScrollBar>
#include "Serial_port/serialport.h"
#include "standardProgrameWidget/standardpragrame_checkboxdelegate.h"
#define ACTION_TABLE_WIDTH 1652 //动作编辑窗口宽度
#define ACTION_TABLE_HIGHT 460  //动作编辑窗口高度

#define STEP_NUM 19  //最多步骤数
class standardPrograme_actionPro : public QWidget
{
    Q_OBJECT
public:
    explicit standardPrograme_actionPro(QWidget *parent = 0);

public:
    /**
     * @brief 视图窗口初始化
     */
    void tabelViewInit();
    /**
     * @brief 设置
     */
    void setActionTabel_delegate();
    /**
     * @brief 信号槽连接函数
     */
    void connectInit();

    /**
     * @brief 获取单步运行命令数据
     * @param 第几行按钮
     * @return 命令字符串
     */
    QString getStepData(int current_row);
public:
    QTableView *tableView;
    QStandardItemModel *model;

private:  //代理类
//    standardPrograme_addBtnDelegate *addDelegate; //添加按钮代理
//    standardprograme_minusDelegate *minusDelegate; //删除按钮代理
//    standardprograme_actionCheckDelegate *actionCheckDelegate; //动作选择按钮
    standardpragrame_checkBoxDelegate *checkBoxDelegate;  //动作是否选择代理
    standardPrograme_startPostionDelegate *startPostionDelegate; //开始位置代理
    standardPrograme_endPostionDelegate *endPostionDelegate; //目标位置
    standardPrograme_afterCountDelegate *afterCountDelegate;  //后续混匀次数
    standardPrograme_beforeCountDelegate* beforeCountDelegate; //前序混匀次数
    standardpragrame_runBtnDelegate *stepRunBtnDelegate;   //单步运行按钮代理
signals:
    void stepRunBtnSignal(int step);
public slots:
    /**
     * @brief 增加一个步骤
     */
    void addActionStep(const QModelIndex&index);
    /**
     * @brief 删除一个步骤
     */
    void minusActionStep(const QModelIndex&index);
    /**
     * @brief 单步运行按钮
     * @param index
     */
    void stepRunBtnSlot(const QModelIndex &index);

};

#endif // STANDARDPROGRAME_ACTIONPRO_H
