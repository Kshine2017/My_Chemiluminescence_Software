 #include "databaseoperation.h"
#include "data/configfile.h"
#include <QDate>
#include <QDebug>
#include <QSqlError>
#include <QModelIndex>
/**
 * @brief DatabaseOperation::DatabaseOperation
 * 数据编码管理数据库操作类
 */
DatabaseOperation::DatabaseOperation()
{

}

bool DatabaseOperation::insertData(QString str_category, QString str_category_code, QString str_projectName, QString str_projectName_code, QString str_reagentType, QString str_reagentType_code)
{
    QSqlQuery query;
    query.prepare("insert into Reagent_Bar_Info values(?,?,?,?,?,?,?,?,?,?,?,?,?)");

    //query.bindValue(0,NULL); //主键自增
    query.bindValue(1,str_category);
    query.bindValue(2,str_category_code);
    query.bindValue(3,str_projectName);
    query.bindValue(4,str_projectName_code);
    query.bindValue(5,str_reagentType);
    query.bindValue(6,str_reagentType_code);

    QString str_four_code_reagent = str_category_code + str_projectName_code + str_reagentType_code;
    ConfigFile cp;
    QString str_create_ID =cp.getCurrentUser_Name();
    QString str_ctrate_TIME = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    QString str_modifier_id = "无";
    QString str_modifier_time = "无";
    int DEL_FLAG = 0 ;

    query.bindValue(7,str_four_code_reagent);
    query.bindValue(8,str_create_ID);
    query.bindValue(9,str_ctrate_TIME);
    query.bindValue(10,str_modifier_id);
    query.bindValue(11,str_modifier_time);
    query.bindValue(12,DEL_FLAG);//DEL_FLAG
    bool ret = query.exec();
   //------------------------------------------------------------------
    if(!ret)qDebug()<<"试剂船信息表---新增---sql语句失败！";
    else qDebug()<<"试剂船信息表---新增---sql执行成功";

    qDebug()<<query.lastError();
    return ret;


}

bool DatabaseOperation::selectCategoryAll(QSqlQueryModel &model)
{
    QString str = "select DISTINCT CATEGORY from Reagent_Bar_Info ";
    model.setQuery(str);
    return true;
}

bool DatabaseOperation::selectProjectNameAll(QSqlQueryModel &model)
{
    QString str = "select DISTINCT PROJECT_NAME from Reagent_Bar_Info ";
    model.setQuery(str);
    return true;
}

bool DatabaseOperation::selectReagentTypeAll(QSqlQueryModel &model)
{
    QString str = "select DISTINCT REAGENT_TYPE from Reagent_Bar_Info ";
    model.setQuery(str);
    return true;
}

bool DatabaseOperation::selectCategory_codeByCategory(QString strCategory, QSqlQueryModel &model)
{
    QString str = "select DISTINCT CATEGORY_CODE from Reagent_Bar_Info where CATEGORY = '";
    str += strCategory+"'";
    model.setQuery(str);

    QModelIndex index = model.index(0,0);
    QString temp_str_category_code = model.data(index).toString();

    if(temp_str_category_code != "")
    {
        return true;
    }
    return false;

}

bool DatabaseOperation::selectProject_nameByCategory(QString strCategory,QSqlQueryModel& model)
{
    QString str = "select DISTINCT PROJECT_NAME from Reagent_Bar_Info where CATEGORY = ";
    str += "'" + strCategory + "'";
    model.setQuery(str);

    return true;
}

bool DatabaseOperation::selectProject_name_codeByProject_name(QString strCategory, QString strProject_name, QSqlQueryModel &model)
{
    QString str = "select DISTINCT PROJECT_NAME_CODE from Reagent_Bar_Info where CATEGORY = ";
    str += "'" + strCategory + "'";
    str += "and PROJECT_NAME = '" + strProject_name + "'";
    model.setQuery(str);

    QModelIndex index = model.index(0,0);
    QString temp = model.data(index).toString();

    if(temp != "")
    {
        return true;
    }
    return false;
}

bool DatabaseOperation::selectReagent_typeByProject_name(QString strCategory, QString strProject_name,QSqlQueryModel& model)
{
    QString str = "select DISTINCT REAGENT_TYPE from Reagent_Bar_Info where CATEGORY = ";
    str += "'" + strCategory + "'";
    str += "and PROJECT_NAME = '" + strProject_name + "'";
    model.setQuery(str);

    QModelIndex index = model.index(0,0);
    QString temp = model.data(index).toString();
    if(temp != "")
    {
        return true;
    }
    return false;

}

bool DatabaseOperation::selectReagent_type_codeByReagent_type(QString strCategory, QString strProject_name, QString strReagent_type, QSqlQueryModel &model)
{
    QString str = "select DISTINCT REAGENT_TYPE_CODE from Reagent_Bar_Info where CATEGORY = ";
    str += "'" + strCategory + "'";
    str += "and PROJECT_NAME = '" + strProject_name + "'";
    str += "and REAGENT_TYPE = '" + strReagent_type + "'";
    model.setQuery(str);

    QModelIndex index = model.index(0,0);
    QString temp = model.data(index).toString();
    if(temp != "")
    {
        return true;
    }
    return false;
}

bool DatabaseOperation::deleteReagentData(QString str_reagent_code)
{
    QSqlQuery query;
    QString str_query = "delete from Reagent_Bar_Info where REAGENT_CODE = ";
    str_query += "'" + str_reagent_code + "'";

    return query.exec(str_query);
}

bool DatabaseOperation::selectCategoryByCategory_code(QString strCategory_code, QSqlQueryModel &model)
{
    QString str = "select DISTINCT CATEGORY from Reagent_Bar_Info where CATEGORY_CODE = '";
    str += strCategory_code+"'";
    model.setQuery(str);

    QModelIndex index = model.index(0,0);
    QString temp_str_category_code = model.data(index).toString();
    if(temp_str_category_code != "")
    {
        return true;
    }
    return false;

}

bool DatabaseOperation::selectProject_nameByProject_name_code(QString strCategory, QString strProject_name_code, QSqlQueryModel &model)
{
    QString str = "select DISTINCT PROJECT_NAME from Reagent_Bar_Info where CATEGORY = ";
    str += "'" + strCategory + "'";
    str += "and PROJECT_NAME_CODE = '" + strProject_name_code + "'";
    model.setQuery(str);

    QModelIndex index = model.index(0,0);
    QString temp_strProject_name_code = model.data(index).toString();

    if(temp_strProject_name_code != "")
    {
        return true;
    }
    return false;
}

bool DatabaseOperation::selectReagent_typeByReagent_type_code(QString strCategory, QString strProject_name, QString strReagent_type_code, QSqlQueryModel &model)
{
    QString str = "select DISTINCT REAGENT_TYPE from Reagent_Bar_Info where CATEGORY = ";
    str += "'" + strCategory + "'";
    str += "and PROJECT_NAME = '" + strProject_name + "'";
    str += "and REAGENT_TYPE_CODE = '" + strReagent_type_code + "'";
    model.setQuery(str);

    QModelIndex index = model.index(0,0);
    QString temp_strReagent_type_code = model.data(index).toString();

    if(temp_strReagent_type_code != "")
    {
        return true;
    }
    return false;

}

bool DatabaseOperation::getReagentInfoByCode(QString &str_category, QString &str_projectName, QString &str_reagentType, QString bar_code)
{

    QString str = "select DISTINCT CATEGORY,PROJECT_NAME,REAGENT_TYPE from Reagent_Bar_Info where REAGENT_CODE = '";
    str +=  bar_code.mid(0,4) + "';";
    QSqlQueryModel model;
    model.setQuery(str);
    str_category= model.index(0,0).data().toString();
    str_projectName= model.index(0,1).data().toString();
    str_reagentType= model.index(0,2).data().toString();
    return true;
}

bool DatabaseOperation::upDataCategory_codeByCategory(QString strCategory, QString strCategoryCode)
{
    QSqlQuery query;
    QString str = "select REAGENT_CODE,ID from Reagent_Bar_Info where CATEGORY = ";
    str += "'" + strCategory + "'";
    QSqlQueryModel model;
    model.setQuery(str);
    int count = model.rowCount();
    for(int i = 0;i < count;i++)
    {
        QString str_code = model.index(i,0).data().toString();
        int id = model.index(i,1).data().toInt();
        QString newStr_code = str_code.replace(0,1,strCategoryCode);
        QString queryStr = "update Reagent_Bar_Info set REAGENT_CODE = ";
        queryStr += "'" + newStr_code + "' where ID = ";
        queryStr += QString::number(id) + ";";
        query.exec(queryStr);
    }
    query.prepare("update Reagent_Bar_Info set "
                  "CATEGORY_CODE = ? "
                  "where CATEGORY = ? ;");
    query.bindValue(0,strCategoryCode);
    query.bindValue(1,strCategory);

    return query.exec();
}

bool DatabaseOperation::upDataCategoryByCategory_code(QString strCategoryCode, QString strCategory)
{
    QSqlQuery query;
    query.prepare("update Reagent_Bar_Info set "
                  "CATEGORY = ? "
                  "where CATEGORY_CODE = ? ;");
    query.bindValue(0,strCategory);
    query.bindValue(1,strCategoryCode);

    return query.exec();
}

bool DatabaseOperation::upDataProject_name_codeByProject_name(QString strCategory, QString strProject_name, QString strProject_nameCode)
{
    QSqlQuery query;
    QString str = "select REAGENT_CODE,ID from Reagent_Bar_Info where PROJECT_NAME = ";
    str += "'" + strProject_name + "'";
    str += " and CATEGORY = '"+ strCategory + "'";
    QSqlQueryModel model;
    model.setQuery(str);
    int count = model.rowCount();
    for(int i = 0;i < count;i++)
    {
        QString str_code = model.index(i,0).data().toString();
        int id = model.index(i,1).data().toInt();
        QString newStr_code = str_code.replace(1,1,strProject_nameCode);
        QString queryStr = "update Reagent_Bar_Info set REAGENT_CODE = ";
        queryStr += "'" + newStr_code + "' where ID = ";
        queryStr += QString::number(id) + ";";
        query.exec(queryStr);
    }
    query.prepare("update Reagent_Bar_Info set "
                  "PROJECT_NAME_CODE = ? "
                  "where PROJECT_NAME = ? "
                  "and CATEGORY = ? ;");
    query.bindValue(0,strProject_nameCode);
    query.bindValue(1,strProject_name);
    query.bindValue(2,strCategory);

    return query.exec();
}

bool DatabaseOperation::upDataProject_nameByProject_name_code(QString strCategory, QString strProject_nameCode, QString strProject_name)
{
    QSqlQuery query;
    query.prepare("update Reagent_Bar_Info set "
                  "PROJECT_NAME = ? "
                  "where PROJECT_NAME_CODE = ? ;");
    query.bindValue(0,strProject_name);
    query.bindValue(1,strProject_nameCode);

    return query.exec();
}

bool DatabaseOperation::upDataReagentData(QString strCategory, QString strCategoryCode,
                                          QString strProjectName, QString strProjectNameCode,
                                          QString strReagentType, QString strReagentTypeCode,QString strReagentCode)
{
    QSqlQuery query;

    QString str = "select ID from Reagent_Bar_Info where REAGENT_CODE = ";
    str += "'" + strReagentCode + "' ;";
    QSqlQueryModel model;
    model.setQuery(str);

    int id = model.index(0,0).data().toInt();
    qDebug()<<"ID-----"<<id;

    QString newReagentCode = strCategoryCode + strProjectNameCode + strReagentTypeCode;


    query.prepare("update Reagent_Bar_Info set "
                  "CATEGORY = ?,"
                  "CATEGORY_CODE = ?,"
                  "PROJECT_NAME = ?,"
                  "PROJECT_NAME_CODE = ?,"
                  "REAGENT_TYPE = ?,"
                  "REAGENT_TYPE_CODE = ?,"
                  "REAGENT_CODE = ? "
                  "where ID = ? ;");
    query.bindValue(0,strCategory);
    query.bindValue(1,strCategoryCode);
    query.bindValue(2,strProjectName);
    query.bindValue(3,strProjectNameCode);
    query.bindValue(4,strReagentType);
    query.bindValue(5,strReagentTypeCode);
    query.bindValue(6,newReagentCode);
    query.bindValue(7,id);


    qDebug()<<query.exec();
    return query.exec();
}
