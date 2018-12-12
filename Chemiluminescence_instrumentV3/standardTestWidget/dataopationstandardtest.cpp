#include "dataopationstandardtest.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

DataOpationStandardtest::DataOpationStandardtest()
{

}


bool DataOpationStandardtest::insertData_standard_info(
        const QString &STANDARD_CODE,
        const QString &CATEGORY,
        const QString &PROJECT_NAME,
        const QString &REAGENT_TYPE,
        const QString &BAR_CODE,
        double STANDARD_CONCENTRATION,
        const QString &START_DATE,
        const QString &END_DATE,
        char STANDARD_FLAG,
        int PHOTON_VALUE,
        double CONCENTRATION,
        double VARIANCE_COEFFICENT,
        const QString &CREATOR_ID,
        const QString &CREATE_TIME,
        const QString &MODIFIER_ID,
        const QString &MODIFY_TIME,
        char DEL_FLAG)
{
    QSqlQuery query;
    query.prepare("insert into standard_info values("
                  "?,?,?,?,?,?,?,?,?,?,"
                  "?,?,?,?,?,?,?,?);");//17
    //query.bindValue(0,NULL); //主键自增
    query.bindValue(1,STANDARD_CODE);
    query.bindValue(2,CATEGORY);
    query.bindValue(3,PROJECT_NAME);
    query.bindValue(4,REAGENT_TYPE);
    query.bindValue(5,BAR_CODE);
    query.bindValue(6,STANDARD_CONCENTRATION);
    query.bindValue(7,START_DATE);
    query.bindValue(8,END_DATE);
    query.bindValue(9,STANDARD_FLAG);
    query.bindValue(10,PHOTON_VALUE);
    query.bindValue(11,CONCENTRATION);
    query.bindValue(12,VARIANCE_COEFFICENT);
    query.bindValue(13,CREATOR_ID);
    query.bindValue(14,CREATE_TIME);
    query.bindValue(15,MODIFIER_ID);
    query.bindValue(16,MODIFY_TIME);
    query.bindValue(17,DEL_FLAG);
    bool ret = query.exec();
   //------------------------------------------------------------------
    if(!ret)qDebug()<<"标准品测试---新增---sql语句失败！"<<query.lastError();
    else qDebug()<<"标准品测试---新增---sql执行成功";
    return ret;
}

bool DataOpationStandardtest::insertData_reagent_standard_info(const QString &STANDARD_CODE, const QStringList &strlist, const QString &CREATOR_ID, const QString &CREATE_TIME, const QString &MODIFIER_ID, const QString &MODIFY_TIME, char DEL_FLAG)
{

    QSqlQuery query;
    query.prepare("insert into reagent_standard_info values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?);");
    //query.bindValue(0,NULL); //主键自增
      query.bindValue(1,STANDARD_CODE);
      //2~25

      //2~2+strlist.length()-1
      for(int i=0;i<strlist.length();i++)
      {
        if(i%2==0)
        {
            qDebug()<<"ooo"<<i+2<<"(double)";
            query.bindValue(2+i,strlist.at(i).toDouble());
        }
        else
        {
            qDebug()<<"ooo"<<i+2<<"(int)";
            query.bindValue(2+i,strlist.at(i).toInt());
        }


      }
      //2+strlist.length()~25
      for(int i=2+strlist.length();i<=25;i++)
      {
           query.bindValue(i,0);
           qDebug()<<"---"<<i;
      }
      //
      query.bindValue(26,CREATOR_ID);
      query.bindValue(27,CREATE_TIME);
      query.bindValue(28,MODIFIER_ID);
      query.bindValue(29,MODIFY_TIME);
      query.bindValue(30,DEL_FLAG);//DEL_FLAG
    bool ret = query.exec();
   //------------------------------------------------------------------
    if(!ret)
        qDebug()<<"标准品测试(12点表)---新增---sql语句失败！"<<query.lastError();
    else
        qDebug()<<"标准品测试((12点表))---新增---sql执行成功";
    return ret;




}


bool DataOpationStandardtest::isExist_standard_info(const QString &STANDARD_CODE)
{
    QSqlQuery query;
    query.exec("select STANDARD_CODE from standard_info where STANDARD_CODE = ?;");
    query.bindValue(0,STANDARD_CODE,QSql::Out);
    query.exec();
    while(query.next()){
        return true;
    }
    return false;
}

bool DataOpationStandardtest::isExist_reagent_standard_info(const QString &STANDARD_CODE)
{
    QSqlQuery query;
    query.exec("select STANDARD_CODE from reagent_standard_info where STANDARD_CODE = ?;");
    query.bindValue(0,STANDARD_CODE,QSql::Out);
    query.exec();
    while(query.next()){
        return true;
    }
    return false;
}


bool DataOpationStandardtest::deleteData_standard_info(const QString &STANDARD_CODE)
{
    QSqlQuery query;
    query.exec("delete from standard_info where STANDARD_CODE = ?;");
    query.bindValue(0,STANDARD_CODE,QSql::Out);
    bool ret = query.exec();
   //------------------------------------------------------------------
    if(!ret)qDebug()<<"标准品测试---删除---sql语句失败！"<<query.lastError();
    else qDebug()<<"标准品测试---删除---sql执行成功";
    return ret;

}

bool DataOpationStandardtest::deleteData_reagent_standard_info(const QString &STANDARD_CODE)
{
    QSqlQuery query;
    query.exec("delete from reagent_standard_info where STANDARD_CODE = ?;");
    query.bindValue(0,STANDARD_CODE,QSql::Out);
    bool ret = query.exec();
   //------------------------------------------------------------------
    if(!ret)qDebug()<<"标准品测试(12点)---删除---sql语句失败！"<<query.lastError();
    else qDebug()<<"标准品测试(12点)---删除---sql执行成功";
    return ret;
}

