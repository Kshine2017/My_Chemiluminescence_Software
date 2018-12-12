#include "historysearch.h"
#include <QString>
#include <QHeaderView>
#include <QDebug>
#include "QMessgeBox/mymessgebox.h"

HistorySearch::HistorySearch(QWidget *parent) : QWidget(parent)
{
    init();
    connect(btn_query,SIGNAL(clicked()),this,SLOT(query()));
    connect(btn_delete,SIGNAL(clicked()),this,SLOT(slot_btn_delete()));
    connect(tableView_patient_info,SIGNAL(clicked(QModelIndex)),this,SLOT(slot_click_tableView(QModelIndex)));

}
//查询
void HistorySearch::query()
{
    QSqlQuery query;
    QString query_term = "select "          //查询条件
                         "name,"
                         "sex,"
                         "age,"
                         "telephone,"
                         "department,"
                         "test_item,"
                         "TEST_CONCENTRATION,"
                         "create_time"
                         " from patient_info where DEL_FLAG = 0";

    if(lineEdit_department->text() != "")
    {
        query_term.append(" and DEPARTMENT = "+ lineEdit_department->text());
    }

    if(lineEdit_name->text() != "")
    {
        query_term.append(" and NAME like %"+ lineEdit_name->text()+"%");
    }

    QString end_data ="'" + dateEdit_end_date->date().toString("yyyy-MM-dd") + "00:00:00'";
    qDebug()<<end_data<< "当前时间";

    QString start_data ="'" + dateEdit_start_date->date().toString("yyyy-MM-dd") + "23:59:59'";

    query_term.append(" and CREATE_TIME >= "+ start_data +" and CREATE_TIME <= " + end_data);

    qDebug()<<"查询条件"<<query_term;
    model->setQuery(query_term);
    tableView_patient_info->setModel(model);

}


//补录病人信息
void HistorySearch::patientInformationCollect(){}
//修正实验数据
void HistorySearch::correctedExperimentData(){}

void HistorySearch::slot_btn_delete()
{
    if(chooseFlag!=-1)
    {


        int row = chooseFlag;
        QAbstractItemModel* modelll = tableView_patient_info->model();
        int id = modelll->index(row,0).data().toInt();//第row行第0列的内容
        QString mbstr="是否删除该条病人信息?";
        qDebug()<<"id:"<<id;
        myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_QUESTION,tr("提示"),mbstr,this);
        if(messge->exec() == QDialog::Accepted){   //模式对话框

            QSqlQuery query;
            query.prepare("delete from Patient_Info where NUM_ID = :id;");
            query.bindValue(":id",(const QVariant)id);

            qDebug()<<query.exec();

            model->setQuery("select "
                            "NUM_ID,"
                            "name,"
                            "sex,"
                            "age,"
                            "telephone,"
                            "department,"
                            "test_item,"
                            "TEST_CONCENTRATION,"
                            "create_time"
                            " from patient_info");
            tableView_patient_info->setModel(model);
            chooseFlag = -1;
        }
        else
        {
            tableView_patient_info->setFocus();
        }
    }
    else
    {

        myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_WARNING,tr("提示"),tr("请选择需要删除的信息！"),this);
        if(messge->exec() == QDialog::Accepted){   //模式对话框

        }
    }

}

void HistorySearch::slot_click_tableView(const QModelIndex &index)
{
    chooseFlag = index.row();
}

//初始化界面
void HistorySearch::init()
{
    chooseFlag = -1;
    widget = new QWidget(this);        //主窗口
    this->setFont(QFont("宋体",14));

    //://query/historyQuery_bg.png

    QPalette palette;
    QPixmap pixmap(":/picture/query/historyQuery_bg.png");
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    widget->setPalette(palette);    //放置背景图片

    widget->setFixedSize(1660,1000);
    widget->setAutoFillBackground(true);


    layout_all = new QHBoxLayout(widget);        //布局
    layout_left = new QVBoxLayout();        //左边布局
    layout_right = new QVBoxLayout();        //右边布局
    layout_query_criteria = new QHBoxLayout();        //查询条件布局
    layout_outpatient_number = new QHBoxLayout();        //门诊号布局
    layout_department = new QHBoxLayout();        //科室布局
    layout_start_date = new QHBoxLayout();        //起始日期布局
    layout_end_date = new QHBoxLayout();        //结束日期布局
    layout_name = new QHBoxLayout();        //姓名布局
    layout_experiment_number = new QHBoxLayout();        //实验号布局
    layout_query = new QHBoxLayout();        //查询按钮布局
    layout_data_processing = new QHBoxLayout();        //数据处理布局
    layout_btn = new QHBoxLayout();        //按钮布局

    label_query_criteria = new QLabel(QString(tr("查询条件")));        //查询条件标签
    label_outpatient_number = new QLabel(QString(tr("门诊号:")));        //门诊号标签
    label_department = new QLabel(QString(tr("科室:")));        //科室标签
    label_start_date = new QLabel(QString(tr("起始日期:")));        //起始日期标签
    label_end_date = new QLabel(QString(tr("结束日期:")));        //结束日期标签
    label_name = new QLabel(QString(tr("姓名:")));        //姓名标签
    label_experiment_number = new QLabel(QString(tr("实验号:")));        //实验号标签
    label_data_processing = new QLabel(QString(tr("数据处理")));        //数据处理标签
    /*设置标签的大小*/
    label_query_criteria->setFixedSize(85,30);
    label_outpatient_number->setFixedSize(85,30);
    label_department->setFixedSize(85,30);
    label_start_date->setFixedSize(85,30);
    label_end_date->setFixedSize(85,30);
    label_name->setFixedSize(85,30);
    label_experiment_number->setFixedSize(85,30);
    label_data_processing->setFixedSize(85,30);

    lineEdit_outpatient_number = new QLineEdit();        //门诊号输入框
    lineEdit_department = new QLineEdit();        //科室输入框
    dateEdit_start_date = new QDateEdit();        //起始日期输入框
    dateEdit_end_date = new QDateEdit();        //结束日期输入框
    lineEdit_name = new QLineEdit();        //姓名输入框
    lineEdit_experiment_number = new QLineEdit();        //实验号输入框
    //时间输入弹出日历
    dateEdit_start_date->setCalendarPopup(true);
    dateEdit_end_date->setCalendarPopup(true);
    //设置起始时间，结束时间的默认值
    dateEdit_start_date->setDate(QDate(2018,1,1));
    dateEdit_end_date->setDate(QDate::currentDate());       //结束时间默认为当天

    //设置输入框的大小
    lineEdit_outpatient_number->setFixedSize(180,33);
    lineEdit_department->setFixedSize(180,33);
    dateEdit_start_date->setFixedSize(180,33);
    dateEdit_end_date->setFixedSize(180,33);
    lineEdit_name->setFixedSize(180,33);
    lineEdit_experiment_number->setFixedSize(180,33);


    dateEdit_start_date->setDisplayFormat("yyyy/MM/dd"); //Kshine Qt5.9与5.7的差异，需要手动设置一下
    dateEdit_end_date->setDisplayFormat("yyyy/MM/dd");


    //btn_query= new QPushButton(QString(tr("查询")));
    //btn_patient_information_collection = new QPushButton(QString(tr("补录病人信息")));        //补录病人信息按钮
    //btn_corrected_experiment_data = new QPushButton(QString(tr("修正实验数据")));        //修正实验数据按钮
    btn_query = new QPushButton();
    btn_patient_information_collection = new QPushButton();
    btn_corrected_experiment_data = new QPushButton();



    /*去按钮边框*/
    btn_query->setFlat(true);
    btn_patient_information_collection->setFlat(true);
    btn_corrected_experiment_data->setFlat(true);

    /*给按钮添加图标*/

    //QIcon icon1(":/picture/query/historyQuery/query.png");
    // btn_query->setIcon(icon1);
    //btn_query->setIconSize(QSize(26,26));
//    QIcon icon2(":/picture/query/historyQuery/patientInformationCollection.png");
//    btn_patient_information_collection->setIcon(icon2);
//    btn_patient_information_collection->setIconSize(QSize(24,24));
//    QIcon icon3(":/picture/query/historyQuery/correctedExperimentData.png");
//    btn_corrected_experiment_data->setIcon(icon3);
//    btn_corrected_experiment_data->setIconSize(QSize(24,24));

    btn_query->setFocusPolicy(Qt::TabFocus);
    btn_query->setFixedSize(135,33);//图片的固定大小
    btn_query->setStyleSheet("QPushButton{border-image: url(:/picture/query/historyQuery/query-up.png);}"
                             "QPushButton:hover{border-image: url(:/picture/query/historyQuery/query-up.png);}"
                             "QPushButton:pressed{border-image: url(:/picture/query/historyQuery/query-down.png);}");
    btn_patient_information_collection->setFocusPolicy(Qt::TabFocus);
    btn_patient_information_collection->setFixedSize(135,33);//图片的固定大小
    btn_patient_information_collection->setStyleSheet("QPushButton{border-image: url(:/picture/query/historyQuery/patientInformationCollection-up.png);}"
                             "QPushButton:hover{border-image: url(:/picture/query/historyQuery/patientInformationCollection-up.png);}"
                             "QPushButton:pressed{border-image: url(:/picture/query/historyQuery/patientInformationCollection-down.png);}");
    btn_corrected_experiment_data->setFocusPolicy(Qt::TabFocus);
    btn_corrected_experiment_data->setFixedSize(135,33);//图片的固定大小
    btn_corrected_experiment_data->setStyleSheet("QPushButton{border-image: url(:/picture/query/historyQuery/correctedExperimentData-up.png);}"
                             "QPushButton:hover{border-image: url(:/picture/query/historyQuery/correctedExperimentData-up.png);}"
                             "QPushButton:pressed{border-image: url(:/picture/query/historyQuery/correctedExperimentData-down.png);}");


    /****************tableView_patient_info 属性设置开始********************/

    tableView_patient_info = new QTableView();        //查询显示窗口
    tableView_patient_info->setFixedSize(1250,630);
    tableView_patient_info->setFont(QFont("宋体",14));//设置字体大小

    model = new QMySQlQueryModel();         //QMySQlQueryModel继承QSQLQueryModel，可实现tableView内容居中
    model->setQuery("select "
                    "NUM_ID,"
                    "name,"
                    "sex,"
                    "age,"
                    "telephone,"
                    "department,"
                    "test_item,"
                    "TEST_CONCENTRATION,"
                    "create_time"
                    " from patient_info");
    model->setHeaderData(0,Qt::Horizontal,QVariant("序号"));
    model->setHeaderData(1,Qt::Horizontal,QVariant("姓名"));
    model->setHeaderData(2,Qt::Horizontal,QVariant("性别"));
    model->setHeaderData(3,Qt::Horizontal,QVariant("年龄"));
    model->setHeaderData(4,Qt::Horizontal,QVariant("电话"));
    model->setHeaderData(5,Qt::Horizontal,QVariant("科室"));
    model->setHeaderData(6,Qt::Horizontal,QVariant("检测项目"));
    model->setHeaderData(7,Qt::Horizontal,QVariant("检测项目浓度"));
    model->setHeaderData(8,Qt::Horizontal,QVariant("检测时间"));
    tableView_patient_info->setModel(model);
    tableView_patient_info->resizeColumnsToContents();
//    model = new QSqlTableModel();         //查询数据模型
//    model->setTable("password");
//    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
//    model->select(); //选取整个表的所有行
//    //model->removeColumn(1); //不显示name属性列,如果这时添加记录，则该属性的值添加不上
//    tableView_patient_info->setModel(model);
//    tableView_patient_info->setEditTriggers(QAbstractItemView::NoEditTriggers); //使其不可编辑

    //设置其选择行为，并不可以编辑
    tableView_patient_info->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView_patient_info->setSelectionMode ( QAbstractItemView::SingleSelection);
    tableView_patient_info->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置各行变色
    tableView_patient_info->setAlternatingRowColors(true);
    //设置交替色的颜色
    tableView_patient_info->setStyleSheet("alternate-background-color: rgb(224, 224, 224);");
    //设置水平表头不可拖动
    tableView_patient_info->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    //设置垂直表头不可拖动
    tableView_patient_info->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    //设置水平表头的高度。
    tableView_patient_info->horizontalHeader()->setFixedHeight(35);
    //设置垂直表头的宽度。
    tableView_patient_info->verticalHeader()->setFixedWidth(30);
    //设置列宽
    tableView_patient_info->setColumnWidth(0,60);
    tableView_patient_info->setColumnWidth(1,150);
    tableView_patient_info->setColumnWidth(2,60);
    tableView_patient_info->setColumnWidth(3,60);
    tableView_patient_info->setColumnWidth(4,150);
    tableView_patient_info->setColumnWidth(5,150);
    tableView_patient_info->setColumnWidth(6,150);
    tableView_patient_info->setColumnWidth(7,150);
    tableView_patient_info->setColumnWidth(8,276);
    //设置：行高
    tableView_patient_info->verticalHeader()->setDefaultSectionSize(35);

    tableView_experiment_data = new QTableView();        //修正实验数据窗口
    tableView_experiment_data->setFixedSize(1250,230);


    btn_delete = new QPushButton(this);
    btn_delete->setFocusPolicy(Qt::TabFocus);
    btn_delete->setFixedSize(135,33);//图片的固定大小
    btn_delete->setStyleSheet("QPushButton{border-image: url(:/picture/query/historyQuery/delete-up.png);}"
                             "QPushButton:hover{border-image: url(:/picture/query/historyQuery/delete-up.png);}"
                             "QPushButton:pressed{border-image: url(:/picture/query/historyQuery/delete-down.png);}");
    btn_delete->setGeometry(1450,675,135,33);


    /*
     *左边布局设计
     */
    //查询条件布局
    layout_query_criteria->addWidget(label_query_criteria);
    layout_query_criteria->addStretch();
    //门诊号布局
    layout_outpatient_number->addWidget(label_outpatient_number);
    layout_outpatient_number->addWidget(lineEdit_outpatient_number);
    layout_outpatient_number->addStretch();
    //科室布局
    layout_department->addWidget(label_department);
    layout_department->addWidget(lineEdit_department);
    layout_department->addStretch();
    //起始日期布局
    layout_start_date->addWidget(label_start_date);
    layout_start_date->addWidget(dateEdit_start_date);
    layout_start_date->addStretch();
    //结束日期布局
    layout_end_date->addWidget(label_end_date);
    layout_end_date->addWidget(dateEdit_end_date);
    layout_end_date->addStretch();
    //姓名布局
    layout_name->addWidget(label_name);
    layout_name->addWidget(lineEdit_name);
    layout_name->addStretch();
    //实验号布局
    layout_experiment_number->addWidget(label_experiment_number);
    layout_experiment_number->addWidget(lineEdit_experiment_number);
    layout_experiment_number->addStretch();
    //查询按钮布局
    layout_query->addStretch();
    layout_query->addWidget(btn_query);
    //数据处理布局
    layout_data_processing->addWidget(label_data_processing);
    layout_data_processing->addStretch();
    //按钮布局
    layout_btn->addWidget(btn_patient_information_collection);
    layout_btn->addWidget(btn_corrected_experiment_data);

    layout_left->addStretch(1);
    layout_left->addLayout(layout_query_criteria);
    layout_left->addStretch(1);
    layout_left->addLayout(layout_outpatient_number);
    layout_left->addStretch(1);
    layout_left->addLayout(layout_department);
    layout_left->addStretch(1);
    layout_left->addLayout(layout_start_date);
    layout_left->addStretch(1);
    layout_left->addLayout(layout_query_criteria);
    layout_left->addStretch(1);
    layout_left->addLayout(layout_end_date);
    layout_left->addStretch(1);
    layout_left->addLayout(layout_name);
    layout_left->addStretch(1);
    layout_left->addLayout(layout_experiment_number);
    layout_left->addStretch(1);
    layout_left->addLayout(layout_query);
    layout_left->addStretch(1);
    layout_left->addLayout(layout_data_processing);
    layout_left->addStretch(1);
    layout_left->addLayout(layout_btn);
    layout_left->addStretch(6);

    /*
     * 右边布局
     */
    layout_right->addStretch(2);
    layout_right->addWidget(tableView_patient_info);
    layout_right->addStretch(6);
    layout_right->addWidget(tableView_experiment_data);
    layout_right->addStretch(1);

    layout_all->addStretch(1);
    layout_all->addLayout(layout_left);
    layout_all->addStretch(4);
    layout_all->addLayout(layout_right);
    layout_all->addStretch(1);
}
