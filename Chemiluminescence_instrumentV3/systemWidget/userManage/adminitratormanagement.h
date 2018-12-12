#ifndef ADMINITRATORMANAGEMENT_H
#define ADMINITRATORMANAGEMENT_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QTableView>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QPushButton>
#include <systemWidget/qmysqlquerymodel.h>
#include "../qmysqlquerymodel.h"
#include "mydialogquery.h"
class AdminitratorManagement: public QWidget
{
    Q_OBJECT
public:
    explicit AdminitratorManagement(QWidget *parent = 0);

private:
    QWidget *widget;

    QVBoxLayout *mainLayout;
    QLabel *lab_bg;
    QTableView *tableView;

    QMySQlQueryModel *model;

    QPushButton *btn_add;
    QPushButton *btn_updata;
    QPushButton *btn_delete;
    QPushButton *btn_query;
    MyDialogQuery *myDialog_query;
    int chooseFlag;

signals:

public slots:
    void btn_addSlot();
    void btn_updateSlot();
    void btn_deleteSlot();
    void btn_querySlot();

    void fresh_table();
    void fresh_table_select();
    void slot_doubleclick_tableview(const QModelIndex &index);
};

#endif // ADMINITRATORMANAGEMENT_H
