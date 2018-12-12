#include "standardprogrameinfodialog.h"
#include <QHeaderView>
#include "QMessgeBox/mymessgebox.h"
#include <QDebug>

StandardProgrameInfoDialog::StandardProgrameInfoDialog(QWidget *parent) : QDialog(parent)
{
    setFixedSize(700,500);
    setWindowTitle(tr("试剂船编辑信息"));
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowModality(Qt::ApplicationModal);
    chooseFlag = -1;
    init();

    connect(tableView,SIGNAL(clicked(QModelIndex)),this,SLOT(getIndex_click_tableView_slot(QModelIndex)));
    connect(tableView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(getIndex_Double_click_tableView_slot(QModelIndex)));

    connect(btn_sure,SIGNAL(clicked()),this,SLOT(btn_sure_solt()));
    connect(btn_delete,SIGNAL(clicked()),this,SLOT(btn_delete_solt()));
    connect(btn_cancel,SIGNAL(clicked()),this,SLOT(btn_cancel_solt()));
}

/**
 * @brief StandardProgrameInfoDialog::init
 *  初始化界面
 */
void StandardProgrameInfoDialog::init()
{
    mainLayout = new QVBoxLayout(this);
    layout_btn = new QHBoxLayout();

    btn_sure = new QPushButton();   //确定按钮
    btn_sure->setFixedSize(110,44);
    btn_sure->setStyleSheet("QPushButton{border-image: url(:/picture/standardPrograme/sure-up.png);}"
                             "QPushButton:hover{border-image: url(:/picture/standardPrograme/sure-up.png);}"
                             "QPushButton:pressed{border-image: url(:/picture/standardPrograme/sure-down.png);}");


    btn_delete = new QPushButton();   //删除按钮
    btn_delete->setFixedSize(110,44);
    btn_delete->setStyleSheet("QPushButton{border-image: url(:/picture/standardPrograme/delete-up.png);}"
                                     "QPushButton:hover{border-image: url(:/picture/standardPrograme/delete-up.png);}"
                                     "QPushButton:pressed{border-image: url(:/picture/standardPrograme/delete-down.png);}");


    btn_cancel = new QPushButton();
    btn_cancel->setFixedSize(110,44);   //取消按钮
    btn_cancel->setStyleSheet("QPushButton{border-image: url(:/picture/standardPrograme/cancel-up.png);}"
                                   "QPushButton:hover{border-image: url(:/picture/standardPrograme/cancel-up.png);}"
                                   "QPushButton:pressed{border-image: url(:/picture/standardPrograme/cancel-down.png);}");

    tableView = new QTableView();
    tableView->setFixedSize(683,400);

    model = new QMySQlQueryModel();
    model->setQuery("select "
                    "ID,"
                    "ACTION_CODE,"
                    "BAR_CODE,"
                    "CREATOR_ID,"
                    "CREATE_TIME "
                    "from reagent_info;");
    model->setHeaderData(0,Qt::Horizontal,QVariant("ID"));
    model->setHeaderData(1,Qt::Horizontal,QVariant("唯一识别号"));
    model->setHeaderData(2,Qt::Horizontal,QVariant("条码"));
    model->setHeaderData(3,Qt::Horizontal,QVariant("创建者"));
    model->setHeaderData(4,Qt::Horizontal,QVariant("创建时间"));

    tableView->setModel(model);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); //使其不可编辑
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode ( QAbstractItemView::SingleSelection);
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
    tableView->verticalHeader()->setFixedWidth(21);
    //设置列宽
    tableView->setColumnWidth(0,80);
    tableView->setColumnWidth(1,100);
    tableView->setColumnWidth(2,100);
    tableView->setColumnWidth(3,100);
    tableView->setColumnWidth(4,280);
    //设置：行高
//    tableView->verticalHeader()->setDefaultSectionSize(42);
    layout_btn->addStretch(1);
    layout_btn->addWidget(btn_sure);
    layout_btn->addStretch(1);
    layout_btn->addWidget(btn_delete);
    layout_btn->addStretch(1);
    layout_btn->addWidget(btn_cancel);
    layout_btn->addStretch(1);
    mainLayout->addWidget(tableView);
    mainLayout->addLayout(layout_btn);


}
/**
 * @brief StandardProgrameInfoDialog::btn_sure_solt
 *  确定信号槽
 */
void StandardProgrameInfoDialog::btn_sure_solt()
{
    if(chooseFlag==-1)
    {
        myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_WARNING,tr("提示"),tr("请选择需要打开的项目！"),this);
        if(messge->exec() == QDialog::Accepted){   //模式对话框
        }
        return;
    }

    int row = chooseFlag;
    QAbstractItemModel* temp_model = tableView->model();
    QString str = temp_model->data(temp_model->index(row,1)).toString();//第row行第2列的内容---项目简写
    qDebug()<<"选择唯一识别号："<<str;

    emit OpenStandardInfo(str);     //发送信号至standardPragrameWidget 参数：项目简写
    chooseFlag = -1;
    this->close();

}
/**
 * @brief StandardProgrameInfoDialog::btn_delete_solt
 * 删除信号槽
 */
void StandardProgrameInfoDialog::btn_delete_solt()
{
    if(chooseFlag==-1)
    {
        myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_WARNING,tr("提示"),tr("请选择需要删除的项目！"),this);
        if(messge->exec() == QDialog::Accepted){   //模式对话框
        }
        return;
    }

    int row = chooseFlag;
    QAbstractItemModel* temp_model = tableView->model();
    QString str = temp_model->data(temp_model->index(row,1)).toString();//第row行第1列的内容---项目条码前7位
    qDebug()<<"选择项目简写："<<str;

    myMessgeBox *delete_msg = new myMessgeBox(myMessgeBox::MY_MESSAGE_QUESTION,tr("提示"),"确定要删除项目:”" + str + "”吗？",this);
    if(delete_msg->exec() == QDialog::Accepted){   //模式对话框
        //TODO
        QSqlQuery query;
        query.exec("delete from reagent_info where ACTION_CODE = '"+str+"';");
        query.exec("delete from reagent_movement where ACTION_CODE = '"+str+"';");
    }

    //删除后重新刷新表格
    model->setQuery("select "
                    "ID,"
                    "ACTION_CODE,"
                    "BAR_CODE,"
                    "CREATOR_ID,"
                    "CREATE_TIME "
                    "from reagent_info;");
    tableView->setModel(model);

    chooseFlag = -1;    //删除后表格为未选中行的状态

}
/**
 * @brief StandardProgrameInfoDialog::btn_cancel_solt
 *  取消信号槽
 */
void StandardProgrameInfoDialog::btn_cancel_solt()
{
    this->close();
}
/**
 * @brief StandardProgrameInfoDialog::getIndex_click_tableView_slot
 * @param index
 *  获取当前选择的行数，如未选择，会默认为-1；
 */
void StandardProgrameInfoDialog::getIndex_click_tableView_slot(const QModelIndex &index)
{
    chooseFlag= index.row();
}

void StandardProgrameInfoDialog::getIndex_Double_click_tableView_slot(const QModelIndex &index)
{
    chooseFlag= index.row();
    if(chooseFlag==-1)
    {
        myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_WARNING,tr("提示"),tr("请选择需要打开的项目！"),this);
        if(messge->exec() == QDialog::Accepted){   //模式对话框
        }
        return;
    }
    int row = chooseFlag;
    QAbstractItemModel* temp_model = tableView->model();
    QString str = temp_model->data(temp_model->index(row,1)).toString();//第row行第2列的内容---项目简写
    qDebug()<<"选择项目条码前7位："<<str;

    emit OpenStandardInfo(str);     //发送信号至standardPragrameWidget 参数：项目简写
    chooseFlag = -1;
    this->close();

}
