#include "myroundprogressbar.h"

//myRoundProgressBar::myRoundProgressBar(QWidget *parent):QWidget(parent, Qt::FramelessWindowHint)
//{
//    QTextCodec *codec = QTextCodec::codecForName("utf8");
//    QTextCodec::setCodecForLocale(codec);
////    QTextCodec::setCodecForCStrings(codec);
////    QTextCodec::setCodecForTr(codec);
//    resize(167, 167);
//    setAutoFillBackground(true);
//    QPalette pal = palette();
//    pal.setColor(QPalette::Background, QColor(0xFF,0xFF,0xFF,0xFF));
//    setPalette(pal);

//    startValueLabel = new QLabel(tr("0%"), this);
//    startValueLabel->setFont(QFont("Arial", 11, QFont::Normal));
//    startValueLabel->setStyleSheet("color:#898989");

//    endValueLabel = new QLabel(tr("100%"),this);
//    endValueLabel->setFont(QFont("Arial", 11, QFont::Normal));
//    endValueLabel->setStyleSheet("color:#898989");

//    dispayValueLabel = new QLabel(this);
//    dispayValueLabel->setStyleSheet("color:#349BDA");

//    updateTimer = new QTimer(this);
//    updateTimer->setInterval(20);
//    connect(updateTimer, SIGNAL(timeout()), this, SLOT(slotUpdateTimer()));
//}

//myRoundProgressBar::~myRoundProgressBar()
//{
////        if (updateTimer->isActive()) {
////            updateTimer->stop();
////        }
////        currentValue = 0;
//}



//void myRoundProgressBar::setUsedValue(int value)
//{
//    userdVaule = value;
//}

//void myRoundProgressBar::showEvent(QShowEvent *event)
//{
//    updateTimer->start();
//    currentValue = 0;
//}

//void myRoundProgressBar::hideEvent(QHideEvent *event)
//{
//    if (updateTimer->isActive()) {
//        updateTimer->stop();
//    }
//    currentValue = 0;
//}

//void myRoundProgressBar::slotUpdateTimer()
//{
//    if (currentValue >= userdVaule) {
//        updateTimer->stop();
//        return;
//    }
//    currentValue++;
//    update();
//}

//void myRoundProgressBar::paintEvent(QPaintEvent *event)
//{

//    QPainter painter(this);
//    QColor usedColor(165, 220, 62);
//    QColor freeColor(215, 215, 215);
//    painter.drawPixmap(QRect((width() - backGround.width())/2 , (height() - backGround.height())/2, backGround.width(), backGround.height()) , backGround);

//    painter.translate(width() / 2, height() / 2);
//    painter.setRenderHint(QPainter::Antialiasing);
//    painter.setRenderHint(QPainter::SmoothPixmapTransform);
//    painter.save();
//    painter.rotate(42);
//    painter.setPen(QPen(usedColor, 2));
//    for (int i = 0; i < currentValue ; ++i) {
//        painter.drawLine(0, 70, 0, 80);
//        painter.rotate(2.8);
//    }
//    painter.setPen(QPen(freeColor, 3));
//    for (int i = currentValue; i < 100 ; ++i) {
//        painter.drawLine(0, 70, 0, 80);
//        painter.rotate(2.8);
//    }
//    if (currentValue == 0) {
//        dispayValueLabel->setFont(QFont("Arial", 12, QFont::Bold));
//        dispayValueLabel->setText(tr("unconfig"));
//    }
//    else {
//        dispayValueLabel->setFont(QFont("Arial", 15, QFont::Bold));
//        dispayValueLabel->setText(tr("%1%").arg(currentValue));
//    }
//    QFontMetrics metrics(dispayValueLabel->font());
//    int textwidth = metrics.width(dispayValueLabel->text());
//    int textheight = metrics.height();
//    dispayValueLabel->setGeometry((width() - textwidth)/2, (height() - textheight)/2 , textwidth, textheight);
//    painter.restore();

//    painter.translate(-width()/2, -height()/2);
//    painter.setBrush(QColor(233, 233, 233));
//    painter.setPen(QPen(QColor(233, 233, 233), 15));
//    painter.drawEllipse(QRectF((width()/2 - 55), (height()/2 - 55), 110, 110));

//    QConicalGradient conicalGradient(width()/2, height()/2, 90);
//    conicalGradient.setColorAt(0, QColor(45, 204, 112));
//    conicalGradient.setColorAt(1.0, QColor(51, 152, 219));
//    painter.setPen(QPen(QBrush(conicalGradient), 30));
//    painter.drawEllipse(QRectF((width()/2 - 35), (height()/2 - 35), 70, 70));

//    painter.setPen(Qt::NoPen);
//    painter.setBrush(QColor(249, 249, 249));
//    painter.drawEllipse(QRectF((width()/2 - 30), (height()/2 - 30), 60, 60));
//}

//void myRoundProgressBar::resizeEvent(QResizeEvent *event)
//{
//    move((QApplication::desktop()->width() - width())/2,  (QApplication::desktop()->height() - height())/2);
//    startValueLabel->setGeometry(35, 140, 25, 20);
//    endValueLabel->setGeometry(97, 140, 50, 20);
//}

///****************move everywhere*******************/
//void myRoundProgressBar::mousePressEvent(QMouseEvent *event)
//{
//    bPressFlag = true;
//    beginDrag = event->pos();
//    QWidget::mousePressEvent(event);
//}

//void myRoundProgressBar::mouseMoveEvent(QMouseEvent *event)
//{
//    if (bPressFlag) {
//        QPoint relaPos(QCursor::pos() - beginDrag);
//        move(relaPos);
//    }
//    QWidget::mouseMoveEvent(event);
//}

//void myRoundProgressBar::mouseReleaseEvent(QMouseEvent *event)
//{
//    bPressFlag = false;
//    QWidget::mouseReleaseEvent(event);
//}
