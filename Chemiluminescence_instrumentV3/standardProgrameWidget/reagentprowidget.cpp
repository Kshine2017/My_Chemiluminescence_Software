#include "reagentprowidget.h"
#include <QDebug>
#include <QSqlQuery>
#include "dataopration.h"
#include "exportimportexcel.h"
#include <QMessageBox>
/**
 * @brief 试剂船项目名称表格属性
 */
//#define TABLE_NAME_WIDTH 110
//#define TABLE_EDIT_WIDTH 220
//#define TABLE_HIGH 30

/**
 * @brief 试剂船工作表格属性
 */
#define TABLEWORK_NAME_WIDTH 220
#define TABLEWORK_PRPS_WIDTH 900
#define TABLEWORK_TIME_WIDTH 220
#define TABLEWORK_HIGH 30

reagentProWidget::reagentProWidget(QWidget *parent) : QWidget(parent)
{
    //tableProjectWidgetInit();
    //tableWorkWidgetInit();
    workToolBarInit();
    /**
  *显示标题定义
  */
    //tableProjectWidget->setGeometry(8,62,1652,32);
    //tableWorkWidget->setGeometry(8,94,1652,62);
    workToolWidget->setGeometry(8,55,1652,60);//150


    titleLab = new QLabel(this);
    QPalette   pal;//按键字体颜色设置
    pal.setColor(QPalette::WindowText, QColor(255, 255, 255, 255));
    titleLab->setPalette(pal);
    titleLab->setFont(QFont("windowTitle",15));
    titleLab->setText(tr("详细步骤"));
    titleLab->setGeometry(85,4,100,50);
    /*
  进度条（已经换到上方）
*/
    //    WorkProgBar = new QProgressBar;
    //    WorkProgBar->setStyleSheet("QProgressBar{border: 1px solid grey;border-radius: 5px;text-align: center;}"
    //                         "QProgressBar::chunk{background-color: #CD96CD;width: 10px;margin: 0.5px;}");
    //    WorkProgBar->setFixedSize(900,30);
    //    WorkProgBar->setValue(40); //临时测试用
    //    tableWorkWidget->setCellWidget(1,1,WorkProgBar);
    /**
  * 试剂船动作编辑视图
  */
    actionProTabelView = new standardPrograme_actionPro(this);
    actionProTabelView->setGeometry(8,108,ACTION_TABLE_WIDTH,ACTION_TABLE_HIGHT);//200

    //工作队列和询问定时器
    WorkQueue = new Queue;  //工作队列
    InquiryTimer = new QTimer(this); //工作队列询问定时器
    InquiryTimer->setInterval( REAGRNT_PRAGRAME_INQUIRY_TIME );
    InquiryTimer->setSingleShot(false);
    InquiryTimer->start();

    //试剂船全速运行设备状态
    standardPrograme_mode = PRO_STOP;
    /**
     * @brief 信号槽连接
     */
    connectInit();

}

/**
 * @brief 试剂船项目名称表格
 */
/*
void reagentProWidget::tableProjectWidgetInit()
{
    tableProjectWidget = new QTableWidget(this);
    tableProjectWidget->setColumnCount(10);
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
    tableProjectWidget->setRowHeight(0,TABLE_HIGH);
    tableProjectWidget->setFixedSize(1652,32);

    QTableWidgetItem *itemName0 = new QTableWidgetItem;
    itemName0->setFlags(Qt::NoItemFlags);
    itemName0->setTextAlignment(Qt::AlignCenter);
    itemName0->setText(tr("文件名称："));
    tableProjectWidget->setItem(0,0,itemName0);

    QTableWidgetItem *itemName1 = new QTableWidgetItem;
    itemName1->setTextAlignment(Qt::AlignCenter);
    itemName1->setFlags(itemName1->flags() & (~Qt::ItemIsEditable));
    tableProjectWidget->setItem(0,1,itemName1);

    QTableWidgetItem *itemName2 = new QTableWidgetItem;
    itemName2->setFlags(Qt::NoItemFlags);
    itemName2->setTextAlignment(Qt::AlignCenter);
    itemName2->setText(tr("文件名简写："));
    tableProjectWidget->setItem(0,2,itemName2);

    QTableWidgetItem *itemName3 = new QTableWidgetItem;
    itemName3->setTextAlignment(Qt::AlignCenter);
    itemName3->setFlags(itemName3->flags() & (~Qt::ItemIsEditable));
    tableProjectWidget->setItem(0,3,itemName3);

    QTableWidgetItem *itemName4 = new QTableWidgetItem;
    itemName4->setFlags(Qt::NoItemFlags);
    itemName4->setTextAlignment(Qt::AlignCenter);
    itemName4->setText(tr("条码图像："));
    tableProjectWidget->setItem(0,4,itemName4);

    QTableWidgetItem *itemName5 = new QTableWidgetItem;
    itemName5->setTextAlignment(Qt::AlignCenter);
    itemName5->setFlags(itemName5->flags() & (~Qt::ItemIsEditable));
    tableProjectWidget->setItem(0,5,itemName5);


    QTableWidgetItem *itemName6 = new QTableWidgetItem;
    itemName6->setFlags(Qt::NoItemFlags);
    itemName6->setTextAlignment(Qt::AlignCenter);
    itemName6->setText(tr("开始使用时间："));
    tableProjectWidget->setItem(0,6,itemName6);

    QTableWidgetItem *itemName7 = new QTableWidgetItem;
    itemName7->setTextAlignment(Qt::AlignCenter);
    itemName7->setFlags(itemName7->flags() & (~Qt::ItemIsEditable));
    tableProjectWidget->setItem(0,7,itemName7);

    QTableWidgetItem *itemName8 = new QTableWidgetItem;
    itemName8->setFlags(Qt::NoItemFlags);
    itemName8->setTextAlignment(Qt::AlignCenter);
    itemName8->setText(tr("结束使用时间："));
    tableProjectWidget->setItem(0,8,itemName8);

    QTableWidgetItem *itemName9 = new QTableWidgetItem;
    itemName9->setTextAlignment(Qt::AlignCenter);
    itemName9->setFlags(itemName9->flags() & (~Qt::ItemIsEditable));
    tableProjectWidget->setItem(0,9,itemName9);

}
*/
/**
 * @brief 试剂船工作进度表格初始化
 */
void reagentProWidget::tableWorkWidgetInit()
{
    tableWorkWidget = new QTableWidget(this);
    tableWorkWidget->setColumnCount(4);
    tableWorkWidget->setRowCount(2);
    tableWorkWidget->horizontalHeader()->hide();
    tableWorkWidget->verticalHeader()->hide();
    tableWorkWidget->setStyleSheet("gridline-color: rgb(0, 139, 139);selection-background-color:lightblue;");
    tableWorkWidget->setColumnWidth(0,TABLEWORK_NAME_WIDTH+90);
    tableWorkWidget->setColumnWidth(1,TABLEWORK_PRPS_WIDTH);
    tableWorkWidget->setColumnWidth(2,TABLEWORK_TIME_WIDTH);
    tableWorkWidget->setColumnWidth(3,TABLEWORK_TIME_WIDTH);
    tableWorkWidget->setRowHeight(0,TABLEWORK_HIGH);
    tableWorkWidget->setRowHeight(1,TABLEWORK_HIGH);
    tableWorkWidget->setRowHeight(2,TABLEWORK_HIGH);

    QTableWidgetItem *itemWorkLabel1 = new QTableWidgetItem;
    itemWorkLabel1->setFlags(Qt::NoItemFlags);
    itemWorkLabel1->setTextAlignment(Qt::AlignCenter);
    itemWorkLabel1->setText(tr("当前工作阶段："));
    tableWorkWidget->setItem(0,0,itemWorkLabel1);

    QTableWidgetItem *itemWorkLabel2 = new QTableWidgetItem;
    itemWorkLabel2->setFlags(Qt::NoItemFlags);
    itemWorkLabel2->setTextAlignment(Qt::AlignCenter);
    itemWorkLabel2->setText(tr("工作进度条："));
    tableWorkWidget->setItem(0,1,itemWorkLabel2);

    QTableWidgetItem *itemWorkLabel3 = new QTableWidgetItem;
    itemWorkLabel3->setFlags(Qt::NoItemFlags);
    itemWorkLabel3->setTextAlignment(Qt::AlignCenter);
    itemWorkLabel3->setText(tr("开始时间："));
    tableWorkWidget->setItem(0,2,itemWorkLabel3);

    QTableWidgetItem *itemWorkLabel4 = new QTableWidgetItem;
    itemWorkLabel4->setFlags(Qt::NoItemFlags);
    itemWorkLabel4->setTextAlignment(Qt::AlignCenter);
    itemWorkLabel4->setText(tr("结束时间："));
    tableWorkWidget->setItem(0,3,itemWorkLabel4);


    QTableWidgetItem *itemWorkLabel5 = new QTableWidgetItem;
    itemWorkLabel5->setTextAlignment(Qt::AlignCenter);
    itemWorkLabel5->setFlags(itemWorkLabel5->flags() & (~Qt::ItemIsEditable));
    tableWorkWidget->setItem(1,0,itemWorkLabel5);

    QTableWidgetItem *itemWorkLabel6 = new QTableWidgetItem;
    itemWorkLabel6->setTextAlignment(Qt::AlignCenter);
    itemWorkLabel6->setFlags(itemWorkLabel6->flags() & (~Qt::ItemIsEditable));
    tableWorkWidget->setItem(1,1,itemWorkLabel6);

    QTableWidgetItem *itemWorkLabel7 = new QTableWidgetItem;
    itemWorkLabel7->setTextAlignment(Qt::AlignCenter);
    itemWorkLabel7->setFlags(itemWorkLabel7->flags() & (~Qt::ItemIsEditable));
    tableWorkWidget->setItem(1,2,itemWorkLabel7);

    QTableWidgetItem *itemWorkLabel8 = new QTableWidgetItem;
    itemWorkLabel8->setTextAlignment(Qt::AlignCenter);
    itemWorkLabel8->setFlags(itemWorkLabel8->flags() & (~Qt::ItemIsEditable));
    tableWorkWidget->setItem(1,3,itemWorkLabel8);

}
/**
 * @brief 工具栏初始化
 */
void reagentProWidget::workToolBarInit()
{
    workToolWidget = new QWidget(this);
    //    workToolWidget->setAutoFillBackground(true);
    //    QPalette pal;
    //    QPixmap pixmap();
    //    pal.setBrush(QPalette::Window,QBrush(pixmap));
    //    workToolWidget->setPalette(pal);

    toolLayout = new QHBoxLayout;



    //    startBtn = new QPushButton;/**< 开始 */
    //    startBtn->setText(tr("连续运行"));
    //    startBtn->setIconSize(QSize(32,32));
    //    startBtn->setIcon(QIcon(":/picture/standardPrograme/start—up.png"));
    //    startBtn->setFlat(true);

    startBtn = new QPushButton;
    startBtn->setFlat(true);
    startBtn->setFocusPolicy(Qt::TabFocus);
    startBtn->setFixedSize(117,31);//图片的固定大小
    startBtn->setStyleSheet("QPushButton{border-image: url(:/picture/standardPrograme/new20180123/start-up.png);}"
                            "QPushButton:hover{border-image: url(:/picture/standardPrograme/new20180123/start-up.png);}"
                            "QPushButton:pressed{border-image: url(:/picture/standardPrograme/new20180123/start-down.png);}");


    //    pauseContinuBtn = new QPushButton;/**< 暂停/继续 */
    //    pauseContinuBtn->setIconSize(QSize(32,32));
    //    pauseContinuBtn->setText(tr("暂停"));
    //    pauseContinuBtn->setIcon(QIcon(":/picture/standardPrograme/continue—up.png"));
    //    pauseContinuBtn->setFlat(true);

    pauseContinuBtn = new QPushButton;
    pauseContinuBtn->setFlat(true);
    pauseContinuBtn->setFocusPolicy(Qt::TabFocus);
    pauseContinuBtn->setFixedSize(78,31);//图片的固定大小
    pauseContinuBtn->setStyleSheet("QPushButton{border-image: url(:/picture/standardPrograme/new20180123/pause-up.png);}"
                                   "QPushButton:hover{border-image: url(:/picture/standardPrograme/new20180123/pause-up.png);}"
                                   "QPushButton:pressed{border-image: url(:/picture/standardPrograme/new20180123/pause-down.png);}");

    //    stopBtn = new QPushButton;/**< 停止 */
    //    stopBtn->setIconSize(QSize(32,32));
    //    stopBtn->setText(tr("停止"));
    //    stopBtn->setIcon(QIcon(":/picture/standardPrograme/stop—up.png"));
    //    stopBtn->setFlat(true);

    stopBtn = new QPushButton;
    stopBtn->setFlat(true);
    stopBtn->setFocusPolicy(Qt::TabFocus);
    stopBtn->setFixedSize(78,31);//图片的固定大小
    stopBtn->setStyleSheet("QPushButton{border-image: url(:/picture/standardPrograme/new20180123/stop-up.png);}"
                           "QPushButton:hover{border-image: url(:/picture/standardPrograme/new20180123/stop-up.png);}"
                           "QPushButton:pressed{border-image: url(:/picture/standardPrograme/new20180123/stop-down.png);}");


    //    saveBtn = new QPushButton;/**< 保存 */
    //    saveBtn->setIconSize(QSize(32,32));
    //    saveBtn->setText(tr("保存"));
    //    saveBtn->setIcon(QIcon(":/picture/standardPrograme/save.png"));
    //    saveBtn->setFlat(true);
    saveBtn = new QPushButton;
    saveBtn->setFlat(true);
    saveBtn->setFocusPolicy(Qt::TabFocus);
    saveBtn->setFixedSize(78,31);//图片的固定大小
    saveBtn->setStyleSheet("QPushButton{border-image: url(:/picture/standardPrograme/new20180123/save-up.png);}"
                           "QPushButton:hover{border-image: url(:/picture/standardPrograme/new20180123/save-up.png);}"
                           "QPushButton:pressed{border-image: url(:/picture/standardPrograme/new20180123/save-down.png);}");

    //    openBtn = new QPushButton;/**< 打开 */
    //    openBtn->setIconSize(QSize(32,32));
    //    openBtn->setText(tr("打开"));
    //    openBtn->setIcon(QIcon(":/picture/standardPrograme/open.png"));
    //    openBtn->setFlat(true);
    openBtn = new QPushButton;
    openBtn->setFlat(true);
    openBtn->setFocusPolicy(Qt::TabFocus);
    openBtn->setFixedSize(78,32);//图片的固定大小
    openBtn->setStyleSheet("QPushButton{border-image: url(:/picture/standardPrograme/new20180123/open-up.png);}"
                           "QPushButton:hover{border-image: url(:/picture/standardPrograme/new20180123/open-up.png);}"
                           "QPushButton:pressed{border-image: url(:/picture/standardPrograme/new20180123/open-down.png);}");


    //    exportBtn = new QPushButton;/**< 导出 */
    //    exportBtn->setIconSize(QSize(32,32));
    //    exportBtn->setText(tr("导出"));
    //    exportBtn->setIcon(QIcon(":/picture/standardPrograme/export.png"));
    //    exportBtn->setFlat(true);
    exportBtn = new QPushButton;
    exportBtn->setFlat(true);
    exportBtn->setFocusPolicy(Qt::TabFocus);
    exportBtn->setFixedSize(78,31);//图片的固定大小
    exportBtn->setStyleSheet("QPushButton{border-image: url(:/picture/standardPrograme/new20180123/export-up.png);}"
                             "QPushButton:hover{border-image: url(:/picture/standardPrograme/new20180123/export-up.png);}"
                             "QPushButton:pressed{border-image: url(:/picture/standardPrograme/new20180123/export-down.png);}");

    //    importBtn = new QPushButton;/**< 导入 */
    //    importBtn->setIconSize(QSize(32,32));
    //    importBtn->setText(tr("导入"));
    //    importBtn->setIcon(QIcon(":/picture/standardPrograme/import.png"));
    //    importBtn->setFlat(true);
    importBtn = new QPushButton;
    importBtn->setFlat(true);
    importBtn->setFocusPolicy(Qt::TabFocus);
    importBtn->setFixedSize(78,32);//图片的固定大小
    importBtn->setStyleSheet("QPushButton{border-image: url(:/picture/standardPrograme/new20180123/import-up.png);}"
                             "QPushButton:hover{border-image: url(:/picture/standardPrograme/new20180123/import-up.png);}"
                             "QPushButton:pressed{border-image: url(:/picture/standardPrograme/new20180123/import-down.png);}");


    toolLayout->addSpacing(50);
    toolLayout->addWidget(startBtn);
    toolLayout->addSpacing(50);
    toolLayout->addWidget(pauseContinuBtn);
    toolLayout->addSpacing(50);
    toolLayout->addWidget(stopBtn);
    toolLayout->addSpacing(50);
    toolLayout->addWidget(saveBtn);
    toolLayout->addSpacing(50);
    toolLayout->addWidget(openBtn);
    toolLayout->addSpacing(50);
    toolLayout->addWidget(importBtn);
    toolLayout->addSpacing(50);
    toolLayout->addWidget(exportBtn);
    toolLayout->addSpacing(900);
    workToolWidget->setLayout(toolLayout);

}

/**
 * @brief 试剂船信息是否有为空
 * @return 空true ,非空false
 */
/*
bool reagentProWidget::ProjectInfoIsEmpty()
{
    if(tableProjectWidget->item(0,1)->text().isEmpty() || tableProjectWidget->item(0,3)->text().isEmpty()
            || tableProjectWidget->item(0,5)->text().isEmpty() || tableProjectWidget->item(0,7)->text().isEmpty()
            || tableProjectWidget->item(0,9)->text().isEmpty()){
        qDebug() << "项目信息不完整";
     return true;
    }
    return false;//K添加
}
*/

/**
 * @brief reagentProWidget::信号槽绑定初始化
 */
void reagentProWidget::connectInit()
{
    connect(startBtn,SIGNAL(clicked()),this,SLOT(startBtnSlot()));
    connect(pauseContinuBtn,SIGNAL(clicked()),this,SLOT(pauseContinuBtnSlot()));
    connect(stopBtn,SIGNAL(clicked()),this,SLOT(stopBtnSlot()));
    connect(saveBtn,SIGNAL(clicked()),this,SLOT(saveBtnSlot()));
    connect(openBtn,SIGNAL(clicked()),this,SLOT(openBtnSlot()));
    connect(importBtn,SIGNAL(clicked()),this,SLOT(importBtnSlot()));
    connect(exportBtn,SIGNAL(clicked()),this,SLOT(exportBtnSlot()));

    connect(InquiryTimer,SIGNAL(timeout()),this,SLOT(reagentpro_InquiryTimerOverSlot()));
}

/**
 * @brief 打开按钮信号槽
 */
void reagentProWidget::openBtnSlot()
{
    emit OpenBtnSignal();
}

/**
 * @brief 保存按钮信号槽
 */
void reagentProWidget::saveBtnSlot()
{
    saveBtn->setFocus();
    emit SaveBtnPress_Sign();
       return;

}

/**
 * @brief 开始按钮信号槽
 */
void reagentProWidget::startBtnSlot()
{
    emit startBtnSignal();
    serialPort::mySend_Data("02,05,ff,ff,00,00"); //询问是否空闲
    standardPrograme_mode = PRO_FULL_START;
}

/**
 * @brief 暂停按钮信号槽
 */
void reagentProWidget::pauseContinuBtnSlot()
{
    if( standardPrograme_mode == PRO_FULL_START || standardPrograme_mode == PRO_STEP_RUN ){ //只有当试剂船全速运行暂停按钮才有效
        if( pauseContinuBtnState ){
            pauseContinuBtn->setStyleSheet("QPushButton{border-image: url(:/picture/standardPrograme/new20180123/continue-up.png);}"
                                           "QPushButton:hover{border-image: url(:/picture/standardPrograme/new20180123/continue-up.png);}"
                                           "QPushButton:pressed{border-image: url(:/picture/standardPrograme/new20180123/continue-down.png);}");
            //        pauseContinuBtn->setText(tr("暂停"));
            serialPort::mySend_Data("02,27,ff,ff,00,00");
            qDebug() << "发送试剂船单步暂停测试命令一次";
            pauseContinuBtnState = false;
        }else {
            pauseContinuBtn->setStyleSheet("QPushButton{border-image: url(:/picture/standardPrograme/new20180123/pause-up.png);}"
                                           "QPushButton:hover{border-image: url(:/picture/standardPrograme/new20180123/pause-up.png);}"
                                           "QPushButton:pressed{border-image: url(:/picture/standardPrograme/new20180123/pause-down.png);}");
            //        pauseContinuBtn->setText(tr("继续"));
            serialPort::mySend_Data("02,28,ff,ff,00,00");
            qDebug() << "发送试剂船单步继续测试命令一次";
            pauseContinuBtnState = true;
        }
    }else {
        QMessageBox::critical(this,tr("提示！"),tr("当前没有正在运行的项目！"));
        return;
    }
}


/**
 * @brief 停止按钮信号槽
 */
void reagentProWidget::stopBtnSlot()
{
    serialPort::mySend_Data("02,29,ff,ff,00,00");
    standardPrograme_mode = PRO_STOP;
    if( pauseContinuBtnState ){  //当停止时暂停按钮变成暂停状态
        pauseContinuBtn->setStyleSheet("QPushButton{border-image: url(:/picture/standardPrograme/new20180123/continue-up.png);}"
                                       "QPushButton:hover{border-image: url(:/picture/standardPrograme/new20180123/continue-up.png);}"
                                       "QPushButton:pressed{border-image: url(:/picture/standardPrograme/new20180123/continue-down.png);}");
        //        pauseContinuBtn->setText(tr("暂停"));
        serialPort::mySend_Data("02,27,ff,ff,00,00");
        qDebug() << "发送试剂船单步暂停测试命令一次";
        pauseContinuBtnState = false;
    }
    qDebug() << "发送试剂船单步停止测试命令一次";
}

/**
 * @brief 导入按钮信号槽
 */
void reagentProWidget::importBtnSlot()
{
    ExportImportExcel eie;
    eie.ImportDialog();
}

/**
 * @brief 导出按钮信号槽
 */
void reagentProWidget::exportBtnSlot()
{
    ExportImportExcel eie;
    eie.ExportDialog();

}


/**
 * @brief reagentProWidget::询问下位机是否空时间定时器超时槽
 */
void reagentProWidget::reagentpro_InquiryTimerOverSlot()
{
    if( !WorkQueue->isEmpty()){
        serialPort::mySend_Data("02,05,ff,ff,00,00");
    }
}



