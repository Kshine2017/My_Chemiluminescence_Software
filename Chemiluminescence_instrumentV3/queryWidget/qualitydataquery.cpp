#include "qualitydataquery.h"
#include <QDebug>
#include <QHeaderView>
#include "QMessgeBox/mymessgebox.h"

#define CHOOSE_QUALITY 1
#define CHOOSE_CALIBRATION 2
#define CHOOSE_STANDARD 3

QualityDataQuery::QualityDataQuery(QWidget *parent) : QWidget(parent)
{
    init();
    connect(btn_query,SIGNAL(clicked()),this,SLOT(query()));
    connect(radioButton_quality,SIGNAL(clicked()),btn_query,SIGNAL(clicked()));
    connect(radioButton_calibration,SIGNAL(clicked()),btn_query,SIGNAL(clicked()));
    connect(radioButton_standard,SIGNAL(clicked()),btn_query,SIGNAL(clicked()));

    connect(tableView,SIGNAL(clicked(QModelIndex)),this,SLOT(slot_click_tableView(QModelIndex)));
    connect(btn_delete,SIGNAL(clicked()),this,SLOT(slot_btn_delete()));

}

void QualityDataQuery::init()
{
    chooseFlag_delete = -1; //删除标志复位
    widget = new QWidget(this);
    this->setFont(QFont("宋体",14));

    QPalette palette;
    QPixmap pixmap(":/picture/query/qualityDataQuery/quality_data_bg.png");
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    widget->setPalette(palette);    //放置背景图片

    widget->setFixedSize(1660,1100);
    widget->setAutoFillBackground(true);

    layout_left = new QVBoxLayout(widget);       //左边布局

    layout_queryItem = new QHBoxLayout();      //查询条件横布局
    layout_startTime = new QHBoxLayout();      //起始日期横布局
    layout_endTime = new QHBoxLayout();      //结束日期横布局
    layout_dateType = new QHBoxLayout();      //数据类型横布局
    layout_queryButton = new QHBoxLayout();      //查询按钮横布局
    layout_buttonGroup = new QVBoxLayout();
    layout_buttonDataType = new QVBoxLayout();

    lab_query_criteria = new QLabel(tr("查询条件"));     //查询条件 label
    lab_date_type = new QLabel(tr("数据类型:"));          //数据类型 label
    lab_start = new QLabel(tr("起始日期:"));             //起始日期 label
    lab_end = new QLabel(tr("结束日期:"));               //结束日期 label

    dateEdit_start = new QDateEdit();     //起始日期
    dateEdit_end = new QDateEdit();       //结束日期

    //时间输入弹出日历
    dateEdit_start->setCalendarPopup(true);
    dateEdit_end->setCalendarPopup(true);

    dateEdit_start->setDate(QDate(2017,1,1));
    dateEdit_end->setDate(QDate::currentDate());       //结束时间默认为当天

    dateEdit_start->setDisplayFormat("yyyy/MM/dd");    //qt5.9需要设置
    dateEdit_end->setDisplayFormat("yyyy/MM/dd");      //qt5.9需要设置

    radioButton_standard = new QRadioButton();;         //标准点
    radioButton_standard->setText(tr("标准点"));

    radioButton_quality = new QRadioButton();         //质控点
    radioButton_quality->setText(tr("质控点"));
    radioButton_quality->setChecked(true);         //单选框默认选中质控点

    radioButton_calibration = new QRadioButton();;         //校准点
    radioButton_calibration->setText(tr("校准点"));

    //将单选按钮添加到按钮组
//    buttonGroup_dateType->addButton(radioButton_quality);
//    buttonGroup_dateType->addButton(radioButton_calibration);
//    buttonGroup_dateType->addButton(radioButton_standard);

    layout_buttonGroup->addWidget(radioButton_quality);
    layout_buttonGroup->addWidget(radioButton_calibration);
    layout_buttonGroup->addWidget(radioButton_standard);



    //btn_query = new QPushButton(tr("查询"));         //查询按钮
    //QIcon icon1(":/picture/query/qualityDataQuery/qualityDataQuery.png");
    //btn_query->setIcon(icon1);
    //btn_query->setIconSize(QSize(26,26));

    btn_query = new QPushButton();         //查询按钮
    /*去按钮边框*/
    btn_query->setFlat(true);
    btn_query->setFocusPolicy(Qt::TabFocus);
    btn_query->setFixedSize(135,33);//图片的固定大小
    btn_query->setStyleSheet("QPushButton{border-image: url(:/picture/query/qualityDataQuery/qualityDataQuery-up.png);}"
                             "QPushButton:hover{border-image: url(:/picture/query/qualityDataQuery/qualityDataQuery-up.png);}"
                             "QPushButton:pressed{border-image: url(:/picture/query/qualityDataQuery/qualityDataQuery-down.png);}");


    layout_queryItem->addStretch(1);
    layout_queryItem->addWidget(lab_query_criteria);
    layout_queryItem->addStretch(80);

    layout_startTime->addStretch(3);
    layout_startTime->addWidget(lab_start);
    layout_startTime->addStretch(2);
    layout_startTime->addWidget(dateEdit_start);
    layout_startTime->addStretch(120);

    layout_endTime->addStretch(3);
    layout_endTime->addWidget(lab_end);
    layout_endTime->addStretch(2);
    layout_endTime->addWidget(dateEdit_end);
    layout_endTime->addStretch(120);

    layout_buttonDataType->addWidget(lab_date_type);
    layout_buttonDataType->addStretch(1);

    layout_dateType->addStretch(3);
    layout_dateType->addLayout(layout_buttonDataType);
    layout_dateType->addStretch(2);
    layout_dateType->addLayout(layout_buttonGroup);
    layout_dateType->addStretch(120);

    layout_queryButton->addStretch(1);
    layout_queryButton->addWidget(btn_query);
    layout_queryButton->addStretch(8);

    layout_left->addStretch(1);
    layout_left->addLayout(layout_queryItem);
    layout_left->addStretch(1);
    layout_left->addLayout(layout_startTime);
    layout_left->addStretch(1);
    layout_left->addLayout(layout_endTime);
    layout_left->addStretch(1);
    layout_left->addLayout(layout_dateType);
    layout_left->addStretch(1);
    layout_left->addLayout(layout_queryButton);
    layout_left->addStretch(8);

    tableView = new QTableView(widget);          //表————查询所得结果
    tableView->setGeometry(360,20,1280,850);

    model = new QMySQlQueryModel();         //QMySQlQueryModel继承QSQLQueryModel，可实现tableView内容居中

 /*

"create table quality_control_info("
                   "ID                                  INTEGER NOT NULL PRIMARY KEY autoincrement,"
                   "CATEGORY                            VARCHAR2(30) NOT NULL,"
                   "PROJECT_NAME                        VARCHAR2(30) NOT NULL,"
                   "REAGENT_TYPE                        VARCHAR2(30) NOT NULL,"
                   "BAR_CODE                            VARCHAR2(50) NOT NULL,"
                   "STANDARD_CONCENTRATION              DOUBLE(10,5),"
                   "START_DATE                          TIMESTAMP(6),"
                   "END_DATE                            TIMESTAMP(6),"
                   "STANDARD_FLAG                       CHAR(1),"
                   "PHOTON_VALUE                        INT(10),"
                   "CONCENTRATION                       DOUBLE(10,5),"
                   "VARIANCE_COEFFICENT                 DOUBLE(10,5),"
                   "CREATOR_ID                          VARCHAR2(32),"
                   "CREATE_TIME                         TIMESTAMP(6),"
                   "MODIFIER_ID                         VARCHAR2(32),"
                   "MODIFY_TIME                         TIMESTAMP(6),"
                   "DEL_FLAG                            CHAR(1)"
*/
    model->setQuery("select "
                    "ID,"
                    "a.CATEGORY,"
                    "a.PROJECT_NAME,"
                    "a.REAGENT_TYPE,"
                    "a.BAR_CODE,"
                    "a.CREATE_TIME,"
                    "a.STANDARD_CONCENTRATION,"
                    "a.CONCENTRATION,"
                    "a.PHOTON_VALUE,"
                    "a.VARIANCE_COEFFICENT,"
                    "a.START_DATE,"
                    "a.END_DATE,"
                    "a.CREATOR_ID,"
                    "a.MODIFIER_ID,"
                    "a.MODIFY_TIME"
                    " from quality_control_info as a;");
    model->setHeaderData(0,Qt::Horizontal,QVariant("序号"));
    model->setHeaderData(1,Qt::Horizontal,QVariant("品类"));
    model->setHeaderData(2,Qt::Horizontal,QVariant("项目名称"));
    model->setHeaderData(3,Qt::Horizontal,QVariant("试剂类别"));
    model->setHeaderData(4,Qt::Horizontal,QVariant("条码"));


    model->setHeaderData(5,Qt::Horizontal,QVariant("创建时间"));
    model->setHeaderData(6,Qt::Horizontal,QVariant("标称浓度"));
    model->setHeaderData(7,Qt::Horizontal,QVariant("测量浓度"));
    model->setHeaderData(8,Qt::Horizontal,QVariant("发光值"));
    model->setHeaderData(9,Qt::Horizontal,QVariant("CV值"));
    model->setHeaderData(10,Qt::Horizontal,QVariant("有效起始时间"));

    model->setHeaderData(11,Qt::Horizontal,QVariant("有效截止时间"));
    model->setHeaderData(12,Qt::Horizontal,QVariant("创建者ID"));
    model->setHeaderData(13,Qt::Horizontal,QVariant("修改者ID"));
    model->setHeaderData(14,Qt::Horizontal,QVariant("修改时间"));
    //model->setHeaderData(14,Qt::Horizontal,QVariant("浓度值"));
    tableView->setModel(model);
    tableView->resizeColumnsToContents();

    //设置列宽
    tableView->setColumnWidth(0,60);
    tableView->setColumnWidth(1,80);
    tableView->setColumnWidth(2,110);
    tableView->setColumnWidth(3,80);
    tableView->setColumnWidth(4,110);

    tableView->setColumnWidth(5,160);
    tableView->setColumnWidth(6,80);
    tableView->setColumnWidth(7,80);
    tableView->setColumnWidth(8,100);
    tableView->setColumnWidth(9,60);

    tableView->setColumnWidth(10,160);
    tableView->setColumnWidth(11,160);
    tableView->setColumnWidth(12,80);
    tableView->setColumnWidth(13,80);
    tableView->setColumnWidth(14,160);
 //   tableView->setColumnWidth(3,220);

    //设置其选择行为，并不可以编辑
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode ( QAbstractItemView::SingleSelection);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //设置各行变色
    tableView->setAlternatingRowColors(true);
    //设置交替色的颜色
    tableView->setStyleSheet("alternate-background-color: rgb(224, 224, 224);");
    //设置水平表头不可拖动
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    //设置垂直表头不可拖动
    tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    //设置水平表头的高度。
    tableView->horizontalHeader()->setFixedHeight(35);
    //设置垂直表头的宽度。
    tableView->verticalHeader()->setFixedWidth(30);

    //设置：行高
    tableView->verticalHeader()->setDefaultSectionSize(35);


    // 删除按钮设置
    btn_delete = new QPushButton(this);
    btn_delete->setFocusPolicy(Qt::TabFocus);
    btn_delete->setStyleSheet("QPushButton{border-image: url(:/picture/query/historyQuery/delete-up.png);}"
                             "QPushButton:hover{border-image: url(:/picture/query/historyQuery/delete-up.png);}"
                             "QPushButton:pressed{border-image: url(:/picture/query/historyQuery/delete-down.png);}");
    btn_delete->setGeometry(1450,900,135,33);


}



//查询
void QualityDataQuery::query()
{

    QString S_time=dateEdit_start->date().toString("yyyy-MM-dd");
    QString E_time=dateEdit_end->date().toString("yyyy-MM-dd");
    S_time+=" 00:00:00";E_time+=" 23:59:59";
    qDebug()<<S_time<<E_time;
    int chooseflag = 0;
    if(radioButton_standard->isChecked())
    {
        chooseflag=CHOOSE_STANDARD;
        qDebug()<<"选中标准点";
    }
    if(radioButton_quality->isChecked())
    {
        chooseflag=CHOOSE_QUALITY;
        qDebug()<<"选中质控点";
    }
    if(radioButton_calibration->isChecked())
    {
        chooseflag=CHOOSE_CALIBRATION;
        qDebug()<<"选中校准点";
    }
    //查询数据，并显示
    selectDATA_freshTable(chooseflag,S_time,E_time);

}

void QualityDataQuery::slot_btn_delete()
{
    if(chooseFlag_delete!=-1)
    {
        int row = chooseFlag_delete;
        QAbstractItemModel* modelll = tableView->model();
        int id = modelll->index(row,0).data().toInt();//第row行第0列的内容
        QString mbstr="是否删除该条检测信息?";
        qDebug()<<"id:"<<id;
        myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_QUESTION,tr("提示"),mbstr,this);
        if(messge->exec() == QDialog::Accepted){   //模式对话框
            QSqlQuery query;
            QString name = "";
            if(radioButton_calibration->isChecked())
            {
                name = "Calibration_Info";
            }else if(radioButton_quality->isChecked())
            {
                name = "Quality_Control_Info";
            }else
            {
                name = "Standard_Info";
            }
            QString strQuery = "";
            strQuery = "delete from " + name + " where ID =" + QString::number(id) + ";";
//            query.prepare("delete from :tableName where NUM_ID = :id;");
//            query.bindValue(":tableName",(const QVariant)name);
//            query.bindValue(":id",(const QVariant)id);

            qDebug()<<strQuery;
            qDebug()<<query.exec(strQuery);

            this->query();      //删除后重新查询刷新表格
            chooseFlag_delete = -1;
        }
        else
        {
            tableView->setFocus();
        }
    }
    else
    {

        myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_WARNING,tr("提示"),tr("请选择需要删除的信息！"),this);
        if(messge->exec() == QDialog::Accepted){   //模式对话框

        }
    }
}

void QualityDataQuery::slot_click_tableView(const QModelIndex &index)
{
    chooseFlag_delete = index.row();
}


void QualityDataQuery::selectDATA_freshTable(int chooseFlag, const QString &S_time, const QString &E_time)
{
    QString sss="select "
                "ID,"
                "CATEGORY,"
                "PROJECT_NAME,"
                "REAGENT_TYPE,"
                "BAR_CODE,"
                "CREATE_TIME,"
                "STANDARD_CONCENTRATION,"
                "CONCENTRATION,"
                "PHOTON_VALUE,"
                "VARIANCE_COEFFICENT,"
                "START_DATE,"
                "END_DATE,"
                "CREATOR_ID,"
                "MODIFIER_ID,"
                "MODIFY_TIME"
                " from ";
    if(chooseFlag==CHOOSE_QUALITY)
        sss+="quality_control_info";
    else if(chooseFlag==CHOOSE_STANDARD)
        sss+="standard_info";
    else if(chooseFlag==CHOOSE_CALIBRATION)
        sss+="calibration_info";
    sss+=" where CREATE_TIME between '"+S_time+"' and '"+E_time+"';";
    qDebug()<<sss;
    model->setQuery(sss);
    tableView->setModel(model);

}
