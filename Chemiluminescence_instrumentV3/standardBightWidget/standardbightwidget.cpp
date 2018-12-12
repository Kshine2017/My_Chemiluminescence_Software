#include "standardbightwidget.h"
#include "QFont"
#include "data\util.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>


#define Fuction_COEFFICIENT_COUNT 4 //函数系统个数
bool standardBightWidget::CurveDisplayFlag = false;

standardBightWidget::standardBightWidget(QWidget *parent):QWidget(parent)
{
    //头图标初始化
    titleInit();
    BtnInit();
    cruveGeneration = NULL;
    windowLayout = new QHBoxLayout; //显示界面布局
    mainlayout = new QVBoxLayout(this);    //主界面
    controlWidget = new standBight_controlWidget;  //控制界面
    DrawWidget = new standardBight_draweWidget;   //绘图界面
    windowLayout->addWidget(controlWidget);
    windowLayout->addWidget(DrawWidget);
    mainlayout->addSpacing(60);
    mainlayout->addLayout(btnLayout);
    mainlayout->addLayout(windowLayout);

    connectInit();
}


/**
 * @brief 窗口标题头初始化
 */
void standardBightWidget::titleInit()
{
    titleIconLab = new QLabel(this);   //头图标
    titleIconLab->setPixmap(QPixmap(":/picture/standardPrograme/tile_icon.png"));

    titleTextLab = new QLabel(titleIconLab); //标题文字
    titleTextLab->setText(tr("标准曲线生成"));

    QPalette   pal;//按键字体颜色设置
    pal.setColor(QPalette::WindowText, QColor(255, 255, 255, 255));
    titleTextLab->setPalette(pal);
    titleTextLab->setFont(QFont("windowTitle",15));
    titleTextLab->setGeometry(75,13,150,40);

    questionBtn = new QPushButton(titleIconLab); //问号按钮
    questionBtn->setIconSize(QSize(46,45));
    questionBtn->setIcon(QIcon(":/picture/standardPrograme/？btn.png"));
    questionBtn->setFlat(true);
    questionBtn->setGeometry(1600,1,45,45);
    titleIconLab->setGeometry(0,0,1687,67);


}

/**
 * @brief standardBightWidget::按钮初始化
 */
void standardBightWidget::BtnInit()
{
    //    QFont *font = new QFont("btnFont",15);

    //    saveBtn = new QPushButton; //保存按钮
    //    saveBtn->setIconSize(QSize(50,50));
    //    saveBtn->setIcon(QIcon(":/picture/standardBight/saveBtn.png"));
    //    saveBtn->setText(tr("保存"));
    //    saveBtn->setFixedSize(110,50);
    //    saveBtn->setFont(*font);
    //    saveBtn->setFlat(true);
        saveBtn = new QPushButton();
        saveBtn->setFlat(true);
        saveBtn->setFocusPolicy(Qt::TabFocus);
        saveBtn->setFixedSize(85,32);//图片的固定大小85 32
        saveBtn->setStyleSheet("QPushButton{border-image: url(:/picture/standardBight/saveBtn-up.png);}"
                                 "QPushButton:hover{border-image: url(:/picture/standardBight/saveBtn-up.png);}"
                                 "QPushButton:pressed{border-image: url(:/picture/standardBight/saveBtn-down.png);}");

    //    quitBtn = new QPushButton; //退出按钮
    //    quitBtn->setIconSize(QSize(50,50));
    //    quitBtn->setIcon(QIcon(":/picture/standardBight/quitBtn.png"));
    //    quitBtn->setText(tr("退出"));
    //    quitBtn->setFixedSize(110,50);
    //    quitBtn->setFont(*font);
    //    quitBtn->setFlat(true);

        quitBtn = new QPushButton();
        quitBtn->setFlat(true);
        quitBtn->setFocusPolicy(Qt::TabFocus);
        quitBtn->setFixedSize(85,32);//图片的固定大小85 32
        quitBtn->setStyleSheet("QPushButton{border-image: url(:/picture/standardBight/quitBtn-up.png);}"
                                 "QPushButton:hover{border-image: url(:/picture/standardBight/quitBtn-up.png);}"
                                 "QPushButton:pressed{border-image: url(:/picture/standardBight/quitBtn-down.png);}");

        btnLayout = new QHBoxLayout; //按钮水平布局
        btnLayout->addWidget(saveBtn);
        btnLayout->addWidget(quitBtn);
        btnLayout->addSpacing(1200);

}

/**
 * @brief 绑定信号和槽初始化
 */
void standardBightWidget::connectInit()
{
    connect(saveBtn,SIGNAL(clicked()),this,SLOT(saveBtnSlot()));
    connect(quitBtn,SIGNAL(clicked()),this,SLOT(quitBtnSlot()));
    connect(controlWidget->produceBightBtn,SIGNAL(clicked()),this,SLOT(createCurve()));
//    connect(controlWidget->checkBoxBtn1,SIGNAL(stateChanged(int)),this,SLOT(checkBoxBtn1Slot(int)));
//    connect(controlWidget->checkBoxBtn2,SIGNAL(stateChanged(int)),this,SLOT(checkBoxBtn2Slot(int)));
//    connect(controlWidget->checkBoxBtn3,SIGNAL(stateChanged(int)),this,SLOT(checkBoxBtn3Slot(int)));
//    connect(controlWidget->checkBoxBtn4,SIGNAL(stateChanged(int)),this,SLOT(checkBoxBtn4Slot(int)));
//    connect(controlWidget->checkBoxBtn5,SIGNAL(stateChanged(int)),this,SLOT(checkBoxBtn5Slot(int)));
//    connect(controlWidget->checkBoxBtn6,SIGNAL(stateChanged(int)),this,SLOT(checkBoxBtn6Slot(int)));
//    connect(controlWidget->checkBoxBtn7,SIGNAL(stateChanged(int)),this,SLOT(checkBoxBtn7Slot(int)));

    connect(controlWidget->radioBtn1,SIGNAL(clicked()),this,SLOT(radioBtnSlot()));
    connect(controlWidget->radioBtn2,SIGNAL(clicked()),this,SLOT(radioBtnSlot()));
    connect(controlWidget->radioBtn3,SIGNAL(clicked()),this,SLOT(radioBtnSlot()));
    connect(controlWidget->radioBtn4,SIGNAL(clicked()),this,SLOT(radioBtnSlot()));
    connect(controlWidget->radioBtn5,SIGNAL(clicked()),this,SLOT(radioBtnSlot()));
    connect(controlWidget->radioBtn6,SIGNAL(clicked()),this,SLOT(radioBtnSlot()));
    connect(controlWidget->radioBtn7,SIGNAL(clicked()),this,SLOT(radioBtnSlot()));
}

/**
 * @brief 控制显示曲线
 */
void standardBightWidget::controlDisCurve()
{
    if( !cruveGeneration ) return;

    if( controlWidget->checkBoxBtn1->checkState() == Qt::Checked ){
        cruveGeneration->setCruveVisible_Log_Logist(true);
    }else{
        cruveGeneration->setCruveVisible_Log_Logist(false);
    }

    if( controlWidget->checkBoxBtn2->checkState() == Qt::Checked ){
        cruveGeneration->setCruveVisible_Duoxiangshi(true);
    }else{
        cruveGeneration->setCruveVisible_Duoxiangshi(false);
    }
    if( controlWidget->checkBoxBtn3->checkState() == Qt::Checked ){
        cruveGeneration->setCruveVisible_Logistic(true);
    }else{
        cruveGeneration->setCruveVisible_Logistic(false);
    }

    if( controlWidget->checkBoxBtn5->checkState() == Qt::Checked ){
        cruveGeneration->setCruveVisible_LogLinearFit(true);
    }else{
        cruveGeneration->setCruveVisible_LogLinearFit(false);
    }



}


/**
 * @brief 根据单选框设置重新生成曲线并显示函数和R^2值;
 */
void standardBightWidget::setFuctionString()
{
    createCurve();
}


/**
 * @brief standardBightWidget::保存和退出按钮信号槽
 */
void standardBightWidget::saveBtnSlot()
{


    //保存标准曲线系数
    QSqlQuery query;

    if(!standardBightWidget::CurveDisplayFlag){
        QMessageBox::critical(this,tr("提示!"),tr("当前参数没有生成，无法保存!"));
        return;
    }else{
        standardBightWidget::CurveDisplayFlag = false;
        //保存当前参数

        double *coefficient;
        int type;   //拟合类型
        if( controlWidget->radioBtn1->isChecked()){
            type = LOGLOGISTIC;
            coefficient = cruveGeneration->lr->getcoeff();
        }else if( controlWidget->radioBtn2->isChecked()){
            coefficient = cruveGeneration->duoxiangshi->getCoefficient();
            type = DUOXIANGSHI;
        }else if( controlWidget->radioBtn3->isChecked()){  //  四参数y = d+(a-d)/(1+(x/c)^b)
            type = LOGISTIC;
            coefficient = cruveGeneration->logistic->getCoefficient();
        }else if( controlWidget->radioBtn4->isChecked()){

        }else if( controlWidget->radioBtn5->isChecked()){
            type = LOGLINEARFIT;
            coefficient = cruveGeneration->linear_fit->getcoef();
            coefficient[2] = cruveGeneration->linear_fit->F0;
        }else if( controlWidget->radioBtn6->isChecked()){

        }else if( controlWidget->radioBtn7->isChecked()){

        }
        // 查询数据库中是否存在该项目的曲线，如果存在 ，则选择是否覆盖？

        query.exec("select ID,DEL_FLAG from cruve_parameter where REAGENT_CODE = " + controlWidget->strBarCode);
        while(query.next())
        {
            QString id = query.value("ID").toString();
            qDebug()<<"id------"<<id;
            int flag = query.value("DEL_FLAG").toInt();
            if(flag == 0){
                if(QMessageBox::question(this,tr("提示"),tr("已存在该项目曲线,是否覆盖？")) == QMessageBox::Yes)
                {
                    QSqlQuery query2;
                    query2.exec("UPDATE cruve_parameter SET DEL_FLAG = 1 where ID = " + id);
                }else
                {
                    return;
                }
            }
        }

        //保存标准点信息
        controlWidget->saveStandData();

        //点击哪个确认按钮将数据写入数据库cruve_parameter
        //query.exec("insert into cruve_parameter values(NULL,'2',3,1.1,2.2,3.3,4.4,5.5,6.6,'2017-11-23 16:43:00','11','12','13','0')");

        query.exec("insert into cruve_parameter values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
//        query.bindValue(0,__null);    //第一列的数据 （第一列为主键，不用添加数据）

        query.bindValue(1,controlWidget->strCateGory);
        query.bindValue(2,controlWidget->strCateGoryCode);
        query.bindValue(3,controlWidget->strProjectName);
        query.bindValue(4,controlWidget->strProjectNameCode);
        query.bindValue(5,controlWidget->strReagentType);
        query.bindValue(6,controlWidget->strReagentTypeCode);
        query.bindValue(7,controlWidget->strBarCode.remove(0,1));
        query.bindValue(8,type);
        query.bindValue(9,coefficient[0]);
        query.bindValue(10,coefficient[1]);
        query.bindValue(11,coefficient[2]);
        query.bindValue(12,coefficient[3]);
        query.bindValue(13,0.0);
        query.bindValue(14,0.0);
        query.bindValue(15,0);
        query.bindValue(16,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        query.bindValue(17,0);
        query.bindValue(18,0);
        query.bindValue(19,0);
        if(!query.exec())
        {
            QMessageBox::critical(this,QObject::tr("错误代码:E0016"),query.lastError().text());
        }else{
            QMessageBox::information(this,tr("提示！"),tr("已成功保存！"));
            return;
        }
    }
}

void standardBightWidget::quitBtnSlot()
{
    if(standardBightWidget::CurveDisplayFlag){
        if(QMessageBox::information(this,tr("提示!"),tr("当前参数没有保存，是否退出!"),QMessageBox::Ok,QMessageBox::Cancel) == QMessageBox::Ok){
            emit quitOkSign();
        }else return;
    }else emit quitOkSign();
}

/**
 * @brief 生成曲线，并显示曲线函数和拟合优度
 */
void standardBightWidget::createCurve()
{
    //更改拟合曲线名称及拟合优度
    double *coefficient;
    QString coefficient_str;        //曲线方程式
    QString R_R_str;                //曲线拟合优度

    int count = 0; //勾选标准点数
    QVector<double> C_Data =  controlWidget->ReturnCheck_C_Data();
    QVector<double> P_Data = controlWidget->ReturnCheck_P_Data();

    if(C_Data.isEmpty()) return;

    count = C_Data.count();
    double x[count];
    double y[count];
    QVector<double>::iterator iter;
    int i = 0;
    int j = 0;
    for(iter = C_Data.begin();iter!= C_Data.end();iter++){
        x[i] = *iter;
        i++;
    }

    for(iter = P_Data.begin();iter!= P_Data.end();iter++){
        y[j] = *iter;
        j++;
    }
    if(standardBightWidget::CurveDisplayFlag){
        delete cruveGeneration;
    }else  standardBightWidget::CurveDisplayFlag = true;

    int type = -1; //曲线拟合类型

    if(controlWidget->radioBtn1->isChecked())  //logistic拟合
    {
        type = LOGLOGISTIC;
    }
    else if(controlWidget->radioBtn2->isChecked())  //多项式拟合
    {
        type = DUOXIANGSHI;
    }
    else if(controlWidget->radioBtn3->isChecked()) //  四参数y = d+(a-d)/(1+(x/c)^b)
    {
        type = LOGISTIC;
    }
    else if(controlWidget->radioBtn4->isChecked())
    {

    }
    else if(controlWidget->radioBtn5->isChecked())     //对数线性拟合
    {
        type = LOGLINEARFIT;
    }
    else if(controlWidget->radioBtn6->isChecked())
    {

    }
    else if(controlWidget->radioBtn7->isChecked())
    {

    }

    //画曲线
    cruveGeneration = new CruveGeneration(DrawWidget->drawWidget,x,y,count,Fuction_COEFFICIENT_COUNT,type);
    cruveGeneration->show();



    if(controlWidget->radioBtn1->isChecked())  //logistic拟合
    {

        coefficient = cruveGeneration->lr->getcoeff();
        QString str = "y = %1/(1+(%2/%3-1)*e^(-%4*x))";
        coefficient_str = str.arg(QString::number(coefficient[0],10,6),QString::number(coefficient[0],10,6),QString::number(coefficient[1],10,6),QString::number(coefficient[2],10,6));
        R_R_str.append(QString::number(cruveGeneration->lr->getBestR(),10,6));
    }
    else if(controlWidget->radioBtn2->isChecked())  //多项式拟合
    {
        coefficient = cruveGeneration->duoxiangshi->getCoefficient();
        coefficient_str.append("y = "+ QString::number(coefficient[0],10,6));
        for(int i = 1;i < Fuction_COEFFICIENT_COUNT;i++){
            if(coefficient[i] > 0){
                coefficient_str.append("+"+QString::number(coefficient[i],10,6)+"x^"+QString::number(i));
            }else{
                coefficient_str.append(QString::number(coefficient[i],10,6)+"x^"+QString::number(i));
            }
        }
        R_R_str.append(QString::number(cruveGeneration->duoxiangshi->getR(),10,6));
    }
    else if(controlWidget->radioBtn3->isChecked()) //  四参数y = d+(a-d)/(1+(x/c)^b)
    {
        coefficient = cruveGeneration->logistic->getCoefficient();
        QString str = "y = (%1-%2)/(1+(x/%3)^%4)+%5";
        coefficient_str = str.arg(QString::number(coefficient[0],10,6),QString::number(coefficient[3],10,6),QString::number(coefficient[2],10,6),QString::number(coefficient[1],10,6),QString::number(coefficient[3],10,6));
        R_R_str.append(QString::number(cruveGeneration->logistic->getR(),10,6));
    }
    else if(controlWidget->radioBtn4->isChecked())
    {

    }
    else if(controlWidget->radioBtn5->isChecked())     //对数线性拟合
    {
        coefficient = cruveGeneration->linear_fit->getcoef();
        QString str = "y = %1+%2*x";
        coefficient_str = str.arg(QString::number(coefficient[0],10,6),QString::number(coefficient[1],10,6));
        R_R_str.append(QString::number(cruveGeneration->linear_fit->getR(),10,6));
    }
    else if(controlWidget->radioBtn6->isChecked())
    {

    }
    else if(controlWidget->radioBtn7->isChecked())
    {

    }


    //显示拟合曲线名称，和曲线拟合优度
    DrawWidget->setfuctionLab(coefficient_str,R_R_str);


}


/**
 * @brief 7个函数显示选择按钮槽
 */
void standardBightWidget::checkBoxBtn1Slot(int state)
{
    if(state == Qt::Checked){
        createCurve();
        controlDisCurve();
    }else if(state == Qt::Unchecked){
        createCurve();
        controlDisCurve();
    }
}

void standardBightWidget::checkBoxBtn2Slot(int state)
{
        if(state == Qt::Checked){
            createCurve();
            controlDisCurve();
        }else if(state == Qt::Unchecked){
            createCurve();
            controlDisCurve();
        }
}

void standardBightWidget::checkBoxBtn3Slot(int state)
{
        if(state == Qt::Checked){
            createCurve();
            controlDisCurve();
        }else if(state == Qt::Unchecked){
            createCurve();
            controlDisCurve();
        }
}

void standardBightWidget::checkBoxBtn4Slot(int state)
{
    if(state == Qt::Checked){
        createCurve();
        controlDisCurve();
    }else if(state == Qt::Unchecked){
        createCurve();
        controlDisCurve();
    }
}

void standardBightWidget::checkBoxBtn5Slot(int state)
{
    if(state == Qt::Checked){
        createCurve();
        controlDisCurve();
    }else if(state == Qt::Unchecked){
        createCurve();
        controlDisCurve();
    }
}

void standardBightWidget::checkBoxBtn6Slot(int state)
{
    if(state == Qt::Checked){
        createCurve();
        controlDisCurve();
    }else if(state == Qt::Unchecked){
        createCurve();
        controlDisCurve();
    }
}

void standardBightWidget::checkBoxBtn7Slot(int state)
{
    if(state == Qt::Checked){
        createCurve();
        controlDisCurve();
    }else if(state == Qt::Unchecked){
        createCurve();
        controlDisCurve();
    }
}


/**
 * @brief 显示曲线单选按钮
 */
void standardBightWidget::radioBtnSlot()
{
    if(standardBightWidget::CurveDisplayFlag){
        setFuctionString();
    }
}
