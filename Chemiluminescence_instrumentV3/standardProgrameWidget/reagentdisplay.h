/**
  *  @brief    试剂船模型和各仓位介绍
  *  @file     reagentdisplay.h
  *  @author   谢飞
  *  @version  1.0(版本号)
  *  @date     2017-09-12
  */
#ifndef REAGENTDISPLAY_H
#define REAGENTDISPLAY_H

#include <QWidget>
#include <QTableWidget>
#include <QLabel>
#include <QPalette>
#include <QGridLayout>
#include <QHeaderView>
#include "workprogressarea.h"
class reagentDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit reagentDisplay(QWidget *parent = 0);

public:
    void TableInit();/**< tab窗口初始化 */
    WorkProgressArea* workPA;
private:
    /**
     * @brief 试剂船模型图片和介绍表
     */
    QLabel *reagentLab;/**< 试剂船模型视图标签 */
    QTableWidget *reagentTab;/**< 试剂船模型表格介绍 */


//布局
    QHBoxLayout *mainlayout; /**< 水平布局 */
    QLabel* label_pic;
signals:

public slots:
};

#endif // REAGENTDISPLAY_H
