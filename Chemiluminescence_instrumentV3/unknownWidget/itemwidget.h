#ifndef ITEMWIDGET_H
#define ITEMWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QProgressBar>
#include <QHBoxLayout>
class itemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit itemWidget(QWidget *parent = 0);
public:
    void setTestProgressBar(int);
private:
    QLabel *checkNameLab;          //检测名称
    QLabel *bachNumberLab;         //批号
    QLabel *currentWorkLab;        //当前工作阶段
    QLabel *startTimerLab;         //开始时间
    QLabel *endTimerLab;           //结束时间
    QLabel *measurePhotonLab;       //测量光子
    QLabel *measureConcentrationLab;  //测量浓度
    QProgressBar *testProgressBar;    //测试进度
    QPushButton *startBtn;          //开始按钮
    QPushButton * OkBtn;             //结束工作按钮
    QHBoxLayout *mainlayout;        //主布局器
signals:

public slots:
};

#endif // ITEMWIDGET_H
