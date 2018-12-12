#ifndef SELFTESTSTEP_H
#define SELFTESTSTEP_H

#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QCheckBox>
#include <QWidget>
class SelfTestStep:public QWidget
{
public:
        Q_OBJECT
public:
    explicit SelfTestStep(QWidget *parent = 0);
    explicit SelfTestStep(int num,QString name);

    int number; //序号
    QCheckBox *checkBox; //复选框
    QLabel *label_result;  //结果
    QLabel *label_expand;  //拓展项
    QLabel *label;  //检测项目
    QSpinBox *spinBox;//次数下拉框
    QPushButton *btn; //单项执行按钮


private:
    void connectInit();

signals:
    void sendData(int num ,int count);
public slots:
    void btnSlot();
};

#endif // SELFTESTSTEP_H
