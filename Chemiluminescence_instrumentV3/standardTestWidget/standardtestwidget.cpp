#include "standardtestwidget.h"
#include <QSqlQuery>
#include <QDateTime>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include "dataopationstandardtest.h"
#include "../data/configfile.h"
#include "systemWidget/reagentNumber/databaseoperation.h"
#define CHECK_MIN 5  //多选框至少选择项数目

standardTestWidget::standardTestWidget(QWidget *parent) : QWidget(parent)
{
    /**
      * @brief 堆栈界面初始化
      */
    WidgetInit();
    connectInit();
}

void standardTestWidget::WidgetInit()
{
    stack = new QStackedWidget(this);
    oneWidget = new standardTest_OneWidget;
    twoWidget = new standardTest_TwoWidget;
    stack->addWidget(oneWidget);
    stack->addWidget(twoWidget);
}

/**
 * @brief 信号槽绑定函数
 */
void standardTestWidget::connectInit()
{
    connect(twoWidget->returnBtn,SIGNAL(clicked()),this,SLOT(twoReturnBtnSlot()));
    connect(twoWidget,SIGNAL(SaveBtnPressSign()),this,SLOT(SaveBtnPressSlot()));
    connect(oneWidget,SIGNAL(nextBtnPressSign()),this,SLOT(nextBtnPressSlot()));
    connect(&serialPort::ReceiveThread,SIGNAL(standard_cmdSign(QString)),this,SLOT(standardTest_cmdSignSlot(QString)), (Qt::ConnectionType)(Qt::UniqueConnection|Qt::QueuedConnection) );
}


/**
 * @brief standardTestWidget::第二个界面返回按钮信号槽
 */
void standardTestWidget::twoReturnBtnSlot()
{
    stack->setCurrentIndex(0);
}


/**
 * @brief 试剂船拔出处理函数
 * @param postion ：试剂船位置
 * @param num  : 1校准品，2质控品
 */
void standardTestWidget::reagentPopup_CMDHandle(int postion,int num)
{
    Q_UNUSED(num);
    if(postion < 0 || postion > 12){
        qDebug()<< "当前试剂船，船舱号超过本设备最大设备船仓数量";
    }
    if( oneWidget->statusWidget->Reagent_status[postion-1] == StatusWidget::RUN){
        emit serialPort::ReceiveThread.ErrDataSign("当前试剂船正在运行,被强制拔出");
    }
    oneWidget->statusWidget->setReagent_Status(postion,StatusWidget::FREE);
    /****试剂船拔出时，清除相应图标数据***********************************************************************/
    for(int i = 1;i < 5; i++ ){
        oneWidget->model->setData(oneWidget->model->index(postion-1,i),QVariant(""));//清空图标数据
    }
    oneWidget->model->setData(oneWidget->model->index(postion-1,6),QVariant(0));  //清空进度条
    for(int i = 6;i < 10; i++ ){
       oneWidget-> model->setData(oneWidget->model->index(postion-1,i),QVariant(""));  //清空图标数据
    }
    oneWidget->tableView->reset();
    oneWidget->okBtnDelegate->okBtn_btns.value(postion-1)->text = tr("");
    oneWidget->okBtnDelegate->okBtn_btns.value(postion-1)->state &= (~QStyle::State_Enabled);
/************清除项目栏类容******当前试剂仓里面一个试剂船也没有****************************************************************************/
    for(int i = 0; i< 12 ;i++){
        if(oneWidget->statusWidget->Reagent_status[i]){
            break;
        }
        if( i == 11 ){
            if( oneWidget->statusWidget->Reagent_status[11] ==  StatusWidget::FREE ){
                oneWidget->tableWidget->item(0,1)->setText("");
                oneWidget->tableWidget->item(0,3)->setText("");
                oneWidget->tableWidget->item(0,5)->setText("" );
                oneWidget->tableWidget->item(0,7)->setText("");
            }
        }

    }

}



/**
 * @brief 设置space_num行试剂船信息内容
 * @param space_num 行
 * @param data 数据
 * @param length 数据长度
 */
void standardTestWidget::setModel_ReagentInfo(int space_num, QByteArray &data, int length)
{
    Q_UNUSED(length);
    int postion = space_num;
    QString sericalNum = "";   //条码号
    QString category = ""; //试剂品类
    QString project_name = "";//项目名称
    QString Reagent_kind = ""; //试剂种类
    QString Detection_Kind = ""; //检测种类
    int Produce_year = 0; //生产日期-年
    int Produce_mouth = 0; //生产日期-月
    int Expiration_date = 0;//保质期
    int Batch_Number = 0;  //批号
    QString temp_serical_number = ""; //临时条码
 /*****************进行ASCII码判断**********************************************************/
    for(int i = 0; i < data.size()-7;i++)
    {
        if( data.at(7+i) < 0x30 ){
            emit serialPort::ReceiveThread.ErrDataSign("扫码枪数据不对");
            return;
        }
    }
/********进行生产日期判断*******************************************************************************/
    if( data.at(7+4) <= 0x39){                            //获取年
        Produce_year = QString::number((data.at(7+4)-0x30),16).toInt() + 2018;
    }else if(data.at(7+4) >=0x41){
        Produce_year = QString::number((data.at(7+4)-0x41),16).toInt() + 2028;
    }

    if( data.at(7+5) <= 0x39){                            //获取月
        Produce_mouth = QString::number((data.at(7+5)-0x30),16).toInt();
    }else if(data.at(7+5) >=0x41){
        Produce_mouth = QString::number((data.at(7+5)-0x41),16).toInt() + 10;
    }

    if( data.at(7+7) == 0x36){  //获取保质期
       Expiration_date = 6;
    }else if( data.at(7+7) == 0x43 ){
       Expiration_date = 12;
    }
    /************获取当前时间*************************/
    int current_date_year = QDateTime::currentDateTime().toString("yyyy").toInt();
    int current_date_mouth = QDateTime::currentDateTime().toString("M").toInt();
 /*************判断是否过期或者条码与实际日期不符合****************************************/
    if( ( current_date_year *12 + current_date_mouth ) < ( Produce_year * 12 + Produce_mouth ) ){
        qDebug() << "当前条码日期比当前实际日期早";
        serialPort::ReceiveThread.ErrDataSign("此条码编码异常");
        return;
    }else if( ( current_date_year *12 + current_date_mouth ) - ( Produce_year * 12 + Produce_mouth ) > Expiration_date ){
        qDebug() << "当前试剂过期";
        serialPort::ReceiveThread.ErrDataSign("此试剂已过期");
        return;
    }

/*****************生产批号*******************************************************************************/
    if( data.at(7+6) <= 0x39){                            //获取批号
        Batch_Number = QString::number((data.at(7+6)-0x30),16).toInt();
    }else if(data.at(7+6) >=0x41){
        Batch_Number = QString::number((data.at(7+6)-0x41),16).toInt() + 10;
    }
/********根据条码检索数据库里面类容*********************************************************/
    for(int i = 0;i < 4 ;i++){
         sericalNum.append(char(data.at(7+i))); //条码前四位
    }
    DatabaseOperation data_op;
    data_op.getReagentInfoByCode(category,project_name,Reagent_kind,sericalNum); //通过数据库得到项目名称和种类
    Detection_Kind = project_name + "-" + Reagent_kind;  //检测项目

    for( int i = 0;i < 3; i++ ){
        sericalNum.append(char(data.at(11+i))); //条码前7位
    }

    temp_serical_number = sericalNum;
    oneWidget->SerialNumber->insert(postion,temp_serical_number.remove(0,1));//储存各试剂船序列号，第二位到第七位条码用于查询标准曲线
    for( int i = 0;i < 4; i++ ){
        sericalNum.append(char(data.at(14+i))); //全部条码
    }
    /******对当前标准品项目试剂进行判别，所有测试是否属于同一项目和试剂种类*****************************************************************************************************************/
    if( oneWidget->tableWidget->item(0,1)->text() ==  "" ){
        oneWidget->tableWidget->item(0,1)->setText(category);
    }
    if( oneWidget->tableWidget->item(0,3)->text() ==  "" ){
        oneWidget->tableWidget->item(0,3)->setText(project_name);
    }
    if( oneWidget->tableWidget->item(0,5)->text() ==  "" ){
        oneWidget->tableWidget->item(0,5)->setText( Reagent_kind );
    }
    if( oneWidget->tableWidget->item(0,7)->text() ==  "" ){
        oneWidget->tableWidget->item(0,7)->setText(sericalNum);
    }
    if( !( category == oneWidget->tableWidget->item(0,1)->text() && project_name == oneWidget->tableWidget->item(0,3)->text() && Reagent_kind ==  oneWidget->tableWidget->item(0,5)->text() ) ){
        QMessageBox::critical(this,tr("错误代码E0026"),tr("错误代码E0026:非同一种类型试剂!"));
       return;
    }

    /***********生产条码和日期***************************************/
    oneWidget->model->setData(oneWidget->model->index(postion-1,1),QVariant( sericalNum ));
    oneWidget->model->setData(oneWidget->model->index(postion-1,2),QVariant( ( QString::number(Produce_year,10) + "-" + QString::number(Produce_mouth,10) )));
    oneWidget->model->setData(oneWidget->model->index(postion-1,3),QVariant( QString::number(Produce_year+ (Produce_mouth + Expiration_date)/12,10) + "-" + QString::number((Produce_mouth + Expiration_date)%12,10) ));
    oneWidget->tableView->reset();
    //插入临时试剂船运行数据进储存QMap
    if(oneWidget->RunData->contains(postion-1)){  //当前位置是否已经有数据
        QMap<int,QString>::iterator it  = oneWidget->RunData->find(postion-1);
        it.value() = oneWidget->getRunInfo(sericalNum.remove(7,4)); //插入数据进入

    }
    else oneWidget->RunData->insert(postion-1,oneWidget->getRunInfo(sericalNum.remove(7,4)));  //查找运行数据并加入QMap进行临时数据保存;


}
/**
 * @brief 测试结果处理函数
 * @param data
 */
void standardTestWidget::testResultHandle(QByteArray &data)
{
    unsigned long photon_result; //最终计算的光子值
    unsigned int temp; //临时变量
    unsigned char postion  = data.at(6 ) & 0xff ; //当前槽号
    if( postion < 1 || postion > 12) return;
    unsigned char photon_number = data.at(6 ) & 0xff ; //当前光子值数量
    unsigned int *TempPhoton_Value = new unsigned int[photon_number] ; //给进行光子运算申请堆空间
    memset(TempPhoton_Value,0,sizeof(unsigned int) * photon_number); //清理堆空间缓存
    for(int i = 0; i < photon_number; i++){
        TempPhoton_Value[i] = ((unsigned int )(data.at(7 + i*4 ) & 0xff)) << 24 | (data.at(8 + i*4) & 0xff) << 16 | (data.at(9 + i*4 ) & 0xff) << 8 | (data.at(10 + i*4 ) & 0xff);
    }
    /*******冒泡排序将光子值进行排序**********************************/
    for(int i = 0;i < photon_number-1;i++){
        for(int j = 0;j < photon_number-i;j++){
            if( TempPhoton_Value[j] > TempPhoton_Value[j+1]){
                temp = TempPhoton_Value[j];
                TempPhoton_Value[j] = TempPhoton_Value[j+1];
                TempPhoton_Value[j+1] = temp;
            }
        }
    }
    /***********取最大10个点之和作为光子值******************************************/
    for(int i = photon_number-1;i > photon_number-11;i-- ){
        photon_result += TempPhoton_Value[i];
    }
    qDebug() <<"当前测试光子数" << photon_result;
    oneWidget->statusWidget->setReagent_Status(postion,StatusWidget::FINISH); //试剂船状态进行切换
    delete []TempPhoton_Value; //释放空间
  /************更新界面设置**************************************************************/
    oneWidget->model->setData(oneWidget->model->index(postion-1,8),QVariant(QString::number(photon_result,10))); //当前光子测试结果
    oneWidget->tableView->reset();
}
/**
 * @brief 试剂船进度处理函数
 * @param postion
 * @num 1:校准品 2：质控品
 */
void standardTestWidget::returnProgress_InfoHandle(QByteArray &data,int interf)
{
    Q_UNUSED(interf);
    unsigned char num = data.at(6)&0xff; //返回进度数量
    unsigned char postion ; //当前槽号
    QString startTime;
    QString endTime;
    QString currentStage; //当前阶段

    for(int i = 0;i < num; i++){
        postion = (data.at(7 + 17*i )&0xff) ;
        qDebug() << "当前试剂船位置 = "<< postion;
        if(postion < 1 || postion > 12) return;

        switch( data.at(8+ 17*i) & 0xff )
        {
        case 1:
            currentStage = "取反应管";
            break;
        case 2:
            currentStage = "取Tap头1";
            break;
        case 3:
            currentStage = "加样本";
            break;
        case 4:
            currentStage = "加试剂1";
            break;
        case 5:
            currentStage = "加试剂2";
            break;
        case 6:
            currentStage = "温育";
            break;
        case 7:
            currentStage = "加磁珠";
            break;
        case 8:
            currentStage = "温育";
            break;
        case 9:
            currentStage = "加试剂3";
            break;
        case 10:
            currentStage = "温育";
            break;
        case 11:
            currentStage = "取Tap头2";
            break;
        case 12:
            currentStage = "第一次洗涤";
            break;
        case 13:
            currentStage = "第二次洗涤";
            break;
        case 14:
            currentStage = "第三次洗涤";
            break;
        case 15:
            currentStage = "移动反应管进发光孔";
            break;
        case 16:
            currentStage = "取Tap头3";
            break;
        case 17:
            currentStage = "加预激发液";
            break;
        case 18:
            currentStage = "取Tap头4";
            break;
        case 19:
            currentStage = "加激发液发光";
            break;
        }
        unsigned char progressData = data.at(9 + i*17) & 0xff; //进度

        unsigned short int start_year = ( (unsigned short int)(data.at(10 + i*17) & 0xff) << 8 ) | ( data.at(11 + i*17) & 0xff );
        unsigned char start_month = data.at(12 + i*17) & 0xff;
        unsigned char start_day = data.at(13 + i*17) & 0xff;
        unsigned char start_hour = data.at(14 + i*17) & 0xff;
        unsigned char start_minute = data.at(15 + i*17) & 0xff;
        unsigned char start_second = data.at(16 + i*17) & 0xff;

        if( !start_year ) continue;
        unsigned short int end_year = ( (unsigned short int)(data.at(17 + i*17) & 0xff) << 8 ) | ( data.at(18 + i*17) & 0xff );
        unsigned char end_month = data.at(19 + i*17) & 0xff;
        unsigned char end_day = data.at(20 + i*17) & 0xff;
        unsigned char end_hour =data.at(21 + i*17) & 0xff;
        unsigned char end_minute = data.at(22 + i*17) & 0xff;
        unsigned char end_second = data.at(23 + i*17) & 0xff;

        startTime += (QString::number(start_year,10) + "/" + QString::number(start_month,10) + "/" + QString::number(start_day,10) +" "
                      +QString::number(start_hour,10) + ":"+QString::number(start_minute,10)+":"+QString::number(start_second,10)  );
        endTime += (QString::number(end_year,10) + "/" + QString::number(end_month,10) + "/" + QString::number(end_day,10) +" "
                    +QString::number(end_hour,10) + ":"+QString::number(end_minute,10)+":"+QString::number(end_second,10)  );

       oneWidget->model->setData(oneWidget->model->index(postion,4),QVariant(currentStage)); //当前阶段
       oneWidget->model->setData(oneWidget->model->index(postion,5),QVariant(progressData)); //当前测试进度
       oneWidget->model->setData(oneWidget->model->index(postion,6),QVariant(startTime)); //开始时间
       oneWidget->model->setData(oneWidget->model->index(postion,7),QVariant(endTime)); //结束时间
       oneWidget->tableView->reset();
    }
}

/**
 * @brief 保存标准品数据槽
 */
void standardTestWidget::SaveBtnPressSlot()
{
#if 1
    qDebug()<<"保存标准点数据";

    //1.数据准备
    QString  STANDARD_CODE          =   oneWidget->tableWidget->item(0,7)->text().mid(0,7);//条码前七位
    QString  CATEGORY               =   oneWidget->tableWidget->item(0,1)->text();//品类
    QString  PROJECT_NAME           =   oneWidget->tableWidget->item(0,3)->text();//项目名称
    QString  REAGENT_TYPE           =   oneWidget->tableWidget->item(0,5)->text();//试剂种类
    QString  BAR_CODE               =   oneWidget->tableWidget->item(0,7)->text();//条码

    double   STANDARD_CONCENTRATION ;//标称浓度
    QString  START_DATE ;//开始日期
    QString  END_DATE ;//结束日期
    char     STANDARD_FLAG ;//AB
    int      PHOTON_VALUE ;//光子值
    double   CONCENTRATION ;//测量浓度
    double   VARIANCE_COEFFICENT ;//CV值
    ConfigFile cf;
    QString CREATOR_ID              =   cf.getCurrentUser_Name();
    QString CREATE_TIME             =   QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString MODIFIER_ID             =   "无";
    QString MODIFY_TIME             =   "无";
    char    DEL_FLAG                =   0;

    //附加表数据准备
    //STANDARD_CODE
    QStringList strlist;//存储12个点的CP值


    //2.查重(只在第一行数据前查重)
    DataOpationStandardtest dost;
    if(dost.isExist_standard_info(STANDARD_CODE))//如果已存在
    {
        //3.是否删除
        QString msg="唯一识别号为:"+STANDARD_CODE+" 的数据已存在，请决定是否更新?";
        myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_QUESTION,tr("提示"),msg,this);
        if(messge->exec() == QDialog::Accepted)//先删除，再新增
        {
//                ConfigFile cf;
//                MODIFIER_ID  =cf.getCurrentUser_Name();
//                MODIFY_TIME =QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
                dost.deleteData_standard_info(STANDARD_CODE) ;
        }
        else
        {
            qDebug()<<"放弃更新!";
            return;
        }
    }
    else    //不存在
    {
//            ConfigFile cf;
//            CREATOR_ID  =cf.getCurrentUser_Name();
//            CREATE_TIME =QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    }

    //4.新增
    for(int i=0;i<12;i++)
    {
        if(i==0&&twoWidget->checkBox1->checkState()==Qt::Unchecked)i++;
        if(i==1&&twoWidget->checkBox2->checkState()==Qt::Unchecked)i++;
        if(i==2&&twoWidget->checkBox3->checkState()==Qt::Unchecked)i++;
        if(i==3&&twoWidget->checkBox4->checkState()==Qt::Unchecked)i++;
        if(i==4&&twoWidget->checkBox5->checkState()==Qt::Unchecked)i++;
        if(i==5&&twoWidget->checkBox6->checkState()==Qt::Unchecked)i++;
        if(i==6&&twoWidget->checkBox7->checkState()==Qt::Unchecked)i++;
        if(i==7&&twoWidget->checkBox8->checkState()==Qt::Unchecked)i++;
        if(i==8&&twoWidget->checkBox9->checkState()==Qt::Unchecked)i++;
        if(i==9&&twoWidget->checkBox10->checkState()==Qt::Unchecked)i++;
        if(i==10&&twoWidget->checkBox11->checkState()==Qt::Unchecked)i++;
        if(i==11&&twoWidget->checkBox12->checkState()==Qt::Unchecked)break;

        //5.数据再准备
        STANDARD_CONCENTRATION  =twoWidget->model->data(twoWidget->model->index(i,5),Qt::DisplayRole).toDouble();
        START_DATE              =twoWidget->model->data(twoWidget->model->index(i,2),Qt::DisplayRole).toString();
        END_DATE                =twoWidget->model->data(twoWidget->model->index(i,3),Qt::DisplayRole).toString();
        STANDARD_FLAG           ='A';//页面无该属性AB
        PHOTON_VALUE            =twoWidget->model->data(twoWidget->model->index(i,4),Qt::DisplayRole).toInt();
        CONCENTRATION           =0;//页面无该属性
        VARIANCE_COEFFICENT     =0;//页面无该属性
        dost.insertData_standard_info(
                    STANDARD_CODE,
                    CATEGORY,
                    PROJECT_NAME,
                    REAGENT_TYPE,
                    BAR_CODE,
                    STANDARD_CONCENTRATION,
                    START_DATE,
                    END_DATE,
                    STANDARD_FLAG,
                    PHOTON_VALUE,
                    CONCENTRATION,
                    VARIANCE_COEFFICENT,
                    CREATOR_ID,
                    CREATE_TIME,
                    MODIFIER_ID,
                    MODIFY_TIME,
                    DEL_FLAG);

        //附加表数据准备
        strlist.append(QString::number(STANDARD_CONCENTRATION));
        strlist.append(QString::number(PHOTON_VALUE));

    }

    //6.附加表（12点表）reagent_standard_info
    if(strlist.isEmpty())return;
    if(dost.isExist_reagent_standard_info(STANDARD_CODE))
    {
        dost.deleteData_reagent_standard_info(STANDARD_CODE) ;
    }
    bool result = dost.insertData_reagent_standard_info(STANDARD_CODE,
                                             strlist,
                                             CREATOR_ID,
                                             CREATE_TIME,
                                             MODIFIER_ID,
                                             MODIFY_TIME,
                                             DEL_FLAG);

    if(result)
    {
        QMessageBox::information(this,tr("提示"),tr("保存数据成功！"),QMessageBox::Ok);
    }

#elif 1
    qDebug()<<"保存标准点数据";

        //1.数据准备
        QString TEST_PROJECT       =oneWidget->tableWidget->item(0,1)->text();//项目名称
        QString FILE_SHORT_NAME   =oneWidget->tableWidget->item(0,3)->text();//项目简写
        QString BAR_CODE     =oneWidget->tableWidget->item(0,5)->text();//条码图像
        ConfigFile cf;
        QString CREATOR_ID  =cf.getCurrentUser_Name();
        QString CREATE_TIME =QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        QString MODIFIER_ID ="无";
        QString MODIFY_TIME ="无";
        int DEL_FLAG   =0;

        //2.查重(只在第一行数据前查重)
        DataOpationStandardtest dost;
        if(dost.isExist_standard_info_v2(FILE_SHORT_NAME))//如果已存在
        {
            //3.是否删除
            QString msg="文件名简写为:"+FILE_SHORT_NAME+" 的数据已存在，请决定是否更新?";
            myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_QUESTION,tr("提示"),msg,this);
            if(messge->exec() == QDialog::Accepted)//先删除，再新增
            {
//                ConfigFile cf;
//                MODIFIER_ID  =cf.getCurrentUser_Name();
//                MODIFY_TIME =QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
                    dost.deleteData_standard_info_v2(FILE_SHORT_NAME) ;
            }
            else
            {qDebug()<<"放弃更新!";return;}
        }
        else
        {
//            ConfigFile cf;
//            CREATOR_ID  =cf.getCurrentUser_Name();
//            CREATE_TIME =QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        }
        //4.新增
        for(int i=0;i<12;i++)
        {
            if(i==0&&twoWidget->checkBox1->checkState()==Qt::Unchecked)continue;
            if(i==1&&twoWidget->checkBox2->checkState()==Qt::Unchecked)continue;
            if(i==2&&twoWidget->checkBox3->checkState()==Qt::Unchecked)continue;
            if(i==3&&twoWidget->checkBox4->checkState()==Qt::Unchecked)continue;
            if(i==4&&twoWidget->checkBox5->checkState()==Qt::Unchecked)continue;
            if(i==5&&twoWidget->checkBox6->checkState()==Qt::Unchecked)continue;
            if(i==6&&twoWidget->checkBox7->checkState()==Qt::Unchecked)continue;
            if(i==7&&twoWidget->checkBox8->checkState()==Qt::Unchecked)continue;
            if(i==8&&twoWidget->checkBox9->checkState()==Qt::Unchecked)continue;
            if(i==9&&twoWidget->checkBox10->checkState()==Qt::Unchecked)continue;
            if(i==10&&twoWidget->checkBox11->checkState()==Qt::Unchecked)continue;
            if(i==11&&twoWidget->checkBox12->checkState()==Qt::Unchecked)break;

                //5.数据再准备
            double STANDARD_CONCENTRATION =twoWidget->model->data(twoWidget->model->index(i,5),Qt::DisplayRole).toDouble();
            QString START_DATE      =twoWidget->model->data(twoWidget->model->index(i,2),Qt::DisplayRole).toString();
            QString END_DATE        =twoWidget->model->data(twoWidget->model->index(i,3),Qt::DisplayRole).toString();
            int STANDARD_FLAG=0;//无该属性
            int PHOTON_VALUE =twoWidget->model->data(twoWidget->model->index(i,3),Qt::DisplayRole).toInt();
            double CONCENTRATION=0;//无该属性
            double VARIANCE_COEFFICENT =0;//无该属性
            int  NUMBER =i+1;//记录位置，无意义
            dost.insertData_standard_info_v2(
                        TEST_PROJECT,FILE_SHORT_NAME,NUMBER,BAR_CODE,STANDARD_CONCENTRATION,START_DATE,END_DATE,STANDARD_FLAG,PHOTON_VALUE,CONCENTRATION,VARIANCE_COEFFICENT,
                        CREATOR_ID,CREATE_TIME,MODIFIER_ID,MODIFY_TIME,DEL_FLAG);

        }








#elif 1
    QVector<double> dataArray;

    int count = 0;  //勾选数据行数，如果小于规定最小值则不允许
    if(twoWidget->checkBox1->checkState() == Qt::Checked){
        if(twoWidget->model->data(twoWidget->model->index(0,4),Qt::DisplayRole).toString().isEmpty()){
            QMessageBox::critical(this,tr("提示!"),tr("不能勾选测量光子值为空的项目栏"));
            dataArray.clear();
            return;
        }
        dataArray << twoWidget->model->data(twoWidget->model->index(0,5),Qt::DisplayRole).toDouble();
        dataArray << twoWidget->model->data(twoWidget->model->index(0,4),Qt::DisplayRole).toDouble();
        ++count;
    }
    if(twoWidget->checkBox2->checkState() == Qt::Checked){
        if(twoWidget->model->data(twoWidget->model->index(1,4),Qt::DisplayRole).toString().isEmpty()){
            QMessageBox::critical(this,tr("提示!"),tr("不能勾选测量光子值为空的项目栏"));
            dataArray.clear();
            return;
        }
        dataArray << twoWidget->model->data(twoWidget->model->index(1,5),Qt::DisplayRole).toDouble();
        dataArray << twoWidget->model->data(twoWidget->model->index(1,4),Qt::DisplayRole).toDouble();
        ++count;
    }
    if(twoWidget->checkBox3->checkState() == Qt::Checked){
        if(twoWidget->model->data(twoWidget->model->index(2,4),Qt::DisplayRole).toString().isEmpty()){
            QMessageBox::critical(this,tr("提示!"),tr("不能勾选测量光子值为空的项目栏"));
            dataArray.clear();
            return;
        }
        dataArray << twoWidget->model->data(twoWidget->model->index(2,5),Qt::DisplayRole).toDouble();
        dataArray << twoWidget->model->data(twoWidget->model->index(2,4),Qt::DisplayRole).toDouble();
        ++count;
    }
    if(twoWidget->checkBox4->checkState() == Qt::Checked){
        if(twoWidget->model->data(twoWidget->model->index(3,4),Qt::DisplayRole).toString().isEmpty()){
            QMessageBox::critical(this,tr("提示!"),tr("不能勾选测量光子值为空的项目栏"));
            dataArray.clear();
            return;
        }
        dataArray << twoWidget->model->data(twoWidget->model->index(3,5),Qt::DisplayRole).toDouble();
        dataArray << twoWidget->model->data(twoWidget->model->index(3,4),Qt::DisplayRole).toDouble();
        ++count;
    }
    if(twoWidget->checkBox5->checkState() == Qt::Checked){
        if(twoWidget->model->data(twoWidget->model->index(4,4),Qt::DisplayRole).toString().isEmpty()){
            QMessageBox::critical(this,tr("提示!"),tr("不能勾选测量光子值为空的项目栏"));
            dataArray.clear();
            return;
        }
        dataArray << twoWidget->model->data(twoWidget->model->index(4,5),Qt::DisplayRole).toDouble();
        dataArray << twoWidget->model->data(twoWidget->model->index(4,4),Qt::DisplayRole).toDouble();
        ++count;
    }
    if(twoWidget->checkBox6->checkState() == Qt::Checked){
        if(twoWidget->model->data(twoWidget->model->index(5,4),Qt::DisplayRole).toString().isEmpty()){
            QMessageBox::critical(this,tr("提示!"),tr("不能勾选测量光子值为空的项目栏"));
            dataArray.clear();
            return;
        }
        dataArray << twoWidget->model->data(twoWidget->model->index(5,5),Qt::DisplayRole).toDouble();
        dataArray << twoWidget->model->data(twoWidget->model->index(5,4),Qt::DisplayRole).toDouble();
        ++count;
    }
    if(twoWidget->checkBox7->checkState() == Qt::Checked){
        if(twoWidget->model->data(twoWidget->model->index(6,4),Qt::DisplayRole).toString().isEmpty()){
            QMessageBox::critical(this,tr("提示!"),tr("不能勾选测量光子值为空的项目栏"));
            dataArray.clear();
            return;
        }
        dataArray << twoWidget->model->data(twoWidget->model->index(6,5),Qt::DisplayRole).toDouble();
        dataArray << twoWidget->model->data(twoWidget->model->index(6,4),Qt::DisplayRole).toDouble();
        ++count;
    }
    if(twoWidget->checkBox8->checkState() == Qt::Checked){
        if(twoWidget->model->data(twoWidget->model->index(7,4),Qt::DisplayRole).toString().isEmpty()){
            QMessageBox::critical(this,tr("提示!"),tr("不能勾选测量光子值为空的项目栏"));
            dataArray.clear();
            return;
        }
        dataArray << twoWidget->model->data(twoWidget->model->index(7,5),Qt::DisplayRole).toDouble();
        dataArray << twoWidget->model->data(twoWidget->model->index(7,4),Qt::DisplayRole).toDouble();
        ++count;
    }
    if(twoWidget->checkBox9->checkState() == Qt::Checked){
        if(twoWidget->model->data(twoWidget->model->index(8,4),Qt::DisplayRole).toString().isEmpty()){
            QMessageBox::critical(this,tr("提示!"),tr("不能勾选测量光子值为空的项目栏"));
            dataArray.clear();
            return;
        }
        dataArray << twoWidget->model->data(twoWidget->model->index(8,5),Qt::DisplayRole).toDouble();
        dataArray << twoWidget->model->data(twoWidget->model->index(8,4),Qt::DisplayRole).toDouble();
        ++count;
    }
    if(twoWidget->checkBox10->checkState() == Qt::Checked){
        if(twoWidget->model->data(twoWidget->model->index(9,4),Qt::DisplayRole).toString().isEmpty()){
            QMessageBox::critical(this,tr("提示!"),tr("不能勾选测量光子值为空的项目栏"));
            dataArray.clear();
            return;
        }
        dataArray << twoWidget->model->data(twoWidget->model->index(9,5),Qt::DisplayRole).toDouble();
        dataArray << twoWidget->model->data(twoWidget->model->index(9,4),Qt::DisplayRole).toDouble();
        ++count;
    }
    if(twoWidget->checkBox11->checkState() == Qt::Checked){
        if(twoWidget->model->data(twoWidget->model->index(10,4),Qt::DisplayRole).toString().isEmpty()){
            QMessageBox::critical(this,tr("提示!"),tr("不能勾选测量光子值为空的项目栏"));
            dataArray.clear();
            return;
        }
        dataArray << twoWidget->model->data(twoWidget->model->index(10,5),Qt::DisplayRole).toDouble();
        dataArray << twoWidget->model->data(twoWidget->model->index(10,4),Qt::DisplayRole).toDouble();
        ++count;
    }

    if(twoWidget->checkBox12->checkState() == Qt::Checked){
        if(twoWidget->model->data(twoWidget->model->index(11,4),Qt::DisplayRole).toString().isEmpty()){
            QMessageBox::critical(this,tr("提示!"),tr("不能勾选测量光子值为空的项目栏"));
            dataArray.clear();
            return;
        }
        dataArray << twoWidget->model->data(twoWidget->model->index(11,5),Qt::DisplayRole).toDouble();
        dataArray << twoWidget->model->data(twoWidget->model->index(11,4),Qt::DisplayRole).toDouble();
        ++count;
    }
    if(count < CHECK_MIN){
        myMessgeBox *messge  = new myMessgeBox(myMessgeBox::MY_MESSAGE_INFORMATION,tr("提示！"),tr("当前勾选项目数量不够，请增加勾选项目"),this);
        if(messge->exec() == QDialog::Accepted){   //模式对话框
        }
        return;
    }
    QSqlQuery query;
    query.exec("insert into reagent_standard_info values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
    query.bindValue(1,oneWidget->tableWidget->item(0,3)->text());
    int pos = 2; //插入数据库数据位置
    QVector<double>::iterator iter;
    for(iter = dataArray.begin();iter != dataArray.end();iter++){
        query.bindValue(pos,*iter);
        pos++;
    }
    dataArray.clear();  //清除容器里面的元素
    for(;pos < 26;pos++){
        query.bindValue(pos,0);
    }
    query.bindValue(26,0);
    query.bindValue(27,QDateTime::currentDateTime().toString());
    query.bindValue(28,0);
    query.bindValue(29,0);
    query.bindValue(30,0);


    if(!query.exec())
    {
        QMessageBox::critical(this,QObject::tr("错误代码:E0018"),query.lastError().text());
    }else{
        QMessageBox::critical(this,QObject::tr("提示!"),tr("标准品数据保存成功!"));
    }

    //保存完数据清空
    twoWidget->checkBox1->setCheckState(Qt::Unchecked);
    twoWidget->checkBox2->setCheckState(Qt::Unchecked);
    twoWidget->checkBox3->setCheckState(Qt::Unchecked);
    twoWidget->checkBox4->setCheckState(Qt::Unchecked);
    twoWidget->checkBox5->setCheckState(Qt::Unchecked);
    twoWidget->checkBox6->setCheckState(Qt::Unchecked);
    twoWidget->checkBox7->setCheckState(Qt::Unchecked);
    twoWidget->checkBox8->setCheckState(Qt::Unchecked);
    twoWidget->checkBox9->setCheckState(Qt::Unchecked);
    twoWidget->checkBox10->setCheckState(Qt::Unchecked);
    twoWidget->checkBox11->setCheckState(Qt::Unchecked);
    twoWidget->checkBox12->setCheckState(Qt::Unchecked);
#endif
}


/**
 * @brief 在下一步按钮被点击触发槽
 */
void standardTestWidget::nextBtnPressSlot()
{
    //在这里要判断当前工作是否完成
    for(int i = 0; i < 12;i++){ //第一个界面和第二个页面进行数据拷贝
        if(!oneWidget->model->data(oneWidget->model->index(i,8)).toString().isEmpty()){
            twoWidget->model->setData( twoWidget->model->index(i,4),oneWidget->model->data(oneWidget->model->index(i,8)) );
            twoWidget->model->setData( twoWidget->model->index(i,5),oneWidget->model->data(oneWidget->model->index(i,9)) );
            twoWidget->model->setData( twoWidget->model->index(i,1),oneWidget->model->data(oneWidget->model->index(i,1)) );
            twoWidget->model->setData( twoWidget->model->index(i,2),oneWidget->model->data(oneWidget->model->index(i,2)) );
            twoWidget->model->setData( twoWidget->model->index(i,3),oneWidget->model->data(oneWidget->model->index(i,3)) );
        }
    }
    stack->setCurrentIndex(1);
}

/**
 * @brief 试剂船错误处理函数
 * @param err
 */
void standardTestWidget::returnRegent_ErrHandle(QByteArray &err)
{
    Q_UNUSED(err);

}
/**
 * @brief standardTestWidget::标准品CMD信号槽
 * @param str
 */
void standardTestWidget::standardTest_cmdSignSlot(QString str)
{
    QByteArray Receive_array = 0;
    QString returnCMD = "";
    int postion = 0;
    qDebug() << "标准品测试收到一条命令" << str;
    qDebug() << "处理接收数据"  << "线程号" << QThread::currentThreadId();
    Receive_array = serialPort::HEXStringToArr(str);
    uint16_t dataLength = (uint16_t)(((Receive_array.at(4)&0xffff)<< 8)|(Receive_array.at(5)&0xff));//数据长度
    unsigned char cmd = (Receive_array.at(1) & 0xff); //命令

    if( ( Receive_array.at(0) & 0xff) & 0x40 ){   //MCU返回码命令解析
        switch(cmd){
        case STANDARD_WHETHER_FREE_RETURN_CMD:
            qDebug()<< "标准品测试收到MCU空闲命令返回";
            if( dataLength != 1){
                qDebug() << "标准品测试空闲命令缺少数据";
                return;
            }
            if( !( Receive_array.at(6) & 0xff ) ){ //判断是否空闲
                qDebug() << "是空闲命令";
                 if( !oneWidget->WorkQueue->isEmpty()){ /**<发送任务队列队首 */
                     QString str;
                     oneWidget->WorkQueue->dequeue(str);
                     qDebug() << "队列字符串"<< str;
                     emit serialPort::ReceiveThread.sendDataSign(str);
                 }
            }else qDebug() << "是忙命令";
            break;
        case STANDARD_WHEHTER_SCHED_RETURN_CMD:
            if( dataLength != 1){
                qDebug() << "标准品测试调度命令缺少数据";
                return;
            }
            qDebug()<< "标准品测试收到MCU可不可以调度命令返回";
            if( !(Receive_array.at(6) & 0xff) ){ //判断是否空闲
                qDebug() << "是不可调度命令";
            }else qDebug() << "是可调度命令";
            break;
        }
        return;
    }
    /***MCU主动发送的命令解析************************************************/
    switch(cmd){
    case STANDARD_PULL_SHIP_CMD :
        qDebug()<< "标准品测试收到MCU有试剂船拔出命令";
        if( dataLength != 1){
            //插入错误数据表
            qDebug() << "校准拔出命令数据长度不对";
             emit serialPort::ReceiveThread.ErrDataSign("数据长度不对");
            return;
        }
        postion = Receive_array.at(6)&0xff;//位置
        reagentPopup_CMDHandle( postion,2);
        returnCMD = "03,02,ff,ff,00,02,"+QString::number(postion,10)+",02"; //绿灯灭
        emit serialPort::ReceiveThread.sendDataSign(returnCMD);
        break;
    case STANDARD_ALL_TEST_PROGRESS_CMD:
        qDebug()<< "标准品测试收到所有试剂船进度MCU命令";
        if( !( dataLength == 205 || dataLength == 18 ) ){
            //插入错误数据表
            qDebug() << "未知品收到所有试剂船进度MCU命令数据长度不对";
            emit serialPort::ReceiveThread.ErrDataSign("数据长度不对");
            return;
        }
        returnProgress_InfoHandle( Receive_array,1);
        break;
    case STANDARD_ERR_CMD:
        qDebug()<< "标准品测试收到错误信息MCU命令";
        returnRegent_ErrHandle( Receive_array );
        break;
    case STANDARD_NEW_SHIP_INFOR_CMD:
        qDebug()<< "标准品测试收到一条插入新试剂船信息";
        if( dataLength != 17){
            //插入错误数据表
            qDebug() << "未知品插入新试剂船命令数据长度不对";
            emit serialPort::ReceiveThread.ErrDataSign("数据长度不对");
            return;
        }
        postion = Receive_array.at(6)&0xff;
        if( postion <= 12 && postion > 0 ){   //试剂船船舱号最大也就12个船舱
            oneWidget->statusWidget->setReagent_Status(postion,StatusWidget::AWAIT);//设置试剂船现在状态
            setModel_ReagentInfo(postion,Receive_array,dataLength); //设置当前试剂船条码
            returnCMD = "03,01,ff,ff,00,02,"+QString::number(postion,16)+",00"; //红灯闪
            emit serialPort::ReceiveThread.sendDataSign(returnCMD);
        }
        break;
    case STANDARD_ONE_TEST_DATA_CMD:
        qDebug()<< "标准品测试某一条试剂测试结果信息";
        if( dataLength != 5){
            qDebug() << "标准品测试某一条试剂测试结果缺少数据";
            return;
        }
        postion = Receive_array.at(6)&0xff;
        returnCMD = "03,01,ff,ff,00,02,"+QString::number(postion,10)+",02";
        emit serialPort::ReceiveThread.sendDataSign(returnCMD);
        for(int i = 0;i< 1000;i++){}
        returnCMD = "03,02,ff,ff,00,02,"+QString::number(postion,10)+",01";
        emit serialPort::ReceiveThread.sendDataSign(returnCMD);             
        /**
        ** 处理测试结果
        **/
        testResultHandle(Receive_array); //测试结果
        break;
    }
}






