#ifndef QWAITDIALOG_H
#define QWAITDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QMovie>
#include <QFrame>
#include <QTimer>
class QWaitDialog : public QDialog
{
    Q_OBJECT
public:
    explicit QWaitDialog(QWidget *parent,const QString &title);
    ~QWaitDialog();
private:

    QMovie *movie;
    QLabel *label;
    QLabel * tip_label;
    QFrame * background;
    QTimer* timer;
signals:

public slots:

};

#endif // QWAITDIALOG_H
