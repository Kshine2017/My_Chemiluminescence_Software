#include "standardpragramewidget.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDateTime>
#include <QDebug>
#include <QSqlError>
#include "Serial_port/serialport.h"
#include <QLineEdit>
#include "QMessgeBox/mymessgebox.h"
#include "standardprogrameinfodialog.h"

#define REAGENT_TABLE_WIDTH 90 //试剂船表格宽度
#define REAGENT_TABLE_HIGHT 30
#include "dataopration.h"
#include "data/configfile.h"
#include "menu/qwaitdialog.h"
#include "systemWidget/reagentNumber/databaseoperation.h"
/**
 * @brief 试剂船项目名称表格属性
 */
#define TABLE_NAME_WIDTH 85
#define TABLE_EDIT_WIDTH 120
#define TABLE_HIGH 30


standardPragrameWidget::standardPragrameWidget(QWidget *parent) : QWidget(parent)
{
    //头图标初始化
    titleInit();

    //显示类
    reagentdisplay = new reagentDisplay(this);
    //reagentdisplay->setFixedSize(1632,218);//图片已被拉伸1671 246
    reagentdisplay->setAutoFillBackground(true);
    QPalette palette;
    QPixmap pixmap(":/picture/standardPrograme/shijichuan_bianji_background.png");
    palette.setBrush(QPalette::Window, QBrush(pixmap));

    reagentdisplay->setPalette(palette);
    reagentdisplay->setGeometry(0,70,1671,246);

    //中间部分（包括两个表格）

    //表格1
    tableProjectWidgetInit();//项目信息
    tableProjectWidget->setGeometry(8,318,1653,32);
    //表格2
    tableInit(); //试剂船编辑
    tableWidget->setGeometry(8,348,1652,124);//320



    //试剂船编辑类（下半部分整体）
    reagentPromWidget = new reagentProWidget(this);
    reagentPromWidget->setFixedSize(1671,606);
    reagentPromWidget->setAutoFillBackground(true);
    QPixmap pixmap_one(":/picture/standardPrograme/display_background.png");
    palette.setBrush(QPalette::Window, QBrush(pixmap_one));
    reagentPromWidget->setPalette(palette);
    reagentPromWidget->setGeometry(0,475,1650,606);//444


    connectInit(); //信号槽绑定函数

    emit signal_refreshNumber();
}
/**
 * @brief 获取当前船位置位置的数据
 * @param 试剂船位置信息
 * @return 试剂船当前位置
 */
QString standardPragrameWidget::getX_Y_Value(unsigned char postion)
{
    unsigned char column = postion + 1; //数据表格位置偏移
    QString postionStr = "";
    QString tempstr = ""; //临时变量字符串
    unsigned int tempNum; //位置临时变量
    //x轴
    tempNum =  ((QLineEdit *)( tableWidget->cellWidget(1,column)))->text().toDouble() * 1000;
    qDebug() << "当前X轴坐标" << ((QLineEdit *)( tableWidget->cellWidget(1,2)))->text();
    if((unsigned char)(( tempNum >>24 )&0xff) <= 0x0f){
        postionStr += "0";
    }
    postionStr += tempstr.setNum( (unsigned char)(( tempNum >>24 )&0xff),16 );
    postionStr += ",";
    if((unsigned char)(( tempNum >>16 )&0xff) <= 0x0f){
        postionStr += "0";
    }
    postionStr += tempstr.setNum( (unsigned char)(( tempNum >>16 )&0xff),16 );
    postionStr += ",";
    if((unsigned char)(( tempNum >>8 )&0xff) <= 0x0f){
        postionStr += "0";
    }
    postionStr += tempstr.setNum( (unsigned char)(( tempNum >>8)&0xff),16 );
    postionStr += ",";
    if((unsigned char)( tempNum &0xff) <= 0x0f){
        postionStr += "0";
    }
    postionStr += tempstr.setNum( (unsigned char)( tempNum &0xff),16 );
    postionStr += ",";

    //Y轴
    tempNum =  ((QLineEdit *)( tableWidget->cellWidget(2,column)))->text().toDouble() * 1000;
    if((unsigned char)(( tempNum >>24 )&0xff) <= 0x0f){
        postionStr += "0";
    }
    postionStr += tempstr.setNum( (unsigned char)(( tempNum >>24 )&0xff),16 );
    postionStr += ",";
    if((unsigned char)(( tempNum >>16 )&0xff) <= 0x0f){
        postionStr += "0";
    }
    postionStr += tempstr.setNum( (unsigned char)(( tempNum >>16 )&0xff),16 );
    postionStr += ",";
    if((unsigned char)(( tempNum >>8 )&0xff) <= 0x0f){
        postionStr += "0";
    }
    postionStr += tempstr.setNum( (unsigned char)(( tempNum >>8)&0xff),16 );
    postionStr += ",";
    if((unsigned char)( tempNum &0xff) <= 0x0f){
        postionStr += "0";
    }
    postionStr += tempstr.setNum( (unsigned char)( tempNum &0xff),16 );
    qDebug() << "当前x y坐标数据" << postionStr;
    return postionStr;
}
/**
 * @brief 获取当前船位置位置的容量
 * @param 试剂船位置信息
 * @return 试剂船当前位置的容量
 */
QString standardPragrameWidget::getC_Value(unsigned char postion)
{
    unsigned char column = postion;
    QString capacityStr = "";
    switch(column){
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
        break;
    case 7:
        break;
    case 8:
        break;
    case 9:
        break;
    case 10:
        break;
    case 11:
        break;
    case 12:
        break;
    case 13:
        break;
    case 14:
        break;
    }
    return capacityStr;
}



/**
 * @brief 窗口标题头初始化
 */
void standardPragrameWidget::titleInit()
{

    titleIconLab = new QLabel(this);   //头图标
    titleIconLab->setPixmap(QPixmap(":/picture/standardPrograme/tile_icon.png"));

    titleTextLab = new QLabel(titleIconLab); //标题文字
    titleTextLab->setText(tr("试剂船编辑区域"));

    QPalette   pal;//按键字体颜色设置
    pal.setColor(QPalette::WindowText, QColor(255, 255, 255, 255));
    titleTextLab->setPalette(pal);
    titleTextLab->setFont(QFont("windowTitle",15));
    titleTextLab->setGeometry(80,13,100,40);

    questionBtn = new QPushButton(titleIconLab); //问号按钮
    questionBtn->setIconSize(QSize(46,45));
    questionBtn->setIcon(QIcon(":/picture/standardPrograme/？btn.png"));
    questionBtn->setFlat(true);
    //    questionBtn->setStyleSheet("QPushButton{border-image: url(:/new/icons/icons/play-pause.png);}"
    //                               "QPushButton:hover{border-image: url(:/new/icons/icons/play-pause-hover.png);}"
    //                               "QPushButton:pressed{border-image: url(:/new/icons/icons/play-pause-pressed.png);}");
    questionBtn->setGeometry(1600,1,45,45);
    titleIconLab->setGeometry(0,0,1687,67);
}
/**
 * @brief 试剂船表格  初始化
 */
void standardPragrameWidget::tableInit()
{
    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(18);
    tableWidget->setRowCount(4);
    tableWidget->horizontalHeader()->hide();
    tableWidget->verticalHeader()->hide();
    //表格边框颜色和选中背景色
    tableWidget->setStyleSheet("gridline-color: rgb(0, 139, 139);selection-background-color:white;");

    tableWidget->setColumnWidth(0,110);
    tableWidget->setColumnWidth(1,REAGENT_TABLE_WIDTH);
    tableWidget->setColumnWidth(2,REAGENT_TABLE_WIDTH);
    tableWidget->setColumnWidth(3,REAGENT_TABLE_WIDTH);
    tableWidget->setColumnWidth(4,REAGENT_TABLE_WIDTH);
    tableWidget->setColumnWidth(5,REAGENT_TABLE_WIDTH);
    tableWidget->setColumnWidth(6,REAGENT_TABLE_WIDTH);
    tableWidget->setColumnWidth(7,REAGENT_TABLE_WIDTH);
    tableWidget->setColumnWidth(8,REAGENT_TABLE_WIDTH);
    tableWidget->setColumnWidth(9,REAGENT_TABLE_WIDTH);
    tableWidget->setColumnWidth(10,REAGENT_TABLE_WIDTH);
    tableWidget->setColumnWidth(11,REAGENT_TABLE_WIDTH);
    tableWidget->setColumnWidth(12,REAGENT_TABLE_WIDTH);
    tableWidget->setColumnWidth(13,REAGENT_TABLE_WIDTH);
    tableWidget->setColumnWidth(14,REAGENT_TABLE_WIDTH);
    tableWidget->setColumnWidth(15,REAGENT_TABLE_WIDTH);
    tableWidget->setColumnWidth(16,REAGENT_TABLE_WIDTH);
    tableWidget->setColumnWidth(17,REAGENT_TABLE_WIDTH+10);
    tableWidget->setRowHeight(0,REAGENT_TABLE_HIGHT);
    tableWidget->setRowHeight(1,REAGENT_TABLE_HIGHT);
    tableWidget->setRowHeight(2,REAGENT_TABLE_HIGHT);

    tableWidget->setFixedSize(1652,122);

    tableWidget->setSpan(0, 0, 4, 1); //合并单元格
    QTableWidgetItem *item = new QTableWidgetItem;
    item->setFlags(Qt::NoItemFlags);
    item->setFont(QFont("edit",13,QFont::Bold));
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(tr("试剂船编辑："));
    tableWidget->setItem(0,0,item);

    //----------------------------------------------------------------
    //----------------------------------------------------------------


    //-----------

    QTableWidgetItem *itemName = new QTableWidgetItem;
    itemName->setTextAlignment(Qt::AlignCenter);
    itemName->setFlags(Qt::NoItemFlags);
    itemName->setText(tr("名    称："));
    tableWidget->setItem(0,1,itemName);

    QTableWidgetItem *itemXP = new QTableWidgetItem;
    itemXP->setTextAlignment(Qt::AlignCenter);
    itemXP->setFlags(Qt::NoItemFlags);
    itemXP->setText(tr("X位置(mm):"));
    tableWidget->setItem(1,1,itemXP);

    QTableWidgetItem *itemYP = new QTableWidgetItem;
    itemYP->setTextAlignment(Qt::AlignCenter);
    itemYP->setFlags(Qt::NoItemFlags);
    itemYP->setText(tr("Y位置(mm):"));
    tableWidget->setItem(2,1,itemYP);

    QTableWidgetItem *itemC = new QTableWidgetItem;
    itemC->setTextAlignment(Qt::AlignCenter);
    itemC->setFlags(Qt::NoItemFlags);
    itemC->setText(tr("容量(ul):"));
    tableWidget->setItem(3,1,itemC);

    QTableWidgetItem *itemRaction1= new QTableWidgetItem;
    itemRaction1->setTextAlignment(Qt::AlignCenter);
    itemRaction1->setFlags(Qt::NoItemFlags);
    itemRaction1->setText(tr("血浆-样本"));
    tableWidget->setItem(0,17,itemRaction1);

    QTableWidgetItem *itemRaction1X= new QTableWidgetItem;
    itemRaction1X->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(1,17,itemRaction1X);


    QTableWidgetItem *itemRaction1Y= new QTableWidgetItem;
    itemRaction1Y->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(2,17,itemRaction1Y);

    QTableWidgetItem *itemRactionC= new QTableWidgetItem;
    itemRactionC->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(3,17,itemRactionC);

    QTableWidgetItem *itemPlasma = new QTableWidgetItem;
    itemPlasma->setTextAlignment(Qt::AlignCenter);
    itemPlasma->setFlags(Qt::NoItemFlags);
    itemPlasma->setText(tr("反应管"));
    tableWidget->setItem(0,16,itemPlasma);

    QTableWidgetItem *itemPlasmaX = new QTableWidgetItem;
    itemPlasmaX->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(1,16,itemPlasmaX);

    QTableWidgetItem *itemPlasmaY = new QTableWidgetItem;
    itemPlasmaY->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(2,16,itemPlasmaY);

    QTableWidgetItem *itemPlasmaC = new QTableWidgetItem;
    itemPlasmaC->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(3,16,itemPlasmaC);


    QTableWidgetItem *itemEster = new QTableWidgetItem;
    itemEster->setTextAlignment(Qt::AlignCenter);
    itemEster->setFlags(Qt::NoItemFlags);
    itemEster->setText(tr("吖啶酯"));
    tableWidget->setItem(0,15,itemEster);

    QTableWidgetItem *itemEsterX = new QTableWidgetItem;
    itemEsterX->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(1,15,itemEsterX);

    QTableWidgetItem *itemEsterY = new QTableWidgetItem;
    itemEsterY->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(2,15,itemEsterY);

    QTableWidgetItem *itemEsterC = new QTableWidgetItem;
    itemEsterC->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(3,15,itemEsterC);


    QTableWidgetItem *itemBiotin = new QTableWidgetItem;
    itemBiotin->setTextAlignment(Qt::AlignCenter);
    itemBiotin->setFlags(Qt::NoItemFlags);
    itemBiotin->setText(tr("生物素"));
    tableWidget->setItem(0,14,itemBiotin);

    QTableWidgetItem *itemBiotinX = new QTableWidgetItem;
    itemBiotinX->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(1,14,itemBiotinX);

    QTableWidgetItem *itemBiotinY = new QTableWidgetItem;
    itemBiotinY->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(2,14,itemBiotinY);

    QTableWidgetItem *itemBiotinC = new QTableWidgetItem;
    itemBiotinC->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(3,14,itemBiotinC);


    QTableWidgetItem *itemReserved = new QTableWidgetItem;
    itemReserved->setTextAlignment(Qt::AlignCenter);
    itemReserved->setFlags(Qt::NoItemFlags);
    itemReserved->setText(tr("预留"));
    tableWidget->setItem(0,13,itemReserved);

    QTableWidgetItem *itemReservedX = new QTableWidgetItem;
    itemReservedX->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(1,13,itemReservedX);

    QTableWidgetItem *itemReservedY = new QTableWidgetItem;
    itemReservedY->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(2,13,itemReservedY);

    QTableWidgetItem *itemReservedC = new QTableWidgetItem;
    itemReservedC->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(3,13,itemReservedC);


    QTableWidgetItem *itemSA= new QTableWidgetItem;
    itemSA->setTextAlignment(Qt::AlignCenter);
    itemSA->setFlags(Qt::NoItemFlags);
    itemSA->setText(tr("SA磁珠"));
    tableWidget->setItem(0,12,itemSA);

    QTableWidgetItem *itemSAX= new QTableWidgetItem;
    itemSAX->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(1,12,itemSAX);

    QTableWidgetItem *itemSAY= new QTableWidgetItem;
    itemSAY->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(2,12,itemSAY);

    QTableWidgetItem *itemSAC= new QTableWidgetItem;
    itemSAC->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(3,12,itemSAC);

    QTableWidgetItem *itemSolution1 = new QTableWidgetItem;
    itemSolution1->setTextAlignment(Qt::AlignCenter);
    itemSolution1->setFlags(Qt::NoItemFlags);
    itemSolution1->setText(tr("洗涤液1"));
    tableWidget->setItem(0,11,itemSolution1);

    QTableWidgetItem *itemSolution1X = new QTableWidgetItem;
    itemSolution1X->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(1,11,itemSolution1X);

    QTableWidgetItem *itemSolution1Y = new QTableWidgetItem;
    itemSolution1Y->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(2,11,itemSolution1Y);

    QTableWidgetItem *itemSolution1C = new QTableWidgetItem;
    itemSolution1C->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(3,11,itemSolution1C);

    QTableWidgetItem *itemSolution2 = new QTableWidgetItem;
    itemSolution2->setTextAlignment(Qt::AlignCenter);
    itemSolution2->setFlags(Qt::NoItemFlags);
    itemSolution2->setText(tr("洗涤液2"));
    tableWidget->setItem(0,10,itemSolution2);

    QTableWidgetItem *itemSolution2X = new QTableWidgetItem;
    itemSolution2X->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(1,10,itemSolution2X);

    QTableWidgetItem *itemSolution2Y = new QTableWidgetItem;
    itemSolution2Y->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(2,10,itemSolution2Y);

    QTableWidgetItem *subStrateC = new QTableWidgetItem;
    subStrateC->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(3,10,subStrateC);


    QTableWidgetItem *itemSolution3 = new QTableWidgetItem;
    itemSolution3->setTextAlignment(Qt::AlignCenter);
    itemSolution3->setFlags(Qt::NoItemFlags);
    itemSolution3->setText(tr("洗涤液3"));
    tableWidget->setItem(0,9,itemSolution3);

    QTableWidgetItem *itemSolution3X = new QTableWidgetItem;
    itemSolution3X->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(1,9,itemSolution3X);

    QTableWidgetItem *itemSolution3Y = new QTableWidgetItem;
    itemSolution3Y->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(2,9,itemSolution3Y);

    QTableWidgetItem *itemSolution3C = new QTableWidgetItem;
    itemSolution3C->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(3,9,itemSolution3C);

    QTableWidgetItem *itemMotivate= new QTableWidgetItem;
    itemMotivate->setTextAlignment(Qt::AlignCenter);
    itemMotivate->setFlags(Qt::NoItemFlags);
    itemMotivate->setText(tr("激发液"));
    tableWidget->setItem(0,8,itemMotivate);

    QTableWidgetItem *itemMotivateX= new QTableWidgetItem;
    itemMotivateX->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(1,8,itemMotivateX);

    QTableWidgetItem *itemTP2Y= new QTableWidgetItem;
    itemTP2Y->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(2,8,itemTP2Y);

    QTableWidgetItem *itemMotivateC= new QTableWidgetItem;
    itemMotivateC->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(3,8,itemMotivateC);

    QTableWidgetItem *itemP_Motivate = new QTableWidgetItem;
    itemP_Motivate->setTextAlignment(Qt::AlignCenter);
    itemP_Motivate->setFlags(Qt::NoItemFlags);
    itemP_Motivate->setText(tr("预激发液"));
    tableWidget->setItem(0,7,itemP_Motivate);

    QTableWidgetItem *itemP_MotivateX = new QTableWidgetItem;
    itemP_MotivateX->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(1,7,itemP_MotivateX);

    QTableWidgetItem *itemP_MotivateY = new QTableWidgetItem;
    itemP_MotivateY->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(2,7,itemP_MotivateY);

    QTableWidgetItem *itemP_MotivateC = new QTableWidgetItem;
    itemP_MotivateC->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(3,7,itemP_MotivateC);

    QTableWidgetItem *itemTIP4 = new QTableWidgetItem;
    itemTIP4->setTextAlignment(Qt::AlignCenter);
    itemTIP4->setFlags(Qt::NoItemFlags);
    itemTIP4->setText(tr("TIP4"));
    tableWidget->setItem(0,6,itemTIP4);

    QTableWidgetItem *itemTIP4X = new QTableWidgetItem;
    itemTIP4X->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(1,6,itemTIP4X);

    QTableWidgetItem *itemTIP4Y = new QTableWidgetItem;
    itemTIP4Y->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(2,6,itemTIP4Y);

    QTableWidgetItem *itemTIP4C = new QTableWidgetItem;
    itemTIP4C->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(3,6,itemTIP4C);

    QTableWidgetItem *itemTIP3 = new QTableWidgetItem;
    itemTIP3->setTextAlignment(Qt::AlignCenter);
    itemTIP3->setFlags(Qt::NoItemFlags);
    itemTIP3->setText(tr("TIP3"));
    tableWidget->setItem(0,5,itemTIP3);

    QTableWidgetItem *itemTIP3X = new QTableWidgetItem;
    itemTIP3X->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(1,5,itemTIP3X);

    QTableWidgetItem *itemTIP3Y = new QTableWidgetItem;
    itemTIP3Y->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(2,5,itemTIP3Y);

    QTableWidgetItem *itemTIP3C = new QTableWidgetItem;
    itemTIP3C->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(3,5,itemTIP3C);


    QTableWidgetItem *itemTIP1 = new QTableWidgetItem;
    itemTIP1->setTextAlignment(Qt::AlignCenter);
    itemTIP1->setFlags(Qt::NoItemFlags);
    itemTIP1->setText(tr("TIP2"));
    tableWidget->setItem(0,4,itemTIP1);

    QTableWidgetItem *itemTIP1X = new QTableWidgetItem;
    itemTIP1X->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(1,4,itemTIP1X);

    QTableWidgetItem *itemTIP1Y = new QTableWidgetItem;
    itemTIP1Y->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(2,4,itemTIP1Y);

    QTableWidgetItem *itemTIP1C = new QTableWidgetItem;
    itemTIP1C->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(3,4,itemTIP1C);

    QTableWidgetItem *itemTIP2 = new QTableWidgetItem;
    itemTIP2->setTextAlignment(Qt::AlignCenter);
    itemTIP2->setFlags(Qt::NoItemFlags);
    itemTIP2->setText(tr("TIP1"));
    tableWidget->setItem(0,3,itemTIP2);

    QTableWidgetItem *itemTIP2X = new QTableWidgetItem;
    itemTIP2X->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(1,3,itemTIP2X);

    QTableWidgetItem *itemTIP2Y = new QTableWidgetItem;
    itemTIP2Y->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(2,3,itemTIP2Y);

    QTableWidgetItem *itemTIP2C= new QTableWidgetItem;
    itemTIP2C->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(3,3,itemTIP2C);

    QTableWidgetItem *itemWaster = new QTableWidgetItem;
    itemWaster->setTextAlignment(Qt::AlignCenter);
    itemWaster->setFlags(Qt::NoItemFlags);
    itemWaster->setText(tr("废液池"));
    tableWidget->setItem(0,2,itemWaster);

    QTableWidgetItem *itemWasterX = new QTableWidgetItem;
    itemWasterX->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(1,2,itemWasterX);

    QTableWidgetItem *itemWasterY = new QTableWidgetItem;
    itemWasterY->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(2,2,itemWasterY);

    QTableWidgetItem *itemWasterC = new QTableWidgetItem;
    itemP_MotivateC->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(3,2,itemWasterC);

    //--限制输入-----------------------------------
    for(int i=1;i<3;i++){
        for(int j=2;j<=17;j++)
        {
            QLineEdit* mle=new QLineEdit(this);
            mle->setAlignment(Qt::AlignCenter);
            mle->setStyleSheet("background:transparent;border-width:0;border-style:outset");
            /*输入限制在0，00--180.99 ***/
            QRegExp rx("^(180|([1-9]?[0-9]|1[0-7][0-9])(\\.\\d{1,2})?)$"); //^(?:[1-9][0-9]*|0)$
            mle->setValidator(new QRegExpValidator(rx,mle));
            tableWidget->setCellWidget(i,j,mle);
        }
    }
    for(int j = 2;j <= 17;j++){
        QLineEdit* mle=new QLineEdit(this);
        mle->setAlignment(Qt::AlignCenter);
        mle->setStyleSheet("background:transparent;border-width:0;border-style:outset");
        /*输入限制在1~~~2000 ***/
        QRegExp rx("^(2000)|(1\\d\\d\\d)|([1-9]\\d\\d)|([1-9]\\d)|(\\d)$"); //(2000|([1-9]?[0-9]|1[0-9][0-9][0-9]))
        mle->setValidator(new QRegExpValidator(rx,mle));
        tableWidget->setCellWidget(3,j,mle);
    }

    //--------------------------------------
}

/**
 * @brief 信号槽绑定
 */
void standardPragrameWidget::connectInit()
{
    connect(reagentPromWidget,SIGNAL(SaveBtnPress_Sign()),this,SLOT(SaveBtnPressSlot()));//试剂船保存按钮
    connect(reagentPromWidget,SIGNAL(OpenBtnSignal()),this,SLOT(OpenBtnSlot()));//试剂船保存按钮
    connect(&serialPort::ReceiveThread,SIGNAL(reagent_programe_cmdSign(QString)),this,SLOT(reagent_programe_cmdSignSlot(QString)),Qt::DirectConnection);
    connect(reagentPromWidget->actionProTabelView,SIGNAL(stepRunBtnSignal(int)),this,SLOT(stepRunBtnSignalSlot(int))); //试剂船单步运行信号槽
    connect(reagentPromWidget,SIGNAL(startBtnSignal()),this,SLOT(StartBtnSignalSlot())); //试剂船全速运行按钮信号和槽绑定
}

/**
 * @brief 设置reagentdisplay.h里面的workPA信息
 * @param startTime
 * @param endTime
 * @param stage
 * @param progressValue
 */
void standardPragrameWidget::setWorkPaINFO(const QString &startTime, const QString &endTime, const QString &stage, int progressValue)
{
    reagentdisplay->workPA->Lvalue_stage->setText(stage);
    reagentdisplay->workPA->Lvalue_start_time->setText(startTime);
    reagentdisplay->workPA->Lvalue_end_time->setText(endTime);
    reagentdisplay->workPA->RoundPB->setValue(progressValue);
}

/**
 * @brief 全速运行时当前进度和时间返回码
 * @param 命令字符串
 */
void standardPragrameWidget::allRunProgressHandle(QByteArray &data)
{
    unsigned char num = data.at(6)&0xff; //返回进度数量
    unsigned char postion = data.at(7)&0xff; //当前槽号

    QString startTime;
    QString endTime;
    QString currentStage; //当前阶段
    if(num > 1){
        emit serialPort::ReceiveThread.ErrDataSign("试剂船全速运行只能插入一个试剂船");
        return;
    }
    switch( data.at(8) & 0xff )
    {
    case 1:
        currentStage = "取反应管";
        break;
    case 2:
        currentStage = "取Tap头1";
        break;
    case 3:
        currentStage = "加样本";
        break;
    case 4:
        currentStage = "加试剂1";
        break;
    case 5:
        currentStage = "加试剂2";
        break;
    case 6:
        currentStage = "温育";
        break;
    case 7:
        currentStage = "加磁珠";
        break;
    case 8:
        currentStage = "温育";
        break;
    case 9:
        currentStage = "加试剂3";
        break;
    case 10:
        currentStage = "温育";
        break;
    case 11:
        currentStage = "取Tap头2";
        break;
    case 12:
        currentStage = "第一次洗涤";
        break;
    case 13:
        currentStage = "第二次洗涤";
        break;
    case 14:
        currentStage = "第三次洗涤";
        break;
    case 15:
        currentStage = "移动反应管进发光孔";
        break;
        break;
    case 16:
        currentStage = "取Tap头3";
        break;
    case 17:
        currentStage = "加预激发液";
        break;
    case 18:
        currentStage = "取Tap头4";
        break;
    case 19:
        currentStage = "加激发液发光";
        break;
    }
    unsigned short int start_year = ((unsigned short int)(data.at(10)&0xff) << 8) | data.at(11)&0xff;
    unsigned char start_month = data.at(12) & 0xff;
    unsigned char start_day = data.at(13) & 0xff;
    unsigned char start_hour = data.at(14) & 0xff;
    unsigned char start_minute = data.at(15) & 0xff;
    unsigned char start_second = data.at(16) & 0xff;

    unsigned char progressData = data.at(9) & 0xff; //进度
    unsigned short int end_year = ((unsigned short int)(data.at(17)&0xff) << 8) | data.at(18)&0xff;
    unsigned char end_month = data.at(19) & 0xff;
    unsigned char end_day = data.at(20) & 0xff;
    unsigned char end_hour =data.at(21) & 0xff;
    unsigned char end_minute = data.at(22) & 0xff;
    unsigned char end_second = data.at(23) & 0xff;

    startTime += (QString::number(start_year,10) + "/" + QString::number(start_month,10) + "/" + QString::number(start_day,10) +" "
                  +QString::number(start_hour,10) + ":"+QString::number(start_minute,10)+":"+QString::number(start_second,10)  );
    endTime += (QString::number(end_year,10) + "/" + QString::number(end_month,10) + "/" + QString::number(end_day,10) +" "
                +QString::number(end_hour,10) + ":"+QString::number(end_minute,10)+":"+QString::number(end_second,10)  );

    setWorkPaINFO(startTime,endTime,currentStage,progressData);
    if( progressData ){
        reagentPromWidget->standardPrograme_mode = reagentPromWidget->PRO_STOP;  //如果当前进度为100时，将当前状态作为停止
    }
}

/**
 * @brief 单步运行时间返回码处理函数
 * @param 命令字符串
 */
void standardPragrameWidget::stepRunTimeHandle(QByteArray &data)
{
    int num = data.at(6)&0xff; //返回槽号
    unsigned char step = (data.at(7)&0xff )-1; //返回步骤号
    unsigned short int runTime =  ( (unsigned short int ) (data.at(8) & 0xff ) <<8 )  |  data.at(9) & 0xff;
    QString stepTime = QString::number(runTime,10);
    qDebug() << "当前运行步骤" <<step;
    qDebug() << "当前试剂单步运行时间" << runTime;
    reagentPromWidget->actionProTabelView->model->setData( reagentPromWidget->actionProTabelView->model->index(step,16),QVariant(stepTime));
    reagentPromWidget->actionProTabelView->tableView->reset();
}

void standardPragrameWidget::tableProjectWidgetInit()
{

    tableProjectWidget = new QTableWidget(this);
    tableProjectWidget->setColumnCount(16);//10-->16
    tableProjectWidget->setRowCount(1);
    tableProjectWidget->horizontalHeader()->hide();
    tableProjectWidget->verticalHeader()->hide();
    tableProjectWidget->setStyleSheet("gridline-color: rgb(0, 139, 139);selection-background-color:lightblue;");
    tableProjectWidget->setColumnWidth(0,TABLE_NAME_WIDTH);
    tableProjectWidget->setColumnWidth(1,TABLE_EDIT_WIDTH);
    tableProjectWidget->setColumnWidth(2,TABLE_NAME_WIDTH);
    tableProjectWidget->setColumnWidth(3,TABLE_EDIT_WIDTH);
    tableProjectWidget->setColumnWidth(4,TABLE_NAME_WIDTH);
    tableProjectWidget->setColumnWidth(5,TABLE_EDIT_WIDTH);

    tableProjectWidget->setColumnWidth(6,TABLE_NAME_WIDTH+10);
    tableProjectWidget->setColumnWidth(7,TABLE_EDIT_WIDTH-10);

    tableProjectWidget->setColumnWidth(8,TABLE_NAME_WIDTH+10);
    tableProjectWidget->setColumnWidth(9,TABLE_EDIT_WIDTH-10);

    tableProjectWidget->setColumnWidth(10,TABLE_NAME_WIDTH);
    tableProjectWidget->setColumnWidth(11,TABLE_EDIT_WIDTH);
    tableProjectWidget->setColumnWidth(12,TABLE_NAME_WIDTH+10);
    tableProjectWidget->setColumnWidth(13,TABLE_EDIT_WIDTH-10);
    tableProjectWidget->setColumnWidth(14,TABLE_NAME_WIDTH+10);
    tableProjectWidget->setColumnWidth(15,TABLE_EDIT_WIDTH);

    tableProjectWidget->setRowHeight(0,TABLE_HIGH);
    tableProjectWidget->setFixedSize(1652,32);

    QTableWidgetItem *itemName0 = new QTableWidgetItem;
    itemName0->setFlags(Qt::NoItemFlags);
    itemName0->setTextAlignment(Qt::AlignCenter);
    itemName0->setText(tr("品类:"));
    tableProjectWidget->setItem(0,0,itemName0);


    DatabaseOperation op;
    QSqlQueryModel model;
    op.selectCategoryAll(model);//model中只有品类名称
    cmbx_type = new QComboBox(this);cmbx_type->setStyleSheet("background-color:white");
    for(int i=0;i<model.rowCount();i++)cmbx_type->insertItem(i,model.index(i,0).data().toString());
    tableProjectWidget->setCellWidget(0,1,cmbx_type);

    QTableWidgetItem *itemName2 = new QTableWidgetItem;
    itemName2->setFlags(Qt::NoItemFlags);
    itemName2->setTextAlignment(Qt::AlignCenter);
    itemName2->setText(tr("项目名称:"));
    tableProjectWidget->setItem(0,2,itemName2);

    op.selectProject_nameByCategory(cmbx_type->currentText(),model);//model中只有品类名称
    cmbx_fileName= new QComboBox(this);cmbx_fileName->setStyleSheet("background-color:white");
    for(int i=0;i<model.rowCount();i++)cmbx_fileName->insertItem(i,model.index(i,0).data().toString());
    tableProjectWidget->setCellWidget(0,3,cmbx_fileName);

    QTableWidgetItem *itemName4 = new QTableWidgetItem;
    itemName4->setFlags(Qt::NoItemFlags);
    itemName4->setTextAlignment(Qt::AlignCenter);
    itemName4->setText(tr("项目试剂:"));
    tableProjectWidget->setItem(0,4,itemName4);

    op.selectReagent_typeByProject_name(cmbx_type->currentText(),cmbx_fileName->currentText(),model);
    cmbx_fileSN = new QComboBox(this);
    for(int i=0;i<model.rowCount();i++)cmbx_fileSN->insertItem(i,model.index(i,0).data().toString());
    cmbx_fileSN->setEditable(1);
    tableProjectWidget->setCellWidget(0,5,cmbx_fileSN);


    QTableWidgetItem *itemName5 = new QTableWidgetItem;
    itemName5->setTextAlignment(Qt::AlignCenter);
    tableProjectWidget->setItem(0,5,itemName5);

    dateEdit_start_time = new QDateEdit(this);
    dateEdit_start_time->setDisplayFormat("yyyy/MM");
    dateEdit_start_time->setCalendarPopup(0);//不弹出
    dateEdit_start_time->setMinimumDate(QDate(2018,01,01));
    dateEdit_start_time->setMaximumDate(QDate(2053,12,31 ));
    dateEdit_start_time->setDate(QDate::currentDate());


//    dateEdit_end_time = new QDateEdit(this);
//    dateEdit_end_time->setCalendarPopup(true);

    QTableWidgetItem *itemName6 = new QTableWidgetItem;
    itemName6->setFlags(Qt::NoItemFlags);
    itemName6->setTextAlignment(Qt::AlignCenter);
    itemName6->setText(tr("生产时间:"));
    tableProjectWidget->setItem(0,6,itemName6);



    tableProjectWidget->setCellWidget(0,7,dateEdit_start_time);

    QTableWidgetItem *itemName8 = new QTableWidgetItem;
    itemName8->setFlags(Qt::NoItemFlags);
    itemName8->setTextAlignment(Qt::AlignCenter);
    itemName8->setText(tr("批号:"));
    tableProjectWidget->setItem(0,8,itemName8);


    cmbx_numberPH = new QComboBox(this);cmbx_numberPH->setStyleSheet("background-color:white");
    for(int i=0;i<15;i++)
    {
        if(i<=8)
            cmbx_numberPH->insertItem(i,"0"+QString::number(i+1)+"批");
        else
            cmbx_numberPH->insertItem(i,QString::number(i+1)+"批");
    }

    tableProjectWidget->setCellWidget(0,9,cmbx_numberPH);


    QTableWidgetItem *itemName10 = new QTableWidgetItem;
    itemName10->setFlags(Qt::NoItemFlags);
    itemName10->setTextAlignment(Qt::AlignCenter);
    itemName10->setText(tr("有效期:"));
    tableProjectWidget->setItem(0,10,itemName10);

    cmbx_POV = new QComboBox(this);cmbx_POV->setStyleSheet("background-color:white");
    cmbx_POV->insertItem(0,"6个月");cmbx_POV->insertItem(1,"12个月");
    tableProjectWidget->setCellWidget(0,11,cmbx_POV);


    QTableWidgetItem *itemName12 = new QTableWidgetItem;
    itemName12->setFlags(Qt::NoItemFlags);
    itemName12->setTextAlignment(Qt::AlignCenter);
    itemName12->setText(tr("预留:"));
    tableProjectWidget->setItem(0,12,itemName12);

    itemName13 = new QTableWidgetItem;
    itemName13->setFlags(Qt::NoItemFlags);
    itemName13->setTextAlignment(Qt::AlignCenter);
    tableProjectWidget->setItem(0,13,itemName13);


    QTableWidgetItem *itemName14 = new QTableWidgetItem;
    itemName14->setFlags(Qt::NoItemFlags);
    itemName14->setTextAlignment(Qt::AlignCenter);
    itemName14->setText(tr("条码:"));
    tableProjectWidget->setItem(0,14,itemName14);

    //在槽中使用itemName15
    itemName15 = new QTableWidgetItem;
    itemName15->setFlags(Qt::NoItemFlags);
    itemName15->setTextAlignment(Qt::AlignCenter);
    tableProjectWidget->setItem(0,15,itemName15);

    //信号槽，发送信号
    connect(cmbx_numberPH,SIGNAL(currentIndexChanged(QString)),this,SLOT(slot_send_signal_autoGenerateNumer(QString)));
    connect(cmbx_POV,SIGNAL(currentIndexChanged(QString)),this,SLOT(slot_send_signal_autoGenerateNumer(QString)));
    connect(cmbx_fileSN,SIGNAL(currentIndexChanged(QString)),this,SLOT(slot_send_signal_autoGenerateNumer(QString)));

    connect(dateEdit_start_time,SIGNAL(dateChanged(QDate)),this,SLOT(slot_send_signal_autoGenerateNumer(QDate)));

    //执行槽
    connect(this,SIGNAL(signal_refreshNumber()),this,SLOT(slot_autoGenerateNumer()));

    //刷新机制
    connect(cmbx_type,SIGNAL(currentIndexChanged(QString)),this,SLOT(slot_RefreshComoBox_FileName_And_SN(QString)));
    connect(cmbx_fileName,SIGNAL(currentIndexChanged(QString)),this,SLOT(slot_RefreshComoBox__SN(QString)));


}
void standardPragrameWidget::slot_autoGenerateNumer()
{
    qDebug()<<"刷新条码";
    /*
        试剂的品类，占一位，用数字表示，目前暂定4种：
        0—质控品；
        1—校验品；
        2—标准品；
        3—实测样本；
    */
    DatabaseOperation op;
    QSqlQueryModel model;

    op.selectCategory_codeByCategory(cmbx_type->currentText(),model);
    QString TM1 = model.index(0,0).data().toString();//品类
    //qDebug()<<TM1<<TM1.length();

    /*
        项目试剂，占三位，其中第一位表示项目名称，后两位表示试剂种类，用数字表示：
        第一位：0—重症感染类、1—心肌类、2—生化类、3—蛋白类、F—其他类；
        000—PCT、001—IL-6、002—IL-10、003—TNF-α、004—sTREM1、005—sHLA-DR、006—suPAR、007—CRP；
    */
    op.selectProject_name_codeByProject_name(cmbx_type->currentText(),cmbx_fileName->currentText(),model);
    QString TM2=model.index(0,0).data().toString();
    //qDebug()<<TM2<<TM2.length();

    op.selectReagent_type_codeByReagent_type(cmbx_type->currentText(),cmbx_fileName->currentText(),cmbx_fileSN->currentText(),model);
    QString TM34=model.index(0,0).data().toString();
    //qDebug()<<TM34<<TM34.length();
    /*
        试剂生产年份，占一位，用数字或字母表示，目前暂定20种：
        0—18年、1—19年、2—20年、3—21年、4—22年、5—23年、6—24年、7—25年、8—26年、9—27年、A—28年、B—29年、C—30年、D—31年、E—32年、F—33年、G—34年、H—35年、J—36年、K—37年；
    */
    QString year=dateEdit_start_time->date().toString("yyyy");//2018
    int Tyear=year.toInt();
    char Cyear=char(Tyear-2018);//0~9(48~57)   A~Z(65~90)


    if(Cyear<0)
    {
        Cyear='*';
    }
    else if(Cyear<=9)
    {
        Cyear+=48;//0->48
    }
    else
    {
        Cyear+=55;//10->65
    }
    /*
        试剂生产月份，占一位，用数字或字母表示，共12种：
        1—1月、2—2月、3—3月、4—4月、5—5月、6—6月、7—7月、8—8月、9—9月、A—10、B—11月、C—12月；
    */
    QString month=dateEdit_start_time->date().toString("MM");//05
    int Tmonth=month.toInt();
    char Cmonth=char(Tmonth);
    if(Cmonth<=9)
    {
        Cmonth+=48;//0->48
    }
    else
    {
        Cmonth+=55;//10->65
    }

    /*
        批号，占一位，用数字或字母表示，目前暂定15种：
        1—01批、2—02批、3—03批、4—04批、5—05批、6—06批、7—07批、8—08批、9—09批、A—10批、B—11批、C—12批、D—13批、E—14批、F—15批；
    */
    char Cph=cmbx_numberPH->currentIndex()+1;
    if(Cph<=9)
    {
        Cph+=48;//0->48
    }
    else
    {
        Cph+=55;//10->65
    }

    /*
        试剂保质期，占一位，用数字或字母表示，目前暂定2种：
        6—6个月、C—12个月；
    */
    char Cpov;
    if(cmbx_POV->currentIndex()==0)//6个月
    {
        Cpov='6';
    }
    else
    {
        Cpov='C';
    }

    /*
        预留，占三位，随机生成；
    */
    QString yuliu="000";

    char str[5]="";str[0]=Cyear;str[1]=Cmonth;str[2]=Cph;str[3]=Cpov;str[4]=0;
    QString NumberTM=TM1+TM2+TM34+str+yuliu;

    itemName15->setText(NumberTM);
}

void standardPragrameWidget::slot_send_signal_autoGenerateNumer(QDate date)
{
    Q_UNUSED(date)
    emit signal_refreshNumber();
}

void standardPragrameWidget::slot_send_signal_autoGenerateNumer(QString text)
{
    Q_UNUSED(text)
    emit signal_refreshNumber();

}

/**
 * @brief 判断项目信息表信息是否完整
 * @return
 */
bool standardPragrameWidget::ProjectInfoIsEmpty()
{

    if(
            tableProjectWidget->item(0,1)->text().isEmpty() //文件名称
            || tableProjectWidget->item(0,3)->text().isEmpty()//文件名简写
            // || tableProjectWidget->item(0,5)->text().isEmpty()//条码图像
            )
    {
        qDebug() << "项目信息不完整";
        return true;
    }
    return false;//K添加
}

/**
 * @brief standardPragrameWidge::判断勾选是否少于参数定义的数量
 * @param num：至少选择步骤数
 * @return
 */
bool standardPragrameWidget::TabelView_CheckBoxnum_IsLessThanNumber(int num)
{
    int counter=0;
    for(int i=0;i<19;i++)
    {
        if(reagentPromWidget->actionProTabelView->model->index(i,0).data().toInt())
            counter++;
    }
    if(counter<num)
        return true;
    return false;
}


/**
 * @brief 获取当前试剂船运动全部实际发送数据
 * @return 当前试剂船项目试剂数据字符串
 */
QString standardPragrameWidget::getProAllInfo()
{
    QString strdata = "";  //临时储存发送数据内容
    QString strcmd = "";  //返回字符串
    QString postion = ""; //存储临时步骤代码
    unsigned char start_postion = 0;
    unsigned char end_postion = 0;
    for(int i = 1;i <=19; i++){
        if(reagentPromWidget->actionProTabelView->model->index(i-1,0).data().toInt()){
            strdata = reagentPromWidget->actionProTabelView->getStepData(i-0);
            start_postion = strdata.mid(42,2).toInt();
            end_postion = strdata.mid(66,2).toInt();
            if( start_postion ){
                strdata.replace(21,23,getX_Y_Value(start_postion));
            }
            if( end_postion ){
                strdata.replace(43,23,getX_Y_Value(end_postion));
            }
            qDebug() << "当前第" << i << "步被选择 " << strdata;

            strcmd += strdata.remove(0,17);
            qDebug() << "当前数据内容 " << strdata;
        }

    }
    qDebug() << "当前数据内容 " << strcmd;
    return strcmd;
}


/**
 * @brief 试剂船全速运行按钮信号槽，用于直接发送连续运行数据去下位机
 */
void standardPragrameWidget::StartBtnSignalSlot()
{
    QString strcmd = "02,06,ff,ff,00,00"; //待发送的数据
    if( tableWidgetIsEmpty() ){   //判断当前试剂船各位置是否编辑完整
        qDebug() << "当前试剂船信息不完整";
        if( QMessageBox::critical(this,tr("提示"),tr("当前试剂船编辑信息表不完整，请填写完整!")) == QMessageBox::Ok){
            return;
        }
    }
    strcmd += getProAllInfo();
    if( strcmd.length() < 25 ){ //判断当前是否勾选操作步骤了
        if( QMessageBox::critical(this,tr("提示"),tr("当前没有选择任何步骤，请选择步骤!")) == QMessageBox::Ok){
            return;
        }
    }
    qDebug()<< "全速运行" << strcmd;
    reagentPromWidget->WorkQueue->enqueue(strcmd);
}



/**
 * @brief 试剂内容是否为空
 * @return
 */
bool standardPragrameWidget::tableWidgetIsEmpty()
{
    bool X_PosFlag = false; //X位置有为空
    bool Y_PosFlag = false; //Y位置有为空
    bool CapFlag = false;   //容量有为空

    //X轴坐标是有空
    for(int i = 2; i< 18;i++)
    {
        if( ((QLineEdit *)( tableWidget->cellWidget(1,i)))->text().isEmpty() ){
            X_PosFlag = true;
            break;
        }
    }
    // Y坐标是有空
    for(int i = 2; i< 18;i++)
    {
        if(((QLineEdit *)( tableWidget->cellWidget(2,i)))->text().isEmpty()){
            Y_PosFlag = true;
            break;
        }
    }
    //容量是否有空
    for(int i = 2; i< 18;i++)
    {
        if(((QLineEdit *)( tableWidget->cellWidget(3,i)))->text().isEmpty()){
            CapFlag = true;
            break;
        }
    }
    if(X_PosFlag || Y_PosFlag || CapFlag){
        return true;
    }
    return false;
}
/**
 * @brief SaveBtnPressSlot
 */
void standardPragrameWidget::SaveBtnPressSlot()
{
    QWaitDialog* wd = new QWaitDialog(this,"正在保存，请耐心等待！");//保存功能的等待界面

    qDebug()<<"点击保存按钮";
    //1.1数据准备
    QString CATEGORY        =   cmbx_type->currentText();                       //质控品 标准品 校验品
    QString PROJECT_NAME    =   cmbx_fileName->currentText();                   //重症感冒类。。。
    QString REAGENT_TYPE    =   cmbx_fileSN->currentText();                     //PCT ...
    QString PRODUCTION_TIME =   dateEdit_start_time->date().toString("yyyy/MM");//生产时间
    int BACH_NUMBER         =   cmbx_numberPH->currentIndex()+1;                //01批 对应 0
    int QUALITY_TIME        =   (cmbx_POV->currentIndex()+1)*6;                 //(i+1)*6  有6和12个月
    QString RESERVE         =   tableProjectWidget->item(0,13)->text();         //预留
    QString BAR_CODE        =   itemName15->text();                             //条码

    QStringList strlist ;

    QString STANDARD_CODE = BAR_CODE.mid(0,7);
    QString ACTION_CODE =   STANDARD_CODE;
    qDebug()<<"@@@1168";
    /*****************************************************/
    QString RUN_DATA = getProAllInfo();//待发送的到下位机的当前试剂有运行的全部数据
    /*****************************************************/
    ConfigFile cp;
    QString Currentpeople_ID =cp.getCurrentUser_Name();
    QString Currentpeople_TIME =QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    qDebug()<<"@@@1175";
    for(int column = 2;column < 18; column++){
        for(int row = 1;row < 4;row++)
        {
            strlist.append( ((QLineEdit*)(tableWidget->cellWidget(row,column)))->text());
            // qDebug()<<"row="<<row<<"column="<<column<<((QLineEdit*)(tableWidget->cellWidget(row,column)))->text();
        }
    }
    qDebug()<<"@@@1183";
    //1.2判空

    bool ret=tableWidgetIsEmpty();//表2，有未填写的内容，则返回真
    if(ret){QMessageBox::critical(this,tr("提示"),tr("试剂船编辑信息表内容不完整，请填写完整!"));return;}

    ret=TabelView_CheckBoxnum_IsLessThanNumber(1);//表3，勾选少于1步，则返回真
    if(ret){QMessageBox::critical(this,tr("提示"),tr("详细步骤勾选的步骤少于1步，请务必勾选!"));return;}

    qDebug()<<"@@@1192";
    //1.3判重
    ret=false;//不存在
    DataOpration op;
    if(op.isExist_reagentInfo(STANDARD_CODE)) //表2数据已存在（已经有了创建者）
    {
        ret=true;//更新操作
        QString msg="唯一关键字:"+STANDARD_CODE+" 的数据已存在，请决定是否更新?";
        myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_QUESTION,tr("提示"),msg,this);
        if(messge->exec() == QDialog::Accepted)
        {
        }
        else
        {
            qDebug()<<"放弃更新!";
            return;
        }
    }
    else //数据不存在
    {
    }
    //1.4写入数据库
    qDebug()<<"----开始sql-----";
    wd->move(0,0);
    if(!ret)//此标志在此处，记录查重结果（true 存在，false 不存在）
    {

        op.insertData_reagentInfo(CATEGORY,PROJECT_NAME,REAGENT_TYPE,PRODUCTION_TIME,BACH_NUMBER,QUALITY_TIME,RESERVE,BAR_CODE,strlist,STANDARD_CODE,ACTION_CODE,RUN_DATA,Currentpeople_ID,Currentpeople_TIME,"无","无",0);
    }
    else
    {
        op.updateData_reagentInfo(CATEGORY,PROJECT_NAME,REAGENT_TYPE,PRODUCTION_TIME,BACH_NUMBER,QUALITY_TIME,RESERVE,BAR_CODE,strlist,STANDARD_CODE,ACTION_CODE,RUN_DATA,Currentpeople_ID,Currentpeople_TIME,0);
    }
    qDebug()<<"@@@1225";
    //2.1数据准备
    int STEP_num;
    QString STEP_name;
    QString START_POSTION;
    QString PUT_IN_POSTION;
    int TIME;
    int BEFORE_BLEND_COUNT;
    int AFTER_BLEND_COUNT;
    int CAPACITY;
    int STEP_TIME;
    int CHOOSE_FLAG;

    for(int i=0;i<19;i++)
    {
        qDebug()<<"@@@------ "<<i+1<<" --------@@@";
        STEP_num=i+1;
        STEP_name=reagentPromWidget->actionProTabelView->model->index(i,2).data().toString();
        START_POSTION=reagentPromWidget->actionProTabelView->model->index(i,4).data().toString();
        PUT_IN_POSTION=reagentPromWidget->actionProTabelView->model->index(i,6).data().toString();
        TIME=reagentPromWidget->actionProTabelView->model->index(i,8).data().toInt();
        BEFORE_BLEND_COUNT=reagentPromWidget->actionProTabelView->model->index(i,10).data().toInt();
        AFTER_BLEND_COUNT=reagentPromWidget->actionProTabelView->model->index(i,12).data().toInt();
        CAPACITY=reagentPromWidget->actionProTabelView->model->index(i,14).data().toInt();
        STEP_TIME=reagentPromWidget->actionProTabelView->model->index(i,16).data().toInt();
        CHOOSE_FLAG=reagentPromWidget->actionProTabelView->model->index(i,0).data().toInt();

        if(!op.isExist_reagentMovement(STEP_num,ACTION_CODE))
        {
            op.insertData_reagentMovement(CHOOSE_FLAG,ACTION_CODE,STEP_num,STEP_name,START_POSTION,
                                             PUT_IN_POSTION,TIME,BEFORE_BLEND_COUNT, AFTER_BLEND_COUNT,
                                             CAPACITY,STEP_TIME,Currentpeople_ID,Currentpeople_TIME,"无","无",0);
        }
        else
        {
            op.updateData_reagentMovement(CHOOSE_FLAG,ACTION_CODE,STEP_num,START_POSTION,
                                             PUT_IN_POSTION,TIME,BEFORE_BLEND_COUNT, AFTER_BLEND_COUNT,
                                             CAPACITY,STEP_TIME,Currentpeople_ID,Currentpeople_TIME,0);

        }
    }
    qDebug()<<"@@@1266";
    delete wd; //析构 -- 等待灰色界面 （不可去除）

    //    }
}
/**
 * @brief standardPragrameWidget::OpenBtnSlot
 *  打开按钮信号槽
 */
void standardPragrameWidget::OpenBtnSlot()
{
    StandardProgrameInfoDialog *dialog = new StandardProgrameInfoDialog(this);
    dialog->show();
    connect(dialog,SIGNAL(OpenStandardInfo(QString&)),this,SLOT(DataToWindow(QString&)));

}

void standardPragrameWidget::DataToWindow(QString &ACTION_CODE)
{
    qDebug()<<"ACTION_CODE= "<<ACTION_CODE <<" 的数据调用出来";
    DataOpration dp;
    QSqlQueryModel model;
    //表1数据设置
    //数据准备
    dp.select_reagentInfo(ACTION_CODE,model);//将查询结果保存在model中
    //int column=model.columnCount();
    //int ID = model.data(model.index(0,0)).toInt();
    QString CATEGORY        =   model.data(model.index(0,1)).toString();                       //质控品 标准品 校验品
    QString PROJECT_NAME    =   model.data(model.index(0,2)).toString();                   //重症感冒类。。。
    QString REAGENT_TYPE    =   model.data(model.index(0,3)).toString();                     //PCT ...
    QString PRODUCTION_TIME =   model.data(model.index(0,4)).toString();            //生产时间
    int BACH_NUMBER         =   model.data(model.index(0,5)).toInt();                //01批 对应 0
    int QUALITY_TIME        =   model.data(model.index(0,6)).toInt();                 //(i+1)*6  有6和12个月
    QString RESERVE         =   model.data(model.index(0,7)).toString();         //预留
    QString BAR_CODE        =   model.data(model.index(0,8)).toString();                             //条码
    qDebug()<<"结束表1数据准备";


    //数据写入
    cmbx_type->setCurrentText(CATEGORY);
    cmbx_fileName->setCurrentText(PROJECT_NAME);
    cmbx_fileSN->setCurrentText(REAGENT_TYPE);
    dateEdit_start_time->setDate(QDate::fromString(PRODUCTION_TIME,"yyyy/MM"));
    qDebug()<<"@@@1497";
    cmbx_numberPH->setCurrentIndex(BACH_NUMBER-1);
    cmbx_POV->setCurrentIndex((QUALITY_TIME/6)-1);
    qDebug()<<"@@@1500";
    itemName13->setText(RESERVE);
    qDebug()<<"@@@1502";
    itemName15->setText(BAR_CODE);
    qDebug()<<"结束表1数据写入";
    //表2数据设置 1+8+3*16
    int tempCounter=0;
    for(int column = 2;column < 18; column++)
        for(int row = 1;row < 4;row++)
            ((QLineEdit*)(tableWidget->cellWidget(row,column)))->setText(model.data(model.index(0,9+tempCounter++)).toString());
    qDebug()<<"结束表2数据写入";


    //表3数据设置
    dp.select_reagentMovement(ACTION_CODE,model);//得到的是二维表
    //  int columnNumber=model.columnCount();
    int rowNumber=model.rowCount();
    QAbstractItemModel* tablemodel=reagentPromWidget->actionProTabelView->tableView->model();
    qDebug()<<rowNumber;
    for(int i=0;i<rowNumber;i++)//
    {
        qDebug()<<"------>"<<i;
        //checkbox
        bool checkstatus=model.data(model.index(i,1)).toBool();     //CHOOSE_FLAG
        //ACTION_CODE
        int Step_num=model.data(model.index(i,3)).toInt()-1;        //STEP_NUM

        tablemodel->setData(tablemodel->index(Step_num,0),QVariant(checkstatus));//0

        //步骤名称
        //2

        //起始位置 ComboBox
        QString START_POSTION=model.data(model.index(i,5)).toString();//START_POSTION
        tablemodel->setData(tablemodel->index(Step_num,4),QVariant(START_POSTION));//4

        //放置位置 ComboBox
        QString PUT_IN_POSTION=model.data(model.index(i,6)).toString();
        tablemodel->setData(tablemodel->index(Step_num,6),QVariant(PUT_IN_POSTION));//6
        //温玉时间 int
        int TIME = model.data(model.index(i,7)).toInt();
        tablemodel->setData(tablemodel->index(Step_num,8),QVariant(TIME));          //8
        //前序混浴次数
        QString BEFORE_BLEND_COUNT = model.data(model.index(i,8)).toString();
        tablemodel->setData(tablemodel->index(Step_num,10),QVariant(BEFORE_BLEND_COUNT));//10

        //后序混匀次数
        QString AFTER_BLEND_COUNT = model.data(model.index(i,9)).toString();
        tablemodel->setData(tablemodel->index(Step_num,12),QVariant(AFTER_BLEND_COUNT));//12

        //试剂量  int
        int CAPACITY =  model.data(model.index(i,10)).toInt();
        tablemodel->setData(tablemodel->index(Step_num,14),QVariant(CAPACITY));//14
        //所需时间 int
        int STEP_TIME =  model.data(model.index(i,11)).toInt();
        tablemodel->setData(tablemodel->index(Step_num,16),QVariant(STEP_TIME));//16

    }




}

/**
 * @brief 全速试剂船编辑信号槽
 * @param str
 */
void standardPragrameWidget::reagent_programe_cmdSignSlot(QString str)
{
    QByteArray Receive_array = 0;
    QString returnCMD = "";
    int postion = 0;
    qDebug()<<"信号槽线程ID = " <<QThread::currentThreadId();
    qDebug() << "未知品收到一条命令" << str;
    Receive_array = serialPort::HEXStringToArr(str);
    uint16_t dataLength = (uint16_t)(((Receive_array.at(4)&0xffff)<< 8)|(Receive_array.at(5)&0xff));//数据长度
    unsigned char cmd = (Receive_array.at(1) & 0xff); //命令
    /****************************************************************************/
    //MCU返回码命令解析
    if( ( Receive_array.at(0) & 0xff) & 0x40 ){
        switch(cmd){
        case REA_ALL_WHETHER_FREE_RETURN_CMD:
            qDebug()<< "试剂船编辑收到MCU空闲命令返回";
            if( !( Receive_array.at(6) & 0xff ) ){ //判断是否空闲
                qDebug() << "是空闲命令";
                if( !reagentPromWidget->WorkQueue->isEmpty()){ /**<发送任务队列队首 */
                    QString str;
                    reagentPromWidget->WorkQueue->dequeue(str);
                    qDebug() << "队列字符串"<< str;
                    emit serialPort::ReceiveThread.sendDataSign(str);
                }
            }else qDebug() << "是忙命令";
            break;
        case REA_ALL_WHEHTER_SCHED_RETURN_CMD:
            qDebug()<< "试剂船编辑收到MCU可不可以调度命令返回";
            if( (Receive_array.at(6) & 0xff) ){ //判断是否空闲
                qDebug() << "是不可调度命令";
            }else qDebug() << "是可调度命令";
            break;
        }
        return;
    }

    /*****************MCU主动发送的命令解析************************************************/
    switch(cmd){
    case REA_ALL_RUN_PULL_SHIP_CMD:
        qDebug()<< "试剂船编辑收到MCU有试剂船拔出命令";
        postion = Receive_array.at(6)&0xff;
        returnCMD = "02,02,ff,ff,00,02,"+QString::number(postion,10)+",02"; //
        emit serialPort::ReceiveThread.sendDataSign(returnCMD);
        break;
    case REA_ALL_RUN_ALL_TEST_PROGRESS_CMD:
        qDebug()<< "试剂船编辑收到所有试剂船进度MCU命令";
        if( dataLength != 18){
            //插入错误数据表
            qDebug() << "试剂船编辑收到所有试剂船进度MCU命令长度不对";
            emit serialPort::ReceiveThread.ErrDataSign("数据长度不对");
            return;
        }
        allRunProgressHandle(Receive_array);
        break;
    case REA_ALL_RUN_ERR_CMD:


        qDebug()<< "试剂船编辑收到错误信息MCU命令";
        break;
    case REA_ALL_RUN_NEW_SHIP_INFOR_CMD:
        qDebug()<< "试剂船编辑收到一条插入新试剂船信息";
        postion = Receive_array.at(6)&0xff;
        returnCMD = "02,01,ff,ff,00,02,"+QString::number(postion,10)+",00";
        emit serialPort::ReceiveThread.sendDataSign(returnCMD);
        break;
    case REA_ALL_RUN_ONE_TEST_DATA_CMD:
        qDebug()<< "试剂船编辑某一条试剂测试结果信息";
        postion = Receive_array.at(6)&0xff;
        returnCMD = "02,01,ff,ff,00,02,"+QString::number(postion,10)+",02"; //红灯灭
        emit serialPort::ReceiveThread.sendDataSign(returnCMD);

        returnCMD = "02,02,ff,ff,00,02,"+QString::number(postion,10)+",01"; //绿灯闪
        emit serialPort::ReceiveThread.sendDataSign(returnCMD);
        /**
  ** 处理测试结果
  **/
        break;

    case REAGENT_STEP_PROGRESS_CMD:
        qDebug()<< "试剂船编辑单步进度信息";
        if( dataLength != 4){
            //插入错误数据表
            qDebug() << "试剂船编辑收到单步试剂船进度MCU命令长度不对";
            emit serialPort::ReceiveThread.ErrDataSign("数据长度不对");
            return;
        }
        stepRunTimeHandle(Receive_array);
        break;
    case REAGENT_STEP_FINISH_CMD:
        qDebug()<< "试剂船编辑单步运行结束";
        break;
    }
}


/**
 * @brief 设备单步运行
 * @param step
 */
void standardPragrameWidget::stepRunBtnSignalSlot(int step)
{
    QString strcmd;
    unsigned char start_postion; //运动开始位置
    unsigned char end_postion; //运动结束位置

    reagentPromWidget->standardPrograme_mode = reagentPromWidget->PRO_STEP_RUN;  //单步运行状态
    if( tableWidgetIsEmpty() ){   //判断当前试剂船各位置是否编辑完整
        qDebug() << "当前试剂船信息不完整";
        if( QMessageBox::critical(this,tr("提示"),tr("当前试剂船编辑信息表不完整，请填写完整!")) == QMessageBox::Ok){
            return;
        }

    }
    strcmd = reagentPromWidget->actionProTabelView->getStepData(step);
    start_postion = strcmd.mid(42,2).toInt();
    end_postion = strcmd.mid(66,2).toInt();

    if( start_postion ){
        strcmd.replace(21,23,getX_Y_Value(start_postion));
    }
    if( end_postion ){
        strcmd.replace(45,23,getX_Y_Value(end_postion));
    }

    qDebug() << strcmd;
    serialPort::mySend_Data(strcmd);
    qDebug() << "发送试剂船单步测试命令一次";;
}

void standardPragrameWidget::slot_RefreshComoBox_FileName_And_SN(QString text)
{
    Q_UNUSED(text)
    DatabaseOperation op;
    QSqlQueryModel model;

    //1
    op.selectProject_nameByCategory(cmbx_type->currentText(),model);//model中只有品类名称
    cmbx_fileName->clear();
    for(int i=0;i<model.rowCount();i++)
        cmbx_fileName->insertItem(i,model.index(i,0).data().toString());

    //2
    op.selectReagent_typeByProject_name(cmbx_type->currentText(),cmbx_fileName->currentText(),model);
    cmbx_fileSN->clear();
    for(int i=0;i<model.rowCount();i++)cmbx_fileSN->insertItem(i,model.index(i,0).data().toString());

    //3
   // emit signal_refreshNumber();//后续会发信号
}

void standardPragrameWidget::slot_RefreshComoBox__SN(QString text)
{
    Q_UNUSED(text)
    DatabaseOperation op;
    QSqlQueryModel model;
    //2
    op.selectReagent_typeByProject_name(cmbx_type->currentText(),cmbx_fileName->currentText(),model);
    cmbx_fileSN->clear();
    for(int i=0;i<model.rowCount();i++)cmbx_fileSN->insertItem(i,model.index(i,0).data().toString());

    //3
   // emit signal_refreshNumber();

}






