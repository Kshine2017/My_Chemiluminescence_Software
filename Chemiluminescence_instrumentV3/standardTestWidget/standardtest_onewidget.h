#ifndef STANDARDTEXT_ONEWIDGET_H
#define STANDARDTEXT_ONEWIDGET_H

#include <QWidget>
#include "QMessgeBox/mymessgebox.h"
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QStandardItemModel>
#include <QTableView>
#include <QPalette>
#include <QTableWidget>
#include <QHeaderView>
#include "standardTestWidget/standtest_progressdelegate.h"
#include "standardTestWidget/standardtest_okbtndelegate.h"
#include "unknownWidget/statuswidget.h"
#include "queue/queue.h"
#include "Serial_port/serialport.h"

#define STANDARD_TEST_QUERY_FREE_TIME 2000   //校准品查询是否空闲定时器定时时间
class standardTest_OneWidget : public QWidget
{
    Q_OBJECT
public:
    explicit standardTest_OneWidget(QWidget *parent = 0);

private:
    /**
     * @brief 初始化
     */
    void title_init();
    /**
     * @brief 操作表格信息初始化
     */
    void tableWidget_init();

    /**
     * @brief 模型视图
     */
    void tableView_init();
    /**
     * @brief 信号和槽绑定
     */
    void connnect_init();
public:
    /**
     * @brief 得到运行步骤数据
     * @param 条码
     * @return 当前试剂运行数据
     */
    QString getRunInfo(QString &serical);

public:
    QPushButton *nextBtn;/**< 下一步动作*/
    QPushButton *questionBtn;  /**< 问号按钮图标 */
    QPushButton *returnBtn;/**< 返回动作*/
    QTableWidget *tableWidget;/**< 项目信息 */
    //模型视图
    QStandardItemModel *model;/**< 模型 */
    QTableView *tableView;/**< 视图 */
    //工作队列
    Queue*  WorkQueue;  //工作队列
    QMap<int ,QString > *RunData; //储存插入试剂船运行数据
    QMap<int,QString> *SerialNumber; //储存各试剂船序列号，第二位到第七位条码用于查询标准曲线

    StatusWidget *statusWidget; //试剂仓状态显示窗口
  //模型视图代理
    standardText_okBtnDelegate *okBtnDelegate;//ok按钮代理
private:
    QLabel *titleLabel; /**< 窗口标题顶栏 */
    QLabel *title_name; /**< 窗口标题顶栏图标 */

private:
    QPushButton *finsh_placeBtn;/**< 结束放置动作 */

private:
  //模型视图代理
    standTest_ProgressDelegate *ProgressDelegate;

private:
    QTimer *queryTimer; //工作队列询问定时器
private:
    QVBoxLayout *mainLayout;/**< 主布局器 */
    QHBoxLayout *BtnLayout; /**< 按钮布局器*/

signals:
    void nextBtnPressSign();   //下一步或者当前测试都确认完成之后发生的信号
public slots:
    /**
     * @brief 三个控制按键信号槽
     */
    void returnBtnSlot();
    void finsh_placeBtnSlot();
    void nextBtnSlot();
    /**
     * @brief 确定按钮信号槽
     */
    void okBtnDelegateSlot(const QModelIndex &index);
    void queryTimerOverSlot();  //工作队列询问是否空闲超时定时器

};

#endif // STANDARDTEXT_ONEWIDGET_H
