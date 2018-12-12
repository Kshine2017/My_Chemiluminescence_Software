#ifndef DIALOGADDDIAGNOSTICCATEGORY_H
#define DIALOGADDDIAGNOSTICCATEGORY_H

#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>

#include <QString>
#include <QStringList>


class DialogAddDiagnosticCategory : public QDialog
{
    Q_OBJECT
public:
    DialogAddDiagnosticCategory(QDialog *parent = 0);
    QVBoxLayout *mainLayout;

    QHBoxLayout *layout_num;
    QHBoxLayout *layout_Department;
    QHBoxLayout *layout_btn;

    QWidget *widget_content;

    QLabel *label_num;
    QLabel *label_DeDepartment;

    QLineEdit *lineEdit_num;
    QLineEdit *lineEdit_DeDepartment;

    QPushButton *btn_saveAdd;
    QPushButton *btn_saveClose;
    QPushButton *btn_cancel;

    QString data_DeDepartment;
    QString data_num;
    QString data;

    QString getData();

public slots:

    void init();
    void saveAdd();
    void saveClose();
    void cancel();
};

#endif // DIALOGADDDIAGNOSTICCATEGORY_H
