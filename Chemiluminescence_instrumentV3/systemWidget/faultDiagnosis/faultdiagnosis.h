#ifndef FAULTDIAGNOSIS_H
#define FAULTDIAGNOSIS_H

#include <QWidget>
#include <QTabWidget>
#include <QTableView>

class FaultDiagnosis : public QWidget
{
    Q_OBJECT
public:
    explicit FaultDiagnosis(QWidget *parent = 0);
    QWidget *widget;
    QTabWidget *tabWidget;
    QTableView *tableView_History;
    QTableView *tableView_Fault;

    void init();



signals:

public slots:
};

#endif // FAULTDIAGNOSIS_H
