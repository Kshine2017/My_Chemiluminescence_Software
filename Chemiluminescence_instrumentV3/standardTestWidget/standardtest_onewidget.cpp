#include "standardtest_onewidget.h"
#include <QMessageBox>
#include <QPushButton>
#include <QTableWidgetItem>
#include <QPixmap>
#include <QHeaderView>
#include <QDebug>
#include <QSqlQuery>

#define INF_TABLE_WIDTH 1665  //项目信息表宽
#define INF_TABLE_HIGH 40     //项目信息表高
standardTest_OneWidget::standardTest_OneWidget(QWidget *parent) : QWidget(parent)
{
    title_init();
    tableWidget_init();
    tableView_init();
    statusWidget = new StatusWidget(this); //试剂仓状态显示窗口
    mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->addSpacing(72);
    mainLayout->addWidget(statusWidget);
    mainLayout->addLayout(BtnLayout);
    mainLayout->addWidget(tableWidget);
    mainLayout->addWidget(tableView);
    mainLayout->addSpacing(2);
    setLayout(mainLayout);

    /***工作队列和超时定时器****/
    WorkQueue = new Queue(this);
    RunData = new QMap<int,QString>; //申请一个QMap容器来储存临时插入试剂船的运行数据
    SerialNumber = new QMap<int,QString>; //储存各试剂船序列号，第二位到第七位条码用于查询标准曲线
    queryTimer = new QTimer(this);
    queryTimer->setInterval(STANDARD_TEST_QUERY_FREE_TIME);
    queryTimer->setSingleShot(false);
    queryTimer->start();
    /**
     * @brief 信号和槽绑定
     */
    connnect_init();

}

//初始化
void standardTest_OneWidget::title_init()
{
    titleLabel = new QLabel(this);
    titleLabel->setPixmap(QPixmap(":/picture/standardTest/tile_icon.png"));

    QPalette   pal;//按键字体颜色设置
    pal.setColor(QPalette::WindowText, QColor(255, 255, 255, 255));

    title_name = new QLabel(titleLabel);
    title_name->setText(tr("标准品操作"));
    title_name->setPalette(pal);
    title_name->setFont(QFont("windowTitle",15));

    questionBtn = new QPushButton(this);
    questionBtn->setIconSize(QSize(46,46));
    questionBtn->setIcon(QIcon(":/picture/standardTest/？btn.png"));
    questionBtn->setFlat(true);
    questionBtn->setGeometry(1600,1,45,45);
    titleLabel->setGeometry(0,0,1687,67);
    title_name->setGeometry(75,13,150,40);

/**
 *  控制按钮创建
 */
    QFont *font;
    font = new QFont(tr("BtnFont"),20);
    BtnLayout = new  QHBoxLayout;
    finsh_placeBtn =  new QPushButton;
    finsh_placeBtn->setFont(*font);
    finsh_placeBtn->setFixedSize(153,42);
    finsh_placeBtn->setStyleSheet("QPushButton{border-image: url(:/picture/standardTest/finishPng-up.png);}"
                               "QPushButton:hover{border-image: url(:/picture/standardTest/finishPng-up.png);}"
                               "QPushButton:pressed{border-image: url(:/picture/standardTest/finishPng-down.png);}");
    finsh_placeBtn->setFlat(true);

    returnBtn = new QPushButton;
    returnBtn->setFont(*font);
    returnBtn->setFixedSize(153,42);
    returnBtn->setStyleSheet("QPushButton{border-image: url(:/picture/standardTest/returnPng-up.png);}"
                               "QPushButton:hover{border-image: url(:/picture/standardTest/returnPng-up.png);}"
                               "QPushButton:pressed{border-image: url(:/picture/standardTest/returnPng-down.png);}");
    returnBtn->setFlat(true);

    nextBtn = new QPushButton;      /**< 下一步动作*/
    nextBtn->setFont(*font);
    nextBtn->setFixedSize(153,42);
    nextBtn->setStyleSheet("QPushButton{border-image: url(:/picture/standardTest/next-up.png);}"
                               "QPushButton:hover{border-image: url(:/picture/standardTest/next-up.png);}"
                               "QPushButton:pressed{border-image: url(:/picture/standardTest/next-down.png);}");
    nextBtn->setFlat(true);
    BtnLayout->addWidget(finsh_placeBtn);
    BtnLayout->addSpacing(50);
    BtnLayout->addWidget(returnBtn);
    BtnLayout->addSpacing(50);
    BtnLayout->addWidget(nextBtn);
    BtnLayout->addStretch();

}

/**
 * @brief 操作表格信息初始化
 */
void standardTest_OneWidget::tableWidget_init()
{
    /**
     * 项目表格编辑
     *
     */
        tableWidget = new QTableWidget(this);
        tableWidget->setColumnCount(8); //列数6-->8
        tableWidget->setRowCount(1);
    //隐藏表头
        tableWidget->horizontalHeader()->hide();
        tableWidget->verticalHeader()->hide();
 //       tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
//        tableWidget->setSelectionMode (QAbstractItemView::NoSelection); //设置不可选择
//        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑
        tableWidget->setStyleSheet("gridline-color: rgb(0, 139, 139)"); //上方表格，边框颜色

        tableWidget->setFixedSize(INF_TABLE_WIDTH,INF_TABLE_HIGH+2);

        tableWidget->setColumnWidth(0,150);
        tableWidget->setColumnWidth(1,250);
        tableWidget->setColumnWidth(2,150);
        tableWidget->setColumnWidth(3,250);
        tableWidget->setColumnWidth(4,150);
        tableWidget->setColumnWidth(5,250);
        tableWidget->setColumnWidth(6,150);
        tableWidget->setColumnWidth(7,313);

        tableWidget->setRowHeight(0,INF_TABLE_HIGH);
        tableWidget->setFont(QFont("standTest",20));
     /*表格添加资源*/
        QTableWidgetItem *itemGet1 = new QTableWidgetItem; //品类
        itemGet1->setTextAlignment(Qt::AlignCenter);
        itemGet1->setFont(QFont("standTest",20));
        tableWidget->setItem(0,1,itemGet1);

        QTableWidgetItem *itemGet3 = new QTableWidgetItem; //项目名称
        itemGet3->setTextAlignment(Qt::AlignCenter);
        itemGet3->setFont(QFont("standTest",20));
        tableWidget->setItem(0,3,itemGet3);

        QTableWidgetItem *itemGet5 = new QTableWidgetItem; //试剂名称
        itemGet5->setTextAlignment(Qt::AlignCenter);
        itemGet5->setFont(QFont("standTest",20));
        tableWidget->setItem(0,5,itemGet5);

        QTableWidgetItem *itemGet7 = new QTableWidgetItem; //条码
        itemGet7->setTextAlignment(Qt::AlignCenter);
        itemGet7->setFont(QFont("standTest",20));
        tableWidget->setItem(0,7,itemGet7);

//        QLabel *lab_icon = new QLabel;                      //条码图像
//        tableWidget->setCellWidget(0,5,lab_icon);


        QTableWidgetItem *itemGet0 = new QTableWidgetItem;
        itemGet0->setTextAlignment(Qt::AlignCenter);
        itemGet0->setFont(QFont("standTest",20));
        itemGet0->setText(tr("品  类："));

        tableWidget->setItem(0,0,itemGet0);
        QTableWidgetItem *itemGet2 = new QTableWidgetItem;
        itemGet2->setTextAlignment(Qt::AlignCenter);
        itemGet2->setFont(QFont("standTest",20));
        itemGet2->setText(tr("项目名称："));
        tableWidget->setItem(0,2,itemGet2);

        QTableWidgetItem *itemGet4 = new QTableWidgetItem;
        itemGet4->setTextAlignment(Qt::AlignCenter);
        itemGet4->setFont(QFont("standTest",20));
        itemGet4->setText(tr("试剂种类："));
        tableWidget->setItem(0,4,itemGet4);

        QTableWidgetItem *itemGet6 = new QTableWidgetItem;
        itemGet6->setTextAlignment(Qt::AlignCenter);
        itemGet6->setFont(QFont("standTest",20));
        itemGet6->setText(tr("条  码："));
        tableWidget->setItem(0,6,itemGet6);

//==============用于测试==========================================

#if 0
        QTableWidgetItem *itemGet6 = new QTableWidgetItem;
        itemGet6->setTextAlignment(Qt::AlignCenter);
        itemGet6->setFont(QFont("standTest",20));
        tableWidget->setItem(0,1,itemGet6);

        QTableWidgetItem *itemGet7 = new QTableWidgetItem;
        itemGet7->setTextAlignment(Qt::AlignCenter);
        itemGet7->setFont(QFont("standTest",20));
        tableWidget->setItem(0,3,itemGet7);

        QTableWidgetItem *itemGet8 = new QTableWidgetItem;
        itemGet8->setTextAlignment(Qt::AlignCenter);
        itemGet8->setFont(QFont("standTest",20));
        tableWidget->setItem(0,5,itemGet8);
#endif
}

/**
 * @brief standardTest_OneWidget::模型视图初始化
 */
void standardTest_OneWidget::tableView_init()
{
    QFont *font;
    font = new QFont("tableview",12);
    model = new QStandardItemModel(12,11);
 //设置表格编辑模式
    for(int i = 0 ;i < 12 ;i++)
    {
        for(int j = 0;j < 11;j++)
        {
            if(j == 9)
            {
                model->setData(model->index(i,9,QModelIndex()),QVariant(tr("")));
                model->item(i,9)->setTextAlignment(Qt::AlignCenter);
            }
            else// if(j!=5 && j!= 10)
            {
                model->setData(model->index(i,j,QModelIndex()),QVariant(tr("")));
                model->item(i,j)->setTextAlignment(Qt::AlignCenter);
                model->item(i,j)->setFlags(model->item(i,j)->flags() & (~Qt::ItemIsEditable));
            }
        }
    }
    tableView = new QTableView(this);
    tableView->setFixedSize(1665,536);
    tableView->setModel(model);
    tableView->setFont(*font);

 //创建代理
    ProgressDelegate = new standTest_ProgressDelegate;
    okBtnDelegate = new standardText_okBtnDelegate;

 //模型视图设置
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("槽编号"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("标准品条码"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("有效起始日期"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("有效截止日期"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("当前工作阶段"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("进度条"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("开始时间"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("结束时间"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("测量光子数"));
    model->setHeaderData(9,Qt::Horizontal,QObject::tr("标称浓度"));
    model->setHeaderData(10,Qt::Horizontal,QObject::tr("确认按钮"));
    model->setData(model->index(0,0,QModelIndex()),QVariant(tr(" 船仓1")));
    model->setData(model->index(1,0,QModelIndex()),QVariant(tr(" 船仓2")));
    model->setData(model->index(2,0,QModelIndex()),QVariant(tr(" 船仓3")));
    model->setData(model->index(3,0,QModelIndex()),QVariant(tr(" 船仓4")));
    model->setData(model->index(4,0,QModelIndex()),QVariant(tr(" 船仓5")));
    model->setData(model->index(5,0,QModelIndex()),QVariant(tr(" 船仓6")));
    model->setData(model->index(6,0,QModelIndex()),QVariant(tr(" 船仓7")));
    model->setData(model->index(7,0,QModelIndex()),QVariant(tr(" 船仓8")));
    model->setData(model->index(8,0,QModelIndex()),QVariant(tr(" 船仓9")));
    model->setData(model->index(9,0,QModelIndex()),QVariant(tr("船仓10")));
    model->setData(model->index(10,0,QModelIndex()),QVariant(tr("船仓11")));
    model->setData(model->index(11,0,QModelIndex()),QVariant(tr("船仓12")));

    //设置列宽
    tableView->setColumnWidth(0,90);
    tableView->setColumnWidth(1,140);
    tableView->setColumnWidth(2,140);
    tableView->setColumnWidth(3,140);
    tableView->setColumnWidth(4,150);
    tableView->setColumnWidth(5,300);
    tableView->setColumnWidth(6,132);
    tableView->setColumnWidth(7,132);
    tableView->setColumnWidth(8,144);
    tableView->setColumnWidth(9,144);
    tableView->setColumnWidth(10,150);
    //设置：行高
    tableView->verticalHeader()->setDefaultSectionSize(42);

    /**
     * tabelView表格设置
     */
    /*tableView设置集合*/
    //设置其选择行为，并不可以编辑
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
//    tableView->setSelectionMode ( QAbstractItemView::SingleSelection);
//    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置下方表格，不可编辑
    tableView->setEditTriggers(QAbstractItemView::AllEditTriggers);
    //隐藏表格线
    tableView->setShowGrid(true);
    //列表头隐藏
    tableView->verticalHeader()->hide();
    //设置各行变色
    tableView->setAlternatingRowColors(true);
    //设置交替色的颜色
    tableView->setStyleSheet("alternate-background-color: rgb(224, 224, 224);");
    //设置列不能拖动
    tableView->horizontalHeader()->setDisabled(true);
    //设置行不能拖动
    tableView->verticalHeader()->setDisabled(true);
    //    tableView->setStyleSheet("selection-background-color: red");

    //配置代理
    tableView->setItemDelegateForColumn(5,ProgressDelegate);
    tableView->setItemDelegateForColumn(10,okBtnDelegate);


}
/**
 * @brief 信号和槽绑定
 */
void standardTest_OneWidget::connnect_init()
{
    /**
     * @brief 绑定信号和槽
     */
    connect(finsh_placeBtn,SIGNAL(clicked()),this,SLOT(finsh_placeBtnSlot()));
    connect(returnBtn,SIGNAL(clicked()),this,SLOT(returnBtnSlot()));
    connect(nextBtn,SIGNAL(clicked()),this,SLOT(nextBtnSlot()));
    connect(queryTimer,SIGNAL(timeout()),this,SLOT(queryTimerOverSlot()));

    /**
     * @brief 12个确定按钮
     */
    connect(okBtnDelegate,SIGNAL(OkBtnClicked(QModelIndex)),this,SLOT(okBtnDelegateSlot(QModelIndex)));
}

/**
 * @brief 得到运行步骤数据
 * @param 条码
 * @return 当前试剂运行数据
 */
QString standardTest_OneWidget::getRunInfo(QString &serical)
{
    QString serical_num = serical;
    QString return_string;
    QSqlQuery query;
    query.exec("select RUN_DATA from reagent_info where STANDARD_CODE = ?;");
    query.bindValue(0,serical_num,QSql::Out);
    query.exec();
    while(query.next()){
        return_string = query.value(0).toString();
        qDebug() << "当前试剂船运行数据 = " << return_string;
        return return_string;
    }
    emit serialPort::ReceiveThread.ErrDataSign("无此试剂方案");
    return 0;
}

/**
 * @brief standardTest_OneWidget::三个控制按钮信号槽 return finsh
 */

void standardTest_OneWidget::returnBtnSlot()
{
    myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_INFORMATION,tr("提示"),tr("返回主窗口"),this);
    if(messge->exec() == QDialog::Accepted){   //模式对话框

    }
}

/**
 * @brief 将当前试剂船仓工作类容插入队列
 */
void standardTest_OneWidget::finsh_placeBtnSlot()
{
    for(int i = 0; i < 12 ; i++){
      if( statusWidget->Reagent_status[i] == StatusWidget::AWAIT ){
         break;
      }
      if (statusWidget->Reagent_status[11] != StatusWidget::AWAIT){
          QMessageBox::critical(this,tr("提示"),tr("当前界面没有待测试剂船!"));
          return;
      }
    }
    QMap< int,QString >::iterator it;
    for(it = RunData->begin();it != RunData->end();it++){
        int postion = it.key();  //获取当前试剂船号
        statusWidget->setReagent_Status(postion,StatusWidget::RUN);//更改当前试剂船状态
        WorkQueue->enqueue("03,06,ff,ff,00,00"+ QString(",")+ QString::number(postion,10)+QString(",")+ it.value()); //将当前试剂船运动数据加入工作队列
    }
    RunData->clear(); //清除哈希表数据
}

void standardTest_OneWidget::nextBtnSlot()
{
    for(int i = 0; i< 12;i++){
        if( statusWidget->Reagent_status[i] != StatusWidget::FREE ){
            QMessageBox::critical(this,tr("提示"),tr("当前界面有试剂船没有完成测试!"));
            return;
        }
    }
    emit nextBtnPressSign();
}


/**
 * @brief standardTest_OneWidget::12个确定按钮信号槽
 */
void standardTest_OneWidget::okBtnDelegateSlot(const QModelIndex &index)
{
    int row = index.row();
    if( model->data(model->index(row,8),Qt::DisplayRole) == ""){
         okBtnDelegate->okBtn_btns.value(index.row())->text = tr("");
         okBtnDelegate->okBtn_btns.value(index.row())->state &= (~QStyle::State_Enabled);
         QMessageBox::critical(this,tr("提示"),tr("当前试剂船没有完成测试!"));
         return;
    }
    if( model->data(model->index(row,9),Qt::DisplayRole) == ""){
         okBtnDelegate->okBtn_btns.value(index.row())->text = tr("");
         okBtnDelegate->okBtn_btns.value(index.row())->state &= (~QStyle::State_Enabled);
         QMessageBox::critical(this,tr("提示"),tr("当前试剂船标称浓度项目栏不能为空!"));
         return;
    }
}

/**
 * @brief standardTest_OneWidget::定时器超时信号槽
 */
void standardTest_OneWidget::queryTimerOverSlot()
{
    if( !WorkQueue->isEmpty() ){
       serialPort::mySend_Data("03,05,ff,ff,00,00");
    }
}
