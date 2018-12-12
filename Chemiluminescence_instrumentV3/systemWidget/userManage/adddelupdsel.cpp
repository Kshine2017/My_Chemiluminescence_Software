#include "adddelupdsel.h"
#include <QDebug>

AddDelUpdSel::AddDelUpdSel()
{


}

bool AddDelUpdSel::insertData_OrdinaryUser(QString name, QString password,QString truename ,QString department,QString hospital,QString telephone, QString mail)
{
    QSqlQuery query;
    query.prepare("insert into usrinfo values("
                  ":name,"
                  ":password,"
                  ":telephone,"
                  ":mail,"
                  ":hospital,"
                  ":department,"
                  ":truename,"
                  "0,0,0,0,0);");
    query.bindValue(":name",(const QVariant)name);
    query.bindValue(":password",(const QVariant)password);
    query.bindValue(":truename",(const QVariant)truename);
    query.bindValue(":department",(const QVariant)department);
    query.bindValue(":hospital",(const QVariant)hospital);
    query.bindValue(":telephone",(const QVariant)telephone);
    query.bindValue(":mail",(const QVariant)mail);
    bool ret = query.exec();
   //------------------------------------------------------------------
    if(!ret)qDebug()<<"普通用户sql语句失败！";
    return ret;
}

bool AddDelUpdSel::deleteData_OrdinaryUser(QString &name)
{

    QSqlQuery query;
    query.prepare("delete from usrinfo where usrname = :name;");
    query.bindValue(":name",(const QVariant)name);

    bool ret = query.exec();
   //------------------------------------------------------------------

    if(!ret)
    {
        return false;
    }
    return true;
}

bool AddDelUpdSel::updateData_OrdinaryUser(QString name, QString password,QString truename ,QString department,QString hospital,QString telephone, QString mail)
{
    QSqlQuery query;
    query.prepare("update usrinfo set pwd = :password, phone_numeber = :telephone ,email = :mail,name=:truename,department=:department,hospital=:hospital where usrname = :name;");

    query.bindValue(":name",(const QVariant)name);
    //---------------------------------------------------------
    query.bindValue(":password",(const QVariant)password);
    query.bindValue(":telephone",(const QVariant)telephone);
    query.bindValue(":mail",(const QVariant)mail);
    query.bindValue(":truename",(const QVariant)truename);
    query.bindValue(":department",(const QVariant)department);
    query.bindValue(":hospital",(const QVariant)hospital);
    bool ret = query.exec();
   //------------------------------------------------------------------

    if(!ret)
    {

        return false;
    }

    return true;
}

bool AddDelUpdSel::selectData_OrdinaryUser(QString name, QString password,QString truename ,QString department,QString hospital,QString telephone, QString mail, QMySQlQueryModel &model)
{
    //qDebug()<<name<<password<<telephone<<mail;

    QString sss="select usrname,pwd,name,department,hospital,phone_numeber,email from usrinfo  where DEL_FLAG = 0";
    QString a,b,c,d,e,f,g;
    if(name!="")a=" and usrname like '%"+name+"%'";
    if(password!="")b=" and pwd like '%"+password+"%'";
    if(telephone!="")c=" and phone_numeber like '%"+telephone+"%'";
    if(mail!="")d=" and email like '%"+mail+"%'" ;
    if(truename!="")d=" and name like '%"+truename+"%'" ;
    if(department!="")d=" and department like '%"+department+"%'" ;
    if(hospital!="")d=" and hospital like '%"+hospital+"%'" ;

    sss+=a+b+c+d+e+f+g+";";
    //qDebug()<<sss;
    model.setQuery(sss);
    model.setHeaderData(0,Qt::Horizontal,QVariant("账号"));
    model.setHeaderData(1,Qt::Horizontal,QVariant("密码"));
    model.setHeaderData(2,Qt::Horizontal,QVariant("姓名"));
    model.setHeaderData(3,Qt::Horizontal,QVariant("科室"));
    model.setHeaderData(4,Qt::Horizontal,QVariant("医院"));
    model.setHeaderData(5,Qt::Horizontal,QVariant("电话"));
    model.setHeaderData(6,Qt::Horizontal,QVariant("邮箱"));

    return true;
}

/*
"create table administator_usrinfo(
usrname varchar2(30) not null primary key,
pwd varchar2(30),
phone_numeber varchar2(11) not null,
email varchar(30),
CREATER_ID VARCHAR2(32)NOT NULL,CREATE_TIME TIMESTAMP(6)NOT NULL,MODIFIER_ID VARCHAR2(32)NOT NULL,MODIFY_TIME TIMESTAMP(6)NOT NULL,DEL_FLAG CAHR(1)NOT NULL)");
*/
bool AddDelUpdSel::insertData_AdminUser(QString name, QString password,QString truename ,QString department,QString hospital,QString telephone, QString mail)
{
    QSqlQuery query;
    query.prepare("insert into administator_usrinfo values("
                  ":name,"
                  ":password,"
                  ":telephone,"
                  ":mail,"
                  ":hospital,"
                  ":department,"
                  ":truename,"
                  "0,0,0,0,0);");
    query.bindValue(":name",(const QVariant)name);
    query.bindValue(":password",(const QVariant)password);
    query.bindValue(":truename",(const QVariant)truename);
    query.bindValue(":department",(const QVariant)department);
    query.bindValue(":hospital",(const QVariant)hospital);
    query.bindValue(":telephone",(const QVariant)telephone);
    query.bindValue(":mail",(const QVariant)mail);
    bool ret = query.exec();
   //------------------------------------------------------------------
    if(!ret)qDebug()<<"管理员界面-新增-sql语句失败！";
    return ret;
}

bool AddDelUpdSel::deleteData_AdminUser(QString &name)
{
    QSqlQuery query;
    query.prepare("delete from administator_usrinfo where usrname = :name;");
    query.bindValue(":name",(const QVariant)name);

    bool ret = query.exec();
   //------------------------------------------------------------------

    if(!ret)
    {
        return false;
    }
    return true;
}

bool AddDelUpdSel::updateData_AdminUser(QString name, QString password,QString truename ,QString department,QString hospital,QString telephone, QString mail)
{
    QSqlQuery query;
    query.prepare("update administator_usrinfo set pwd = :password, phone_numeber = :telephone ,email = :mail,name=:truename,department=:department,hospital=:hospital where usrname = :name;");

    query.bindValue(":name",(const QVariant)name);
    //---------------------------------------------------------
    query.bindValue(":password",(const QVariant)password);
    query.bindValue(":telephone",(const QVariant)telephone);
    query.bindValue(":mail",(const QVariant)mail);
    query.bindValue(":truename",(const QVariant)truename);
    query.bindValue(":department",(const QVariant)department);
    query.bindValue(":hospital",(const QVariant)hospital);
    bool ret = query.exec();
   //------------------------------------------------------------------

    if(!ret)
    {

        return false;
    }

    return true;

}

bool AddDelUpdSel::selectData_AdminUser(QString name, QString password, QString truename, QString department, QString hospital, QString telephone, QString mail, QMySQlQueryModel &model)
{
    QString sss="select usrname,pwd,name,department,hospital,phone_numeber,email from administator_usrinfo  where DEL_FLAG = 0";
    QString a,b,c,d,e,f,g;
    if(name!="")a=" and usrname like '%"+name+"%'";
    if(password!="")b=" and pwd like '%"+password+"%'";
    if(telephone!="")c=" and phone_numeber like '%"+telephone+"%'";
    if(mail!="")d=" and email like '%"+mail+"%'" ;
    if(truename!="")d=" and name like '%"+truename+"%'" ;
    if(department!="")d=" and department like '%"+department+"%'" ;
    if(hospital!="")d=" and hospital like '%"+hospital+"%'" ;

    sss+=a+b+c+d+e+f+g+";";
    //qDebug()<<sss;
    model.setQuery(sss);
    model.setHeaderData(0,Qt::Horizontal,QVariant("账号"));
    model.setHeaderData(1,Qt::Horizontal,QVariant("密码"));
    model.setHeaderData(2,Qt::Horizontal,QVariant("姓名"));
    model.setHeaderData(3,Qt::Horizontal,QVariant("科室"));
    model.setHeaderData(4,Qt::Horizontal,QVariant("医院"));
    model.setHeaderData(5,Qt::Horizontal,QVariant("电话"));
    model.setHeaderData(6,Qt::Horizontal,QVariant("邮箱"));

    return true;

}

bool AddDelUpdSel::selectData_department(QString hospital, QSqlQueryModel &model)
{
    QString sss="select DISTINCT DEPATMENT_NAME from  hospital_info where HOSPITAL_NAME = '";
    sss+=hospital+"';";
    qDebug()<<sss;
    model.setQuery(sss);
    return true;
}

bool AddDelUpdSel::selectData_ALL_hospital(QSqlQueryModel &model)
{
    QString sss="select DISTINCT HOSPITAL_NAME from  hospital_info;";
    model.setQuery(sss);
    return true;
}

bool AddDelUpdSel::selectData_All_TestItem(QSqlQueryModel &model)
{
    QString sss="select DISTINCT FILE_SHORT_NAME from  Reagent_Bar_Info;";
    model.setQuery(sss);
    return true;
}
