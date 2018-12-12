#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPixmap>
#include <QLabel>
#include <reagentvesseleditor.h>

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);
private slots:

private:
    QHBoxLayout *mainLayout;//主界面
    QVBoxLayout *layout_operation;//操作界面
    QStackedWidget *stack; //堆栈界面

    QPushButton *btn_unknowProduct;//未知品操作
    QPushButton *btn_qualityControl;//校准、质控品
    QPushButton *btn_standard;//标准品
    QPushButton *btn_selfCheck;//自检
    QPushButton *btn_lookUp;//查询
    QPushButton *btn_system;//系统
    QPushButton *btn_reagentVesselEditor;//试剂船编辑
    QPushButton *btn_standardCurveGeneration;//标准曲线生成

    QPixmap *pit_temp;//温度图片
    QLabel *label_temp;//显示温度
    QPixmap *pit_selfCheck;//自检图片
    QLabel *label_selfCheck;//显示自检

    ReagentVesselEditor *window_editor;

signals:

public slots:

};

#endif // MAINWIDGET_H
