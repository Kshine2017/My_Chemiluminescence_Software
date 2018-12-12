#include "clinicaldiagnosis.h"
#include <QString>
#include <QStringList>
#include <QHeaderView>
#include <QDebug>
#include <QMessgeBox/mymessgebox.h>

/**
 * @brief ClinicalDiagnosis::ClinicalDiagnosis
 * @param parent
 * @author huangzhijie
 * 科室与临床诊断管理界面
 */
ClinicalDiagnosis::ClinicalDiagnosis(QWidget *parent) : QWidget(parent)
{
    init();                 //初始化界面

    connect(btn_AddDepartment,SIGNAL(clicked()),this,SLOT(addDepartment()));
    connect(btn_DeleteDepartment,SIGNAL(clicked()),this,SLOT(deleteDepartment()));
    connect(btn_AddDiagnosticCategory,SIGNAL(clicked()),this,SLOT(AddDiagnosticCategory()));
    connect(btn_DeleteDiagnosticCategory,SIGNAL(clicked()),this,SLOT(deleteDiagnosticCategory()));

    //------表格默认行号初始化-------
    delete_table_row_flag_department=-1;
}

void ClinicalDiagnosis::addDepartment()     //增加科室
{
    dialog_addDepartment = new DialogAddDepartment();
    connect(dialog_addDepartment,SIGNAL(signal_saveAdd()),this,SLOT(update_tableView()));
    connect(dialog_addDepartment,SIGNAL(signal_saveClose()),this,SLOT(update_tableView()));

    dialog_addDepartment->show();
}

void ClinicalDiagnosis::deleteDepartment()      //删除选中科室科室
{
    tableView_InspectionDepartment->setFocus(Qt::MouseFocusReason);
    qDebug()<<"###  "<<delete_table_row_flag_department;

    if(delete_table_row_flag_department >= 0)
    {

        QString department = tableView_InspectionDepartment->model()
                ->data(tableView_InspectionDepartment->model()->index(delete_table_row_flag_department,1))
                .toString();

        myMessgeBox *msgBox = new myMessgeBox(myMessgeBox::MY_MESSAGE_QUESTION,tr("提示"),"你确定要删除科室 “"+department +"” 吗？",this);
        msgBox->show();

        if(msgBox->exec() == QDialog::Accepted){   //模式对话框---点击确定就执行以下内容
            QSqlQuery query;

            QAbstractItemModel *model = tableView_InspectionDepartment->model();
            QModelIndex index = model->index(delete_table_row_flag_department,1);//选中行第一列的内容
            QVariant data = model->data(index);

            qDebug() <<"选中 pwd："<<data.value<QString>();

            /**
             * 删除表hospital_info，科室名等于传入的 data的一行
             * @param username
             */
            query.prepare("DELETE FROM hospital_info WHERE DEPATMENT_NAME = :data");
            query.bindValue(":data", data.value<QString>());
            query.exec();

            model_InspectionDepartment->setQuery("select HOSPITAL_NAME,DEPATMENT_NAME from hospital_info");
            tableView_InspectionDepartment->setModel(model_InspectionDepartment);
        }
    }
    else
    {
        myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_WARNING,tr("提示"),tr("请选择需要删除的科室！"),this);
        if(messge->exec() == QDialog::Accepted){   //模式对话框
        }
        return;
    }

}

void ClinicalDiagnosis::AddDiagnosticCategory()         //新增临床诊断类型
{
    DialogAddDiagnosticCategory *dialog_addDiagnostic = new DialogAddDiagnosticCategory();


    dialog_addDiagnostic->show();
}

void ClinicalDiagnosis::deleteDiagnosticCategory()          //删除临床诊断类型
{
    myMessgeBox *msgBox = new myMessgeBox(myMessgeBox::MY_MESSAGE_QUESTION,tr("提示"),tr("你确定要删除本行吗？"),this);
    msgBox->show();

    if(msgBox->exec() == QDialog::Accepted){   //模式对话框---点击确定就执行以下内容
        QSqlQuery query;
        int row = tableView_DiagnosisDepartment->currentIndex().row();
        QAbstractItemModel *model = tableView_DiagnosisDepartment->model();
        QModelIndex index = model->index(row,0);//选中行第一列的内容
        QVariant data = model->data(index);

        qDebug() <<"选中 pwd："<<data.value<QString>();

        /**
         * 删除表password，密码等于传入的 data的一行
         * @param username
         */
        query.prepare("DELETE FROM password WHERE usrname=:data");
        query.bindValue(":data", data.value<QString>());
        query.exec();

//        model_DiagnosisDepartment->select();
        tableView_DiagnosisDepartment->setModel(model_DiagnosisDepartment);
    }

}


//刷新表格
void ClinicalDiagnosis::update_tableView()
{
    model_InspectionDepartment->setQuery("select HOSPITAL_NAME,DEPATMENT_NAME from hospital_info");
    tableView_InspectionDepartment->setModel(model_InspectionDepartment);
    delete_table_row_flag_department = -1; //每次刷新后回到不选择状态；
}

//获取选择的行号，如果未选择行，则为-1；
void ClinicalDiagnosis::slot_getTablerow_department(QModelIndex index)
{
    delete_table_row_flag_department= index.row();
    qDebug()<<"点击第"<<delete_table_row_flag_department<<"行";
}

//初始化界面
void ClinicalDiagnosis::init(){

    layout_InspectionDepartment = new QVBoxLayout();        //送检科室管理界面
    layout_DiagnosisDepartment = new QVBoxLayout();         //诊断科室类别管理界面

    layout_InspectionBtn = new QHBoxLayout();       //放置科室管理按钮
    layout_DiagnosisBtn = new QHBoxLayout();        //放置诊断科室类别管理按钮

    widget_content = new QWidget(this); //放置背景图片的的
    widget_content->setFixedSize(1671,1000);
    widget_content->setAutoFillBackground(true);

    QPalette palette;
    QPixmap pixmap(":/picture/System/clinicalDiagnosis/bg.png");
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    widget_content->setPalette(palette);    //放置背景图片

    layout_Manage = new QHBoxLayout(widget_content);        //两个layout 放一起

    lab_InspectionDepartment = new QLabel(QString(tr("送检科室管理")));        //标签——送检科室管理
    lab_InspectionDepartment->setFont(QFont("宋体",20));
    lab_InspectionDepartment->setFixedSize(400,60);

    lab_DiagnosisDepartment = new QLabel(QString(tr("诊断科室类别管理")));        //标签——诊断科室类别管理
    lab_DiagnosisDepartment->setFont(QFont("宋体",20));
    lab_DiagnosisDepartment->setFixedSize(400,60);

    tableView_InspectionDepartment = new QTableView();        //表格——送检科室管理
//    tableView_InspectionDepartment->selectRow(-1);      //设置默认选择-1行
    connect(tableView_InspectionDepartment,SIGNAL(clicked(QModelIndex)),this,SLOT(slot_getTablerow_department(QModelIndex)));

    tableView_InspectionDepartment->setFixedSize(720,750);
    tableView_InspectionDepartment->setFont(QFont("windowTitle",18));//设置字体大小

    model_InspectionDepartment = new QMySQlQueryModel();      //送检科室管理模型
    model_InspectionDepartment->setQuery("select HOSPITAL_NAME,DEPATMENT_NAME from hospital_info");
    tableView_InspectionDepartment->setModel(model_InspectionDepartment);

    model_InspectionDepartment->setHeaderData(0,Qt::Horizontal,QVariant("医院"));
    model_InspectionDepartment->setHeaderData(1,Qt::Horizontal,QVariant("科室"));

    /*tableView_InspectionDepartment设置集合*/
    //设置其选择行为，并不可以编辑
    tableView_InspectionDepartment->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView_InspectionDepartment->setSelectionMode ( QAbstractItemView::SingleSelection);
    tableView_InspectionDepartment->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //隐藏表格线
    tableView_InspectionDepartment->setShowGrid(true);
    //设置各行变色
    tableView_InspectionDepartment->setAlternatingRowColors(true);
    //设置交替色的颜色
    tableView_InspectionDepartment->setStyleSheet("alternate-background-color: rgb(224, 224, 224);");
    //设置水平表头不可拖动
    tableView_InspectionDepartment->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    //设置垂直表头不可拖动
    tableView_InspectionDepartment->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    //设置水平表头的高度。
    tableView_InspectionDepartment->horizontalHeader()->setFixedHeight(42);
    //设置垂直表头的宽度。
    tableView_InspectionDepartment->verticalHeader()->setFixedWidth(42);
    //隐藏垂直表头
    tableView_InspectionDepartment->verticalHeader()->setVisible(false);
    //设置水平表头内文字的字体、颜色和大小。
    tableView_InspectionDepartment->horizontalHeader()->setStyleSheet
            ("QHeaderView::section{font:18pt 'windowTitle';color: black;};");
    //设置垂直表头内文字的字体、颜色和大小。
    tableView_InspectionDepartment->verticalHeader()->setStyleSheet
            ("QHeaderView::section{font:18pt 'windowTitle';color: black;};");
    //设置列宽
    tableView_InspectionDepartment->setColumnWidth(0,380);
    tableView_InspectionDepartment->setColumnWidth(1,338);
    //设置：行高
    tableView_InspectionDepartment->verticalHeader()->setDefaultSectionSize(42);

    tableView_DiagnosisDepartment = new QTableView();        //表格——诊断科室类别管理
    tableView_DiagnosisDepartment->setFixedSize(720,750);
    tableView_DiagnosisDepartment->setFont(QFont("windowTitle",18));//设置字体大小

    model_DiagnosisDepartment = new QMySQlQueryModel();
//    model_DiagnosisDepartment->setTable("password");       //把表名为password的表数据传入模型
//    model_DiagnosisDepartment->setEditStrategy(QSqlTableModel::OnManualSubmit);

//    model_DiagnosisDepartment->select(); //选取整个表的所有行
    model_DiagnosisDepartment->removeColumn(1); //不显示第一列,如果这时添加记录，则该属性的值添加不上
    model_DiagnosisDepartment->removeColumn(2);

//    model_DiagnosisDepartment->setHeaderData(0,Qt::Horizontal,QVariant("编号"));
//    model_DiagnosisDepartment->setHeaderData(1,Qt::Horizontal,QVariant("临床诊断类别管理"));
    tableView_DiagnosisDepartment->setModel(model_DiagnosisDepartment);

    /*tableView_DiagnosisDepartment设置集合*/
    //设置其选择行为，并不可以编辑
    tableView_DiagnosisDepartment->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView_DiagnosisDepartment->setSelectionMode ( QAbstractItemView::SingleSelection);
    tableView_DiagnosisDepartment->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //隐藏表格线
    tableView_DiagnosisDepartment->setShowGrid(true);
    //设置各行变色
    tableView_DiagnosisDepartment->setAlternatingRowColors(true);
    //设置交替色的颜色
    tableView_DiagnosisDepartment->setStyleSheet("alternate-background-color: rgb(224, 224, 224);");
    //设置水平表头不可拖动
    tableView_DiagnosisDepartment->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    //设置垂直表头不可拖动
    tableView_DiagnosisDepartment->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    //设置水平表头的高度。
    tableView_DiagnosisDepartment->horizontalHeader()->setFixedHeight(42);
    //设置垂直表头的宽度。
    tableView_DiagnosisDepartment->verticalHeader()->setFixedWidth(42);
    //隐藏垂直表头
    tableView_DiagnosisDepartment->verticalHeader()->setVisible(false);
    //设置水平表头内文字的字体、颜色和大小。
    tableView_DiagnosisDepartment->horizontalHeader()->setStyleSheet
            ("QHeaderView::section{font:18pt 'windowTitle';color: black;};");
    //设置垂直表头内文字的字体、颜色和大小。
    tableView_DiagnosisDepartment->verticalHeader()->setStyleSheet
            ("QHeaderView::section{font:18pt 'windowTitle';color: black;};");
    //设置列宽
    tableView_DiagnosisDepartment->setColumnWidth(0,180);
    tableView_DiagnosisDepartment->setColumnWidth(1,538);
    //设置：行高
    tableView_DiagnosisDepartment->verticalHeader()->setDefaultSectionSize(42);




//    btn_AddDepartment = new QPushButton(QString(tr("新增科室")));        //按钮——新增科室
//    btn_AddDepartment->setFont(QFont("宋体",20));
//    btn_AddDepartment->setFixedSize(200,40);
//    btn_AddDepartment->setFlat(true);
//    QIcon icon1(":/picture/System/clinicalDiagnosis/addDepartment .png");
//    btn_AddDepartment->setIcon(icon1);
//    btn_AddDepartment->setIconSize(QSize(36,36));

    btn_AddDepartment = new QPushButton();
    btn_AddDepartment->setFlat(true);
    btn_AddDepartment->setFocusPolicy(Qt::TabFocus);
    btn_AddDepartment->setFixedSize(153,42);//图片的固定大小
    btn_AddDepartment->setStyleSheet("QPushButton{border-image: url(:/picture/System/clinicalDiagnosis/addDepartment-up.png);}"
                             "QPushButton:hover{border-image: url(:/picture/System/clinicalDiagnosis/addDepartment-up.png);}"
                             "QPushButton:pressed{border-image: url(:/picture/System/clinicalDiagnosis/addDepartment-down.png);}");

    //    btn_DeleteDepartment = new QPushButton(QString(tr("删除科室")));        //按钮——删除科室
    //    btn_DeleteDepartment->setFont(QFont("宋体",20));
    //    btn_DeleteDepartment->setFixedSize(200,40);
    //    btn_DeleteDepartment->setFlat(true);
    //    QIcon icon2(":/picture/System/clinicalDiagnosis/deleteDepartment.png");
    //    btn_DeleteDepartment->setIcon(icon2);
    //    btn_DeleteDepartment->setIconSize(QSize(36,36));
        btn_DeleteDepartment = new QPushButton();
        btn_DeleteDepartment->setFlat(true);
        btn_DeleteDepartment->setFocusPolicy(Qt::TabFocus);
        btn_DeleteDepartment->setFixedSize(153,42);//图片的固定大小
        btn_DeleteDepartment->setStyleSheet("QPushButton{border-image: url(:/picture/System/clinicalDiagnosis/deleteDepartment-up.png);}"
                                 "QPushButton:hover{border-image: url(:/picture/System/clinicalDiagnosis/deleteDepartment-up.png);}"
                                 "QPushButton:pressed{border-image: url(:/picture/System/clinicalDiagnosis/deleteDepartment-down.png);}");

    //    btn_AddDiagnosticCategory = new QPushButton(QString(tr("新增临床诊断类型")));        //按钮——新增临床诊断类型
    //    btn_AddDiagnosticCategory->setFont(QFont("宋体",20));
    //    btn_AddDiagnosticCategory->setFixedSize(280,40);
    //    btn_AddDiagnosticCategory->setFlat(true);
    //    QIcon icon3(":/picture/System/clinicalDiagnosis/addDiagnosticCategory.png");
    //    btn_AddDiagnosticCategory->setIcon(icon3);
    //    btn_AddDiagnosticCategory->setIconSize(QSize(36,36));
        btn_AddDiagnosticCategory = new QPushButton();
        btn_AddDiagnosticCategory->setFlat(true);
        btn_AddDiagnosticCategory->setFocusPolicy(Qt::TabFocus);
        btn_AddDiagnosticCategory->setFixedSize(213,42);//图片的固定大小
        btn_AddDiagnosticCategory->setStyleSheet("QPushButton{border-image: url(:/picture/System/clinicalDiagnosis/addDiagnosticCategory-up.png);}"
                                 "QPushButton:hover{border-image: url(:/picture/System/clinicalDiagnosis/addDiagnosticCategory-up.png);}"
                                 "QPushButton:pressed{border-image: url(:/picture/System/clinicalDiagnosis/addDiagnosticCategory-down.png);}");

    //    btn_DeleteDiagnosticCategory = new QPushButton(QString(tr("删除临床诊断类型")));        //按钮——删除临床诊断类型
    //    btn_DeleteDiagnosticCategory->setFont(QFont("宋体",20));
    //    btn_DeleteDiagnosticCategory->setFixedSize(280,40);
    //    btn_DeleteDiagnosticCategory->setFlat(true);
    //    QIcon icon4(":/picture/System/clinicalDiagnosis/deleteDiagnosticCategory.png");
    //    btn_DeleteDiagnosticCategory->setIcon(icon4);
    //    btn_DeleteDiagnosticCategory->setIconSize(QSize(36,36));
        btn_DeleteDiagnosticCategory = new QPushButton();
        btn_DeleteDiagnosticCategory->setFlat(true);
        btn_DeleteDiagnosticCategory->setFocusPolicy(Qt::TabFocus);
        btn_DeleteDiagnosticCategory->setFixedSize(213,42);//图片的固定大小
        btn_DeleteDiagnosticCategory->setStyleSheet("QPushButton{border-image: url(:/picture/System/clinicalDiagnosis/deleteDiagnosticCategory-up.png);}"
                                 "QPushButton:hover{border-image: url(:/picture/System/clinicalDiagnosis/deleteDiagnosticCategory-up.png);}"
                                 "QPushButton:pressed{border-image: url(:/picture/System/clinicalDiagnosis/deleteDiagnosticCategory-down.png);}");


    /*
     * 送检科室管理布局
     */
    layout_InspectionBtn->addSpacing(1);
    layout_InspectionBtn->addWidget(btn_AddDepartment);
    layout_InspectionBtn->addWidget(btn_DeleteDepartment);

    layout_InspectionDepartment->addWidget(lab_InspectionDepartment);
    layout_InspectionDepartment->addWidget(tableView_InspectionDepartment);
    layout_InspectionDepartment->addSpacing(16);
    layout_InspectionDepartment->addLayout(layout_InspectionBtn);
    layout_InspectionDepartment->addStretch();

    /*
     * 诊断科室类别管理布局
     */
    layout_DiagnosisBtn->addSpacing(5);
    layout_DiagnosisBtn->addWidget(btn_AddDiagnosticCategory);
    layout_DiagnosisBtn->addWidget(btn_DeleteDiagnosticCategory);

    layout_DiagnosisDepartment->addWidget(lab_DiagnosisDepartment);
    layout_DiagnosisDepartment->addWidget(tableView_DiagnosisDepartment);
    layout_DiagnosisDepartment->addSpacing(16);
    layout_DiagnosisDepartment->addLayout(layout_DiagnosisBtn);
    layout_DiagnosisDepartment->addStretch();


    layout_Manage->addLayout(layout_InspectionDepartment);
    layout_Manage->addLayout(layout_DiagnosisDepartment);
}
