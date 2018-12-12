#ifndef HISTORYSEARCH_H
#define HISTORYSEARCH_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QTableView>
#include <QPushButton>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include "systemWidget/qmysqlquerymodel.h"

/* query criteria       查询条件
 * Outpatient number    门诊号
 * Department           科室
 * Start date           起始日期
 * End date             结束日期
 * name                 姓名
 * Experiment number    实验号
 * query                查询
 * data processing      数据处理
 * Patient information collection   补录病人信息
 * Corrected experimental data     修正实验数据
 */

class HistorySearch : public QWidget
{
    Q_OBJECT
public:
    explicit HistorySearch(QWidget *parent = 0);

private:
    QWidget *widget;        //主窗口

    QHBoxLayout *layout_all;        //布局
    QVBoxLayout *layout_left;        //左边布局
    QVBoxLayout *layout_right;        //右边布局
    QHBoxLayout *layout_query_criteria;        //查询条件布局
    QHBoxLayout *layout_outpatient_number;        //门诊号布局
    QHBoxLayout *layout_department;        //科室布局
    QHBoxLayout *layout_start_date;        //起始日期布局
    QHBoxLayout *layout_end_date;        //结束日期布局
    QHBoxLayout *layout_name;        //姓名布局
    QHBoxLayout *layout_experiment_number;        //实验号布局
    QHBoxLayout *layout_query;        //查询按钮布局
    QHBoxLayout *layout_data_processing;        //数据处理布局
    QHBoxLayout *layout_btn;        //按钮布局

    QLabel *label_query_criteria;        //查询条件标签
    QLabel *label_outpatient_number;        //门诊号标签
    QLabel *label_department;        //科室标签
    QLabel *label_start_date;        //起始日期标签
    QLabel *label_end_date;        //结束日期标签
    QLabel *label_name;        //姓名标签
    QLabel *label_experiment_number;        //实验号标签
    QLabel *label_data_processing;        //数据处理标签

    QLineEdit *lineEdit_outpatient_number;        //门诊号输入框
    QLineEdit *lineEdit_department;        //科室输入框
    QDateEdit *dateEdit_start_date;        //起始日期输入框
    QDateEdit *dateEdit_end_date;        //结束日期输入框
    QLineEdit *lineEdit_name;        //姓名输入框
    QLineEdit *lineEdit_experiment_number;        //实验号输入框

    QPushButton *btn_query;        //查询按钮
    QPushButton *btn_patient_information_collection;        //补录病人信息按钮
    QPushButton *btn_corrected_experiment_data;        //修正实验数据按钮


    QPushButton *btn_delete;        //删除按钮
    int chooseFlag;                 //删除标志

    QTableView *tableView_patient_info;        //查询显示窗口

    QMySQlQueryModel *model;

    QTableView *tableView_experiment_data;        //修正实验数据窗口

    void init();

signals:

public slots:

    void query();
    void patientInformationCollect();
    void correctedExperimentData();
    void slot_btn_delete();
    void slot_click_tableView(const QModelIndex &index);
};

#endif // HISTORYSEARCH_H
