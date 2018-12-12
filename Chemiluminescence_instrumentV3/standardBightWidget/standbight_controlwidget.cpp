#include "standbight_controlwidget.h"
#include <QStandardItem>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QStandardItem>
#include "data/util.h"
#include <QSqlQueryModel>
#include "data/configfile.h"

#include"../standardTestWidget/dataopationstandardtest.h"

#define CHECK_MIN 5 //生成标准曲线最小需要的点数
standBight_controlWidget::standBight_controlWidget(QWidget *parent):QWidget(parent)
{
    setFixedSize(400,915);
    setWindowFlags(Qt::FramelessWindowHint);
    setAutoFillBackground(true);
    QPalette pa;
    QPixmap fuctionPixMap(":/picture/standardBight/backGround.png");
    pa.setBrush(QPalette::Window,QBrush(fuctionPixMap));
    setPalette(pa);

    controlWindowInit();
    tableViewInit();
    PointCheckWidgetInit();
    fuctionViewInit();

    init_comboxData();

    btnLayout = new QHBoxLayout;    //按钮布局器
    checkLayout = new QHBoxLayout;  //选择布局管理器
    mainLayout = new QVBoxLayout(this);  //主布局管理器

    checkLayout1 = new QHBoxLayout;
    checkLayout2 = new QHBoxLayout;
    checkLayout3 = new QHBoxLayout;
    checkLayout4 = new QHBoxLayout;

    checkLayout1->addStretch(2);
    checkLayout1->addWidget(label_projectName);
    checkLayout1->addStretch(1);
    checkLayout1->addWidget(combox_projectName);
    checkLayout1->addStretch(2);
    checkLayout1->addWidget(label_reagentType);
    checkLayout1->addStretch(1);
    checkLayout1->addWidget(combox_reagentType);
    checkLayout1->addStretch(4);

    checkLayout2->addStretch(2);
    checkLayout2->addWidget(label_productionDate);
    checkLayout2->addStretch(1);
    checkLayout2->addWidget(dateEdit_productionDate);
    checkLayout2->addStretch(2);
    checkLayout2->addWidget(label_lotNumber);
    checkLayout2->addStretch(1);
    checkLayout2->addWidget(combox_lotNumber);
    checkLayout2->addStretch(4);

    mainLayout->setMargin(0);
    btnLayout->addSpacing(2);
    btnLayout->addWidget(produceBightBtn);
    btnLayout->addSpacing(3);
    btnLayout->addWidget(resetBightBtn);
    btnLayout->addSpacing(2);

    ParameterWidgetLayout = new QHBoxLayout; //标准点参数布局器
    ParameterWidgetLayout->setSpacing(10);
    ParameterWidgetLayout->setMargin(10);
    ParameterWidgetLayout->addSpacing(10);
    ParameterWidgetLayout->addWidget(pointCheckWidget);
    ParameterWidgetLayout->addWidget(parameterWidget);
    ParameterWidgetLayout->addSpacing(30);

//    checkLayout->addSpacing(0);
//    checkLayout->addWidget(checkTitleLabel);
//    checkLayout->addWidget(combox);
//    checkLayout->addSpacing(20);
    mainLayout->addSpacing(10);
    mainLayout->addLayout(checkLayout1);
    mainLayout->addLayout(checkLayout2);
//    mainLayout->addLayout(checkLayout3);
//    mainLayout->addLayout(checkLayout4);
    mainLayout->addSpacing(10);
    mainLayout->addLayout(btnLayout);
    mainLayout->addLayout(ParameterWidgetLayout);
    mainLayout->addWidget(fuctionLabel);
    mainLayout->addWidget(fuctionWidget);


//    setStyleSheet("QWidget{background-color:gray;border-top-left-radius:15px;border-top-right-radius:15px;}");
    connectInit();
}
/**
 * @brief standBight_controlWidget::控制界面初始化
 */
void standBight_controlWidget::controlWindowInit()
{
    QFont *font = new QFont("labelFont",15);
    checkTitleLabel = new QLabel;  // 选择标题
    checkTitleLabel->setFont(*font);
    checkTitleLabel->setText(tr("  选择标准品："));
    fuctionLabel = new  QLabel;     //函数标题
    fuctionLabel->setFont(*font);
    fuctionLabel->setText(tr("曲线拟合函数："));

//标准品项目选择下拉框
    combox = new QComboBox;
    combox->setFixedSize(200,30);
    combox->setAutoFillBackground(true);

    combox->setStyleSheet("background-color: rgb(251, 254, 255);" );
    combox->setStyleSheet(
                        //"QComboBox { min-height: 40px; min-width: 60px; }"
                          "QComboBox QAbstractItemView::item { min-height: 60px; min-width: 60px; }");
    combox->setEditable(true);

    /**
      *     下拉框选择更改
      */
    combox_projectName = new QComboBox;        //项目名称下拉框
    combox_reagentType = new QComboBox;        //试剂种类下拉框
    combox_productionDate = new QComboBox;     //生产日期下拉框
    combox_lotNumber = new QComboBox;          //批号下拉框

    dateEdit_productionDate = new QDateEdit;   //生产日期下拉框
    dateEdit_productionDate->setDisplayFormat("yyyy/MM");
    dateEdit_productionDate->setMinimumDate(QDate(2018,01,01));
    dateEdit_productionDate->setMaximumDate(QDate(2053,12,31 ));
    dateEdit_productionDate->setDate(QDate::currentDate());
    dateEdit_productionDate->setFixedSize(110,26);

    combox_projectName->setFixedSize(110,26);
    combox_reagentType->setFixedSize(80,26);
    combox_productionDate->setFixedSize(110,26);
    combox_lotNumber->setFixedSize(80,26);

    combox_projectName->setEditable(true);
    combox_reagentType->setEditable(true);
    combox_productionDate->setEditable(true);
    combox_lotNumber->setEditable(true);

    combox->setAutoFillBackground(true);

    label_projectName = new QLabel(tr("项目名称："));        //项目名称标题
    label_reagentType = new QLabel(tr("试剂种类："));        //试剂种类标题
    label_productionDate = new QLabel(tr("生产日期："));     //生产日期标题
    label_lotNumber = new QLabel(tr("生产批号："));          //批号标题
    QFont fontLabel("title",13);
    label_projectName->setFont(fontLabel);
    label_reagentType->setFont(fontLabel);
    label_productionDate->setFont(fontLabel);
    label_lotNumber->setFont(fontLabel);

    label_projectName->setFixedSize(80,26);
    label_reagentType->setFixedSize(80,26);
    label_productionDate->setFixedSize(80,26);
    label_lotNumber->setFixedSize(80,26);



//在下拉框里面添加项目
    QSqlQuery query;
    query.exec("select FILE_SHORT_NAME from reagent_standard_info");
    while(query.next()){
       combox->addItem(query.value(0).toString());
    }


    //    produceBightBtn = new QPushButton;  //生成曲线按钮
    //    produceBightBtn->setIconSize(QSize(40,40));
    //    produceBightBtn->setIcon(QIcon(":/picture/standardBight/produceBtn.png"));
    //    produceBightBtn->setText(tr("生成曲线"));
    //    produceBightBtn->setFlat(true);

        produceBightBtn = new QPushButton();
        produceBightBtn->setFlat(true);
        produceBightBtn->setFocusPolicy(Qt::TabFocus);
        produceBightBtn->setFixedSize(153,42);//图片的固定大小
        produceBightBtn->setStyleSheet("QPushButton{border-image: url(:/picture/standardBight/produceBtn-up.png);}"
                                 "QPushButton:hover{border-image: url(:/picture/standardBight/produceBtn-up.png);}"
                                 "QPushButton:pressed{border-image: url(:/picture/standardBight/produceBtn-down.png);}");

    //    resetBightBtn = new QPushButton;   //重置曲线按钮
    //    resetBightBtn->setIconSize(QSize(40,40));
    //    resetBightBtn->setIcon(QIcon(":/picture/standardBight/resetBtn.png"));
    //    resetBightBtn->setText(tr("重置曲线"));
    //    resetBightBtn->setFlat(true);
        resetBightBtn = new QPushButton();
        resetBightBtn->setFlat(true);
        resetBightBtn->setFocusPolicy(Qt::TabFocus);
        resetBightBtn->setFixedSize(153,42);//图片的固定大小
        resetBightBtn->setStyleSheet("QPushButton{border-image: url(:/picture/standardBight/resetBtn-up.png);}"
                                 "QPushButton:hover{border-image: url(:/picture/standardBight/resetBtn-up.png);}"
                                 "QPushButton:pressed{border-image: url(:/picture/standardBight/resetBtn-down.png);}");


/**
  *窗口界面
  */
    fuctionWidget = new QWidget;   //函数选择窗口
    fuctionWidget->setFixedSize(398,300);
    fuctionWidget->setWindowFlags(Qt::FramelessWindowHint);
    fuctionWidget->setAutoFillBackground(true);

    QPalette pa;
    QPixmap fuctionPixMap(":/picture/standardBight/backGround1.png");
    pa.setBrush(QPalette::Window,QBrush(fuctionPixMap));
    fuctionWidget->setPalette(pa);
//参数窗口背景
    parameterWidget = new QWidget; //参数界面窗口
    parameterWidget->setFixedSize(313,457);
    parameterWidget->setWindowFlags(Qt::FramelessWindowHint);
//    parameterWidget->setAutoFillBackground(true);
//    fuctionPixMap.load(":/picture/standardBight/backGround2.png");
//    pa.setBrush(QPalette::Window,QBrush(fuctionPixMap));
//    parameterWidget->setPalette(pa);

}

/**
 * @brief 信号和槽绑定函数初始化
 */
void standBight_controlWidget::connectInit()
{
    connect(resetBightBtn,SIGNAL(clicked()),this,SLOT(resetBightBtnSlot()));       
    connect(combox_projectName,SIGNAL(currentTextChanged(QString)),this,SLOT(initReagentType(QString)));
    connect(combox_reagentType,SIGNAL(currentTextChanged(QString)),this,SLOT(initLotNumber(QString)));
    connect(dateEdit_productionDate,SIGNAL(dateChanged(QDate)),this,SLOT(initLotNumber(QDate)));

    connect(combox_lotNumber,SIGNAL(currentTextChanged(QString)),this,SLOT(currentTextChangedSlot(QString)));
}

/**
 * @brief standBight_controlWidget::模型视图初始化
 */
void standBight_controlWidget::tableViewInit()
{
    QFont *font = new QFont("tableViewFont",15);
  /**
   *浓度参数窗口设计
   */
    parameterTableView = new QTableView(parameterWidget);
    parameterTableView->setGeometry(10,10,450,453);
    parameterTableView->setFixedSize(450,420);
    parameterTableView->setFont(*font);

    parameterTableView->verticalHeader()->hide();
    parameterTableView->setColumnWidth(0,90); //90
    parameterTableView->setColumnWidth(1,105);
    parameterTableView->setColumnWidth(2,105);
    parameterTableView->setColumnWidth(3,105);//主要为了把滚动条弄消失
    parameterTableView->verticalHeader()->setDefaultSectionSize(33);

    parameterTableView->verticalHeader()->hide();
    //设置列不能拖动
    parameterTableView->horizontalHeader()->setDisabled(true);
    //设置行不能拖动
    parameterTableView->verticalHeader()->setDisabled(true);
    parameterTableView->setContentsMargins(5,2,2,5);
//    parameterTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    sqlModel = new QStandardItemModel(12,3);   //数据库模型

    //让tableView中的文本居中
    for(int i = 0 ;i < 12 ;i++)
    {
        for(int j = 0;j < 3;j++)
        {
            sqlModel->setData(sqlModel->index(i,j,QModelIndex()),QVariant(tr("")));
            sqlModel->item(i,j)->setTextAlignment(Qt::AlignCenter);
        }
    }

    parameterTableView->setModel(sqlModel);
    sqlModel->setHeaderData(0,Qt::Horizontal,QObject::tr("标准点"));
    sqlModel->setHeaderData(1,Qt::Horizontal,QObject::tr("X-浓度"));
    sqlModel->setHeaderData(2,Qt::Horizontal,QObject::tr("Y-发光值"));

    sqlModel->setData(sqlModel->index(0,0,QModelIndex()),QVariant(tr("1")));
    sqlModel->setData(sqlModel->index(1,0,QModelIndex()),QVariant(tr("2")));
    sqlModel->setData(sqlModel->index(2,0,QModelIndex()),QVariant(tr("3")));
    sqlModel->setData(sqlModel->index(3,0,QModelIndex()),QVariant(tr("4")));
    sqlModel->setData(sqlModel->index(4,0,QModelIndex()),QVariant(tr("5")));
    sqlModel->setData(sqlModel->index(5,0,QModelIndex()),QVariant(tr("6")));
    sqlModel->setData(sqlModel->index(6,0,QModelIndex()),QVariant(tr("7")));
    sqlModel->setData(sqlModel->index(7,0,QModelIndex()),QVariant(tr("8")));
    sqlModel->setData(sqlModel->index(8,0,QModelIndex()),QVariant(tr("9")));
    sqlModel->setData(sqlModel->index(9,0,QModelIndex()),QVariant(tr("10")));
    sqlModel->setData(sqlModel->index(10,0,QModelIndex()),QVariant(tr("11")));
    sqlModel->setData(sqlModel->index(11,0,QModelIndex()),QVariant(tr("12")));
//    sqlModel->setItem(0,0,new QStandardItem(tr("1")));
//    sqlModel->setItem(1,0,new QStandardItem(tr("2")));
//    sqlModel->setItem(2,0,new QStandardItem(tr("3")));
//    sqlModel->setItem(3,0,new QStandardItem(tr("4")));
//    sqlModel->setItem(4,0,new QStandardItem(tr("5")));
//    sqlModel->setItem(5,0,new QStandardItem(tr("6")));
//    sqlModel->setItem(6,0,new QStandardItem(tr("7")));
//    sqlModel->setItem(7,0,new QStandardItem(tr("8")));
//    sqlModel->setItem(8,0,new QStandardItem(tr("9")));
//    sqlModel->setItem(9,0,new QStandardItem(tr("10")));
//    sqlModel->setItem(10,0,new QStandardItem(tr("11")));
//    sqlModel->setItem(11,0,new QStandardItem(tr("12")));
}

/**
 * @brief standBight_controlWidget::函数视图初始化
 */
void standBight_controlWidget::fuctionViewInit()
{
    radioWidget = new QWidget;  //单选窗口
    checkBoxWidget = new QWidget; //多选窗口

    fuctionWidgetLayout = new QHBoxLayout(fuctionWidget); //方程式布局

    radioBtnLayout = new QVBoxLayout(radioWidget);  //单选布局
//    checkBtnLayout = new QVBoxLayout(checkBoxWidget); //多选按钮布局
    checkLabelLayout = new QVBoxLayout;               //多选标签布局

 //绘制曲线方程式单选按钮
    radioBtn1 = new QRadioButton;
    radioBtn2 = new QRadioButton;
    radioBtn3 = new QRadioButton;
    radioBtn4 = new QRadioButton;
    radioBtn5 = new QRadioButton;
    radioBtn6 = new QRadioButton;
    radioBtn7 = new QRadioButton;

    radioBtn2->setChecked(true);

    radioBtnLayout->setMargin(0);
    radioBtnLayout->setSpacing(2);
    radioBtnLayout->addSpacing(20);
    radioBtnLayout->addWidget(radioBtn1);
    radioBtnLayout->addWidget(radioBtn2);
    radioBtnLayout->addWidget(radioBtn3);
    radioBtnLayout->addWidget(radioBtn4);
    radioBtnLayout->addWidget(radioBtn5);
    radioBtnLayout->addWidget(radioBtn6);
    radioBtnLayout->addWidget(radioBtn7);
    radioBtnLayout->addSpacing(20);

//绘制曲线方式式多选按钮
//    checkBoxBtn1 = new QCheckBox;
//    checkBoxBtn2 = new QCheckBox;
//    checkBoxBtn3 = new QCheckBox;
//    checkBoxBtn4 = new QCheckBox;
//    checkBoxBtn5 = new QCheckBox;
//    checkBoxBtn6 = new QCheckBox;
//    checkBoxBtn7 = new QCheckBox;

//    checkBoxBtn1->setStyleSheet(
//                "QCheckBox {spacing: 0px;}"
//                "QCheckBox::indicator {width: 20px;height: 20px;}"
//                "QCheckBox::indicator:unchecked {image: url(:/picture/standardBight/unchecked.png);} "
//                "QCheckBox::indicator:checked   {image: url(:/picture/standardBight/checked.png); }"
//                );
//    checkBoxBtn2->setStyleSheet(
//                "QCheckBox {spacing: 0px;}"
//                "QCheckBox::indicator {width: 20px;height: 20px;}"
//                "QCheckBox::indicator:unchecked {image: url(:/picture/standardBight/unchecked.png);} "
//                "QCheckBox::indicator:checked{image: url(:/picture/standardBight/checked.png); }"
//                );
//    checkBoxBtn3->setStyleSheet(
//                "QCheckBox {spacing: 0px;}"
//                "QCheckBox::indicator {width: 20px;height: 20px;}"
//                "QCheckBox::indicator:unchecked {image: url(:/picture/standardBight/unchecked.png);} "
//                "QCheckBox::indicator:checked{image: url(:/picture/standardBight/checked.png); }"
//                );
//    checkBoxBtn4->setStyleSheet(
//                "QCheckBox {spacing: 0px;}"
//                "QCheckBox::indicator {width: 20px;height: 20px;}"
//                "QCheckBox::indicator:unchecked {image: url(:/picture/standardBight/unchecked.png);} "
//                "QCheckBox::indicator:checked{image: url(:/picture/standardBight/checked.png); }"
//                );
//    checkBoxBtn5->setStyleSheet(
//                "QCheckBox {spacing: 0px;}"
//                "QCheckBox::indicator {width: 20px;height: 20px;}"
//                "QCheckBox::indicator:unchecked {image: url(:/picture/standardBight/unchecked.png);} "
//                "QCheckBox::indicator:checked{image: url(:/picture/standardBight/checked.png); }"
//                );
//    checkBoxBtn6->setStyleSheet(
//                "QCheckBox {spacing: 0px;}"
//                "QCheckBox::indicator {width: 20px;height: 20px;}"
//                "QCheckBox::indicator:unchecked {image: url(:/picture/standardBight/unchecked.png);} "
//                "QCheckBox::indicator:checked{image: url(:/picture/standardBight/checked.png); }"
//                );
//    checkBoxBtn7->setStyleSheet(
//                "QCheckBox {spacing: 0px;}"
//                "QCheckBox::indicator {width: 20px;height: 20px;}"
//                "QCheckBox::indicator:unchecked {image: url(:/picture/standardBight/unchecked.png);} "
//                "QCheckBox::indicator:checked{image: url(:/picture/standardBight/checked.png); }"
//                );

////----------------------------------------------------------

//    checkBoxBtn2->setCheckState(Qt::Checked);//默认选中
////---------------------------------------------------------
//    checkBtnLayout->setMargin(0);
//    checkBtnLayout->setSpacing(0);
//    checkBtnLayout->addSpacing(20);
//    checkBtnLayout->addWidget(checkBoxBtn1);
//    checkBtnLayout->addWidget(checkBoxBtn2);
//    checkBtnLayout->addWidget(checkBoxBtn3);
//    checkBtnLayout->addWidget(checkBoxBtn4);
//    checkBtnLayout->addWidget(checkBoxBtn5);
//    checkBtnLayout->addWidget(checkBoxBtn6);
//    checkBtnLayout->addWidget(checkBoxBtn7);
//    checkBtnLayout->addSpacing(25);

 //曲线方程式颜色标签
    checkLabel1 = new QLabel;
    checkLabel1->setFixedSize(30,15);
    checkLabel1->setStyleSheet("background-color:red");
    checkLabel2 = new QLabel;
    checkLabel2->setFixedSize(30,15);
    checkLabel2->setStyleSheet("background-color:cyan");
    checkLabel3 = new QLabel;
    checkLabel3->setFixedSize(30,15);
    checkLabel3->setStyleSheet("background-color:darkBlue");
    checkLabel4 = new QLabel;
    checkLabel4->setFixedSize(30,15);
    checkLabel4->setStyleSheet("background-color:green");
    checkLabel5 = new QLabel;
    checkLabel5->setFixedSize(30,15);
    checkLabel5->setStyleSheet("background-color:blue");
    checkLabel6 = new QLabel;
    checkLabel6->setFixedSize(30,15);
    checkLabel6->setStyleSheet("background-color:yellow");
    checkLabel7 = new QLabel;
    checkLabel7->setFixedSize(30,15);
    checkLabel7->setStyleSheet("background-color:darkYellow");
    checkLabelLayout->setMargin(0);
    checkLabelLayout->setSpacing(2);
    checkLabelLayout->addSpacing(20);
    checkLabelLayout->addWidget(checkLabel1);
    checkLabelLayout->addWidget(checkLabel2);
    checkLabelLayout->addWidget(checkLabel3);
    checkLabelLayout->addWidget(checkLabel4);
    checkLabelLayout->addWidget(checkLabel5);
    checkLabelLayout->addWidget(checkLabel6);
    checkLabelLayout->addWidget(checkLabel7);
    checkLabelLayout->addSpacing(20);

    /**
     *方程式选择窗口
     */
    fuctionListWidget = new QListWidget(fuctionWidget);
    fuctionListWidget->setViewMode(QListView::ListMode);
    fuctionListWidget->setFixedSize(200,250);
    fuctionListWidget->setSpacing(8);
    fuctionListWidget->addItem(new QListWidgetItem(tr("Log-Logist方程")));
    fuctionListWidget->addItem(new QListWidgetItem(tr("多项式(2~6次)方程")));
    fuctionListWidget->addItem(new QListWidgetItem(tr("四参数方程")));
    fuctionListWidget->addItem(new QListWidgetItem(tr("对数Ln方程")));
    fuctionListWidget->addItem(new QListWidgetItem(tr("线性拟合方程")));
    fuctionListWidget->addItem(new QListWidgetItem(tr("xxxxxxx方程")));
    fuctionListWidget->addItem(new QListWidgetItem(tr("xxxxxxx方程")));


    fuctionWidgetLayout->setMargin(0);
    fuctionWidgetLayout->setSpacing(2);
//    fuctionWidgetLayout->addSpacing(30);
//    fuctionWidgetLayout->addWidget(checkBoxWidget);
    fuctionWidgetLayout->addSpacing(40);
    fuctionWidgetLayout->addLayout(checkLabelLayout);
    fuctionWidgetLayout->addSpacing(20);
    fuctionWidgetLayout->addWidget(radioWidget);
    fuctionWidgetLayout->addSpacing(40);
    fuctionWidgetLayout->addWidget(fuctionListWidget);
    fuctionWidgetLayout->addSpacing(20);

}

/**
 * @brief 标准点多选按钮
 */
void standBight_controlWidget::PointCheckWidgetInit()
{
    pointCheckWidget = new QWidget;
    PointcheckBtnLayout = new QVBoxLayout(pointCheckWidget);
    PointcheckBtnLayout->setMargin(0);
    PointcheckBtnLayout->setSpacing(5);
    PCheckBtn1 = new QCheckBox;
    PCheckBtn1->setStyleSheet("QCheckBox::indicator{ width: 28px;  height: 28px;}QCheckBox::indicator:checked{image:url(:/picture/standardTest/Checked_png.png);}"
                          "QCheckBox::indicator:unchecked{image:url(:/picture/standardTest/UnChecked_png.png); } "
                          "QCheckBox::indicator:checked:disabled{image:url(:/picture/standardTest/UnChecked_png.png);}"
                          );
    PCheckBtn2 = new QCheckBox;
    PCheckBtn2->setStyleSheet("QCheckBox::indicator{ width: 28px;  height: 28px;}QCheckBox::indicator:checked{image:url(:/picture/standardTest/Checked_png.png);}"
                          "QCheckBox::indicator:unchecked{image:url(:/picture/standardTest/UnChecked_png.png); } "
                          "QCheckBox::indicator:checked:disabled{image:url(:/picture/standardTest/UnChecked_png.png);}"
                          );
    PCheckBtn3 = new QCheckBox;
    PCheckBtn3->setStyleSheet("QCheckBox::indicator{ width: 28px;  height: 28px;}QCheckBox::indicator:checked{image:url(:/picture/standardTest/Checked_png.png);}"
                          "QCheckBox::indicator:unchecked{image:url(:/picture/standardTest/UnChecked_png.png); } "
                          "QCheckBox::indicator:checked:disabled{image:url(:/picture/standardTest/UnChecked_png.png);}"
                          );
    PCheckBtn4 = new QCheckBox;
    PCheckBtn4->setStyleSheet("QCheckBox::indicator{ width: 28px;  height: 28px;}QCheckBox::indicator:checked{image:url(:/picture/standardTest/Checked_png.png);}"
                          "QCheckBox::indicator:unchecked{image:url(:/picture/standardTest/UnChecked_png.png); } "
                          "QCheckBox::indicator:checked:disabled{image:url(:/picture/standardTest/UnChecked_png.png);}"
                          );
    PCheckBtn5 = new QCheckBox;
    PCheckBtn5->setStyleSheet("QCheckBox::indicator{ width: 28px;  height: 28px;}QCheckBox::indicator:checked{image:url(:/picture/standardTest/Checked_png.png);}"
                          "QCheckBox::indicator:unchecked{image:url(:/picture/standardTest/UnChecked_png.png); } "
                          "QCheckBox::indicator:checked:disabled{image:url(:/picture/standardTest/UnChecked_png.png);}"
                          );
    PCheckBtn6 = new QCheckBox;
    PCheckBtn6->setStyleSheet("QCheckBox::indicator{ width: 28px;  height: 28px;}QCheckBox::indicator:checked{image:url(:/picture/standardTest/Checked_png.png);}"
                          "QCheckBox::indicator:unchecked{image:url(:/picture/standardTest/UnChecked_png.png); } "
                          "QCheckBox::indicator:checked:disabled{image:url(:/picture/standardTest/UnChecked_png.png);}"
                          );
    PCheckBtn6 = new QCheckBox;
    PCheckBtn6->setStyleSheet("QCheckBox::indicator{ width: 28px;  height: 28px;}QCheckBox::indicator:checked{image:url(:/picture/standardTest/Checked_png.png);}"
                          "QCheckBox::indicator:unchecked{image:url(:/picture/standardTest/UnChecked_png.png); } "
                          "QCheckBox::indicator:checked:disabled{image:url(:/picture/standardTest/UnChecked_png.png);}"
                          );
    PCheckBtn7 = new QCheckBox;
    PCheckBtn7->setStyleSheet("QCheckBox::indicator{ width: 28px;  height: 28px;}QCheckBox::indicator:checked{image:url(:/picture/standardTest/Checked_png.png);}"
                          "QCheckBox::indicator:unchecked{image:url(:/picture/standardTest/UnChecked_png.png); } "
                          "QCheckBox::indicator:checked:disabled{image:url(:/picture/standardTest/UnChecked_png.png);}"
                          );
    PCheckBtn8 = new QCheckBox;
    PCheckBtn8->setStyleSheet("QCheckBox::indicator{ width: 28px;  height: 28px;}QCheckBox::indicator:checked{image:url(:/picture/standardTest/Checked_png.png);}"
                          "QCheckBox::indicator:unchecked{image:url(:/picture/standardTest/UnChecked_png.png); } "
                          "QCheckBox::indicator:checked:disabled{image:url(:/picture/standardTest/UnChecked_png.png);}"
                          );
    PCheckBtn9 = new QCheckBox;
    PCheckBtn9->setStyleSheet("QCheckBox::indicator{ width: 28px;  height: 28px;}QCheckBox::indicator:checked{image:url(:/picture/standardTest/Checked_png.png);}"
                          "QCheckBox::indicator:unchecked{image:url(:/picture/standardTest/UnChecked_png.png); } "
                          "QCheckBox::indicator:checked:disabled{image:url(:/picture/standardTest/UnChecked_png.png);}"
                          );
    PCheckBtn10 = new QCheckBox;
    PCheckBtn10->setStyleSheet("QCheckBox::indicator{ width: 28px;  height: 28px;}QCheckBox::indicator:checked{image:url(:/picture/standardTest/Checked_png.png);}"
                          "QCheckBox::indicator:unchecked{image:url(:/picture/standardTest/UnChecked_png.png); } "
                          "QCheckBox::indicator:checked:disabled{image:url(:/picture/standardTest/UnChecked_png.png);}"
                          );
    PCheckBtn11 = new QCheckBox;
    PCheckBtn11->setStyleSheet("QCheckBox::indicator{width: 28px;  height: 28px;}QCheckBox::indicator:checked{image:url(:/picture/standardTest/Checked_png.png);}"
                          "QCheckBox::indicator:unchecked{image:url(:/picture/standardTest/UnChecked_png.png); } "
                          "QCheckBox::indicator:checked:disabled{image:url(:/picture/standardTest/UnChecked_png.png);}"
                          );
    PCheckBtn12 = new QCheckBox;
    PCheckBtn12->setStyleSheet("QCheckBox::indicator{width: 28px;  height: 28px;}QCheckBox::indicator:checked{image:url(:/picture/standardTest/Checked_png.png);}"
                          "QCheckBox::indicator:unchecked{image:url(:/picture/standardTest/UnChecked_png.png); } "
                          "QCheckBox::indicator:checked:disabled{image:url(:/picture/standardTest/UnChecked_png.png);}"
                          );
    PointcheckBtnLayout->addSpacing(80);
    PointcheckBtnLayout->addWidget(PCheckBtn1);
    PointcheckBtnLayout->addWidget(PCheckBtn2);
    PointcheckBtnLayout->addWidget(PCheckBtn3);
    PointcheckBtnLayout->addWidget(PCheckBtn4);
    PointcheckBtnLayout->addWidget(PCheckBtn5);
    PointcheckBtnLayout->addWidget(PCheckBtn6);
    PointcheckBtnLayout->addWidget(PCheckBtn7);
    PointcheckBtnLayout->addWidget(PCheckBtn8);
    PointcheckBtnLayout->addWidget(PCheckBtn9);
    PointcheckBtnLayout->addWidget(PCheckBtn10);
    PointcheckBtnLayout->addWidget(PCheckBtn11);
    PointcheckBtnLayout->addWidget(PCheckBtn12);
}



/**
 * @brief 生成曲线时，返回选择值
 * @return
 */
QVector<double> standBight_controlWidget::ReturnCheck_C_Data()
{
    int count = 0;   //已经选择的标准点数
    QVector<double> temp;
    if(PCheckBtn1->checkState() == Qt::Checked){
        if(sqlModel->data(sqlModel->index(0,1)).toString().isEmpty()){
            QMessageBox::critical(this,tr("提示!"),tr("不能选择空光子值项."));
            temp.clear();
            return temp;
        }
        temp << sqlModel->data(sqlModel->index(0,1)).toDouble();
        count++;
    }
    if(PCheckBtn2->checkState() == Qt::Checked){
        if(sqlModel->data(sqlModel->index(1,1)).toString().isEmpty()){
            QMessageBox::critical(this,tr("提示!"),tr("不能选择空光子值项."));
            temp.clear();
            return temp;
        }
        temp << sqlModel->data(sqlModel->index(1,1)).toDouble();
        count++;
    }
    if(PCheckBtn3->checkState() == Qt::Checked){
        if(sqlModel->data(sqlModel->index(2,1)).toString().isEmpty()){
            QMessageBox::critical(this,tr("提示!"),tr("不能选择空光子值项."));
            temp.clear();
            return temp;
        }
        temp << sqlModel->data(sqlModel->index(2,1)).toDouble();
        count++;
    }

    if(PCheckBtn4->checkState() == Qt::Checked){
        if(sqlModel->data(sqlModel->index(3,1)).toString().isEmpty()){
            QMessageBox::critical(this,tr("提示!"),tr("不能选择空光子值项."));
            temp.clear();
            return temp;
        }
        temp << sqlModel->data(sqlModel->index(3,1)).toDouble();
        count++;
    }

    if(PCheckBtn5->checkState() == Qt::Checked){
        if(sqlModel->data(sqlModel->index(4,1)).toString().isEmpty()){
            QMessageBox::critical(this,tr("提示!"),tr("不能选择空光子值项."));
            temp.clear();
            return temp;
        }
        temp << sqlModel->data(sqlModel->index(4,1)).toDouble();
        count++;
    }
    if(PCheckBtn6->checkState() == Qt::Checked){
        if(sqlModel->data(sqlModel->index(5,1)).toString().isEmpty()){
            QMessageBox::critical(this,tr("提示!"),tr("不能选择空光子值项."));
            temp.clear();
            return temp;
        }
        temp << sqlModel->data(sqlModel->index(5,1)).toDouble();
        count++;
    }
    if(PCheckBtn7->checkState() == Qt::Checked){
        if(sqlModel->data(sqlModel->index(6,1)).toString().isEmpty()){
            QMessageBox::critical(this,tr("提示!"),tr("不能选择空光子值项."));
            temp.clear();
            return temp;
        }
        temp << sqlModel->data(sqlModel->index(6,1)).toDouble();
        count++;
    }
    if(PCheckBtn8->checkState() == Qt::Checked){
        if(sqlModel->data(sqlModel->index(7,1)).toString().isEmpty()){
            QMessageBox::critical(this,tr("提示!"),tr("不能选择空光子值项."));
            temp.clear();
            return temp;
        }
        temp << sqlModel->data(sqlModel->index(7,1)).toDouble();
        count++;
    }
    if(PCheckBtn9->checkState() == Qt::Checked){
        if(sqlModel->data(sqlModel->index(8,1)).toString().isEmpty()){
            QMessageBox::critical(this,tr("提示!"),tr("不能选择空光子值项."));
            temp.clear();
            return temp;
        }
        temp << sqlModel->data(sqlModel->index(8,1)).toDouble();
        count++;
    }
    if(PCheckBtn10->checkState() == Qt::Checked){
        if(sqlModel->data(sqlModel->index(9,1)).toString().isEmpty()){
            QMessageBox::critical(this,tr("提示!"),tr("不能选择空光子值项."));
            temp.clear();
            return temp;
        }
        temp << sqlModel->data(sqlModel->index(9,1)).toDouble();
        count++;
    }
    if(PCheckBtn11->checkState() == Qt::Checked){
        if(sqlModel->data(sqlModel->index(10,1)).toString().isEmpty()){
            QMessageBox::critical(this,tr("提示!"),tr("不能选择空光子值项."));
            temp.clear();
            return temp;
        }
        temp << sqlModel->data(sqlModel->index(10,1)).toDouble();
        count++;
    }
    if(PCheckBtn12->checkState() == Qt::Checked){
        if(sqlModel->data(sqlModel->index(11,1)).toString().isEmpty()){
            QMessageBox::critical(this,tr("提示!"),tr("不能选择空光子值项."));
            temp.clear();
            return temp;
        }
        temp << sqlModel->data(sqlModel->index(11,1)).toDouble();
        count++;
    }
    if(count < CHECK_MIN){
        QMessageBox::critical(this,tr("提示!"),tr("选择标准点数量小于生成曲线最小数量。"));
        temp.clear();
        return temp;
    }
    return temp;
}

QVector<double> standBight_controlWidget::ReturnCheck_P_Data()
{
    int count = 0;   //已经选择的标准点数
    QVector<double> temp;
    if(PCheckBtn1->checkState() == Qt::Checked){
        temp << sqlModel->data(sqlModel->index(0,2)).toDouble();
    }
    if(PCheckBtn2->checkState() == Qt::Checked){
        temp << sqlModel->data(sqlModel->index(1,2)).toDouble();
    }
    if(PCheckBtn3->checkState() == Qt::Checked){
        temp << sqlModel->data(sqlModel->index(2,2)).toDouble();
    }

    if(PCheckBtn4->checkState() == Qt::Checked){
        temp << sqlModel->data(sqlModel->index(3,2)).toDouble();
    }

    if(PCheckBtn5->checkState() == Qt::Checked){
        temp << sqlModel->data(sqlModel->index(4,2)).toDouble();
    }
    if(PCheckBtn6->checkState() == Qt::Checked){
        temp << sqlModel->data(sqlModel->index(5,2)).toDouble();
    }
    if(PCheckBtn7->checkState() == Qt::Checked){
        temp << sqlModel->data(sqlModel->index(6,2)).toDouble();
    }
    if(PCheckBtn8->checkState() == Qt::Checked){
        temp << sqlModel->data(sqlModel->index(7,2)).toDouble();
    }
    if(PCheckBtn9->checkState() == Qt::Checked){
        temp << sqlModel->data(sqlModel->index(8,2)).toDouble();
    }
    if(PCheckBtn10->checkState() == Qt::Checked){
        temp << sqlModel->data(sqlModel->index(9,2)).toDouble();
    }
    if(PCheckBtn11->checkState() == Qt::Checked){
        temp << sqlModel->data(sqlModel->index(10,2)).toDouble();
    }
    if(PCheckBtn12->checkState() == Qt::Checked){
        temp << sqlModel->data(sqlModel->index(11,2)).toDouble();
    }
    return temp;
}

/**
 * @brief standBight_controlWidget::init_comboxData
 * 初始化combox 初始值
 */
void standBight_controlWidget::init_comboxData()
{
    QSqlQueryModel model;
    QString str = "select DISTINCT PROJECT_NAME from Reagent_Bar_Info where CATEGORY = '标准品'";
    model.setQuery(str);
    int count = model.rowCount();
    for(int i = 0;i < count;i++)
    {
        QModelIndex index_rt = model.index(i,0);
        QString str_rt = model.data(index_rt).toString();
        combox_projectName->addItem(str_rt);
    }

    QString strProject_name = combox_projectName->currentText();

    str = "select DISTINCT REAGENT_TYPE from Reagent_Bar_Info where CATEGORY = ";
    str += "'标准品'";
    str += "and PROJECT_NAME = '" + strProject_name + "'";
    model.setQuery(str);

    int count_r = model.rowCount();
    for(int i = 0;i < count_r;i++)
    {
        QModelIndex index_rt = model.index(i,0);
        QString str_rt = model.data(index_rt).toString();
        combox_reagentType->addItem(str_rt);
    }

    for(int i = 0 ;i <= 15;i++)
    {
        if(i == 0)
        {
            combox_lotNumber->addItem("");
        }else if(i < 10)
        {
            combox_lotNumber->addItem("0" + QString::number(i) + "批");
        }else
        {
            combox_lotNumber->addItem(QString::number(i) + "批");
        }
    }
}

void standBight_controlWidget::initReagentType(QString strProjectName)
{
    QSqlQueryModel model;
    QString str = "select DISTINCT REAGENT_TYPE from Reagent_Bar_Info where CATEGORY = ";
    str += "'标准品'";
    str += "and PROJECT_NAME = '" + strProjectName + "'";
    model.setQuery(str);
    combox_reagentType->clear();

    int count_r = model.rowCount();
    for(int i = 0;i < count_r;i++)
    {
        QModelIndex index_rt = model.index(i,0);
        QString str_rt = model.data(index_rt).toString();
        combox_reagentType->addItem(str_rt);
    }
}

void standBight_controlWidget::initLotNumber(QString str)
{
    combox_lotNumber->setCurrentText("");
}

void standBight_controlWidget::initLotNumber(QDate date)
{
    combox_lotNumber->setCurrentText("");
}




/**
 * @brief 重新生成曲线
 */
void standBight_controlWidget::resetBightBtnSlot()
{

}

/**
 * @brief standBight_controlWidget::当下拉选择框数据变化时更改参数表数据
 */
void standBight_controlWidget::currentTextChangedSlot(const QString &text)
{
//    QString strCateGory; //品类
//    QString strCateGoryCode; //品类条码
//    QString strProjectName; //项目名称
//    QString strProjectNameCOde; //项目名称条码
//    QString strReagentType; //试剂种类
//    QString strReagentTypeCode; //试剂种类条码

    strProjectName = combox_projectName->currentText();
    qDebug() << "选中项目：" <<strProjectName ;
    strReagentType = combox_reagentType->currentText();
    qDebug() << "选中种类：" <<strReagentType ;
    int year = dateEdit_productionDate->date().year();
    int month = dateEdit_productionDate->date().month();
    qDebug() << "选中时间：" << year <<"---"<< month ;
    QString strLotNumber = text;
    qDebug() << "选中批号：" <<strLotNumber ;


    QSqlQueryModel model;
    QString queryStr = "";

    //查询项目名称编码
    queryStr = "select DISTINCT PROJECT_NAME_CODE from Reagent_Bar_Info where CATEGORY = ";
    queryStr += "'标准品'";
    queryStr += "and PROJECT_NAME = '" + strProjectName + "'";
    model.setQuery(queryStr);

    strProjectNameCode = model.index(0,0).data().toString();

    strCateGory = "标准品";
    //查询标准品编码
    queryStr = "select DISTINCT CATEGORY_CODE from Reagent_Bar_Info where CATEGORY = '标准品'";
    model.setQuery(queryStr);

    strCateGoryCode = model.index(0,0).data().toString();

    //查询试剂种类编码

    queryStr = "select DISTINCT REAGENT_TYPE_CODE from Reagent_Bar_Info where CATEGORY = '标准品'";
    queryStr += "and PROJECT_NAME = '" + strProjectName + "'";
    queryStr += "and REAGENT_TYPE = '" + strReagentType + "'";
    model.setQuery(queryStr);

    strReagentTypeCode = model.index(0,0).data().toString();

    QString strYearCode = "";
    QString strMonthCode = "";
    QString strLotNumberCode = "";

    //年份编码
    int f = year - 2018;

    if(f < 0)
    {
        strYearCode = "*";
    }else if(f < 9)
    {
        strYearCode = QString::number(f);
    }else
    {
        char temp = f + 55;
        strYearCode = (QString)temp;
    }
    //月份编码
    if(month < 9)
    {
        strMonthCode = QString ::number(month);
    }else
    {
        char temp = month + 55;
        strMonthCode = (QString)temp;
    }

    //批号编码

    QString strLot = strLotNumber.mid(0,2);
    int temp_strLot = strLot.toInt();

    qDebug()<<"temp_strLot:"<<temp_strLot;

    if(temp_strLot <= 9)
    {
        strLotNumberCode = QString :: number(temp_strLot);
    }else
    {
        char temp = temp_strLot + 55;
        strLotNumberCode = (QString)temp;
    }

    //七位编码
    strBarCode = strCateGoryCode + strProjectNameCode + strReagentTypeCode +
            strYearCode + strMonthCode + strLotNumberCode;

    //根据七位编码查找标准点信息
    QSqlQuery query;
    int row = 0;
    for(int j = 0;j < 12;j++){
        for(int i = 1;i<3;i++){
            sqlModel->setData(sqlModel->index(j,i),QVariant(""));
            row++;
        }
    }
    row = 0;

    query.exec("select POINT_C_ONE,POINT_P_ONE,POINT_C_TWO,POINT_P_TWO,POINT_C_THREE,POINT_P_THREE,POINT_C_FOUR,POINT_P_FOUR,POINT_C_FIVE,POINT_P_FIVE,POINT_C_SIX,POINT_P_SIX,POINT_C_SEVEN,POINT_P_SEVEN,"
               "POINT_C_EIGHT,POINT_P_EIGHT,POINT_C_NINE,POINT_P_NINE,POINT_C_TEN,POINT_P_TEN,POINT_C_ELEVEN,POINT_P_ELEVEN,POINT_C_TWELVE,POINT_P_TWELVE from reagent_standard_info where STANDARD_CODE = ?");
    qDebug() <<"七位编码：" <<strBarCode;
    query.bindValue(0,strBarCode);
    qDebug()<<"数据查询："<<query.exec();
    qDebug()<<"数据查询："<<query.value(0).toDouble();
    qDebug()<<"数据查询："<<query.value(1).toInt();
    while(query.next()){
        for(int j = 0;j < 12;j++){
            for(int i = 1;i<3;i++){
                qDebug()<<"行："<<i;
                if(query.value(row) == 0)
                    return;
                sqlModel->setData(sqlModel->index(j,i),query.value(row));
                row++;
            }
        }
    }




}
void standBight_controlWidget::saveStandData()
{
    //保存标准点数据

    ConfigFile cf;
    QString CREATOR_ID              =   cf.getCurrentUser_Name();
    QString CREATE_TIME             =   QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString MODIFIER_ID             =   "无";
    QString MODIFY_TIME             =   "无";
    char    DEL_FLAG                =   0;

    //附加表数据准备
    //STANDARD_CODE
    QStringList strlist;//存储12个点的CP值


    for(int i=0;i<12;i++)
    {
        if(i==0&&PCheckBtn1->checkState()==Qt::Unchecked)i++;
        if(i==1&&PCheckBtn2->checkState()==Qt::Unchecked)i++;
        if(i==2&&PCheckBtn3->checkState()==Qt::Unchecked)i++;
        if(i==3&&PCheckBtn4->checkState()==Qt::Unchecked)i++;
        if(i==4&&PCheckBtn5->checkState()==Qt::Unchecked)i++;
        if(i==5&&PCheckBtn6->checkState()==Qt::Unchecked)i++;
        if(i==6&&PCheckBtn7->checkState()==Qt::Unchecked)i++;
        if(i==7&&PCheckBtn8->checkState()==Qt::Unchecked)i++;
        if(i==8&&PCheckBtn9->checkState()==Qt::Unchecked)i++;
        if(i==9&&PCheckBtn10->checkState()==Qt::Unchecked)i++;
        if(i==10&&PCheckBtn11->checkState()==Qt::Unchecked)i++;
        if(i==11&&PCheckBtn12->checkState()==Qt::Unchecked)break;

        strlist.append(sqlModel->index(i,1).data().toString());
        strlist.append(sqlModel->index(i,2).data().toString());

    }

    DataOpationStandardtest dost;

    if(strlist.isEmpty())return;
    dost.deleteData_reagent_standard_info(strBarCode) ;
    dost.insertData_reagent_standard_info(strBarCode,
                                             strlist,
                                             CREATOR_ID,
                                             CREATE_TIME,
                                             MODIFIER_ID,
                                             MODIFY_TIME,
                                             DEL_FLAG);

}
