#include "dataopration.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
DataOpration::DataOpration()
{

}

bool DataOpration::insertData_reagentInfo(const QString &CATEGORY,
                                          const QString &PROJECT_NAME,
                                          const QString &REAGENT_TYPE,
                                          const QString &PRODUCTION_TIME,
                                          int BACH_NUMBER,
                                          int QUALITY_TIME,
                                          const QString &RESERVE,
                                          const QString &BAR_CODE,
                                          const QStringList &strlist,
                                          const QString &STANDARD_CODE,
                                          const QString &ACTION_CODE,
                                          const QString &RUN_DATA,
                                          const QString &CREATOR_ID,
                                          const QString &CREATE_TIME,
                                          const QString &MODIFIER_ID,
                                          const QString &MODIFY_TIME,
                                          int DEL_FLAG)
{
    QSqlQuery query;

    query.prepare("insert into reagent_info values("
                  "?,?,?,?,?,?,?,?,?,?,"
                  "?,?,?,?,?,?,?,?,?,?,"
                  "?,?,?,?,?,?,?,?,?,?,"
                  "?,?,?,?,?,?,?,?,?,?,"
                  "?,?,?,?,?,?,?,?,?,?,"
                  "?,?,?,?,?,?,?,?,?,?,"
                  "?,?,?,?,?);");

    //query.bindValue(0,NULL); //主键自增
    query.bindValue(1,CATEGORY);
    query.bindValue(2,PROJECT_NAME);
    query.bindValue(3,REAGENT_TYPE);
    query.bindValue(4,PRODUCTION_TIME);
    query.bindValue(5,BACH_NUMBER);
    query.bindValue(6,QUALITY_TIME);
    query.bindValue(7,RESERVE);
    query.bindValue(8,BAR_CODE);
    //9~56 共48个，16x3
    for(int i=0;i<16;i++) //14个试剂船位置
    {
        query.bindValue(9+i*3,strlist.at(i*3).toDouble()); //x轴位置
        query.bindValue(9+i*3+1,strlist.at(i*3+1).toDouble()); //y轴位置
        query.bindValue(9+i*3+2,strlist.at(i*3+2).toInt()); //容量
    }
    query.bindValue(57,STANDARD_CODE);
    query.bindValue(58,ACTION_CODE);
    query.bindValue(59,RUN_DATA);
    query.bindValue(60,CREATOR_ID);
    query.bindValue(61,CREATE_TIME);
    query.bindValue(62,MODIFIER_ID);
    query.bindValue(63,MODIFY_TIME);
    query.bindValue(64,DEL_FLAG);//DEL_FLAG

    bool ret = query.exec();
   //------------------------------------------------------------------
    if(!ret)
        qDebug()<<"试剂船信息表---新增---sql语句失败！";
    else
        qDebug()<<"试剂船信息表---新增---sql执行成功";

    qDebug()<<query.lastError();
    return ret;
}




bool DataOpration::isExist_reagentInfo(const QString &STANDARD_CODE)
{
    QSqlQuery query;
    query.exec("select STANDARD_CODE from reagent_info where STANDARD_CODE = ?;");
    query.bindValue(0,STANDARD_CODE,QSql::Out);
    query.exec();
    while(query.next()){
        qDebug() << "当前项目信息已经存在"<<STANDARD_CODE;
        return true;
    }
     qDebug() << "当前项目信息不存在"<<STANDARD_CODE;
     return false;


}

bool DataOpration::updateData_reagentInfo(
        const QString &CATEGORY,
        const QString &PROJECT_NAME,
        const QString &REAGENT_TYPE,
        const QString &PRODUCTION_TIME,
        int BACH_NUMBER,


        int QUALITY_TIME,
        const QString &RESERVE,
        const QString &BAR_CODE,

        const QStringList &strlist,

        const QString &STANDARD_CODE,
        const QString &ACTION_CODE,
        const QString &RUN_DATA,
        const QString &MODIFIER_ID,
        const QString &MODIFY_TIME,
        int DEL_FLAG)
{
    QSqlQuery query;

    query.prepare("update reagent_info set "
                  "QUALITY_TIME     =?,"
                  "RESERVE          =?,"
                  "BAR_CODE         =?,"
                  "RUBBTION_X_POS=?,"
                  "RUBBTION_Y_POS= ?,"
                  "RUBBTION_CAPACITY= ?,"
                  "TP1_X_POS= ?,"
                  "TP1_Y_POS= ?,"
                  "TP1_CAPACITY= ?,"
                  "TP2_X_POS= ?,"
                  "TP2_Y_POS= ?,"
                  "TP2_CAPACITY= ?,"
                  "TP3_X_POS= ?,"
                  "TP3_Y_POS= ?,"
                  "TP3_CAPACITY= ?,"
                  "TP4_X_POS= ?,"
                  "TP4_Y_POS= ?,"
                  "TP4_CAPACITY= ?,"
                  "PREEXCITATION_FLUID_X_POS= ?,"
                  "PREEXCITATION_FLUID_Y_POS= ?,"
                  "PREEXCITATION_FLUID_CAPACITY= ?,"
                  "EXCITATION_FLUID_X_POS= ?,"
                  "EXCITATION_FLUID_Y_POS= ?,"
                  "EXCITATION_FLUID_CAPACITY= ?,"
                  "WASH3_X_POS= ?,"
                  "WASH3_Y_POS= ?,"
                  "WASH3_CAPACITY= ?,"
                  "WASH2_X_POS= ?,"
                  "WASH2_Y_POS= ?,"
                  "WASH2_CAPACITY= ?,"
                  "WASH1_X_POS= ?,"
                  "WASH1_Y_POS= ?,"
                  "WASH1_CAPACITY= ?,"
                  "MAGNETIC_X_POS= ?,"
                  "MAGNETIC_Y_POS= ?,"
                  "MAGNETIC_CAPACITY= ?,"
                  "RESERVE_X_POS= ?,"
                  "RESERVE_Y_POS= ?,"
                  "RESERVE_CAPACITY= ?,"
                  "BIOTIN_X_POS= ?,"
                  "BIOTIN_Y_POS= ?,"
                  "BIOTIN_CAPACITY= ?,"
                  "ACRIDINE_ESTER_X_POS= ?,"
                  "ACRIDINE_ESTER_Y_POS= ?,"
                  "ACRIDINE_ESTER_CAPACITY= ?,"
                  "REACTION1_TUBE_X_POS= ?,"
                  "REACTION1_TUBE_Y_POS= ?,"
                  "REACTION1_TUBE_CAPACITY= ?,"
                  "PLASMA_X_POS= ?,"
                  "PLASMA_Y_POS= ?,"
                  "PLASMA_CAPACITY= ?,"
                  "STANDARD_CODE= ?,"
                  "ACTION_CODE= ?,"
                  "RUN_DATA = ?,"
                  "MODIFIER_ID= ?,"
                  "MODIFY_TIME= ?,"
                  "DEL_FLAG = ? "
                  "where CATEGORY= ? "
                  "and PROJECT_NAME =? "
                  "and REAGENT_TYPE =? "
                  "and PRODUCTION_TIME =?"
                  "and BACH_NUMBER=?;");

    query.bindValue(0,QUALITY_TIME);
    query.bindValue(1,RESERVE);
    query.bindValue(2,BAR_CODE);

    //3~50 共48个，16x3
    for(int i=0;i<16;i++)               //14个试剂船位置
    {
        query.bindValue(3+i*3,strlist.at(i*3).toDouble()); //x轴位置
        query.bindValue(3+i*3+1,strlist.at(i*3+1).toDouble()); //y轴位置
        query.bindValue(3+i*3+2,strlist.at(i*3+2).toInt()); //容量
    }
    query.bindValue(51,STANDARD_CODE);
    query.bindValue(52,ACTION_CODE);
    query.bindValue(53,RUN_DATA);
    query.bindValue(54,MODIFIER_ID);
    query.bindValue(55,MODIFY_TIME);
    query.bindValue(56,DEL_FLAG);       //DEL_FLAG

    query.bindValue(57,CATEGORY);       //条件
    query.bindValue(58,PROJECT_NAME);   //条件
    query.bindValue(59,REAGENT_TYPE);   //条件
    query.bindValue(60,PRODUCTION_TIME);//条件
    query.bindValue(61,BACH_NUMBER);    //条件

    bool ret = query.exec();
   //------------------------------------------------------------------
    if(!ret)
        qDebug()<<"试剂船信息表---更改---sql语句失败！"<<query.lastError();
    else
        qDebug()<<"试剂船信息表---更改---sql执行成功";
    return ret;


}

bool DataOpration::deleteData_reagentInfo()
{
    return true;
}


bool DataOpration::insertData_reagentMovement(
        int CHOOSE_FLAG,
        const QString &ACTION_CODE,
        int STEP_num,
        const QString &STEP_NAME,
        const QString &START_POSTION,
        const QString &PUT_IN_POSTION,
        int TIME,
        int BEFORE_BLEND_COUNT,
        int AFTER_BLEND_COUNT,
        int CAPACITY,
        int STEP_TIME,
        const QString &CREATOR_ID,
        const QString &CREATE_TIME,
        const QString &MODIFIER_ID,
        const QString &MODIFY_TIME,
        int DEL_FLAG)
{
    QSqlQuery query;
    query.prepare("insert into reagent_movement values("
                  "?,?,?,?,?,?,?,?,?,?,"
                  "?,?,?,?,?,?,?);");
    //query.bindValue(0,NULL); //主键自增
      query.bindValue(1,CHOOSE_FLAG);
      query.bindValue(2,ACTION_CODE);
      query.bindValue(3,STEP_num);
      query.bindValue(4,STEP_NAME);
      query.bindValue(5,START_POSTION);
      query.bindValue(6,PUT_IN_POSTION);
      query.bindValue(7,TIME);
      query.bindValue(8,BEFORE_BLEND_COUNT);
      query.bindValue(9,AFTER_BLEND_COUNT);
      query.bindValue(10,CAPACITY);
      query.bindValue(11,STEP_TIME);
      query.bindValue(12,CREATOR_ID);
      query.bindValue(13,CREATE_TIME);
      query.bindValue(14,MODIFIER_ID);
      query.bindValue(15,MODIFY_TIME);
      query.bindValue(16,DEL_FLAG);//DEL_FLAG
      bool ret = query.exec();
     //------------------------------------------------------------------
      if(!ret)qDebug()<<"试剂船动作表---新增---sql语句失败！"<<query.lastError();
      else qDebug()<<"试剂船动作表---新增---sql执行成功";
      return ret;
}

bool DataOpration::updateData_reagentMovement(
        int CHOOSE_FLAG,
        const QString &ACTION_CODE,
        int STEP_num,
        const QString &START_POSTION,
        const QString &PUT_IN_POSTION,
        int TIME,
        int BEFORE_BLEND_COUNT,
        int AFTER_BLEND_COUNT,
        int CAPACITY,
        int STEP_TIME,

        const QString &MODIFIER_ID,
        const QString &MODIFY_TIME,
        int DEL_FLAG)
{
    QSqlQuery query;
    query.prepare("update reagent_movement set "
                  "CHOOSE_FLAG      =?, "
                  "START_POSTION    =?, "
                  "PUT_IN_POSTION   =?, "
                  "TIME             =?, "
                  "BEFORE_BLEND_COUNT  =?, "
                  "AFTER_BLEND_COUNT =?, "
                  "CAPACITY   =?, "
                  "STEP_TIME  =?, "
                  "MODIFIER_ID   =?, "
                  "MODIFY_TIME  =?, "
                  "DEL_FLAG     =?"
                  "where ACTION_CODE=? and  STEP_NUM =? ;");
      query.bindValue(0,CHOOSE_FLAG);
      query.bindValue(1,START_POSTION);
      query.bindValue(2,PUT_IN_POSTION);
      query.bindValue(3,TIME);
      query.bindValue(4,BEFORE_BLEND_COUNT);
      query.bindValue(5,AFTER_BLEND_COUNT);
      query.bindValue(6,CAPACITY);
      query.bindValue(7,STEP_TIME);
      query.bindValue(8,MODIFIER_ID);
      query.bindValue(9,MODIFY_TIME);
      query.bindValue(10,DEL_FLAG);

      query.bindValue(11,ACTION_CODE);  //条件
      query.bindValue(12,STEP_num);     //条件

      bool ret = query.exec();
     //------------------------------------------------------------------
      if(!ret)qDebug()<<"试剂船动作表---第"<<STEP_num<<"步--更改---sql语句失败！";
      else qDebug()<<"试剂船动作表---第"<<STEP_num<<"步---更改---sql执行成功";
      return ret;

}


bool DataOpration::isExist_reagentMovement(int STEP_num, const QString &ACTION_CODE)
{
    QSqlQuery query;
    query.exec("select ACTION_CODE from reagent_movement where ACTION_CODE = ? and STEP_NUM =?;"); //账号
    query.bindValue(0,ACTION_CODE,QSql::Out);
    query.bindValue(1,STEP_num,QSql::Out);
    query.exec();
    while(query.next()){
        return true;
    }
    return false;
}


bool DataOpration::select_reagentInfo(const QString &ACTION_CODE, QSqlQueryModel &model)
{
    QString sss="select * from reagent_info where ACTION_CODE = '" + ACTION_CODE + "' ;";
    model.setQuery(sss);
    //qDebug()<<sss<<model.lastError();
    return true;
}

bool DataOpration::select_reagentMovement(const QString &ACTION_CODE, QSqlQueryModel &model)
{
    QString sss="select * from reagent_movement where ACTION_CODE = '" + ACTION_CODE + "' ;";
    model.setQuery(sss);
    //qDebug()<<sss<<model.lastError();
    return true;
}
