#include "calibration_onewidget.h"
#include <QDebug>
#include <QHeaderView>
#include <QAbstractItemDelegate>
#include "data/util.h"
#include "standardBightWidget/qcustomplot.h"
calibration_oneWidget::calibration_oneWidget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(1671,1080);
    titleInit();
    tableViewInit();
    PushBtnInit();
    QCustomplotInit();
    statusWidget = new StatusWidget; //试剂仓状态显示窗口
    mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->addWidget(titleIconLab);
    mainLayout->addWidget(statusWidget);
    mainLayout->addLayout(btnLayout);
    mainLayout->addWidget(tableView);
    mainLayout->addSpacing(280);
    setLayout(mainLayout);

    /***工作队列和超时定时器****/
    Calibration_WorkQueue = new Queue(this);

    RunData = new QMap<int,QString>; //申请一个QMap容器来储存临时插入试剂船的运行数据
    SerialNumber = new QMap<int,QString>; //储存各试剂船序列号，第二位到第七位条码用于查询标准曲线
    queryTimer = new QTimer(this);
    queryTimer->setInterval(CALIBRATION_QUERY_FREE_TIME);
    queryTimer->setSingleShot(false);
    queryTimer->start();

    connect(finishPlaceBtn,SIGNAL(clicked()),this,SLOT(finishPlaceBtnSlot()));
    connect(nextBtn,SIGNAL(clicked()),this,SLOT(nextBtnSlot()));
    connect(okBtn,SIGNAL(btnClicked(QModelIndex)),this,SLOT(Display_btnSlot(QModelIndex)));
    connect(this->queryTimer,SIGNAL(timeout()),this,SLOT(calibration_queryTimerOverSlot()));
}

/**
 * @brief 窗口标题头初始化
 */
void calibration_oneWidget::titleInit()
{
    titleIconLab = new QLabel(this);   //头图标
    titleIconLab->setPixmap(QPixmap(":/picture/standardPrograme/tile_icon.png"));

    titleTextLab = new QLabel(titleIconLab); //标题文字
    titleTextLab->setText(tr("校准品操作"));

    QPalette   pal;//按键字体颜色设置
    pal.setColor(QPalette::WindowText, QColor(255, 255, 255, 255));
    titleTextLab->setPalette(pal);
    titleTextLab->setFont(QFont("windowTitle",15));
    titleTextLab->setGeometry(75,13,150,40);
    questionBtn = new QPushButton(titleIconLab); //问号按钮
    questionBtn->setIconSize(QSize(46,45));
    questionBtn->setIcon(QIcon(":/picture/standardPrograme/？btn.png"));
    questionBtn->setFlat(true);
    questionBtn->setGeometry(1600,1,45,45);

}

/**
 * @brief 模型视图初始化
 */
void calibration_oneWidget::tableViewInit()
{
    model = new QStandardItemModel(12,12);

    model->setData(model->index(2,2,QModelIndex()),QVariant(tr("222")));
    model->item(2,2)->setTextAlignment(Qt::AlignCenter);
    //让tableView中的文本居中
//    for(int i = 0 ;i < 12 ;i++)
//    {
//        for(int j = 0;j < 12;j++)
//        {
//            model->setData(model->index(i,j,QModelIndex()),QVariant(tr("")));
//            model->item(i,j)->setTextAlignment(Qt::AlignCenter);
//        }
//    }
    tableView = new  QTableView(this);
    /*创建代理*/

    progressBarDelegate = new calibration_ProgressBarDelegate(this);
    comBoxDelegate = new calibration_QComboxDelegate;
    okBtn = new calibration_okBtnDelegate;

    tableView->setFixedSize(1665,530);
    tableView->setModel(model);


    model->setHeaderData(0,Qt::Horizontal,QObject::tr("槽编号"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("校准品条码"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("项目"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("标称浓度"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("有效起始日期"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("有效截止日期"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("A/B"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("当前工作阶段"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("进度条"));

    model->setHeaderData(9,Qt::Horizontal,QObject::tr("测量光子数"));
    model->setHeaderData(10,Qt::Horizontal,QObject::tr("测量浓度"));
    model->setHeaderData(11,Qt::Horizontal,QObject::tr("显示曲线"));
    /*tableView设置集合*/
    //设置其选择行为，并不可以编辑
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
//    tableView->setSelectionMode ( QAbstractItemView::SingleSelection);
//    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setEditTriggers(QAbstractItemView::AllEditTriggers); //允许所有的编辑操作，主要是为了 combobox可以单击
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
    //设置列宽
    tableView->setColumnWidth(0,60);
    tableView->setColumnWidth(1,121);
    tableView->setColumnWidth(2,150);
    tableView->setColumnWidth(3,120);
    tableView->setColumnWidth(4,110);
    tableView->setColumnWidth(5,110);
    tableView->setColumnWidth(6,50);
    tableView->setColumnWidth(7,160);
    tableView->setColumnWidth(8,420);
    tableView->setColumnWidth(9,130);
    tableView->setColumnWidth(10,130);
    tableView->setColumnWidth(11,100);
    //设置：行高
    tableView->verticalHeader()->setDefaultSectionSize(42);

    //设置列的代理
    tableView->setItemDelegateForColumn(6,comBoxDelegate);
    tableView->setItemDelegateForColumn(8,progressBarDelegate);
    tableView->setItemDelegateForColumn(11,okBtn);

/**************设置文本框属性****************************************************/
    for(int i=0;i<=11;i++)
    {
        for(int j=0;j<12;j++)
        {
            if(j==0)
            {
                QStandardItem* item=new QStandardItem;
                item->setFlags(item->flags() & (~Qt::ItemIsEditable));
                item->setText(QString("船仓%1").arg(i+1));
                model->setItem(i,j,item);
            }
            else if(j==6)//下拉框
            {
                model->setData(model->index(i,j),QVariant("A"),Qt::DisplayRole);
            }
            else if(j == 8)//进度条
            {
            }
            else if(j == 3) //标称浓度
            {
                model->setData(model->index(i,3,QModelIndex()),QVariant(tr("")));
                model->item(i,3)->setTextAlignment(Qt::AlignCenter);
            }
            else
            {
//                QStandardItem* item=new QStandardItem;
//                item->setFlags(item->flags() & (~Qt::ItemIsEditable));
//                model->setItem(i,j,item);

                //文本不可编辑、居中显示
                model->setData(model->index(i,j,QModelIndex()),QVariant(tr("")));
                model->item(i,j)->setTextAlignment(Qt::AlignCenter);
                model->item(i,j)->setFlags(model->item(i,j)->flags() & (~Qt::ItemIsEditable));
            }
        }
    }

}


/**
 * @brief 得到运行步骤数据
 * @param 条码
 * @return 当前试剂运行数据
 */
QString calibration_oneWidget::getRunInfo(QString &serical)
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
 * @brief 操作按钮初始化
 */
void calibration_oneWidget::PushBtnInit()
{
    finishPlaceBtn = new QPushButton; //结束放置按钮
    finishPlaceBtn->setFixedSize(150,40);
    finishPlaceBtn->setStyleSheet("QPushButton{border-image: url(:/picture/calibrationWidget/finishPng-up.png);}"
                               "QPushButton:hover{border-image: url(:/picture/calibrationWidget/finishPng-up.png);}"
                               "QPushButton:pressed{border-image: url(:/picture/calibrationWidget/finishPng-down.png);}");
    finishPlaceBtn->setFlat(true);

    returnBtn = new QPushButton;      //返回按钮
    returnBtn->setFixedSize(150,40);
    returnBtn->setStyleSheet("QPushButton{border-image: url(:/picture/calibrationWidget/returnPng-up.png);}"
                               "QPushButton:hover{border-image: url(:/picture/calibrationWidget/returnPng-up.png);}"
                               "QPushButton:pressed{border-image: url(:/picture/calibrationWidget/returnPng-down.png);}");
    returnBtn->setFlat(true);

    nextBtn = new QPushButton;      //下一步按钮
    nextBtn->setFixedSize(150,40);
    nextBtn->setStyleSheet("QPushButton{border-image: url(:/picture/calibrationWidget/next-up.png);}"
                               "QPushButton:hover{border-image: url(:/picture/calibrationWidget/next-up.png);}"
                               "QPushButton:pressed{border-image: url(:/picture/calibrationWidget/next-down.png);}");
    nextBtn->setFlat(true);

    btnLayout = new QHBoxLayout; /**< 按钮水平布局器*/
    btnLayout->setMargin(0);
    btnLayout->setSpacing(100);
    btnLayout->addWidget(finishPlaceBtn);
    btnLayout->addWidget(returnBtn);
    btnLayout->addWidget(nextBtn);

    btnLayout->addStretch();
}
/**
 * @brief calibration_oneWidget::QCustomplotInit
 * 画图板初始化
 */
void calibration_oneWidget::QCustomplotInit()
{
    customPlot = new QCustomPlot(this);
    customPlot->setGeometry(1100,75,550,320);
    //设置完数据后可以对x，y轴进行设置
    customPlot->xAxis->setLabel("浓度");
    customPlot->yAxis->setLabel("发光值");
//    //或者设置x，y轴的范围
//    customPlot->xAxis->setRange(0,6000);
//    customPlot->yAxis->setRange(0,2700000);
    customPlot->setPalette(QPalette(QColor(243,243,243)));
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                           QCP::iSelectLegend | QCP::iSelectPlottables);
}

/**
 * @brief 结束放置按钮槽
 */
void calibration_oneWidget::finishPlaceBtnSlot()
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
    qDebug()<< QString(tr("结束放置"));
    QMap< int,QString >::iterator it;
    for(it = RunData->begin();it != RunData->end();it++){
        int postion = it.key();  //获取当前试剂船号
        statusWidget->setReagent_Status(postion,StatusWidget::RUN);//更改当前试剂船状态
        Calibration_WorkQueue->enqueue("04,06,ff,ff,00,00"+ QString(",")+ QString::number(postion,10)+QString(",")+ it.value()); //将当前试剂船运动数据加入工作队列
    }
    RunData->clear(); //清除哈希表数据
}


/**
 * @brief 下一步按钮槽
 */
void calibration_oneWidget::nextBtnSlot()
{
    for(int i = 0; i< 12;i++){
        if( statusWidget->Reagent_status[i] != StatusWidget::FREE ){
            QMessageBox::critical(this,tr("提示"),tr("当前界面有试剂船没有完成测试!"));
            return;
        }
    }
    emit measurementFinshSignal(2);
    //todo
}




/**
 * @brief calibration_okBtnDelegate::显示曲线图信号槽
 * @param index返回第几行，从0开始----------列也是从0开始
 */
void calibration_oneWidget::Display_btnSlot(const QModelIndex &index)
{  
    int row = index.row();
    if( model->data(model->index(row,9),Qt::DisplayRole) == ""){
        okBtn->Display_btns.value(row)->text = tr("");
        okBtn->Display_btns.value(row)->state &= ( ~QStyle::State_Enabled);
        QMessageBox::critical(this,tr("提示"),tr("当前试剂船没有测试完成!"));
        return;
    }
    qDebug() << "校准品操作界面---第" << index.row()+1 << "行---显示曲线" ;
    double standardConcentration = model->data(model->index(row,3)).toDouble();   //获得标准浓度
    double testPhoton = model->data(model->index(row,9)).toDouble();          //获得测量光子值
    double testConcentration = model->data(model->index(row,10)).toDouble();  //获得测量浓度
    QString serial_number = SerialNumber->value(row +1 ); //6位编码

    /**********测试数据，方便代码编写*********/
//    name = "1111";
//    standardConcentration = 2000.00;
//    testPhoton = 1110000.00;
//    testConcentration = Util::getX("1111",testPhoton);
    /***************************************/

    /**************根据项目名称获得曲线拟合方式和曲线拟合参数数组***********************/
    QSqlQuery query;
    int generation_type;    //拟合方式
    double *para = new double[6]; //函数参数数组
    QString queryStr = "select GENERATION_TYPE,PARAMETER_ONE,PARAMETER_TWO,PARAMETER_THREE,"
                       "PARAMETER_FOUR,PARAMETER_FIVE,PARAMETER_SIX "
                       "from cruve_parameter "
                       "where REAGENT_CODE = '" + serial_number + "' and DEL_FLAG = 0";
    if( !query.exec(queryStr) ){
        QMessageBox::critical(this,tr("错误代码E0027"),tr("错误代码E0027:当前试剂没有做标准曲线定标!"));
        return;
    }
    while(query.next())
    {
        generation_type = query.value("GENERATION_TYPE").toInt();//取出数据库中存储的函数系数
        para[0] = query.value("PARAMETER_ONE").toDouble();
        para[1] = query.value("PARAMETER_TWO").toDouble();
        para[2] = query.value("PARAMETER_THREE").toDouble();
        para[3] = query.value("PARAMETER_FOUR").toDouble();
        para[4] = query.value("PARAMETER_FIVE").toDouble();
        para[5] = query.value("PARAMETER_SIX").toDouble();
    }
    /**********************************************/


    /************画点---*************/
    customPlot->addGraph();
    QVector <double> key_one(1);            //第一个点
    QVector <double> value_one(1);
    key_one[0]= standardConcentration;      //标准浓度
    value_one[0] = testPhoton ;             //测量光子值
    customPlot->graph(0)->setData(key_one,value_one);//添加数据
    customPlot->graph(0)->setPen(QColor(255,0,0));
    customPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
    customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 6));
    customPlot->graph(0)->setName("点的位置");

    customPlot->addGraph();
    QVector <double> key_two(1);            //第二个点
    QVector <double> value_two(1);
    key_two[0]= testConcentration;      //计算浓度
    value_two[0] = testPhoton ;             //测量光子值
    customPlot->graph(1)->setData(key_two,value_two);//添加数据
    customPlot->graph(1)->setPen(QColor(0,0,255));
    customPlot->graph(1)->setLineStyle(QCPGraph::lsNone);
    customPlot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 6));


    /************画点结束*************/

    QVector <double> key(500);                  //将点的坐标存入QVector
    QVector <double> value(500);

    if(generation_type == LOGLINEARFIT)         //对数线性拟合
    {
        for(int i = 0;i < 500;i++)
        {
            double maxX = qLn(standardConcentration)/qLn(10);
            key[i] = maxX * 2 * i /500;
            value[i] = Util::getYValue(generation_type ,key[i],para); //根据浓度、拟合方式和拟合参数数组求光子值
        }
    }else{
        for(int i = 0;i < 500;i++)
        {
            key[i] = standardConcentration * 2 * i /500;
            value[i] = Util::getYValue(generation_type ,key[i],para); //根据浓度、拟合方式和拟合参数数组求光子值
        }
    }

    if(generation_type == LOGLINEARFIT)
    {
        customPlot->xAxis->setLabel("浓度对数值");
        customPlot->yAxis->setLabel("发光值对数值");
    }else{
        customPlot->xAxis->setLabel("浓度");
        customPlot->yAxis->setLabel("发光值");
    }
    //或者设置x，y轴的范围
    customPlot->xAxis->setRange(0,standardConcentration* 2.2);
    customPlot->yAxis->setRange(0,testPhoton * 2.2);

    /*************画曲线***********/
    customPlot->addGraph();
    customPlot->graph(2)->setData(key,value);//添加数据
    customPlot->graph(2)->setPen(QColor("cyan"));

    /*************画曲线***********/

    customPlot->replot();
}

/**
 * @brief calibration_oneWidget::校准品询问空闲超时定时器超时信号槽
 */
void calibration_oneWidget::calibration_queryTimerOverSlot()
{
    if( !Calibration_WorkQueue->isEmpty() ){
        serialPort::mySend_Data("04,05,ff,ff,00,00");
    }
}


