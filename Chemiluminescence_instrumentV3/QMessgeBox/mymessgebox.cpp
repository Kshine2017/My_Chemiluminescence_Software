#include "mymessgebox.h"

#define LAYOUT_SPACING 20
#define DEFAULT_HEIGHT  (300)
#define DEFAULT_WIDTH   (550)
#define MIN_WEIGHT      (100)
#define MIN_WIDTH       (150)
#define FONT_SIZE       (26)


myMessgeBox::myMessgeBox(MY_MESSAGE_TYPE type, const QString &strTitle, const QString &strInfo,QWidget *parent, Qt::WindowFlags flags)
    :QDialog(parent, flags), m_eMYType(type)
{
    initialize(strInfo);
    setAttribute(Qt::WA_DeleteOnClose);
    setTextInfo(type, strTitle, strInfo);
    resize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    setMinimumSize(MIN_WIDTH, MIN_WEIGHT);
    alignment();
}

//设置标签的内容
void myMessgeBox::setTextInfo(const QString &strInfo)
{
    if(!strInfo.isEmpty())
        m_pLabelInfo->setText(strInfo);
}

void myMessgeBox::setTextInfo(const QString &strTitle, const QString &strInfo)
{
    if(!strTitle.isEmpty())
        this->setWindowTitle(strTitle);

    if(!strInfo.isEmpty())
        m_pLabelInfo->setText(strInfo);
}

void myMessgeBox::setTextInfo(MY_MESSAGE_TYPE type, const QString &strTitle, const QString &strInfo)
{
    if(!strTitle.isEmpty())
   {

        this->setWindowTitle(strTitle);

    }
    if(!strInfo.isEmpty())
        m_pLabelInfo->setText(strInfo);
    else
        return ;

     m_eMYType = type;
     QString fileName;
     switch(m_eMYType){
     case MY_MESSAGE_QUESTION:
         fileName = ":/picture/MessgeBox/question.png";
         break;
     case MY_MESSAGE_INFORMATION:
         fileName = ":/picture/MessgeBox/information.png";
         break;
     case MY_MESSAGE_WARNING:
         fileName = ":/picture/MessgeBox/warning.png";
         break;
     case MY_MESSAGE_CRITICAL:
         fileName = ":/picture/MessgeBox/error.png";
         break;
     default:
         break;
     }
     QPixmap iconPix(fileName);
     m_pLabelIcon->setPixmap(iconPix);
}


void myMessgeBox::initialize(const QString &strInfo)
{
    m_pLabelIcon = new QLabel(this);
    QString fileName;
    switch(m_eMYType){
    case MY_MESSAGE_QUESTION:
        fileName = ":/picture/MessgeBox/question.png";
        break;
    case MY_MESSAGE_INFORMATION:
        fileName = ":/picture/MessgeBox/information.png";
        break;
    case MY_MESSAGE_WARNING:
        fileName = ":/picture/MessgeBox/warning.png";
        break;
    case MY_MESSAGE_CRITICAL:
        fileName = ":/picture/MessgeBox/error.png";
        break;
    default:
        break;
    }

    QPixmap iconPix(fileName);
    m_pLabelIcon->setPixmap(iconPix);
    m_pLabelIcon->setFixedSize(50,50);
    /**
     * @brief font 设置显示字体的大小
     */
    QFont font;
    font.setPixelSize(FONT_SIZE);

    m_pLabelInfo = new QLabel(strInfo, this);
    m_pLabelInfo->setWordWrap(true);
    m_pLabelInfo->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_pLabelInfo->setFont(font); //设置字体

    m_pBtnYes = new QPushButton(this);

    m_pBtnYes->setFocusPolicy(Qt::TabFocus);
    m_pBtnYes->setFixedSize(110,44);
    m_pBtnYes->setStyleSheet("QPushButton{border-image: url(:/picture/MessgeBox/sure-up.png);}"
                             "QPushButton:hover{border-image: url(:/picture/MessgeBox/sure-up.png);}"
                             "QPushButton:pressed{border-image: url(:/picture/MessgeBox/sure-down.png);}");
    connect(m_pBtnYes, SIGNAL(released()), this, SLOT(accept()));

    if(m_eMYType == MY_MESSAGE_QUESTION)
    {
        m_pBtnNo = new QPushButton(this);
        m_pBtnNo->setFocusPolicy(Qt::TabFocus);
        m_pBtnNo->setFixedSize(110,44);
        m_pBtnNo->setStyleSheet("QPushButton{border-image: url(:/picture/MessgeBox/cancel-up.png);}"
                                       "QPushButton:hover{border-image: url(:/picture/MessgeBox/cancel-up.png);}"
                                       "QPushButton:pressed{border-image: url(:/picture/MessgeBox/cancel-down.png);}");

        connect(m_pBtnNo, SIGNAL(released()), this, SLOT(reject()));
    }

}
/**
 * @brief 界面布局
 */
void myMessgeBox::alignment()
{
    QHBoxLayout *hbLabelLayout = new QHBoxLayout;
    hbLabelLayout->addWidget(m_pLabelIcon);
    hbLabelLayout->addWidget(m_pLabelInfo);

    QHBoxLayout *hbBtnLayout = new QHBoxLayout;
    hbBtnLayout->addStretch();
    hbBtnLayout->addWidget(m_pBtnYes);
    if(m_eMYType == MY_MESSAGE_QUESTION){
        hbBtnLayout->addStretch();
        hbBtnLayout->addWidget(m_pBtnNo);
    }
    hbBtnLayout->addStretch();

    QVBoxLayout *vbLayout = new QVBoxLayout;
    vbLayout->addLayout(hbLabelLayout);
    vbLayout->addSpacing(20);
    vbLayout->addLayout(hbBtnLayout);
    setLayout(vbLayout);
}
