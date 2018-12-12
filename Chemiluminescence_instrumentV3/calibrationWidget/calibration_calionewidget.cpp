#include "calibration_calionewidget.h"
#include <QHeaderView>
#include <QPrintDialog>
#include <QPrinter>
#include <QPainter>
#include <QTextDocument>
#include "QMessgeBox/mymessgebox.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <QDateTime>
#include "data/configfile.h"
#include "systemWidget/reagentNumber/databaseoperation.h"

//校准下一步的页面
calibration_caliOneWidget::calibration_caliOneWidget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(1671,1080);
    titleInit();
    BtnInit();
    checkWidgetInit();
    tableviewInit();
    displayWindowInit();
    connectInit();
    checkWidget->setGeometry(90,160,70,782);
    tableview->setGeometry(180,150,1432,782);
}

/**
 * @brief 标题头初始化
 */
void calibration_caliOneWidget::titleInit()
{
    titleIconLab = new QLabel(this);   //头图标
    titleIconLab->setPixmap(QPixmap(":/picture/standardPrograme/tile_icon.png"));

    titleTextLab = new QLabel(titleIconLab); //标题文字
    titleTextLab->setText(tr("校准品结果"));

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
 * @brief 按钮初始化
 */
void calibration_caliOneWidget::BtnInit()
{
    BtnWidget = new QWidget(this);
    disPlayBtn = new QPushButton;  /**< 显示图形*/
    disPlayBtn->setFixedSize(150,40);
    disPlayBtn->setStyleSheet("QPushButton{border-image: url(:/picture/calibrationWidget/display_png-up.png);}"
                              "QPushButton:hover{border-image: url(:/picture/calibrationWidget/display_png-up.png);}"
                              "QPushButton:pressed{border-image: url(:/picture/calibrationWidget/display_png-down.png);}");
    disPlayBtn->setFlat(true);

    printBtn = new QPushButton;   /**< 打印按钮*/
    printBtn->setFixedSize(150,40);
    printBtn->setStyleSheet("QPushButton{border-image: url(:/picture/calibrationWidget/printBtn-up.png);}"
                            "QPushButton:hover{border-image: url(:/picture/calibrationWidget/printBtn-up.png);}"
                            "QPushButton:pressed{border-image: url(:/picture/calibrationWidget/printBtn-down.png);}");
    printBtn->setFlat(true);




    btn_save = new QPushButton;   /**<保存 */
    btn_save->setFixedSize(150,40);
    btn_save->setStyleSheet("QPushButton{border-image: url(:/picture/calibrationWidget/save-up.png);}"
                            "QPushButton:hover{border-image: url(:/picture/calibrationWidget/save-up.png);}"
                            "QPushButton:pressed{border-image: url(:/picture/calibrationWidget/save-down.png);}");
    btn_save->setFlat(true);



    returnBtn = new QPushButton;    /**< 返回*/
    returnBtn->setFixedSize(150,40);
    returnBtn->setStyleSheet("QPushButton{border-image: url(:/picture/calibrationWidget/returnPng-up.png);}"
                             "QPushButton:hover{border-image: url(:/picture/calibrationWidget/returnPng-up.png);}"
                             "QPushButton:pressed{border-image: url(:/picture/calibrationWidget/returnPng-down.png);}");
    returnBtn->setFlat(true);

    BtnLayout = new QHBoxLayout(BtnWidget);
    BtnLayout->setMargin(50);
    BtnLayout->setSpacing(30);
    BtnLayout->addWidget(disPlayBtn);
    BtnLayout->addWidget(printBtn);
    BtnLayout->addWidget(btn_save);
    BtnLayout->addWidget(returnBtn);
    BtnLayout->addStretch();
    BtnWidget->setGeometry(0,0,1300,200);
}

/**
 * @brief 选择初始化
 */
void calibration_caliOneWidget::checkWidgetInit()
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
    checkLayout->setMargin(8);
    checkLayout->setSpacing(15);
    checkLayout->addSpacing(15);
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
    checkWidget->setLayout(checkLayout);

}

/**
 * @brief 视图初始化
 */
void calibration_caliOneWidget::tableviewInit()
{
    QFont font("tablefont",15);
    tableview = new QTableView(this);
    tableview->setFixedSize(1422,774);
    tableview->setFont(font);
    model = new QStandardItemModel(12,10);
    //让tableView中的文本居中
    for(int i = 0 ;i < 12 ;i++)
    {
        for(int j = 0;j < 10;j++)
        {
            model->setData(model->index(i,j,QModelIndex()),QVariant(tr("")));
            model->item(i,j)->setTextAlignment(Qt::AlignCenter);
        }
    }
    model->setHeaderData(0,Qt::Horizontal,tr("槽编号"));
    model->setHeaderData(1,Qt::Horizontal,tr("校准品条码"));
    model->setHeaderData(2,Qt::Horizontal,tr("项目"));
    model->setHeaderData(3,Qt::Horizontal,tr("标称浓度"));
    model->setHeaderData(4,Qt::Horizontal,tr("有效起始日期"));
    model->setHeaderData(5,Qt::Horizontal,tr("有效截止日期"));
    model->setHeaderData(6,Qt::Horizontal,tr("标准品A/B"));
    model->setHeaderData(7,Qt::Horizontal,tr("测量光子数"));
    model->setHeaderData(8,Qt::Horizontal,tr("测量浓度"));
    model->setHeaderData(9,Qt::Horizontal,tr("CV值"));
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
//    //------测试数据------
//    model->setData(model->index(0,2,QModelIndex()),QVariant(tr("测试项目1")));
//    model->setData(model->index(1,2,QModelIndex()),QVariant(tr("测试项目2")));
//    model->setData(model->index(2,2,QModelIndex()),QVariant(tr("测试项目3")));
//    model->setData(model->index(3,2,QModelIndex()),QVariant(tr("测试项目4")));
//    model->setData(model->index(4,2,QModelIndex()),QVariant(tr("测试项目5")));
//    model->setData(model->index(5,2,QModelIndex()),QVariant(tr("测试项目6")));
//    model->setData(model->index(6,2,QModelIndex()),QVariant(tr("测试项目7")));
//    model->setData(model->index(7,2,QModelIndex()),QVariant(tr("测试项目8")));
//    model->setData(model->index(8,2,QModelIndex()),QVariant(tr("测试项目9")));
//    model->setData(model->index(9,2,QModelIndex()),QVariant(tr("测试项目10")));
//    model->setData(model->index(10,2,QModelIndex()),QVariant(tr("测试项目11")));
//    model->setData(model->index(11,2,QModelIndex()),QVariant(tr("测试项目12")));

//    model->setData(model->index(0,3,QModelIndex()),QVariant(tr("0.0001")));
//    model->setData(model->index(1,3,QModelIndex()),QVariant(tr("0.0002")));
//    model->setData(model->index(2,3,QModelIndex()),QVariant(tr("0.0003")));
//    model->setData(model->index(3,3,QModelIndex()),QVariant(tr("0.0004")));
//    model->setData(model->index(4,3,QModelIndex()),QVariant(tr("0.0005")));
//    model->setData(model->index(5,3,QModelIndex()),QVariant(tr("0.0006")));
//    model->setData(model->index(6,3,QModelIndex()),QVariant(tr("0.0007")));
//    model->setData(model->index(7,3,QModelIndex()),QVariant(tr("0.0008")));
//    model->setData(model->index(8,3,QModelIndex()),QVariant(tr("0.0009")));
//    model->setData(model->index(9,3,QModelIndex()),QVariant(tr("0.0010")));
//    model->setData(model->index(10,3,QModelIndex()),QVariant(tr("0.0011")));
//    model->setData(model->index(11,3,QModelIndex()),QVariant(tr("0.0012")));

//    model->setData(model->index(0,8,QModelIndex()),QVariant(tr("2000")));
//    model->setData(model->index(1,8,QModelIndex()),QVariant(tr("9.002")));
//    model->setData(model->index(2,8,QModelIndex()),QVariant(tr("9.003")));
//    model->setData(model->index(3,8,QModelIndex()),QVariant(tr("9.004")));
//    model->setData(model->index(4,8,QModelIndex()),QVariant(tr("9.005")));
//    model->setData(model->index(5,8,QModelIndex()),QVariant(tr("9.006")));
//    model->setData(model->index(6,8,QModelIndex()),QVariant(tr("9.007")));
//    model->setData(model->index(7,8,QModelIndex()),QVariant(tr("9.008")));
//    model->setData(model->index(8,8,QModelIndex()),QVariant(tr("9.009")));
//    model->setData(model->index(9,8,QModelIndex()),QVariant(tr("9.010")));
//    model->setData(model->index(10,8,QModelIndex()),QVariant(tr("9.011")));
//    model->setData(model->index(11,8,QModelIndex()),QVariant(tr("9.012")));

//    //填入模拟数据
//    model->setData(model->index(0,1,QModelIndex()),QVariant(tr("2018030010001")));
//    model->setData(model->index(0,4,QModelIndex()),QVariant(tr("2018-02-01 14:15:16")));
//    model->setData(model->index(0,5,QModelIndex()),QVariant(tr("2019-03-01 14:15:16")));
//    model->setData(model->index(0,6,QModelIndex()),QVariant(tr("A")));
//    model->setData(model->index(0,7,QModelIndex()),QVariant(tr("1113562")));
//    model->setData(model->index(0,9,QModelIndex()),QVariant(tr("0.9")));
    //------------------
    tableview->setModel(model);
    tableview->verticalHeader()->hide();
    //设置其选择行为，并不可以编辑
    tableview->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableview->setSelectionMode ( QAbstractItemView::SingleSelection);
    tableview->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置列不能拖动
    tableview->horizontalHeader()->setDisabled(true);
    tableview->horizontalHeader()->setHighlightSections(true);
    //设置行不能拖动
    tableview->verticalHeader()->setDisabled(true);
    tableview->setStyleSheet("gridline-color: rgb(0, 139, 139);selection-background-color:lightblue;");
    tableview->setColumnWidth(0,120);
    tableview->setColumnWidth(1,230);
    tableview->setColumnWidth(2,130);
    tableview->setColumnWidth(3,120);
    tableview->setColumnWidth(4,150);
    tableview->setColumnWidth(5,150);
    tableview->setColumnWidth(6,150);
    tableview->setColumnWidth(7,150);
    tableview->setColumnWidth(8,110);
    tableview->setColumnWidth(9,110);
    tableview->verticalHeader()->setDefaultSectionSize(62);

}

/**
 * @brief 曲线显示初始化
 */
void calibration_caliOneWidget::displayWindowInit()
{

}

/**
 * @brief 信号绑定函数初始化
 */
void calibration_caliOneWidget::connectInit()
{
    connect(disPlayBtn,SIGNAL(clicked()),this,SLOT(disPlayBtnSlot()));
    connect(printBtn,SIGNAL(clicked()),this,SLOT(printBtnSlot()));
    connect(btn_save,SIGNAL(clicked()),this,SLOT(saveBtnSlot()));
    connect(returnBtn,SIGNAL(clicked()),this,SLOT(returnBtnSlot()));
}



/**
 * @brief 画曲线
 */
void calibration_caliOneWidget::disPlayBtnSlot()
{
    QStringList list_name;      //校准品条码列表
    QStringList list_concentration;     //测量浓度列表
    QStringList list_photon;        //发光值列表

    if(checkBox1->checkState() == Qt::Checked)
    {
        QString name = model->data(model->index(0,1,QModelIndex())).toString();
        list_name.append(name);

        QString concentration = model->data(model->index(0,8,QModelIndex())).toString();
        list_concentration.append(concentration);
        QString photon = model->data(model->index(0,7,QModelIndex())).toString();
        list_photon.append(photon);

    }
    if(checkBox2->checkState() == Qt::Checked)
    {
        QString name = model->data(model->index(1,1,QModelIndex())).toString();
        list_name.append(name);
        QString concentration = model->data(model->index(1,8,QModelIndex())).toString();
        list_concentration.append(concentration);
        QString photon = model->data(model->index(1,7,QModelIndex())).toString();
        list_photon.append(photon);
    }
    if(checkBox3->checkState() == Qt::Checked)
    {
        QString name = model->data(model->index(2,1,QModelIndex())).toString();
        list_name.append(name);
        QString concentration = model->data(model->index(2,8,QModelIndex())).toString();
        list_concentration.append(concentration);
        QString photon = model->data(model->index(2,7,QModelIndex())).toString();
        list_photon.append(photon);
    }
    if(checkBox4->checkState() == Qt::Checked)
    {
        QString name = model->data(model->index(3,1,QModelIndex())).toString();
        list_name.append(name);
        QString concentration = model->data(model->index(3,8,QModelIndex())).toString();
        list_concentration.append(concentration);
        QString photon = model->data(model->index(3,7,QModelIndex())).toString();
        list_photon.append(photon);
    }
    if(checkBox5->checkState() == Qt::Checked)
    {
        QString name = model->data(model->index(4,1,QModelIndex())).toString();
        list_name.append(name);
        QString concentration = model->data(model->index(4,8,QModelIndex())).toString();
        list_concentration.append(concentration);
        QString photon = model->data(model->index(4,7,QModelIndex())).toString();
        list_photon.append(photon);
    }
    if(checkBox6->checkState() == Qt::Checked)
    {
        QString name = model->data(model->index(5,1,QModelIndex())).toString();
        list_name.append(name);
        QString concentration = model->data(model->index(5,8,QModelIndex())).toString();
        list_concentration.append(concentration);
        QString photon = model->data(model->index(5,7,QModelIndex())).toString();
        list_photon.append(photon);
    }
    if(checkBox7->checkState() == Qt::Checked)
    {
        QString name = model->data(model->index(6,1,QModelIndex())).toString();
        list_name.append(name);
        QString concentration = model->data(model->index(6,8,QModelIndex())).toString();
        list_concentration.append(concentration);
        QString photon = model->data(model->index(6,7,QModelIndex())).toString();
        list_photon.append(photon);
    }
    if(checkBox8->checkState() == Qt::Checked)
    {
        QString name = model->data(model->index(7,1,QModelIndex())).toString();
        list_name.append(name);
        QString concentration = model->data(model->index(7,8,QModelIndex())).toString();
        list_concentration.append(concentration);
        QString photon = model->data(model->index(7,7,QModelIndex())).toString();
        list_photon.append(photon);
    }
    if(checkBox9->checkState() == Qt::Checked)
    {
        QString name = model->data(model->index(8,1,QModelIndex())).toString();
        list_name.append(name);
        QString concentration = model->data(model->index(8,8,QModelIndex())).toString();
        list_concentration.append(concentration);
        QString photon = model->data(model->index(8,7,QModelIndex())).toString();
        list_photon.append(photon);
    }
    if(checkBox10->checkState() == Qt::Checked)
    {
        QString name = model->data(model->index(9,1,QModelIndex())).toString();
        list_name.append(name);
        QString concentration = model->data(model->index(9,8,QModelIndex())).toString();
        list_concentration.append(concentration);
        QString photon = model->data(model->index(9,7,QModelIndex())).toString();
        list_photon.append(photon);
    }
    if(checkBox11->checkState() == Qt::Checked)
    {
        QString name = model->data(model->index(10,1,QModelIndex())).toString();
        list_name.append(name);
        QString concentration = model->data(model->index(10,8,QModelIndex())).toString();
        list_concentration.append(concentration);
        QString photon = model->data(model->index(10,7,QModelIndex())).toString();
        list_photon.append(photon);
    }
    if(checkBox12->checkState() == Qt::Checked)
    {
        QString name = model->data(model->index(11,1,QModelIndex())).toString();
        list_name.append(name);
        QString concentration = model->data(model->index(11,8,QModelIndex())).toString();
        list_concentration.append(concentration);
        QString photon = model->data(model->index(11,7,QModelIndex())).toString();
        list_photon.append(photon);
    }

    int len = list_name.length();
    if(len == 0)
    {
       myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_INFORMATION,tr("提示"),tr("请先勾选检测项目！"),this);
       messge->exec();
       return;
    }
    for(int i=1;i<len;i++)
    {
        if(list_name.at(i)!=list_name.at(0))
        {

            myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_INFORMATION,tr("提示"),tr("所选项目名称不一致！"),this);
            messge->exec();
            return;
        }
    }

    displayCruve = new DisplayCruve(this);
    displayCruve->setFixedSize(960,640);
    displayCruve->show();

    int len_c = list_concentration.length();
    double *x = new double[len_c];

    double *y = new double[len_c];

    for(int i = 0;i<len_c;i++)
    {
        QString str_c = list_concentration.at(i);
        QString str_p = list_photon.at(i);

        double temp_c = str_c.toDouble();
        double temp_p = str_p.toDouble();

        x[i] = temp_c;
        y[i] = temp_p;
    }

    QString name = list_name.at(0);
    /**************测试数据******************/

//    double *x = new double[2];
//    x[0] = 500;
//    x[1] = 2000;
//    double *y = new double[2];
//    y[0] = 500000;
//    y[1] = 1110000;
//    QString name = "1111";
    /*************************************/

    //根据所传入的参数绘画曲线
    displayCruve->paint_cruve(name,x,y,len_c);

}
/**
 * @brief 打印和返回按钮槽
 */
void calibration_caliOneWidget::printBtnSlot()
{
    //1、创建打印机---------------------------------------------------------------
    QPrinter printer;
    //2、创建打印对话框
    QPrintDialog printDlg(&printer, this);
    // printer.setOrientation(QPrinter::Landscape);

    //3、判断是否点击了“打印”按钮
    if (printDlg.exec()) //根据打印对话框的返回值
    {
        QPainter painter(&printer);         //创建画图（继承打印机）

        //------------
        int border_up =40;
        int border_left =50;
        //======================上下相邻参考，左右边界参考=====================================
        int BigTitle_leftX=border_left+60;
        int BigTitle_leftY=border_up+20;
        QString tem_TableName="铂纳科技化学发光上位机测试表格";
        //标题下方内容------科室 采样日期 操作人员 备注------
        int Info_X = border_left+ 30;
        int Info_Y = BigTitle_leftY + 60;
        int distance_X=135;


        ConfigFile op;
        QString Department=op.getCurrentUser_department();

        QString Operator=op.getCurrentUser_Name();
        QString Date=QDateTime::currentDateTime().toString("yyyy-MM-dd");//"2018-12-13";
        QString Remarks="无";

        //线框
        int Line_X =border_left+30;
        int line1_Y =Info_Y+30;
        int line2_Y =Info_Y+60;
        int line_length=640;

        int column_width_add[5]    ={0,0,0,0,0};
        int column_distance=140;
        char column[5][30]={"序号","项目名称","标称浓度","测量浓度","单位"};

        //----------------------------------------------
        int group_number=0;
        int group_distanceY = 60;

        int Text_X=border_left+30;
        int Text_Y=line2_Y+0;





        //大标题文字
        //QFont font("Microsoft YaHei", 25, 75);
        QFont font("宋体", 25);
        painter.setFont(font);
        painter.drawText(QRect(border_left+BigTitle_leftX,BigTitle_leftY,tem_TableName.length()*40,100),tem_TableName,QTextOption());

        //信息文字
        QFont font1("楷体",15,30);
        int word_Height=20;//字高
        painter.setFont(font1);

        //科室：骨科         操作人员：习近平         采样日期：2014-12-14    备注：
        painter.drawText(QRect(Info_X+distance_X*0,Info_Y,((strlen("科室：")+Department.length())*20),100),"科室："+Department,QTextOption());
        painter.drawText(QRect(Info_X+distance_X*1,Info_Y,((strlen("操作人员：")+Operator.length())*20),100),"操作人员："+Operator,QTextOption());
        painter.drawText(QRect(Info_X+distance_X*2+60,Info_Y,((strlen("采样日期：")+Date.length())*20),100),"采样日期："+Date,QTextOption());
        painter.drawText(QRect(Info_X+distance_X*3+160,Info_Y,((strlen("备注：")+Remarks.length())*20),100),"备注:"+Remarks,QTextOption());

        //线
        painter.drawLine(Line_X,line1_Y,Line_X+line_length,line1_Y);
        painter.drawLine(Line_X,line2_Y,Line_X+line_length,line2_Y);

        //栏目名称
        for(int i =0;i<5;i++)
        {
            painter.drawText(QRect(Line_X+column_distance*i+column_width_add[i],line1_Y+5,QString(column[i]).length()*20,100),column[i],QTextOption());
        }

        //#########################  写入数据 第一组 ##########################//
        QPen pen;//(Qt::black, 2, Qt::DotLine);
        QVector<qreal> dashes;
        qreal space = 3;
        dashes << 5 << space << 5 <<space;
        pen.setDashPattern(dashes);
        pen.setWidth(1);
        painter.setPen(pen);


       if(checkBox1->checkState()==Qt::Checked)
        {
            group_number++;
            painter.drawLine(Line_X,Text_Y+(group_number)*group_distanceY,Line_X+line_length,Text_Y+(group_number)*group_distanceY);
            //组别
            painter.drawText(QRect(Text_X+column_distance*0+column_width_add[0],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100)," "+QString::number(group_number),QTextOption());
            //项目名称
            painter.drawText(QRect(Text_X+column_distance*1+column_width_add[1],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),model->data(model->index(0,1,QModelIndex())).toString(),QTextOption());
            //标称浓度
            painter.drawText(QRect(Text_X+column_distance*2+column_width_add[2],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),model->data(model->index(0,3,QModelIndex())).toString(),QTextOption());
            //测量浓度
            painter.drawText(QRect(Text_X+column_distance*3+column_width_add[3],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),model->data(model->index(0,8,QModelIndex())).toString(),QTextOption());
            //单位
            painter.drawText(QRect(Text_X+column_distance*4+column_width_add[4],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),"mol/mL",QTextOption());
        }
       if(checkBox2->checkState()==Qt::Checked)
        {
            group_number++;
            painter.drawLine(Line_X,Text_Y+(group_number)*group_distanceY,Line_X+line_length,Text_Y+(group_number)*group_distanceY);
            //组别
            painter.drawText(QRect(Text_X+column_distance*0+column_width_add[0],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100)," "+QString::number(group_number),QTextOption());
            //项目名称
            painter.drawText(QRect(Text_X+column_distance*1+column_width_add[1],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),model->data(model->index(1,1,QModelIndex())).toString(),QTextOption());
            //标称浓度
            painter.drawText(QRect(Text_X+column_distance*2+column_width_add[2],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),model->data(model->index(1,3,QModelIndex())).toString(),QTextOption());
            //测量浓度
            painter.drawText(QRect(Text_X+column_distance*3+column_width_add[3],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),model->data(model->index(1,8,QModelIndex())).toString(),QTextOption());
            //单位
            painter.drawText(QRect(Text_X+column_distance*4+column_width_add[4],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),"mol/mL",QTextOption());
        }

       if(checkBox3->checkState()==Qt::Checked)
        {
            group_number++;
            painter.drawLine(Line_X,Text_Y+(group_number)*group_distanceY,Line_X+line_length,Text_Y+(group_number)*group_distanceY);
            //组别
            painter.drawText(QRect(Text_X+column_distance*0+column_width_add[0],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100)," "+QString::number(group_number),QTextOption());
            //项目名称
            painter.drawText(QRect(Text_X+column_distance*1+column_width_add[1],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),model->data(model->index(2,1,QModelIndex())).toString(),QTextOption());
            //标称浓度
            painter.drawText(QRect(Text_X+column_distance*2+column_width_add[2],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),model->data(model->index(2,3,QModelIndex())).toString(),QTextOption());
            //测量浓度
            painter.drawText(QRect(Text_X+column_distance*3+column_width_add[3],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),model->data(model->index(2,8,QModelIndex())).toString(),QTextOption());
            //单位
            painter.drawText(QRect(Text_X+column_distance*4+column_width_add[4],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),"mol/mL",QTextOption());
        }
       if(checkBox4->checkState()==Qt::Checked)
        {
            group_number++;
            painter.drawLine(Line_X,Text_Y+(group_number)*group_distanceY,Line_X+line_length,Text_Y+(group_number)*group_distanceY);
            //组别
            painter.drawText(QRect(Text_X+column_distance*0+column_width_add[0],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100)," "+QString::number(group_number),QTextOption());
            //项目名称
            painter.drawText(QRect(Text_X+column_distance*1+column_width_add[1],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),model->data(model->index(3,1,QModelIndex())).toString(),QTextOption());
            //标称浓度
            painter.drawText(QRect(Text_X+column_distance*2+column_width_add[2],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),model->data(model->index(3,3,QModelIndex())).toString(),QTextOption());
            //测量浓度
            painter.drawText(QRect(Text_X+column_distance*3+column_width_add[3],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),model->data(model->index(3,8,QModelIndex())).toString(),QTextOption());
            //单位
            painter.drawText(QRect(Text_X+column_distance*4+column_width_add[4],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),"mol/mL",QTextOption());
        }
       if(checkBox5->checkState()==Qt::Checked)
        {
            group_number++;
            painter.drawLine(Line_X,Text_Y+(group_number)*group_distanceY,Line_X+line_length,Text_Y+(group_number)*group_distanceY);
            //组别
            painter.drawText(QRect(Text_X+column_distance*0+column_width_add[0],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100)," "+QString::number(group_number),QTextOption());
            //项目名称
            painter.drawText(QRect(Text_X+column_distance*1+column_width_add[1],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),model->data(model->index(4,1,QModelIndex())).toString(),QTextOption());
            //标称浓度
            painter.drawText(QRect(Text_X+column_distance*2+column_width_add[2],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),model->data(model->index(4,3,QModelIndex())).toString(),QTextOption());
            //测量浓度
            painter.drawText(QRect(Text_X+column_distance*3+column_width_add[3],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),model->data(model->index(4,8,QModelIndex())).toString(),QTextOption());
            //单位
            painter.drawText(QRect(Text_X+column_distance*4+column_width_add[4],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),"mol/mL",QTextOption());
        }
       if(checkBox6->checkState()==Qt::Checked)
        {
            group_number++;
            painter.drawLine(Line_X,Text_Y+(group_number)*group_distanceY,Line_X+line_length,Text_Y+(group_number)*group_distanceY);
            //组别
            painter.drawText(QRect(Text_X+column_distance*0+column_width_add[0],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100)," "+QString::number(group_number),QTextOption());
            //项目名称
            painter.drawText(QRect(Text_X+column_distance*1+column_width_add[1],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),model->data(model->index(5,1,QModelIndex())).toString(),QTextOption());
            //标称浓度
            painter.drawText(QRect(Text_X+column_distance*2+column_width_add[2],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),model->data(model->index(5,3,QModelIndex())).toString(),QTextOption());
            //测量浓度
            painter.drawText(QRect(Text_X+column_distance*3+column_width_add[3],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),model->data(model->index(5,8,QModelIndex())).toString(),QTextOption());
            //单位
            painter.drawText(QRect(Text_X+column_distance*4+column_width_add[4],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),"mol/mL",QTextOption());
        }
       if(checkBox7->checkState()==Qt::Checked)
        {
            group_number++;
            painter.drawLine(Line_X,Text_Y+(group_number)*group_distanceY,Line_X+line_length,Text_Y+(group_number)*group_distanceY);
            //组别
            painter.drawText(QRect(Text_X+column_distance*0+column_width_add[0],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100)," "+QString::number(group_number),QTextOption());
            //项目名称
            painter.drawText(QRect(Text_X+column_distance*1+column_width_add[1],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),model->data(model->index(6,1,QModelIndex())).toString(),QTextOption());
            //标称浓度
            painter.drawText(QRect(Text_X+column_distance*2+column_width_add[2],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),model->data(model->index(6,3,QModelIndex())).toString(),QTextOption());
            //测量浓度
            painter.drawText(QRect(Text_X+column_distance*3+column_width_add[3],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),model->data(model->index(6,8,QModelIndex())).toString(),QTextOption());
            //单位
            painter.drawText(QRect(Text_X+column_distance*4+column_width_add[4],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),"mol/mL",QTextOption());
        }
       if(checkBox8->checkState()==Qt::Checked)
        {
            group_number++;
            painter.drawLine(Line_X,Text_Y+(group_number)*group_distanceY,Line_X+line_length,Text_Y+(group_number)*group_distanceY);
            //组别
            painter.drawText(QRect(Text_X+column_distance*0+column_width_add[0],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100)," "+QString::number(group_number),QTextOption());
            //项目名称
            painter.drawText(QRect(Text_X+column_distance*1+column_width_add[1],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),model->data(model->index(7,1,QModelIndex())).toString(),QTextOption());
            //标称浓度
            painter.drawText(QRect(Text_X+column_distance*2+column_width_add[2],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),model->data(model->index(7,3,QModelIndex())).toString(),QTextOption());
            //测量浓度
            painter.drawText(QRect(Text_X+column_distance*3+column_width_add[3],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),model->data(model->index(7,8,QModelIndex())).toString(),QTextOption());
            //单位
            painter.drawText(QRect(Text_X+column_distance*4+column_width_add[4],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),"mol/mL",QTextOption());
        }
       if(checkBox9->checkState()==Qt::Checked)
        {
            group_number++;
            painter.drawLine(Line_X,Text_Y+(group_number)*group_distanceY,Line_X+line_length,Text_Y+(group_number)*group_distanceY);
            //组别
            painter.drawText(QRect(Text_X+column_distance*0+column_width_add[0],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100)," "+QString::number(group_number),QTextOption());
            //项目名称
            painter.drawText(QRect(Text_X+column_distance*1+column_width_add[1],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),model->data(model->index(8,1,QModelIndex())).toString(),QTextOption());
            //标称浓度
            painter.drawText(QRect(Text_X+column_distance*2+column_width_add[2],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),model->data(model->index(8,3,QModelIndex())).toString(),QTextOption());
            //测量浓度
            painter.drawText(QRect(Text_X+column_distance*3+column_width_add[3],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),model->data(model->index(8,8,QModelIndex())).toString(),QTextOption());
            //单位
            painter.drawText(QRect(Text_X+column_distance*4+column_width_add[4],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),"mol/mL",QTextOption());
        }
       if(checkBox10->checkState()==Qt::Checked)
        {
            group_number++;
            painter.drawLine(Line_X,Text_Y+(group_number)*group_distanceY,Line_X+line_length,Text_Y+(group_number)*group_distanceY);
            //组别
            painter.drawText(QRect(Text_X+column_distance*0+column_width_add[0],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100)," "+QString::number(group_number),QTextOption());
            //项目名称
            painter.drawText(QRect(Text_X+column_distance*1+column_width_add[1],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),model->data(model->index(9,1,QModelIndex())).toString(),QTextOption());
            //标称浓度
            painter.drawText(QRect(Text_X+column_distance*2+column_width_add[2],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),model->data(model->index(9,3,QModelIndex())).toString(),QTextOption());
            //测量浓度
            painter.drawText(QRect(Text_X+column_distance*3+column_width_add[3],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),model->data(model->index(9,8,QModelIndex())).toString(),QTextOption());
            //单位
            painter.drawText(QRect(Text_X+column_distance*4+column_width_add[4],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),"mol/mL",QTextOption());
        }
       if(checkBox11->checkState()==Qt::Checked)
        {
            group_number++;
            painter.drawLine(Line_X,Text_Y+(group_number)*group_distanceY,Line_X+line_length,Text_Y+(group_number)*group_distanceY);
            //组别
            painter.drawText(QRect(Text_X+column_distance*0+column_width_add[0],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100)," "+QString::number(group_number),QTextOption());
            //项目名称
            painter.drawText(QRect(Text_X+column_distance*1+column_width_add[1],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),model->data(model->index(10,1,QModelIndex())).toString(),QTextOption());
            //标称浓度
            painter.drawText(QRect(Text_X+column_distance*2+column_width_add[2],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),model->data(model->index(10,3,QModelIndex())).toString(),QTextOption());
            //测量浓度
            painter.drawText(QRect(Text_X+column_distance*3+column_width_add[3],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),model->data(model->index(10,8,QModelIndex())).toString(),QTextOption());
            //单位
            painter.drawText(QRect(Text_X+column_distance*4+column_width_add[4],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),"mol/mL",QTextOption());
        }
       if(checkBox12->checkState()==Qt::Checked)
        {
            group_number++;
            painter.drawLine(Line_X,Text_Y+(group_number)*group_distanceY,Line_X+line_length,Text_Y+(group_number)*group_distanceY);
            //组别
            painter.drawText(QRect(Text_X+column_distance*0+column_width_add[0],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100)," "+QString::number(group_number),QTextOption());
            //项目名称
            painter.drawText(QRect(Text_X+column_distance*1+column_width_add[1],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),model->data(model->index(11,1,QModelIndex())).toString(),QTextOption());
            //标称浓度
            painter.drawText(QRect(Text_X+column_distance*2+column_width_add[2],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),model->data(model->index(11,3,QModelIndex())).toString(),QTextOption());
            //测量浓度
            painter.drawText(QRect(Text_X+column_distance*3+column_width_add[3],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),model->data(model->index(11,8,QModelIndex())).toString(),QTextOption());
            //单位
            painter.drawText(QRect(Text_X+column_distance*4+column_width_add[4],Text_Y+group_number*group_distanceY-group_distanceY/2-word_Height/2,200,100),"mol/mL",QTextOption());
        }

    }
}


bool calibration_caliOneWidget::insert_into_table_calibration_info(const QString &CATEGORY, const QString &PROJECT_NAME, const QString &REAGENT_TYPE, const QString &BAR_CODE, double STANDARD_CONCENTRATION, const QString &START_DATE, const QString &END_DATE, char STANDARD_FLAG, int PHOTON_VALUE, double CONCENTRATION, double VARIANCE_COEFFICENT, const QString &CREATOR_ID, const QString &CREATE_TIME, const QString &MODIFIER_ID, const QString &MODIFY_TIME, char DEL_FLAG)
{
        QSqlQuery query;

        query.exec("insert into calibration_info values (?,?,?,?,?,?,?,?,?,?,"
                                                            "?,?,?,?,?,?,?);");                                                        //ID 0
        query.bindValue(1,CATEGORY);                    //CATEGORY 1
        query.bindValue(2,PROJECT_NAME);                //PROJECT_NAME 2
        query.bindValue(3,REAGENT_TYPE);                //REAGENT_TYPE
        query.bindValue(4,BAR_CODE);                    //BAR_CODE
        query.bindValue(5,STANDARD_CONCENTRATION);      //STANDARD_CONCENTRATION
        query.bindValue(6,START_DATE);                  //START_DATE
        query.bindValue(7,END_DATE);                    //END_DATE
        query.bindValue(8,STANDARD_FLAG);               //STANDARD_FLAG
        query.bindValue(9,PHOTON_VALUE);                //PHOTON_VALUE
        query.bindValue(10,CONCENTRATION);              //CONCENTRATION
        query.bindValue(11,VARIANCE_COEFFICENT);        //VARIANCE_COEFFICENT
        query.bindValue(12,CREATOR_ID);                 //CREATOR_ID
        query.bindValue(13,CREATE_TIME);                //CREATE_TIME
        query.bindValue(14,MODIFIER_ID);                //MODIFIER_ID
        query.bindValue(15,MODIFY_TIME);                //MODIFY_TIME
        query.bindValue(16,DEL_FLAG);                   //DEL_FLAG

        bool ret = query.exec();
       //------------------------------------------------------------------
        if(!ret)qDebug()<<"校准品---新增---sql语句失败！"<<query.lastError();
        else qDebug()<<"校准品---新增---sql执行成功";
        return ret;

}
//不使用
bool calibration_caliOneWidget::update_table_calibration_info(
        const QString &BAR_CODE,
        double STANDARD_CONCENTRATION,
        const QString &START_DATE,
        const QString &END_DATE,
        char STANDARD_FLAG,
        int PHOTON_VALUE,
        double CONCENTRATION,
        double VARIANCE_COEFFICENT,
        const QString &MODIFIER_ID,
        const QString &MODIFY_TIME,
        char DEL_FLAG)
{

    QSqlQuery query;

    query.prepare("update calibration_info set "
                  "STANDARD_CONCENTRATION   = ?,"
                  "START_DATE               = ?,"
                  "END_DATE                 = ?,"
                  "STANDARD_FLAG            = ?,"
                  "PHOTON_VALUE             = ?,"
                  "CONCENTRATION            = ?,"
                  "VARIANCE_COEFFICENT      = ?,"
                  "MODIFIER_ID              = ?,"
                  "MODIFY_TIME              = ?,"
                  "DEL_FLAG                 = ? "
                  "where BAR_CODE           = ?;");
    query.bindValue(0,STANDARD_CONCENTRATION);
    query.bindValue(1,START_DATE);
    query.bindValue(2,END_DATE);
    query.bindValue(3,STANDARD_FLAG);
    query.bindValue(4,PHOTON_VALUE);
    query.bindValue(5,CONCENTRATION);
    query.bindValue(6,VARIANCE_COEFFICENT);
    query.bindValue(7,MODIFIER_ID);
    query.bindValue(8,MODIFY_TIME);
    query.bindValue(9,DEL_FLAG);
    query.bindValue(10,BAR_CODE);

    bool ret = query.exec();
   //------------------------------------------------------------------
    if(!ret)qDebug()<<"校验表---更改---sql语句失败！"<<query.lastError();
    else qDebug()<<"校验表---更改---sql执行成功";
    return ret;
}
//不使用
bool calibration_caliOneWidget::isExist_calibration_info(const QString &BAR_CODE)
{
    QSqlQuery query;
    query.exec("select BAR_CODE from calibration_info where BAR_CODE = ?;");
    query.bindValue(0,BAR_CODE,QSql::Out);
    query.exec();
    while(query.next()){
        qDebug() << "当前项目信息已经存在"<<BAR_CODE;
        return true;
    }
     qDebug() << "当前项目信息不存在"<<BAR_CODE;
     return false;
    return true;
}


void calibration_caliOneWidget::saveBtnSlot()
{
    qDebug()<<"点击保存按钮";
    QString  CATEGORY="品类";
    QString  PROJECT_NAME="项目名称";
    QString  REAGENT_TYPE="TEST";
    QString  BAR_CODE="123456789";
    double  STANDARD_CONCENTRATION;
    QString  START_DATE;
    QString  END_DATE;
    char    STANDARD_FLAG;
    int     PHOTON_VALUE;
    double CONCENTRATION;
    double VARIANCE_COEFFICENT;
    ConfigFile op;
    QString  CREATOR_ID =op.getCurrentUser_Name();
    QString  CREATE_TIME=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString  MODIFIER_ID="无";
    QString  MODIFY_TIME="无";
    char DEL_FLAG=0;
    DatabaseOperation opp;
    //开始保存
    for(int i=0;i<model->rowCount();i++)
    {
        if(i==0 && checkBox1->checkState() == Qt::Unchecked)i++;
        if(i==1 && checkBox2->checkState() == Qt::Unchecked)i++;
        if(i==2 && checkBox3->checkState() == Qt::Unchecked)i++;
        if(i==3 && checkBox4->checkState() == Qt::Unchecked)i++;
        if(i==4 && checkBox5->checkState() == Qt::Unchecked)i++;
        if(i==5 && checkBox6->checkState() == Qt::Unchecked)i++;
        if(i==6 && checkBox7->checkState() == Qt::Unchecked)i++;
        if(i==7 && checkBox8->checkState() == Qt::Unchecked)i++;
        if(i==8 && checkBox9->checkState() == Qt::Unchecked)i++;
        if(i==9 && checkBox10->checkState() == Qt::Unchecked)i++;
        if(i==10 && checkBox11->checkState() == Qt::Unchecked)i++;
        if(i==11 && checkBox12->checkState() == Qt::Unchecked)break;

        BAR_CODE                =   model->data(model->index(i,1)).toString();
        //获取其他信息

        opp.getReagentInfoByCode(CATEGORY,PROJECT_NAME,REAGENT_TYPE,BAR_CODE);

        //REAGENT_TYPE            =   model->data(model->index(i,2)).toString();//使用条码获取的
        STANDARD_CONCENTRATION  =   model->data(model->index(i,3)).toDouble();
        START_DATE              =   model->data(model->index(i,4)).toString();
        END_DATE                =   model->data(model->index(i,5)).toString();
        STANDARD_FLAG           =   model->data(model->index(i,6)).toInt();
        PHOTON_VALUE            =   model->data(model->index(i,7)).toInt();
        CONCENTRATION           =   model->data(model->index(i,8)).toDouble();
        VARIANCE_COEFFICENT     =   model->data(model->index(i,9)).toDouble();
        qDebug()<<"----->保存船仓"<<i+1;
        insert_into_table_calibration_info(CATEGORY,PROJECT_NAME,REAGENT_TYPE,BAR_CODE,
                                              STANDARD_CONCENTRATION,START_DATE,END_DATE,
                                              STANDARD_FLAG,PHOTON_VALUE,CONCENTRATION,
                                              VARIANCE_COEFFICENT,CREATOR_ID,CREATE_TIME,
                                              MODIFIER_ID,MODIFY_TIME,DEL_FLAG);

    }

}

void calibration_caliOneWidget::returnBtnSlot()
{
    myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_QUESTION,tr("提示"),tr("是否退出当前界面,返回主界面！"),this);
    if(messge->exec() == QDialog::Accepted){   //模式对话框
        emit returnBtnSignal(0);
    }
}
