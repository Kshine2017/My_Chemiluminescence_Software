#include "reagentdisplay.h"
#include <QTableWidgetItem>
#define SERICAL_WIDTH 40
#define TABLE_NAME_HIGHT 34  //原为34 因多一行，压缩行距//29
#define TABLE_NAME_WIDTH 90 //180
reagentDisplay::reagentDisplay(QWidget *parent) : QWidget(parent)
{


    //1）添加示意图片
    reagentLab = new QLabel;
    reagentLab->setPixmap(QPixmap(":/picture/standardPrograme/shijichuan_modle2.png"));
    reagentLab->setFixedSize(697,230);
    reagentLab->setScaledContents(true);        //


    //2）创建表格
    TableInit();

    //3）创建工作进度区
    //添加底图
    label_pic = new QLabel(this);
    //label_pic->setFixedSize(448,328);
    QPixmap pix_background(":/picture/unknowWidget/lineEdit_background.png");
    pix_background.scaled(label_pic->size(), Qt::IgnoreAspectRatio);
    label_pic->setScaledContents(true);
    label_pic->setPixmap(pix_background);
    label_pic->setGeometry(1315,20,345,200);

    workPA =new WorkProgressArea(this); //this是指 上半部分总体


    //4）添加到布局
    mainlayout = new QHBoxLayout(this);
    mainlayout->setMargin(6);//边界距离
    mainlayout->addWidget(reagentTab);

    mainlayout->addWidget(reagentLab);
    mainlayout->addWidget(workPA);

    this->setLayout(mainlayout);




}

/**< tab窗口初始化 */
void reagentDisplay::TableInit()
{
    reagentTab = new QTableWidget(this);
    reagentTab->setColumnCount(6); //列
    reagentTab->setRowCount(6); //6行 增加一行，现为7行
    reagentTab->horizontalHeader()->hide();
    reagentTab->verticalHeader()->hide();
    reagentTab->setColumnWidth(0,SERICAL_WIDTH);
    reagentTab->setColumnWidth(1,TABLE_NAME_WIDTH);
    reagentTab->setColumnWidth(2,SERICAL_WIDTH);
    reagentTab->setColumnWidth(3,TABLE_NAME_WIDTH);
    reagentTab->setColumnWidth(4,SERICAL_WIDTH);
    reagentTab->setColumnWidth(5,TABLE_NAME_WIDTH);

    reagentTab->setRowHeight(0,TABLE_NAME_HIGHT);
    reagentTab->setRowHeight(1,TABLE_NAME_HIGHT);
    reagentTab->setRowHeight(2,TABLE_NAME_HIGHT);
    reagentTab->setRowHeight(3,TABLE_NAME_HIGHT);
    reagentTab->setRowHeight(4,TABLE_NAME_HIGHT);
    reagentTab->setRowHeight(5,TABLE_NAME_HIGHT);
    //reagentTab->setRowHeight(6,TABLE_NAME_HIGHT);//增加行

    reagentTab->setStyleSheet("gridline-color: rgb(0, 139, 139)");
    reagentTab->setFixedSize(3*(SERICAL_WIDTH+TABLE_NAME_WIDTH)+2,6*TABLE_NAME_HIGHT+2); //382+30+30，//442 206
//表格选择
    reagentTab->setSelectionMode(QAbstractItemView::NoSelection);
    reagentTab->setEditTriggers(QAbstractItemView::NoEditTriggers);
    reagentTab->setSelectionBehavior(QAbstractItemView::SelectRows);

//放置表格里面1~12的图标
    QLabel *serical_lab = new QLabel;
    serical_lab->setPixmap(QPixmap(":/picture/standardPrograme/01.png").scaled(20,20));
    QHBoxLayout *layout1 = new QHBoxLayout;
    layout1->addWidget(serical_lab);
    QWidget *window1 = new QWidget;
    window1->setFixedSize(40,40);
    window1->setLayout(layout1);
    reagentTab->setCellWidget(0,0,window1);

    QLabel *serica2_lab = new QLabel;
    serica2_lab->setPixmap(QPixmap(":/picture/standardPrograme/02.png").scaled(20,20));
    QHBoxLayout *layout2 = new QHBoxLayout;
    layout2->addWidget(serica2_lab);
    QWidget *window2 = new QWidget;
    window2->setFixedSize(40,40);
    window2->setLayout(layout2);
    reagentTab->setCellWidget(1,0,window2);

    QLabel *serica3_lab = new QLabel;
    serica3_lab->setPixmap(QPixmap(":/picture/standardPrograme/03.png").scaled(20,20));
    QHBoxLayout *layout3 = new QHBoxLayout;
    layout3->addWidget(serica3_lab);
    QWidget *window3 = new QWidget;
    window3->setFixedSize(40,40);
    window3->setLayout(layout3);
    reagentTab->setCellWidget(2,0,window3);

    QLabel *serica4_lab = new QLabel;
    serica4_lab->setPixmap(QPixmap(":/picture/standardPrograme/04.png").scaled(20,20));
    QHBoxLayout *layout4 = new QHBoxLayout;
    layout4->addWidget(serica4_lab);
    QWidget *window4 = new QWidget;
    window4->setFixedSize(40,40);
    window4->setLayout(layout4);
    reagentTab->setCellWidget(3,0,window4);

    QLabel *serica5_lab = new QLabel;
    serica5_lab->setPixmap(QPixmap(":/picture/standardPrograme/05.png").scaled(20,20));
    QHBoxLayout *layout5 = new QHBoxLayout;
    layout5->addWidget(serica5_lab);
    QWidget *window5 = new QWidget;
    window5->setFixedSize(40,40);
    window5->setLayout(layout5);
    reagentTab->setCellWidget(4,0,window5);

    QLabel *serica6_lab = new QLabel;
    serica6_lab->setPixmap(QPixmap(":/picture/standardPrograme/06.png").scaled(20,20));
    QHBoxLayout *layout6 = new QHBoxLayout;
    layout6->addWidget(serica6_lab);
    QWidget *window6 = new QWidget;
    window6->setFixedSize(40,40);
    window6->setLayout(layout6);
    reagentTab->setCellWidget(5,0,window6);



    QLabel *serica7_lab = new QLabel;
    serica7_lab->setPixmap(QPixmap(":/picture/standardPrograme/07.png").scaled(20,20));
    QHBoxLayout *layout7 = new QHBoxLayout;
    layout7->addWidget(serica7_lab);
    QWidget *window7 = new QWidget;
    window7->setFixedSize(40,40);
    window7->setLayout(layout7);
    reagentTab->setCellWidget(0,2,window7);

    QLabel *serica8_lab = new QLabel;
    serica8_lab->setPixmap(QPixmap(":/picture/standardPrograme/08.png").scaled(20,20));
    QHBoxLayout *layout8 = new QHBoxLayout;
    layout8->addWidget(serica8_lab);
    QWidget *window8 = new QWidget;
    window8->setFixedSize(40,40);
    window8->setLayout(layout8);
    reagentTab->setCellWidget(1,2,window8);

    QLabel *serica9_lab = new QLabel;
    serica9_lab->setPixmap(QPixmap(":/picture/standardPrograme/09.png").scaled(20,20));
    QHBoxLayout *layout9 = new QHBoxLayout;
    layout9->addWidget(serica9_lab);
    QWidget *window9 = new QWidget;
    window9->setFixedSize(40,40);
    window9->setLayout(layout9);
    reagentTab->setCellWidget(2,2,window9);

    QLabel *serica10_lab = new QLabel;
    serica10_lab->setPixmap(QPixmap(":/picture/standardPrograme/10.png").scaled(20,20));
    QHBoxLayout *layout10 = new QHBoxLayout;
    layout10->addWidget(serica10_lab);
    QWidget *window10 = new QWidget;
    window10->setFixedSize(40,40);
    window10->setLayout(layout10);
    reagentTab->setCellWidget(3,2,window10);

    QLabel *serica11_lab = new QLabel;
    serica11_lab->setPixmap(QPixmap(":/picture/standardPrograme/11.png").scaled(20,20));
    QHBoxLayout *layout11 = new QHBoxLayout;
    layout11->addWidget(serica11_lab);
    QWidget *window11 = new QWidget;
    window11->setFixedSize(40,40);
    window11->setLayout(layout11);
    reagentTab->setCellWidget(4,2,window11);


    QLabel *serical12_lab = new QLabel;
    serical12_lab->setPixmap(QPixmap(":/picture/standardPrograme/12.png").scaled(20,20));
    QHBoxLayout *layout12 = new QHBoxLayout;
    layout12->addWidget(serical12_lab);
    QWidget *window12 = new QWidget;
    window12->setFixedSize(40,40);
    window12->setLayout(layout12);
    reagentTab->setCellWidget(5,2,window12);


    //新增列
    QLabel *serical13_lab = new QLabel;
    serical13_lab->setPixmap(QPixmap(":/picture/standardPrograme/13.png").scaled(20,20));
    QHBoxLayout *layout13 = new QHBoxLayout;
    layout13->addWidget(serical13_lab);
    QWidget *window13 = new QWidget;
    window13->setFixedSize(40,40);
    window13->setLayout(layout13);
    reagentTab->setCellWidget(0,4,window13);

    QLabel *serical14_lab = new QLabel;
    serical14_lab->setPixmap(QPixmap(":/picture/standardPrograme/14.png").scaled(20,20));
    QHBoxLayout *layout14 = new QHBoxLayout;
    layout14->addWidget(serical14_lab);
    QWidget *window14 = new QWidget;
    window14->setFixedSize(40,40);
    window14->setLayout(layout14);
    reagentTab->setCellWidget(1,4,window14);

    QLabel *serical15_lab = new QLabel;
    serical15_lab->setPixmap(QPixmap(":/picture/standardPrograme/15.png").scaled(20,20));
    QHBoxLayout *layout15 = new QHBoxLayout;
    layout15->addWidget(serical15_lab);
    QWidget *window15 = new QWidget;
    window15->setFixedSize(40,40);
    window15->setLayout(layout15);
    reagentTab->setCellWidget(2,4,window15);

    QLabel *serical16_lab = new QLabel;
    serical16_lab->setPixmap(QPixmap(":/picture/standardPrograme/16.png").scaled(20,20));
    QHBoxLayout *layout16 = new QHBoxLayout;
    layout16->addWidget(serical16_lab);
    QWidget *window16 = new QWidget;
    window16->setFixedSize(40,40);
    window16->setLayout(layout16);
    reagentTab->setCellWidget(3,4,window16);

    QLabel *serical17_lab = new QLabel;
    serical17_lab->setPixmap(QPixmap(":/picture/standardPrograme/17.png").scaled(20,20));
    QHBoxLayout *layout17 = new QHBoxLayout;
    layout17->addWidget(serical17_lab);
    QWidget *window17 = new QWidget;
    window17->setFixedSize(40,40);
    window17->setLayout(layout17);
    reagentTab->setCellWidget(4,4,window17);


//设置表格文字
    QTableWidgetItem *itemGet0 = new QTableWidgetItem;
    itemGet0->setTextAlignment(Qt::AlignCenter);
    itemGet0->setText(tr("废液池"));
    reagentTab->setItem(0,1,itemGet0);

    QTableWidgetItem *itemGet1 = new QTableWidgetItem;
    itemGet1->setTextAlignment(Qt::AlignCenter);
    itemGet1->setText(tr("TIP头1"));
    reagentTab->setItem(1,1,itemGet1);

    QTableWidgetItem *itemGet2 = new QTableWidgetItem;
    itemGet2->setTextAlignment(Qt::AlignCenter);
    itemGet2->setText(tr("TIP头2"));
    reagentTab->setItem(2,1,itemGet2);

    QTableWidgetItem *itemGet3 = new QTableWidgetItem;
    itemGet3->setTextAlignment(Qt::AlignCenter);
    itemGet3->setText(tr("TIP头3"));
    reagentTab->setItem(3,1,itemGet3);

    QTableWidgetItem *itemGet4 = new QTableWidgetItem;
    itemGet4->setTextAlignment(Qt::AlignCenter);
    itemGet4->setText(tr("TIP头4"));
    reagentTab->setItem(4,1,itemGet4);

    QTableWidgetItem *itemGet5 = new QTableWidgetItem;
    itemGet5->setTextAlignment(Qt::AlignCenter);
    itemGet5->setText(tr("预激发液"));
    reagentTab->setItem(5,1,itemGet5);

    QTableWidgetItem *itemGet6 = new QTableWidgetItem;
    itemGet6->setTextAlignment(Qt::AlignCenter);
    itemGet6->setText(tr("激发液"));
    reagentTab->setItem(0,3,itemGet6);

    QTableWidgetItem *itemGet7 = new QTableWidgetItem;
    itemGet7->setTextAlignment(Qt::AlignCenter);
    itemGet7->setText(tr("洗涤液3"));
    reagentTab->setItem(1,3,itemGet7);

    QTableWidgetItem *itemGet8 = new QTableWidgetItem;
    itemGet8->setTextAlignment(Qt::AlignCenter);
    itemGet8->setText(tr("洗涤液2"));
    reagentTab->setItem(2,3,itemGet8);

    QTableWidgetItem *itemGet9 = new QTableWidgetItem;
    itemGet9->setTextAlignment(Qt::AlignCenter);
    itemGet9->setText(tr("洗涤液1"));
    reagentTab->setItem(3,3,itemGet9);

    QTableWidgetItem *itemGet10 = new QTableWidgetItem;
    itemGet10->setTextAlignment(Qt::AlignCenter);
    itemGet10->setText(tr("SA磁珠"));
    reagentTab->setItem(4,3,itemGet10);

    QTableWidgetItem *itemGet11 = new QTableWidgetItem;
    itemGet11->setTextAlignment(Qt::AlignCenter);
    itemGet11->setText(tr("预留"));
    reagentTab->setItem(5,3,itemGet11);

    //

    QTableWidgetItem *itemGet12 = new QTableWidgetItem;
    itemGet12->setTextAlignment(Qt::AlignCenter);
    itemGet12->setText(tr("生物素"));
    reagentTab->setItem(0,5,itemGet12);

    QTableWidgetItem *itemGet13 = new QTableWidgetItem;
    itemGet13->setTextAlignment(Qt::AlignCenter);
    itemGet13->setText(tr("吖啶酯"));
    reagentTab->setItem(1,5,itemGet13);

    QTableWidgetItem *itemGet14 = new QTableWidgetItem;
    itemGet14->setTextAlignment(Qt::AlignCenter);
    itemGet14->setText(tr("反应管"));
    reagentTab->setItem(2,5,itemGet14);

    QTableWidgetItem *itemGet15 = new QTableWidgetItem;
    itemGet15->setTextAlignment(Qt::AlignCenter);
    itemGet15->setText(tr("血浆样本"));
    reagentTab->setItem(3,5,itemGet15);

    QTableWidgetItem *itemGet16 = new QTableWidgetItem;
    itemGet16->setTextAlignment(Qt::AlignCenter);
    itemGet16->setText(tr("手持区"));
    reagentTab->setItem(4,5,itemGet16);


}
