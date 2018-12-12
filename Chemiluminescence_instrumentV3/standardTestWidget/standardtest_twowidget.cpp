
#include "standardtest_twowidget.h"
#include <QHeaderView>
#include "standardTestWidget/standardtestwidget.h"
#include "dataopationstandardtest.h"
#include <QDateTime>
/**
 * @brief standardTest_TwoWidget::构造函数
 * @param parent
 */
standardTest_TwoWidget::standardTest_TwoWidget(QWidget *parent) : QWidget(parent)
{
    title_init();
    tableView_init();
    checkWidgetInit();
    connect(SureBtn,SIGNAL(clicked()),this,SLOT(SureBtnSlot()));
    connect(btn_save,SIGNAL(clicked()),this,SLOT(saveBtnSlot()));
}

void standardTest_TwoWidget::title_init()
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

    BtnWidget = new  QWidget(this);
    BtnLayout = new  QHBoxLayout;


    SureBtn =  new QPushButton;             //确定
    SureBtn->setFont(*font);
    SureBtn->setFixedSize(153,42);
    SureBtn->setFlat(true);
    SureBtn->setStyleSheet("QPushButton{border-image: url(:/picture/standardTest/sure-up.png);}"
                               "QPushButton:hover{border-image: url(:/picture/standardTest/sure-up.png);}"
                               "QPushButton:pressed{border-image: url(:/picture/standardTest/sure-down.png);}");


    btn_save = new QPushButton;   /**<保存 */
    btn_save->setFixedSize(150,40);
    btn_save->setStyleSheet("QPushButton{border-image: url(:/picture/calibrationWidget/save-up.png);}"
                               "QPushButton:hover{border-image: url(:/picture/calibrationWidget/save-up.png);}"
                               "QPushButton:pressed{border-image: url(:/picture/calibrationWidget/save-down.png);}");
    btn_save->setFlat(true);



    returnBtn = new QPushButton;            //返回
    returnBtn->setFont(*font);
    returnBtn->setFixedSize(153,42);
    returnBtn->setFlat(true);
    returnBtn->setStyleSheet("QPushButton{border-image: url(:/picture/standardTest/returnPng-up.png);}"
                               "QPushButton:hover{border-image: url(:/picture/standardTest/returnPng-up.png);}"
                               "QPushButton:pressed{border-image: url(:/picture/standardTest/returnPng-down.png);}");

    //布局
    BtnLayout->addWidget(SureBtn);
    BtnLayout->addSpacing(100);
    BtnLayout->addWidget(btn_save);
    BtnLayout->addSpacing(100);
    BtnLayout->addWidget(returnBtn);
    BtnLayout->addSpacing(100);
    BtnLayout->addStretch();
    //QWidget
    BtnWidget->setLayout(BtnLayout);
    BtnWidget->setGeometry(20,60,1000,90);
}


/**
 * @brief standardTest_TwoWidget::模型视图初始化
 */
void standardTest_TwoWidget::tableView_init()
{
    QFont *font;
    font = new QFont("tableview",16);

    model = new QStandardItemModel(12,6);

    //文本居中
    for(int i = 0 ;i < 12 ;i++)
    {
        for(int j = 1;j < 6;j++)
        {

            model->setData(model->index(i,j,QModelIndex()),QVariant(tr("")));
            model->item(i,j)->setTextAlignment(Qt::AlignCenter);
        }
    }
    tableView = new QTableView(this);
    tableView->setFixedSize(1425,730);
    tableView->setModel(model);
    tableView->setFont(*font);


 //模型视图设置
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("槽编号"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("标准品条码"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("有效起始日期"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("有效截止日期"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("测量光子数"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("标称浓度"));
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


    //设置列宽
    tableView->setColumnWidth(0,237);
    tableView->setColumnWidth(1,237);
    tableView->setColumnWidth(2,237);
    tableView->setColumnWidth(3,237);
    tableView->setColumnWidth(4,237);
    tableView->setColumnWidth(5,237);
    //设置：行高
    tableView->verticalHeader()->setDefaultSectionSize(58);

    /**
     * tabelView表格设置
     */
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
    //    tableView->setStyleSheet("selection-background-color: red");

    tableView->setGeometry(200,150,800,780);


}


/**
 * @brief 多选框初始化z
 */
void standardTest_TwoWidget::checkWidgetInit()
{
    checkWidget = new QWidget(this);
    checkWidget->setFixedSize(70,782);
    checkBox1 = new  QCheckBox(checkWidget);
    checkBox1->setStyleSheet("QCheckBox::indicator{ width: 40px;  height: 40px;}QCheckBox::indicator:checked{image:url(:/picture/standardTest/Checked_png.png);}"
                          "QCheckBox::indicator:unchecked{image:url(:/picture/standardTest/UnChecked_png.png); } "
                          "QCheckBox::indicator:checked:disabled{image:url(:/picture/standardTest/UnChecked_png.png);}"
                          );
    checkBox2 = new  QCheckBox(checkWidget);
    checkBox2->setStyleSheet("QCheckBox::indicator{ width: 40px;  height: 40px;}QCheckBox::indicator:checked{image:url(:/picture/standardTest/Checked_png.png);}"
                          "QCheckBox::indicator:unchecked{image:url(:/picture/standardTest/UnChecked_png.png); } "
                          "QCheckBox::indicator:checked:disabled{image:url(:/picture/standardTest/UnChecked_png.png);}"
                          );
    checkBox3 = new  QCheckBox(checkWidget);
    checkBox3->setStyleSheet("QCheckBox::indicator{ width: 40px;  height: 40px;}QCheckBox::indicator:checked{image:url(:/picture/standardTest/Checked_png.png);}"
                          "QCheckBox::indicator:unchecked{image:url(:/picture/standardTest/UnChecked_png.png); } "
                          "QCheckBox::indicator:checked:disabled{image:url(:/picture/standardTest/UnChecked_png.png);}"
                          );
    checkBox4 = new  QCheckBox(checkWidget);
    checkBox4->setStyleSheet("QCheckBox::indicator{ width: 40px;  height: 40px;}QCheckBox::indicator:checked{image:url(:/picture/standardTest/Checked_png.png);}"
                          "QCheckBox::indicator:unchecked{image:url(:/picture/standardTest/UnChecked_png.png); } "
                          "QCheckBox::indicator:checked:disabled{image:url(:/picture/standardTest/UnChecked_png.png);}"
                          );
    checkBox5 = new  QCheckBox(checkWidget);
    checkBox5->setStyleSheet("QCheckBox::indicator{ width: 40px;  height: 40px;}QCheckBox::indicator:checked{image:url(:/picture/standardTest/Checked_png.png);}"
                          "QCheckBox::indicator:unchecked{image:url(:/picture/standardTest/UnChecked_png.png); } "
                          "QCheckBox::indicator:checked:disabled{image:url(:/picture/standardTest/UnChecked_png.png);}"
                          );
    checkBox6 = new  QCheckBox(checkWidget);
    checkBox6->setStyleSheet("QCheckBox::indicator{ width: 40px;  height: 40px;}QCheckBox::indicator:checked{image:url(:/picture/standardTest/Checked_png.png);}"
                          "QCheckBox::indicator:unchecked{image:url(:/picture/standardTest/UnChecked_png.png); } "
                          "QCheckBox::indicator:checked:disabled{image:url(:/picture/standardTest/UnChecked_png.png);}"
                          );
    checkBox7 = new  QCheckBox(checkWidget);
    checkBox7->setStyleSheet("QCheckBox::indicator{ width: 40px;  height: 40px;}QCheckBox::indicator:checked{image:url(:/picture/standardTest/Checked_png.png);}"
                          "QCheckBox::indicator:unchecked{image:url(:/picture/standardTest/UnChecked_png.png); } "
                          "QCheckBox::indicator:checked:disabled{image:url(:/picture/standardTest/UnChecked_png.png);}"
                          );
    checkBox8 = new  QCheckBox(checkWidget);
    checkBox8->setStyleSheet("QCheckBox::indicator{ width: 40px;  height: 40px;}QCheckBox::indicator:checked{image:url(:/picture/standardTest/Checked_png.png);}"
                          "QCheckBox::indicator:unchecked{image:url(:/picture/standardTest/UnChecked_png.png); } "
                          "QCheckBox::indicator:checked:disabled{image:url(:/picture/standardTest/UnChecked_png.png);}"
                          );
    checkBox9 = new  QCheckBox(checkWidget);
    checkBox9->setStyleSheet("QCheckBox::indicator{ width: 40px;  height: 40px;}QCheckBox::indicator:checked{image:url(:/picture/standardTest/Checked_png.png);}"
                          "QCheckBox::indicator:unchecked{image:url(:/picture/standardTest/UnChecked_png.png); } "
                          "QCheckBox::indicator:checked:disabled{image:url(:/picture/standardTest/UnChecked_png.png);}"
                          );
    checkBox10 = new  QCheckBox(checkWidget);
    checkBox10->setStyleSheet("QCheckBox::indicator{ width: 40px;  height: 40px;}QCheckBox::indicator:checked{image:url(:/picture/standardTest/Checked_png.png);}"
                          "QCheckBox::indicator:unchecked{image:url(:/picture/standardTest/UnChecked_png.png); } "
                          "QCheckBox::indicator:checked:disabled{image:url(:/picture/standardTest/UnChecked_png.png);}"
                          );
    checkBox11 = new  QCheckBox(checkWidget);
    checkBox11->setStyleSheet("QCheckBox::indicator{ width: 40px;  height: 40px;}QCheckBox::indicator:checked{image:url(:/picture/standardTest/Checked_png.png);}"
                          "QCheckBox::indicator:unchecked{image:url(:/picture/standardTest/UnChecked_png.png); } "
                          "QCheckBox::indicator:checked:disabled{image:url(:/picture/standardTest/UnChecked_png.png);}"
                          );
    checkBox12 = new  QCheckBox(checkWidget);
    checkBox12->setStyleSheet("QCheckBox::indicator{ width: 40px;  height: 40px;}QCheckBox::indicator:checked{image:url(:/picture/standardTest/Checked_png.png);}"
                          "QCheckBox::indicator:unchecked{image:url(:/picture/standardTest/UnChecked_png.png); } "
                          "QCheckBox::indicator:checked:disabled{image:url(:/picture/standardTest/UnChecked_png.png);}"
                          );
    checkLayout = new QVBoxLayout(checkWidget);
    checkLayout->setMargin(10);
    checkLayout->setSpacing(13);
    checkLayout->addSpacing(10);
    checkLayout->addWidget(checkBox1);
    checkLayout->addWidget(checkBox2);
    checkLayout->addWidget(checkBox3);
    checkLayout->addWidget(checkBox4);
    checkLayout->addWidget(checkBox5);
    checkLayout->addWidget(checkBox6);
    checkLayout->addWidget(checkBox7);
    checkLayout->addWidget(checkBox8);
    checkLayout->addWidget(checkBox9);
    checkLayout->addWidget(checkBox10);
    checkLayout->addWidget(checkBox11);
    checkLayout->addWidget(checkBox12);
    checkLayout->addSpacing(40);
    checkWidget->setLayout(checkLayout);
    checkWidget->setGeometry(90,160,70,782);

}


/**
 * @brief standardTest_TwoWidget::确定按钮信号槽
 */
void standardTest_TwoWidget::SureBtnSlot()
{
    //在这里要加入判断当前选择的样品数量是否达到最小值

    myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_QUESTION,tr("提示！"),tr("是否将标准品信息写入标准品数据库？"),this);
    if(messge->exec() == QDialog::Accepted){   //模式对话框
       emit SaveBtnPressSign();
    }
}

void standardTest_TwoWidget::saveBtnSlot()
{
    qDebug()<<"点击保存按钮";
    myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_QUESTION,tr("提示！"),tr("是否将标准品信息写入标准品数据库？"),this);
    if(messge->exec() == QDialog::Accepted){   //模式对话框
       emit SaveBtnPressSign();
    }

//    //1.1数据准备
//    QString STANDARD_NAME;
//    QString FILE_SHORT_NAME;
//    QStringList strlist;
//    QString CREATOR_ID ="无";
//    QString CREATE_TIME =QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
//    QString MODIFIER_ID ="无";
//    QString MODIFY_TIME="无" ;
//    //1.2判空

//    //1.3写入数据库
//    DataOpationStandardtest op;
//    //op.insertData_reagent_standard();



}




