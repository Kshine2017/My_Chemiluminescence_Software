#ifndef DISPLAYCRUVE_H
#define DISPLAYCRUVE_H

#include <QWidget>
#include <QDialog>
#include <standardBightWidget/qcustomplot.h>

class DisplayCruve : public QDialog
{
    Q_OBJECT
public:
    explicit DisplayCruve(QWidget *parent = 0);
    double maxX;    //浓度最大值
    double maxY;    //发光值最大值

public:
    void paint_cruve(QString name, double *x,double *y,int n);

private :

    QCustomPlot *customPlot;

    void init();
    /**
     * @brief paint_cruve 画曲线
     * @param name  项目名
     * @param x     浓度 数组
     * @param y     发光值数组
     * @param n     点的个数
     * 浓度与发光值位置需一一对应
     */


signals:

public slots:
};

#endif // DISPLAYCRUVE_H
