#include <QApplication>
#include <QPixmap>
#include <QSplashScreen>
#include <windows.h>
#include "data/connection.h"
#include "login/login.h"
#include "mainwindow.h"
#include "Serial_port/serialport.h"
#include "data/util.h"
#include <QSettings>
#include <QDebug>


int main(int argc, char *argv[])
{
    //保存-----------------------------------------
//    QString iniFilePath = "config.ini";
//    QSettings settings(iniFilePath,QSettings::IniFormat);

//    settings.setValue("PICTURE/window_background_pic",":/picture/login/WindowBackground.jpg");

    //读取----------------------------------------
//        QString iniFilePath = "config.ini";
//        QSettings settings(iniFilePath,QSettings::IniFormat);

//        QString wbgp = settings.value("PICTURE/window_background_pic").toString();
//        qDebug()<<wbgp;
    //-------------------------------------------
    QApplication a(argc, argv);
    QFont font("黑体",12);
    a.setFont(font);
   // qInstallMessageHandler(ouPutMessage);  //安装消息处理机制
    if(!createConnection())
    {
        return 0;
    }
    QPixmap pixmap(":/picture/login/WindowBackground.jpg");
    QSplashScreen splash(pixmap);
    splash.show();
    a.processEvents(QEventLoop::ExcludeUserInputEvents);   //不要相应任何鼠标输入和键盘输入
    Sleep(10);
    /**
     * @brief 通讯串口
     */
    serialPort serial;
    serial.getSerialPortID();
    serial.setSerialPort(); //设置串口
 /*********主窗口***************************/
   MainWindow mainwindow;

/**获取当前系统时间，并发送握手********************************************************************************/
    QString current_date_time = QDateTime::currentDateTime().toString("yyyy MM dd hh mm ss");
    qDebug()<<current_date_time;
    QStringList list_time = current_date_time.split(" ");
    QString current_date_time_new = "";
    foreach(QString str,list_time)
    {
        if(!str.isEmpty())
        {
            int temp_str = str.toInt();
            QString temp = QString::number(temp_str,16);
            current_date_time_new += temp+ ",";
        }
    }
    current_date_time_new.insert(1,",");
    current_date_time_new = current_date_time_new.left(current_date_time_new.length()-1);
    qDebug()<<current_date_time_new;
    serial.mySend_Data("06,30,FF,FF,00,07,"+ current_date_time_new); //发送握手加时间
/************************************************************************************************************/

    Util::getX("1111",1117376.0);

//登录窗口
    Login w;
    if(w.exec() == QDialog::Accepted){
        mainwindow.show();                  //主界面展示
        splash.finish(&w);
        qDebug() << "登录成功";
        return a.exec();
    }else{
       qDebug() << "登录界面点击取消按钮";
       splash.finish(&w);
       mainwindow.close();
    }
}
