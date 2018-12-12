#ifndef REAGENTNUMBER_H
#define REAGENTNUMBER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QTableView>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QPushButton>
#include "../qmysqlquerymodel.h"

class reagentNumber : public QWidget
{
    Q_OBJECT
public:
    explicit reagentNumber(QWidget *parent = 0);
private:
    QWidget *widget;

    QVBoxLayout *mainLayout;
    QTableView *tableView;

    QMySQlQueryModel *model;

    QPushButton *btn_add;   //新增按钮
    QPushButton *btn_updata;    //修改按钮
    QPushButton *btn_delete;    //删除按钮
    QPushButton *btn_query;     //查询按钮
    int chooseFlag;

signals:

public slots:
    void btn_addSlot();     //新增按钮槽
    void btn_updateSlot();  //修改按钮槽
    void btn_deleteSlot();  //删除按钮槽
    void btn_querySlot();   //查询按钮槽

    void fresh_table();     //进行数据库操作后刷新表格
    void fresh_table_select(QString str_category, QString str_projectName, QString str_reagentType);    //进行数据库查询操作后刷新表格
    void slot_doubleclick_tableview(const QModelIndex &index);

};

#endif // REAGENTNUMBER_H
