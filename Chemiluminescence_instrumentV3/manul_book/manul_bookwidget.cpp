#include "manul_bookwidget.h"

manul_bookWidget::manul_bookWidget(QWidget *parent) : QDialog(parent)
{
    setWindowFlags(Qt::Dialog);
    setWindowTitle(tr("帮助文档"));
    titleInit();
    DisplayTest();
}

/**
 * @brief 标题头显示
 */
void manul_bookWidget::titleInit()
{
    //窗口标签
    WindowTile = new QLabel(this);
    WindowTile->setPixmap(QPixmap(":/picture/standardPrograme/tile_icon.png"));
    WindowTile->setGeometry(0,0,1687,69);
    //显示状态
    statusTitleLab  = new  QLabel(this);
    statusTitleLab->setText(tr("帮助文档"));
    QPalette   pal;//按键字体颜色设置
    pal.setColor(QPalette::WindowText, QColor(255, 255, 255, 255));
    statusTitleLab->setPalette(pal);
    statusTitleLab->setFont(QFont("windowTitle",15));
    statusTitleLab->setGeometry(80,13,100,40);
}

/**
 * @brief 显示说明书内容
 */
void manul_bookWidget::DisplayTest()
{
    file = new QFile(":/manulText/manul.txt"); //要读取的文件夹
    textEdit = new QTextEdit(this);  //显示文件
    textEdit->setReadOnly(true);
    textEdit->setGeometry(10,70,1660,950);
    if(file->open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream textStream(file);
        while(!textStream.atEnd()){
            QString string = textStream.readLine();
            textEdit->append(string);
        }
    }
}
