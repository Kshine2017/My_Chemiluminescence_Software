#ifndef TEMPERATUREPLOT_H
#define TEMPERATUREPLOT_H

#include <QWidget>
#include "standardBightWidget/qcustomplot.h"
class TemperaturePlot : public QWidget
{
    Q_OBJECT
public:
    explicit TemperaturePlot(QWidget *parent = nullptr);
    ~TemperaturePlot();

    //公开接口：添加新的温度
    void insertData(double tem);

    //QWidget* Widget_main;//这个类的主界面
    QCustomPlot* temPIC;
    double* Storge;//存储之前的温度值
    //int Length;


signals:

public slots:
};

#endif // TEMPERATUREPLOT_H
