#ifndef QUALITYDATAQUERY_H
#define QUALITYDATAQUERY_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QDateEdit>
#include <QRadioButton>
#include <QTableView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QButtonGroup>
#include <QtSql/QSqlQueryModel>
#include "../systemWidget/qmysqlquerymodel.h"
class QualityDataQuery : public QWidget
{
    Q_OBJECT
public:
    explicit QualityDataQuery(QWidget *parent = 0);

private:

    QWidget *widget;
    QVBoxLayout *layout_left;       //左边布局
    QHBoxLayout *layout_queryItem;      //查询横布局
    QHBoxLayout *layout_startTime;      //起始日期横布局
    QHBoxLayout *layout_endTime;      //结束日期横布局
    QHBoxLayout *layout_dateType;      //数据类型横布局
    QHBoxLayout *layout_queryButton;      //查询按钮横布局

    QLabel *lab_query_criteria;     //查询条件label
    QLabel *lab_date_type;          //数据类型label
    QLabel *lab_start;             //起始日期label
    QLabel *lab_end;               //结束日期label

    QDateEdit *dateEdit_start;     //起始日期
    QDateEdit *dateEdit_end;       //结束日期

    QButtonGroup *buttonGroup_dateType;         //数据类型单选按钮组
    QVBoxLayout *layout_buttonDataType;
    QVBoxLayout *layout_buttonGroup;
    QRadioButton *radioButton_quality;         //质控点
    QRadioButton *radioButton_calibration;         //校准点
    QRadioButton *radioButton_standard;         //标准点

    QPushButton *btn_query;         //查询按钮
    QTableView *tableView;          //表————查询所得结果

    QMySQlQueryModel *model;

    QPushButton *btn_delete;        //删除按钮
    int chooseFlag_delete;                 //删除标志--即选中需要删除的行

    void init();
    void selectDATA_freshTable(int chooseFlag,const QString& S_time,const QString& E_time);

signals:

public slots:
    void query();
    void slot_btn_delete();
    void slot_click_tableView(const QModelIndex &index);
};

#endif // QUALITYDATAQUERY_H
