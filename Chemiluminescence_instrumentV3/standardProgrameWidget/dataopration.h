#ifndef DATAOPRATION_H
#define DATAOPRATION_H
#include <QStringList>
#include <QSqlQueryModel>
class DataOpration
{
public:
    DataOpration();
    //试剂船信息


    //20180515 新增 reagent_info
    bool insertData_reagentInfo(const QString &CATEGORY,
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
                                int DEL_FLAG);




     //20180515 新增 reagent_info
    bool isExist_reagentInfo(const QString &STANDARD_CODE);



     //20180515 新增 reagent_info
    bool updateData_reagentInfo(   const QString &CATEGORY,
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
                                      int DEL_FLAG);


    bool deleteData_reagentInfo();

    //试剂船动作方案


    //20180515 新增 reagent_movement
    bool insertData_reagentMovement(
                                    int CHOOSE_FLAG,
                                    const QString& ACTION_CODE,
                                    int            STEP_num,
                                    const QString& STEP_NAME,
                                    const QString &START_POSTION,
                                    const QString &PUT_IN_POSTION,
                                    int TIME,
                                    int BEFORE_BLEND_COUNT,
                                    int AFTER_BLEND_COUNT,
                                    int CAPACITY,
                                    int STEP_TIME,
                                    const QString&CREATOR_ID,
                                    const QString&CREATE_TIME,
                                    const QString&MODIFIER_ID,
                                    const QString&MODIFY_TIME,
                                    int DEL_FLAG
                                    );


    //20180515 新增
    bool updateData_reagentMovement(int CHOOSE_FLAG,
                                    const QString& ACTION_CODE,
                                    int            STEP_num,
                                    const QString &START_POSTION,
                                    const QString &PUT_IN_POSTION,
                                    int TIME,
                                    int BEFORE_BLEND_COUNT,
                                    int AFTER_BLEND_COUNT,
                                    int CAPACITY,
                                    int STEP_TIME,
                                    const QString&MODIFIER_ID,
                                    const QString&MODIFY_TIME, int DEL_FLAG);



    bool isExist_reagentMovement(int STEP_num, const QString& ACTION_CODE);
    //试剂船标准品信息


    //20180515 新增 reagent_info
    bool select_reagentInfo(const QString& ACTION_CODE,QSqlQueryModel& model);



    //20180515 新增
     bool select_reagentMovement(const QString& ACTION_CODE,QSqlQueryModel& model);
};

#endif // DATAOPRATION_H
