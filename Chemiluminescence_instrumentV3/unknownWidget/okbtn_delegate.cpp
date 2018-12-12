#include "okbtn_delegate.h"
#include <QPainter>
#include <QApplication>
#include <QStyleOption>
#include <QMouseEvent>
#include <QDialog>
#include <QDesktopWidget>

okbtn_Delegate::okbtn_Delegate(QObject *parent):
    QStyledItemDelegate(parent)
{


}

void okbtn_Delegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionButton* button = OK_btns.value(index.row());
    if (!button) {
        button = new QStyleOptionButton();
        button->features |= QStyleOptionButton::AutoDefaultButton;
        button->rect = option.rect.adjusted(4, 4, -4, -4);
        button->iconSize = QSize(103,47);
        button->icon = QIcon(":/picture/unknowWidget/sure-up.png");
        button->state |= QStyle::State_Enabled;

        (const_cast<okbtn_Delegate *>(this))->OK_btns.insert(index.row(), button);
    }
    if (option.state & QStyle::State_Selected) {
        painter->fillRect(option.rect, option.palette.highlight());
    }
    painter->restore();
    QApplication::style()->drawControl(QStyle::CE_PushButtonLabel, button, painter);
}


bool okbtn_Delegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent* e =(QMouseEvent*)event;
        if (option.rect.adjusted(4, 4, -4, -4).contains(e->x(), e->y()) &&OK_btns.contains(index.row())) {
            OK_btns.value(index.row())->state |= QStyle::State_Sunken;
            OK_btns.value(index.row())->icon = QIcon(":/picture/unknowWidget/sure-down.png");
        }
    }
    if (event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent* e =(QMouseEvent*)event;

        if (option.rect.adjusted(4, 4, -4, -4).contains(e->x(), e->y()) && OK_btns.contains(index.row())) {
            OK_btns.value(index.row())->state &= (~QStyle::State_Sunken);
            OK_btns.value(index.row())->icon = QIcon(":/picture/unknowWidget/sure-up.png");
            emit OkBtnClicked(index);
        }
    }
}
