#ifndef DIALOGADDDEPARTMENT_H
#define DIALOGADDDEPARTMENT_H

#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>

#include <QString>
#include <QStringList>

#include <QSqlQuery>

/**
 * @brief The DialogAddDepartment class
 * 新增科室对话框
 */

class DialogAddDepartment : public QDialog
{
    Q_OBJECT
public:
    DialogAddDepartment(QDialog *parent = 0);
    QVBoxLayout *mainLayout;

    QHBoxLayout *layout_hospital;
    QHBoxLayout *layout_Department;
    QHBoxLayout *layout_btn;

    QWidget *widget_content;

    QLabel *label_hospital;
    QLabel *label_DeDepartment;

    QLineEdit *lineEdit_hospital;
    QLineEdit *lineEdit_DeDepartment;

    QPushButton *btn_saveAdd;
    QPushButton *btn_saveClose;
    QPushButton *btn_cancel;

    QString data_DeDepartment;
    QString data_hospital;
    QString data;

    QString getData();

signals:
    void signal_saveAdd();
    void signal_saveClose();

public slots:

    void init();
    void saveAdd();
    void saveClose();
    void cancel();



};

#endif // DIALOGADDDEPARTMENT_H
