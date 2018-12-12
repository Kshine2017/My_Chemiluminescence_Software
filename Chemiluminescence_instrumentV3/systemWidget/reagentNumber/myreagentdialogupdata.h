#ifndef MYREAGENTDIALOGUPDATA_H
#define MYREAGENTDIALOGUPDATA_H


#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QComboBox>

/**
 * @brief The MyReagentDialogUpdata class
 * 更新弹窗界面
 */

class MyReagentDialogUpdata : public QDialog
{
    Q_OBJECT
public:
    MyReagentDialogUpdata(QWidget *parent,QString str_category,QString str_category_code,
                          QString str_projectName,QString str_projectName_code,
                          QString str_reagentType,QString str_reagentType_code);
public:
    QVBoxLayout *mainLayout;
    QHBoxLayout *layout_CATEGORY;           //试剂品类
    QHBoxLayout *layout_CATEGORY_code;        //试剂品类编码

    QHBoxLayout *layout_PROJECT_NAME;      //项目名称
    QHBoxLayout *layout_PROJECT_NAME_code;      //项目名称编码

    QHBoxLayout *layout_REAGENT_TYPE;      //试剂种类
    QHBoxLayout *layout_REAGENT_TYPE_code;      //试剂种类编码

    QHBoxLayout *layout_btn;        //按钮布局


    QLabel *label_CATEGORY;
    QLabel *label_CATEGORY_code;

    QLabel *label_PROJECT_NAME;
    QLabel *label_PROJECT_NAME_code;

    QLabel *label_REAGENT_TYPE;
    QLabel *label_REAGENT_TYPE_code;

    QComboBox *cBox_CATEGORY;
    QLineEdit *le_CATEGORY_code;

    QComboBox *cBox_PROJECT_NAME;
    QLineEdit *le_PROJECT_NAME_code;

    QComboBox *cBox_REAGENT_TYPE;
    QLineEdit *le_REAGENT_TYPE_code;

    void init();
    void initComboBoxData();

    QPushButton *btn_sure;
    QPushButton *btn_cancel;


    int checkCategory();
    int checkProjectName();
    int checkReagentType();

    QString str_categoryInfo;
    QString str_categoryCodeInfo;
    QString str_projectNameInfo;
    QString str_projectNameCodeInfo;
    QString str_reagentTypeInfo;
    QString str_reagentTypeCodeInfo;

signals:
    //发送信号后，让试剂编码界面更新表格
    void siganl_please_fresh_table();

public slots:

    void btn_cancelSlot();
    void btn_addSlot();

    /**
     * @brief slot_fresh_cBox_PROJECT_NAME 品类更改时刷新项目名称
     * @param str_category  品类
     */
    void slot_fresh_cBox_PROJECT_NAME(QString str_category);
    /**
     * @brief slot_fresh_cBox_REAGENT_TYPE  项目名称更改时刷新试剂种类
     * @param str_projectName   项目名称
     */
    void slot_fresh_cBox_REAGENT_TYPE(QString str_projectName);
    /**
     * @brief slot_fresh_le_CATEGORY_code品类更改时刷新品类编码
     * @param str_category  品类
     */
    void slot_fresh_le_CATEGORY_code(QString str_category);
    /**
     * @brief slot_fresh_le_PROJECT_NAME_code   项目名称更改时刷项目名称编码
     * @param str_PROJECT_NAME      项目名称
     */
    void slot_fresh_le_PROJECT_NAME_code(QString str_PROJECT_NAME);
    /**
     * @brief slot_fresh_le_REAGENT_TYPE_code   试剂种类更改时刷新试剂种类编码
     * @param str_REAGENT_TYPE      试剂种类
     */
    void slot_fresh_le_REAGENT_TYPE_code(QString str_REAGENT_TYPE);
};

#endif // MYREAGENTDIALOGUPDATA_H
