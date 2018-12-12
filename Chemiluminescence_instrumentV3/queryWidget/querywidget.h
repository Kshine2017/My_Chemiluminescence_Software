#ifndef QUERYWIDGET_H
#define QUERYWIDGET_H

#include <QWidget>
#include <QDateEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableView>

#include <queryWidget/historysearch.h>
#include <queryWidget/qualitydataquery.h>

class queryWidget : public QWidget
{
    Q_OBJECT
public:
    queryWidget(QWidget *parent = 0);

    QWidget *widget;
    QTabWidget *tabWidget;

    QPushButton *questionBtn; //问号按钮

    HistorySearch *history;
    QualityDataQuery * qualityData;

    void init();

};

#endif // INFOSEARCH_H
