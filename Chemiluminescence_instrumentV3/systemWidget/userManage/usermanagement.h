#ifndef USERMANAGEMENT_H
#define USERMANAGEMENT_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QTabWidget>

class UserManagement : public QWidget
{
    Q_OBJECT
public:
    explicit UserManagement(QWidget *parent = 0);
    QTabWidget *tabWidget;
    QWidget *widget;

private:

    QVBoxLayout *mainLayout;


signals:

public slots:
};

#endif // USERMANAGEMENT_H
