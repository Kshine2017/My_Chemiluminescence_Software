#ifndef USERINFORMATION_H
#define USERINFORMATION_H
#include <QString>

class UserInformation
{
public:
    UserInformation();
    UserInformation(QString name,QString department,QString passWord,QString cellPhone,QString mailBox);

    QString name;       //姓名
    QString department;       //科室
    QString passWord;       //密码
    QString cellPhone;       //手机号
    QString mailBox;       //邮箱
};

#endif // USERINFORMATION_H
