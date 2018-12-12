#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <QString>
class ConfigFile
{
public:
    ConfigFile();
    void saveCurrentUser(const QString&account,const QString& password,const QString&name,int status,const QString &department,const QString& hospital);

    void getCurrentUser_AllInfo(QString &account, QString &password, QString &name, int &status);
    QString getCurrentUser_ID();
    QString getCurrentUser_Name();
    QString getCurrentUser_department();
    QString getCurrentUser_hospital();

};

#endif // CONFIGFILE_H
