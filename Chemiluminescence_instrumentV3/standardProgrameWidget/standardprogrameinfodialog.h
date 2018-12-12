#ifndef STANDARDPROGRAMEINFODIALOG_H
#define STANDARDPROGRAMEINFODIALOG_H

#include <QWidget>
#include <QDialog>

#include <QPushButton>
#include <QTableView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QtSql/QSqlQuery>
#include <QSqlQueryModel>
#include "systemWidget/qmysqlquerymodel.h"

class StandardProgrameInfoDialog : public QDialog
{
    Q_OBJECT
public:
    StandardProgrameInfoDialog(QWidget *parent = 0);

public:
    QPushButton *btn_sure;
    QPushButton *btn_delete;
    QPushButton *btn_cancel;
private:
    QVBoxLayout *mainLayout;
    QHBoxLayout *layout_btn;
    QTableView *tableView;
    QMySQlQueryModel *model;
    int chooseFlag;         //选择的行数，未选择视为-1；
    void init();

signals:

    void OpenStandardInfo(QString &fileShortName);
    void DeleteStandardInfo(QString &fileShortName);
public slots:
    void btn_sure_solt();
    void btn_delete_solt();
    void btn_cancel_solt();
    void getIndex_click_tableView_slot(const QModelIndex &index);
    void getIndex_Double_click_tableView_slot(const QModelIndex &index);
};

#endif // STANDARDPROGRAMEINFODIALOG_H
