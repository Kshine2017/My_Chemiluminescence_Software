#include "exportimportexcel.h"
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QModelIndex>
#include "dataopration.h"
//#include <sapi.h>
#include "qt_windows.h"
#include "../standardTestWidget/dataopationstandardtest.h"
#include <QMessageBox>

ExportImportExcel::ExportImportExcel(QWidget *parent)
:QDialog(parent)
{

    qDebug()<<"创建导出导入文件的对象";
    this->move(-1920,-1080);
    //设置透明度
   this->setWindowOpacity(0.6);
    //取消对话框标题
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    this->setStyleSheet("background-color:transparent;");
//    HRESULT r = OleInitialize(0);
//    if (r != S_OK && r != S_FALSE)
//    {qWarning("Qt:初始化Ole失败（error %x）",(unsigned int)r);}

    //设置背景色为淡蓝色,顶层窗口做不出圆角来
    background = new QFrame(this);
    background->setStyleSheet("background-color: rgb(200, 200,200);border-radius:10px;");
    background->setGeometry(0, 0, 1920, 1080);

//    label = new QLabel(background);
//   label->setStyleSheet("background-color:transparent;");
//   label->setGeometry(0, 0, 1920, 1080);
//    movie = new QMovie(":/picture/menu/waitgif.gif");
//   label->setScaledContents(true);
//   label->setMovie(movie);

   tip_label = new QLabel(background);
   tip_label->setText("等待执行命令。。。");
   tip_label->setStyleSheet("color: black;background-color: transparent;");
   tip_label->setGeometry(1800,1000, 120, 80);

   show();
}
void ExportImportExcel::ExportDialog()
{
    qDebug()<<"【点击按钮】---导出文件";
    QString fileName = QFileDialog::getSaveFileName(this,tr("导出"),"",tr("Excel 2007 (*.xlsx);;Excel 97-2003 (*.xls);;CSV (*.csv)"));
    if(!fileName.isNull())
    {
        this->move(0,0);
        onExportExcel(fileName);
    }
    else //取消
    {

    }

}

void ExportImportExcel::ImportDialog()
{
    qDebug()<<"【点击按钮】---导入文件";
    QString fileName = QFileDialog::getOpenFileName(this,tr("导入"),"",tr("Excel 2007 (*.xlsx);;Excel 97-2003 (*.xls);;CSV (*.csv)"));
    if(!fileName.isNull())
    {
        this->move(0,0);
        onImportExcel(fileName);
    }
    else //取消
    {

    }


}

ExportImportExcel::~ExportImportExcel()
{
    qDebug()<<"释放导出导入文件的对象";

}

void ExportImportExcel::onImportExcel(QString filePath)
{
    QAxObject excel;//("Excel.Application");
    bool ret = excel.setControl("Excel.Application");
    qDebug()<<"----"<<ret;
    if(!ret)//如果连接excel空间失败
    {

        QMessageBox::critical(this,tr("提示"),tr("连接Excel控件失败，建议 安装WPS个人版 或者 购买安装正版微软office！"));
        return;

    }
    excel.setProperty("Visible", false);
    QAxObject *work_books = excel.querySubObject("WorkBooks");
    work_books->dynamicCall("Open (const QString&)",  QDir::toNativeSeparators(filePath));
    QAxObject *work_book = excel.querySubObject("ActiveWorkBook");
    DATAtoBase_0517(work_book);
    work_book->dynamicCall("Close(Boolean)", false);  //关闭文件
    excel.dynamicCall("Quit(void)");  //退出
}

void ExportImportExcel::onExportExcel(QString filePath)
{
//    HRESULT r = OleInitialize(0);
//    if (r != S_OK && r != S_FALSE) {
//        qWarning("Qt: Could not initialize OLE (error %x)", (unsigned int)r);
//    }
    QAxObject excel;//("Excel.Application");
    bool ret = excel.setControl("Excel.Application");
    qDebug()<<"1、Excel控件 连接情况："<<ret;
    if(!ret)//如果连接excel空间失败
    {

        QMessageBox::critical(this,tr("提示"),tr("连接Excel控件失败，建议 安装WPS个人版 或者 购买安装正版微软office！"));
        return;

    }
//    OleUninitialize();
    excel.setProperty("Visible", false);
    excel.setProperty("DisplayAlerts", false);
    QAxObject *work_books = excel.querySubObject("WorkBooks");
    QAxObject *work_book = NULL;

    QFile xlsFile(filePath);
    qDebug()<<filePath;
    if (xlsFile.exists())
    {
        work_book = work_books->querySubObject("Open(const QString &)", QDir::toNativeSeparators(filePath));
    }
    else
    {
        work_books->dynamicCall("Add");
        work_book = excel.querySubObject("ActiveWorkBook");
    }
    DATAtoExcel_0517(work_book);
    qDebug()<<"数据已写入excel!";
    //===============================================================================================
    work_book->dynamicCall("SaveAs(const QString &)", QDir::toNativeSeparators(filePath));
    qDebug()<<"已保存";
    work_book->dynamicCall("Close(Boolean)", false);  //关闭文件
    qDebug()<<"已关闭文件";
    excel.dynamicCall("Quit(void)");  //退出
    qDebug()<<"已退出Excel控件";
}


void ExportImportExcel::DATAtoExcel_0517(QAxObject *work_book)
{
    if(work_book==NULL)
    {
        qDebug()<<"work_book is NULL!";
        return;
    }
    qDebug()<<"2、work_book is "<<work_book;
    QSqlQueryModel model;
    model.setQuery("select * from reagent_info;");
    int columnNumber=model.columnCount();
    int rowNumber=model.rowCount();
    //----------得到标题名称-------------------

    //qDebug()<<model.headerData(2,Qt::Horizontal).toString();
    //---------------------------------------
    QAxObject *work_sheets = work_book->querySubObject("Sheets");//默认有一张表1
    work_sheets->querySubObject("Add()");//表2
    work_sheets->querySubObject("Add()");//表3
    qDebug()<<"3、work_sheets is "<<work_sheets;
    QAxObject *first_sheet = work_sheets->querySubObject("Item(int)", 1);
    qDebug()<<"3.1、first_sheet is "<<first_sheet;
    first_sheet->setProperty("Name","试剂船信息表");
    QAxObject *cell ;
    //写入栏目名
    for(int i=0;i<columnNumber;i++)
    {
        cell = first_sheet->querySubObject("Cells(int,int)", 1, i+1);
        cell->setProperty("Value",model.headerData(i,Qt::Horizontal).toString());
        cell->dynamicCall("SetValue(const QVariant&)",model.headerData(i,Qt::Horizontal));
    }
    //写入数据
    for(int i=0;i<rowNumber;i++)
        for(int j=0;j<columnNumber;j++)
        {

            cell = first_sheet->querySubObject("Cells(int,int)", i+2, j+1);
            cell->setProperty("Value", model.data(model.index(i,j)));
            cell->dynamicCall("SetValue(const QVariant&)",model.data(model.index(i,j)));
        }


    qDebug()<<"已完成第一页表格数据";
    QAxObject *second_sheet = work_sheets->querySubObject("Item(int)", 2);
    second_sheet->setProperty("Name","试剂船动作方案表");
    qDebug()<<"3.2、second_sheet is "<<second_sheet;
    model.setQuery("select * from reagent_movement;");
    columnNumber=model.columnCount();
    rowNumber=model.rowCount();
    //写入栏目名
    for(int i=0;i<columnNumber;i++)
    {
        cell = second_sheet->querySubObject("Cells(int,int)", 1, i+1);
        cell->setProperty("Value",model.headerData(i,Qt::Horizontal).toString());
        cell->dynamicCall("SetValue(const QVariant&)",model.headerData(i,Qt::Horizontal));
    }
    //写入数据
    for(int i=0;i<rowNumber;i++)
        for(int j=0;j<columnNumber;j++)
        {
            cell = second_sheet->querySubObject("Cells(int,int)", i+2, j+1);
            cell->setProperty("Value", model.data(model.index(i,j)));
            cell->dynamicCall("SetValue(const QVariant&)",model.data(model.index(i,j)));
        }

    qDebug()<<"已完成第二页表格数据";
    QAxObject *third_sheet = work_sheets->querySubObject("Item(int)", 3);
    third_sheet->setProperty("Name","试剂船标准品信息表");
     qDebug()<<"3.3、third_sheet is "<<third_sheet;
    model.setQuery("select * from reagent_standard_info;");
    columnNumber=model.columnCount();
    rowNumber=model.rowCount();
    //写入栏目名
    for(int i=0;i<columnNumber;i++)
    {
        cell = third_sheet->querySubObject("Cells(int,int)", 1, i+1);
        cell->setProperty("Value",model.headerData(i,Qt::Horizontal).toString());
        cell->dynamicCall("SetValue(const QVariant&)",model.headerData(i,Qt::Horizontal));
    }
    //写入数据
    for(int i=0;i<rowNumber;i++)
        for(int j=0;j<columnNumber;j++)
        {
            cell = third_sheet->querySubObject("Cells(int,int)", i+2, j+1);
            cell->setProperty("Value", model.data(model.index(i,j)));
            cell->dynamicCall("SetValue(const QVariant&)",model.data(model.index(i,j)));
        }
    qDebug()<<"已完成第三页表格数据";


}

void ExportImportExcel::DATAtoBase_0517(QAxObject *work_book)
{
    if(work_book==NULL)
    {
        qDebug()<<"work_book is NULL!";
        return;
    }
    qDebug()<<"work_book is "<<work_book;
    QAxObject *work_sheets = work_book->querySubObject("Sheets");
    int sheet_count = work_sheets->property("Count").toInt();  //获取工作表数目
    if(sheet_count > 0)
    {
        QAxObject *work_sheet = work_book->querySubObject("Sheets(int)", 1);//reagent_info
        QAxObject *used_range = work_sheet->querySubObject("UsedRange");
        QAxObject *rows = used_range->querySubObject("Rows");
        int row_number = rows->property("Count").toInt()-1;  //获取行数
        //qDebug()<<"表1有 "<<row_number<<" 个数据";
        if(row_number<0)row_number=0;
        for(int i=0;i<row_number;i++)//多条数据+循环写入
        {
            //1.1数据准备
            QString CATEGORY        =   work_sheet->querySubObject("Cells(int,int)", i+2, 2)->dynamicCall("Value").toString();                       //质控品 标准品 校验品
            QString PROJECT_NAME    =   work_sheet->querySubObject("Cells(int,int)", i+2, 3)->dynamicCall("Value").toString();
            QString REAGENT_TYPE    =   work_sheet->querySubObject("Cells(int,int)", i+2, 4)->dynamicCall("Value").toString();  //PCT ...
            QString PRODUCTION_TIME =   work_sheet->querySubObject("Cells(int,int)", i+2, 5)->dynamicCall("Value").toString();
            int BACH_NUMBER         =   work_sheet->querySubObject("Cells(int,int)", i+2, 6)->dynamicCall("Value").toInt(); //01批 对应 0
            int QUALITY_TIME        =   work_sheet->querySubObject("Cells(int,int)", i+2, 7)->dynamicCall("Value").toInt();;                 //(i+1)*6  有6和12个月
            QString RESERVE         =   work_sheet->querySubObject("Cells(int,int)", i+2, 8)->dynamicCall("Value").toString();;         //预留
            QString BAR_CODE        =   work_sheet->querySubObject("Cells(int,int)", i+2, 9)->dynamicCall("Value").toString();;                             //条码
            QStringList strlist ;

            //第10列 到第 57列 共48个
            for(int j=0;j<48;j++)
                strlist.append(work_sheet->querySubObject("Cells(int,int)", i+2, j+10)->dynamicCall("Value").toString());

            QString STANDARD_CODE = work_sheet->querySubObject("Cells(int,int)", i+2, 58)->dynamicCall("Value").toString();
            QString ACTION_CODE =   work_sheet->querySubObject("Cells(int,int)", i+2, 59)->dynamicCall("Value").toString();
            qDebug()<<"@@@1168";
            /*****************************************************/
            QString RUN_DATA = work_sheet->querySubObject("Cells(int,int)", i+2, 60)->dynamicCall("Value").toString();//待发送的到下位机的当前试剂有运行的全部数据
            QString Create_ID =work_sheet->querySubObject("Cells(int,int)", i+2, 61)->dynamicCall("Value").toString();
            QString Create_TIME =work_sheet->querySubObject("Cells(int,int)", i+2, 62)->dynamicCall("Value").toString();
            QString Modify_ID=work_sheet->querySubObject("Cells(int,int)", i+2, 63)->dynamicCall("Value").toString();
            QString Modify_TIME=work_sheet->querySubObject("Cells(int,int)", i+2, 64)->dynamicCall("Value").toString();
            int DEL_FLAG=work_sheet->querySubObject("Cells(int,int)", i+2, 65)->dynamicCall("Value").toInt();

            //判断是否已有
            DataOpration dp;
            if(dp.isExist_reagentInfo(STANDARD_CODE))
                {
                dp.updateData_reagentInfo(CATEGORY,PROJECT_NAME,REAGENT_TYPE,PRODUCTION_TIME,BACH_NUMBER,QUALITY_TIME,RESERVE,BAR_CODE,strlist,STANDARD_CODE,ACTION_CODE,RUN_DATA,Modify_ID,Modify_TIME,DEL_FLAG);
                //qDebug()<<"试剂船信息表: 第"<<i+1<<"条数据 已存在！";
            }else
                dp.insertData_reagentInfo(CATEGORY,PROJECT_NAME,REAGENT_TYPE,PRODUCTION_TIME,BACH_NUMBER,QUALITY_TIME,RESERVE,BAR_CODE,strlist,STANDARD_CODE,ACTION_CODE,RUN_DATA,Create_ID,Create_TIME,Modify_ID,Modify_TIME,DEL_FLAG);

        }

        work_sheet = work_book->querySubObject("Sheets(int)", 2);//reagent_movement
        used_range = work_sheet->querySubObject("UsedRange");
        rows = used_range->querySubObject("Rows");
        row_number = rows->property("Count").toInt()-1;  //获取行数
        //qDebug()<<"表2有 "<<row_number<<" 个数据";
        if(row_number<0)row_number=0;

        for(int i=0;i<row_number;i++)//多条数据+循环写入
        {

            int CHOOSE_FLAG=work_sheet->querySubObject("Cells(int,int)", i+2, 2)->dynamicCall("Value").toInt();
            QString ACTION_CODE= work_sheet->querySubObject("Cells(int,int)", i+2, 3)->dynamicCall("Value").toString();
            int STEP_num=work_sheet->querySubObject("Cells(int,int)", i+2, 4)->dynamicCall("Value").toInt();

            QString STEP_name=work_sheet->querySubObject("Cells(int,int)", i+2, 5)->dynamicCall("Value").toString();;
            QString START_POSTION=work_sheet->querySubObject("Cells(int,int)", i+2,6)->dynamicCall("Value").toString();
            QString PUT_IN_POSTION=work_sheet->querySubObject("Cells(int,int)", i+2, 7)->dynamicCall("Value").toString();;

            int TIME=work_sheet->querySubObject("Cells(int,int)", i+2, 8)->dynamicCall("Value").toInt();
            int BEFORE_BLEND_COUNT=work_sheet->querySubObject("Cells(int,int)", i+2,9)->dynamicCall("Value").toInt();
            int AFTER_BLEND_COUNT=work_sheet->querySubObject("Cells(int,int)", i+2,10)->dynamicCall("Value").toInt();
            int CAPACITY=work_sheet->querySubObject("Cells(int,int)", i+2, 11)->dynamicCall("Value").toInt();
            int STEP_TIME=work_sheet->querySubObject("Cells(int,int)", i+2, 12)->dynamicCall("Value").toInt();

            QString Create_ID =work_sheet->querySubObject("Cells(int,int)", i+2, 13)->dynamicCall("Value").toString();
            QString Create_TIME =work_sheet->querySubObject("Cells(int,int)", i+2, 14)->dynamicCall("Value").toString();
            QString Modify_ID=work_sheet->querySubObject("Cells(int,int)", i+2, 15)->dynamicCall("Value").toString();
            QString Modify_TIME=work_sheet->querySubObject("Cells(int,int)", i+2, 16)->dynamicCall("Value").toString();

            int DEL_FLAG=work_sheet->querySubObject("Cells(int,int)", i+2, 17)->dynamicCall("Value").toInt();
            DataOpration dp;
            if(!dp.isExist_reagentMovement(STEP_num,ACTION_CODE))
            {
                dp.insertData_reagentMovement(CHOOSE_FLAG,ACTION_CODE,STEP_num,STEP_name,START_POSTION,
                                                 PUT_IN_POSTION,TIME,BEFORE_BLEND_COUNT, AFTER_BLEND_COUNT,
                                                 CAPACITY,STEP_TIME,Create_ID,Create_TIME,Modify_ID,Modify_TIME,DEL_FLAG);
            }
            else
            {
                //qDebug()<<"试剂船动作表: 第"<<i+1<<"条数据 已存在！";
                dp.updateData_reagentMovement(CHOOSE_FLAG,ACTION_CODE,STEP_num,START_POSTION,
                                                 PUT_IN_POSTION,TIME,BEFORE_BLEND_COUNT, AFTER_BLEND_COUNT,
                                                 CAPACITY,STEP_TIME,Modify_ID,Modify_TIME,DEL_FLAG);
            }
        }

        work_sheet = work_book->querySubObject("Sheets(int)", 3);//standard_info
        used_range = work_sheet->querySubObject("UsedRange");
        rows = used_range->querySubObject("Rows");
        row_number = rows->property("Count").toInt()-1;  //获取行数
        if(row_number<0)row_number=0;
        //qDebug()<<"表3有 "<<row_number<<" 个数据";
        for(int i=0;i<row_number;i++)//多条数据+循环写入
        {

            //1.数据准备
            QString  STANDARD_CODE          =   work_sheet->querySubObject("Cells(int,int)", i+2,2)->dynamicCall("Value").toString();
            QStringList strlist;//存储12个点的CP值
            //3~26
            for(int i=0;i<24;i++)
                strlist.append(work_sheet->querySubObject("Cells(int,int)", i+3,2)->dynamicCall("Value").toString());
            QString CREATOR_ID              =   work_sheet->querySubObject("Cells(int,int)", i+2,27)->dynamicCall("Value").toString();
            QString CREATE_TIME             =   work_sheet->querySubObject("Cells(int,int)", i+2,28)->dynamicCall("Value").toString();
            QString MODIFIER_ID             =   work_sheet->querySubObject("Cells(int,int)", i+2,29)->dynamicCall("Value").toString();
            QString MODIFY_TIME             =   work_sheet->querySubObject("Cells(int,int)", i+2,30)->dynamicCall("Value").toString();
            char    DEL_FLAG                =   work_sheet->querySubObject("Cells(int,int)", i+2,31)->dynamicCall("Value").toInt();

            DataOpationStandardtest dost;
            if(dost.isExist_reagent_standard_info(STANDARD_CODE))
            {
               // qDebug()<<"标准品表: 第"<<i+1<<"条数据 已存在！";
                dost.deleteData_reagent_standard_info(STANDARD_CODE);
            }
            dost.insertData_reagent_standard_info(STANDARD_CODE,
                                                     strlist,
                                                     CREATOR_ID,
                                                     CREATE_TIME,
                                                     MODIFIER_ID,
                                                     MODIFY_TIME,
                                                     DEL_FLAG);


        }


    }

}
