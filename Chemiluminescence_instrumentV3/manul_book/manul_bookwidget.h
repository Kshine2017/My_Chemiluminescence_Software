/**
  *  @brief    说明书
  *  @file     manul_bookwidget.h
  *  @author   谢飞
  *  @version  1.0(版本号)
  *  @date     2017-10-22
  */
#ifndef MANUL_BOOKWIDGET_H
#define MANUL_BOOKWIDGET_H

#include <QDialog>
#include <QFile>
#include <QTextEdit>
#include <QLabel>
#include <QTextStream>
#include <QWidget>
class manul_bookWidget : public QDialog
{
    Q_OBJECT
public:
    explicit manul_bookWidget(QWidget *parent = 0);

//窗口标题显示
    void titleInit();
//显示说明书文档
    void DisplayTest();

private:
    QFile *file; //要读取的文件夹
    QTextEdit *textEdit;  //显示文件
//窗口标题显示
    //窗口标签
        QLabel *WindowTile;
    //显示状态
        QLabel *statusTitleLab;
signals:

public slots:
};

#endif // MANUL_BOOKWIDGET_H
