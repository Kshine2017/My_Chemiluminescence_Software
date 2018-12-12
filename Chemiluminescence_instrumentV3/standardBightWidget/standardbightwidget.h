#ifndef STANDARDBIGHTWIDGET_H
#define STANDARDBIGHTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include "standardBightWidget/standbight_controlwidget.h"
#include "standardBightWidget/standardbight_drawewidget.h"
#include "cruvegeneration.h"
class standardBightWidget : public QWidget
{
    Q_OBJECT
public:
    static bool CurveDisplayFlag;
public:
    explicit standardBightWidget(QWidget *parent = 0);

private:
    /**
     * @brief 标题初始化
     */
    void titleInit();
    /**
     * @brief 按钮初始化
     */
    void BtnInit();
    /**
     * @brief 绑定信号和槽初始化
     */
    void connectInit();
    /**
     * @brief 控制显示曲线
     */
    void controlDisCurve();
    /**
     * @brief 根据单选框设置显示函数和R^2值;
     */
    void setFuctionString();

public:
    static bool DisCruventFlag;  //曲线是否已经生成
    QPushButton *questionBtn; //问号按钮
    QPushButton *quitBtn; //退出按钮
private:
    /**
     * @brief 标题头资源
     */
    QLabel *titleIconLab;   //头图标
    QLabel *titleTextLab; //标题文字


private:
    /**
     * @brief 几个按钮
     */
    QPushButton *saveBtn; //保存按钮
    /**
     * @brief 界面显示
     */
    standBight_controlWidget *controlWidget;  //控制界面
    standardBight_draweWidget *DrawWidget;   //绘图界面
private:
    QHBoxLayout *btnLayout; //按钮水平布局
    QHBoxLayout *windowLayout; //显示界面布局
    QVBoxLayout *mainlayout;    //主界面


private:
    CruveGeneration *cruveGeneration; //曲线拟合
signals:
    void quitOkSign();  //允许退出按钮
public slots:
    void saveBtnSlot();
    void quitBtnSlot();
    void createCurve(); //生成曲线
    /**
     * @brief 7个显示函数选择信号槽
     */
    void checkBoxBtn1Slot(int state);
    void checkBoxBtn2Slot(int state);
    void checkBoxBtn3Slot(int state);
    void checkBoxBtn4Slot(int state);
    void checkBoxBtn5Slot(int state);
    void checkBoxBtn6Slot(int state);
    void checkBoxBtn7Slot(int state);
    //单选按钮信号槽
    void radioBtnSlot();

};

#endif // STANDARDBIGHTWIDGET_H
