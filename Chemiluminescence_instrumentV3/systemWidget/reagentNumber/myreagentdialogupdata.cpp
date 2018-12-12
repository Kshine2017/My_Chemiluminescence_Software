#include "myreagentdialogupdata.h"
#include "databaseoperation.h"
#include <QDebug>
#include "QMessgeBox/mymessgebox.h"
MyReagentDialogUpdata::MyReagentDialogUpdata(QWidget *parent,QString str_category,QString str_category_code,
                                             QString str_projectName,QString str_projectName_code,
                                             QString str_reagentType,QString str_reagentType_code) : QDialog(parent)
{

    init();
    initComboBoxData();
    cBox_CATEGORY->setCurrentText(str_category);
    slot_fresh_cBox_PROJECT_NAME(str_category);
    slot_fresh_cBox_REAGENT_TYPE(str_projectName);

    cBox_PROJECT_NAME->setCurrentText(str_projectName);
    cBox_REAGENT_TYPE->setCurrentText(str_reagentType);


    le_CATEGORY_code->setText(str_category_code);
    le_PROJECT_NAME_code->setText(str_projectName_code);
    le_REAGENT_TYPE_code->setText(str_reagentType_code);

    str_categoryInfo = str_category;
    str_categoryCodeInfo = str_category_code;
    str_projectNameInfo = str_projectName;
    str_projectNameCodeInfo = str_projectName_code;
    str_reagentTypeInfo = str_reagentType;
    str_reagentTypeCodeInfo = str_reagentType_code;



    connect(btn_sure,SIGNAL(clicked()),this,SLOT(btn_addSlot()));
    connect(btn_cancel,SIGNAL(clicked()),this,SLOT(btn_cancelSlot()));

    connect(cBox_CATEGORY,SIGNAL(currentTextChanged(QString)),this,SLOT(slot_fresh_le_CATEGORY_code(QString)));
    connect(cBox_CATEGORY,SIGNAL(currentTextChanged(QString)),this,SLOT(slot_fresh_cBox_PROJECT_NAME(QString)));
    connect(cBox_PROJECT_NAME,SIGNAL(currentIndexChanged(QString)),this,SLOT(slot_fresh_le_PROJECT_NAME_code(QString)));
    connect(cBox_PROJECT_NAME,SIGNAL(currentIndexChanged(QString)),this,SLOT(slot_fresh_cBox_REAGENT_TYPE(QString)));
    connect(cBox_REAGENT_TYPE,SIGNAL(currentIndexChanged(QString)),this,SLOT(slot_fresh_le_REAGENT_TYPE_code(QString)));

}

void MyReagentDialogUpdata::init()
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
/**
 * @brief MyReagentDialogUpdata::initComboBoxData
 *  初始化各项默认数据
 */
void MyReagentDialogUpdata::initComboBoxData()
{
    DatabaseOperation op;
    QSqlQueryModel myModel;
    op.selectCategoryAll(myModel);
    for(int i=0;i<myModel.rowCount();i++)
    {
        QModelIndex index = myModel.index(i,0);
        QString str = myModel.data(index).toString();
                //myModel.data(index).toString();
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
/**
 * @brief MyReagentDialogUpdata::checkCategory  检查数据库中有无品类及其编码重复
 * @return
 *
 * 0---------品类及编码都未改变
 * 1---------品类和编码可以修改------修改当前一条
 * 2---------修改品类对应编码--------修改该品类名称对应的所有编码
 * 3---------修改编码对应的品类名称---修改该编码对应的所有品类名称
 * -1--------编码已存在对应品类名称
 * -2--------品类名称已对应编码
 */
int MyReagentDialogUpdata::checkCategory()
{
    QString str_category = cBox_CATEGORY->currentText();
    QString str_category_code = le_CATEGORY_code->text();

    QString str_projectName = cBox_PROJECT_NAME->currentText();
    QString str_projectName_code = le_PROJECT_NAME_code->text();

    QString str_reagentType = cBox_REAGENT_TYPE->currentText();
    QString str_reagentType_code = le_REAGENT_TYPE_code->text();

    DatabaseOperation op;
    QSqlQueryModel myModel;

    //  品类限制
    if(str_category == str_categoryInfo && str_category_code == str_categoryCodeInfo)
    {
        return 0;
    }else if(str_category != str_categoryInfo && str_category_code == str_categoryCodeInfo)
    {
        if(op.selectCategory_codeByCategory(str_category,myModel))
        {
            return -2;
        }else
        {
            return 3;
        }
    }else if (str_category == str_categoryInfo && str_category_code != str_categoryCodeInfo)
    {
        if(op.selectCategoryByCategory_code(str_category_code,myModel))
        {
            return -1;
        }else
        {
            return 2;
        }
    }else
    {
        if(op.selectCategory_codeByCategory(str_category,myModel))
        {
            QModelIndex index = myModel.index(0,0);
            QString temp_str_category_code = myModel.data(index).toString();

            if(temp_str_category_code == str_category_code)
            {
                return 1;
            }else
            {
                return -2;
            }


        }else
        {
            if(op.selectCategoryByCategory_code(str_category_code,myModel))
            {
                return -1;
            }else
            {
                return 0;
            }
        }
    }

}
/**
 * @brief MyReagentDialogUpdata::checkProjectName  检查数据库中有无项目名称及其编码重复
 * @return
 *
 * 0---------项目名称及编码都未改变
 * 1---------项目名称和编码可以修改------修改当前一条
 * 2---------修改项目名称对应编码--------修改该项目名称对应的所有编码
 * 3---------修改编码对应的项目名称---修改该编码对应的所有项目名称
 * -1--------编码已存在对应项目名称
 * -2--------项目名称已对应编码
 */
int MyReagentDialogUpdata::checkProjectName()
{
    QString str_category = cBox_CATEGORY->currentText();
    QString str_category_code = le_CATEGORY_code->text();

    QString str_projectName = cBox_PROJECT_NAME->currentText();
    QString str_projectName_code = le_PROJECT_NAME_code->text();

    QString str_reagentType = cBox_REAGENT_TYPE->currentText();
    QString str_reagentType_code = le_REAGENT_TYPE_code->text();

    DatabaseOperation op;
    QSqlQueryModel myModel;
    //项目名称限制
    qDebug()<<"str_projectName"<<str_projectName<<"----"<<str_projectNameInfo;
    qDebug()<<"str_projectName_code"<<str_projectName_code<<"----"<<str_projectNameCodeInfo;


    if(str_projectName == str_projectNameInfo && str_projectName_code == str_projectNameCodeInfo)
    {
        return 0;

    }else if(str_projectName != str_projectNameInfo && str_projectName_code == str_projectNameCodeInfo)
    {
        if(op.selectProject_name_codeByProject_name(str_category,str_projectName,myModel))
        {
//            QString mbstr="该项目名称已存在对应编码！";
//            myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_INFORMATION,tr("提示"),mbstr,this);
//            if(messge->exec() == QDialog::Accepted){   //模式对话框
//                return 0;
//            }
            return -2;
        }else
        {
//            QString mbstr="是否修改项目名称编码“" + str_projectName_code + "”对应的项目名称！";
//            myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_QUESTION,tr("提示"),mbstr,this);
//            if(messge->exec() == QDialog::Accepted){   //模式对话框
//                return 1;
//            }else   //不修改
//            {
//                return 0;
//            }
            return 3;
        }
    }else if (str_projectName == str_projectNameInfo && str_projectName_code != str_projectNameCodeInfo)
    {
        if(op.selectProject_nameByProject_name_code(str_category,str_projectName_code,myModel))
        {
//            QString mbstr="该编码已存在对应项目名称！";
//            myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_INFORMATION,tr("提示"),mbstr,this);
//            if(messge->exec() == QDialog::Accepted){   //模式对话框
//                return 0;
//            }
            return -1;
        }else
        {
//            QString mbstr = "是否修改项目名称“"+str_projectName+"”对应的名称编码！";
//            myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_QUESTION,tr("提示"),mbstr,this);
//            if(messge->exec() == QDialog::Accepted){   //模式对话框
//                return 2;
//            }else   //不修改
//            {
//                return 0;
//            }
            return 2;
        }
    }else
    {
        if(op.selectProject_name_codeByProject_name(str_category,str_projectName,myModel))
        {
            QModelIndex index = myModel.index(0,0);
            QString temp_str_projectName_code = myModel.data(index).toString();

            if(temp_str_projectName_code == str_projectName_code)
            {
//                QString mbstr = "是否修改该项目名称信息？";
//                myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_QUESTION,tr("提示"),mbstr,this);
//                if(messge->exec() == QDialog::Accepted){   //模式对话框
//                    return -1;
//                }else   //不修改
//                {
//                    return 0;
//                }
                return 1;
            }else
            {
//                QString mbstr="该项目名称已存在对应编码！";
//                myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_INFORMATION,tr("提示"),mbstr,this);
//                if(messge->exec() == QDialog::Accepted){   //模式对话框
//                    return 0;
//                }

                return -2;
            }

        }else
        {
            if(op.selectProject_nameByProject_name_code(str_category,str_projectName_code,myModel))
            {
//                QString mbstr="该编码已存在对应项目名称！";
//                myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_INFORMATION,tr("提示"),mbstr,this);
//                if(messge->exec() == QDialog::Accepted){   //模式对话框
//                    return 0;
//                }
                return -1;
            }else
            {
//                QString mbstr = "是否修改该项目名称信息？";
//                myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_QUESTION,tr("提示"),mbstr,this);
//                if(messge->exec() == QDialog::Accepted){   //模式对话框
//                    return -1;
//                }else   //不修改
//                {
//                    return 0;
//                }
                return 1;
            }
        }
    }
    return 0;

}
/**
 * @brief MyReagentDialogUpdata::checkReagentType  检查数据库中有无试剂种类及其编码重复
 * @return
 *
 * 0---------试剂种类及编码都未改变
 * 1---------试剂种类和编码可以修改------修改当前一条
 * 2---------修改试剂种类对应编码--------修改该试剂种类对应的所有编码
 * 3---------修改编码对应的试剂种类---修改该编码对应的所有试剂种类
 * -1--------编码已存在对应试剂种类
 * -2--------试剂种类已对应编码
 */
int MyReagentDialogUpdata::checkReagentType()
{
    QString str_category = cBox_CATEGORY->currentText();
    QString str_category_code = le_CATEGORY_code->text();

    QString str_projectName = cBox_PROJECT_NAME->currentText();
    QString str_projectName_code = le_PROJECT_NAME_code->text();

    QString str_reagentType = cBox_REAGENT_TYPE->currentText();
    QString str_reagentType_code = le_REAGENT_TYPE_code->text();

    DatabaseOperation op;
    QSqlQueryModel myModel;

    //试剂种类限制
    qDebug()<<"str_reagentType"<<str_reagentType<<"----"<<str_reagentTypeInfo;
    qDebug()<<"str_reagentType_code"<<str_reagentType_code<<"----"<<str_reagentTypeCodeInfo;

    if(str_reagentType == str_reagentTypeInfo && str_reagentType_code == str_reagentTypeCodeInfo)
    {
        return 0;

    }else if(str_reagentType != str_reagentTypeInfo && str_reagentType_code == str_reagentTypeCodeInfo)
    {
        if(op.selectReagent_type_codeByReagent_type(str_category,str_projectName,str_reagentType,myModel))
        {
//            QString mbstr="该试剂种类已存在对应编码！";
//            myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_INFORMATION,tr("提示"),mbstr,this);
//            if(messge->exec() == QDialog::Accepted){   //模式对话框
//                return 0;
//            }
            return -2;
        }else
        {
//            QString mbstr="是否修改试剂种类编码“" + str_projectName_code + "”对应的试剂种类！";
//            myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_QUESTION,tr("提示"),mbstr,this);
//            if(messge->exec() == QDialog::Accepted){   //模式对话框
//                return 1;
//            }else   //不修改
//            {
//                return 0;
//            }
            return 1;
        }
    }else if (str_reagentType == str_reagentTypeInfo && str_reagentType_code != str_reagentTypeCodeInfo)
    {
        if(op.selectReagent_typeByReagent_type_code(str_category,str_projectName,str_reagentType_code,myModel))
        {
//            QString mbstr="该编码已存在对应试剂种类！";
//            myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_INFORMATION,tr("提示"),mbstr,this);
//            if(messge->exec() == QDialog::Accepted){   //模式对话框
//                return 0;
//            }
            return -1;
        }else
        {
//            QString mbstr = "是否修改试剂种类“"+str_projectName+"”对应的种类编码！";
//            myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_QUESTION,tr("提示"),mbstr,this);
//            if(messge->exec() == QDialog::Accepted){   //模式对话框
//                return 2;
//            }else   //不修改
//            {
//                return 0;
//            }
            return 1;
        }
    }else
    {
        if(op.selectReagent_type_codeByReagent_type(str_category,str_projectName,str_reagentType,myModel))
        {
//            QModelIndex index = myModel.index(0,0);
//            QString temp_str_reagent_type_code = myModel.data(index).toString();

//            if(temp_str_reagent_type_code == str_reagentType_code)
//            {
//                QString mbstr = "是否修改该试剂种类信息？";
//                myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_QUESTION,tr("提示"),mbstr,this);
//                if(messge->exec() == QDialog::Accepted){   //模式对话框
//                    return -1;
//                }else   //不修改
//                {
//                    return 0;
//                }
//            }else
//            {
//                QString mbstr="该试剂种类已存在对应编码！";
//                myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_INFORMATION,tr("提示"),mbstr,this);
//                if(messge->exec() == QDialog::Accepted){   //模式对话框
//                    return 0;
//                }
//            }
            return -2;

        }else
        {
            if(op.selectReagent_typeByReagent_type_code(str_category,str_projectName,str_reagentType_code,myModel))
            {
//                QString mbstr="该编码已存在对应试剂种类！";
//                myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_INFORMATION,tr("提示"),mbstr,this);
//                if(messge->exec() == QDialog::Accepted){   //模式对话框
//                    return 0;
//                }
                return -1;
            }else
            {
                return 1;
            }
        }
    }

    return 0;

}

void MyReagentDialogUpdata::btn_cancelSlot()
{
    this->close();
}

void MyReagentDialogUpdata::btn_addSlot()
{
    QString str_category = cBox_CATEGORY->currentText();
    QString str_category_code = le_CATEGORY_code->text();

    QString str_projectName = cBox_PROJECT_NAME->currentText();
    QString str_projectName_code = le_PROJECT_NAME_code->text();

    QString str_reagentType = cBox_REAGENT_TYPE->currentText();
    QString str_reagentType_code = le_REAGENT_TYPE_code->text();

    DatabaseOperation op;
    QSqlQueryModel myModel;

    int flag_C = checkCategory();
    int flag_P = checkProjectName();
    int flag_R = checkReagentType();

    if(flag_C <0)
    {
        if(flag_C == -1)
        {
            QString mbstr="该编码已存在对应品类名称！";
            myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_INFORMATION,tr("提示"),mbstr,this);
            if(messge->exec() == QDialog::Accepted){   //模式对话框
            }
        }else
        {
            QString mbstr="该品类名称已存在对应编码！";
            myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_INFORMATION,tr("提示"),mbstr,this);
            if(messge->exec() == QDialog::Accepted){   //模式对话框
            }
        }

    }else if(flag_C == 0 || flag_C == 1)
    {
        if(flag_P== 0 || flag_P == 1)
        {
            if(flag_R== 0 || flag_R == 1)
            {
                if(flag_R == 1 || flag_P == 1 || flag_C == 1)
                {
                    QString mbstr = "是否修改该试剂种类信息？";
                    myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_QUESTION,tr("提示"),mbstr,this);
                    if(messge->exec() == QDialog::Accepted){   //模式对话框
                        QString strReagentCode = str_categoryCodeInfo + str_projectNameCodeInfo + str_reagentTypeCodeInfo;
                        //更新
                        op.upDataReagentData(str_category,str_category_code,str_projectName,
                                             str_projectName_code,str_reagentType,
                                             str_reagentType_code,strReagentCode);
                    }
                }else
                {
                    QString mbstr = "当前信息未经过修改";
                    myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_INFORMATION,tr("提示"),mbstr,this);
                    if(messge->exec() == QDialog::Accepted){   //模式对话框
                    }
                }
            }else if(flag_R < 0)
            {
                if(flag_R == -1)
                {
                    QString mbstr="该试剂种类编码已存在对应试剂种类！";
                    myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_INFORMATION,tr("提示"),mbstr,this);
                    if(messge->exec() == QDialog::Accepted){   //模式对话框
                    }
                }else
                {
                    QString mbstr="该试剂种类已存在对应编码！";
                    myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_INFORMATION,tr("提示"),mbstr,this);
                    if(messge->exec() == QDialog::Accepted){   //模式对话框
                    }
                }
            }

        }else if(flag_P < 0)
        {
            if(flag_P == -1)
            {
                QString mbstr="该编码已存在对应项目名称！";
                myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_INFORMATION,tr("提示"),mbstr,this);
                if(messge->exec() == QDialog::Accepted){   //模式对话框
                }
            }else
            {
                QString mbstr="该项目名称已存在对应编码！";
                myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_INFORMATION,tr("提示"),mbstr,this);
                if(messge->exec() == QDialog::Accepted){   //模式对话框
                }
            }

        }else
        {
            if(flag_P == 2)
            {
                QString mbstr = "是否修改项目名称“"+str_projectName+"”对应的名称编码！";
                myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_QUESTION,tr("提示"),mbstr,this);
                if(messge->exec() == QDialog::Accepted){   //模式对话框
                    op.upDataProject_name_codeByProject_name(str_category,str_projectName,str_projectName_code);
                }
            }else
            {
                QString mbstr="是否修改项目名称编码“" + str_projectName_code + "”对应的项目名称！";
                myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_QUESTION,tr("提示"),mbstr,this);
                if(messge->exec() == QDialog::Accepted){   //模式对话框
                    op.upDataProject_nameByProject_name_code(str_category,str_projectName_code,str_projectName);
                }
            }
        }
    }else
    {
        if(flag_C == 2)
        {
            QString mbstr = "是否修改试剂品类“"+str_category+"”对应的品类编码！";
            myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_QUESTION,tr("提示"),mbstr,this);
            if(messge->exec() == QDialog::Accepted){   //模式对话框
                qDebug()<<"修改数据"<<str_category<<"----"<<str_category_code;
                op.upDataCategory_codeByCategory(str_category,str_category_code);
            }
        }else
        {
            QString mbstr="是否修改试剂品类编码“"+str_category_code+"”对应的品类名称！";
            myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_QUESTION,tr("提示"),mbstr,this);
            if(messge->exec() == QDialog::Accepted){   //模式对话框
                op.upDataCategoryByCategory_code(str_category_code,str_category);
            }
        }
    }
    emit siganl_please_fresh_table();
    this->close();
}

/**
 * @brief slot_fresh_cBox_PROJECT_NAME 品类更改时刷新项目名称
 * @param str_category  品类
 */
void MyReagentDialogUpdata::slot_fresh_cBox_PROJECT_NAME(QString str_category)
{
    DatabaseOperation op;
    QSqlQueryModel myModel;
    op.selectProject_nameByCategory(str_category,myModel);

    cBox_PROJECT_NAME->clear();

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
void MyReagentDialogUpdata::slot_fresh_cBox_REAGENT_TYPE(QString str_projectName)
{
    DatabaseOperation op;
    QSqlQueryModel myModel;
    QString str_category = cBox_CATEGORY->currentText();
    op.selectReagent_typeByProject_name(str_category,str_projectName,myModel);

    cBox_REAGENT_TYPE->clear();

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
void MyReagentDialogUpdata::slot_fresh_le_CATEGORY_code(QString str_category)
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
void MyReagentDialogUpdata::slot_fresh_le_PROJECT_NAME_code(QString str_PROJECT_NAME)
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
void MyReagentDialogUpdata::slot_fresh_le_REAGENT_TYPE_code(QString str_REAGENT_TYPE)
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
