#include "myreagentdialogquery.h"

#include <QDebug>
#include "databaseoperation.h"
#include "../qmysqlquerymodel.h"
#include "QMessgeBox/mymessgebox.h"

MyReagentDialogQuery::MyReagentDialogQuery(QWidget *parent) : QDialog(parent)
{
    init();
    initComboBoxData();

    connect(btn_cancel,SIGNAL(clicked()),this,SLOT(btn_cancelSlot()));
    connect(btn_sure,SIGNAL(clicked()),this,SLOT(btn_addSlot()));

    connect(cBox_CATEGORY,SIGNAL(currentTextChanged(QString)),this,SLOT(slot_fresh_le_CATEGORY_code(QString)));
    connect(cBox_CATEGORY,SIGNAL(currentTextChanged(QString)),this,SLOT(slot_fresh_cBox_PROJECT_NAME(QString)));
    connect(cBox_PROJECT_NAME,SIGNAL(currentIndexChanged(QString)),this,SLOT(slot_fresh_le_PROJECT_NAME_code(QString)));
    connect(cBox_PROJECT_NAME,SIGNAL(currentIndexChanged(QString)),this,SLOT(slot_fresh_cBox_REAGENT_TYPE(QString)));
    connect(cBox_REAGENT_TYPE,SIGNAL(currentIndexChanged(QString)),this,SLOT(slot_fresh_le_REAGENT_TYPE_code(QString)));
}

void MyReagentDialogQuery::init()
{
    setWindowModality(Qt::ApplicationModal);
    this->setWindowTitle(tr("条码编码"));
    this->setFixedSize(849,666);
    QPalette palette;
    QPixmap pixmap(":/picture/login/register_background.jpg");
    palette.setBrush(QPalette::Window,QBrush(pixmap));
    setPalette(palette);

    mainLayout = new QVBoxLayout(this);
    layout_CATEGORY = new QHBoxLayout();        //试剂品类
    layout_CATEGORY_code = new QHBoxLayout();        //试剂品类编码

    layout_PROJECT_NAME = new QHBoxLayout();                //项 目 名 称
    layout_PROJECT_NAME_code = new QHBoxLayout();           //项目名称编码

    layout_REAGENT_TYPE = new QHBoxLayout();        //试剂种类
    layout_REAGENT_TYPE_code = new QHBoxLayout();        //试剂种类编码

    layout_btn = new QHBoxLayout();        //试剂品类


    label_CATEGORY = new QLabel("试剂品类:");
    label_CATEGORY->setFixedSize(100,40);
    label_CATEGORY->setFont(QFont("window title",16));

    label_CATEGORY_code = new QLabel("品类编码:");
    label_CATEGORY_code->setFixedSize(100,40);
    label_CATEGORY_code->setFont(QFont("window title",16));

    label_PROJECT_NAME = new QLabel("项目名称:");
    label_PROJECT_NAME->setFixedSize(100,40);
    label_PROJECT_NAME->setFont(QFont("window title",16));

    label_PROJECT_NAME_code = new QLabel("名称编码:");
    label_PROJECT_NAME_code->setFixedSize(100,40);
    label_PROJECT_NAME_code->setFont(QFont("window title",16));

    label_REAGENT_TYPE = new QLabel("试剂种类:");
    label_REAGENT_TYPE->setFixedSize(100,40);
    label_REAGENT_TYPE->setFont(QFont("window title",16));

    label_REAGENT_TYPE_code = new QLabel("种类编码:");
    label_REAGENT_TYPE_code->setFixedSize(100,40);
    label_REAGENT_TYPE_code->setFont(QFont("window title",16));

    //输入框
    cBox_CATEGORY = new QComboBox();
    cBox_CATEGORY->setFixedSize(500,40);
    cBox_CATEGORY->setEditable(true);   //设置该下拉框可编辑
    le_CATEGORY_code = new QLineEdit();
    le_CATEGORY_code->setFixedSize(500,40);

    cBox_PROJECT_NAME = new QComboBox();
    cBox_PROJECT_NAME->setFixedSize(500,40);
    cBox_PROJECT_NAME->setEditable(true);   //设置该下拉框可编辑

    le_PROJECT_NAME_code = new QLineEdit();
    le_PROJECT_NAME_code->setFixedSize(500,40);

    cBox_REAGENT_TYPE = new QComboBox();
    cBox_REAGENT_TYPE->setFixedSize(500,40);
    cBox_REAGENT_TYPE->setEditable(true);   //设置该下拉框可编辑
    le_REAGENT_TYPE_code = new QLineEdit();
    le_REAGENT_TYPE_code->setFixedSize(500,40);

    //布局
    layout_CATEGORY->addStretch(3);
    layout_CATEGORY->addWidget(label_CATEGORY);
    layout_CATEGORY->addStretch(1);
    layout_CATEGORY->addWidget(cBox_CATEGORY);
    layout_CATEGORY->addStretch(3);

    layout_CATEGORY_code->addStretch(3);
    layout_CATEGORY_code->addWidget(label_CATEGORY_code);
    layout_CATEGORY_code->addStretch(1);
    layout_CATEGORY_code->addWidget(le_CATEGORY_code);
    layout_CATEGORY_code->addStretch(3);

    layout_PROJECT_NAME->addStretch(3);
    layout_PROJECT_NAME->addWidget(label_PROJECT_NAME);
    layout_PROJECT_NAME->addStretch(1);
    layout_PROJECT_NAME->addWidget(cBox_PROJECT_NAME);
    layout_PROJECT_NAME->addStretch(3);

    layout_PROJECT_NAME_code->addStretch(3);
    layout_PROJECT_NAME_code->addWidget(label_PROJECT_NAME_code);
    layout_PROJECT_NAME_code->addStretch(1);
    layout_PROJECT_NAME_code->addWidget(le_PROJECT_NAME_code);
    layout_PROJECT_NAME_code->addStretch(3);

    layout_REAGENT_TYPE->addStretch(3);
    layout_REAGENT_TYPE->addWidget(label_REAGENT_TYPE);
    layout_REAGENT_TYPE->addStretch(1);
    layout_REAGENT_TYPE->addWidget(cBox_REAGENT_TYPE);
    layout_REAGENT_TYPE->addStretch(3);

    layout_REAGENT_TYPE_code->addStretch(3);
    layout_REAGENT_TYPE_code->addWidget(label_REAGENT_TYPE_code);
    layout_REAGENT_TYPE_code->addStretch(1);
    layout_REAGENT_TYPE_code->addWidget(le_REAGENT_TYPE_code);
    layout_REAGENT_TYPE_code->addStretch(3);

    //按钮布局
    btn_sure = new QPushButton ();
    btn_sure->setFixedSize(110,43);
    btn_sure->setStyleSheet("QPushButton{border-image: url(:/picture/MessgeBox/sure-up.png);}"
                             "QPushButton:hover{border-image: url(:/picture/MessgeBox/sure-up.png);}"
                             "QPushButton:pressed{border-image: url(:/picture/MessgeBox/sure-down.png);}");

    btn_cancel = new QPushButton ();
    btn_cancel->setFixedSize(110,43);
    btn_cancel->setStyleSheet("QPushButton{border-image: url(:/picture/MessgeBox/cancel-up.png);}"
                                "QPushButton:hover{border-image: url(:/picture/MessgeBox/cancel-up.png);}"
                                "QPushButton:pressed{border-image: url(:/picture/MessgeBox/cancel-down.png);}");

    layout_btn->addWidget(btn_sure);
    layout_btn->addWidget(btn_cancel);

    mainLayout->addStretch(2);
    mainLayout->addLayout(layout_CATEGORY);
    mainLayout->addStretch(1);
    mainLayout->addLayout(layout_CATEGORY_code);
    mainLayout->addStretch(1);
    mainLayout->addLayout(layout_PROJECT_NAME);
    mainLayout->addStretch(1);
    mainLayout->addLayout(layout_PROJECT_NAME_code);
    mainLayout->addStretch(1);
    mainLayout->addLayout(layout_REAGENT_TYPE);
    mainLayout->addStretch(1);
    mainLayout->addLayout(layout_REAGENT_TYPE_code);
    mainLayout->addStretch(3);
    mainLayout->addLayout(layout_btn);
    mainLayout->addStretch(2);
}

void MyReagentDialogQuery::initComboBoxData()
{
    DatabaseOperation op;
    QSqlQueryModel myModel;
    op.selectCategoryAll(myModel);
    cBox_CATEGORY->addItem("");
    for(int i=0;i<myModel.rowCount();i++)
    {
        QModelIndex index = myModel.index(i,0);
        QString str = myModel.data(index).toString();
        cBox_CATEGORY->addItem(str);
    }

    //品类编码初始值
    QString str_category = cBox_CATEGORY->currentText();
    op.selectCategory_codeByCategory(str_category,myModel);
    QModelIndex index = myModel.index(0,0);
    QString str = myModel.data(index).toString();
    le_CATEGORY_code->setText(str);

    //项目名称初始值
    op.selectProject_nameByCategory(str_category,myModel);
    cBox_PROJECT_NAME->addItem("");
    for(int i=0;i<myModel.rowCount();i++)
    {
        QModelIndex index_pn = myModel.index(i,0);
        QString str_pn = myModel.data(index_pn).toString();
        cBox_PROJECT_NAME->addItem(str_pn);
    }

    //项目名称编码初始值
    QString str_project_name = cBox_PROJECT_NAME->currentText();
    op.selectProject_name_codeByProject_name(str_category,str_project_name,myModel);
    index = myModel.index(0,0);
    str = myModel.data(index).toString();
    le_PROJECT_NAME_code->setText(str);

    //试剂种类初始值

    op.selectReagent_typeByProject_name(str_category,str_project_name,myModel);
    cBox_REAGENT_TYPE->addItem("");
    for(int i=0;i<myModel.rowCount();i++)
    {
        QModelIndex index_rt = myModel.index(i,0);
        QString str_rt = myModel.data(index_rt).toString();
        cBox_REAGENT_TYPE->addItem(str_rt);
    }

    //试剂种类编码初始值
    QString str_reagent_type = cBox_REAGENT_TYPE->currentText();
    op.selectReagent_type_codeByReagent_type(str_category,str_project_name,str_reagent_type,myModel);
    index = myModel.index(0,0);
    str = myModel.data(index).toString();
    le_REAGENT_TYPE_code->setText(str);
}

void MyReagentDialogQuery::btn_cancelSlot()
{
    this->close();
}

void MyReagentDialogQuery::btn_addSlot()
{
    QString str_catrgory = cBox_CATEGORY->currentText();
    QString str_projectName = cBox_PROJECT_NAME->currentText();
    QString str_reagentType = cBox_REAGENT_TYPE->currentText();

    emit siganl_please_fresh_table(str_catrgory,str_projectName,str_reagentType);
    this->close();

}

/**
 * @brief slot_fresh_cBox_PROJECT_NAME 品类更改时刷新项目名称
 * @param str_category  品类
 */
void MyReagentDialogQuery::slot_fresh_cBox_PROJECT_NAME(QString str_category)
{
    DatabaseOperation op;
    QSqlQueryModel myModel;
    op.selectProject_nameByCategory(str_category,myModel);

    cBox_PROJECT_NAME->clear();
    cBox_PROJECT_NAME->addItem("");

    for(int i=0;i<myModel.rowCount();i++)
    {
        QModelIndex index = myModel.index(i,0);
        QString str = myModel.data(index).toString();
        cBox_PROJECT_NAME->addItem(str);
    }
}
/**
 * @brief slot_fresh_cBox_REAGENT_TYPE  项目名称更改时刷新试剂种类
 * @param str_projectName   项目名称
 */
void MyReagentDialogQuery::slot_fresh_cBox_REAGENT_TYPE(QString str_projectName)
{
    DatabaseOperation op;
    QSqlQueryModel myModel;
    QString str_category = cBox_CATEGORY->currentText();
    op.selectReagent_typeByProject_name(str_category,str_projectName,myModel);

    cBox_REAGENT_TYPE->clear();
    cBox_REAGENT_TYPE->addItem("");
    for(int i=0;i<myModel.rowCount();i++)
    {
        QModelIndex index = myModel.index(i,0);
        QString str = myModel.data(index).toString();
        cBox_REAGENT_TYPE->addItem(str);
    }

}
/**
 * @brief slot_fresh_le_CATEGORY_code品类更改时刷新品类编码
 * @param str_category  品类
 */
void MyReagentDialogQuery::slot_fresh_le_CATEGORY_code(QString str_category)
{
    DatabaseOperation op;
    QSqlQueryModel myModel;
    op.selectCategory_codeByCategory(str_category,myModel);

    QModelIndex index = myModel.index(0,0);
    QString str = myModel.data(index).toString();
    le_CATEGORY_code->setText(str);

}
/**
 * @brief slot_fresh_le_PROJECT_NAME_code   项目名称更改时刷项目名称编码
 * @param str_PROJECT_NAME      项目名称
 */
void MyReagentDialogQuery::slot_fresh_le_PROJECT_NAME_code(QString str_PROJECT_NAME)
{
    DatabaseOperation op;
    QSqlQueryModel myModel;
    QString str_category = cBox_CATEGORY->currentText();
    op.selectProject_name_codeByProject_name(str_category,str_PROJECT_NAME,myModel);

    QModelIndex index = myModel.index(0,0);
    QString str = myModel.data(index).toString();
    le_PROJECT_NAME_code->setText(str);
}
/**
 * @brief slot_fresh_le_REAGENT_TYPE_code   试剂种类更改时刷新试剂种类编码
 * @param str_REAGENT_TYPE      试剂种类
 */
void MyReagentDialogQuery::slot_fresh_le_REAGENT_TYPE_code(QString str_REAGENT_TYPE)
{
    DatabaseOperation op;
    QSqlQueryModel myModel;
    QString str_PROJECT_NAME = cBox_PROJECT_NAME->currentText();
    QString str_category = cBox_CATEGORY->currentText();

    op.selectReagent_type_codeByReagent_type(str_category,str_PROJECT_NAME,str_REAGENT_TYPE,myModel);

    QModelIndex index = myModel.index(0,0);
    QString str = myModel.data(index).toString();
    le_REAGENT_TYPE_code->setText(str);

}
