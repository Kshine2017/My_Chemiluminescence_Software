#include "mycheckmessagebox.h"
#define LAYOUT_SPACING 20
#define DEFAULT_HEIGHT  (300)
#define DEFAULT_WIDTH   (550)
#define MIN_WEIGHT      (100)
#define MIN_WIDTH       (150)
#define FONT_SIZE       (26)
myCheckmessageBox::myCheckmessageBox(myCheckmessageBox::MY_MESSAGE_TYPE type, const QString &strTitle, const QString &strInfo, QWidget *parent, Qt::WindowFlags flags)
                :QDialog(parent, flags), m_eMYType(type)
{
    initialize(strInfo);
    setTextInfo(type, strTitle, strInfo);
    resize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    setMinimumSize(MIN_WIDTH, MIN_WEIGHT);

    alignment();
}

void myCheckmessageBox::setTextInfo(const QString &strInfo)
{
    if(!strInfo.isEmpty())
        m_pLabelInfo->setText(strInfo);
}

void myCheckmessageBox::setTextInfo(const QString &strTitle, const QString &strInfo)
{
    if(!strTitle.isEmpty())
        this->setWindowTitle(strTitle);

    if(!strInfo.isEmpty())
        m_pLabelInfo->setText(strInfo);
}

void myCheckmessageBox::setTextInfo(myCheckmessageBox::MY_MESSAGE_TYPE type, const QString &strTitle, const QString &strInfo)
{
    if(!strTitle.isEmpty())
        this->setWindowTitle(strTitle);

    if(!strInfo.isEmpty())
        m_pLabelInfo->setText(strInfo);
    else
        return ;

     m_eMYType = type;
     QString fileName;
     switch(m_eMYType){
     case MY_CALIBRATION:
         fileName = ":/picture/MessgeBox/checkIcon.png";
         break;
     default:
         break;
     }
     QPixmap iconPix(fileName);
     m_pLabelIcon->setPixmap(iconPix);
}

void myCheckmessageBox::initialize(const QString &strInfo)
{
    m_pLabelIcon = new QLabel(this);
    QString fileName;
    switch(m_eMYType){
    case MY_CALIBRATION:
        fileName = ":/picture/MessgeBox/checkIcon.png";
        break;
    default:
        break;
    }
    QPixmap iconPix(fileName);
    m_pLabelIcon->setPixmap(iconPix);
    m_pLabelIcon->setFixedSize(72,72);
    /**
     * @brief font 设置显示字体的大小
     */
    QFont font;
    font.setPixelSize(FONT_SIZE);

    m_pLabelInfo = new QLabel(strInfo, this);
    m_pLabelInfo->setWordWrap(true);
    m_pLabelInfo->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_pLabelInfo->setFont(font); //设置字体


    m_oneBtn = new QPushButton(this);
    m_oneBtn->setStyleSheet("QPushButton{border-image: url(:/picture/calibrationWidget/calibraionBtnIcon-up.png);}"
                               "QPushButton:hover{border-image: url(:/picture/calibrationWidget/calibraionBtnIcon-up.png);}"
                               "QPushButton:pressed{border-image: url(:/picture/calibrationWidget/calibraionBtnIcon-down.png);}");
    m_oneBtn->setFixedSize(120,50);
    m_oneBtn->setFlat(true);
    connect(m_oneBtn, SIGNAL(released()), this, SLOT(accept()));

    m_twoBtn = new QPushButton(this);

    m_twoBtn->setFocusPolicy(Qt::NoFocus);
    m_twoBtn->setFlat(true);
    m_twoBtn->setFont(font);
    m_twoBtn->setStyleSheet("QPushButton{border-image: url(:/picture/calibrationWidget/qualityControlBtnIcon-up.png);}"
                               "QPushButton:hover{border-image: url(:/picture/calibrationWidget/qualityControlBtnIcon-up.png);}"
                               "QPushButton:pressed{border-image: url(:/picture/calibrationWidget/qualityControlBtnIcon-down.png);}");
    m_twoBtn->setFixedSize(120,50);
    connect(m_twoBtn, SIGNAL(released()), this, SLOT(reject()));
}

void myCheckmessageBox::alignment()
{
    QHBoxLayout *hbLabelLayout = new QHBoxLayout;
    hbLabelLayout->addWidget(m_pLabelIcon);
    hbLabelLayout->addWidget(m_pLabelInfo);

    QHBoxLayout *hbBtnLayout = new QHBoxLayout;
    hbBtnLayout->addStretch();
    hbBtnLayout->addWidget(m_oneBtn);
    hbBtnLayout->addStretch();
    hbBtnLayout->addWidget(m_twoBtn);
    hbBtnLayout->addStretch();

    QVBoxLayout *vbLayout = new QVBoxLayout;
    vbLayout->addLayout(hbLabelLayout);

    vbLayout->addLayout(hbBtnLayout);
    vbLayout->addSpacing(20);
    setLayout(vbLayout);
}
