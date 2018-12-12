#include "start_pushbuttondelegate.h"
#include <QPainter>
#include <QApplication>
#include <QStyleOption>
#include <QMouseEvent>
#include <QDialog>
#include <QDesktopWidget>
#include <QDebug>
start_PushButtonDelegate::start_PushButtonDelegate(QObject *parent):
    QStyledItemDelegate(parent)
{


}

void start_PushButtonDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionButton* button = m_btns.value(index.row());
    if (!button) {
        button = new QStyleOptionButton();
        button->rect = option.rect.adjusted(0, 0, 0, 0);
        button->iconSize = QSize(103,47);
        button->icon = QIcon(":/picture/unknowWidget/complate-up.png");
        button->state |= QStyle::State_Enabled;
        (const_cast<start_PushButtonDelegate *>(this))->m_btns.insert(index.row(), button);
    }
    if (option.state & QStyle::State_Selected) {
        painter->fillRect(option.rect, option.palette.highlight());

    }
    painter->restore();
    QApplication::style()->drawControl(QStyle::CE_PushButton, button, painter);
}



bool start_PushButtonDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
   if( m_btns.value(index.row())->state & QStyle::State_Selected ) {
        qDebug() << "当前按钮已经被选择";
        return false; //如果当前按钮被启动
   }
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent* e =(QMouseEvent*)event;
        if (option.rect.adjusted(4, 4, -4, -4).contains(e->x(), e->y()) && m_btns.contains(index.row())) {
            m_btns.value(index.row())->state |= QStyle::State_Sunken;
            m_btns.value(index.row())->icon = QIcon(":/picture/unknowWidget/complate-down.png");
        }
    }
    if (event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent* e =(QMouseEvent*)event;

        if (option.rect.adjusted(4, 4, -4, -4).contains(e->x(), e->y()) && m_btns.contains(index.row())) {
            m_btns.value(index.row())->state &= (~QStyle::State_Sunken);
            m_btns.value(index.row())->state |= QStyle::State_Selected;
            m_btns.value(index.row())->icon = QIcon(":/picture/unknowWidget/运行-up.png");
            qDebug() << "发送数据到下位机";
            emit startBtnClicked(index);
        }
    }

}





