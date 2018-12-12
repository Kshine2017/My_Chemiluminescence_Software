#include "calibrationwidget.h"
#include "QMessgeBox/mymessgebox.h"

#include <QMessageBox>
#include <QDebug>
#include "systemWidget/reagentNumber/databaseoperation.h"
calibrationWidget::calibrationWidget(QWidget *parent) : QWidget(parent)
{
    /**
      * @brief 堆栈界面初始化
      */
     WidgetInit();
     connectInit();

}
/**
 * @brief 堆栈界面初始化
 */
void calibrationWidget::WidgetInit()
{
    stack = new QStackedWidget(this);
    oneWidget = new calibration_oneWidget;
    twoWidget = new calibration_twoWidget;
    caliOneWidget = new calibration_caliOneWidget;
    qualityOneWidget = new calibration_qualityOneWidget; /**< 质控第一个界面*/   


    stack->addWidget(oneWidget);
    stack->addWidget(twoWidget);
    stack->addWidget(caliOneWidget);
    stack->addWidget(qualityOneWidget);


}

/**
 * @brief 信号槽绑定
 */
void calibrationWidget::connectInit()
{
    connect(oneWidget,SIGNAL(measurementFinshSignal(int)),this,SLOT(changeWindow(int)));
    connect(twoWidget,SIGNAL(measurementFinshSignal(int)),this,SLOT(changeWindow(int)));
    connect(caliOneWidget,SIGNAL(returnBtnSignal(int)),this,SLOT(changeWindow(int)));
    connect(qualityOneWidget,SIGNAL(returnBtnSignal(int)),this,SLOT(changeWindow(int)));
    connect(&serialPort::ReceiveThread,SIGNAL(calibration_cmdSign(QString)),this,SLOT(calibration_cmdSignSlot(QString)),(Qt::ConnectionType)(Qt::UniqueConnection|Qt::QueuedConnection));
    connect(&serialPort::ReceiveThread,SIGNAL(quality_cmdSign(QString)),this,SLOT(quality_cmdSignSlot(QString)),(Qt::ConnectionType)(Qt::UniqueConnection|Qt::QueuedConnection));
}

/**
 * @brief 设置space_num行试剂船信息内容
 * @param space_num 行
 * @param data 数据
 * @param length 数据长度
 */
void calibrationWidget::setModel_ReagentInfo(int space_num, QByteArray &data, int interf)
{
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
    if( interf == 1){
        oneWidget->SerialNumber->insert(postion,temp_serical_number.remove(0,1));//储存各试剂船序列号，第二位到第七位条码用于查询标准曲线
        //插入临时试剂船运行数据进储存QMap
        if(oneWidget->RunData->contains(postion-1)){  //当前位置是否已经有数据
            QMap<int,QString>::iterator it  = oneWidget->RunData->find(postion-1);
            it.value() = oneWidget->getRunInfo(sericalNum); //插入数据进入
        }
        else oneWidget->RunData->insert(postion-1,oneWidget->getRunInfo(sericalNum));  //查找运行数据并加入QMap进行临时数据保存;
        for( int i = 0;i < 4; i++ ){
            sericalNum.append(char(data.at(14+i))); //条码前11位
        }
        oneWidget->model->setData( oneWidget->model->index(postion-1,1),QVariant( sericalNum ) );//显示条码
        oneWidget->model->setData( oneWidget->model->index(postion-1,2),QVariant( project_name + "-" + Reagent_kind ) );//显示项目
        oneWidget->model->setData( oneWidget->model->index(postion-1,4),QVariant( QString::number(Produce_year,10) + tr("年") + QString::number(Produce_mouth,10) + tr("月") ));//显示开始使用时间
        oneWidget->model->setData( oneWidget->model->index(postion-1,5),QVariant( QString::number( ( Produce_year * 12 + Produce_mouth + Expiration_date) / 12,10 ) + tr("年") + QString::number( ( Produce_year * 12 + Produce_mouth + Expiration_date) % 12,10 ) + tr("月")) );//显示截止使用时间
        oneWidget->tableView->reset();

    }else if( interf == 2){
        twoWidget->SerialNumber->insert(postion,temp_serical_number.remove(0,1));//储存各试剂船序列号，第二位到第七位条码用于查询标准曲线
        //插入临时试剂船运行数据进储存QMap
        if(twoWidget->RunData->contains(postion-1)){  //当前位置是否已经有数据
            QMap<int,QString>::iterator it  = twoWidget->RunData->find(postion-1);
            it.value() = twoWidget->getRunInfo(sericalNum); //插入数据进入
        }
        else twoWidget->RunData->insert(postion-1,twoWidget->getRunInfo(sericalNum));  //查找运行数据并加入QMap进行临时数据保存;
        for( int i = 0;i < 4; i++ ){
            sericalNum.append(char(data.at(14+i))); //条码前11位
        }
        twoWidget->model->setData( oneWidget->model->index(postion-1,1),QVariant( sericalNum ) );//显示条码
        twoWidget->model->setData( oneWidget->model->index(postion-1,2),QVariant( project_name + "-" + Reagent_kind ) );//显示项目
        twoWidget->model->setData( oneWidget->model->index(postion-1,4),QVariant( QString::number(Produce_year,10) + tr("年") + QString::number(Produce_mouth,10) + tr("月") ));//显示开始使用时间
        twoWidget->model->setData( oneWidget->model->index(postion-1,5),QVariant( QString::number( ( Produce_year * 12 + Produce_mouth + Expiration_date) / 12,10 ) + tr("年") + QString::number( ( Produce_year * 12 + Produce_mouth + Expiration_date) % 12,10 ) + tr("月")) );//显示截止使用时间
        twoWidget->tableView->reset();
    }
}
/**
 * @brief 试剂船拔出处理函数
 * @param postion ：试剂船位置
 * @param num  : 1校准品，2质控品
 */
void calibrationWidget::reagentPopup_CMDHandle(int postion,int num)
{
    if( num == 1){
        if( oneWidget->statusWidget->Reagent_status[postion] == StatusWidget::RUN){
            emit serialPort::ReceiveThread.ErrDataSign("当前试剂船正在运行,被强制拔出");
        }
        oneWidget->statusWidget->setReagent_Status(postion,StatusWidget::FREE);
        /****试剂船拔出时，清除相应图标数据***********************************************************************/
        /****试剂船拔出时，清除相应图标数据***********************************************************************/
        for(int i = 1;i < 6; i++ ){
            oneWidget->model->setData(oneWidget->model->index(postion-1,i),QVariant(""));//清空图标数据
        }
        oneWidget->model->setData(oneWidget->model->index(postion-1,7),QVariant(""));//清空图标数据
        oneWidget->model->setData(oneWidget->model->index(postion-1,8),QVariant(0));  //清空进度条
        for(int i = 9;i < 11; i++ ){
           twoWidget-> model->setData(twoWidget->model->index(postion-1,i),QVariant(""));  //清空图标数据
        }
        oneWidget->tableView->reset();
        oneWidget->okBtn->Display_btns.value(postion-1)->text = tr("");
        oneWidget->okBtn->Display_btns.value(postion-1)->state &= ( ~QStyle::State_Enabled);

    }else if( num == 2){
        if( twoWidget->statusWidget->Reagent_status[postion] == StatusWidget::RUN){
            emit serialPort::ReceiveThread.ErrDataSign("当前试剂船正在运行,被强制拔出");
        }
        twoWidget->statusWidget->setReagent_Status(postion,StatusWidget::FREE);
        /****试剂船拔出时，清除相应图标数据***********************************************************************/
        for(int i = 1;i < 6; i++ ){
            twoWidget->model->setData(twoWidget->model->index(postion-1,i),QVariant(""));//清空图标数据
        }
        twoWidget->model->setData(twoWidget->model->index(postion-1,7),QVariant(""));//清空图标数据
        twoWidget->model->setData(twoWidget->model->index(postion-1,8),QVariant(0));  //清空进度条
        for(int i = 9;i < 11; i++ ){
           twoWidget-> model->setData(twoWidget->model->index(postion-1,i),QVariant(""));  //清空图标数据
        }
        twoWidget->tableView->reset();
        twoWidget->okBtn->Display_btns.value(postion-1)->text = tr("");
        twoWidget->okBtn->Display_btns.value(postion-1)->state &= ( ~QStyle::State_Enabled);
    } 
}
/**
 * @brief 试剂船进度处理函数
 * @param postion
 * @num 1:校准品 2：质控品
 */
void calibrationWidget::returnProgress_InfoHandle(QByteArray &data,int interf)
{
    unsigned char num = data.at(6)&0xff; //返回进度数量
    unsigned char postion ; //当前槽号
    QString startTime;
    QString endTime;
    QString currentStage; //当前阶段
    for(int i = 0;i < num; i++){
       postion = ( data.at(7 + 17*i )&0xff )  ;
       qDebug() << "当前试剂船船位置 = "<< postion;
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
       unsigned short int start_year = ((unsigned short int)(data.at(10 + i*17) & 0xff) << 8) | data.at(11 + i*17) & 0xff;
       unsigned char start_month = data.at(12 + i*17) & 0xff;
       unsigned char start_day = data.at(13 + i*17) & 0xff;
       unsigned char start_hour = data.at(14 + i*17) & 0xff;
       unsigned char start_minute = data.at(15 + i*17) & 0xff;
       unsigned char start_second = data.at(16 + i*17) & 0xff;

       unsigned char progressData = data.at(9 + i*17) & 0xff; //进度
       unsigned short int end_year = ((unsigned short int)(data.at(17 + i*17) & 0xff) << 8) | data.at(18 + i*17) & 0xff;
       unsigned char end_month = data.at(19 + i*17) & 0xff;
       unsigned char end_day = data.at(20 + i*17) & 0xff;
       unsigned char end_hour =data.at(21 + i*17) & 0xff;
       unsigned char end_minute = data.at(22 + i*17) & 0xff;
       unsigned char end_second = data.at(23 + i*17) & 0xff;

       startTime += (QString::number(start_year,10) + "/" + QString::number(start_month,10) + "/" + QString::number(start_day,10) +" "
                     +QString::number(start_hour,10) + ":"+QString::number(start_minute,10)+":"+QString::number(start_second,10)  );
       endTime += (QString::number(end_year,10) + "/" + QString::number(end_month,10) + "/" + QString::number(end_day,10) +" "
                   +QString::number(end_hour,10) + ":"+QString::number(end_minute,10)+":"+QString::number(end_second,10)  );
       if(interf == 1){
           oneWidget->model->setData(oneWidget->model->index(postion-1,7),QVariant(currentStage)); //当前阶段
           oneWidget->model->setData(oneWidget->model->index(postion-1,8),QVariant(progressData)); //当前测试进度
           oneWidget->tableView->reset();
       }else if( interf == 2 ){
           twoWidget->model->setData(oneWidget->model->index(postion-1,7),QVariant(currentStage)); //当前阶段
           twoWidget->model->setData(oneWidget->model->index(postion-1,8),QVariant(progressData)); //当前测试进度
           twoWidget->tableView->reset();
       }
   }
}
/**
 * @brief 试剂船错误处理函数
 * @param err
 */
void calibrationWidget::returnRegent_ErrHandle(QByteArray &err)
{

}
/**
 * @brief 测试结果处理函数
 * @param data
 */
void calibrationWidget::testResultHandle(int interf,QByteArray &data)
{
    QSqlQuery query;
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
    delete []TempPhoton_Value; //释放空间
    qDebug() <<"当前测试光子数" << photon_result;
    if( interf == 1){
        oneWidget->statusWidget->setReagent_Status(postion,StatusWidget::FINISH); //试剂船状态进行切换
        /*************根据进行浓度计算*****************************************************************/
        QString queryStr = "select GENERATION_TYPE,PARAMETER_ONE,PARAMETER_TWO,PARAMETER_THREE,"
                           "PARAMETER_FOUR,PARAMETER_FIVE,PARAMETER_SIX "
                           "from cruve_parameter "
                           "where REAGENT_CODE = '" + oneWidget->SerialNumber->value(postion) + "' and DEL_FLAG = 0";

        if( !query.exec(queryStr)){
            QMessageBox::critical(this,tr("错误代码E0027"),tr("错误代码E0027:当前试剂没有做标准曲线定标!"));
            oneWidget->model->setData(oneWidget->model->index(postion-1,9),QVariant(QString::number(photon_result,10))); //当前光子测试结果
            oneWidget->tableView->reset();
            return;
        }
        double concentration = Util::getX(twoWidget->SerialNumber->value(postion),(double)photon_result); //进行浓度换算
        oneWidget->model->setData(oneWidget->model->index(postion-1,9),QVariant(QString::number(photon_result,10))); //当前光子测试结果
        oneWidget->model->setData(oneWidget->model->index(postion-1,10),QVariant(QString::number(concentration,8,7))); //当前浓度测试结果
        oneWidget->tableView->reset();
    }
    if( interf == 2 ){
        twoWidget->statusWidget->setReagent_Status(postion,StatusWidget::FINISH); //试剂船状态进行切换
        /*************根据进行浓度计算*****************************************************************/
        QString queryStr = "select GENERATION_TYPE,PARAMETER_ONE,PARAMETER_TWO,PARAMETER_THREE,"
                           "PARAMETER_FOUR,PARAMETER_FIVE,PARAMETER_SIX "
                           "from cruve_parameter "
                           "where REAGENT_CODE = '" + twoWidget->SerialNumber->value(postion) + "' and DEL_FLAG = 0";
        if( !query.exec(queryStr)){
            QMessageBox::critical(this,tr("错误代码E0027"),tr("错误代码E0027:当前试剂没有做标准曲线定标!"));
            twoWidget->model->setData(twoWidget->model->index(postion-1,9),QVariant(QString::number(photon_result,10))); //当前光子测试结果
            oneWidget->tableView->reset();
            return;
        }
        double concentration = Util::getX(twoWidget->SerialNumber->value(postion),(double)photon_result); //进行浓度换算
        twoWidget->model->setData(twoWidget->model->index(postion-1,9),QVariant(QString::number(photon_result,10))); //当前光子测试结果
        twoWidget->model->setData(twoWidget->model->index(postion-1,10),QVariant(QString::number(concentration,8,7))); //当前浓度测试结果
        twoWidget->tableView->reset();
    }
}


/**
 * @brief 切换界面
 * @param num
 */
void calibrationWidget::changeWindow(int num)
{
    if( num == 2 ){  //校准品第二个界面
        for(int i = 0; i < 12; i++){ //进行界面数据拷贝
            caliOneWidget->model->setData( caliOneWidget->model->index(i,1),oneWidget->model->data(oneWidget->model->index(i,1)) );
            caliOneWidget->model->setData( caliOneWidget->model->index(i,2),oneWidget->model->data(oneWidget->model->index(i,2)) );
            caliOneWidget->model->setData( caliOneWidget->model->index(i,3),oneWidget->model->data(oneWidget->model->index(i,3)) );
            caliOneWidget->model->setData( caliOneWidget->model->index(i,4),oneWidget->model->data(oneWidget->model->index(i,4)) );
            caliOneWidget->model->setData( caliOneWidget->model->index(i,5),oneWidget->model->data(oneWidget->model->index(i,5)) );
            caliOneWidget->model->setData( caliOneWidget->model->index(i,6),oneWidget->model->data(oneWidget->model->index(i,6)) );
            caliOneWidget->model->setData( caliOneWidget->model->index(i,8),oneWidget->model->data(oneWidget->model->index(i,7)) );
            caliOneWidget->model->setData( caliOneWidget->model->index(i,9),oneWidget->model->data(oneWidget->model->index(i,8)) );
        }
    }else if( num == 3){//质控品第二个界面
        for(int i = 0; i < 12; i++){ //进行界面数据拷贝
            qualityOneWidget->model->setData( qualityOneWidget->model->index(i,1),twoWidget->model->data(twoWidget->model->index(i,1)));
            qualityOneWidget->model->setData( qualityOneWidget->model->index(i,2),twoWidget->model->data(twoWidget->model->index(i,2)));
            qualityOneWidget->model->setData( qualityOneWidget->model->index(i,3),twoWidget->model->data(twoWidget->model->index(i,3)));
            qualityOneWidget->model->setData( qualityOneWidget->model->index(i,4),twoWidget->model->data(twoWidget->model->index(i,4)));
            qualityOneWidget->model->setData( qualityOneWidget->model->index(i,5),twoWidget->model->data(twoWidget->model->index(i,5)));
            qualityOneWidget->model->setData( qualityOneWidget->model->index(i,6),twoWidget->model->data(twoWidget->model->index(i,6)));
            qualityOneWidget->model->setData( qualityOneWidget->model->index(i,8),twoWidget->model->data(twoWidget->model->index(i,7)));
            qualityOneWidget->model->setData( qualityOneWidget->model->index(i,9),twoWidget->model->data(twoWidget->model->index(i,8)));
        }
    }
    stack->setCurrentIndex(num);
}

/**
 * @brief 校准品处理接收到的命令信号槽
 * @param str
 */
void calibrationWidget::calibration_cmdSignSlot(QString str)
{
    QByteArray Receive_array = 0;
    QString returnCMD = "";
    int postion = 0;
    qDebug()<<"信号槽线程ID = " <<QThread::currentThreadId();
    qDebug() << "质控校准收到一条命令" << str;
    Receive_array = serialPort::HEXStringToArr(str);
    uint16_t dataLength = (uint16_t)(((Receive_array.at(4)&0xffff)<< 8)|(Receive_array.at(5)&0xff));//数据长度
    unsigned char cmd = (Receive_array.at(1) & 0xff); //命令
    if( ( Receive_array.at(0) & 0xff) & 0x40 ){   //MCU返回码命令解析
        switch(cmd){
        case CALIBRATION_WHETHER_FREE_RETURN_CMD:
            qDebug()<< "质控/校准收到MCU空闲命令返回";
            if( dataLength != 1){
                qDebug() << "质控/校准品空闲命令缺少数据";
                return;
            }
            if( !( Receive_array.at(6) & 0xff ) ){ //判断是否空闲
                qDebug() << "是空闲命令";
                if( !oneWidget->Calibration_WorkQueue->isEmpty()){ /**<发送任务队列队首 */
                    QString str;
                    oneWidget->Calibration_WorkQueue->dequeue(str);
                    qDebug() << "队列字符串"<< str;
                    emit serialPort::ReceiveThread.sendDataSign(str);
                }
            }else qDebug() << "是忙命令";
            break;
        case CALIBRATION_WHEHTER_SCHED_RETURN_CMD:
            if( dataLength != 1){
                qDebug() << "质控/校准品调度命令缺少数据";
                return;
            }
            qDebug()<< "质控/校准品收到MCU可不可以调度命令返回";
            if( !(Receive_array.at(6) & 0xff) ){ //判断是否空闲
                qDebug() << "是不可调度命令";
            }else{ qDebug() << "是可调度命令";
                emit serialPort::ReceiveThread.sendDataSign("04,01,ff,ff,00,01,01");//红灯闪
            }
            break;
        }
        return;
    }
    /***MCU主动发送的命令解析************************************************/
    switch(cmd){
    case CALIBRATION_PULL_SHIP_CMD :
        qDebug()<< "校准品收到MCU有试剂船拔出命令";
        if( dataLength != 1){
            //插入错误数据表
            qDebug() << "校准拔出命令数据长度不对";
             emit serialPort::ReceiveThread.ErrDataSign("数据长度不对");
            return;
        }
        postion = Receive_array.at(6)&0xff;//位置
        reagentPopup_CMDHandle( postion,1);
        returnCMD = "04,02,ff,ff,00,02,"+QString::number(postion,10)+",02"; //绿灯灭
        emit serialPort::ReceiveThread.sendDataSign(returnCMD);
        break;
    case CALIBRATION_ALL_TEST_PROGRESS:
        qDebug()<< "质控/校准品收到所有试剂船进度MCU命令";
        if( !( dataLength == 205 || dataLength == 18 )){
            //插入错误数据表
            qDebug() << "质控品收到所有试剂船进度MCU命令数据长度不对";
            emit serialPort::ReceiveThread.ErrDataSign("数据长度不对");
            return;
        }
        returnProgress_InfoHandle( Receive_array ,1);
        break;
    case CALIBRATION_ERR_CMD:
        qDebug()<< "质控/校准品收到错误信息MCU命令";
        break;
    case CALIBRATION_NEW_SHIP_INFOR_CMD:
        qDebug()<< "质控/校准品收到一条插入新试剂船信息";
        if( dataLength != 17){
            qDebug() << "质控/校准品插入新试剂船信息缺少数据";
            return;
        }
        postion = Receive_array.at(6)&0xff;
        if( postion <= 12 && postion > 0 ){   //试剂船船舱号最大也就12个船舱
            oneWidget->statusWidget->setReagent_Status(postion,StatusWidget::AWAIT);//设置试剂船现在状态
            setModel_ReagentInfo(postion,Receive_array,1); //设置当前试剂船条码
            returnCMD = "04,01,ff,ff,00,02,"+QString::number(postion,10)+",00";
            emit serialPort::ReceiveThread.sendDataSign(returnCMD);
        }
        break;
    case CALIBRATION_ONE_TEST_DATA_CMD:
        qDebug()<< "质控/校准品某一条试剂测试结果信息";
        if( dataLength != 5){
            qDebug() << "质控/校准品某一条试剂测试结果缺少数据";
            return;
        }
        postion = Receive_array.at(6)&0xff;
        returnCMD = "04,01,ff,ff,00,02,"+QString::number(postion,10)+",02";
        emit serialPort::ReceiveThread.sendDataSign(returnCMD);
        for(int i = 0;i< 1000;i++){}
        returnCMD = "04,02,ff,ff,00,02,"+QString::number(postion,10)+",01";
        emit serialPort::ReceiveThread.sendDataSign(returnCMD);
        /**
        ** 处理测试结果
       **/
        testResultHandle(1, Receive_array );
        break;
    }
}

/**
 * @brief 质控品处理接收到的命令信号槽
 * @param str
 */
void calibrationWidget::quality_cmdSignSlot(QString str)
{
    QByteArray Receive_array = 0;
    QString returnCMD = "";
    int postion = 0;
    qDebug()<<"信号槽线程ID = " <<QThread::currentThreadId();
    qDebug() << "质控校准收到一条命令" << str;
    Receive_array = serialPort::HEXStringToArr(str);
    uint16_t dataLength = (uint16_t)(((Receive_array.at(4)&0xffff)<< 8)|(Receive_array.at(5)&0xff));//数据长度
    unsigned char cmd = (Receive_array.at(1) & 0xff); //命令
    if( ( Receive_array.at(0) & 0xff) & 0x40 ){   //MCU返回码命令解析
        switch(cmd){
        case QUALITY_WHETHER_FREE_RETURN_CMD:
            qDebug()<< "质控品收到MCU空闲命令返回";
            if( dataLength != 1){
                qDebug() << "质控/校准品空闲命令缺少数据";
                return;
            }
            if( !( Receive_array.at(6) & 0xff ) ){ //判断是否空闲
                qDebug() << "是空闲命令";
                if( !twoWidget->queue_WorkQueue->isEmpty()){ /**<发送任务队列队首 */
                    QString str;
                    twoWidget->queue_WorkQueue->dequeue(str);
                    qDebug() << "队列字符串"<< str;
                    emit serialPort::ReceiveThread.sendDataSign(str);
                }
            }else qDebug() << "是忙命令";
            break;
        case QUALITY_WHEHTER_SCHED_RETURN_CMD:
            if( dataLength != 1){
                qDebug() << "质控品调度命令缺少数据";
                return;
            }
            qDebug()<< "质控品收到MCU可不可以调度命令返回";
            if( !(Receive_array.at(6) & 0xff) ){ //判断是否空闲
                qDebug() << "是不可调度命令";
            }else{ qDebug() << "是可调度命令";
                emit serialPort::ReceiveThread.sendDataSign("05,01,ff,ff,00,01,01");//红灯闪
            }
            break;
        }
        return;
    }
    /***MCU主动发送的命令解析************************************************/
    switch(cmd){
    case QUALITY_PULL_SHIP_CMD :
        qDebug()<< "质控品收到MCU有试剂船拔出命令";
        if( dataLength != 1){
            //插入错误数据表
            qDebug() << "校准拔出命令数据长度不对";
             emit serialPort::ReceiveThread.ErrDataSign("数据长度不对");
            return;
        }
        postion = Receive_array.at(6)&0xff;//位置
        reagentPopup_CMDHandle( postion,2);
        returnCMD = "05,02,ff,ff,00,02,"+QString::number(postion,10)+",02"; //绿灯灭
        emit serialPort::ReceiveThread.sendDataSign(returnCMD);
        break;
    case QUALITY_ALL_TEST_PROGRESS:
        qDebug()<< "质控/校准品收到所有试剂船进度MCU命令";
        if( !( dataLength == 205 || dataLength == 18 )){
            //插入错误数据表
            qDebug() << "质控品收到所有试剂船进度MCU命令数据长度不对";
            emit serialPort::ReceiveThread.ErrDataSign("数据长度不对");
            return;
        }
        returnProgress_InfoHandle( Receive_array ,2);
        break;
    case QUALITY_ERR_CMD:
        qDebug()<< "质控品收到错误信息MCU命令";
        break;
    case QUALITY_NEW_SHIP_INFOR_CMD:
        qDebug()<< "质控/校准品收到一条插入新试剂船信息";
        if( dataLength != 17){
            qDebug() << "质控/校准品插入新试剂船信息缺少数据";
            return;
        }
        postion = Receive_array.at(6)&0xff;
        if( postion <= 12 && postion > 0 ){   //试剂船船舱号最大也就12个船舱
            twoWidget->statusWidget->setReagent_Status(postion,StatusWidget::AWAIT);//设置试剂船现在状态
            setModel_ReagentInfo(postion,Receive_array,2); //设置当前试剂船条码
            returnCMD = "05,01,ff,ff,00,02,"+QString::number(postion,10)+",00";
            emit serialPort::ReceiveThread.sendDataSign(returnCMD);
        }
        break;
    case QUALITY_ONE_TEST_DATA_CMD:
        qDebug()<< "质控品某一条试剂测试结果信息";
        if( dataLength != 5){
            qDebug() << "质控品某一条试剂测试结果缺少数据";
            return;
        }
        postion = Receive_array.at(6)&0xff;
        returnCMD = "05,01,ff,ff,00,02,"+QString::number(postion,10)+",02";
        emit serialPort::ReceiveThread.sendDataSign(returnCMD);
        for(int i = 0;i< 1000;i++){}
        returnCMD = "05,02,ff,ff,00,02,"+QString::number(postion,10)+",01";
        emit serialPort::ReceiveThread.sendDataSign(returnCMD);
   /**
    ** 处理测试结果
    **/
        testResultHandle(2, Receive_array );
       break;
    }
}




