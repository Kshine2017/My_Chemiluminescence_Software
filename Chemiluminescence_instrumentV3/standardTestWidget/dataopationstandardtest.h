#ifndef DATAOPATIONSTANDARDTEST_H
#define DATAOPATIONSTANDARDTEST_H

#include <QStringList>
class DataOpationStandardtest
{
public:
    DataOpationStandardtest();

    //20180517
    bool insertData_standard_info
            (
            const QString& STANDARD_CODE,
            const QString& CATEGORY,
            const QString& PROJECT_NAME,
            const QString& REAGENT_TYPE,
            const QString& BAR_CODE,
            double         STANDARD_CONCENTRATION,
            const QString& START_DATE,
            const QString& END_DATE,
            char           STANDARD_FLAG,
            int            PHOTON_VALUE,
            double         CONCENTRATION,
            double         VARIANCE_COEFFICENT,
            const QString& CREATOR_ID,
            const QString& CREATE_TIME,
            const QString& MODIFIER_ID,
            const QString& MODIFY_TIME,
            char           DEL_FLAG
            );
    //reagent_standard_info
    bool insertData_reagent_standard_info
            (
            const QString& STANDARD_CODE,
            const QStringList& strlist,
            const QString& CREATOR_ID,
            const QString& CREATE_TIME,
            const QString& MODIFIER_ID,
            const QString& MODIFY_TIME,
            char           DEL_FLAG
            );




    bool isExist_standard_info(const QString& STANDARD_CODE);
    bool isExist_reagent_standard_info(const QString& STANDARD_CODE);


    bool deleteData_standard_info(const QString& STANDARD_CODE);
    bool deleteData_reagent_standard_info(const QString& STANDARD_CODE);

};

#endif // DATAOPATIONSTANDARDTEST_H
