/**
  *  @brief    未知品试剂仓状态
  *  @file     statuswidget.h
  *  @author   谢飞
  *  @version  1.0(版本号)
  *  @date     2017-09-12
  */
#ifndef STATUSWIDGET_H
#define STATUSWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
class StatusWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StatusWidget(QWidget *parent = 0);

public:
    /**
     * @brief 试剂船状态
     */
    enum STATUS{
        FREE = 0,   /**< 空闲 */
        AWAIT,      /**< 待机 */
        RUN,        /**< 运行 */
        FINISH,     /**< 结束 */
        ERR         /**< 异常 */
    };

    enum STATUS Reagent_status[12]; //12个试剂船状态
public:
    /**
     * @brief setReagent_Status:更改试剂仓状态
     * @param space_num：试剂仓号
     * @param data：当前状态(空闲，运行，结束，异常)
     */
    void setReagent_Status(int space_num,STATUS data);

private:
 /**
  * 每个位置槽的状态标签
  */
    QLabel *statusLab_1;
    QLabel *statusLab_2;
    QLabel *statusLab_3;
    QLabel *statusLab_4;
    QLabel *statusLab_5;
    QLabel *statusLab_6;
    QLabel *statusLab_7;
    QLabel *statusLab_8;
    QLabel *statusLab_9;
    QLabel *statusLab_10;
    QLabel *statusLab_11;
    QLabel *statusLab_12;
 /**
   *加急区和普通区位置槽标签
   */
    QLabel *urgentLabel;
    QLabel *commonLabel;
    QLabel *urgentNumLabel;
    QLabel *commonNumLabel;

/**
  * @brief 状态颜色标签
  */
   QLabel *statusLab;

   /**
     * @brief 布局管理器
     */
    QHBoxLayout *status1layout;
    QHBoxLayout *status2layout;
    QHBoxLayout *status3layout;
 //竖直布局
    QVBoxLayout *statusSub1Layout;
    QVBoxLayout *statusSub2Layout;
 //水平布局
    QHBoxLayout *mainlayout;

signals:

public slots:
};

#endif // STATUSWIDGET_H
