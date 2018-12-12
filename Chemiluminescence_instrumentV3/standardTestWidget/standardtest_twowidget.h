/**
  *  @brief    标准品测试下一步第一个界面
  *  @file     standardtestonewidget.h
  *  @author   谢飞
  *  @version  1.0(版本号)
  *  @date     2017-10-12
  */
#ifndef STANDARDTEST_TWOWIDGET_H
#define STANDARDTEST_TWOWIDGET_H

#include <QWidget>
#include <QTableView>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QStandardItemModel>
#include <QCheckBox>


class standardTest_TwoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit standardTest_TwoWidget(QWidget *parent = 0);


public:
    QPushButton *returnBtn;/**< 返回按钮*/
    QPushButton* btn_save;
    QPushButton *questionBtn;  /**< 问号按钮图标 */
    //模型视图
    QStandardItemModel *model;/**< 模型 */
private:
    QTableView *tableView;

private:
    /**
     * @brief 初始化
     */
    void title_init();
    /**
     * @brief 模型视图
     */
    void tableView_init();
    void checkWidgetInit();

private:
    QLabel *titleLabel; /**< 窗口标题顶栏 */
    QLabel *title_name; /**< 窗口标题顶栏图标 */

    QWidget *checkWidget;    /**< 多选框界面*/
    QWidget *BtnWidget;     /**< 按钮窗口*/
private:
    QPushButton *SureBtn;/**< 确定按钮 */

private:
    QHBoxLayout *BtnLayout; /**< 按钮布局器*/
    QVBoxLayout *checkLayout;


public:
    QCheckBox *checkBox1;
    QCheckBox *checkBox2;
    QCheckBox *checkBox3;
    QCheckBox *checkBox4;
    QCheckBox *checkBox5;
    QCheckBox *checkBox6;
    QCheckBox *checkBox7;
    QCheckBox *checkBox8;
    QCheckBox *checkBox9;
    QCheckBox *checkBox10;
    QCheckBox *checkBox11;
    QCheckBox *checkBox12;
signals:
    void SaveBtnPressSign();
public slots:
    void SureBtnSlot();
    void saveBtnSlot();
};

#endif // STANDARDTESTONEWIDGET_H
