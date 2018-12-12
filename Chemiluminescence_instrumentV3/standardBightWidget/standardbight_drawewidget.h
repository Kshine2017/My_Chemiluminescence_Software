/**
  *  @brief   曲线生成画图窗口
  *  @file    standardbight_drawewidget.h
  *  @author   谢飞
  *  @version  1.0(版本号)
  *  @date     2017-10-16
  */
#ifndef STANDARDBIGHT_DRAWEWIDGET_H
#define STANDARDBIGHT_DRAWEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
class standardBight_draweWidget : public QWidget
{
    Q_OBJECT
public:
    explicit standardBight_draweWidget(QWidget *parent = 0);

public:
    /**
     * @brief 设置函数标签内容
     */
    void setfuctionLab(const QString &fuctionLab, const QString &RRstring);

private:
    void LabelInit();
    void drawWidgetInit();

public:
        QWidget *drawWidget; /**< 图曲线界面>*/
private:


    QLabel *fuctionOneNameLabel;
    QLabel *fuctionOneColorLabel;
    QLabel *fuctionTwoNameLabel;
    QLabel *fuctionTwoColorLabel;
    QLabel *fuctionThreeNameLabel;
    QLabel *fuctionThreeColorLabel;
    QLabel *fuctionFourNameLabel;
    QLabel *fuctionFourColorLabel;
    QLabel *fuctionFiveNameLabel;
    QLabel *fuctionFiveColorLabel;

    QLabel *disfuctionLabel;
    QLabel *RCoefficientNameLabel;
    QLabel *RCoefficientValueLabel;

private:
    QHBoxLayout *fuctionLayout;
    QHBoxLayout *R2Layout;
    QVBoxLayout *mainLayout;
signals:

public slots:
};

#endif // STANDARDBIGHT_DRAWEWIDGET_H
