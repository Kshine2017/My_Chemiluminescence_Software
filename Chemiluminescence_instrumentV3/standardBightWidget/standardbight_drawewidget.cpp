#include "standardbight_drawewidget.h"
#include "data/util.h"

standardBight_draweWidget::standardBight_draweWidget(QWidget *parent) : QWidget(parent)
{  
    setFixedSize(1230,900);
    setWindowFlags(Qt::FramelessWindowHint);
    setAutoFillBackground(true);
    QPalette pa;
    QPixmap pixmap(tr(":/picture/standardBight/draw_Ground.png"));
    pa.setBrush(QPalette::Window,QBrush(pixmap));
    setPalette(pa);

    LabelInit();
    drawWidgetInit();
    mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(0);
    mainLayout->addWidget(drawWidget);
    mainLayout->addLayout(fuctionLayout);
    mainLayout->addWidget(disfuctionLabel);
    mainLayout->addLayout(R2Layout);

}
/**
 * @brief 设置函数标签内容
 */
void standardBight_draweWidget::setfuctionLab(const QString &fuctionLab,const QString &RRstring)
{
     disfuctionLabel->setText(fuctionLab);
     RCoefficientValueLabel->setText(RRstring);
}

/**
 * @brief standardBight_draweWidget::标签初始化
 */
void standardBight_draweWidget::LabelInit()
{
    fuctionOneNameLabel = new QLabel;
    fuctionOneNameLabel->setText(tr("log-Logist方程:"));
    fuctionOneColorLabel = new QLabel;
    fuctionOneColorLabel->setFixedSize(100,30);
    fuctionOneColorLabel->setStyleSheet("background-color:red");
    fuctionTwoNameLabel = new QLabel;
    fuctionTwoNameLabel->setText(tr("多项式(2~6次)方程:"));
    fuctionTwoColorLabel = new  QLabel;
    fuctionTwoColorLabel->setFixedSize(100,30);
    fuctionTwoColorLabel->setStyleSheet("background-color:cyan");
    fuctionThreeNameLabel =new QLabel;
    fuctionThreeNameLabel->setText(tr("四参数:"));
    fuctionThreeColorLabel = new QLabel;
    fuctionThreeColorLabel->setFixedSize(100,30);
    fuctionThreeColorLabel->setStyleSheet("background-color:darkBlue");
    fuctionFourNameLabel = new QLabel;
    fuctionFourNameLabel->setText(tr("对数Ln:"));
    fuctionFourColorLabel = new QLabel;
    fuctionFourColorLabel->setFixedSize(100,30);
    fuctionFourColorLabel->setStyleSheet("background-color:green");
    fuctionFiveNameLabel = new QLabel;
    fuctionFiveNameLabel->setText(tr("对数线性拟合："));
    fuctionFiveColorLabel = new QLabel;
    fuctionFiveColorLabel->setFixedSize(100,30);
    fuctionFiveColorLabel->setStyleSheet("background-color:darkCyan");

    disfuctionLabel = new  QLabel;
 //这句话要删除

    disfuctionLabel->setText("Y = ");
    R2Layout = new QHBoxLayout;
    RCoefficientNameLabel = new QLabel;
    RCoefficientNameLabel->setText(tr("相关系数R ="));
    RCoefficientValueLabel = new QLabel;
    R2Layout->addWidget(RCoefficientNameLabel);
    R2Layout->addWidget(RCoefficientValueLabel);
    R2Layout->addStretch();

    fuctionLayout = new QHBoxLayout;
    fuctionLayout->addWidget(fuctionOneNameLabel);
    fuctionLayout->addWidget(fuctionOneColorLabel);
    fuctionLayout->addSpacing(50);
    fuctionLayout->addWidget(fuctionTwoNameLabel);
    fuctionLayout->addWidget(fuctionTwoColorLabel);
    fuctionLayout->addSpacing(50);
    fuctionLayout->addWidget(fuctionThreeNameLabel);
    fuctionLayout->addWidget(fuctionThreeColorLabel);
    fuctionLayout->addSpacing(50);
    fuctionLayout->addWidget(fuctionFourNameLabel);
    fuctionLayout->addWidget(fuctionFourColorLabel);
    fuctionLayout->addSpacing(50);
    fuctionLayout->addWidget(fuctionFiveNameLabel);
    fuctionLayout->addWidget(fuctionFiveColorLabel);
    fuctionLayout->addSpacing(20);
}

/**
 * @brief standardBight_draweWidget::绘图窗口初始化
 */
void standardBight_draweWidget::drawWidgetInit()
{
    drawWidget = new QWidget;
    drawWidget->setWindowFlags(Qt::FramelessWindowHint);
    drawWidget->setFixedSize(1200,800);

    Util::getX("1111",50000.0);
}
