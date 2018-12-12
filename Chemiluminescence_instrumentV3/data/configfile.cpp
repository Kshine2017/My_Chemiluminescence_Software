#include "configfile.h"
#include <QSettings>
ConfigFile::ConfigFile()
{

}

void ConfigFile::saveCurrentUser(const QString&account,const QString& password,const QString&name,int status,const QString &department,const QString& hospital)
{
        QString iniFilePath = "./data/current_user.ini";
        QSettings settings(iniFilePath,QSettings::IniFormat);
        settings.setValue("account: ",account);
        settings.setValue("password: ",password);
        settings.setValue("name: ",name);
        settings.setValue("status: ",status);//123
        settings.setValue("department: ",department);
        settings.setValue("hospital: ",hospital);
}



void ConfigFile::getCurrentUser_AllInfo(QString&account,QString& password,QString&name,int &status)
{
    QString iniFilePath = "./data/current_user.ini";
    QSettings settings(iniFilePath,QSettings::IniFormat);
    account=settings.value("account: ").toString();
    password=settings.value("password: ").toString();
    name=settings.value("name: ").toString();
    status=settings.value("status: ").toInt();
}

QString ConfigFile::getCurrentUser_ID()
{
    QString iniFilePath = "./data/current_user.ini";
    QSettings settings(iniFilePath,QSettings::IniFormat);
    return settings.value("account: ").toString();
}

QString ConfigFile::getCurrentUser_Name()
{
    QString iniFilePath = "./data/current_user.ini";
    QSettings settings(iniFilePath,QSettings::IniFormat);
    return settings.value("name: ").toString();
}

QString ConfigFile::getCurrentUser_department()
{
    QString iniFilePath = "./data/current_user.ini";
    QSettings settings(iniFilePath,QSettings::IniFormat);
    return settings.value("department: ").toString();
}

QString ConfigFile::getCurrentUser_hospital()
{
    QString iniFilePath = "./data/current_user.ini";
    QSettings settings(iniFilePath,QSettings::IniFormat);
    return settings.value("hospital: ").toString();
}
