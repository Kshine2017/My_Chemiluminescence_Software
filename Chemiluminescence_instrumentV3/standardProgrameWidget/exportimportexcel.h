#ifndef EXPORTIMPORTEXCEL_H
#define EXPORTIMPORTEXCEL_H

#include <QString>
#include <QDialog>
#include <QObject>
#include <QAxObject>
#include <QLabel>
#include <QFrame>
class ExportImportExcel:public QDialog
{
    Q_OBJECT
public:
    ExportImportExcel(QWidget *parent = 0);
    void ExportDialog();
    void ImportDialog();
    ~ExportImportExcel();
    QFrame* background;
    QLabel* tip_label;

private:
    void onImportExcel(QString filePath);
    void onExportExcel(QString filePath);
    //void DATAtoExcel(QAxObject *work_book);
    void DATAtoExcel_0517(QAxObject *work_book);
    //void DATAtoBase(QAxObject *work_book);
    void DATAtoBase_0517(QAxObject *work_book);
};

#endif // EXPORTIMPORTEXCEL_H
