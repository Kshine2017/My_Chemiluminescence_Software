#ifndef SYSTEMMAINTENANCE_H
#define SYSTEMMAINTENANCE_H
/*
 *
 */

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTableView>
#include <QString>

class SystemMaintenance : public QWidget
{
    Q_OBJECT
public:
    explicit SystemMaintenance(QWidget *parent = 0);
    QVBoxLayout *mainLayout;
    QWidget *widget;
    QHBoxLayout *layout_la;
    QVBoxLayout *layout_RoutineMaintain;
    QVBoxLayout *layout_SingleMaintain;
    QHBoxLayout *layout_btn_routine;
    QHBoxLayout *layout_btn_single;

    QHBoxLayout *layout_btn_AutomaticDay;
    QHBoxLayout *layout_btn_AutomaticWeek;
    QHBoxLayout *layout_btn_Instrument;
    QHBoxLayout *layout_btn_PMT;

    QLabel *label_RoutineMaintain;

    QPushButton *btn_AutomaticDay;
    QPushButton *btn_AutomaticWeek;

    QTableView *tableView_RoutineMaintain;
    QTableView *tableView_SingleMaintain;

    QPushButton *btn_start;
    QPushButton *btn_pause;
    QPushButton *btn_continue;

    QLabel *label_SingleMaintain;
    QPushButton *btn_Instrument;
    QPushButton *btn_PMT;

    QPushButton *btn_InstrumentStart;
    QPushButton *btn_InstrumentStop;

    void init();


signals:

public slots:

    void automaticDayMaintain();
    void automaticWeekMaintain();
    void initInstrument();
    void testPMT();

    void startMaintain();
    void pauseMaintain();
    void continueMaintain();

    void startInstrument();
    void stopInstrument();
};

#endif // SYSTEMMAINTENANCE_H
#ifndef SYSTEMMAINTENANCE_H
#define SYSTEMMAINTENANCE_H

#include <QWidget>

class SystemMaintenance : public QWidget
{
    Q_OBJECT
public:
    explicit SystemMaintenance(QWidget *parent = 0);

signals:

public slots:
};

#endif // SYSTEMMAINTENANCE_H
