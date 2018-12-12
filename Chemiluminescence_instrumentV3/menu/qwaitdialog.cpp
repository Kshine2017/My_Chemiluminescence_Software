#include "qwaitdialog.h"
#include <QTimer>
#include <QDebug>
QWaitDialog::QWaitDialog(QWidget *parent,const QString &title) :
    QDialog(parent)
{
    this->setFixedSize(1920, 1080);
    this->move(-1920,-1080);
    //setWindowModality(Qt::ApplicationModal);
   // setAttribute(Qt::WA_DeleteOnClose);
      //设置透明度
     this->setWindowOpacity(0.6);
      //取消对话框标题
      this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
      this->setStyleSheet("background-color:transparent;");

      //设置背景色为淡蓝色,顶层窗口做不出圆角来
      background = new QFrame(this);
      background->setStyleSheet("background-color: rgb(215, 215,215);border-radius:10px;");
      background->setGeometry(0, 0, 1920, 1080);

     tip_label = new QLabel(background);
     tip_label->setText(title);
     tip_label->setFont(QFont("宋体",20,75));
     tip_label->setStyleSheet("color: black;background-color: transparent;");
     tip_label->setGeometry(1400, 1000, 520, 80);

    show();

}

QWaitDialog::~QWaitDialog(){


    qDebug()<<"释放qWaitDialog";
}


