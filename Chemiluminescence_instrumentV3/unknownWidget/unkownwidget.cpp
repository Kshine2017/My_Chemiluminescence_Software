#include "unkownwidget.h"
#include <QPixmap>
#include <QDebug>
#include <QString>
#include "data/connection.h"
#include "systemWidget/reagentNumber/databaseoperation.h"
#include <QStyle>
#include "data/util.h"
UnkownWidget::UnkownWidget(QWidget *parent) : QWidget(parent)
{
    mainlayout = new QVBoxLayout;
    infolayout = new QHBoxLayout;
    mainlayout->setMargin(0);
    infolayout->setMargin(0);
    /**
     * @brief 窗口标题初始化
     */
    titleInit();

 //状态和病人信息界面
    statusWidget = new StatusWidget; //状态显示窗口


    //输入信息部分的底框
    label_backpic = new QLabel(this);

    QPixmap pix_background(":/picture/unknowWidget/lineEdit_background.png");
    pix_background.scaled(label_backpic->size(), Qt::IgnoreAspectRatio);
    label_backpic->setScaledContents(true);
    label_backpic->setPixmap(pix_background);
    label_backpic->setGeometry(1150,75,480,328);
    infoWidget = new InfoWidget;   //信息录入窗口
    //添加到水平布局
    infolayout->addSpacing(10);
    infolayout->addWidget(statusWidget);
    infolayout->addSpacing(50);
    infolayout->addWidget(infoWidget);
    infolayout->addSpacing(50);

//底层界面初始化
    underWidget = new QWidget;
    underWidget->setAutoFillBackground(true);
    QPalette underPalette;
    QPixmap pixmap(":/picture/unknowWidget/underWidget_background.png");
    underPalette.setBrush(QPalette::Window,QBrush(pixmap));
    underWidget->setPalette(underPalette);
    underWidget->setFixedSize(1671,606); //大小根据图片来

    tableModel_Init(); //模型视图初始化


     mainlayout->addWidget(WindowTile);
     mainlayout->addLayout(infolayout);
     mainlayout->addSpacing(40);
     mainlayout->addWidget(underWidget);
     setLayout(mainlayout);

//全局变量初始化
     for(int i = 0; i< 12;i++){
         OkBtnState[i] = {NO_CLICKED}; //ok确定键状态
         StartBtnState[i] = {NO_CLICKED};//开始键状态
     }
     RunData = new QMap<int,QString>; //申请一个QMap容器来储存临时插入试剂船的运行数据

     SerialNumber = new QMap<int,QString>; //储存各试剂船序列号
     /**
      * @brief 工作队列和队列定时器
      */
     WorkQueue = new Queue(this);  //申请一个工作队列

     queryTimer = new QTimer(this); //定时器
     queryTimer->setInterval(UNKNOW_INQUIRY_TIME);
     queryTimer->setSingleShot(false); //设置为循环定时器
     queryTimer->start();

     /**
      * @brief 信号和槽连接函数
      */
     connectInit();


}

/**
 * @brief 设置space_num行试剂船信息内容
 * @param space_num 行
 * @param data 数据
 * @param length 数据长度
 */
void UnkownWidget::setModel_ReagentInfo(int space_num, QByteArray &data, int length)
{
    Q_UNUSED(length);
    int postion = space_num;
    QString sericalNum = "";   //条码号
    QString category = ""; //试剂品类
    QString project_name = "";//项目名称
    QString Reagent_kind = ""; //试剂种类
    QString Detection_Kind = ""; //检测种类
    int Produce_year = 0; //生产日期-年
    int Produce_mouth = 0; //生产日期-月
    int Expiration_date = 0;//保质期
    int Batch_Number = 0;  //批号
 /*****************进行ASCII码判断**********************************************************/
    for(int i = 0; i < data.size()-7;i++)
    {
        if( data.at(7+i) < 0x30 ){
            emit serialPort::ReceiveThread.ErrDataSign("扫码枪数据不对");
            return;
        }
    }
/********进行生产日期判断*******************************************************************************/
    if( data.at(7+4) <= 0x39){                            //获取年
        Produce_year = QString::number((data.at(7+4)-0x30),16).toInt() + 2018;
    }else if(data.at(7+4) >=0x41){
        Produce_year = QString::number((data.at(7+4)-0x41),16).toInt() + 2028;
    }

    if( data.at(7+5) <= 0x39){                            //获取月
        Produce_mouth = QString::number((data.at(7+5)-0x30),16).toInt();
    }else if(data.at(7+5) >=0x41){
        Produce_mouth = QString::number((data.at(7+5)-0x41),16).toInt() + 10;
    }

    if( data.at(7+7) == 0x36){  //获取保质期
       Expiration_date = 6;
    }else if( data.at(7+7) == 0x43 ){
       Expiration_date = 12;
    }
    /************获取当前时间*************************/
    int current_date_year = QDateTime::currentDateTime().toString("yyyy").toInt();
    int current_date_mouth = QDateTime::currentDateTime().toString("M").toInt();
 /*************判断是否过期或者条码与实际日期不符合****************************************/
    if( ( current_date_year *12 + current_date_mouth ) < ( Produce_year * 12 + Produce_mouth ) ){
        qDebug() << "当前条码日期比当前实际日期早";
        serialPort::ReceiveThread.ErrDataSign("此条码编码异常");
        return;
    }else if( ( current_date_year *12 + current_date_mouth ) - ( Produce_year * 12 + Produce_mouth ) > Expiration_date ){
        qDebug() << "当前试剂过期" << Produce_year << Produce_mouth << "保质期限" << Expiration_date;
        serialPort::ReceiveThread.ErrDataSign("此试剂已过期");
        return;
    }

/*****************生产批号*******************************************************************************/
    if( data.at(7+6) <= 0x39){                            //获取批号
        Batch_Number = QString::number((data.at(7+6)-0x30),16).toInt();
    }else if(data.at(7+6) >=0x41){
        Batch_Number = QString::number((data.at(7+6)-0x41),16).toInt() + 10;
    }
/********根据条码检索数据库里面类容*********************************************************/
    for(int i = 0;i < 4 ;i++){
         sericalNum.append(char(data.at(7+i))); //条码前四位
    }
    DatabaseOperation data_op;
    data_op.getReagentInfoByCode(category,project_name,Reagent_kind,sericalNum); //通过数据库得到项目名称和种类
    Detection_Kind = project_name + "-" + Reagent_kind;  //检测项目

    for( int i = 0;i < 3; i++ ){
        sericalNum.append(char(data.at(11+i))); //条码前7位
    }


    model->setData(model->index(postion-1,1),QVariant( Detection_Kind ));
    model->setData(model->index(postion-1,2),QVariant( ( QString::number(Produce_year,10) + "年" + QString::number(Produce_mouth,10) + "月第" + QString::number(Batch_Number,10)+ "批" ) ));
    tableView->reset();
    if( getRunInfo(sericalNum) == "") return;  //无此试剂运行数据
    //插入临时试剂船运行数据进储存QMap
    if(RunData->contains(postion)){  //当前位置是否已经有数据
        QMap<int,QString>::iterator it  = RunData->find(postion);
        it.value() = getRunInfo(sericalNum); //插入数据进入
    }
    else RunData->insert(postion,getRunInfo(sericalNum));  //查找运行数据并加入QMap进行临时数据保存;
    SerialNumber->insert(postion,sericalNum.remove(0,1));  //储存第二位到第七位条码用于查询标准曲线
}




/**
 * @brief 窗口标题初始化
 */
void UnkownWidget::titleInit()
{
    WindowTile = new QLabel(this);
    WindowTile->setPixmap(QPixmap(":/picture/unknowWidget/unkonwTitle.png"));
    WindowTile->setGeometry(0,0,1687,69);

    statusTitleLab = new QLabel(WindowTile);
    statusTitleLab->setText(tr("试剂船状态"));
    patientTitleLab = new QLabel(WindowTile);   //患者信息头
    patientTitleLab->setText(tr("患者信息"));
    questionBtn = new QPushButton(this);
    questionBtn->setIconSize(QSize(45,45));
    questionBtn->setIcon(QIcon(":/picture/unknowWidget/？btn.png"));
    questionBtn->setFlat(true);

    QPalette   pal;//按键字体颜色设置
    pal.setColor(QPalette::WindowText, QColor(255, 255, 255, 255));
    statusTitleLab->setPalette(pal);
    statusTitleLab->setFont(QFont("windowTitle",15));
    statusTitleLab->setGeometry(80,13,100,40);
    patientTitleLab->setPalette(pal);
    patientTitleLab->setFont(QFont("windowTitle",15));
    patientTitleLab->setGeometry(1185,13,100,40);
    questionBtn->setGeometry(1600,1,45,45);

}



/**
 * @brief 模型视图初始化
 */
void UnkownWidget::tableModel_Init()
{
    model = new QStandardItemModel(12,12); //模型视图
    //让tableView中的文本居中
    for(int i = 0 ;i < 12 ;i++)
    {
        for(int j = 0;j < 12;j++)
        {
            if(j!=4 &&j !=6 && j!= 11)//4、6、11列均为代理
            {
                model->setData(model->index(i,j,QModelIndex()),QVariant(tr("")));
                model->item(i,j)->setTextAlignment(Qt::AlignCenter);
            }
        }
    }
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("序号"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("检测名称"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("批号"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("患者信息"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("启动按钮"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("当前工作阶段"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("进度条"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("开始时间"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("结束时间"));
    model->setHeaderData(9,Qt::Horizontal,QObject::tr("测量光子值"));
    model->setHeaderData(10,Qt::Horizontal,QObject::tr("浓度"));
    model->setHeaderData(11,Qt::Horizontal,QObject::tr("结束按钮"));
    model->setData(model->index(0,0,QModelIndex()),QVariant(tr("船仓1")));
    model->setData(model->index(1,0,QModelIndex()),QVariant(tr("船仓2")));
    model->setData(model->index(2,0,QModelIndex()),QVariant(tr("船仓3")));
    model->setData(model->index(3,0,QModelIndex()),QVariant(tr("船仓4")));
    model->setData(model->index(4,0,QModelIndex()),QVariant(tr("船仓5")));
    model->setData(model->index(5,0,QModelIndex()),QVariant(tr("船仓6")));
    model->setData(model->index(6,0,QModelIndex()),QVariant(tr("船仓7")));
    model->setData(model->index(7,0,QModelIndex()),QVariant(tr("船仓8")));
    model->setData(model->index(8,0,QModelIndex()),QVariant(tr("船仓9")));
    model->setData(model->index(9,0,QModelIndex()),QVariant(tr("船仓10")));
    model->setData(model->index(10,0,QModelIndex()),QVariant(tr("船仓11")));
    model->setData(model->index(11,0,QModelIndex()),QVariant(tr("船仓12")));

    //代理
    checkNameDelegate = new check_nameDelegate;
    serialNumDelegate = new serial_numDelegate;
    progessBarDelegate = new progress_BarDelegate;
    startPushButtonDelegate = new start_PushButtonDelegate;
    okbtnDelegate = new okbtn_Delegate;
    //视图
    tableView = new QTableView(underWidget);
    tableView->setModel(model);             //将模型挂载视图
    tableView->setGeometry(7,60,1657,606);  //设置其位置


    tableView->setItemDelegateForColumn(2,checkNameDelegate);
    tableView->setItemDelegateForColumn(6,progessBarDelegate);
    tableView->setItemDelegateForColumn(4,startPushButtonDelegate);
    tableView->setItemDelegateForColumn(11,okbtnDelegate);

    /*tableView设置集合*/
    //设置其选择行为，并不可以编辑
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode ( QAbstractItemView::SingleSelection);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
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
    tableView->setStyleSheet("selection-background-color: rgb(224, 224, 224)");
    //设置列宽
    tableView->setColumnWidth(0,60);
    tableView->setColumnWidth(1,130);
    tableView->setColumnWidth(2,130);
    tableView->setColumnWidth(3,150);
    tableView->setColumnWidth(4,100);
    tableView->setColumnWidth(5,150);
    tableView->setColumnWidth(6,280);
    tableView->setColumnWidth(7,140);
    tableView->setColumnWidth(8,140);
    tableView->setColumnWidth(9,110);
    tableView->setColumnWidth(10,130);
    tableView->setColumnWidth(11,130);
    tableView->setColumnWidth(12,40);
    //设置：行高
    tableView->verticalHeader()->setDefaultSectionSize(42);
    selectModel = tableView->selectionModel(); //选择模型定义，用于触发选择
}
/**
 * @brief 试剂船拔出处理函数
 * @param postion
 */
QString UnkownWidget::reagentPopup_CMDHandle(int postion)
{
    QString returnStr = "";
    if(postion < 0 || postion > 12){
        qDebug()<< "当前试剂船，船舱号超过本设备最大设备船仓数量";
        return "";
    }
    if( statusWidget->Reagent_status[postion-1] == StatusWidget::RUN){
        emit serialPort::ReceiveThread.ErrDataSign("当前试剂船正在运行,被强制拔出");
    }
    returnStr = "01,02,ff,ff,00,02,"+QString::number(postion,10)+",02"; //绿灯灭
    statusWidget->setReagent_Status(postion,StatusWidget::FREE);
/****试剂船拔出时，清除相应图标数据***********************************************************************/
    for(int i = 1;i < 4; i++ ){
        model->setData(model->index(postion-1,i),QVariant(""));  //清空图标数据
    }
    model->setData(model->index(postion-1,5),QVariant(""));  //清空图标数据
    model->setData(model->index(postion-1,6),QVariant(0));  //清空进度条
    for(int i = 7;i < 11; i++ ){
        model->setData(model->index(postion-1,i),QVariant(""));  //清空图标数据
    }
    tableView->reset();
    infoWidget->patientInfo.remove(postion-1);//清除当前列对应的病人信息
    startPushButtonDelegate->m_btns.value( postion-1)->icon = QIcon(":/picture/unknowWidget/complate-up.png");//启动按钮不能启动
    startPushButtonDelegate->m_btns.value(postion-1)->state &= ( ~QStyle::State_Selected ); //清除启动按钮禁止启动标志
    okbtnDelegate->OK_btns.value(postion-1)->state &= ( ~QStyle::State_Selected ); //清除启动按钮禁止启动标志
    OkBtnState[ postion-1 ] = NO_CLICKED; //保存按钮可以点击
    return returnStr;
}

/**
 * @brief 试剂船进度处理函数
 * @param postion
 */
void UnkownWidget::returnProgress_InfoHandle(QByteArray &data)
{
    unsigned char num = data.at(6)&0xff; //返回进度数量
    unsigned char postion ; //当前槽号
    QString startTime;
    QString endTime;
    QString currentStage; //当前阶段
    for(int i = 0;i < num; i++){
        postion = (data.at(7 + 17*i )&0xff) ;
        qDebug() << "当前试剂船位置 = "<< postion;
        if(postion < 1 || postion > 12) return;

        switch( data.at(8+ 17*i) & 0xff )
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
        unsigned char progressData = data.at(9 + i*17) & 0xff; //进度

        unsigned short int start_year = ( (unsigned short int)(data.at(10 + i*17) & 0xff) << 8 ) | ( data.at(11 + i*17) & 0xff );
        unsigned char start_month = data.at(12 + i*17) & 0xff;
        unsigned char start_day = data.at(13 + i*17) & 0xff;
        unsigned char start_hour = data.at(14 + i*17) & 0xff;
        unsigned char start_minute = data.at(15 + i*17) & 0xff;
        unsigned char start_second = data.at(16 + i*17) & 0xff;

        if( !start_year ) continue;
        unsigned short int end_year = ( (unsigned short int)(data.at(17 + i*17) & 0xff) << 8 ) | ( data.at(18 + i*17) & 0xff );
        unsigned char end_month = data.at(19 + i*17) & 0xff;
        unsigned char end_day = data.at(20 + i*17) & 0xff;
        unsigned char end_hour =data.at(21 + i*17) & 0xff;
        unsigned char end_minute = data.at(22 + i*17) & 0xff;
        unsigned char end_second = data.at(23 + i*17) & 0xff;

        startTime += (QString::number(start_year,10) + "/" + QString::number(start_month,10) + "/" + QString::number(start_day,10) +" "
                      +QString::number(start_hour,10) + ":"+QString::number(start_minute,10)+":"+QString::number(start_second,10)  );
        endTime += (QString::number(end_year,10) + "/" + QString::number(end_month,10) + "/" + QString::number(end_day,10) +" "
                    +QString::number(end_hour,10) + ":"+QString::number(end_minute,10)+":"+QString::number(end_second,10)  );

        model->setData(model->index(postion-1,7),QVariant(startTime));  //开始时间
        model->setData(model->index(postion-1,8),QVariant(endTime)); //结束时间
        model->setData(model->index(postion-1,5),QVariant(currentStage)); //当前阶段
        model->setData(model->index(postion-1,6),QVariant(progressData)); //当前测试进度
        startTime = "";
        endTime = "";
        currentStage = "";
        tableView->reset();
    }
}
/**
 * @brief 试剂船错误处理函数
 * @param err
 */
void UnkownWidget::returnRegent_ErrHandle(QByteArray &err)
{
    Q_UNUSED(err);

}

/**
 * @brief UnkownWidget::测试结果处理函数
 * @param data
 */
void UnkownWidget::testResultHandle(QByteArray &data)
{
    QSqlQuery query;
    unsigned long photon_result; //最终计算的光子值
    unsigned int temp; //临时变量
    unsigned char postion  = data.at(6 ) & 0xff ; //当前槽号
    if( postion < 1 || postion > 12) return;
    unsigned char photon_number = data.at(7 ) & 0xff ; //当前光子值数量
    qDebug() << "当前收到"<< photon_number << "个光子值";
    unsigned int *TempPhoton_Value = new unsigned int[photon_number] ; //给进行光子运算申请堆空间
    memset(TempPhoton_Value,0,sizeof(unsigned int) * photon_number); //清理堆空间缓存
    for(int i = 0; i < photon_number; i++){
        TempPhoton_Value[i] = ((unsigned int )(data.at(8 + i*4 ) & 0xff)) << 24 | (data.at(9 + i*4) & 0xff) << 16 | (data.at(10 + i*4 ) & 0xff) << 8 | (data.at(11 + i*4 ) & 0xff);
  //      qDebug() << "第" << i+1 << "光子值 = " << TempPhoton_Value[i];
    }
    /*******冒泡排序将光子值进行排序**********************************/
    for(int i = 0;i < photon_number-1;i++){
        for(int j = 0;j < photon_number-i;j++){
            if( TempPhoton_Value[j] > TempPhoton_Value[j+1]){
                temp = TempPhoton_Value[j];
                TempPhoton_Value[j] = TempPhoton_Value[j+1];
                TempPhoton_Value[j+1] = temp;
            }
        }
    }
    /***********取最大10个点之和作为光子值******************************************/
    for(int i = photon_number-1;i > photon_number-11;i-- ){
//        qDebug() << "当前最大值第" << i << "值"<< TempPhoton_Value[i];
        photon_result += TempPhoton_Value[i];
    }
    qDebug() <<"当前测试光子数" << photon_result;
    statusWidget->setReagent_Status(postion,StatusWidget::FINISH); //试剂船状态进行切换
    delete []TempPhoton_Value; //释放空间
    QString queryStr = "select GENERATION_TYPE,PARAMETER_ONE,PARAMETER_TWO,PARAMETER_THREE,"
                       "PARAMETER_FOUR,PARAMETER_FIVE,PARAMETER_SIX "
                       "from cruve_parameter "
                       "where REAGENT_CODE = '" + SerialNumber->value(postion) + "' and DEL_FLAG = 0";

    if( !query.exec(queryStr)){
        QMessageBox::critical(this,tr("错误代码E0027"),tr("错误代码E0027:当前试剂没有做标准曲线定标!"));
        model->setData(model->index(postion-1,9),QVariant(QString::number(photon_result,10))); //当前光子测试结果
        tableView->reset();
        return;
    }
    /*************根据进行浓度计算*****************************************************************/
    double concentration = Util::getX(SerialNumber->value(postion),(double)photon_result); //进行浓度换算
    model->setData(model->index(postion-1,9),QVariant(QString::number(photon_result,10))); //当前光子测试结果
    model->setData(model->index(postion-1,10),QVariant(QString::number(concentration,8,7)));
    tableView->reset();
}

/**
 * @brief 信号和槽绑定函数
 */
void UnkownWidget::connectInit()
{
    connect(okbtnDelegate,SIGNAL(OkBtnClicked(QModelIndex)),this,SLOT(OkBtnSlot(QModelIndex)));
    connect(startPushButtonDelegate,SIGNAL(startBtnClicked(QModelIndex)),this,SLOT(startBtnSlot(QModelIndex)));
    connect(selectModel,SIGNAL(selectionChanged(QItemSelection,QItemSelection)),this,SLOT(selectionIndexesSlot(QItemSelection,QItemSelection)));
    connect(infoWidget,SIGNAL(OKBtnPress(int)),this,SLOT(infoWidgetOkBtnSlot(int)));
    connect(this,SIGNAL(selectRowSign(int)),infoWidget,SLOT(selectRowSignSlot(int)));
    connect(&serialPort::ReceiveThread,SIGNAL(unkonow_cmdSign(QString)),this,SLOT(unkonow_cmdSignSlot(QString)),(Qt::ConnectionType)(Qt::UniqueConnection|Qt::QueuedConnection));//
    connect(this->queryTimer,SIGNAL(timeout()),this,SLOT(Unknow_queryTimerOverSlot()));
}

/**
 * @brief 得到运行步骤数据
 * @param 条码
 * @return 当前试剂运行数据
 */
QString UnkownWidget::getRunInfo(QString &serical)
{
    QString serical_num = serical;
    qDebug() << "当前条码前四位" << serical_num;
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
    return "";
}


/**
 * @brief UnkownWidget::tableview按钮信号槽
 */
void UnkownWidget::OkBtnSlot(const QModelIndex &index)
{
   QSqlQuery query;
   QString returnCMD; //返回码大小
   int row = index.row();
   if(OkBtnState[row]){
     QMessageBox::information(this,tr("提示！"),tr("当前试剂船测试结果已经保存!"));
     qDebug() <<"当前按钮已经按下" ;
     return;
   }
   //点击哪个确认按钮将数据写入数据库
   QStringList stringList = infoWidget->patientInfo.value(row);
   if(stringList.isEmpty()){
       QMessageBox::information(this,tr("提示！"),tr("当前病人信息不完整,请输入完整病人信息!"));
       return;
   }
   if( statusWidget->Reagent_status[row] != StatusWidget::FINISH ){
       QMessageBox::information(this,tr("提示！"),tr("当前病人测试项目未完成!"));
       return;
   }
   /**设置试剂船上面的状态指示灯**/
   returnCMD = "01,01,ff,ff,00,02,"+QString::number(row+1,16)+",02"; //红灯灭
   emit serialPort::ReceiveThread.sendDataSign(returnCMD);
   returnCMD = "01,02,ff,ff,00,02,"+QString::number(row+1,16)+",01"; //绿灯闪
   emit serialPort::ReceiveThread.sendDataSign(returnCMD);

   query.exec("insert into patient_info values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
   query.bindValue(1,stringList.at(0));
   query.bindValue(2,stringList.at(1));
   query.bindValue(3,stringList.at(2));
   query.bindValue(4,stringList.at(3));
   query.bindValue(5,stringList.at(4));
   query.bindValue(6,stringList.at(5));
   query.bindValue(7,model->data(model->index(row,1),Qt::DisplayRole));
   query.bindValue(8,model->data(model->index(row,2),Qt::DisplayRole));
   query.bindValue(9,model->data(model->index(row,10),Qt::DisplayRole));
   query.bindValue(10,0);
   query.bindValue(11,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
   query.bindValue(12,0);
   query.bindValue(13,0);
   query.bindValue(14,0);

   if(!query.exec())
   {
       QMessageBox::critical(this,QObject::tr("错误代码:E0016"),query.lastError().text());
   }
   OkBtnState[row] = CLICKED;
   if( startPushButtonDelegate->m_btns.contains( index.row() ) ){
       qDebug() << "更改当前启动按钮状态";
       startPushButtonDelegate->m_btns.value(index.row())->state &= ( ~QStyle::State_Selected ); //清除启动按钮禁止启动标志
       startPushButtonDelegate->m_btns.value(index.row())->icon = QIcon(":/picture/unknowWidget/complate-up.png");
   }
   QMessageBox::information(this,tr("提示！"),tr("当前检测信息保存完成!"));
}


/**
 * @brief 启动测试按钮控制函数
 * @param index
 */
void UnkownWidget::startBtnSlot(const QModelIndex &index)
{
    int row = index.row();
    if ( row > 255 ) return; //试剂船舱不能超过255行
    if(statusWidget->Reagent_status[row] != StatusWidget::AWAIT){
        startPushButtonDelegate->m_btns.value(index.row())->icon = QIcon(":/picture/unknowWidget/complate-up.png");//启动按钮不能启动
        QMessageBox::warning(this,tr("提示!"),tr("当前试剂船舱不处于等待测试状态!"));
        return;
    }
    if( !RunData->contains(row+1) ){
        startPushButtonDelegate->m_btns.value(index.row())->icon = QIcon(":/picture/unknowWidget/complate-up.png");//启动按钮不能启动
        QMessageBox::warning(this,tr("提示!"),tr("当前数据库无此试剂船项目!"));
        return;
    }
    statusWidget->setReagent_Status(row+1,StatusWidget::RUN);//设置试剂船现在状态

    /*****根据当前启动按钮的工作内容将工作任务加入队列，注意1~3仓是抢占的**********/
    if( row < 3){
        WorkQueue->frontEnqueue("01,06,ff,ff,00,00"+QString(",")+ QString::number(row+1,16)+QString(",")+ RunData->find(row+1).value()); //插入队首
        return;
    }else{
        /***仅仅用于测试********************/
        WorkQueue->enqueue("01,06,ff,ff,00,00"+ QString(",")+ QString::number(row+1,16)+QString(",")+ RunData->find(row+1).value());
    }
}

/**
 * @brief 选择行信号，根据选择行信号和病人信息录入窗口绑定
 */
void UnkownWidget::selectionIndexesSlot(QItemSelection newSelect, QItemSelection delSelect)
{
    Q_UNUSED(delSelect);
    QModelIndex index;
    QModelIndexList items = newSelect.indexes();
    if(items.isEmpty())return;
    index = items.at(0);
    QString infStr = "";
    if(index.row() < 9){
        infStr = QString(tr("    舱位 0%1").arg(index.row()+1));
    }else{
        infStr = QString(tr("    舱位 %1").arg(index.row()+1));
    }
    //设置船舱信息
    infoWidget->PositionLab->setText(infStr);
    emit selectRowSign(index.row());
}

/**
 * @brief UnkownWidget::接收从信息框发送过来的确定信号slot
 */
void UnkownWidget::infoWidgetOkBtnSlot(int num)
{
    QStringList stringList = infoWidget->patientInfo.value(num);
    if(stringList.isEmpty()) return;
    qDebug() <<"当前第" <<num << "试剂船信息被确定";
    QString name = stringList.at(1);
    model->setData(model->index(num,3),QVariant(name));
}
/**
 * @brief 未知品命令处理
 * @param str
 */
void UnkownWidget::unkonow_cmdSignSlot(QString str)
{
    QByteArray Receive_array = 0;
    QString returnCMD = "";
    int postion = 0;
    qDebug()<<"处理信号槽线程ID = " <<QThread::currentThreadId();
    qDebug() << "未知品收到一条命令" << str;
    Receive_array = serialPort::HEXStringToArr(str);
    uint16_t dataLength = (uint16_t)(((Receive_array.at(4)&0xffff)<< 8)|(Receive_array.at(5)&0xff));//数据长度
    unsigned char cmd = (Receive_array.at(1) & 0xff); //命令

    if( ( Receive_array.at(0) & 0xff) & 0x40 ){   //MCU返回码命令解析
        switch(cmd){
        case UNKONOE_WHETHER_FREE_RETURN_CMD:
            qDebug()<< "未知品收到MCU空闲命令返回";
            if( dataLength != 1){
                emit serialPort::ReceiveThread.ErrDataSign("数据长度不对");
                return;
            }
            if( !( Receive_array.at(6) & 0xff ) ){ //判断是否空闲
                qDebug() << "是空闲命令";
                if( !WorkQueue->isEmpty()){ /**<发送任务队列队首 */
                    QString str;
                    WorkQueue->dequeue(str);
                    qDebug() << "队列字符串"<< str;
                    emit serialPort::ReceiveThread.sendDataSign(str);
                }
            }else{
                qDebug() << "是忙命令";
            }
            break;
        case UNKONOE_WHEHTER_SCHED_RETURN_CMD:
            if( dataLength != 1){
                qDebug() << "未知品调度命令数据长度不对";
                 emit serialPort::ReceiveThread.ErrDataSign("数据长度不对");
                return;
            }
            qDebug()<< "未知品收到MCU可不可以调度命令返回";
            if( (Receive_array.at(6) & 0xff) ){ //判断是否可以调度
                qDebug() << "是不可调度命令";
            }else{
                qDebug() << "是可调度命令";
                emit serialPort::ReceiveThread.sendDataSign("01,01,ff,ff,00,01,01");//红灯闪
            }
            break;
        }
        return;
    }
    /***MCU主动发送的命令解析************************************************/
    switch(cmd){
    case UNKONOW_PULL_SHIP_CMD:
        qDebug()<< "未知品收到MCU有试剂船拔出命令";
        if( dataLength != 1){
            //插入错误数据表
            qDebug() << "未知品拔出命令数据长度不对";
             emit serialPort::ReceiveThread.ErrDataSign("数据长度不对");
            return;
        }   
        postion = Receive_array.at(6)&0xff;//位置
        returnCMD = reagentPopup_CMDHandle( postion );
        emit serialPort::ReceiveThread.sendDataSign(returnCMD);
        break;
    case UNKONOE_ALL_TEST_PROGRESS_CMD:
        qDebug()<< "未知品收到所有试剂船进度MCU命令";
        if( !( dataLength == 205 || dataLength == 18 ) ){
            //插入错误数据表
            qDebug() << "未知品收到所有试剂船进度MCU命令数据长度不对";
            emit serialPort::ReceiveThread.ErrDataSign("数据长度不对");
            return;
        }
        returnProgress_InfoHandle( Receive_array );

        break;
    case UNKONOE_ERR_INFOR_CMD:
        qDebug()<< "未知品收到错误信息MCU命令";
        if( dataLength != 1){
            //插入错误数据表
            qDebug() << "未知品调度命令数据长度不对";
            emit serialPort::ReceiveThread.ErrDataSign("数据长度不对");
            return;
        }
        returnRegent_ErrHandle( Receive_array); //错误处理函数
        break;
    case UNKONOW_NEW_SHIP_INFOR_CMD:
        qDebug()<< "未知品收到一条插入新试剂船信息";
        if( dataLength != 17){
            //插入错误数据表
            qDebug() << "未知品插入新试剂船命令数据长度不对";
            emit serialPort::ReceiveThread.ErrDataSign("数据长度不对");
            return;
        }
        postion = Receive_array.at(6)&0xff;
        if( postion <= 12 && postion > 0 ){   //试剂船船舱号最大也就12个船舱
            statusWidget->setReagent_Status(postion,StatusWidget::AWAIT);//设置试剂船现在状态
            setModel_ReagentInfo(postion,Receive_array,dataLength); //设置当前试剂船条码
            returnCMD = "01,01,ff,ff,00,02,"+QString::number(postion,16)+",00"; //红灯闪
            emit serialPort::ReceiveThread.sendDataSign(returnCMD);
        }
        break;
    case UNKONOE_ONE_TEST_DATA_CMD:
        qDebug()<< "未知品某一条试剂测试结果信息";
        if( dataLength < 10){
            qDebug() << "未知品某一条试剂测试结果缺少数据";
            emit serialPort::ReceiveThread.ErrDataSign("数据长度不对");
            return;
        }
        testResultHandle( Receive_array );
/**
  ** 处理测试结果
  **/
       break;
    }
}


/**
 * @brief UnkownWidget::询问是否空闲超时信号槽
 */
void UnkownWidget::Unknow_queryTimerOverSlot()
{
    if( !WorkQueue->isEmpty() ){
        serialPort::mySend_Data("01,05,ff,ff,00,00");  //发送询问是否空闲命令
    }
}







