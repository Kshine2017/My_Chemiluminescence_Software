#ifndef OPERATION_STEP_H
#define OPERATION_STEP_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>

/*
 * 试剂船编辑 操作步骤
 */
class Operation_step : public QWidget
{
    Q_OBJECT
public:
    explicit Operation_step(QWidget *parent = 0);
    QHBoxLayout *mainLayout;
    QVBoxLayout *layout_btn;
    QPushButton *btn_add;//加
    QPushButton *btn_minus;//减
    QPushButton *btn_singleStep;//单步运行

    QLabel *label_step;
    QLabel *label_startPosition;
    QLabel *label_endPosition;
    QLabel *label_time;
    QLabel *label_preOrderMixingTimes;//前序混匀次数
    QLabel *label_ordinalMixingTimes;//前序混匀次数

    QComboBox * combo_step;//步骤
    QComboBox * combo_startPosition;//起始位置
    QComboBox * combo_endPosition;//放入位置
    QComboBox * combo_time;//时间
    QComboBox * combo_preOrderMixingTimes;//前序混匀次数
    QComboBox * combo_ordinalMixingTimes;//前序混匀次数





signals:

public slots:
};

#endif // OPERATION_STEP_H
