/**
  *  @brief   standbight_controlwidget.h  生产标准曲线的控制界面
  *  @file    standbight_controlwidget.h
  *  @author   谢飞
  *  @version  1.0(版本号)
  *  @date     2017-10-16
  */
#ifndef STANDBIGHT_CONTROLWIDGET_H
#define STANDBIGHT_CONTROLWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTableView>
#include <QListWidget>
#include <QHeaderView>
#include <QPainter>
#include <QCheckBox>
#include <QGridLayout>
#include <QStandardItemModel>
#include <QPalette>
#include <QComboBox>
#include <QRadioButton>
#include <QDateEdit>
#include <QDate>
class standBight_controlWidget:public QWidget
{
        Q_OBJECT
public:
    explicit standBight_controlWidget(QWidget *parent = 0);

    enum{
        LOG_LOGIST = 1,
        POLYNOMIAL,
        FOUR_PARAME,
        LOG_LN,
    };
private:
    /**
     * @brief 控制界面初始化
     */
    void controlWindowInit();
    /**
     * @brief 信号和槽绑定函数初始化
     */
    void connectInit();
    /**
     * @brief 模型视图初始化
     */
    void tableViewInit();
    /**
     * @brief 函数选择视图初始化
     */
    void fuctionViewInit();
    /**
     * @brief 标准点多选按钮初始化
     */
    void PointCheckWidgetInit();

public:
    QString strBarCode; //七位条码
    QString strCateGory; //品类
    QString strCateGoryCode; //品类条码
    QString strProjectName; //项目名称
    QString strProjectNameCode; //项目名称条码
    QString strReagentType; //试剂种类
    QString strReagentTypeCode; //试剂种类条码



public:
    /**
     * @brief saveStandData
     * 保存标准点信息
     */
    void saveStandData();
    /**
     * @brief 生成曲线时，返回选择浓度值
     * @return
     */
    QVector<double> ReturnCheck_C_Data();
    /**
     * @brief 生成曲线时，返回选择光子值
     * @return
     */
    QVector<double> ReturnCheck_P_Data();

public:
    QPushButton *produceBightBtn;  //生成曲线按钮
    //7个多选按钮
      QCheckBox *checkBoxBtn1;
      QCheckBox *checkBoxBtn2;
      QCheckBox *checkBoxBtn3;
      QCheckBox *checkBoxBtn4;
      QCheckBox *checkBoxBtn5;
      QCheckBox *checkBoxBtn6;
      QCheckBox *checkBoxBtn7;

      //7个单选按钮
      QRadioButton *radioBtn1;
      QRadioButton *radioBtn2;
      QRadioButton *radioBtn3;
      QRadioButton *radioBtn4;
      QRadioButton *radioBtn5;
      QRadioButton *radioBtn6;
      QRadioButton *radioBtn7;

      QComboBox *combox;       //下拉选择框
      QComboBox *combox_projectName;        //项目名称下拉框
      QComboBox *combox_reagentType;        //试剂种类下拉框
      QComboBox *combox_productionDate;     //生产日期下拉框
      QDateEdit *dateEdit_productionDate;   //生产日期下拉框
      QComboBox *combox_lotNumber;          //批号下拉框

private:
    QLabel *checkTitleLabel;  // 选择标题
    QLabel *label_projectName;        //项目名称标题
    QLabel *label_reagentType;        //试剂种类标题
    QLabel *label_productionDate;     //生产日期标题
    QLabel *label_lotNumber;          //批号标题
    QLabel *fuctionLabel;     //函数标题




    QPushButton *resetBightBtn;   //重置曲线按钮


private:
    QTableView *parameterTableView;     //浓度参数视图
    QStandardItemModel *sqlModel;       //数据库模型
    QListWidget *fuctionListWidget;      //方程式视图


private:
    QWidget *fuctionWidget;   //函数选择窗口
    QWidget *parameterWidget; //参数界面窗口


private:
    QWidget *radioWidget;  //单选窗口
    QWidget *checkBoxWidget; //多选窗口
    QWidget *pointCheckWidget; //标准点选择窗口

  //12个标准点多选按钮
    QCheckBox *PCheckBtn1;
    QCheckBox *PCheckBtn2;
    QCheckBox *PCheckBtn3;
    QCheckBox *PCheckBtn4;
    QCheckBox *PCheckBtn5;
    QCheckBox *PCheckBtn6;
    QCheckBox *PCheckBtn7;
    QCheckBox *PCheckBtn8;
    QCheckBox *PCheckBtn9;
    QCheckBox *PCheckBtn10;
    QCheckBox *PCheckBtn11;
    QCheckBox *PCheckBtn12;


   //7个选择颜色指示
    QLabel *checkLabel1;
    QLabel *checkLabel2;
    QLabel *checkLabel3;
    QLabel *checkLabel4;
    QLabel *checkLabel5;
    QLabel *checkLabel6;
    QLabel *checkLabel7;

 //选择按钮布局管理器
    QVBoxLayout *radioBtnLayout;  //单选按钮布局
    QVBoxLayout *checkBtnLayout;  //多选按钮布局
    QVBoxLayout *checkLabelLayout;//
    QVBoxLayout *PointcheckBtnLayout; //标准点布局
    QHBoxLayout *ParameterWidgetLayout;//参数界面布局



private:
    QHBoxLayout *btnLayout;    //按钮布局器
    QHBoxLayout *checkLayout;  //选择布局管理器
    QVBoxLayout *mainLayout;  //主布局管理器

    //选择下拉框更改
    QHBoxLayout *checkLayout1;
    QHBoxLayout *checkLayout2;
    QHBoxLayout *checkLayout3;
    QHBoxLayout *checkLayout4;

    QHBoxLayout *fuctionWidgetLayout; //函数窗口选择布局器

private:
    void init_comboxData();
signals:

public slots:
    void initReagentType(QString strProjectName);
    void initLotNumber(QString str);
    void initLotNumber(QDate date);
    void resetBightBtnSlot();

    void currentTextChangedSlot(const QString &text);
};

#endif // STANDBIGHT_CONTROLWIDGET_H
