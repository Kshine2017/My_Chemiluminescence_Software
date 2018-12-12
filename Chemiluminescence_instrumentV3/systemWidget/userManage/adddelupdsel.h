#ifndef ADDDELUPDSEL_H
#define ADDDELUPDSEL_H
#include <QString>
#include "../qmysqlquerymodel.h"


enum WF_enum
{
    NOUSER=0,
    ORDINARYUSER=1,
    ADMINUSER=2
};
class AddDelUpdSel
{
public:
    AddDelUpdSel();

    bool insertData_OrdinaryUser(QString name, QString password,QString truename ,QString department,QString hospital,QString telephone, QString mail);
    bool deleteData_OrdinaryUser(QString& name);
    bool updateData_OrdinaryUser(QString name, QString password,QString truename ,QString department,QString hospital,QString telephone, QString mail);
    bool selectData_OrdinaryUser(QString name, QString password, QString truename, QString department, QString hospital, QString telephone, QString mail, QMySQlQueryModel& model);

    bool insertData_AdminUser(QString name, QString password,QString truename ,QString department,QString hospital,QString telephone, QString mail);
    bool deleteData_AdminUser(QString& name);
    bool updateData_AdminUser(QString name, QString password,QString truename ,QString department,QString hospital,QString telephone, QString mail);
    bool selectData_AdminUser(QString name, QString password, QString truename, QString department, QString hospital, QString telephone, QString mail, QMySQlQueryModel& model);

    bool selectData_department(QString hospital, QSqlQueryModel &model); //当选择了一个医院之后，根据医院名，搜索所有其下科室
    bool selectData_ALL_hospital(QSqlQueryModel& model);//先返回所有的医院信息

    bool selectData_All_TestItem(QSqlQueryModel& model);//返回所有的检测项目信息

};

#endif // ADDDELUPDSEL_H
