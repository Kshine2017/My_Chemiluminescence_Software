#ifndef MYHEADERVIEW_H
#define MYHEADERVIEW_H

#include <QtGui>
#include <QHeaderView>
#include <QStyleOptionButton>
#include <QStyle>


class MyHeaderView : public QHeaderView
{
    Q_OBJECT
public:
    MyHeaderView( int checkColumnIndex,
             Qt::Orientation orientation,
             QWidget * parent = 0) :
    QHeaderView(orientation, parent)
    {
        m_checkColIdx = checkColumnIndex;
        isChecked = false;
    }
signals:
    void checkStausChange(bool);

protected:
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
    {
        painter->save();

        QHeaderView::paintSection(painter, rect, logicalIndex);

        painter->restore();


        if (logicalIndex == m_checkColIdx)
        {
            QStyleOptionButton option;




            int width = 10;
            for (int i=0; i<logicalIndex; ++i)
            width += sectionSize( i );
            option.state = QStyle::State_Enabled;
            option.rect = QRect(15, 15, 30, 30);
            if (isChecked)
            {
                option.iconSize = QSize(30,30);
                option.icon = QIcon(":/picture/selfTest/Checked_png.png");
               // option.state = QStyle::State_On;
            }
            else
            {
                option.iconSize = QSize(30,30);
                option.icon = QIcon(":/picture/selfTest/UnChecked_png.png");
               // option.state = QStyle::State_Off;
            }
                //        this->style()->drawPrimitive(QStyle::PE_IndicatorCheckBox, &option, painter);
//            QPalette palette;
//            painter->setRenderHint(QPainter::Antialiasing, true);
//            painter->setPen(Qt::NoPen);
//            painter->setBrush(palette.highlight());
            this->style()->drawControl(QStyle::CE_CheckBoxLabel, &option, painter);
        }

    }
    void mousePressEvent(QMouseEvent *event)
    {
        if (visualIndexAt(event->pos().x()) == m_checkColIdx)
        {
            if (isChecked)
                isChecked = false;
            else
                isChecked = true;
            this->updateSection(m_checkColIdx);
            emit checkStausChange(isChecked);
        }

        QHeaderView::mousePressEvent(event);
    }

private:
    bool isChecked;
    int m_checkColIdx;
};

#endif // MYHEADERVIEW_H
