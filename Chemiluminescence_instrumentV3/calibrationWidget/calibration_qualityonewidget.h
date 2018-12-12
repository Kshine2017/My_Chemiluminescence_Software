/**
  *  @brief    质控数据结果界面
  *  @file     calibration_qualityonewidget.h
  *  @author   谢飞
  *  @version  1.0(版本号)
  *  @date     2017-10-20
  */
#ifndef CALIBRATION_QUALITYONEWIDGET_H
#define CALIBRATION_QUALITYONEWIDGET_H

#include <QWidget>
#include <QTableView>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QCheckBox>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QStringList>
#include "displaycruve.h"
class calibration_qualityOneWidget : public QWidget
{
    Q_OBJECT
public:
    explicit calibration_qualityOneWidget(QWidget *parent = 0);

public:
    QPushButton *returnBtn; /**< 返回按钮*/
    QPushButton* btn_save;
    QStandardItemModel *model;
private:
    void titleInit();
    void BtnInit();
    void checkWidgetInit();
    void tableviewInit();
    void displayWindowInit();
    void connectInit();
    bool insert_into_table_calibration_info(const QString& CATEGORY,
                                               const QString& PROJECT_NAME,
                                               const QString& REAGENT_TYPE,
                                               const QString& BAR_CODE,
                                               double STANDARD_CONCENTRATION,
                                               const QString& START_DATE,
                                               const QString& END_DATE,
                                               char STANDARD_FLAG,
                                               int PHOTON_VALUE,
                                               double CONCENTRATION,
                                               double VARIANCE_COEFFICENT,
                                               const QString& CREATOR_ID,
                                               const QString& CREATE_TIME,
                                               const QString& MODIFIER_ID,
                                               const QString& MODIFY_TIME,
                                               char DEL_FLAG);



public:
    QPushButton *questionBtn; //问号按钮
private:
    /**
     * @brief 标题头资源
     */
    QLabel *titleIconLab;   //头图标
    QLabel *titleTextLab; //标题文字

    QPushButton *disPlayBtn;  /**< 显示图形*/
    QPushButton *printBtn;    /**< 打印按钮*/
    QWidget *checkWidget;    /**< 多选框界面*/
    QWidget *disPictureWidget; /**< 显示曲线图界面*/
    QTableView *tableview;   /**< 视图界面*/
    QWidget *BtnWidget;     /**< 按钮界面窗口*/

    DisplayCruve *displayCruve; /**< 画曲线*/

private:
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

private:
    QVBoxLayout *checkLayout;
    QHBoxLayout *BtnLayout;
signals:
    void returnBtnSignal(int num);
public slots:
    void disPlayBtnSlot();
    void printBtnSlot();
    void saveBtnSLot();
    void returnBtnSlot();
};

#endif // CALIBRATION_QUALITYONEWIDGET_H
