#ifndef CLINICALDIAGNOSIS_H
#define CLINICALDIAGNOSIS_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTableView>
#include <QWidget>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <systemWidget/qmysqlquerymodel.h>
#include <systemWidget/clinicalDiagnosis/dialogadddepartment.h>
#include <systemWidget/clinicalDiagnosis/dialogadddiagnosticcategory.h>


class ClinicalDiagnosis : public QWidget
{
    Q_OBJECT
public:
    explicit ClinicalDiagnosis(QWidget *parent = 0);

    QVBoxLayout *mainLayout;

    QVBoxLayout *layout_InspectionDepartment;
    QVBoxLayout *layout_DiagnosisDepartment;

    QHBoxLayout *layout_InspectionBtn;
    QHBoxLayout *layout_DiagnosisBtn;

    QHBoxLayout *layout_Manage;

    QLabel * lab_bg;
    QWidget *widget_content;

    QLabel * lab_InspectionDepartment;
    QLabel * lab_DiagnosisDepartment;

    QTableView *tableView_InspectionDepartment;
    QTableView *tableView_DiagnosisDepartment;

    QMySQlQueryModel *model_InspectionDepartment;
    QMySQlQueryModel *model_DiagnosisDepartment;

    QPushButton *btn_AddDepartment;
    QPushButton *btn_DeleteDepartment;

    QPushButton *btn_AddDiagnosticCategory;
    QPushButton *btn_DeleteDiagnosticCategory;

    DialogAddDiagnosticCategory *dialog_addDiagnostic; //增加诊断类型管理-弹窗
    DialogAddDepartment *dialog_addDepartment;  //增加科室-弹窗

    int delete_table_row_flag_department;
signals:

public slots:
    void init();
    void addDepartment();
    void deleteDepartment();
    void AddDiagnosticCategory();
    void deleteDiagnosticCategory();

    void update_tableView();

    //--------
    void slot_getTablerow_department(QModelIndex index);
};

#endif // CLINICALDIAGNOSIS_H
