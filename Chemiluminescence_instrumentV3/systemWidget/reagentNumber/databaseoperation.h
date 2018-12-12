#ifndef DATABASEOPERATION_H
#define DATABASEOPERATION_H

#include"../qmysqlquerymodel.h"


/**
 * @brief The DatabaseOperation class
 * 试剂条码编码信息表数据库操作类
 */
class DatabaseOperation
{
public:
    DatabaseOperation();

    //插入新的试剂条码编码信息
    bool insertData(QString str_category, QString str_category_code, QString str_projectName, QString str_projectName_code, QString str_reagentType, QString str_reagentType_code);
    //查找所有的品类信息
    bool selectCategoryAll(QSqlQueryModel &model);
    //查找所有的项目名称信息
    bool selectProjectNameAll(QSqlQueryModel &model);
    //查找所有的试剂种类信息
    bool selectReagentTypeAll(QSqlQueryModel &model);


    //根据品类名称查找品类编码
    bool selectCategory_codeByCategory(QString strCategory,QSqlQueryModel& model);
    //根据品类名称查找当前品类下所有的项目名称
    bool selectProject_nameByCategory(QString strCategory, QSqlQueryModel &model);
    //根据项目名称查找该项名称对应的编码
    bool selectProject_name_codeByProject_name(QString strCategory,QString strProject_name,QSqlQueryModel& model);
    //根据项目名称查找该项名称下所有的试剂种类
    bool selectReagent_typeByProject_name(QString strCategory, QString strProject_name, QSqlQueryModel &model);
    //根据试剂种类查找该试剂种类对应的编码
    bool selectReagent_type_codeByReagent_type(QString strCategory,QString strProject_name,QString strReagent_type,QSqlQueryModel& model);

    //删除试剂编码信息----根据四位编码
    bool deleteReagentData(QString str_reagent_code);

    //根据品类编码查找该编码对应的试剂品类
    bool selectCategoryByCategory_code(QString strCategory_code,QSqlQueryModel& model);
    //根据项目名称编码查找该编码对应的项目名称
    bool selectProject_nameByProject_name_code(QString strCategory, QString strProject_name_code, QSqlQueryModel& model);
    //根据试剂种类编码查找该编码对应的试剂种类
    bool selectReagent_typeByReagent_type_code(QString strCategory, QString strProject_name, QString strReagent_type_code, QSqlQueryModel &model);

    //根据四位编码查询对应的试剂品类、项目名称、试剂种类。
    bool getReagentInfoByCode(QString &str_category,QString &str_projectName,QString &str_reagentType,QString bar_code);

    //更新品类编码，品类名称不改变
    bool upDataCategory_codeByCategory(QString strCategory,QString strCategoryCode);
    //更新实际品类名称，品类编码不改变
    bool upDataCategoryByCategory_code(QString strCategoryCode,QString strCategory);

    //更新品类编码，品类名称不改变
    bool upDataProject_name_codeByProject_name(QString strCategory,QString strProject_name,QString strProject_nameCode);
    //更新实际品类名称，品类编码不改变
    bool upDataProject_nameByProject_name_code(QString strCategory,QString strProject_nameCode,QString strProject_name);

    //更新单条试剂编码信息---根据原四位编码
    bool upDataReagentData(QString strCategory, QString strCategoryCode
                           , QString strProjectName, QString strProjectNameCode
                           , QString strReagentType, QString strReagentTypeCode, QString strReagentCode);


};

#endif // DATABASEOPERATION_H
