#ifndef CONNECTION_H
#define CONNECTION_H

#include <QtSql>
#include <QDebug>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QMutex>
#include <QSqlError>
static bool createConnection()
{
    QSqlDatabase usr_db = QSqlDatabase::addDatabase("QSQLITE");
    usr_db.setHostName("chemistry-0001");
    usr_db.setDatabaseName("data.db");
    usr_db.setUserName("xiefei");
    usr_db.setPassword("123456");

    if(!usr_db.open()){          //数据库打开失败
        QMessageBox::critical(0,QObject::tr("错误代码:E0014"),usr_db.lastError().text());
        return false;
    }
    qDebug() <<"打开数据库成功";
    QSqlQuery query;

    //表1：创建普通用户
          query.exec("create table usrinfo(\
                      usrname                 varchar2(30) not null primary key,\
                      pwd                     varchar2(30),\
                      phone_numeber           varchar2(11) not null,\
                      email                   varchar(30),\
                      hospital                varchar(30),\
                      department              varchar(30),\
                      name                    varchar(30),\
                      CREATOR_ID              VARCHAR2(32)NOT NULL,\
                      CREATE_TIME             TIMESTAMP(6)NOT NULL,\
                      MODIFIER_ID             VARCHAR2(32)NOT NULL,\
                      MODIFY_TIME             TIMESTAMP(6)NOT NULL,\
                      DEL_FLAG                CAHR(1)NOT NULL\
          )");

        //表2：创建管理员表
        query.exec("create table administator_usrinfo("
                   "usrname                 varchar2(30) not null primary key,"
                   "pwd                     varchar2(30),"
                   "phone_numeber           varchar2(11) not null,"
                   "email                   varchar(30),hospital varchar(30),"
                   "department              varchar(30),name varchar(30),"
                   "CREATER_ID              VARCHAR2(32)NOT NULL,"
                   "CREATE_TIME             TIMESTAMP(6)NOT NULL,"
                   "MODIFIER_ID             VARCHAR2(32)NOT NULL,"
                   "MODIFY_TIME             TIMESTAMP(6)NOT NULL,"
                   "DEL_FLAG                CAHR(1)NOT NULL)"
                   "");
         //表3：创建病人信息表
        query.exec("create table patient_info ("
                   "NUM_ID                  INTEGER NOT NULL PRIMARY KEY,"
                   "PATIENT_ID              INT(20) NOT NULL,"
                   "NAME                    VARCHAR2(50) NOT NULL,"
                   "SEX                     VARCHAR2(1) NOT NULL,"
                   "AGE                     INT(130) NOT NULL,"
                   "TELEPHONE               VARCHAR2(11)NOT NULL,"
                   "DEPARTMENT              VARCHAR2(20)NOT NULL,"
                   "TEST_ITEM               VARCHAR2(20)NOT NULL,"
                   "SERICAL_NUM             VARCHAR2(30)NOT NULL,"
                   "TEST_CONCENTRATION      FLOAT(10,6),"
                   "CREATOR_ID              VARCHAR2(32)NOT NULL,"
                   "CREATE_TIME             TIMESTAMP(6)NOT NULL,"
                   "MODIFIER_ID             VARCHAR2(32)NOT NULL,"
                   "MODIFY_TIME             TIMESTAMP(6)NOT NULL,"
                   "DEL_FLAG                CAHR(1)NOT NULL)"
                   "");

        //

      //表4：故障信息表
        query.exec("create table ERR_Info("
                   "NUM_ID                  INTEGER NOT NULL PRIMARY KEY,"
                   "USR_ID                  VARCHAR2(20),"
                   "HOSPITAL_NAME           VARCHAR2(40),"
                   "DEAPARTMENT             VARCHAR2(40),"
                   "OPERATION_NAME          VARCHAR2(10),"
                   "ERR_CODE                VARCHAR2(20),"
                   "ERR_INFO                VARCHAR2(200),"
                   "CREATOR_ID              VARCHAR2(32),"
                   "CREATE_TIME             TIMESTAMP(6),"
                   "MODIFIER_ID             VARCHAR2(32),"
                   "MODIFY_TIME             TIMESTAMP(6),"
                   "DEL_FLAG                CHAR(1))"
                   "");


        //表5：医院科室信息表
        query.exec("create table hospital_info(ID INTEGER NOT NULL PRIMARY KEY autoincrement,"
                   "HOSPITAL_NAME           VARCHAR2(40) NOT NULL,"
                   "DEPATMENT_NAME          VARCHAR2(40) NOT NULL,"
                   "CREATOR_ID              VARCHAR2(32),"
                   "CREATE_TIME             TIMESTAMP(6),"
                   "MODIFIER_ID             VARCHAR2(32),"
                   "MODIFY_TIME             TIMESTAMP(6),"
                   "DEL_FLAG                CHAR(1))");


        //表6：医院临床诊断类型管理信息表
        query.exec("create table category_info(ID INTEGER NOT NULL PRIMARY KEY autoincrement,"
                   "CATEGORY_NAME           VARCHAR2(40) NOT NULL,"
                   "CREATOR_ID              VARCHAR2(32),"
                   "CREATE_TIME             TIMESTAMP(6),"
                   "MODIFIER_ID             VARCHAR2(32),"
                   "MODIFY_TIME             TIMESTAMP(6),"
                   "DEL_FLAG                CHAR(1))");


    //表7：试剂船信息表 20180511
        query.exec("create table reagent_info("
                   "ID                                  INTEGER       NOT NULL PRIMARY KEY autoincrement,"
                   "CATEGORY                            VARCHAR2(30),"
                   "PROJECT_NAME                        VARCHAR2(30),"
                   "REAGENT_TYPE                        VARCHAR2(30),"
                   "PRODUCTION_TIME                     TIMESTAMP(6),"
                   "BACH_NUMBER                         INT(2),"
                   "QUALITY_TIME                        INT(2),"
                   "RESERVE                             varchar2(6),"
                   "BAR_CODE                            varchar2(20),"
                   "RUBBTION_X_POS                      DOUBLE(5,2),"
                   "RUBBTION_Y_POS                      DOUBLE(5,2),"
                   "RUBBTION_CAPACITY                   INT(6),"
                   "TP1_X_POS                           DOUBLE(5,2),"
                   "TP1_Y_POS                           DOUBLE(5,2),"
                   "TP1_CAPACITY                        INT(6),"
                   "TP2_X_POS                           DOUBLE(5,2),"
                   "TP2_Y_POS                           DOUBLE(5,2),"
                   "TP2_CAPACITY                        INT(6),"
                   "TP3_X_POS                           DOUBLE(5,2),"
                   "TP3_Y_POS                           DOUBLE(5,2),"
                   "TP3_CAPACITY                        INT(6),"
                   "TP4_X_POS                           DOUBLE(5,2),"
                   "TP4_Y_POS                           DOUBLE(5,2),"
                   "TP4_CAPACITY                        INT(6),"
                   "PREEXCITATION_FLUID_X_POS           DOUBLE(5,2),"
                   "PREEXCITATION_FLUID_Y_POS           DOUBLE(5,2),"
                   "PREEXCITATION_FLUID_CAPACITY        INT(6),"
                   "EXCITATION_FLUID_X_POS              DOUBLE(5,2),"
                   "EXCITATION_FLUID_Y_POS              DOUBLE(5,2),"
                   "EXCITATION_FLUID_CAPACITY           INT(6),"
                   "WASH3_X_POS                         DOUBLE(5,2),"
                   "WASH3_Y_POS                         DOUBLE(5,2),"
                   "WASH3_CAPACITY                      INT(6),"
                   "WASH2_X_POS                         DOUBLE(5,2),"
                   "WASH2_Y_POS                         DOUBLE(5,2),"
                   "WASH2_CAPACITY                      INT(6),"
                   "WASH1_X_POS                         DOUBLE(5,2),"
                   "WASH1_Y_POS                         DOUBLE(5,2),"
                   "WASH1_CAPACITY                      INT(6),"
                   "MAGNETIC_X_POS                      DOUBLE(5,2),"
                   "MAGNETIC_Y_POS                      DOUBLE(5,2),"
                   "MAGNETIC_CAPACITY                   INT(6),"
                   "RESERVE_X_POS                       DOUBLE(5,2),"
                   "RESERVE_Y_POS                       DOUBLE(5,2),"
                   "RESERVE_CAPACITY                    INT(6),"
                   "BIOTIN_X_POS                        DOUBLE(5,2),"
                   "BIOTIN_Y_POS                        DOUBLE(5,2),"
                   "BIOTIN_CAPACITY                     INT(6),"
                   "ACRIDINE_ESTER_X_POS                DOUBLE(5,2),"
                   "ACRIDINE_ESTER_Y_POS                DOUBLE(5,2),"
                   "ACRIDINE_ESTER_CAPACITY             INT(6),"
                   "REACTION1_TUBE_X_POS                DOUBLE(5,2),"
                   "REACTION1_TUBE_Y_POS                DOUBLE(5,2),"
                   "REACTION1_TUBE_CAPACITY             INT(6),"
                   "PLASMA_X_POS                        DOUBLE(5,2),"
                   "PLASMA_Y_POS                        DOUBLE(5,2),"
                   "PLASMA_CAPACITY                     INT(6),"
                   "STANDARD_CODE                       VARCHAR2(8),"
                   "ACTION_CODE                         VARCHAR2(8),"
                   "RUN_DATA                            VARCHAR2(500),"
                   "CREATOR_ID                          VARCHAR2(32),"
                   "CREATE_TIME                         TIMESTAMP(6),"
                   "MODIFIER_ID                         VARCHAR2(32),"
                   "MODIFY_TIME                         TIMESTAMP(6),"
                   "DEL_FLAG                            CHAR(1)"
                   ");");


        //表8：插入一个试剂船动作方案表20180514
        query.exec("create table reagent_movement("
                   "ID                                  INTEGER NOT NULL PRIMARY KEY autoincrement,"
                   "CHOOSE_FLAG                         CHAR(1),"
                   "ACTION_CODE                         VARCHAR2(8),"
                   "STEP_NUM                            INT(2),"
                   "STEP_NAME                           VARCHAR2(20),"
                   "START_POSTION                       VARCHAR2(20),"
                   "PUT_IN_POSTION                      VARCHAR2(20),"
                   "TIME                                INT(6),"
                   "BEFORE_BLEND_COUNT                  TINYINT(3),"
                   "AFTER_BLEND_COUNT                   TINYINT(3),"
                   "CAPACITY                            INT(6),"
                   "STEP_TIME                           INT(6),"
                   "CREATOR_ID                          VARCHAR2(32),"
                   "CREATE_TIME                         TIMESTAMP(6),"
                   "MODIFIER_ID                         VARCHAR2(32),"
                   "MODIFY_TIME                         TIMESTAMP(6),"
                   "DEL_FLAG                            CHAR(1)"
                   ");");

        //表9：插入一个试剂船 标准品信息表 20180514
        query.exec("create table reagent_standard_info("
                   "ID                                  INTEGER NOT NULL PRIMARY KEY autoincrement,"
                   "STANDARD_CODE                       VARCHAR2(8),"
                   "POINT_C_ONE                         DOUBLE(10,5),"
                   "POINT_P_ONE                         INT(10),"
                   "POINT_C_TWO                         DOUBLE(10,5),"
                   "POINT_P_TWO                         INT(10),"
                   "POINT_C_THREE                       DOUBLE(10,5),"
                   "POINT_P_THREE                       INT(10),"
                   "POINT_C_FOUR                        DOUBLE(10,5),"
                   "POINT_P_FOUR                        INT(10),"
                   "POINT_C_FIVE                        DOUBLE(10,5),"
                   "POINT_P_FIVE                        INT(10),"
                   "POINT_C_SIX                         DOUBLE(10,5),"
                   "POINT_P_SIX                         INT(10),"
                   "POINT_C_SEVEN                       DOUBLE(10,5),"
                   "POINT_P_SEVEN                       INT(10),"
                   "POINT_C_EIGHT                       DOUBLE(10,5),"
                   "POINT_P_EIGHT                       INT(10),"
                   "POINT_C_NINE                        DOUBLE(10,5),"
                   "POINT_P_NINE                        INT(10),"
                   "POINT_C_TEN                         DOUBLE(10,5),"
                   "POINT_P_TEN                         INT(10),"
                   "POINT_C_ELEVEN                      DOUBLE(10,5),"
                   "POINT_P_ELEVEN                      INT(10),"
                   "POINT_C_TWELVE                      DOUBLE(10,5),"
                   "POINT_P_TWELVE                      INT(10),"
                   "CREATOR_ID                          VARCHAR2(32),"
                   "CREATE_TIME                         TIMESTAMP(6),"
                   "MODIFIER_ID                         VARCHAR2(32),"
                   "MODIFY_TIME                         TIMESTAMP(6),"
                   "DEL_FLAG                            CHAR(1)"
                   ");");

        //表10：曲线参数表 20180514
        query.exec("create table cruve_parameter("
                   "ID                      INTEGER NOT NULL PRIMARY KEY autoincrement,"
                   "CATEGORY                VARCHAR2(30) NOT NULL, "
                   "CATEGORY_CODE           VARCHAR2(2) NOT NULL, "
                   "PROJECT_NAME            VARCHAR2(30) NOT NULL, "
                   "PROJECT_NAME_CODE       VARCHAR2(2) NOT NULL, "
                   "REAGENT_TYPE            VARCHAR2(30) NOT NULL, "
                   "REAGENT_TYPE_CODE       VARCHAR2(2) NOT NULL, "
                   "REAGENT_CODE            VARCHAR2(8) NOT NULL, "
                   "GENERATION_TYPE         INTEGER NOT NULL,"
                   "PARAMETER_ONE           DOUBLE(10,5),"
                   "PARAMETER_TWO           DOUBLE(10,5),"
                   "PARAMETER_THREE         DOUBLE(10,5),"
                   "PARAMETER_FOUR          DOUBLE(10,5),"
                   "PARAMETER_FIVE          DOUBLE(10,5),"
                   "PARAMETER_SIX           DOUBLE(10,5),"
                   "CREATOR_ID              VARCHAR2(32),"
                   "CREATE_TIME             TIMESTAMP(6),"
                   "MODIFIER_ID             VARCHAR2(32),"
                   "MODIFY_TIME             TIMESTAMP(6),"
                   "DEL_FLAG                CHAR(1)"
                   ")");

        //表11：质控点信息表20180514
        query.exec("create table quality_control_info("
                   "ID                                  INTEGER NOT NULL PRIMARY KEY autoincrement,"
                   "CATEGORY                            VARCHAR2(30) NOT NULL,"
                   "PROJECT_NAME                        VARCHAR2(30) NOT NULL,"
                   "REAGENT_TYPE                        VARCHAR2(30) NOT NULL,"
                   "BAR_CODE                            VARCHAR2(50) NOT NULL,"
                   "STANDARD_CONCENTRATION              DOUBLE(10,5),"
                   "START_DATE                          TIMESTAMP(6),"
                   "END_DATE                            TIMESTAMP(6),"
                   "STANDARD_FLAG                       CHAR(1),"
                   "PHOTON_VALUE                        INT(10),"
                   "CONCENTRATION                       DOUBLE(10,5),"
                   "VARIANCE_COEFFICENT                 DOUBLE(10,5),"
                   "CREATOR_ID                          VARCHAR2(32),"
                   "CREATE_TIME                         TIMESTAMP(6),"
                   "MODIFIER_ID                         VARCHAR2(32),"
                   "MODIFY_TIME                         TIMESTAMP(6),"
                   "DEL_FLAG                            CHAR(1)"
                   ")");
        //


        //表12：校准点信息表20180514
        query.exec("create table calibration_info("
                   "ID                                  INTEGER      NOT NULL PRIMARY KEY autoincrement,"
                   "CATEGORY                            VARCHAR2(30) NOT NULL,"
                   "PROJECT_NAME                        VARCHAR2(30) NOT NULL,"
                   "REAGENT_TYPE                        VARCHAR2(30) NOT NULL,"
                   "BAR_CODE                            VARCHAR2(50) NOT NULL,"
                   "STANDARD_CONCENTRATION              DOUBLE(10,5),"
                   "START_DATE                          TIMESTAMP(6),"
                   "END_DATE                            TIMESTAMP(6),"
                   "STANDARD_FLAG                       CHAR(1),"
                   "PHOTON_VALUE                        INT(10),"
                   "CONCENTRATION                       DOUBLE(10,5),"
                   "VARIANCE_COEFFICENT                 DOUBLE(10,5),"
                   "CREATOR_ID                          VARCHAR2(32),"
                   "CREATE_TIME                         TIMESTAMP(6),"
                   "MODIFIER_ID                         VARCHAR2(32),"
                   "MODIFY_TIME                         TIMESTAMP(6),"
                   "DEL_FLAG                            CHAR(1)"
                   ")");

              //表13：标准品信息表20180514
        query.exec("create table standard_info("
                   "ID                                  INTEGER      NOT NULL PRIMARY KEY autoincrement,"
                   "STANDARD_CODE                       VARCHAR2(30) NOT NULL,"
                   "CATEGORY                            VARCHAR2(30) NOT NULL,"
                   "PROJECT_NAME                        VARCHAR2(30) NOT NULL,"
                   "REAGENT_TYPE                        VARCHAR2(30) NOT NULL,"
                   "BAR_CODE                            VARCHAR2(50),"
                   "STANDARD_CONCENTRATION              DOUBLE(10,5),"
                   "START_DATE                          TIMESTAMP(6),"
                   "END_DATE                            TIMESTAMP(6),"
                   "STANDARD_FLAG                       CHAR(1),"
                   "PHOTON_VALUE                        INT(10),"
                   "CONCENTRATION                       DOUBLE(10,5),"
                   "VARIANCE_COEFFICENT                 DOUBLE(10,5),"
                   "CREATOR_ID                          VARCHAR2(32),"
                   "CREATE_TIME                         TIMESTAMP(6),"
                   "MODIFIER_ID                         VARCHAR2(32),"
                   "MODIFY_TIME                         TIMESTAMP(6),"
                   "DEL_FLAG                            CHAR(1)"
                   ");");



    //表14：试剂条码编码信息表(20180514)
    query.exec("create table Reagent_Bar_Info("
               "ID                                  INTEGER      NOT NULL PRIMARY KEY autoincrement,"
               "CATEGORY                            VARCHAR2(30) NOT NULL,"
               "CATEGORY_CODE                       VARCHAR2(2),"
               "PROJECT_NAME                        VARCHAR2(30),"
               "PROJECT_NAME_CODE                   VARCHAR2(2),"
               "REAGENT_TYPE                        VARCHAR2(30),"
               "REAGENT_TYPE_CODE                   VARCHAR2(4),"
               "REAGENT_CODE                        VARCHAR2(8),"
               "CREATOR_ID                          VARCHAR2(32),"
               "CREATE_TIME                         TIMESTAMP(6),"
               "MODIFIER_ID                         VARCHAR2(32),"
               "MODIFY_TIME                         TIMESTAMP(6),"
               "DEL_FLAG                            CHAR(1)"
               ");");
    //qDebug()<< query.lastError();


 #if 1
//=====================================================================================================================
//=====================================================================================================================
//=====================================================================================================================
    //插入一个普通用户
    query.exec("insert into usrinfo values('22','122','13605511574','xiefei@bb-care.com.cn','上海第一人民医院','心脏外科','刘锋',0,0,0,0,0)");
    query.exec("insert into usrinfo values('1','1','13605511574','xiefei@bb-care.com.cn','南京鼓楼医院','护理室','钱好多',0,0,0,0,0)");
    //插入一个管理员
    query.exec("insert into administator_usrinfo values('xiefei','xiefei','13605511574','xiefei@bb-c  are.com','上海贝生医疗科技有限公司','开发部','谢飞',0,0,0,0,0)");
    //插入一个医院科室信息表
    query.exec("insert into  hospital_info values(1,'上海市儿童医院','骨科',0,0,0,0,0)");
    //插入一个医院临床诊断类型管理信息表信息
    query.exec("insert into  category_info values(1,'肺炎',0,0,0,0,0)");

    //插入病人信息
    query.exec("insert into  patient_info values(1,123,'赵四','男','55','13113331321','骨科','肋骨CT','37432566',0.342,'韩彩英','2018-03-01 00:00:00','韩佳人','2018-04-01 00:00:00','0')");
    query.exec("insert into  patient_info values(2,5224,'刘能','男','65','13113331321','脑科','智力','523455',0.182,'秦岚','2018-01-01 00:00:00','韩佳人','2018-05-01 00:00:00','0')");

    //插入4个质控点
    query.exec("insert into quality_control_info values(1,'质控品','重症感染类','TENCENT','0000111XXXX',2030.66,'2018-01-01 00:00:00','2018-04-01 00:00:00','A',1101100,1998.22,0.98,'韩梅梅','2018-03-01 00:00:00','李雷','2018-04-01 00:00:00','0')");
    query.exec("insert into quality_control_info values(2,'质控品','蛋白类','PPS','0000111XXXX',2030.66,'2018-01-01 00:00:00','2018-04-01 00:00:00','A',1101100,1998.22,0.98,'韩梅梅','2018-03-01 00:00:00','李雷','2018-04-01 00:00:00','0')");
    query.exec("insert into quality_control_info values(3,'质控品','心肌类','PPTV','0000111XXXX',2030.66,'2018-01-01 00:00:00','2018-04-01 00:00:00','A',1101100,1998.22,0.98,'韩梅梅','2018-03-01 00:00:00','李雷','2018-04-01 00:00:00','0')");
    query.exec("insert into quality_control_info values(4,'质控品','其他类','IQIYI','0000111XXXX',2030.66,'2018-01-01 00:00:00','2018-04-01 00:00:00','A',1101100,1998.22,0.98,'韩梅梅','2018-03-01 00:00:00','李雷','2018-04-01 00:00:00','0')");

    //插入5个校准点
    query.exec("insert into calibration_info values(1,'校准品','心肌类','SJLB1','0000111XXXX',2030.66,'2018-01-01 00:00:00','2018-04-01 00:00:00','A',1101100,1998.22,0.98,'韩梅梅','2018-03-01 00:00:00','李雷','2018-04-01 00:00:00','0')");
    query.exec("insert into calibration_info values(2,'校准品','重症感染类','SJLB1','0000111XXXX',2030.66,'2018-01-01 00:00:00','2018-04-01 00:00:00','A',1101100,1998.22,0.98,'韩梅梅','2018-03-01 00:00:00','李雷','2018-04-01 00:00:00','0')");
    query.exec("insert into calibration_info values(3,'校准品','其他类','SJLB1','0000111XXXX',2030.66,'2018-01-01 00:00:00','2018-04-01 00:00:00','A',1101100,1998.22,0.98,'韩梅梅','2018-03-01 00:00:00','李雷','2018-04-01 00:00:00','0')");
    query.exec("insert into calibration_info values(4,'校准品','其他类','SJLB1','0000111XXXX',2030.66,'2018-01-01 00:00:00','2018-04-01 00:00:00','A',1101100,1998.22,0.98,'韩梅梅','2018-03-01 00:00:00','李雷','2018-04-01 00:00:00','0')");
    query.exec("insert into calibration_info values(5,'校准品','测试名称','SJLB1','0000111XXXX',2030.66,'2018-01-01 00:00:00','2018-04-01 00:00:00','A',1101100,1998.22,0.98,'韩梅梅','2018-03-01 00:00:00','李雷','2018-04-01 00:00:00','0')");

    //插入3个标准点点
    query.exec("insert into standard_info values(1,'0000111','标准品','心肌类','SJLB1','0000111XXXX',2030.66,'2018-01-01 00:00:00','2018-04-01 00:00:00','A',1101100,1998.22,0.98,'韩梅梅','2018-03-01 00:00:00','李雷','2018-04-01 00:00:00','0')");
    query.exec("insert into standard_info values(2,'0000111','标准品','蛋白类','SJLB1','0000111XXXX',2030.66,'2018-01-01 00:00:00','2018-04-01 00:00:00','A',1101100,1998.22,0.98,'韩梅梅','2018-03-01 00:00:00','李雷','2018-04-01 00:00:00','0')");
    query.exec("insert into standard_info values(3,'0000111','标准品','人类','SJLB1','0000111XXXX',2030.66,'2018-01-01 00:00:00','2018-04-01 00:00:00','A',1101100,1998.22,0.98,'韩梅梅','2018-03-01 00:00:00','李雷','2018-04-01 00:00:00','0')");

//=====================================================================================================================
//=====================================================================================================================
//=====================================================================================================================
#endif
    return true;
}


/**
 * @brief ouPutMessage日志文件
 * @param type
 * @param context 日志信息附加(包含文件名称 行号 日期)
 * @param msg
 */
static void ouPutMessage(QtMsgType type,const QMessageLogContext &context,const QString &msg)
{
    static QMutex mutex;
    mutex.lock();
    QString text;
    switch(type){
    case QtDebugMsg:
        text = QString(QObject::tr("Debug"));
        break;
    case QtInfoMsg:
        text = QString(QObject::tr("Info"));
        break;
    case QtWarningMsg:
        text = QString(QObject::tr("Warning"));
        break;
    case QtCriticalMsg:
        text = QString(QObject::tr("Critical"));
        break;
    case QtFatalMsg:
        text = QString(QObject::tr("Fatal"));
        break;
    }
    QString context_info = QString("File:(%1)Line:(%2)").arg(QString(context.file)).arg(context.line);
    QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm ddd");
    QString current_date = QString("(%1)").arg(current_date_time);
    QString message = QString("%1 %2 %3 %4").arg(text).arg(context_info).arg(msg).arg(current_date_time);

    QFile file("log.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream text_stream(&file);
    text_stream << message << "\r\n";
    file.flush();
    file.close();

    mutex.unlock();

}
#endif // CONNECTION_H
