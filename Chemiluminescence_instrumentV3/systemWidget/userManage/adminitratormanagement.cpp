#include "adminitratormanagement.h"
#include <QDebug>
#include <QHeaderView>
#include "mydialogadd.h"
#include "mydialogupdate.h"
#include "../../QMessgeBox/mymessgebox.h"
AdminitratorManagement::AdminitratorManagement(QWidget *parent)
    : QWidget(parent)
{
    widget = new QWidget(this);         //主窗口
    widget->setFixedSize(1671,1010);
    widget->setAutoFillBackground(true);
    chooseFlag=-1;
    QPalette palette;
    QPixmap pixmap(":/picture/System/userManage/user_bg.png");
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    widget->setPalette(palette);    //放置背景图片

    tableView = new QTableView(widget);
    //connect(tableView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(slot_doubleclick_tableview(QModelIndex)));
    connect(tableView,SIGNAL(clicked(QModelIndex)),this,SLOT(slot_doubleclick_tableview(QModelIndex)));
    tableView->setFont(QFont("windowTitle",18));//设置字体大小
    tableView->setFixedSize(1671,810);
    model = new QMySQlQueryModel();         //普通用户管理数据模型

    //model->setTable("usrinfo");

    model->setQuery("select usrname,pwd,name,department,hospital,phone_numeber,email from administator_usrinfo;");
    //model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setHeaderData(0,Qt::Horizontal,QVariant("账号"));
    model->setHeaderData(1,Qt::Horizontal,QVariant("密码"));
    model->setHeaderData(2,Qt::Horizontal,QVariant("姓名"));
    model->setHeaderData(3,Qt::Horizontal,QVariant("科室"));
    model->setHeaderData(4,Qt::Horizontal,QVariant("医院"));
    model->setHeaderData(5,Qt::Horizontal,QVariant("电话"));
    model->setHeaderData(6,Qt::Horizontal,QVariant("邮箱"));

    //model->select(); //选取整个表的所有行
   // model->removeColumn(1); //不显示name属性列,如果这时添加记录，则该属性的值添加不上

    tableView->setModel(model);

    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); //使其不可编辑

    /*tableView设置集合*/
    //设置其选择行为，并不可以编辑
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode ( QAbstractItemView::SingleSelection);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //隐藏表格线
    tableView->setShowGrid(true);
    //设置各行变色
    tableView->setAlternatingRowColors(true);
    //设置交替色的颜色
    tableView->setStyleSheet("alternate-background-color: rgb(224, 224, 224);");
    //设置水平表头不可拖动
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    //设置垂直表头不可拖动
    tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    //设置水平表头的高度。
    tableView->horizontalHeader()->setFixedHeight(42);
    //设置垂直表头的宽度。
    tableView->verticalHeader()->setFixedWidth(42);
    //设置水平表头内文字的字体、颜色和大小。
    tableView->horizontalHeader()->setStyleSheet
            ("QHeaderView::section{font:18pt 'windowTitle';color: black;};");
    //设置垂直表头内文字的字体、颜色和大小。
    tableView->verticalHeader()->setStyleSheet
            ("QHeaderView::section{font:18pt 'windowTitle';color: black;};");

    //设置列宽
    tableView->setColumnWidth(0,200);
    tableView->setColumnWidth(1,200);
    tableView->setColumnWidth(2,200);
    tableView->setColumnWidth(3,200);
    tableView->setColumnWidth(4,200);
    tableView->setColumnWidth(5,200);
    tableView->setColumnWidth(6,1671-1200-42-2);
    //设置：行高
    tableView->verticalHeader()->setDefaultSectionSize(42);

//    QSqlQuery query;
//    query.exec("insert into password values('谢飞发财略略略略略略略','123','13605511574','xiefei@bb-care.com.cn')");

//    model->select();
//    tableView->setModel(model);
    /*
     * 增删改查
     * */
    btn_add = new QPushButton(widget);      //新增按钮
    btn_updata = new QPushButton(widget);      //修改按钮
    btn_delete = new QPushButton(widget);      //删除按钮
    btn_query = new QPushButton(widget);      //查询按钮

    btn_add->setGeometry(tableView->x()+450,tableView->y()+tableView->height()+30,150,40);
    btn_add->setStyleSheet("QPushButton{border-image: url(:/picture/System/userManage/add-up.png);}"
                               "QPushButton:hover{border-image: url(:/picture/System/userManage/add-up.png);}"
                               "QPushButton:pressed{border-image: url(:/picture/System/userManage/add-down.png);}");
    btn_add->setFlat(true);

    btn_updata->setGeometry(tableView->x()+650,tableView->y()+tableView->height()+30,150,40);
    btn_updata->setStyleSheet("QPushButton{border-image: url(:/picture/System/userManage/update-up.png);}"
                               "QPushButton:hover{border-image: url(:/picture/System/userManage/update-up.png);}"
                               "QPushButton:pressed{border-image: url(:/picture/System/userManage/update-down.png);}");
    btn_updata->setFlat(true);

    btn_delete->setGeometry(tableView->x()+850,tableView->y()+tableView->height()+30,150,40);
    btn_delete->setStyleSheet("QPushButton{border-image: url(:/picture/System/userManage/delete-up.png);}"
                              "QPushButton:hover{border-image: url(:/picture/System/userManage/delete-up.png);}"
                              "QPushButton:pressed{border-image: url(:/picture/System/userManage/delete-down.png);}");
    btn_delete->setFlat(true);

    btn_query->setGeometry(tableView->x()+1050,tableView->y()+tableView->height()+30,150,40);
    btn_query->setStyleSheet("QPushButton{border-image: url(:/picture/System/userManage/query-up.png);}"
                              "QPushButton:hover{border-image: url(:/picture/System/userManage/query-up.png);}"
                              "QPushButton:pressed{border-image: url(:/picture/System/userManage/query-down.png);}");
    btn_query->setFlat(true);



    connect(btn_add,SIGNAL(clicked()),this,SLOT(btn_addSlot()));
    connect(btn_updata,SIGNAL(clicked()),this,SLOT(btn_updateSlot()));
    connect(btn_delete,SIGNAL(clicked()),this,SLOT(btn_deleteSlot()));
    connect(btn_query,SIGNAL(clicked()),this,SLOT(btn_querySlot()));

}

void AdminitratorManagement::btn_addSlot()
{
    MyDialogAdd *myDialog = new MyDialogAdd(this,ADMINUSER);
    connect(myDialog,SIGNAL(siganl_please_fresh_table()),this,SLOT(fresh_table()));
    myDialog->show();
}

void AdminitratorManagement::btn_updateSlot()
{
    if(chooseFlag==-1)
    {
        myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_WARNING,tr("提示"),tr("请选择需要更改的用户！"),this);
        if(messge->exec() == QDialog::Accepted){   //模式对话框
        }

        return;
    }

    int row = chooseFlag;
    QAbstractItemModel* modelll = tableView->model();
    QString str0=modelll->data(modelll->index(row,0)).toString();//第row行第0列的内容
    QString str1=modelll->data(modelll->index(row,1)).toString();//第row行第1列的内容
    QString str2=modelll->data(modelll->index(row,2)).toString();//第row行第2列的内容
    QString str3=modelll->data(modelll->index(row,3)).toString();//第row行第3列的内容
    QString str4=modelll->data(modelll->index(row,4)).toString();//第row行第1列的内容
    QString str5=modelll->data(modelll->index(row,5)).toString();//第row行第2列的内容
    QString str6=modelll->data(modelll->index(row,6)).toString();//第row行第3列的内容
    MyDialogUpdate *myDialog = new MyDialogUpdate(this,str0,str1,str2,str3,str4,str5,str6,ADMINUSER);
    connect(myDialog,SIGNAL(siganl_please_fresh_table()),this,SLOT(fresh_table()));
    myDialog->show();
}

void AdminitratorManagement::btn_deleteSlot()
{
    if(chooseFlag!=-1)
    {

        int row = chooseFlag;
        QAbstractItemModel* modelll = tableView->model();
        QString str0=modelll->data(modelll->index(row,0)).toString();//第row行第0列的内容
        QString mbstr="是否删除管理员用户：“"+str0+"” ?";
        myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_QUESTION,tr("提示"),mbstr,this);
        if(messge->exec() == QDialog::Accepted){   //模式对话框
            AddDelUpdSel op;
            op.deleteData_AdminUser(str0);
            model->setQuery("select usrname,pwd,name,department,hospital,phone_numeber,email from administator_usrinfo;");
            tableView->setModel(model);
            chooseFlag=-1;
        }
        else
        {
            tableView->setFocus();
        }
    }
    else
    {

        myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_WARNING,tr("提示"),tr("请选择需要删除的管理员用户！"),this);
        if(messge->exec() == QDialog::Accepted){   //模式对话框

        }
    }
}

void AdminitratorManagement::btn_querySlot()
{
    myDialog_query = new MyDialogQuery(this,ADMINUSER);
    connect(myDialog_query,SIGNAL(siganl_please_fresh_table()),this,SLOT(fresh_table_select()));
    myDialog_query->show();
}

void AdminitratorManagement::fresh_table()
{
    qDebug()<<"刷新表格";
    model->setQuery("select usrname,pwd,name,department,hospital,phone_numeber,email from administator_usrinfo;");

    tableView->setModel(model);
    chooseFlag=-1;
}

void AdminitratorManagement::fresh_table_select()
{
tableView->setModel(&(myDialog_query->model));
}

void AdminitratorManagement::slot_doubleclick_tableview(const QModelIndex &index)
{
chooseFlag= index.row();
}
