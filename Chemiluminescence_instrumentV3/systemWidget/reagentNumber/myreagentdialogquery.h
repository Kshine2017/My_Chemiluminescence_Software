#ifndef MYREAGENTDIALOGQUERY_H
#define MYREAGENTDIALOGQUERY_H

#include <QWidget>
#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>

class MyReagentDialogQuery : public QDialog
{
    Q_OBJECT
public:
    explicit MyReagentDialogQuery(QWidget *parent = 0);

private:

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


signals:
    siganl_please_fresh_table(QString str_category,QString str_projectName,QString str_REAGENT_TYPE);

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

#endif // MYREAGENTDIALOGQUERY_H
