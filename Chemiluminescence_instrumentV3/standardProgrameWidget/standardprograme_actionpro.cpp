#include "standardprograme_actionpro.h"
#include <QDebug>
#include <QLineEdit>
#include "standardProgrameWidget/standardpragramewidget.h"
#include "QMessageBox"
standardPrograme_actionPro::standardPrograme_actionPro(QWidget *parent) : QWidget(parent)
{
    tabelViewInit();
    setActionTabel_delegate();
    connectInit();
}

/**
 * @brief standardPrograme_actionPro::视图窗口初始化
 */
void standardPrograme_actionPro::tabelViewInit()
{
    tableView = new QTableView(this);
    tableView->setFixedSize(ACTION_TABLE_WIDTH,ACTION_TABLE_HIGHT);

    model = new QStandardItemModel;
    model->setColumnCount(18);
    model->setRowCount(19);
    tableView->setModel(model);

    /***视图横向和纵向头标题隐藏*****************************/
    tableView->horizontalHeader()->hide();
    tableView->verticalHeader()->hide();
    tableView->verticalScrollBar()->setStyleSheet("QScrollBar:vertical{"        //垂直滑块整体
                                                  "background:#FFFFFF;"  //背景色
                                                  "padding-top:20px;"    //上预留位置（放置向上箭头）
                                                  "padding-bottom:20px;" //下预留位置（放置向下箭头）
                                                  "padding-left:3px;"    //左预留位置（美观）
                                                  "padding-right:3px;"   //右预留位置（美观）
                                                  "border-left:1px solid #d7d7d7;}"//左分割线
                                                  "QScrollBar::handle:vertical{"//滑块样式
                                                  "background:#dbdbdb;"  //滑块颜色
                                                  "border-radius:6px;"   //边角圆润
                                                  "min-height:80px;}"    //滑块最小高度
                                                  "QScrollBar::handle:vertical:hover{"//鼠标触及滑块样式
                                                  "background:#d0d0d0;}" //滑块颜色
                                                  "QScrollBar::add-line:vertical{"//向下箭头样式
                                                  "background:url(:/picture/standardPrograme/arrow_down.png) center no-repeat;}"
                                                  "QScrollBar::sub-line:vertical{"//向上箭头样式
                                                  "background:url(:/picture/standardPrograme/arrow_up.png) center no-repeat;}");
    tableView->setColumnWidth(0,75); //选择
    tableView->setColumnWidth(1,70); //步骤
    tableView->setColumnWidth(2,125); //名称
    tableView->setColumnWidth(3,95); //起始位置
    tableView->setColumnWidth(4,105); //#1
    tableView->setColumnWidth(5,95); //放置位置
    tableView->setColumnWidth(6,105); //#1
    tableView->setColumnWidth(7,135); //温育时间（m）
    tableView->setColumnWidth(8,50); //123
    tableView->setColumnWidth(9,125); //前序混匀次数
    tableView->setColumnWidth(10,44); //0
    tableView->setColumnWidth(11,125); //后续混匀次数
    tableView->setColumnWidth(12,44); //0
    tableView->setColumnWidth(13,115); //试剂量（ul）
    tableView->setColumnWidth(14,50); //0
    tableView->setColumnWidth(15,115); //所需时间： 120
    tableView->setColumnWidth(16,50); //0
    tableView->setColumnWidth(17,110); //单步运行
    tableView->verticalHeader()->setDefaultSectionSize(35); //26
    //tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
    //tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setEditTriggers(QAbstractItemView::AllEditTriggers);

    for(int i = 1;i <20;i++){
        QStandardItem* item2=new QStandardItem;
        item2->setText(QString("步骤:%1").arg(i));
        item2->setFlags(item2->flags() & (~Qt::ItemIsEditable));
        model->setItem(i-1,1,item2);

        QStandardItem* item3=new QStandardItem;
        item3->setText(tr(""));
        item3->setFlags(item3->flags() & (~Qt::ItemIsEditable));
        model->setItem(i-1,2,item3);


        QStandardItem* item4=new QStandardItem;
        item4->setText(tr("起始位置:"));
        item4->setFlags(item4->flags() & (~Qt::ItemIsEditable));
        model->setItem(i-1,3,item4);

        model->setData(model->index(i-1,4),QVariant(tr("#1")));

        QStandardItem* item6=new QStandardItem;
        item6->setText(tr("放入位置:"));
        item6->setFlags(item6->flags() & (~Qt::ItemIsEditable));
        model->setItem(i-1,5,item6);

        model->setData(model->index(i-1,6),QVariant(tr("温育孔#1")));

        QStandardItem* item8=new QStandardItem;
        item8->setText(tr("温育时间(s)："));
        item8->setFlags(item8->flags() & (~Qt::ItemIsEditable));
        model->setItem(i-1,7,item8);



        model->setData(model->index(i-1,8),QVariant(tr("0"))); //温育时间数值
//        QLineEdit* mle9=new QLineEdit(this);
//        mle9->setStyleSheet("background:transparent;border-width:0;border-style:outset");
//        QRegExp rx("^[1-9]\d*|0$"); //正整数，含0
//        mle9->setValidator(new QRegExpValidator(rx,mle9));
//        tableView->setCellWidget(i-1,9,mle9);
//        tableView->childAt(i-1,9)->setV
//       // model->setData()


        //model->setData(model->index(i-1,10),QVariant(tr("前序混匀次数:")));
        QStandardItem* item10=new QStandardItem;
        item10->setText(tr("前序混匀次数:"));
        item10->setFlags(item10->flags() & (~Qt::ItemIsEditable));
        model->setItem(i-1,9,item10);

        model->setData(model->index(i-1,10),QVariant(tr("0")));


       //model->setData(model->index(i-1,12),QVariant(tr("后序混匀次数:")));
        QStandardItem* item12=new QStandardItem;
        item12->setText(tr("后序混匀次数:"));
        item12->setFlags(item12->flags() & (~Qt::ItemIsEditable));
        model->setItem(i-1,11,item12);

        model->setData(model->index(i-1,12),QVariant(tr("0")));


        //model->setData(model->index(i-1,14),QVariant(tr("试剂量(ul):")));
        QStandardItem* item14=new QStandardItem;
        item14->setText(tr("试剂量(ul):"));
        item14->setFlags(item14->flags() & (~Qt::ItemIsEditable));
        model->setItem(i-1,13,item14);


        model->setData(model->index(i-1,14),QVariant(tr("0")));


        //model->setData(model->index(i-1,16),QVariant(tr("所需时间(m):")));
        QStandardItem* item16=new QStandardItem;
        item16->setText(tr("所需时间(s):"));
        item16->setFlags(item16->flags() & (~Qt::ItemIsEditable));
        model->setItem(i-1,15,item16);


        model->setData(model->index(i-1,16),QVariant(tr("0")));
    }
    model->setData(model->index(0,2),QVariant(tr("取反应管")));
    model->setData(model->index(1,2),QVariant(tr("取Tap头1")));
    model->setData(model->index(2,2),QVariant(tr("加样本")));
    model->setData(model->index(3,2),QVariant(tr("加试剂1")));
    model->setData(model->index(4,2),QVariant(tr("加试剂2")));
    model->setData(model->index(5,2),QVariant(tr("温育")));
    model->setData(model->index(6,2),QVariant(tr("加磁珠")));
    model->setData(model->index(7,2),QVariant(tr("温育")));
    model->setData(model->index(8,2),QVariant(tr("加试剂3")));
    model->setData(model->index(9,2),QVariant(tr("温育")));
    model->setData(model->index(10,2),QVariant(tr("取Tap头2")));
    model->setData(model->index(11,2),QVariant(tr("第一次洗涤")));
    model->setData(model->index(12,2),QVariant(tr("第二次洗涤")));
    model->setData(model->index(13,2),QVariant(tr("第三次洗涤")));
    model->setData(model->index(14,2),QVariant(tr("移动反应管进发光孔")));
    model->setData(model->index(15,2),QVariant(tr("取Tap头3")));
    model->setData(model->index(16,2),QVariant(tr("加预激发液")));
    model->setData(model->index(17,2),QVariant(tr("取Tap头4")));
    model->setData(model->index(18,2),QVariant(tr("加激发液发光")));

}


/**
 * @brief reagentProWidget::设置代理
 */
void standardPrograme_actionPro::setActionTabel_delegate()
{
//    addDelegate = new standardPrograme_addBtnDelegate; //添加按钮代理
//    tableView->setItemDelegateForColumn(0,addDelegate);
//    minusDelegate = new standardprograme_minusDelegate;
//    tableView->setItemDelegateForColumn(1,minusDelegate);
//    actionCheckDelegate = new standardprograme_actionCheckDelegate;
//    tableView->setItemDelegateForColumn(3,actionCheckDelegate);
    checkBoxDelegate = new standardpragrame_checkBoxDelegate;
    tableView->setItemDelegateForColumn(0,checkBoxDelegate);

    startPostionDelegate =  new standardPrograme_startPostionDelegate;
    tableView->setItemDelegateForColumn(4,startPostionDelegate);
    endPostionDelegate = new  standardPrograme_endPostionDelegate; //目标位置
    tableView->setItemDelegateForColumn(6,endPostionDelegate);
    afterCountDelegate = new standardPrograme_afterCountDelegate;  //后续混匀次数
    beforeCountDelegate = new standardPrograme_beforeCountDelegate; //前序混匀次数
    tableView->setItemDelegateForColumn(10,beforeCountDelegate);
    tableView->setItemDelegateForColumn(12,afterCountDelegate);
    stepRunBtnDelegate = new standardpragrame_runBtnDelegate;
    tableView->setItemDelegateForColumn(17,stepRunBtnDelegate);


}

/**
 * @brief standardPrograme_actionPro::信号槽连接初始化
 */
void standardPrograme_actionPro::connectInit()
{
//    connect(addDelegate,SIGNAL(AddBtnClicked(QModelIndex)),this,SLOT(addActionStep(QModelIndex)));
//    connect(minusDelegate,SIGNAL(MinusBtnClicked(QModelIndex)),this,SLOT(minusActionStep(QModelIndex)));
    connect(stepRunBtnDelegate,SIGNAL(stepRnBtnClicked(QModelIndex)),this,SLOT(stepRunBtnSlot(QModelIndex)));
}

/**
 * @brief 获取单步运行命令数据
 * @param 第几行按钮
 * @return 命令字符串
 */
QString standardPrograme_actionPro::getStepData(int current_row)
{
    int row = current_row;
    QString cmd = "";
    unsigned short int time = 0;     //时间
    unsigned short int reagent_count = 0;  //试剂量
    QString tempStrl;  //临时字符串
    cmd = "02,20,ff,ff,00,00,01,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00";
    QString startPstring = model->index(current_row-1,4).data(Qt::DisplayRole).toString();  //开始位置
    if(startPstring == "温育孔#1"){
        cmd += ",01";
    }else if( startPstring == "温育孔#2" ){
        cmd += ",02";
    }else{
        startPstring.remove(0,1);
        if(startPstring.toInt() > 9){//防止有位置大于两位数
            cmd.replace(42,2,startPstring);
        }else{
            cmd.replace(43,1,startPstring);
        }
        cmd += ",00";

    }

    QString endPstring = model->index(current_row-1,6).data(Qt::DisplayRole).toString();  //结束位置
    if(endPstring == "温育孔#1"){
        cmd += ",01";
    }else if( endPstring == "温育孔#2" ){
        cmd += ",02";
    }else{
        endPstring.remove( 0,1 );
        if( endPstring.toInt() > 9){  //防止有位置大于两位数
             cmd.replace( 66,2,endPstring );
        }else { cmd.replace( 67,1,endPstring );
        }
        cmd += ",00";

    }
    time = model->index(current_row-1,8).data(Qt::DisplayRole).toInt(); //温育时间
    cmd = cmd + ","+ tempStrl.setNum( (unsigned char)((time >> 8)&0xff),16);
    cmd = cmd + ","+ tempStrl.setNum( (unsigned char)(time&0xff),16);
    cmd = cmd + "," + model->index(current_row-1,10).data(Qt::DisplayRole).toString();//前序次数
    cmd = cmd + "," + model->index(current_row-1,12).data(Qt::DisplayRole).toString();//后序次数
    reagent_count = model->index(current_row-1,14).data(Qt::DisplayRole).toInt();//试剂量
    cmd = cmd + ","+ tempStrl.setNum( (unsigned char)((reagent_count >> 8)&0xff),16);
    cmd = cmd + ","+ tempStrl.setNum( (unsigned char)(reagent_count&0xff),16);
    switch( row ){
    case 1:
        cmd.replace(18,2,"01");
        break;
    case 2:
        cmd.replace(18,2,"02");
        break;
    case 3:
        cmd.replace(18,2,"03");
        break;
    case 4:
        cmd.replace(18,2,"04");
        break;
    case 5:
        cmd.replace(18,2,"05");
        break;
    case 6:
        cmd.replace(18,2,"06");
        break;
    case 7:
        cmd.replace(18,2,"07");
        break;
    case 8:
        cmd.replace(18,2,"08");
        break;
    case 9:
        cmd.replace(18,2,"09");
        break;
    case 10:
        cmd.replace(18,2,"0A");
        break;
    case 11:
        cmd.replace(18,2,"0B");
        break;
    case 12:
        cmd.replace(18,2,"0C");
        break;
    case 13:
        cmd.replace(18,2,"0D");
        break;
    case 14:
        cmd.replace(18,2,"0E");
        break;
    case 15:
        cmd.replace(18,2,"0F");
        break;
    case 16:
        cmd.replace(18,2,"10");
        break;
    case 17:
        cmd.replace(18,2,"11");
        break;
    case 18:
        cmd.replace(18,2,"12");
        break;
    case 19:
        cmd.replace(18,2,"13");
        break;
    }
   qDebug() << "当前步骤数据"<< cmd;
   return cmd;
}



/**
 * @brief standardPrograme_actionPro::增加一个步骤信号槽
 */
void standardPrograme_actionPro::addActionStep(const QModelIndex&index)
{
    if(model->rowCount() > STEP_NUM-1 ){
        return;
    }
    model->insertRow(index.row());
    int row = index.row();
//    model->setData(model->index(row,3),QVariant(tr("取反应管")));
//    model->setData(model->index(row,4),QVariant(tr("起始位置：")));
//    model->setData(model->index(row,5),QVariant(tr("0")));
//    model->setData(model->index(row,6),QVariant(tr("放入位置：")));
//    model->setData(model->index(row,7),QVariant(tr("0")));
//    model->setData(model->index(row,8),QVariant(tr("温育时间(m)：")));
//    model->setData(model->index(row,9),QVariant(tr("0")));
//    model->setData(model->index(row,10),QVariant(tr("前序混匀次数：")));
//    model->setData(model->index(row,11),QVariant(tr("0")));
//    model->setData(model->index(row,12),QVariant(tr("后序混匀次数：")));
//    model->setData(model->index(row,13),QVariant(tr("0")));
//    model->setData(model->index(row,14),QVariant(tr("试剂量(ul)：")));
//    model->setData(model->index(row,15),QVariant(tr("0")));
//    model->setData(model->index(row,16),QVariant(tr("所需时间：")));
//    model->setData(model->index(row,17),QVariant(tr("0")));

//    for(int i = 0;i < model->rowCount();i++){
//        QString string = QString(tr("步骤:"));
//        QString numStep = QString::number(i+1);
//        string.append(numStep);
//        model->setData(model->index(i,2),QVariant(string));
//    }


//重新刷 步骤顺序
    for(int i = 0;i < model->rowCount();i++){

        QStandardItem* item2=new QStandardItem;
        item2->setText(QString("步骤:%1").arg(i+1));
        item2->setFlags(item2->flags() & (~Qt::ItemIsEditable));
        model->setItem(i,2,item2);
    }
//新增行的标签和数据
    QStandardItem* item3=new QStandardItem;
    item3->setText(tr("取反应管"));
    item3->setFlags(item3->flags() & (~Qt::ItemIsEditable));
    model->setItem(row,3,item3);


    QStandardItem* item4=new QStandardItem;
    item4->setText(tr("起始位置:"));
    item4->setFlags(item4->flags() & (~Qt::ItemIsEditable));
    model->setItem(row,4,item4);

    model->setData(model->index(row,5),QVariant(tr("0")));



    QStandardItem* item6=new QStandardItem;
    item6->setText(tr("放入位置:"));
    item6->setFlags(item6->flags() & (~Qt::ItemIsEditable));
    model->setItem(row,6,item6);

    model->setData(model->index(row,7),QVariant(tr("0")));


    QStandardItem* item8=new QStandardItem;
    item8->setText(tr("温育时间(m)"));
    item8->setFlags(item8->flags() & (~Qt::ItemIsEditable));
    model->setItem(row,8,item8);

    model->setData(model->index(row,9),QVariant(tr("0")));



    QStandardItem* item10=new QStandardItem;
    item10->setText(tr("前序混匀次数:"));
    item10->setFlags(item10->flags() & (~Qt::ItemIsEditable));
    model->setItem(row,10,item10);

    model->setData(model->index(row,11),QVariant(tr("0")));



    QStandardItem* item12=new QStandardItem;
    item12->setText(tr("后序混匀次数:"));
    item12->setFlags(item12->flags() & (~Qt::ItemIsEditable));
    model->setItem(row,12,item12);

    model->setData(model->index(row,13),QVariant(tr("0")));



    QStandardItem* item14=new QStandardItem;
    item14->setText(tr("试剂量(ul):"));
    item14->setFlags(item14->flags() & (~Qt::ItemIsEditable));
    model->setItem(row,14,item14);


    model->setData(model->index(row,15),QVariant(tr("0")));



    QStandardItem* item16=new QStandardItem;
    item16->setText(tr("所需时间:"));
    item16->setFlags(item16->flags() & (~Qt::ItemIsEditable));
    model->setItem(row,16,item16);


    model->setData(model->index(row,17),QVariant(tr("0")));

}

/**
 * @brief standardPrograme_actionPro::删除一个步骤信号槽
 * @param index
 */
void standardPrograme_actionPro::minusActionStep(const QModelIndex&index)
{
    if(model->rowCount() <= 1){
        return;
    }
    model->removeRow(index.row());

    for(int i = 0;i < model->rowCount();i++){
        QString string = QString(tr("步骤："));
        QString numStep = QString::number(i+1);
        string.append(numStep);
        model->setData(model->index(i,2),QVariant(string));
    }
}

/**
 * @brief standardPrograme_actionPro::单步运行按钮信号槽
 * @param index
 */
void standardPrograme_actionPro::stepRunBtnSlot(const QModelIndex &index)
{
    int step = index.row()+1;//index是按照从0开始的
    emit stepRunBtnSignal(step);
}

