#include "userinformation.h"

UserInformation::UserInformation()
{

}
/**
 *  初始化用户
 * @brief UserInformation::UserInformation
 * @param name
 * @param department
 * @param passWord
 * @param cellPhone
 * @param mailBox
 */
UserInformation::UserInformation(QString name, QString department, QString passWord, QString cellPhone, QString mailBox)
{
    this->name = name;
    this->department = department;
    this->passWord = passWord;
    this->cellPhone = cellPhone;
    this->mailBox = mailBox;
}
